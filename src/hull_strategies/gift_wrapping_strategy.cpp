#include "gift_wrapping_strategy.h"


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
    do {
        convexHull.push_back(cloud[pointOnHullIndex]);
        
        for (unsigned long long j = 0; j < n; ++j) {
            if (j == pointOnHullIndex) continue;
            if (this->isMoreCCW(cloud[pointOnHullIndex], cloud[next], cloud[j])) {
                next = j;
            }
        }
        pointOnHullIndex = next;
        
        next = firstIndex;
    } while ( pointOnHullIndex != firstIndex);

    Poligono<T> capsula(convexHull);
    return capsula;
}

template class GiftWrappingStrategy<int>;
template class GiftWrappingStrategy<double>;
template class GiftWrappingStrategy<float>;
template class GiftWrappingStrategy<long>;
template class GiftWrappingStrategy<long long>;
