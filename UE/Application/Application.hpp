#pragma once

#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"
#include "IEventsHandler.hpp"
#include "Context.hpp"

namespace ue
{

using common::PhoneNumber;
using common::ILogger;

class Application : public IEventsHandler
{
public:
    Application(PhoneNumber phoneNumber,
                ILogger& iLogger,
                IBtsPort& bts,
                IUserPort& user,
                ITimerPort& timer,
                ISmsDatabase& db
                , ISmsDatabase& db_w);
    ~Application();
    void handleSendSms(common::PhoneNumber from, std::string message) override;
    void handleSendCallAccept(common::PhoneNumber from) override;
    void handleSendCallRequest(common::PhoneNumber from) override;
    void handleSendCallDropped(common::PhoneNumber from) override;

    // ITimerEventsHandler interface
    void handleTimeout() override;

    // IBtsEventsHandler interface
    void handleSib(common::BtsId btsId) override;
    void handleDisconnected() override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleSmsReceived(common::PhoneNumber PhoneNumber, std::string msg) override;
    void handleReceivedCallRequest(common::PhoneNumber PhoneNumber) override;
    void handleReceivedCallAccepted(common::PhoneNumber PhoneNumber) override;
    void handleReceivedCallDropped(common::PhoneNumber PhoneNumber) override;
    void handleSendCallDrop(common::PhoneNumber sender, common::PhoneNumber reciever) override;
    virtual void handlePeerNotConnected(common::PhoneNumber) override;
    void handleSendTalkMessage(const std::string incomingMessage) override;
    void handleTalkMessage(const std::string) override;
    void handlePeerUeBecomesUnknown() override;
    void handleCallDrop() override;



private:
    Context context;
    common::PrefixedLogger logger;

};

}
