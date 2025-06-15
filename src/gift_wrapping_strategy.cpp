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
inline bool GiftWrappingStrategy<T>::compareByAngle(Vector<T>&refDir, Vector<T>& lastCandidate, Vector<T>& candidate) {
    T lastBestCross = refDir.productoCruz(lastCandidate).getCoords().getZ();
    T lastBestDot = refDir.productoPunto(lastCandidate);
    T candidateCross = refDir.productoCruz(candidate).getCoords().getZ();
    T candidateDot = refDir.productoPunto(candidate);
     // If angles are on different sides of the refDir
    if ((lastBestCross < 0 && candidateCross >= 0)) return true;
    if ((lastBestCross >= 0 && candidateCross < 0)) return false;

    // If same direction (possibly collinear), compare using tan = cross / dot
    T cmp = lastBestCross * candidateDot - candidateCross * lastBestDot;
    if (!Punto<T>::equal_within_ulps(cmp,0)) return cmp > 0;

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
    Vector<T> lastCandidate(cloud[(pointOnHullIndex + 1) % n] - cloud[pointOnHullIndex]);
    std::vector<bool> pointsUsed(n,false);
    pointsUsed[pointOnHullIndex] = true;
    Vector<T> previousEdge(Punto<T>(1,0));
    do {
        convexHull.push_back(cloud[pointOnHullIndex]);
        unsigned long long k;
        if (convexHull.size() == 1) {
            k = (pointOnHullIndex + 1) % n;
        } else {
            k = firstIndex;
        }
        if (pointOnHullIndex != firstIndex) lastCandidate = Vector<T>(cloud[firstIndex] - cloud[pointOnHullIndex]);

        for (unsigned long long j = 0; j < n; ++j) {
            if (j == pointOnHullIndex || pointsUsed[j]) continue;
            Vector<T> newEdge = Vector<T>(cloud[j] - cloud[pointOnHullIndex]);
            if (compareByAngle(previousEdge, lastCandidate, newEdge)) {
                lastCandidate = newEdge;
                k = j;
            }
        }
        previousEdge = lastCandidate;
        pointOnHullIndex = k;
        pointsUsed[k] = true;
    } while ( pointOnHullIndex != firstIndex);

    Poligono<T> capsula(convexHull);
    return capsula;
}

template class GiftWrappingStrategy<int>;
template class GiftWrappingStrategy<double>;
template class GiftWrappingStrategy<float>;
template class GiftWrappingStrategy<long>;
template class GiftWrappingStrategy<long long>;
