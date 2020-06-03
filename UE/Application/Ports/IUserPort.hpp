#pragma once
#include "Messages/PhoneNumber.hpp"
#include "IUeGui.hpp"


namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
    virtual void handleSendSms(common::PhoneNumber from, std::string message) = 0;
    virtual void handleSendCallRequest(common::PhoneNumber from) = 0;
    virtual void handleSendCallAccept(common::PhoneNumber from) = 0;
    virtual void handleSendCallDropped(common::PhoneNumber from) = 0;
    virtual void handleSendCallDrop(common::PhoneNumber) = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
<<<<<<< Updated upstream
    virtual void showReceivedSms() = 0;
=======
    virtual void showNewSms() = 0;
    virtual void showSmsList() = 0;
    virtual void showMenu() = 0;
    virtual void showSms(int id) = 0;
    virtual void showComposeSmsMode() = 0;
    virtual void showSmsReceived() = 0;
    virtual void showSentSMSList() = 0;
    virtual void showSentSMS(int id) = 0;
    virtual void showCallRequest(common::PhoneNumber) = 0;
    virtual void showNotAvailable(common::PhoneNumber) = 0;
    virtual void showPeerConnected(common::PhoneNumber) = 0;
    virtual void showPeerNotConnected(common::PhoneNumber) = 0;
    virtual void showCallDropped(common::PhoneNumber) = 0;
    virtual void showPeerUserDisconnected() = 0;
    virtual void callTimeout() = 0;
>>>>>>> Stashed changes
};

}
