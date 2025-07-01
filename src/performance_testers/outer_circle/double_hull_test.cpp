#include <divide_and_conquer_strategy.h>
#include <gift_wrapping_strategy.h>
#include <hull_tester.h>
#include <hull_percentage_strategy.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage ./DoubleHullTest.exe <times per size> <percentage on hull from 0.0 to 1.00> [<colinear point amount>] [<seed>] [<filename>]" << std::endl;
        return 1;
    }
    float percentageOnHull = std::stof(argv[2]);
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
    auto hullStrategy2 = std::unique_ptr<DivideAndConquerStrategy<double>>(new DivideAndConquerStrategy<double>());
    executeTest<double>(atoi(argv[1]), filename, -200000.0, 200000.0, seed, std::move(strategy), std::move(hullStrategy), std::move(hullStrategy2));
}
