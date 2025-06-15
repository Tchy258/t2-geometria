#include "gift_wrapping_strategy.h"
#include <at_least_three_colinear_points_strategy.h>
#include <iostream>
#include <fstream>
#include <sstream>
/*
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
    Poligono<int> capsulaReal(capsulaRealPuntos);
    if (!(capsula == capsulaReal)) {
        std::cerr << capsula << std::endl;
        std::cerr << capsulaReal << std::endl;
        throw std::logic_error("Capsulas distintas");
    }

    puntos = std::vector<Punto<int>>({
        {0,0}, {4,0}, {4,3}, {0,3}, {2,1}, {3,2}, {1,2}
    });

    capsula = strategy->apply(puntos);

    capsulaRealPuntos = std::vector<Punto<int>>({
        {0,0}, {4,0}, {4,3}, {0,3}
    });

    capsulaReal = Poligono<int>(capsulaRealPuntos);
    if (!(capsula == capsulaReal)) {
        std::cerr << capsula << std::endl;
        std::cerr << capsulaReal << std::endl;
        throw std::logic_error("Capsulas distintas");
    }
}
*/
///*
int main(int argc, char** argv) {
    PointGenerationStrategy<long long>* strategy = new AtLeastThreeColinearPointsStrategy<long long>();
    ConvexHullStrategy<long long>* hullStrategy = new GiftWrappingStrategy<long long>();
    strategy->setSeed(123);
    strategy->setBounds(-1000, 1000);
    int values[] = {10000, 100000, 1000000};
    for (int i = 0; i < 3; ++i) {
        for (int k = 0; k < 3; ++k) {
            std::stringstream name;
            name << "out_" << values[i] << "_" << k << ".txt" ;
            std::ofstream file(name.str());
            std::vector<Punto<long long>> randomPoints = strategy->generate(values[i]);
            file << "Points: " << std::endl;
            file << Poligono<long long>(randomPoints) << std::endl;
            Poligono<long long> capsula = hullStrategy->apply(randomPoints);
            file << std::endl << "Hull: " << std::endl;
            file << capsula << std::endl << std::endl;
            file.close();
        }
    }
}
//*/