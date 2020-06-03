#include "ConnectedState.hpp"
#include "TalkingState.hpp"

namespace ue
{

TalkingState::TalkingState(Context& context, common::PhoneNumber from)
    :BaseState(context, "TalkingState"),from(from)
{
}
void TalkingState::handlePeerNotConnected(common::PhoneNumber from)
{
    context.user.showPeerNotConnected(from);
    context.setState<ConnectedState>();
}
void TalkingState::handleTimeout()
{
    context.bts.sendCallDropped(from);
    context.user.showCallDropped(from);
    context.setState<ConnectedState>();
}
}
