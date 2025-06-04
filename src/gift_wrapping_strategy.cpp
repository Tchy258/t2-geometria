#include "gift_wrapping_strategy.h"

template<typename T>
T safe_infinity_cast() {
    if (std::is_integral<T>::value) {
        return std::numeric_limits<T>::max();
    } else {
        return std::numeric_limits<T>::infinity();
    }
}

template<typename T>
T safe_negative_infinity_cast() {
    if (std::is_integral<T>::value) {
        return std::numeric_limits<T>::min();
    } else {
        return -std::numeric_limits<T>::infinity();
    }
}

template <class T>
GiftWrappingStrategy<T>::GiftWrappingStrategy(unsigned long long n) : n(n) {}


template <class T>
Poligono<T> GiftWrappingStrategy<T>::apply(Punto<T> cloud[])
{
    if (n <= 3) {
        std::vector<Punto<T>> vPuntos(cloud, cloud + n);
        return Poligono<T>(vPuntos);
    }
    std::vector<Punto<T>> convexHull;
    unsigned long long pointOnHullIndex = 0;
    for (unsigned long long i = 0; i < n; i++) {
        if (cloud[i].getY() < cloud[pointOnHullIndex].getY() ||
        (cloud[i].getY() == cloud[pointOnHullIndex].getY() && cloud[i].getX() < cloud[pointOnHullIndex].getX())) {
            pointOnHullIndex = i;
        }
    }
    unsigned long long firstIndex = pointOnHullIndex;
    bool pointsUsed[n] = {false};
    pointsUsed[pointOnHullIndex] = true;
    Vector<T> arco_previo(1,0);
    do {
        convexHull.push_back(cloud[pointOnHullIndex]);
        unsigned long long k = firstIndex;
        T mejorProductoCruz = safe_infinity_cast<T>();
        for (unsigned long long j = 0; j < n; j++) {
            if (j == pointOnHullIndex || pointsUsed[j]) != convexHull.end()) continue;
            Vector<T> nuevo_arco = Vector<T>(cloud[j] - cloud[pointOnHullIndex]);
            T nuevoProductoCruz = arco_previo.productoCruz(nuevo_arco).getCoords().getZ();
            if (mejorProductoCruz > nuevoProductoCruz || 
                mejorProductoCruz == nuevoProductoCruz && nuevo_arco.magnitud() > (Vector<T>(cloud[k] - cloud[pointOnHullIndex]).magnitud())) {
                k = j;
                pointsUsed[j] = true;
                mejorProductoCruz = nuevoProductoCruz;
            }
        }
        arco_previo = Vector<T>(cloud[k] - cloud[pointOnHullIndex]);
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
