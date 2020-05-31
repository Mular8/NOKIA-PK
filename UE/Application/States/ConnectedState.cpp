#include "ConnectedState.hpp"
#include "Sms/Sms.hpp"
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
}
void ConnectedState::handleReceivedCallDropped(common::PhoneNumber recipient)
{
    context.logger.logDebug("Received Call dropped from ", recipient);
}
void ConnectedState::handleReceivedCallRequest(common::PhoneNumber recipient)
{
    context.logger.logDebug("Received Call request from ", recipient);
}
}
