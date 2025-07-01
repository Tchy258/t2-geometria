#include <divide_and_conquer_strategy.h>
#include <gift_wrapping_strategy.h>
#include <hull_tester.h>
#include <non_colinear_points_strategy.h>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage ./IntegerNonColinearTest.exe <times per size> [seed] [<filename>]" << std::endl;
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
    auto strategy = std::unique_ptr<PointGenerationStrategy<int>>(new NonColinearPointsStrategy<int>());
    auto hullStrategy = std::unique_ptr<GiftWrappingStrategy<int>>(new GiftWrappingStrategy<int>());
    auto hullStrategy2 = std::unique_ptr<DivideAndConquerStrategy<int>>(new DivideAndConquerStrategy<int>());
    executeTest<int>(atoi(argv[1]), filename, -16383, 16383, seed, std::move(strategy), std::move(hullStrategy), std::move(hullStrategy2));
}
