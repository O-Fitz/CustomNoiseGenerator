#pragma once

#include <random>

class RANDOM {
    std::default_random_engine generator;
public:
    RANDOM(int seed);
    double randomDoubleRange(double lower, double upper);
    int randomIntRange(int lower, int upper);
    int randomNegative();
};