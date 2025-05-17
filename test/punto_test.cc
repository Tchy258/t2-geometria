#include <gtest/gtest.h>
#include "punto.h"

template <typename T>
class PuntoTest : public ::testing:: Test {};

using testTypes = ::testing::Types<int, float, double, long, long long>;



TYPED_TEST_SUITE(PuntoTest, testTypes);

template <typename T>
void equalityTest(const T& a, const T& b)
{
    if (std::is_floating_point<T>::value)
    {
        EXPECT_NEAR(a, b, std::numeric_limits<T>::epsilon());
    }
    else
    {
        EXPECT_EQ(a, b);
    }
}


TYPED_TEST(PuntoTest, ConstructorAndGetters)
{
    // Constructor with 2 coords
    Punto<TypeParam> punto(static_cast<TypeParam>(4),static_cast<TypeParam>(3));

    equalityTest(punto.getX(),(static_cast<TypeParam>(4)));
    equalityTest(punto.getY(),(static_cast<TypeParam>(3)));
    equalityTest(punto.getZ(),(static_cast<TypeParam>(0)));
    
    // Constructor with 3 coords
    Punto<TypeParam> punto2(static_cast<TypeParam>(3),static_cast<TypeParam>(2),static_cast<TypeParam>(1));

    equalityTest(punto2.getX(),(static_cast<TypeParam>(3)));
    equalityTest(punto2.getY(),(static_cast<TypeParam>(2)));
    equalityTest(punto2.getZ(),(static_cast<TypeParam>(1)));

}

TYPED_TEST(PuntoTest, CopyConstructor)
{
    Punto<TypeParam> punto(static_cast<TypeParam>(2),static_cast<TypeParam>(3));
    Punto<TypeParam> copia(punto);
    equalityTest(copia.getX(), punto.getX());
    equalityTest(copia.getY(), punto.getY());
    equalityTest(copia.getZ(), punto.getZ());

}


TYPED_TEST(PuntoTest, OperatorEquals)
{
    Punto<TypeParam> p1(static_cast<TypeParam>(4),static_cast<TypeParam>(3));
    Punto<TypeParam> p2(static_cast<TypeParam>(4),static_cast<TypeParam>(3));
    EXPECT_TRUE(p1 == p2);

    Punto<TypeParam> pDistinto(static_cast<TypeParam>(3),static_cast<TypeParam>(4));
    EXPECT_FALSE(p1 == pDistinto);
    
    Punto<TypeParam> p3(static_cast<TypeParam>(4),static_cast<TypeParam>(3),static_cast<TypeParam>(2));
    Punto<TypeParam> p4(static_cast<TypeParam>(4),static_cast<TypeParam>(3),static_cast<TypeParam>(2));
    EXPECT_TRUE(p3 == p4);

    Punto<TypeParam> pDistintoZ(static_cast<TypeParam>(4),static_cast<TypeParam>(3),static_cast<TypeParam>(1));
    EXPECT_FALSE(p3 == pDistintoZ);
}


TYPED_TEST(PuntoTest, Distancia)
{
    Punto<TypeParam> a(static_cast<TypeParam>(0), static_cast<TypeParam>(0));
    Punto<TypeParam> b(static_cast<TypeParam>(3), static_cast<TypeParam>(4));
    EXPECT_DOUBLE_EQ(5.0, a.distancia(b));

    Punto<TypeParam> c(static_cast<TypeParam>(1), static_cast<TypeParam>(2));
    Punto<TypeParam> d(static_cast<TypeParam>(7), static_cast<TypeParam>(10));
    EXPECT_DOUBLE_EQ(10.0, c.distancia(d));
}