#ifndef NON_COLINEAR_POINTS_STRATEGY_H
#define NON_COLINEAR_POINTS_STRATEGY_H
#include "point_generation_strategy.h"
#include <vector.h>

template<typename T>
class NonColinearPointsStrategy : public PointGenerationStrategy<T> {
public:
    std::vector<Punto<T>> generate(unsigned int amount) override;
};


#endif