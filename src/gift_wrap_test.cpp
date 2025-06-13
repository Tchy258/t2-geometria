#include "gift_wrapping_strategy.h"
#include <iostream>

int main(int argc, char** argv) {
    std::vector<Punto<int>> puntos({
        {-1,0}, {4,0}, {3,1},
        {1,2}, {2,3}, {-1,3}
    });

    ConvexHullStrategy<int>* strategy = new GiftWrappingStrategy<int>();
    Poligono<int> capsula = strategy->apply(puntos);
    std::vector<Punto<int>> capsulaRealPuntos = {
        {-1,0}, {4,0}, {2,3}, {-1,3}
    };
    Poligono<int> capsulaReal = Poligono<int>(capsulaRealPuntos);

    std::vector<Punto<int>> puntos2({
        {0,0}, {4,0}, {4,3}, {0,3}, {2,1}, {3,2}, {1,2}
    });

    Poligono<int> capsula2 = strategy->apply(puntos2);

    std::vector<Punto<int>> capsulaRealPuntos2({
        {0,0}, {4,0}, {4,3}, {0,3}
    });

}