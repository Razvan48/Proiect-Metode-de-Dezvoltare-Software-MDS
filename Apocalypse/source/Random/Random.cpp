#include "Random.h"

#include <random>

const double Random::EPSILON = 0.05;

double Random::random01()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);

    return dis(gen);
}