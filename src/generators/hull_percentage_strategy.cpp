#include <hull_percentage_strategy.h>
#define TWO_PI ((float) (3.14159265358979323846 * 2))
#define PI_FOURTHS ((float) (3.14159265358979323846 / 4))
template <typename T>
HullPercentageStrategy<T>::HullPercentageStrategy(float percentageOnHull) : percentageOnHull(percentageOnHull) {}

template <typename T>
std::vector<Punto<T>> HullPercentageStrategy<T>::generate(unsigned int amount) {
    T lowerBound = this->dist.min();
    T upperBound = this->dist.max();
    unsigned int amountOnHull =  std::ceil((double) (amount) * percentageOnHull);
    unsigned int outsideOfHull = amount - amountOnHull;
    T radius = (upperBound - lowerBound) / 2;
    T center = (upperBound + lowerBound) / 2;
    std::vector<Punto<T>> points;
    for (float angle = 0.0; angle < TWO_PI; angle += (TWO_PI / (float) amountOnHull)) {
        T x = static_cast<T>(std::cosf(angle) * radius) + center;
        T y = static_cast<T>(std::sinf(angle) * radius) + center;
        points.emplace_back(Punto<T>(x,y));
    }
    T minimum = std::is_integral<T>::value ? static_cast<T>(1) : static_cast<T>(0.1);
    this->setBounds(-(static_cast<T>(radius * PI_FOURTHS)) + minimum, static_cast<T>(radius * PI_FOURTHS) - minimum);
    for (int i = 0; i < outsideOfHull; ++i) {
        T x = this->getRandom();
        T y = this->getRandom();
        points.emplace_back(Punto<T>(x,y));
    }
    this->setBounds(lowerBound, upperBound);
    return points;
}

template <typename T>
void HullPercentageStrategy<T>::setPercentageOnHull(float percentage) {
    percentageOnHull = percentage;
}

template class HullPercentageStrategy<int>;
template class HullPercentageStrategy<double>;
template class HullPercentageStrategy<float>;
template class HullPercentageStrategy<long>;
template class HullPercentageStrategy<long long>;
