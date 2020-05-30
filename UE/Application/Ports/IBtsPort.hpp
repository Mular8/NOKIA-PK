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
};

class IBtsPort
{
public:
    virtual ~IBtsPort() = default;
    virtual void sendSms(common::PhoneNumber, std::string) = 0;
    virtual void sendAttachRequest(common::BtsId) = 0;
};

}
