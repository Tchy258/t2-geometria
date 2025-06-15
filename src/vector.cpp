#include "vector.h"

template <typename T>
Vector<T>::Vector(T x, T y) : coords(x,y) {}

template <typename T>
Vector<T>::Vector(T x, T y, T z) : coords(x,y,z) {}

template <typename T>
Vector<T>::Vector(Punto<T> p) : coords(p.getX(),p.getY(),p.getZ()) {}

template <typename T>
Vector<T>::Vector(const Vector<T>& v) : coords(v.getCoords().getX(),v.getCoords().getY(),v.getCoords().getZ()) {}

template <typename T>
const Punto<T>& Vector<T>::getCoords() const
{
    return this->coords;
}

template <typename T>
double Vector<T>::magnitud()
{
    Punto<T> origen(static_cast<T>(0), static_cast<T>(0));
    return coords.distancia(origen);
}

template <typename T>
T Vector<T>::magnitud2() {
    // Producto punto consigo mismo es magnitud al cuadrado
    return this->productoPunto(*this);
}

template <typename T>
T Vector<T>::productoPunto(Vector<T>& other)
{
    return coords.getX() * other.getCoords().getX() + coords.getY() * other.getCoords().getY() + coords.getZ() * other.getCoords().getZ();
}

template <typename T>
Vector<T> Vector<T>::productoCruz(Vector<T>& other) 
{
    T x1 = coords.getX();
    T y1 = coords.getY();
    T z1 = coords.getZ();
    T x2 = other.getCoords().getX();
    T y2 = other.getCoords().getY();
    T z2 = other.getCoords().getZ();
    T newX = (y1 * z2) - (z1 * y2);
    T newY = (z1 * x2) - (x1 * z2);
    T newZ = (x1 * y2) - (y1 * x2);
    return Vector(newX, newY, newZ);
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other)
{
    T x1 = coords.getX();
    T y1 = coords.getY();
    T z1 = coords.getZ();
    T x2 = other.getCoords().getX();
    T y2 = other.getCoords().getY();
    T z2 = other.getCoords().getZ();
    return Vector<T>(x1 + x2, y1 + y2, z1 + z2);
}

template <typename T>
Vector<T> Vector<T>::operator-() const {
    return Vector<T>(-coords.getX(), -coords.getY(), -coords.getZ());
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& other) const
{
    return coords == other.getCoords();
}

template <typename T>
Vector<T> Vector<T>::operator*(T scalar)
{
    return Vector<T>(coords.getX() * scalar, coords.getY() * scalar, coords.getZ() * scalar);
}

template <class U>
std::ostream &operator<<(std::ostream& os, const Vector<U>& p)
{
    os << p.getCoords();
    return os;
}

template class Vector<int>;
template class Vector<double>;
template class Vector<float>;
template class Vector<long>;
template class Vector<long long>;
template std::ostream& operator<<(std::ostream&, const Vector<int>&);
template std::ostream& operator<<(std::ostream&, const Vector<float>&);
template std::ostream& operator<<(std::ostream&, const Vector<double>&);
template std::ostream& operator<<(std::ostream&, const Vector<long>&);
template std::ostream& operator<<(std::ostream&, const Vector<long long>&);