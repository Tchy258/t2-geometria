#include <divide_and_conquer_strategy.h>
#include <gift_wrapping_strategy.h>
#include <hull_tester.h>
#include <at_least_three_colinear_points_strategy.h>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage ./FloatAtLeastThreeColinearTest.exe <times per size> [seed] [<filename>]" << std::endl;
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
    auto strategy = std::unique_ptr<PointGenerationStrategy<float>>(new AtLeastThreeColinearPointsStrategy<float>());
    auto hullStrategy = std::unique_ptr<GiftWrappingStrategy<float>>(new GiftWrappingStrategy<float>());
    auto hullStrategy2 = std::unique_ptr<DivideAndConquerStrategy<float>>(new DivideAndConquerStrategy<float>());
    executeTest<float>(atoi(argv[1]), filename, -30000.0, 30000.0, seed, std::move(strategy), std::move(hullStrategy), std::move(hullStrategy2));
}
