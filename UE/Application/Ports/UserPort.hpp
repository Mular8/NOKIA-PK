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
<<<<<<< Updated upstream
    SMS_SENT,
    SMS_RECEIVED
=======
    SmsSent,
    SmsReceived,
    SmsView,
    SentSmsView,
    NewCall,
    OutCall,
    InCall
>>>>>>> Stashed changes
};

class UserPort : public IUserPort
{
public:
<<<<<<< Updated upstream
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber);
=======
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber, ISmsDatabase& db, ISmsDatabase& db_w);
    constexpr static unsigned NewCallItem = 2;
>>>>>>> Stashed changes
    constexpr static unsigned ListSmsItem = 1;
    constexpr static unsigned NewSmsItem = 0;
    std::pair<View, IUeGui::BaseMode*> getCurrentMode() { return std::pair(View, currentMode); };
    void setCurrentMode(View curView, IUeGui::BaseMode* mode) { View = curView; currentMode = mode; };
    void start(IUserEventsHandler& handler);
    void stop();
    void showNotConnected() override;
    void showConnecting() override;
    void showConnected() override;
<<<<<<< Updated upstream
    void showReceivedSms() override;
=======
    void showNewSms() override;
    void showSmsReceived() override;
    void showSmsList() override;
    void showMenu() override;
    void showSms(int id) override;
    void showComposeSmsMode() override;
    void showSentSMSList() override;
    void showSentSMS(int id) override;
    void showCallRequest(common::PhoneNumber) override;
    void showCallDropped(common::PhoneNumber) override;
    void showPeerUserDisconnected() override;
    void showNotAvailable(common::PhoneNumber) override;
    void showPeerNotConnected(common::PhoneNumber) override;
    void showPeerConnected(common::PhoneNumber) override;
    void callTimeout() override;
>>>>>>> Stashed changes
private:
    IUeGui& gui;
    IUserEventsHandler* handler = nullptr;

    IUeGui::BaseMode* currentMode;
    common::PrefixedLogger logger;
    common::PhoneNumber fromPhoneNumber;
    common::PhoneNumber phoneNumber;
    void handleHomeClicked();
    void handleAcceptClicked();
    void handleRejectClicked();
    View View;
    ISmsDatabase* db = nullptr;
};


}
