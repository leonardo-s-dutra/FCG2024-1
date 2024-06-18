#include <chrono>
#include <thread>
#include <ctime>


class Timer
{
public:
    Timer();
    Timer(uint32_t fps);
    ~Timer();

    void start();
    void finish();
    void wait();

    double getElapsedTimeMs();
    double getElapsedTimeS();

    double getWaitingTimeMs(uint32_t fps, double elapsedTimeMs);

    void setFps(uint32_t fps);

private:
    std::chrono::time_point<std::chrono::system_clock> __begin;
    std::chrono::time_point<std::chrono::system_clock> __end;
    uint32_t __fps;
};
