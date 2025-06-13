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
        (cloud[i].getY() == cloud[pointOnHullIndex].getY() && cloud[i].getX() < cloud[pointOnHullIndex].getX())) {
            pointOnHullIndex = i;
        }
    }
    unsigned long long firstIndex = pointOnHullIndex;
    std::bitset<n> pointsUsed;
    pointsUsed[pointOnHullIndex] = true;
    Vector<T> arcoPrevio(1,0);
    do {
        convexHull.push_back(cloud[pointOnHullIndex]);
        unsigned long long k = firstIndex;
        T mejorProductoCruz = safe_infinity_cast<T>();
        for (unsigned long long j = 0; j < n; ++j) {
            if (j == pointOnHullIndex || pointsUsed.test(j)) != convexHull.end()) continue;
            Vector<T> nuevoArco = Vector<T>(cloud[j] - cloud[pointOnHullIndex]);
            T nuevoProductoCruz = arcoPrevio.productoCruz(nuevoArco).getCoords().getZ();
            if (mejorProductoCruz > nuevoProductoCruz || 
                mejorProductoCruz == nuevoProductoCruz && nuevoArco.magnitud() > (Vector<T>(cloud[k] - cloud[pointOnHullIndex]).magnitud())) {
                k = j;
                pointsUsed.set(j);
                mejorProductoCruz = nuevoProductoCruz;
            }
        }
        arcoPrevio = Vector<T>(cloud[k] - cloud[pointOnHullIndex]);
        pointOnHullIndex = k;
    } while ( pointOnHullIndex != firstIndex);

    Poligono<T> capsula(convexHull);
    capsula.convertirACCW();
    return capsula;
}

template class GiftWrappingStrategy<int>;
template class GiftWrappingStrategy<double>;
template class GiftWrappingStrategy<float>;
template class GiftWrappingStrategy<long>;
template class GiftWrappingStrategy<long long>;
