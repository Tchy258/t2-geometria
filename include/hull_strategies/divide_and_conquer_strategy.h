#ifndef DIVIDE_AND_CONQUER_STRATEGY
#define DIVIDE_AND_CONQUER_STRATEGY
#include "convex_hull_strategy.h"

template <typename T>
class DivideAndConquerStrategy : public ConvexHullStrategy<T> {
    public:
        DivideAndConquerStrategy<T>() = default;
        Poligono<T> apply(std::vector<Punto<T>> &cloud) override;
        std::string name() override {
            return std::string("DivideAndConquer");
        };
    private:
        std::vector<Punto<T>> joinHulls(std::vector<Punto<T>> &leftHull, std::vector<Punto<T>> &rightHull);
        std::vector<Punto<T>> applyRecursive(std::vector<Punto<T>> &cloud);
        inline bool isMoreCW(Punto<T> &reference, Punto<T>& currentBest, Punto<T>& newCandidate, bool keepFarthest = true);
};

#endif