#ifndef GIFT_WRAPPING_STRATEGY_H
#define GIFT_WRAPPING_STRATEGY_H
#include "convex_hull_strategy.h"
#include <bitset>
template <typename T>
class GiftWrappingStrategy : public ConvexHullStrategy<T> {
    public:
        GiftWrappingStrategy<T>() = default;
        Poligono<T> apply(std::vector<Punto<T>> &cloud) override;
    private:
        inline bool compareByAngle(Vector<T>& refDir, Vector<T>& lastCandidate, Vector<T>& candidate);
};

#endif