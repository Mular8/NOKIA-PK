#include "UserPort.hpp"
#include "Database/ISmsDatabase.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ITextMode.hpp"

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber, ISmsDatabase &db) : logger(logger, "[USER-PORT]"),
      gui(gui),
      currentMode(nullptr),
      phoneNumber(phoneNumber),
      View(View::Status),
      db(db)

{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;
    gui.setTitle("Nokia " + to_string(phoneNumber));
    gui.setRejectCallback([this]() { handleRejectClicked(); });
    gui.setAcceptCallback([this]() { handleAcceptClicked(); });
    db.insert(Sms{PhoneNumber{23},"Fwgaewhawehawha"});
    db.insert(Sms{PhoneNumber{25},"Fgegawgawgawwa"});
    db.insert(Sms{PhoneNumber{53},"HSeregseehawha"});
    db.insert(Sms{PhoneNumber{65},"Fgre"});

}

void UserPort::stop()
{
    handler = nullptr;
    gui.setRejectCallback(nullptr);
    gui.setAcceptCallback(nullptr);

}

void UserPort::handleAcceptClicked()
{
    auto current = getCurrentMode();
    switch(current.first) {
    case View::NewSms: {
        auto menu = (IUeGui::ISmsComposeMode*)current.second;
        auto recipient = menu->getPhoneNumber();
        auto text = menu->getSmsText();
        handler->handleSendSms(recipient, text);
        menu->clearSmsText();
        showConnected();
        break;
    }
    case View::HomeMenu: {
        auto currentItem = ((IUeGui::IListViewMode*)current.second)->getCurrentItemIndex();
        if(currentItem.first && currentItem.second == UserPort::NewSmsItem) {
            setCurrentMode(View::NewSms, &gui.setSmsComposeMode());
            }
        else if(currentItem.first && currentItem.second == UserPort::ListSmsItem)
        {
            showSmsList();
        }
        break;
        }
    case View::SmsList:
    {
        auto currentItem = ((IUeGui::IListViewMode*)current.second)->getCurrentItemIndex();
        if(currentItem.first)
        {
            showSms(currentItem.second + 1);
        }
        break;
    }
    default: {
        break;
         }
    }
}

void UserPort::handleRejectClicked()
{
    switch(View) {
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
    }

}

void UserPort::handleHomeClicked()
{

}

void UserPort::showNotConnected()
{
    View = View::Status;
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    View = View::Status;
    gui.showConnecting();
}

void UserPort::showConnected()
{
    gui.showConnected();
    showMenu();
}


void UserPort::showReceivedSms()
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
        menu.addSelectionListItem(to_string(sms.from)+(sms.read==true?"\tNew":""),sms.message);
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
    std::string text="From: "+to_string(sms->from)+"\n\n"+sms->message;
    menu.setText(text);
    sms->read=false;
    setCurrentMode(View::SmsView, &menu);
}

void UserPort::showMenu()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("View SMS", "List all new messages");
    menu.addSelectionListItem("Compose SMS", "New SMS");
    setCurrentMode(View::HomeMenu, &menu);
    gui.setAcceptCallback([&](){
        switch(menu.getCurrentItemIndex().second){
            case 0:
                showSmsList();
                break;
            case 1:
                setCurrentMode(View::NewSms, &gui.setSmsComposeMode());
                break;
        }
    });

}
}
