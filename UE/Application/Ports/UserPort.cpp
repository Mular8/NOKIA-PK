#include "UserPort.hpp"
#include "Database/ISmsDatabase.hpp"
#include "UeGui/IListViewMode.hpp"

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

}

void UserPort::stop()
{
    handler = nullptr;
    gui.setRejectCallback(nullptr);
    gui.setAcceptCallback(nullptr);

}
void UserPort::handleRejectClicked()
{
    auto current = getCurrentMode();
    switch(current.first) {
        case View::NewSms: {
            auto menu = (IUeGui::ISmsComposeMode*)current.second;
            menu->clearSmsText();
            showConnected();
        }
        default: {
            break;
        }
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
            break;
        }
        default: {
            break;
         }
    }
}


void UserPort::showConnected()
{
    gui.showConnected();
    showMenu();
    //showSmsList();
}


void UserPort::showReceivedSms()
{
    gui.showNewSms();
}

void UserPort::showSmsList()
{
    auto menu = (IUeGui::IListViewMode*) &gui.setListViewMode();
    menu->clearSelectionList();
    std::vector<Sms> smsList=db.getAll();
    if(db.size()==0) menu->addSelectionListItem("No messages","");
    for(Sms sms : smsList)
    {
        menu->addSelectionListItem((sms.read==true?"- ":"+ ")+to_string(sms.from),sms.message);
    }
    setCurrentMode(View::SmsList,menu);
}

void UserPort::showMenu()
{
    auto menu = (IUeGui::IListViewMode*) &gui.setListViewMode();
    menu->clearSelectionList();
    menu->addSelectionListItem("View SMS", "List all new messages");
    menu->addSelectionListItem("Compose SMS", "New SMS");
    setCurrentMode(View::HomeMenu, menu);
}
}
