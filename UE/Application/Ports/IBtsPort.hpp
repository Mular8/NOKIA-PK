#pragma once
#include "Messages/PhoneNumber.hpp"
#include "Messages/BtsId.hpp"
#include "Messages/PhoneNumber.hpp"
namespace ue
{

class IBtsEventsHandler
{
public:
    virtual ~IBtsEventsHandler() = default;

    virtual void handleDisconnected() = 0;
    virtual void handleSib(common::BtsId) = 0;
    virtual void handleAttachAccept() = 0;
    virtual void handleAttachReject() = 0;
    virtual void handleSmsReceived(common::PhoneNumber, std::string) = 0;
    virtual void handleReceivedCallRequest(common::PhoneNumber recipient) = 0;
    virtual void handleReceivedCallAccepted(common::PhoneNumber) = 0;
    virtual void handleReceivedCallDropped(common::PhoneNumber) = 0;
    virtual void handlePeerNotConnected(common::PhoneNumber) = 0;
    virtual void handleTalkMessage(const std::string) = 0;
    virtual void handlePeerUeBecomesUnknown() = 0;
    virtual void handleCallDrop() = 0;
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;
    virtual void sendSms(common::PhoneNumber, std::string) = 0;
    virtual void sendAttachRequest(common::BtsId) = 0;
    virtual void sendCallRequest(common::PhoneNumber) = 0;
    virtual void sendCallAccept(common::PhoneNumber) = 0;
    virtual void sendCallDropped(common::PhoneNumber) = 0;
    virtual void sendTalkMessage(const std::string, const common::PhoneNumber) = 0;
    virtual void sendCallDrop(common::PhoneNumber, common::PhoneNumber) = 0;
};

}
