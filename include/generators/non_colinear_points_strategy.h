#ifndef NON_COLINEAR_POINTS_STRATEGY_H
#define NON_COLINEAR_POINTS_STRATEGY_H
#include "point_generation_strategy.h"
#include <vector.h>

template<typename T>
class NonColinearPointsStrategy : public PointGenerationStrategy<T> {
public:
    std::vector<Punto<T>> generate(unsigned int amount) override {
        std::vector<Punto<T>> points;
        while (points.size() < amount) {
            Punto<T> p(this->distribution,dist(this->rng), dist(this->rng));
            bool colinear = false;

            for (size_t i = 0; i < points.size(); ++i) {
                for (size_t j = i+1; j < points.size(); ++j) {
                    Vector<T> v1 = Vector<T>(points[j] - points[i]);
                    Vector<T> v2 = Vector<T>(p - points[i]);
                    if (v1.productoCruz(v2) == 0) {
                        colinear = true;
                        break;
                    }
                }
                if (colinear) break;
            }

            if (!colinear)
                points.push_back(p);
        }

        return points;
    }
};


#endif