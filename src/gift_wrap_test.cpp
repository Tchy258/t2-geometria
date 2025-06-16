#include "gift_wrapping_strategy.h"
#include <at_least_three_colinear_points_strategy.h>
#include <hull_tester.h>
#include <hull_percentage_strategy.h>
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
    if (argc < 2) {
        std::cout << "Usage ./Test.exe <times per size> [<filename>]" << std::endl;
        return 1;
    }
    auto strategy = std::unique_ptr<PointGenerationStrategy<long long>>(new HullPercentageStrategy<long long>(0.6));
    auto hullStrategy = std::unique_ptr<GiftWrappingStrategy<long long>>(new GiftWrappingStrategy<long long>());
    auto hullStrategy2 = std::unique_ptr<GiftWrappingStrategy<long long>>(new GiftWrappingStrategy<long long>());
    HullTester<long long> tester = HullTester<long long>(std::move(strategy), std::move(hullStrategy), std::move(hullStrategy2));
    tester.setSeed(123);
    tester.setBounds(-1000, 1000);
    std::vector<size_t> sizes({10000, 100000, 1000000});
    std::string filename = std::string("");
    if (argc > 2) {
        filename = std::string(argv[2]);
    }
    tester.timeAndTest(atoi(argv[1]), sizes, filename);
}
//*/