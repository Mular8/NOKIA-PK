#include "UserPort.hpp"
#include "SmsDatabasePort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ITextMode.hpp"
#include "UeGui/ICallMode.hpp"

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
    gui.setRejectCallback([this]() { handleRejectClicked(); });
    gui.setAcceptCallback([this]() { handleAcceptClicked(); });
    logger.logDebug("UserPort started");
}

void UserPort::stop()
{
    handler = nullptr;
    gui.setRejectCallback(nullptr);
    gui.setAcceptCallback(nullptr);

}

void UserPort::handleAcceptClicked()
{
}

void UserPort::handleRejectClicked()
{
    switch(view) {
    case View::HomeMenu:
        break;
    case View::SmsList:
        showMenu();
        break;
    case View::SmsView:
        showSmsList();
        break;
    case View::NewSms:
        showMenu();
        break;
    case View::SentSmsView:
        showSentSMSList();
        break;
    }

}

void UserPort::handleHomeClicked()
{

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
            menu.addSelectionListItem(to_string(sms.from)+(sms.read==false?"\tNew":""),sms.message);
        }
        gui.setAcceptCallback([&](){
            showSms(menu.getCurrentItemIndex().second);
        });
    }
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
}

void UserPort::showMenu()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("View SMS", "List all new messages");
    menu.addSelectionListItem("Compose SMS", "New SMS");
    menu.addSelectionListItem("Sent SMS list", "Sent messages list");
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
        }
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

}
