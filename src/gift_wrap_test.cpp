#include "gift_wrapping_strategy.h"
#include <iostream>

int main(int argc, char** argv) {
    Punto<int> puntos[6] = {
        {-1,0}, {4,0}, {3,1},
        {1,2}, {2,3}, {-1,3}
    };

    ConvexHullStrategy<int>* strategy = new GiftWrappingStrategy<int>(6ULL);
    Poligono<int> capsula = strategy->apply(puntos);
    std::vector<Punto<int>> capsulaRealPuntos = {
        {-1,0}, {4,0}, {3,1}, {2,3}, {-1,3}
    };
    Poligono<int> capsulaReal = Poligono<int>(capsulaRealPuntos);
}