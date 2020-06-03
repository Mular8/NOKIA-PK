#include "ConnectedState.hpp"
<<<<<<< Updated upstream
#include "Sms/Sms.hpp"
=======
#include "SmsForDatabase/Sms.hpp"
#include "TalkingState.hpp"
>>>>>>> Stashed changes
namespace ue
{
void ConnectedState::handleSendSms(common::PhoneNumber recipient, std::string message)
{
    context.bts.sendSms(recipient, message);
}
ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    context.user.showConnected();
}
void ConnectedState::handleSmsReceived(common::PhoneNumber from,
                                       std::string text)
{
    Sms incomingSms(from,text);
    incomingSms.read = false;
    incomingSms.sent = false;
    context.db.insert(incomingSms);
    context.user.showReceivedSms();
}
void ConnectedState::handleSendCallRequest(common::PhoneNumber from)
{
    using namespace std::chrono_literals;
    context.bts.sendCallRequest(from);
    context.timer.startTimer(30s);
}

void ConnectedState::handleSendCallDrop(common::PhoneNumber from)
{
    context.logger.logDebug("Send call drop to", from);
    context.timer.stopTimer();
    context.bts.sendCallDropped(from);
}

void ConnectedState::handlePeerNotConnected(common::PhoneNumber from)
{
    context.logger.logDebug("Recieved Unknown Recipient after CallRequest");
    context.timer.stopTimer();
    context.user.showPeerNotConnected(from);
}
void ConnectedState::handleSendCallAccept(common::PhoneNumber from)
{
    context.bts.sendCallAccept(from);
    context.setState<TalkingState>(from);
}

void ConnectedState::handleSendCallDropped(common::PhoneNumber from)
{
    context.user.showConnected();
    context.bts.sendCallDropped(from);
}
void ConnectedState::handleTimeout()
{
    context.logger.logDebug("Timeout: ");
    context.user.callTimeout();
}
}
