#ifndef CONVEX_HULL_STRATEGY_H
#define CONVEX_HULL_STRATEGY_H

#include "poligono.h"
#include "punto.h"

template <typename T>
class ConvexHullStrategy {
    public:
        virtual ~ConvexHullStrategy() = default;
        virtual Poligono<T> apply(std::vector<Punto<T>> &cloud) = 0;
};

#endif