#include <hull_tester.h>

template<typename T>
HullTester<T>::HullTester(std::unique_ptr<PointGenerationStrategy<T>>&& generator,
           std::unique_ptr<ConvexHullStrategy<T>>&& builder,
           std::unique_ptr<ConvexHullStrategy<T>>&& builder2)
 : generator(std::move(generator)), builder(std::move(builder)), builder2(std::move(builder2)) {}

template<typename T>
HullTester<T>& HullTester<T>::setGenerator(std::unique_ptr<PointGenerationStrategy<T>> generator) {
    this->generator = std::move(generator);
    return *this;
}

template<typename T>
HullTester<T>& HullTester<T>::setBuilder(std::unique_ptr<ConvexHullStrategy<T>> builder) {
    this->builder = std::move(builder);
    return *this;
}

template<typename T>
HullTester<T>& HullTester<T>::setBuilder2(std::unique_ptr<ConvexHullStrategy<T>> builder2) {
    this->builder2 = std::move(builder2);
    return *this;
}

template<typename T>
void HullTester<T>::timeAndTest(unsigned int amountOfTimesPerSize, std::vector<size_t> sizes, std::string filename) {
    std::ofstream file;
    if (filename != "") {
        file.open(filename);        
    } else {
        file.open("results.csv");
    }
    std::stringstream head;
    head << sizes[0] << builder->name() << ",";
    head << sizes[0] << builder2->name() << ",";
    for (int i = 1; i < sizes.size(); ++i) {
        head << "," << sizes[i] << builder->name();
        head << "," << sizes[i] << builder2->name();
    }
    head << std::endl;
    file << head.str();
    for (int k = 0; k < amountOfTimesPerSize; ++k) {
        std::stringstream row;
        row.str(std::string());
        for (int i = 0; i < sizes.size(); ++i) {
            std::vector<Punto<T>> points = generator->generate(sizes[i]);
            auto start1 = std::chrono::high_resolution_clock::now();
            Poligono<T> poligono = builder->apply(points);
            auto end1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration1 = end1 - start1;
            row << (i == 0 ? "" : ",") << duration1.count();
            auto start2 = std::chrono::high_resolution_clock::now();
            Poligono<T> poligono2 = builder2->apply(points);
            auto end2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration2 = end2 - start2;
            row << "," << duration2.count();
        }
        row << std::endl;
        file << row.str();
    }
    file.close();
}

template class HullTester<int>;
template class HullTester<double>;
template class HullTester<float>;
template class HullTester<long>;
template class HullTester<long long>;
