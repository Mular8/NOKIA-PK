#include "ConnectedState.hpp"
#include "Sms/Sms.hpp"
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
    context.db.insert(incomingSms);
    context.user.showNewSms();
}
}
