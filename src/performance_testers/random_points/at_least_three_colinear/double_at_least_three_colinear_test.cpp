#include <divide_and_conquer_strategy.h>
#include <gift_wrapping_strategy.h>
#include <hull_tester.h>
#include <at_least_three_colinear_points_strategy.h>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage ./DoubleAtLeastThreeColinearTest.exe <times per size> [seed] [<filename>]" << std::endl;
        return 1;
    }
    int seed = 123;
    if (argc > 2) {
        seed = atoi(argv[2]);
    }
    std::string filename = std::string("");
    if (argc > 3) {
        filename = std::string(argv[3]);
    }
    auto strategy = std::unique_ptr<PointGenerationStrategy<double>>(new AtLeastThreeColinearPointsStrategy<double>());
    auto hullStrategy = std::unique_ptr<GiftWrappingStrategy<double>>(new GiftWrappingStrategy<double>());
    auto hullStrategy2 = std::unique_ptr<DivideAndConquerStrategy<double>>(new DivideAndConquerStrategy<double>());
    executeTest<double>(atoi(argv[1]), filename, -159200.0, 159200.0, seed, std::move(strategy), std::move(hullStrategy), std::move(hullStrategy2));
}
