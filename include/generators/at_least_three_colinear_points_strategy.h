#ifndef AT_LEAST_THREE_COLINEAR_POINTS_STRATEGY_H
#define AT_LEAST_THREE_COLINEAR_POINTS_STRATEGY_H
#include "point_generation_strategy.h"

template<typename T>
class AtLeastThreeColinearPointsStrategy : public PointGenerationStrategy<T> {
public:
    std::vector<Punto<T>> generate(unsigned int amount) override {
        std::vector<Punto<T>> points;

        // Generate 3 colinear points on line y = mx + b
        T m = this->distribution(this->rng), b = this->distribution(this->rng);
        for (int i = 0; i < 3; ++i) {
            T x = this->distribution(rng);
            points.emplace_back(x, m * x + b);
        }

        while (points.size() < amount) {
            T x = this->distribution(this->rng);
            T y = this->distribution(this->rng);
            points.emplace_back(x, y);
        }

        return points;
    }
};

#endif