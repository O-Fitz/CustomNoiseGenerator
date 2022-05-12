#include "RANDOM.h"

RANDOM::RANDOM (int seed){
    generator = std::default_random_engine(seed);
}

double RANDOM::randomDoubleRange(double lower, double upper) {
        std::uniform_real_distribution<double> distribution(lower, upper);
        return distribution(generator);
}

int RANDOM::randomIntRange(int lower, int upper) {
        std::uniform_int_distribution<int> distribution(lower, upper);
        return distribution(generator);
}

int RANDOM::randomNegative() {
        int ran[2] = { -1, 1 };
        return ran[this->randomIntRange(0, 1)];
}