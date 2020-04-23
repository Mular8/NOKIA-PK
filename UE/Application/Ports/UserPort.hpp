#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
    constexpr static unsigned ListSmsItem = 1;
    constexpr static unsigned NewSmsItem = 0;
    std::pair<CurrentView, IUeGui::BaseMode*> getCurrentMode() { return std::pair(currentView, currentMode); };
    void setCurrentMode(CurrentView curView, IUeGui::BaseMode* mode) { currentView = curView; currentMode = mode; };
    void start(IUserEventsHandler& handler);
    void stop();

    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;

private:
    IUeGui& gui;
    IUserEventsHandler* handler = nullptr;
    IUeGui::BaseMode* currentMode;
    common::PrefixedLogger logger;
    common::PhoneNumber phoneNumber;
    void handleHomeClicked();
    void handleAcceptClicked();
    void handleRejectClicked();
    CurrentView currentView;

};
enum class CurrentView {
    Status,
    HomeMenu,
    NewSms,
    SmsList
};

}
