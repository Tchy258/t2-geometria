#include <gtest/gtest.h>
#include "punto.h"
#include "vector.h"
#include "poligono.h"


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

template <typename T>
class PoligonoTest : public ::testing::Test 
{
    protected:
        Poligono<T> *triangulo;
        Poligono<T> *rectangulo;
        Poligono<T> *rectanguloCW;
        Punto<T> *tp0;
        Punto<T> *tp1;
        Punto<T> *tp2;
        Punto<T> *rp0;
        Punto<T> *rp1;
        Punto<T> *rp2;
        Punto<T> *rp3;

        // Esto es un "beforeEach"
        void SetUp() override {
            this->tp0 = new Punto<T>(static_cast<T>(0),static_cast<T>(0));
            this->tp1 = new Punto<T>(static_cast<T>(2),static_cast<T>(0));
            this->tp2 = new Punto<T>(static_cast<T>(1),static_cast<T>(1));
            std::vector<Punto<T>>vertices_t = {
                *tp0,
                *tp1,
                *tp2,
            };
            this->triangulo = new Poligono<T>(vertices_t);

            this->rp0 = new Punto<T>(static_cast<T>(0),static_cast<T>(0));
            this->rp1 = new Punto<T>(static_cast<T>(2),static_cast<T>(0));
            this->rp2 = new Punto<T>(static_cast<T>(2),static_cast<T>(2));
            this->rp3 = new Punto<T>(static_cast<T>(0),static_cast<T>(2));
            std::vector<Punto<T>> vertices_r = {
                *rp0,
                *rp1,
                *rp2,
                *rp3
            };
            this->rectangulo = new Poligono<T>(vertices_r);

            std::vector<Punto<T>> vertices_r_cw = {
                *rp3,
                *rp2,
                *rp1,
                *rp0
            };

            this->rectanguloCW = new Poligono<T>(vertices_r_cw);
        }

        // Esto es un "afterEach"
        void TearDown() override {
            delete triangulo;
            delete rectangulo;
            delete rectanguloCW;
            delete tp0;
            delete tp1;
            delete tp2;
            delete rp0;
            delete rp1;
            delete rp2;
            delete rp3;
        }
};

using testTypes = ::testing::Types<int, float, double, long, long long>;



TYPED_TEST_SUITE(PoligonoTest, testTypes);

TYPED_TEST(PoligonoTest, ConstructorAndOperatorBracket)
{

    EXPECT_EQ((*this->triangulo)[0], *this->tp0);
    EXPECT_EQ((*this->triangulo)[1], *this->tp1);
    EXPECT_EQ((*this->triangulo)[2], *this->tp2);
    EXPECT_FALSE((*this->triangulo)[0] == (*this->triangulo)[1]);
    EXPECT_FALSE((*this->triangulo)[0] == *this->tp1);
    EXPECT_FALSE((*this->triangulo)[1] == *this->tp2);

    Punto<TypeParam> puntoUnico(static_cast<TypeParam>(2), static_cast<TypeParam>(3));
    std::vector<Punto<TypeParam>> vectorTamannoUno = {puntoUnico};
    EXPECT_THROW((Poligono<TypeParam>(vectorTamannoUno)),std::logic_error);
}

TYPED_TEST(PoligonoTest, CantidadDePuntos)
{


    EXPECT_EQ((*this->triangulo).cantidadDePuntos(), 3);
    EXPECT_EQ((*this->rectangulo).cantidadDePuntos(), 4);
}

TYPED_TEST(PoligonoTest, OrientacionCCW)
{
    EXPECT_TRUE((*this->triangulo).orientacionCCW());
    EXPECT_TRUE((*this->rectangulo).orientacionCCW());
    EXPECT_FALSE((*this->rectanguloCW).orientacionCCW());
}

TYPED_TEST(PoligonoTest, ConvertirACCW)
{
    EXPECT_TRUE((*this->triangulo).orientacionCCW());
    (*this->triangulo).convertirACCW();
    EXPECT_TRUE((*this->triangulo).orientacionCCW());
    EXPECT_FALSE((*this->rectanguloCW).orientacionCCW());
    (*this->rectanguloCW).convertirACCW();
    EXPECT_TRUE((*this->rectanguloCW).orientacionCCW());
}

TYPED_TEST(PoligonoTest, Area2YArea)
{
    equalityTest((*this->triangulo).area2(),static_cast<TypeParam>(2));
    EXPECT_DOUBLE_EQ((*this->triangulo).area(), 1.0);
    equalityTest((*this->rectangulo).area2(),static_cast<TypeParam>(8));
    EXPECT_DOUBLE_EQ((*this->rectangulo).area(), 4.0);
    equalityTest((*this->rectanguloCW).area2(), static_cast<TypeParam>(-8));
    EXPECT_DOUBLE_EQ((*this->rectanguloCW).area(), -4.0);
}
