#ifndef POINT_GENERATION_STRATEGY_H
#define POINT_GENERATION_STRATEGY_H

#include <punto.h>
#include <random>

template <typename T>
class PointGenerationStrategy {
public:
    std::vector<Punto<T>> generate(unsigned int amount) = 0;
    void setSeed(unsigned int seed) {
        rng.seed(seed);
    }
    void setBounds(T lowerBound, T upperBound) {
        distribution = std::uniform_real_distribution<T>(lowerBound, upperBound);
    }
protected:
    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<T> distribution(static_cast<T>(-100),static_cast<T>(100));
};

#endif