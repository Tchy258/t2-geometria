#ifndef GIFT_WRAPPING_STRATEGY_H
#define GIFT_WRAPPING_STRATEGY_H
#include "convex_hull_strategy.h"

template <typename T>
class GiftWrappingStrategy : public ConvexHullStrategy<T> {
    public:
        GiftWrappingStrategy<T>() = default;
        Poligono<T> apply(std::vector<Punto<T>> &cloud) override;
        std::string name() override {
            return std::string("GiftWrapping");
        };
};

#endif