#pragma once

#include "ITimerPort.hpp"
#include "Logger/PrefixedLogger.hpp"
#include <thread>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

namespace ue
{

class TimerPort : public ITimerPort
{
public:
    TimerPort(common::ILogger& logger);
    ~TimerPort();
    void start(ITimerEventsHandler& handler);
    void stop();
    void waitForTimeout(Duration duration);

    // ITimerPort interface
    void startTimer(const Duration duration) override;
    void stopTimer() override;
    //std::clock_t clockStart;
    //double clockDuration;
   std::chrono::high_resolution_clock::time_point clockStart;
   std::chrono::high_resolution_clock::time_point clockEnd;


private:
    common::PrefixedLogger logger;
    ITimerEventsHandler* handler = nullptr;
    std::thread timerThread;


};

}
