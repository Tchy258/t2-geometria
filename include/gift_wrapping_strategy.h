#ifndef GIFT_WRAPPING_STRATEGY_H
#define GIFT_WRAPPING_STRATEGY_H
#include "convex_hull_strategy.h"

template <typename T>
class GiftWrappingStrategy : public ConvexHullStrategy<T> {
    private:
        unsigned long long n;
    public:
        GiftWrappingStrategy(unsigned long long n);
        Poligono<T> apply(Punto<T> cloud[]) override;
};

#endif