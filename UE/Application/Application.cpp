#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue
{

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger &iLogger,
                         IBtsPort &bts,
                         IUserPort &user,
                         ITimerPort &timer,
                         ISmsDatabase &db
                         )
    : context{iLogger, bts, user, timer, db},
      logger(iLogger, "[APP] ")
{
    logger.logInfo("Started");
    context.setState<NotConnectedState>();
}

Application::~Application()
{
    logger.logInfo("Stopped");
}

void Application::handleTimeout()
{
    context.state->handleTimeout();
}
void Application::handleDisconnected()
{
    context.state->handleDisconnected();
}

void Application::handleSib(common::BtsId btsId)
{
    context.state->handleSib(btsId);
}

void Application::handleAttachAccept()
{
    context.state->handleAttachAccept();
}

void Application::handleAttachReject()
{
    context.state->handleAttachReject();
}
void Application::handleSendSms(common::PhoneNumber from, std::string message)
{
    context.state->handleSendSms(from, message);
}

void Application::handleSmsReceived(common::PhoneNumber from, std::string message)
{
    context.state->handleSmsReceived(from, message);
}

<<<<<<< Updated upstream
=======
void Application::handleReceivedCallRequest(common::PhoneNumber phoneNumber)
{
    context.state->handleReceivedCallRequest(phoneNumber);
}

void Application::handleReceivedCallAccepted(common::PhoneNumber phoneNumber)
{
    context.state->handleReceivedCallAccepted(phoneNumber);
}

void Application::handleReceivedCallDropped(common::PhoneNumber phoneNumber)
{
    context.state->handleReceivedCallDropped(phoneNumber);
}
void Application::handleSendCallRequest(common::PhoneNumber from)
{
    context.state->handleSendCallRequest(from);
}
void Application::handleSendCallDrop(common::PhoneNumber from)
{
    context.state->handleSendCallDrop(from);
}
void Application::handleSendCallAccept(common::PhoneNumber from)
{
    context.state->handleSendCallAccept(from);
}
void Application::handleSendCallDropped(common::PhoneNumber from)
{
    context.state->handleSendCallDropped(from);
}
void Application::handlePeerNotConnected(common::PhoneNumber from)
{
    context.state->handlePeerNotConnected(from);
}
>>>>>>> Stashed changes
}


