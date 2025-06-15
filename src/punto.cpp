#include "punto.h"

template <typename T>
Punto<T>::Punto(T x, T y) : x(x), y(y), z((T) 0) {}

template <typename T>
Punto<T>::Punto(T x, T y, T z) : x(x), y(y), z(z) {}

template <typename T>
const T Punto<T>::getX() const 
{
    return x;
}

template <typename T>
const T Punto<T>::getY() const 
{
    return y;
}

template <typename T>
const T Punto<T>::getZ() const
{
    return z;
}

template <typename T>
Punto<T>::Punto(const Punto<T>& p) 
{
    this->x = p.getX();
    this->y = p.getY();
    this->z = p.getZ();
}

template <typename T>
double Punto<T>::distancia(Punto<T>& p) 
{
    T x1 = getX();
    T y1 = getY();
    T z1 = getZ();
    T x2 = p.getX();
    T y2 = p.getY();
    T z2 = p.getZ();
    return sqrt(pow((double) (x2 - x1),2.0) + pow((double) (y2 - y1),2.0) + pow((double) (z2 - z1),2.0));
}

template <class T>
Punto<T> Punto<T>::operator-(const Punto<T> &other) const {
    return Punto<T>(getX() - other.getX(), getY() - other.getY(), getZ() - other.getZ());
}

template <class T>
bool Punto<T>::operator==(const Punto<T> &other) const
{
    return Punto<T>::equal_within_ulps(getX(),other.getX()) && Punto<T>::equal_within_ulps(getY(),other.getY()) && Punto<T>::equal_within_ulps(getZ(),other.getZ());
}

template <class T>
bool Punto<T>::operator<(const Punto<T> &other) const {
    return (getX() < other.getX()) || (equal_within_ulps(getX(),other.getX()) && getY() < other.getY());
}

template <class U>
std::ostream &operator<<(std::ostream &os, const Punto<U>& p) 
{
    os << "(" << p.getX() << "," << p.getY() << ")";
    return os;
}


template class Punto<int>;
template class Punto<double>;
template class Punto<float>;
template class Punto<long>;
template class Punto<long long>;
template std::ostream& operator<<(std::ostream&, const Punto<int>&);
template std::ostream& operator<<(std::ostream&, const Punto<float>&);
template std::ostream& operator<<(std::ostream&, const Punto<double>&);
template std::ostream& operator<<(std::ostream&, const Punto<long>&);
template std::ostream& operator<<(std::ostream&, const Punto<long long>&);