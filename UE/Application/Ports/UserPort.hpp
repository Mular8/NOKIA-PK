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
    SmsSent,
    SmsReceived,
    SmsView
};

class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber, ISmsDatabase& db);
    constexpr static unsigned ListSmsItem = 1;
    constexpr static unsigned NewSmsItem = 0;
    std::pair<View, IUeGui::BaseMode*> getCurrentMode() { return std::pair(view, currentMode); };
    void setCurrentMode(View curView, IUeGui::BaseMode* mode) { view = curView; currentMode = mode; };
    void start(IUserEventsHandler& handler);
    void stop();
    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
    void showNewSms() override;
    void showSmsReceived() override;
    void showSmsList() override;
    void showMenu() override;
    void showSms(int id) override;
    void showComposeSmsMode() override;
private:
    IUeGui& gui;
    IUserEventsHandler* handler = nullptr;

    IUeGui::BaseMode* currentMode;
    common::PrefixedLogger logger;
    common::PhoneNumber phoneNumber;
    void handleHomeClicked();
    void handleAcceptClicked();
    void handleRejectClicked();
    View view;
    ISmsDatabase& db;
    int test=0;
};


}
