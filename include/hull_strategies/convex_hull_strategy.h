#ifndef CONVEX_HULL_STRATEGY_H
#define CONVEX_HULL_STRATEGY_H

#include "poligono.h"
#include "punto.h"

template <typename T>
class ConvexHullStrategy {
    public:
        virtual ~ConvexHullStrategy() = default;
        virtual Poligono<T> apply(std::vector<Punto<T>> &cloud) = 0;
        virtual std::string name() = 0;
    protected:
        inline bool isMoreCW(Punto<T> &reference, Punto<T>& currentBest, Punto<T>& newCandidate, bool keepFarthest = true) {
            Vector<T> old = Vector<T>(currentBest - reference);
            Vector<T> current = Vector<T>(newCandidate - reference);
            T crossProduct = old.productoCruz(current).getCoords().getZ();
            
            if (!Punto<T>::equal_within_ulps(crossProduct,0)) {
                return crossProduct < 0;
            }

            T distA = old.magnitud2();
            T distB = current.magnitud2();
            if (keepFarthest) {
                return distB > distA;
            } else {
                return distB <= distA;
            }
        }
};

#endif