#include <iostream>
#include "punto.h"
#include "vector.h"
#include "poligono.h"

int main(int argc, char** argv) {
    std::cout << "Probando operaciones sobre punto" << std::endl << std::endl << "Constructor" << std::endl;
    Punto<int> punto(1,2);
    std::cout << "Imprimiendo punto:" << std::endl;
    std::cout << punto << std::endl;
    std::cout << "Creando otro punto:" << std::endl;
    Punto<int> punto2(2,3);
    std::cout << punto2 << std::endl;
    std::cout << "Distancia entre estos puntos:" << std::endl;
    std::cout << punto.distancia(punto2) << std::endl;
    std::cout << "Iguales? " << (punto == punto2 ? "Si" : "No") << std::endl;
    std::cout << "Copiando primer punto" << std::endl;
    Punto<int> puntoCopia(punto);
    std::cout << puntoCopia << std::endl;
    std::cout << "Iguales? " << (punto == puntoCopia ? "Si" : "No") << std::endl;

    std::cout << std::endl << "Probando operaciones sobre vector" << std::endl << std::endl << "Constructor" << std::endl;
    Vector<int> vec(3,5);
    std::cout << "Imprimiendo vector:" << std::endl;
    std::cout << vec << std::endl;
    std::cout << "Creando otro vector:" << std::endl;
    Vector<int> vec2(5,7);
    std::cout << vec2 << std::endl;
    std::cout << "Imprimiendo magnitud del vector1:" << std::endl;
    std::cout << vec.magnitud() << std::endl;
    std::cout << "Imprimiendo magnitud del vector2:" << std::endl;
    std::cout << vec2.magnitud() << std::endl;
    std::cout << "Producto punto entre estos vectores:" << std::endl;
    std::cout << vec.productoPunto(vec2) << std::endl;
    std::cout << "Producto cruz entre estos vectores:" << std::endl;
    Vector<int> cruz = vec.productoCruz(vec2);
    std::cout << cruz << std::endl;
    std::cout << "Coordenada Z con resultado:" << std::endl;
    std::cout << cruz.getCoords().getZ() << std::endl;
    std::cout << "Vector a partir de un punto" << std::endl;
    Vector<int> desdePunto(punto);
    std::cout << desdePunto << std::endl;
    std::cout << "Multiplicación por escalar con valor 2" << std::endl;
    Vector<int> multiplicado = desdePunto * 2;
    std::cout << multiplicado << std::endl;
    Vector<int> sumado = multiplicado + vec;
    std::cout << "Suma de esta multiplicación con vector1:" << std::endl;
    std::cout << sumado << std::endl;
    std::cout << std::endl << "Probando operaciones sobre poligono" << std::endl << std::endl;
    std::cout << "Constructor generando un triangulo" << std::endl;
    Punto<int> tp0(0,0);
    Punto<int> tp1(2,0);
    Punto<int> tp2(1,1);
    Poligono<int> triangulo(std::vector<Punto<int>>{tp0,tp1,tp2});
    std::cout << "Imprimiendo triangulo:" << std::endl;
    std::cout << triangulo << std::endl;
    std::cout << "Cantidad de puntos: " << triangulo.cantidadDePuntos() << std::endl;
    std::cout << "Es CCW? " << (triangulo.orientacionCCW() ? "Si" : "No") << std::endl;
    std::cout << "Doble del area: " << triangulo.area2() << std::endl;
    std::cout << "Area: " << triangulo.area() << std::endl;
    std::cout << "Imprimiendo puntos individuales:" << std::endl;
    std::cout << triangulo[0] << std::endl << triangulo[1] << std::endl << triangulo[2] << std::endl;
    std::cout << "Creando el mismo triangulo en CW" << std::endl;
    Poligono<int> trianguloCW(std::vector<Punto<int>>{tp2,tp1,tp0});
    std::cout << trianguloCW << std::endl;
    std::cout << "Es CCW? " << (trianguloCW.orientacionCCW() ? "Si" : "No") << std::endl;
    std::cout << "Convirtiendo de CW a CCW" << std::endl;
    trianguloCW.convertirACCW();
    std::cout << trianguloCW << std::endl;
    std::cout << "Es CCW? " << (trianguloCW.orientacionCCW() ? "Si" : "No") << std::endl;
}
