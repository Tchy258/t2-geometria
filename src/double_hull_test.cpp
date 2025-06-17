#include "gift_wrapping_strategy.h"
#include <at_least_three_colinear_points_strategy.h>
#include <hull_tester.h>
#include <hull_percentage_strategy.h>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage ./DoubleHullTest.exe <times per size> <percentage on hull from 0 to 100> [<colinear point amount?] [seed] [<filename>]" << std::endl;
        return 1;
    }
    float percentageOnHull = static_cast<float>(atoi(argv[2])) / 100.0f;
    unsigned int colinear = 0;
    if (argc > 3) {
        colinear = atoi(argv[3]);
    }
    int seed = 123;
    if (argc > 4) {
        seed = atoi(argv[4]);
    }
    std::string filename = std::string("");
    if (argc > 5) {
        filename = std::string(argv[5]);
    }
    auto strategy = std::unique_ptr<PointGenerationStrategy<double>>(new HullPercentageStrategy<double>(percentageOnHull, colinear));
    auto hullStrategy = std::unique_ptr<GiftWrappingStrategy<double>>(new GiftWrappingStrategy<double>());
    auto hullStrategy2 = std::unique_ptr<GiftWrappingStrategy<double>>(new GiftWrappingStrategy<double>());
    executeTest<double>(atoi(argv[1]), filename, -159200.0, 159200.0, seed, std::move(strategy), std::move(hullStrategy), std::move(hullStrategy2));
}
