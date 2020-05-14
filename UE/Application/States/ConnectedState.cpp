#include "ConnectedState.hpp"
#include "Sms/Sms.hpp"
namespace ue
{

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
}
