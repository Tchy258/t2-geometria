#ifndef HULL_TESTER_H
#define HULL_TESTER_H
#include <point_generation_strategy.h>
#include <convex_hull_strategy.h>
#include <memory>
#include <fstream>
#include <chrono>
#include <sstream>

template <typename T>
class HullTester {
    private:
        std::unique_ptr<PointGenerationStrategy<T>> generator;
        std::unique_ptr<ConvexHullStrategy<T>> builder;
        std::unique_ptr<ConvexHullStrategy<T>> builder2;
    public:
        void timeAndTest(unsigned int amountOfTimesPerSize, std::vector<size_t> sizes, std::string filename = "");
        HullTester(std::unique_ptr<PointGenerationStrategy<T>>&& generator,
           std::unique_ptr<ConvexHullStrategy<T>>&& builder,
           std::unique_ptr<ConvexHullStrategy<T>>&& builder2);
        HullTester<T>& setGenerator(std::unique_ptr<PointGenerationStrategy<T>> generator);
        HullTester<T>& setBuilder(std::unique_ptr<ConvexHullStrategy<T>> builder);
        HullTester<T>& setBuilder2(std::unique_ptr<ConvexHullStrategy<T>> builder2);
        HullTester<T>& setSeed(unsigned int seed) { 
            this->generator->setSeed(seed);
            return *this;
        }
        HullTester<T>& setBounds(T lowerBound, T upperBound) {
            this->generator->setBounds(lowerBound,upperBound);
            return *this;
        }
        HullTester(const HullTester&) = delete;
        HullTester& operator=(const HullTester&) = delete;
        HullTester(HullTester&&) = default;
        HullTester& operator=(HullTester&&) = default;
};

#endif