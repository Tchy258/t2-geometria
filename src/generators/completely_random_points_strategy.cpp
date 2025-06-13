#include <completely_random_points_strategy.h>

template <typename T>
std::vector<Punto<T>> CompletelyRandomPointsStrategy<T>::generate(unsigned int amount) {
        std::vector<Punto<T>> points;

        while (points.size() < amount) {
            T x = this->distribution(rng);
            T y = this->distribution(rng);
            points.emplace_back(x, y);
        }

        return points;
}


template class CompletelyRandomPointsStrategy<int>;
template class CompletelyRandomPointsStrategy<double>;
template class CompletelyRandomPointsStrategy<float>;
template class CompletelyRandomPointsStrategy<long>;
template class CompletelyRandomPointsStrategy<long long>;
