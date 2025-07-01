#include <divide_and_conquer_strategy.h>
#include <gift_wrapping_strategy.h>
#include <hull_tester.h>
#include <completely_random_points_strategy.h>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage ./Long longegerRandomTest.exe <times per size> [seed] [<filename>]" << std::endl;
        return 1;
    }
    long long seed = 123;
    if (argc > 2) {
        seed = atoi(argv[2]);
    }
    std::string filename = std::string("");
    if (argc > 3) {
        filename = std::string(argv[3]);
    }
    auto strategy = std::unique_ptr<PointGenerationStrategy<long long>>(new CompletelyRandomPointsStrategy<long long>());
    auto hullStrategy = std::unique_ptr<GiftWrappingStrategy<long long>>(new GiftWrappingStrategy<long long>());
    auto hullStrategy2 = std::unique_ptr<DivideAndConquerStrategy<long long>>(new DivideAndConquerStrategy<long long>());
    executeTest<long long>(atoi(argv[1]), filename, -200000, 200000, seed, std::move(strategy), std::move(hullStrategy), std::move(hullStrategy2));
}
