#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{

public:
    ConnectedState(Context& context);
    void handleSendSms(common::PhoneNumber recipient, std::string message) final;
    void handleSendCallRequest(common::PhoneNumber recipient) final;
    void handleSmsReceived(common::PhoneNumber phoneNumber, std::string msg);
    void handleReceivedCallRequest(common::PhoneNumber recipient) override;
    void handleReceivedCallAccepted(common::PhoneNumber recipient) override;
    void handleReceivedCallDropped(common::PhoneNumber recipient) override;
    void handleSendCallDrop(common::PhoneNumber) final;
    void handlePeerNotConnected(common::PhoneNumber) final;
    void handleTimeout() final;
    void handleSendCallAccept(common::PhoneNumber recipient) final;
    void handleSendCallDropped(common::PhoneNumber recipient) final;
    void handlePeerUeBecomesUnknown() final;

private:
    common::PhoneNumber currentlyDialedPhoneNumber;
};

}
