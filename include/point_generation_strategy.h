#ifndef POINT_GENERATION_STRATEGY_H
#define POINT_GENERATION_STRATEGY_H

#include "punto.h"

template <typename T>
class PointGenerationStrategy {
    virtual Punto<T>[] generate(unsigned int amount) = 0;
};

#endif