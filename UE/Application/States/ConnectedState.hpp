#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleSendSms(common::PhoneNumber recipient, std::string message) final;
    void handleSmsReceived(common::PhoneNumber phoneNumber, std::string msg);
<<<<<<< Updated upstream

=======
    void handleReceivedCallRequest(common::PhoneNumber recipient) override;
    void handleReceivedCallAccepted(common::PhoneNumber recipient) override;
    void handleReceivedCallDropped(common::PhoneNumber recipient) override;
    void handleSendCallRequest(common::PhoneNumber from) final;
    void handleSendCallAccept(common::PhoneNumber from) final;
    void handleSendCallDropped(common::PhoneNumber from) final;
    void handleSendCallDrop(common::PhoneNumber) final;
    void handlePeerNotConnected(common::PhoneNumber) final;
    void handleTimeout() final;
>>>>>>> Stashed changes
};

}
