#include "BaseState.hpp"

namespace ue
{


BaseState::BaseState(Context &context, const std::string &name)
    : context(context),
      logger(context.logger, "[" + name + "]")
{
    logger.logDebug("entry");
}

BaseState::~BaseState()
{
    logger.logDebug("exit");
}

void BaseState::handleTimeout()
{
    logger.logError("Unexpected: handleTimeout");
}

void BaseState::handleDisconnected()
{
    logger.logError("Unexpected: handleDisconnected");
}
void BaseState::handleSib(common::BtsId btsId)
{
    logger.logError("Unexpected: handleSib: ", btsId);
}
void BaseState::handleSendSms(common::PhoneNumber from, std::string message)
{
    logger.logError("Uexpected: handleSendSms");
}
void BaseState::handleAttachAccept()
{
    logger.logError("Unexpected: handleAttachAccept");
}
void BaseState::handleAttachReject()
{
    logger.logError("Unexpected: handleAttachReject");
}
void BaseState::handleSmsReceived(common::PhoneNumber from, std::string text)
{
    logger.logError("Unexpected handleSmsReceived: ", from, text);
}
void BaseState::handleReceivedCallDropped(common::PhoneNumber from)
{
    logger.logError("Unexpected ReceivedCallDropped: ", from);
}
void BaseState::handleReceivedCallAccepted(common::PhoneNumber from)
{
    logger.logError("Unexpected ReceivedCallAccepted: ", from);
}
void BaseState::handleReceivedCallRequest(common::PhoneNumber recipient)
{
    logger.logError("Unexpected ReceivedCallRequest: ", recipient);
}
}
