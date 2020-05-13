#include "ConnectedState.hpp"

namespace ue
{
void ConnectedState::handleSendSms(common::PhoneNumber recipient, std::string message)
{
    context.bts.sendSms(recipient, message);
}
ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
}

}
