#pragma once

#include "IUserPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "IUeGui.hpp"
#include "Messages/PhoneNumber.hpp"
#include "ISmsDatabasePort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"

namespace ue
{
class UserPort : public IUserPort
{
public:
    UserPort(common::ILogger& logger, IUeGui& gui, common::PhoneNumber phoneNumber, ISmsDatabase& db, ISmsDatabase& db_w);
    constexpr static unsigned NewCallItem = 2;
    constexpr static unsigned ListSmsItem = 1;
    constexpr static unsigned NewSmsItem = 0;
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
    void showSentSMSList() override;
    void showSentSMS(int id) override;
    std::string encrypted(std::string sms) override;
    std::string decrypted(std::string sms) override;
    void showNotAvailable(common::PhoneNumber) override;
    void showPeerNotConnected(common::PhoneNumber) override;
    void showPeerConnected(common::PhoneNumber) override;
    void showCallRequest(common::PhoneNumber) override;
    void showPeerUserDisconnected() override;
    void showCallDropped(common::PhoneNumber) override;
    void callTimeout() override;
    void showStartDialView() override;
    void showCallView(const std::string incomingText) override;
    void showDialingView(common::PhoneNumber to) override;
    void showPeerUeBecomesUnknown(common::PhoneNumber phoneNumber) override;
    void clearCallMessages() override;
private:
    IUeGui& gui;
    IUserEventsHandler* handler = nullptr;

    IUeGui::BaseMode* currentMode;
    common::PrefixedLogger logger;
    common::PhoneNumber phoneNumber;
    common::PhoneNumber fromPhoneNumber;
    common::PhoneNumber reciever;
    void handleHomeClicked();
    void handleAcceptClicked();
    void handleRejectClicked();
    ISmsDatabase& db;
    ISmsDatabase& db_w;
    int test=0;
};


}
