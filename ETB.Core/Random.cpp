#include "Random.h"

std::random_device ETB::Random::dev;
std::mt19937 ETB::Random::rng(ETB::Random::dev());

int ETB::Random::Range(int32_t min, int32_t max) {
    return std::uniform_int_distribution<std::mt19937::result_type>(min, max)(ETB::Random::rng);
}
