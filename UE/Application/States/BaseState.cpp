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
void BaseState::handleSendSms(common::PhoneNumber, std::string)
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
<<<<<<< Updated upstream
=======
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
void BaseState::handleSendCallRequest(common::PhoneNumber)
{
    logger.logError("Uexpected: handleSendCallRequest");
}
void BaseState::handleSendCallDrop(common::PhoneNumber)
{
    logger.logError("Unexpected: handleSendCallDrop");
}

void BaseState::handlePeerNotConnected(common::PhoneNumber)
{
    logger.logError("Unexpected: handleUnknownRecipient after CallRequest");
}
void BaseState::handleSendCallAccept(common::PhoneNumber)
{
    logger.logError("Uexpected: handleSendCallAccept");
}
void BaseState::handleSendCallDropped(common::PhoneNumber)
{
    logger.logError("Uexpected: handleSendCallDroppped");
}
>>>>>>> Stashed changes
}
