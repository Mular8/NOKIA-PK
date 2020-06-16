#include "UserPort.hpp"
#include "SmsDatabasePort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/ICallMode.hpp"
#include "UeGui/IDialMode.hpp"

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber, ISmsDatabase &db, ISmsDatabase &db_w) : logger(logger, "[USER-PORT]"),
      gui(gui),
      currentMode(nullptr),
      phoneNumber(phoneNumber),
      db(db),
      db_w(db_w)

{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
    logger.logDebug("UserPort started");
    gui.setHomeCallback([this](){handleHomeClicked();});
}

void UserPort::stop()
{
    handler = nullptr;
    gui.setRejectCallback(nullptr);
    gui.setAcceptCallback(nullptr);
    gui.setHomeCallback(nullptr);

}

void UserPort::handleHomeClicked()
{
    showMenu();
}

void UserPort::showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    gui.showConnecting();
}

void UserPort::showConnected()
{
    gui.showConnected();
    showMenu();
}

void UserPort::showSmsReceived()
{
    gui.showSmsReceived();
}

void UserPort::showNewSms()
{
    gui.showNewSms();
}

void UserPort::showPeerUeBecomesUnknown(common::PhoneNumber phoneNumber){
    gui.showPeerUserNotAvailable(phoneNumber);
}

void UserPort::showSmsList()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    std::vector<Sms> smsList=db.getAll();
    if(db.size()==0) {
        menu.addSelectionListItem("No messages","");
        gui.setAcceptCallback([&](){
        });
    }
    else
    {
        for(Sms sms : smsList)
        {
                menu.addSelectionListItem(to_string(sms.from)+(sms.read==false?"\tNew":"\tSeen"),sms.message);
        }
        gui.setAcceptCallback([&](){
            showSms(menu.getCurrentItemIndex().second);
        });
    }
    gui.setRejectCallback([&](){
        showMenu();
    });
}

void UserPort::showSms(int id)
{
    IUeGui::ITextMode& menu = gui.setViewTextMode();
    Sms* sms = db.get(id);
    std::string text="From: "+to_string(sms->from)+"\n\n"+decrypted(sms->message);
    menu.setText(text);
    sms->read=true;
    bool allRead=true;
    for(Sms sms : db.getAll())
        if(sms.read==false){allRead=false;break;}
    if(allRead==true)showSmsReceived();
    gui.setRejectCallback([&](){
        showSmsList();
    });
}

void UserPort::showStartDialView(){
    IUeGui::IDialMode& callView = gui.setDialMode();
    gui.setAcceptCallback([&](){
        handler->handleSendCallRequest(callView.getPhoneNumber());
        showCallView("");
    });
    gui.setRejectCallback([&](){
        showMenu();
    });
}

void UserPort::showDialingView(common::PhoneNumber to){
    IUeGui::ITextMode& dialingView = gui.setAlertMode();
    reciever = to;
    dialingView.setText("Calling...");
    gui.setAcceptCallback(nullptr);
    gui.setRejectCallback([&, to]{
        reciever.value = 0;
        handler->handleSendCallDropped(to);
    });
}

void UserPort::showCallView(const std::string incomingText){
    IUeGui::ICallMode& callView = gui.setCallMode();
    callView.appendIncomingText(incomingText);
    gui.setAcceptCallback([&](){
        handler->handleSendTalkMessage(callView.getOutgoingText());
        callView.clearOutgoingText();

    });
    gui.setRejectCallback([&](){
        if(reciever.value != 0){
            handler->handleSendCallDrop(phoneNumber, reciever);
        }
        else showMenu();

    });
}

void UserPort::showMenu()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("View SMS", "List all new messages");
    menu.addSelectionListItem("Compose SMS", "New SMS");
    menu.addSelectionListItem("Sent SMS list", "Sent messages list");
    menu.addSelectionListItem("Make a call", "");
    gui.setAcceptCallback([&](){
        switch(menu.getCurrentItemIndex().second){
            case 0:
                showSmsList();
                break;
            case 1:
                showComposeSmsMode();
                break;
            case 2:
                showSentSMSList();
                break;
            case 3:
                showStartDialView();
        }
    });
    gui.setRejectCallback([&](){
    });

}

void UserPort::showComposeSmsMode()
{
     IUeGui::ISmsComposeMode& composeMode = gui.setSmsComposeMode();
     composeMode.clearSmsText();
     gui.setAcceptCallback([&](){
         handler->handleSendSms(composeMode.getPhoneNumber(),encrypted(composeMode.getSmsText()));
         composeMode.clearSmsText();
         showMenu();
     });
     gui.setRejectCallback([&]()
     {
         showMenu();
     });
}
void UserPort::showSentSMSList(){

    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    std::vector<Sms> smsList=db_w.getAll();
    if(db_w.size()==0) menu.addSelectionListItem("No messages","");
    else
    {
    for(Sms sms : smsList)
    {
        menu.addSelectionListItem(to_string(sms.from)+(sms.read==false?"\tNew":""),sms.message);
    }
    gui.setAcceptCallback([&](){

        showSentSMS(menu.getCurrentItemIndex().second);

    });
    }
    gui.setRejectCallback([&]()
    {
        showMenu();
    });
}
void UserPort::showSentSMS(int id)
{
    IUeGui::ITextMode& menu = gui.setViewTextMode();
    Sms* sms = db_w.get(id);
    std::string text="To: "+to_string(sms->from)+"\n\n"+decrypted(sms->message);
    menu.setText(text);
    sms->read=true;
    bool allRead=true;
    for(Sms sms : db_w.getAll())
        if(sms.read==false){allRead=false;break;}
    if(allRead==true)showSmsReceived();
    gui.setRejectCallback([&]()
    {
        showSentSMSList();
    });
}

std::string UserPort::encrypted(std::string sms)
{


    for(int i = 0; i < sms.length(); ++i){
        sms[i] = sms[i] + 3;
    }
    return sms;

}

std::string UserPort::decrypted(std::string sms)
{
    for(int i = 0; i < sms.length(); ++i){
        sms[i] = sms[i] - 3;
    }
    return sms;

}
void UserPort::showCallRequest(common::PhoneNumber from)
{
    IUeGui::ITextMode& info= gui.setAlertMode();
    info.setText("Incoming from " + std::to_string(from.value));


    gui.setAcceptCallback([&, from]{
        reciever = from;
        handler->handleSendCallAccept(from);
    });
    gui.setRejectCallback([&, from]{
        reciever.value = 0;
        handler->handleSendCallDropped(from);
    });
}

void UserPort::showPeerUserDisconnected()
{
    IUeGui::ICallMode& info=gui.setCallMode();
    info.appendIncomingText("Unknown recipient");
}

void UserPort::showNotAvailable(common::PhoneNumber from)
{
    gui.showPeerUserNotAvailable(from);
}

void UserPort::showPeerNotConnected(common::PhoneNumber from)
{
    IUeGui::ICallMode& info=gui.setCallMode();
    info.appendIncomingText(to_string(from)+" is not available");
    showConnected();
}

void UserPort::showPeerConnected(common::PhoneNumber from)
{
    IUeGui::ICallMode& info=gui.setCallMode();
    info.appendIncomingText("Connected to "+to_string(from));
}

void UserPort::showCallDropped(common::PhoneNumber from)
{
    IUeGui::ICallMode& info=gui.setCallMode();
    info.appendIncomingText("Drop call");
    showConnected();
}

void UserPort::callTimeout()
{
    handler->handleSendCallDrop(fromPhoneNumber,phoneNumber);
    showConnected();
}

void UserPort::clearCallMessages(){
    IUeGui::ICallMode& callView = gui.setCallMode();
    callView.clearIncomingText();
}
}
