#include "ConnectedState.hpp"
#include "SmsForDatabase/Sms.hpp"
#include "TalkingState.hpp"
namespace ue
{
void ConnectedState::handleSendSms(common::PhoneNumber recipient, std::string message)
{
    context.bts.sendSms(recipient, message);
    Sms sentSms(recipient, message);
    sentSms.read=true;
    context.db_w.insert(sentSms);

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
    context.db.insert(incomingSms);
    context.user.showNewSms();
}
void ConnectedState::handleReceivedCallAccepted(common::PhoneNumber recipient)
{
    context.logger.logDebug("Received Call Accepted from ", recipient);
    context.user.showPeerConnected(recipient);
    context.setState<TalkingState>(recipient);
}
void ConnectedState::handleReceivedCallDropped(common::PhoneNumber recipient)
{
    context.logger.logDebug("Received Call dropped from ", recipient);
    context.user.showCallDropped(recipient);
}
void ConnectedState::handleReceivedCallRequest(common::PhoneNumber recipient)
{
    context.user.showCallRequest(recipient);
    context.logger.logDebug("Received Call request from ", recipient);
}
void ConnectedState::handleSendCallRequest(common::PhoneNumber from)
{
    using namespace std::chrono_literals;
    context.bts.sendCallRequest(from);
    //context.timer.startTimer(30s);
}
void ConnectedState::handleTimeout()
{
    context.logger.logDebug("Timeout ");
    context.user.callTimeout();
}

void ConnectedState::handleSendCallDropped(common::PhoneNumber from)
{
    context.logger.logDebug("Send Call Drop", from);
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

void ConnectedState::handlePeerUeBecomesUnknown()
{
    context.timer.stopTimer();
    context.user.showPeerUeBecomesUnknown(this->currentlyDialedPhoneNumber);
    context.setState<ConnectedState>();
}

void ConnectedState::handleCallDrop(){
    context.user.clearCallMessages();
    context.user.showMenu();
    context.timer.stopTimer();
}

}
