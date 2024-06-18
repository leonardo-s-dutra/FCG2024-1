#include "Timer.h"


Timer::Timer()
{
    this->__fps = 24;
}

Timer::Timer(uint32_t fps)
{
    this->__fps = fps;
}

Timer::~Timer()
{

}

void Timer::start()
{
    this->__begin = std::chrono::system_clock::now();
}

void Timer::finish()
{
    this->__end = std::chrono::system_clock::now();
}

void Timer::wait()
{
    std::chrono::time_point<std::chrono::system_clock> now, last;
    std::chrono::duration<double> dt;
    last = std::chrono::system_clock::now();
    do {
        now = std::chrono::system_clock::now();
        dt = last - now;
    } while(dt.count()*1000 < (1.0 / static_cast<float>(this->__fps)));
}

double Timer::getElapsedTimeMs()
{
    std::chrono::duration<double> elapsed = this->__end - this->__begin;
    return 1000.0*elapsed.count();
}

double Timer::getElapsedTimeS()
{
    std::chrono::duration<double> elapsed = this->__end - this->__begin;
    return elapsed.count();
}

double Timer::getWaitingTimeMs(uint32_t fps, double elapsedTimeMs)
{
    return (1000.0 / static_cast<double>(fps)) - elapsedTimeMs;
}

void Timer::setFps(uint32_t fps)
{
    this->__fps = fps;
}