#include <chrono>

#include "Timer.h"

std::chrono::time_point<std::chrono::high_resolution_clock> ETB::Time::start;
float ETB::Time::deltaTime;
float ETB::Time::playTime;

void ETB::Time::Start() {
    Time::start = std::chrono::high_resolution_clock::now();
}

void ETB::Time::Tick() {
    std::chrono::time_point<std::chrono::high_resolution_clock> now;
    now = std::chrono::high_resolution_clock::now();

    Time::deltaTime = (float) (std::chrono::duration_cast<std::chrono::microseconds>(now - Time::start).count() / 1000000.0);

    Time::playTime += Time::deltaTime;

    Time::start = std::chrono::high_resolution_clock::now();
}
