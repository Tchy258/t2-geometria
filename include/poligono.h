#ifndef _POLIGONO_H
#define _POLIGONO_H
#include "vector.h"
#include <vector>
#include <algorithm>

template <typename T>
class Poligono
{
    private:
        std::vector<Punto<T>> puntos;
    public:
        Poligono(const std::vector<Punto<T>>& vpuntos);
        int cantidadDePuntos();
        bool orientacionCCW();
        void convertirACCW(); // Este método asume que el poligono está en CW
        T area2();
        double area();
        Punto<T>& operator[](int i);
        template <class U>
        friend std::ostream& operator<<(std::ostream& os, const Poligono<U>& p);
};

#endif