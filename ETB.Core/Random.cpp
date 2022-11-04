#include <random>
#include <sstream>

#include "Random.h"

std::random_device xtb::Random::dev;
std::mt19937 xtb::Random::rng(xtb::Random::dev());

int xtb::Random::Range(int32_t min, int32_t max) {
    return std::uniform_int_distribution<std::mt19937::result_type>(min, max)(xtb::Random::rng);
}

static std::random_device              rd;
static std::mt19937                    gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);

std::string xtb::GetUUID() {
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++) {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++) {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++) {
        ss << dis(gen);
    };
    return ss.str();
}
