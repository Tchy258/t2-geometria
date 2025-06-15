#include "non_colinear_points_strategy.h"


template<typename T>
std::vector<Punto<T>> NonColinearPointsStrategy<T>::generate(unsigned int amount) {
    std::vector<Punto<T>> points;
    while (points.size() < amount) {
        Punto<T> p(this->getRandom(), this->getRandom(), this->getRandom());
        bool colinear = false;

        for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = i+1; j < points.size(); ++j) {
                Vector<T> v1 = Vector<T>(points[j] - points[i]);
                Vector<T> v2 = Vector<T>(p - points[i]);
                if (Punto<T>::equal_within_ulps(v1.productoCruz(v2).getCoords().getZ(),0)) {
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

template class NonColinearPointsStrategy<int>;
template class NonColinearPointsStrategy<double>;
template class NonColinearPointsStrategy<float>;
template class NonColinearPointsStrategy<long>;
template class NonColinearPointsStrategy<long long>;
