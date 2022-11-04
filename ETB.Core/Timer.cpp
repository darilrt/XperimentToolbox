#include <chrono>

#include "Timer.h"

std::chrono::time_point<std::chrono::high_resolution_clock> xtb::Time::start;
float xtb::Time::deltaTime;
float xtb::Time::playTime;

void xtb::Time::Start() {
    Time::start = std::chrono::high_resolution_clock::now();
}

void xtb::Time::Tick() {
    std::chrono::time_point<std::chrono::high_resolution_clock> now;
    now = std::chrono::high_resolution_clock::now();

    Time::deltaTime = (float) (std::chrono::duration_cast<std::chrono::microseconds>(now - Time::start).count() / 1000000.0);

    Time::playTime += Time::deltaTime;

    Time::start = std::chrono::high_resolution_clock::now();
}
