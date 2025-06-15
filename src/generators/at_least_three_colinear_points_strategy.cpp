
#include <at_least_three_colinear_points_strategy.h>

template<typename T>
std::vector<Punto<T>> AtLeastThreeColinearPointsStrategy<T>::generate(unsigned int amount) {
    
    // Pick two random points within bounds
    T x1 = this->getRandom(), y1 = this->getRandom();
    T x2 = this->getRandom(), y2 = this->getRandom();
    while (x1 == x2) x2 = this->getRandom(); // Avoid division by zero
    
    // Calculate slope and intercept
    T m = (y2 - y1) / (x2 - x1);
    T b = y1 - m * x1;

    std::vector<Punto<T>> points = {Punto<T>(x1,y1), Punto<T>(x2,y2)};
    while (points.size() < 3) {        
        T x = this->getRandom();
        T y = m * x + b;
        if (y < this->dist.min() || y > this->dist.max()) continue;
        Punto<T> p(x, y);
        if (std::find(points.begin(), points.end(), p) == points.end()) {
            points.push_back(p);
        }
    }

    while (points.size() < amount) {
        T x = this->getRandom();
        T y = this->getRandom();
        points.emplace_back(x, y);
    }

    return points;
}

template class AtLeastThreeColinearPointsStrategy<int>;
template class AtLeastThreeColinearPointsStrategy<double>;
template class AtLeastThreeColinearPointsStrategy<float>;
template class AtLeastThreeColinearPointsStrategy<long>;
template class AtLeastThreeColinearPointsStrategy<long long>;
