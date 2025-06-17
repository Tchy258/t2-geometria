#ifndef HULL_PERCENTAGE_STRATEGY_H
#define HULL_PERCENTAGE_STRATEGY_H
#include "point_generation_strategy.h"
#include <cmath>
#include <cstdlib>
#include <cinttypes>
template <typename T>
class HullPercentageStrategy : public PointGenerationStrategy<T> {
    private:
        float percentageOnHull;
        unsigned int colinearCount = 0;
        inline bool obeysCircleConstraint(T x, T y, T radius, T center);
        std::vector<Punto<T>> generateCircle(unsigned int amount);
    public:
        std::vector<Punto<T>> generate(unsigned int amount);
        HullPercentageStrategy(float percentageOnHull);
        HullPercentageStrategy(float percentageOnHull, unsigned int colinearCount);
        HullPercentageStrategy<T>& setPercentageOnHull(float percentage);
        HullPercentageStrategy<T>& setColinearPointAmount(unsigned int amount);
        HullPercentageStrategy(const HullPercentageStrategy&) = delete;
        HullPercentageStrategy& operator=(const HullPercentageStrategy&) = delete;
        HullPercentageStrategy(HullPercentageStrategy&&) = default;
        HullPercentageStrategy& operator=(HullPercentageStrategy&&) = default;
};

#endif