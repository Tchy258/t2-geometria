#include "poligono.h"

template <typename T>
Poligono<T>::Poligono(const std::vector<Punto<T>>& vpuntos): puntos(vpuntos) 
{
    if (vpuntos.size() < 3) {
        throw std::logic_error("Poligono debe tener al menos 3 puntos");
    }
}

template <typename T>
int Poligono<T>::cantidadDePuntos()
{
    return puntos.size();
}

template <typename T>
Punto<T>& Poligono<T>::operator[](int i)
{
    return puntos[i];
}

template <typename T>
T Poligono<T>::area2()
{
    T total = (T) 0;
    for (int i = 0; i < puntos.size(); i++) {
        Vector<T> vec1(puntos[i]);
        Vector<T> vec2(puntos[(i + 1) % puntos.size()]);
        total += vec1.productoCruz(vec2).getCoords().getZ();
    }
    return total;
}

template <typename T>
double Poligono<T>::area()
{
    return (double) area2()/2.0;
}

template <typename T>
bool Poligono<T>::orientacionCCW()
{
    return area2() > 0;
}


template <typename T>
void Poligono<T>::convertirACCW()
{
    if (orientacionCCW()) return;
    else {
        std::reverse(puntos.begin(),puntos.end());
    }
}

template <class U>
std::ostream &operator<<(std::ostream& os, const Poligono<U>& poligono)
{
    os << "[" << poligono.puntos[0];
    for (int i = 1; i < poligono.puntos.size(); i++) {
        os << "," << poligono.puntos[i];
    }
    os << "]";
    return os;
}

template class Poligono<int>;
template class Poligono<double>;
template class Poligono<float>;
template class Poligono<long>;
template class Poligono<long long>;
template std::ostream& operator<<(std::ostream&, const Poligono<int>&);
template std::ostream& operator<<(std::ostream&, const Poligono<float>&);
template std::ostream& operator<<(std::ostream&, const Poligono<double>&);
template std::ostream& operator<<(std::ostream&, const Poligono<long>&);
template std::ostream& operator<<(std::ostream&, const Poligono<long long>&);