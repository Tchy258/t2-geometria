#include <hull_percentage_strategy.h>
#define TWO_PI ((float) (3.14159265358979323846 * 2))

template <typename T>
HullPercentageStrategy<T>::HullPercentageStrategy(float percentageOnHull) : percentageOnHull(percentageOnHull) {}

template <typename T>
HullPercentageStrategy<T>::HullPercentageStrategy(float percentageOnHull, unsigned int colinearCount) : percentageOnHull(percentageOnHull), colinearCount(colinearCount) {}

template <typename T>
inline bool HullPercentageStrategy<T>::obeysCircleConstraint(T x, T y, T radius, T center) {
    return (((x - center)*(x - center)) + ((y-center)*(y-center)) < (radius*radius));
}

template <typename T>
std::vector<Punto<T>> HullPercentageStrategy<T>::generate(unsigned int amount) {
    T lowerBound = this->dist.min();
    T upperBound = this->dist.max();

    unsigned int amountOnHull = std::round(static_cast<double>(amount) * percentageOnHull);
    if (amountOnHull == 0) amountOnHull = 1;
    unsigned int colinearCountClamped = std::min(colinearCount, amountOnHull);

    std::vector<Punto<T>> points;

    T radius = (upperBound - lowerBound) / static_cast<T>(2);
    T center = (upperBound + lowerBound) / static_cast<T>(2);

    float angleStep = TWO_PI / std::max(1u, amountOnHull - colinearCountClamped);

    if (colinearCountClamped >= 3) {
        // Generate colinear points along a small arc that approximates a line on the hull
        // Choose a base angle and direction
        float baseAngle = 0.0f;
        float arcAngle = 0.0001f; // Tiny angle to keep them nearly colinear

        for (unsigned int i = 0; i < colinearCountClamped; ++i) {
            float angle = baseAngle + i * arcAngle;
            T x = static_cast<T>(std::cosf(angle) * static_cast<float>(radius)) + center;
            T y = static_cast<T>(std::sinf(angle) * static_cast<float>(radius)) + center;
            points.emplace_back(Punto<T>(x, y));
        }

        // Generate the rest of the hull points evenly on the circle
        for (unsigned int i = 0; i < amountOnHull - colinearCountClamped; ++i) {
            float angle = angleStep * static_cast<float>(i + 1); // skip the tiny arc area
            T x = static_cast<T>(std::cosf(angle) * static_cast<float>(radius)) + center;
            T y = static_cast<T>(std::sinf(angle) * static_cast<float>(radius)) + center;
            points.emplace_back(Punto<T>(x, y));
        }
    } else {
        // No colinear points — uniform circle spacing
        for (unsigned int i = 0; i < amountOnHull; ++i) {
            float angle = angleStep * static_cast<float>(i);
            T x = static_cast<T>(std::cosf(angle) * static_cast<float>(radius)) + center;
            T y = static_cast<T>(std::sinf(angle) * static_cast<float>(radius)) + center;
            points.emplace_back(Punto<T>(x, y));
        }
    }

    // Restrict bounds for internal points
    T minBound = std::is_integral<T>::value ? static_cast<T>(1) : static_cast<T>(0.1);
    this->setBounds(center - radius + minBound, center + radius - minBound);
    // Fill random inner points
    while (points.size() < amount) {
        T x = this->getRandom();
        T y = this->getRandom();
        if (obeysCircleConstraint(x, y, radius, center)) {
            points.emplace_back(Punto<T>(x, y));
        }
    }

    this->setBounds(lowerBound, upperBound);
    return points;
}



template <typename T>
HullPercentageStrategy<T>& HullPercentageStrategy<T>::setPercentageOnHull(float percentage) {
    percentageOnHull = percentage;
    return *this;
}

template <typename T>
HullPercentageStrategy<T>& HullPercentageStrategy<T>::setColinearPointAmount(unsigned int amount) {
    colinearCount = amount;
    return *this;
}

template class HullPercentageStrategy<int>;
template class HullPercentageStrategy<double>;
template class HullPercentageStrategy<float>;
template class HullPercentageStrategy<long>;
template class HullPercentageStrategy<long long>;
