#include "NotConnectedState.hpp"
#include "TalkingState.hpp"

namespace ue
{

TalkingState::TalkingState(Context& context, common::PhoneNumber from)
    :BaseState(context, "Talking State"),
      from(from)
{
}


}
