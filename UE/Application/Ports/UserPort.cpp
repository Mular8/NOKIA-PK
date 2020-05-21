#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "Database/SmsDatabase.hpp"


namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber) : logger(logger, "[USER-PORT]"),
      gui(gui),
      currentMode(nullptr),
      phoneNumber(phoneNumber),
      View(View::Status)

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

    auto menu = (IUeGui::IListViewMode*) &gui.setListViewMode();
    menu->clearSelectionList();
    menu->addSelectionListItem("View SMS", "List all new messages");
    menu->addSelectionListItem("Compose SMS", "New SMS");
    setCurrentMode(View::HomeMenu, menu);
    gui.showConnected();
}

void UserPort::showSmsListViewSent(){
    IUeGui::IListViewMode& smsListView = gui.setListViewMode();
    std::vector<Sms> tab = smsDatabase.getAll();
    int smsFromDb;
    for(int i = 0; i < tab.size(); i++){
        if(tab.at(i).sent == false){
            smsFromDb = tab.at(i).phoneNumber;
            std::string str = std::to_string(smsFromDb);
            smsListView.addSelectionListItem(str,"");
            gui.setAcceptCallback([&](){

            });
            gui.setRejectCallback([&](){
                showConnected();
            });
        }
    }
}


void UserPort::showReceivedSms()
{
    gui.showNewSms();
}
}
