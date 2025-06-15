#ifndef POINT_GENERATION_STRATEGY_H
#define POINT_GENERATION_STRATEGY_H

#include <punto.h>
#include <random>
#include <type_traits>
#include <typeinfo>

template <typename T>
class PointGenerationStrategy {
public:
    virtual ~PointGenerationStrategy() = default;
    virtual std::vector<Punto<T>> generate(unsigned int amount) = 0;
    void setSeed(unsigned int seed) {
        rng.seed(seed);
    }
    void setBounds(T lowerBound, T upperBound) {
        dist = DistType(lowerBound, upperBound);
    }
protected:
    std::mt19937 rng{std::random_device{}()};
    
    using DistType = typename std::conditional<std::is_integral<T>::value,std::uniform_int_distribution<T>,std::uniform_real_distribution<T>>::type;

    DistType dist = DistType(static_cast<T>(-100), static_cast<T>(100));

    T getRandom() {
        return dist(rng);
    }
};

#endif