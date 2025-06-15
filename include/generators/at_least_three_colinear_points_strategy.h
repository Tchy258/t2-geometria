#ifndef AT_LEAST_THREE_COLINEAR_POINTS_STRATEGY_H
#define AT_LEAST_THREE_COLINEAR_POINTS_STRATEGY_H
#include "point_generation_strategy.h"
#include <algorithm>
template<typename T>
class AtLeastThreeColinearPointsStrategy : public PointGenerationStrategy<T> {
public:
    std::vector<Punto<T>> generate(unsigned int amount) override;
};

#endif