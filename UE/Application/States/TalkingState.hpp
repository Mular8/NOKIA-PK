#pragma once

#include "BaseState.hpp"

namespace ue
{

class TalkingState : public BaseState
{
public:
    TalkingState(Context& context, common::PhoneNumber from);
     void handleSendTalkMessage(const std::string) final;
     void handleTalkMessage(const std::string) final;
     void handlePeerUeBecomesUnknown() final;

private:
    common::PhoneNumber from;
};

}
