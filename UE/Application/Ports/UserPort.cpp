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
      view(View::Status),
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
    view = View::Status;
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    view = View::Status;
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
    if(db.size()==0) menu.addSelectionListItem("No messages","");
    else
    {
        for(Sms sms : smsList)
        {
            if(sms.read == false){
                menu.addSelectionListItem(to_string(sms.from)+(sms.read==false?"\tNew":""),sms.message);
            }
            if(sms.read == true){
                menu.addSelectionListItem(to_string(sms.from)+(sms.read==true?"\tSeen":""),sms.message);
            }

        }
        gui.setAcceptCallback([&](){
            showSms(menu.getCurrentItemIndex().second);
        });
    }
    gui.setRejectCallback([&](){
        showMenu();
    });
    setCurrentMode(View::SmsList,&menu);
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
    setCurrentMode(View::SmsView, &menu);
    gui.setRejectCallback([&](){
        showSmsList();
    });
}

void UserPort::showStartDialView(){
    IUeGui::IDialMode& callView = gui.setDialMode();
    gui.setAcceptCallback([&](){
        handler->handleSendCallRequest(callView.getPhoneNumber());
    });
    gui.setRejectCallback([&](){
        showMenu();
    });
}

void UserPort::showDialingView(common::PhoneNumber to){
    IUeGui::ITextMode& dialingView = gui.setAlertMode();
    dialingView.setText("Calling...");
    gui.setAcceptCallback(nullptr);
    gui.setRejectCallback([&]{
        handler->handleSendCallDropped(to);
    });
}

void UserPort::showCallView(const std::string incomingText){
    IUeGui::ICallMode& callView = gui.setCallMode();
    callView.appendIncomingText(incomingText);
    gui.setAcceptCallback([&] (){
        handler->handleSendTalkMessage(callView.getOutgoingText());
        callView.clearOutgoingText();

    });
    gui.setRejectCallback(nullptr);
}

void UserPort::showMenu()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("View SMS", "List all new messages");
    menu.addSelectionListItem("Compose SMS", "New SMS");
    menu.addSelectionListItem("Sent SMS list", "Sent messages list");
    menu.addSelectionListItem("Make a call", "");
    setCurrentMode(View::HomeMenu, &menu);
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
     setCurrentMode(View::NewSms, &composeMode);
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
    setCurrentMode(View::SmsList,&menu);
}
void UserPort::showSentSMS(int id)
{
    IUeGui::ITextMode& menu = gui.setViewTextMode();
    Sms* sms = db_w.get(id);
    std::string text="To: "+to_string(sms->from)+"\n\n"+sms->message;
    menu.setText(text);
    sms->read=true;
    bool allRead=true;
    for(Sms sms : db_w.getAll())
        if(sms.read==false){allRead=false;break;}
    if(allRead==true)showSmsReceived();
    setCurrentMode(View::SentSmsView, &menu);
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
    IUeGui::ITextMode& info= gui.setViewTextMode();
    setCurrentRecipent(from);
    setCurrentMode(View::IncCall, &info);
    info.setText("Incoming from " + to_string(from));
    gui.setAcceptCallback([&]{
        fromPhoneNumber = phoneNumber;
        handler->handleSendCallAccept(phoneNumber);
    });
    gui.setRejectCallback([&]{
        handler->handleSendCallDropped(phoneNumber);
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
    setCurrentMode(View::Call, &info);
}

void UserPort::showCallDropped(common::PhoneNumber from)
{
    IUeGui::ICallMode& info=gui.setCallMode();
    info.appendIncomingText("Drop call");
    showConnected();
}

void UserPort::callTimeout()
{
    handler->handleSendCallDrop(fromPhoneNumber);
    showConnected();
}

void UserPort::setCurrentRecipent(common::PhoneNumber from)
{
    fromPhoneNumber = from;
}

common::PhoneNumber UserPort::getCurrentRecipent()
{
    return fromPhoneNumber;
}
}
