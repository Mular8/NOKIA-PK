#include "NotConnectedState.hpp"
#include "TalkingState.hpp"
#include "ConnectedState.hpp"

namespace ue {

TalkingState::TalkingState(Context& context, const common::PhoneNumber from)
    : BaseState(context, "TalkingState"), from{from}
{
    context.user.showCallView("");
}

void TalkingState::handleSendTalkMessage(const std::string message){
    //context.timer.stopTimer();
    using namespace std::chrono_literals;
    //context.timer.startTimer(120000ms);
    context.bts.sendTalkMessage(message, from);
}

void TalkingState::handleTalkMessage(const std::string message){
    //context.timer.stopTimer();
    using namespace std::chrono_literals;
    //context.timer.startTimer(120000ms);
    context.user.showCallView(message);
}

void TalkingState::handlePeerUeBecomesUnknown()
{
    //context.timer.stopTimer();
    context.user.showPeerUeBecomesUnknown(this->from);
    context.setState<ConnectedState>();
}

}
