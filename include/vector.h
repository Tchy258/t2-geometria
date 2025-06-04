#ifndef _VECTOR_H
#define _VECTOR_H
#include "punto.h"

template <typename T>
class Vector 
{
    private:
        Punto<T> coords;
    public:
        Vector(T x, T y);
        Vector(T x, T y, T z);
        Vector(Punto<T> p);
        Vector(const Vector<T>& v);
        const Punto<T>& getCoords() const;
        double magnitud();
        T productoPunto(Vector<T>& other);
        Vector<T> productoCruz(Vector<T>& other);
        Vector<T> operator+(const Vector<T>& other);
        Vector<T> operator-() const;
        bool operator==(const Vector<T>& other) const;
        Vector<T> operator*(T scalar);
        template <class U>
        friend std::ostream &operator<<(std::ostream& os, const Vector<U>& p);
};

#endif