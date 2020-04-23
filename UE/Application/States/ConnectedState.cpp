#include "ConnectedState.hpp"

namespace ue
{
void ConnectedState::handleSendSms(common::PhoneNumber recipent, std::string message)
{
    context.bts.sendSms(recipent, message);
}
ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
}

}
