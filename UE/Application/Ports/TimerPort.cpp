#include "TimerPort.hpp"
#include <ctime>

namespace ue
{

TimerPort::TimerPort(common::ILogger &logger)
    : logger(logger, "[TIMER PORT]")
{

}

TimerPort::~TimerPort()
{

}

void TimerPort::start(ITimerEventsHandler &handler)
{
    logger.logDebug("Started");
    clockStart=Clock::now();
    this->handler = &handler;
}

void TimerPort::stop()
{
    handler = nullptr;
    if(timerThread.joinable()){
        timerThread.detach();
    }
    clockEnd=Clock::now();
    logger.logInfo("Phone stopped working after ", std::chrono::duration_cast<std::chrono::seconds>(clockEnd-clockStart).count()," seconds");
}

void TimerPort::startTimer(const Duration duration)
{
    logger.logDebug("Start timer: ", duration.count(), "ms");

    timerThread=std::thread{&TimerPort::waitForTimeout, this, duration};
}

void TimerPort::stopTimer()
{
    pthread_cancel(timerThread.native_handle());
    logger.logDebug("Stop timer");



}
void TimerPort::waitForTimeout(Duration duration)
{

    std::this_thread::sleep_for(duration);
    handler->handleTimeout();

}
}
