
#include <at_least_three_colinear_points_strategy.h>

template<typename T>
std::vector<Punto<T>> AtLeastThreeColinearPointsStrategy<T>::generate(unsigned int amount) {
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

template class AtLeastThreeColinearPointsStrategy<int>;
template class AtLeastThreeColinearPointsStrategy<double>;
template class AtLeastThreeColinearPointsStrategy<float>;
template class AtLeastThreeColinearPointsStrategy<long>;
template class AtLeastThreeColinearPointsStrategy<long long>;
