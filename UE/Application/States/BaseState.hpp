#pragma once
#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Context.hpp"
#include "Messages/PhoneNumber.hpp"
namespace ue
{

class BaseState : public IEventsHandler
{
public:
    BaseState(Context& context, const std::string& name);
    ~BaseState() override;

    // ITimerEventsHandler interface
    void handleTimeout() override;
    //IUserEventsHandler interface
    void handleSendSms(common::PhoneNumber recipient, std::string message) override;
    // IBtsEventsHandler interface
    void handleDisconnected() override;
    void handleSib(common::BtsId btsId) override;
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleSmsReceived(common::PhoneNumber from, std::string text) override;
    void handleReceivedCallRequest(common::PhoneNumber recipient) override;
    void handleReceivedCallAccepted(common::PhoneNumber recipient) override;
    void handleReceivedCallDropped(common::PhoneNumber recipient) override;
protected:
    Context& context;
private:
    common::PrefixedLogger logger;
};

}
