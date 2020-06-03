#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"

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


void UserPort::showReceivedSms()
{
    gui.showNewSms();
}
<<<<<<< Updated upstream
=======
void UserPort::showCallDropped(common::PhoneNumber from)
{
    auto mode = (IUeGui::ICallMode *)currentMode;
    mode->appendIncomingText("Drop call");
    showConnected();
}
void UserPort::showNotAvailable(common::PhoneNumber from)
{
    gui.showPeerUserNotAvailable(from);
}

void UserPort::showPeerNotConnected(common::PhoneNumber from)
{
    auto mode = (IUeGui::ICallMode *)currentMode;
    mode->appendIncomingText(to_string(from)+" is not available");
    showConnected();
}

void UserPort::showPeerConnected(common::PhoneNumber from)
{
    auto mode = (IUeGui::ICallMode *)currentMode;
    mode->appendIncomingText("Connected to "+to_string(from));
}
void UserPort::showCallRequest(common::PhoneNumber from)
{
    fromPhoneNumber = from;
    setCurrentMode(View::InCall, &gui.setCallMode());
    auto info = (IUeGui::ICallMode*) currentMode;
    info->appendIncomingText("From " + to_string(from));
}
void UserPort::showPeerUserDisconnected()
{
    auto info = (IUeGui::ICallMode*) currentMode;
    info->appendIncomingText("Recipient unknown");
}
void UserPort::callTimeout()
{
    handler->handleSendCallDrop(fromPhoneNumber);
    showConnected();
}
>>>>>>> Stashed changes
}
