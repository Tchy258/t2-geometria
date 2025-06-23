#ifndef _PUNTO_H
#define _PUNTO_H
#include<limits>
#include<ostream>
#include<cmath>
#include<utility>

#define PRECISION 6

template <class T>
class Punto 
{
    private:
        T x;
        T y;
        T z;
    public:
        Punto(T x, T y);
        Punto(T x, T y, T z);
        Punto(const Punto<T>& p);
        const T getX() const;
        const T getY() const;
        const T getZ() const;
        double distancia(Punto<T> &p);
        bool operator==(const Punto<T> &other) const; // El último const es necesario para que gtest funcione
        Punto<T> operator-(const Punto<T> &other) const;
        bool operator<(const Punto<T>& other) const;  // Compara por x luego por y
        template <class U>
        friend std::ostream& operator<<(std::ostream& os, const Punto<U>& p);
        // https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
        static bool equal_within_ulps(T x, T y) 
        {
            if (std::is_integral<T>::value) {
                // Exact comparison for integers
                return x == y;
            } else {
                // Since `epsilon()` is the gap size (ULP, unit in the last place)
                // of floating-point numbers in interval [1, 2), we can scale it to
                // the gap size in interval [2^e, 2^{e+1}), where `e` is the exponent
                // of `x` and `y`.
            
                // If `x` and `y` have different gap sizes (which means they have
                // different exponents), we take the smaller one. Taking the bigger
                // one is also reasonable, I guess.
                const T m = std::min(std::fabs(x), std::fabs(y));
            
                // Subnormal numbers have fixed exponent, which is `min_exponent - 1`.
                const int exp = m < std::numeric_limits<T>::min()
                            ? std::numeric_limits<T>::min_exponent - 1
                            : std::ilogb(m);
            
                // We consider `x` and `y` equal if the difference between them is
                // within `PRECISION` ULPs.
                return std::fabs(x - y) <= PRECISION * std::ldexp(std::numeric_limits<T>::epsilon(), exp);
            }
        };
};
#endif