#ifndef COMPLETELY_RANDOM_POINTS_STRATEGY_H
#define COMPLETELY_RANDOM_POINTS_STRATEGY_H
#include "point_generation_strategy.h"

template <typename T>
class CompletelyRandomPointsStrategy : public PointGenerationStrategy<T> {
public:
    std::vector<Punto<T>> generate(unsigned int amount) override;
};

#endif