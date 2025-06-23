#include <divide_and_conquer_strategy.h>
#include <iostream>

template <typename T>
inline bool DivideAndConquerStrategy<T>::isMoreCCW(Punto<T> &reference, Punto<T>& currentBest, Punto<T>& newCandidate, bool keepFarthest) {
    Vector<T> old = Vector<T>(currentBest - reference);
    Vector<T> current = Vector<T>(newCandidate - reference);
    T crossProduct = old.productoCruz(current).getCoords().getZ();
    
    if (!Punto<T>::equal_within_ulps(crossProduct,0)) {
        return crossProduct > 0;
    }

    T distA = old.magnitud2();
    T distB = current.magnitud2();
    if (keepFarthest) {
        return distB > distA;
    } else {
        return distB <= distA;
    }
}

template <typename T>
Poligono<T> DivideAndConquerStrategy<T>::apply(std::vector<Punto<T>>& cloud) {
    size_t n = cloud.size();
    if (n <= 3) {
        return Poligono<T>(cloud);
    }
    std::sort(cloud.begin(), cloud.end());

    std::vector<Punto<T>> leftPoints(cloud.begin(), cloud.begin() + (n/2));
    std::vector<Punto<T>> rightPoints(cloud.begin() + (n/2), cloud.end());
    std::vector<Punto<T>> leftHull = applyRecursive(leftPoints);
    std::vector<Punto<T>> rightHull = applyRecursive(rightPoints);
    std::vector<Punto<T>> hullPoints = joinHulls(leftHull, rightHull);
    return Poligono<T>(hullPoints);
}

template <typename T>
std::vector<Punto<T>> DivideAndConquerStrategy<T>::applyRecursive(std::vector<Punto<T>>& cloud) {
    size_t n = cloud.size();
    if (n == 1) {
        return cloud;
    }
    if (n == 2) {
        if (cloud[0] == cloud[1]) {
            cloud.pop_back();
        }
        return cloud;
    }
     if (n == 3) {
        // Input is pre-sorted, just compute hull
        Vector<T> v1 = Vector<T>(cloud[1] - cloud[0]);
        Vector<T> v2 = Vector<T>(cloud[2] - cloud[0]);
        T cross = v1.productoCruz(v2).getCoords().getZ();
        if (Punto<T>::equal_within_ulps(cross, 0)) {
            return { cloud[0], v1.magnitud2() >= v2.magnitud2() ? cloud[1] : cloud[2] };
        } else if (cross > 0) {
            return cloud;
        } else {
            return { cloud[0], cloud[2], cloud[1] };
        }
    }
    std::vector<Punto<T>> leftPoints(cloud.begin(), cloud.begin() + (n/2));
    std::vector<Punto<T>> rightPoints(cloud.begin() + (n/2), cloud.end());
    std::vector<Punto<T>> leftHull = applyRecursive(leftPoints);
    std::vector<Punto<T>> rightHull = applyRecursive(rightPoints);
    std::vector<Punto<T>> hullPoints = joinHulls(leftHull, rightHull);
    return hullPoints;
}



template <typename T>
std::vector<Punto<T>> DivideAndConquerStrategy<T>::joinHulls(std::vector<Punto<T>> &leftHull, std::vector<Punto<T>> &rightHull) {
    size_t n1 = leftHull.size(); 
    size_t n2 = rightHull.size();
    size_t initialLTop = 0, initialRBottom = 0;
    size_t initialRTop = 0, initialLBottom = 0;
    size_t indexL = 0, indexR = 0, nextL = 0, nextR = 0;
    for (int i = 0; i < n1; ++i) {
        if (leftHull[i].getX() > leftHull[indexL].getX()) {
            indexL = i;
            initialLBottom = i;
            initialLTop = i;
        } else if (leftHull[i].getX() == leftHull[indexL].getX()) {
            if (leftHull[i].getY() < leftHull[indexL].getY()) {
                initialLBottom = i;
                initialLTop = indexL;
            } else {
                initialLTop = i;
                initialLBottom = indexL;
            }
        }
    }
    for (int i = 0; i < n2; ++i) {
        if (rightHull[i].getX() < rightHull[indexR].getX()) {
            indexR = i;
            initialRBottom = i;
            initialRTop = i;
        } else if (rightHull[i].getX() == rightHull[indexR].getX()) {
            if (rightHull[i].getY() < rightHull[indexR].getY()) {
                initialRBottom = i;
                initialRTop = indexR;
            } else {
                initialRBottom = indexR;
                initialRTop = i;
            }
        }
    }
    indexR = initialRTop;
    indexL = initialLTop;
    nextL = indexL;
    bool tangentFound = false;
    // Upper Tangent
    while(!tangentFound) {
        tangentFound = true;
        nextL = (indexL + 1) % n1;
        while (this->isMoreCW(rightHull[indexR],leftHull[indexL], leftHull[nextL], true)) {
            if (nextL == indexL) break;
            indexL = nextL;
            nextL = (indexL + 1) % n1;
        }
        nextR = (indexR + n2 - 1) % n2;
        while (this->isMoreCCW(leftHull[indexL], rightHull[indexR], rightHull[nextR], true)) {
            if (nextR == indexR) break;
            tangentFound = false;
            indexR = nextR;
            nextR = (indexR + n2 - 1) % n2;
        }
    }
    size_t upperTangentL = indexL;
    size_t upperTangentR = indexR;
    indexL = initialLBottom;
    indexR = initialRBottom;
    tangentFound = false;
    // Lower tangent
    nextL = indexL;
    while(!tangentFound) {
        tangentFound = true;
        nextR = (indexR + 1) % n2;
        while (this->isMoreCW(leftHull[indexL], rightHull[indexR], rightHull[nextR], true)) {
            if (nextR == indexR) break;
            indexR = nextR;
            nextR = (indexR + 1) % n2;
        }
        nextL = (indexL + n1 - 1) % n1;
        while (this->isMoreCCW(rightHull[indexR], leftHull[indexL], leftHull[nextL], true)) {
            if (nextL == indexL) break;
            tangentFound = false;
            indexL = nextL;
            nextL = (indexL + n1 - 1) % n1;
        }
    }
    size_t lowerTangentL = indexL;
    size_t lowerTangentR = indexR;
    std::vector<Punto<T>> mergedHull;
    mergedHull.push_back(rightHull[indexR]);
    while (indexR != upperTangentR) {
        indexR = (indexR + 1) % n2;
        mergedHull.push_back(rightHull[indexR]);
    } 
    indexL = upperTangentL;
    mergedHull.push_back(leftHull[indexL]);
    while (indexL != lowerTangentL) {
        indexL = (indexL + 1) % n1;
        mergedHull.push_back(leftHull[indexL]);
    } 
    return mergedHull;
}

template class DivideAndConquerStrategy<int>;
template class DivideAndConquerStrategy<double>;
template class DivideAndConquerStrategy<float>;
template class DivideAndConquerStrategy<long>;
template class DivideAndConquerStrategy<long long>;
