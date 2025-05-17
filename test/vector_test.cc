#include <gtest/gtest.h>
#include "vector.h"
#include "punto.h"

template <typename T>
class VectorTest : public ::testing:: Test {};

using testTypes = ::testing::Types<int, float, double, long, long long>;



TYPED_TEST_SUITE(VectorTest, testTypes);


TYPED_TEST(VectorTest, ConstructorAndGetter)
{
    // Constructor with 2 coords
    Vector<TypeParam> vec(static_cast<TypeParam>(0),static_cast<TypeParam>(0));

    EXPECT_EQ(vec.getCoords(), Punto<TypeParam>(static_cast<TypeParam>(0),static_cast<TypeParam>(0)));
    
    // Constructor with 3 coords
    Vector<TypeParam> vec2(static_cast<TypeParam>(0),static_cast<TypeParam>(0),static_cast<TypeParam>(0));

    EXPECT_EQ(vec2.getCoords(), Punto<TypeParam>(static_cast<TypeParam>(0),static_cast<TypeParam>(0),static_cast<TypeParam>(0)));
}

TYPED_TEST(VectorTest, CopyConstructor)
{
        Vector<TypeParam> vec(static_cast<TypeParam>(2),static_cast<TypeParam>(3));
        Vector<TypeParam> copia(vec);
        EXPECT_EQ(copia.getCoords(), vec.getCoords());
}

TYPED_TEST(VectorTest, ConstructorFromPunto)
{
    // Constructor with 2 coords
    Punto<TypeParam> punto(static_cast<TypeParam>(0),static_cast<TypeParam>(0));
    Vector<TypeParam> vec(punto);
    Punto<TypeParam> puntoIdentico(static_cast<TypeParam>(0),static_cast<TypeParam>(0));
    Punto<TypeParam> coords = vec.getCoords();

    EXPECT_EQ(coords, puntoIdentico);

    // Constructor with 3 coords
    Punto<TypeParam> punto2(static_cast<TypeParam>(0),static_cast<TypeParam>(0), static_cast<TypeParam>(0));
    Vector<TypeParam> vec2(punto2);
    Punto<TypeParam> puntoIdentico2(static_cast<TypeParam>(0),static_cast<TypeParam>(0), static_cast<TypeParam>(0));
    Punto<TypeParam> coords2 = vec2.getCoords();
    EXPECT_EQ(coords2, puntoIdentico2);
}

TYPED_TEST(VectorTest, OperatorEquals)
{
    Vector<TypeParam> v1(static_cast<TypeParam>(4),static_cast<TypeParam>(3));
    Vector<TypeParam> v2(static_cast<TypeParam>(4),static_cast<TypeParam>(3));
    EXPECT_TRUE(v1 == v2);

    Vector<TypeParam> distinto(static_cast<TypeParam>(3),static_cast<TypeParam>(4));
    EXPECT_FALSE(v1 == distinto);
    EXPECT_FALSE(v2 == distinto);
    
    Vector<TypeParam> v3(static_cast<TypeParam>(4),static_cast<TypeParam>(3), static_cast<TypeParam>(2));
    Vector<TypeParam> v4(static_cast<TypeParam>(4),static_cast<TypeParam>(3), static_cast<TypeParam>(2));
    EXPECT_TRUE(v3 == v4);

    Vector<TypeParam> distintoZ(static_cast<TypeParam>(4),static_cast<TypeParam>(3), static_cast<TypeParam>(1));
    EXPECT_FALSE(v3 == distintoZ);
    EXPECT_FALSE(v4 == distintoZ);
}

TYPED_TEST(VectorTest, Magnitud)
{
    // int
    Vector<TypeParam> vec(static_cast<TypeParam>(3), static_cast<TypeParam>(4));
    EXPECT_DOUBLE_EQ(5.0, vec.magnitud());
}

TYPED_TEST(VectorTest, ProductoPunto)
{
    Vector<TypeParam> v1(static_cast<TypeParam>(6),static_cast<TypeParam>(3));
    Vector<TypeParam> v2(static_cast<TypeParam>(4),static_cast<TypeParam>(2));
    TypeParam resultadoEsperado = static_cast<TypeParam>(30);
    EXPECT_EQ(v1.productoPunto(v2), resultadoEsperado);
}

TYPED_TEST(VectorTest, ProductoCruz)
{
    Vector<TypeParam> v1(static_cast<TypeParam>(3), static_cast<TypeParam>(4));
    Vector<TypeParam> v2(static_cast<TypeParam>(2), static_cast<TypeParam>(7));
    Vector<TypeParam> resultado = v1.productoCruz(v2);
    Vector<TypeParam> resultadoEsperado(static_cast<TypeParam>(0), static_cast<TypeParam>(0), static_cast<TypeParam>(13));
    EXPECT_EQ(resultado,resultadoEsperado);
}

TYPED_TEST(VectorTest, OperatorSum)
{
    Vector<TypeParam> v1(static_cast<TypeParam>(2), static_cast<TypeParam>(4));
    Vector<TypeParam> v2(static_cast<TypeParam>(4), static_cast<TypeParam>(8));
    Vector<TypeParam> resultadoEsperado(static_cast<TypeParam>(6), static_cast<TypeParam>(12));
    EXPECT_EQ(v1 + v2, resultadoEsperado);

    Vector<TypeParam> v3(static_cast<TypeParam>(2), static_cast<TypeParam>(4), static_cast<TypeParam>(6));
    Vector<TypeParam> v4(static_cast<TypeParam>(4), static_cast<TypeParam>(8), static_cast<TypeParam>(10));
    Vector<TypeParam> resultadoEsperado2(static_cast<TypeParam>(6), static_cast<TypeParam>(12), static_cast<TypeParam>(16));
    EXPECT_EQ(v3 + v4, resultadoEsperado2);
}

TYPED_TEST(VectorTest, OperatorMultiplyByScalar)
{
    TypeParam scalar = static_cast<TypeParam>(2);
    Vector<TypeParam> vec(static_cast<TypeParam>(3), static_cast<TypeParam>(6));
    Vector<TypeParam> resultadoEsperado(static_cast<TypeParam>(6), static_cast<TypeParam>(12));
    EXPECT_EQ(vec * scalar, resultadoEsperado);
}