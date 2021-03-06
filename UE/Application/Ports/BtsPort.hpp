#pragma once

#include "IBtsPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "ITransport.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

class BtsPort : public IBtsPort
{
public:
    BtsPort(common::ILogger& logger, common::ITransport& transport, common::PhoneNumber phoneNumber);
    void sendSms(common::PhoneNumber recipient, std::string message) override;
    void sendCallRequest(common::PhoneNumber) override;
    void sendCallAccept(common::PhoneNumber recipient) override;
    void sendCallDropped(common::PhoneNumber recipient) override;
    void sendTalkMessage(const std::string, const common::PhoneNumber) override;
    void start(IBtsEventsHandler& handler);
    void stop();
    void sendCallDrop(common::PhoneNumber sender, common::PhoneNumber reciever) override;

    void sendAttachRequest(common::BtsId) override;

private:
    void handleMessage(BinaryMessage msg);
    void handleDisconnected();
    void handleCallDrop();
    common::PrefixedLogger logger;
    common::ITransport& transport;
    common::PhoneNumber phoneNumber;

    IBtsEventsHandler* handler = nullptr;
};

}
