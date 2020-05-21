#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Database/ISmsDatabase.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"

namespace ue
{
enum class View {
    Status,
    HomeMenu,
    NewSms,
    SmsList,
    SMS_SENT,
    SMS_RECEIVED
};

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber, ISmsDatabase& db);
    constexpr static unsigned ListSmsItem = 1;
    constexpr static unsigned NewSmsItem = 0;
    std::pair<View, IUeGui::BaseMode*> getCurrentMode() { return std::pair(View, currentMode); };
    void setCurrentMode(View curView, IUeGui::BaseMode* mode) { View = curView; currentMode = mode; };
    void start(IUserEventsHandler& handler);
    void stop();
    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void showReceivedSms() override;
    void showSmsList() override;
    void showMenu() override;
private:
    IUeGui& gui;
    IUserEventsHandler* handler = nullptr;

    IUeGui::BaseMode* currentMode;
    common::PrefixedLogger logger;
    common::PhoneNumber phoneNumber;
    void handleHomeClicked();
    void handleAcceptClicked();
    void handleRejectClicked();
    View View;
    ISmsDatabase& db;
};


}
