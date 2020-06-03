#pragma once

#include "BaseState.hpp"

namespace ue
{

class TalkingState : public BaseState
{
public:
    TalkingState(Context &context, common::PhoneNumber from);
    void handleSib(common::BtsId btsId) override;
    void handlePeerNotConnected(common::PhoneNumber) override;
    void handleTimeout() override;
private:
    common::PhoneNumber from;
};

}
