#include "gift_wrapping_strategy.h"

template<typename T>
inline T safe_infinity_cast() {
    if (std::is_integral<T>::value) {
        return std::numeric_limits<T>::max();
    } else {
        return std::numeric_limits<T>::infinity();
    }
}

template<typename T>
inline T safe_negative_infinity_cast() {
    if (std::is_integral<T>::value) {
        return std::numeric_limits<T>::min();
    } else {
        return -std::numeric_limits<T>::infinity();
    }
}

template<class T>
inline bool GiftWrappingStrategy<T>::compareByAngle(Vector<T>& lastCandidate, Vector<T>& candidate) {
    T crossProduct = lastCandidate.productoCruz(candidate).getCoords().getZ();
    
    if (!Punto<T>::equal_within_ulps(crossProduct,0)) {
        return crossProduct < 0; // > 0 for CW
    }

    // Collinear: pick the point farther from p
    T distA = lastCandidate.magnitud2();
    T distB = candidate.magnitud2();
    return distB > distA;
}


template <class T>
Poligono<T> GiftWrappingStrategy<T>::apply(std::vector<Punto<T>> &cloud)
{
    size_t n = cloud.size();
    if (n <= 3) {
        return Poligono<T>(cloud);
    }
    std::vector<Punto<T>> convexHull;
    unsigned long long pointOnHullIndex = 0;
    for (unsigned long long i = 0; i < n; ++i) {
        if (cloud[i].getY() < cloud[pointOnHullIndex].getY() ||
        (Punto<T>::equal_within_ulps(cloud[i].getY(),cloud[pointOnHullIndex].getY()) && cloud[i].getX() < cloud[pointOnHullIndex].getX())) {
            pointOnHullIndex = i;
        }
    }
    
    unsigned long long firstIndex = pointOnHullIndex;
    unsigned long long next = (pointOnHullIndex + 1) % n;
    Vector<T> lastCandidate(cloud[next] - cloud[pointOnHullIndex]);
    do {
        convexHull.push_back(cloud[pointOnHullIndex]);
        
        for (unsigned long long j = 0; j < n; ++j) {
            if (j == pointOnHullIndex) continue;
            Vector<T> newEdge = Vector<T>(cloud[j] - cloud[pointOnHullIndex]);
            if (compareByAngle(lastCandidate, newEdge)) {
                lastCandidate = newEdge;
                next = j;
            }
        }
        pointOnHullIndex = next;
        
        next = firstIndex;
        lastCandidate = Vector<T>(cloud[firstIndex] - cloud[pointOnHullIndex]);
    } while ( pointOnHullIndex != firstIndex);

    Poligono<T> capsula(convexHull);
    return capsula;
}

template class GiftWrappingStrategy<int>;
template class GiftWrappingStrategy<double>;
template class GiftWrappingStrategy<float>;
template class GiftWrappingStrategy<long>;
template class GiftWrappingStrategy<long long>;
