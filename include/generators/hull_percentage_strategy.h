#ifndef HULL_PERCENTAGE_STRATEGY_H
#define HULL_PERCENTAGE_STRATEGY_H
#include "point_generation_strategy.h"
#include <cmath>
template <typename T>
class HullPercentageStrategy : public PointGenerationStrategy<T> {
    public:
        std::vector<Punto<T>> generate(unsigned int amount);
        HullPercentageStrategy(float percentageOnHull);
        void setPercentageOnHull(float percentage);
    private:
        float percentageOnHull;
};

#endif