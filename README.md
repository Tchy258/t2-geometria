# Tarea 2 y 3 Geometría Computacional

Este código corresponde a la Tarea 2 y 3 - Cerradura Convexa de Nicolás Escobar Zarzar alumno del curso CC5502 Geometría Computacional del semestre otoño 2025.
Esta tarea consiste en programar dos algoritmos de cerradura convexa haciendo uso de las clases hechas en la Tarea 1, los algoritmos a implementar son GiftWrapping y Divide and Conquer. Esto se hace mediante la implementación del patrón de diseño _strategy_ usando la clase `ConvexHullStrategy` como base. También se pide diseñar un experimento para determinar para que distribuciones de punto es mejor usar uno u otro, junto con un método que genere una lista aleatoria de n puntos y otro que genere un conjunto de puntos en que un cierto porcentaje de estos forme parte de la cerradura convexa y el resto se distribuya aleatoriamente en el interior, también usando el patrón strategy con la clase `PointGenerationStrategy`.
Fue desarrollada usando Visual Studio Code en Windows, pero a continuación se dan las instrucciones para su compilación y ejecución en cualquier entorno de escritorio (Windows, Linux, MacOS). También es necesario aclarar ciertos detalles de implementación

## Detalles de implementación

Para el algoritmo GiftWrapping, lo usual es iniciar desde el punto más hacia abajo (y a la izquierda), y luego revisar para cada punto con cual se forma el ángulo menor en ccw respecto al punto actual y seguir formando la cápsula a través de este.

Dado que calcular ángulos es computacionalmente caro, se opta por usar tanto producto cruz como producto punto, aprovechandose de las siguientes identidades:
$$
\vec A × \vec B = sin(\theta)\ ||A||\cdot ||B||
\newline
\vec A \cdot \vec B = cos(\theta)\ ||A||\cdot ||B||
\newline
\Rightarrow tan(\theta) = \frac{\vec A × \vec B}{\vec A \cdot \vec B}
\newline
$$
También se tiene que
$$
\vec A \cdot \vec A = ||A||^2
\newline
\vec A × \vec A = 0
$$
Como queremos comparar si un ángulo es menor que otro, no basta con solo usar producto cruz, ya que, por definición, este es el seno del ángulo multiplicado por el producto de la magnitud de los vectores. Por lo tanto, utilizamos la siguiente función de [gift_wrapping_strategy](src/gift_wrapping_strategy.cpp)
```cpp
template<class T>
inline bool GiftWrappingStrategy<T>::compareByAngle(Vector<T>&refDir, Vector<T>& lastCandidate, Vector<T>& candidate) {
    T lastBestCross = refDir.productoCruz(lastCandidate).getCoords().getZ();
    T lastBestDot = refDir.productoPunto(lastCandidate);
    T candidateCross = refDir.productoCruz(candidate).getCoords().getZ();
    T candidateDot = refDir.productoPunto(candidate);
     // If angles are on different sides of the refDir
    if ((lastBestCross < 0 && candidateCross >= 0)) return true;
    if ((lastBestCross >= 0 && candidateCross < 0)) return false;

    // If same direction (possibly collinear), compare using tan = cross / dot
    T cmp = lastBestCross * candidateDot - candidateCross * lastBestDot;
    if (!Punto<T>::equal_within_ulps(cmp,0)) return cmp > 0;

    // Collinear: pick the point farther from p
    T distA = lastCandidate.magnitud2();
    T distB = candidate.magnitud2();
    return distB > distA;
}
```

Esta función hace lo siguiente: Dado un vector de referencia (de donde venimos), un vector candidato anterior (el vector que se cree que apunta al próximo punto de la cápusla convexa) y un candidato nuevo (un vector que apunta hacia algún otro punto):
+ Si el producto cruz entre el vector de referencia y el candidato anterior es negativo (el candidato anterior estaba a la derecha (o colineal) de la punta del vector de referencia) y el producto cruz con el nuevo candidato es positivo (está a la izquierda del vector de referencia), entonces el nuevo candidato es quien permite hacer un giro ccw útil, ya que el anterior iba a la derecha.
+ Si el candidato anterior ya hace un giro en sentido anti horario y el nuevo candidato no, entonces no sirve
+ Si ninguna de las dos anteriores se cumple, entonces ambos permiten hacer un giro anti horario, por lo que se debe revisar cual es el giro anti horario más útil (aquel que tiene menor ángulo), para ello, considerando el vector de referencia como R, el candidato anterior como A y el nuevo como B, se cálcula el siguiente valor $\alpha$:
$$
\alpha = ||(\vec R × \vec A)|| \cdot (\vec R \cdot \vec B)  - ||(\vec R × \vec B)|| \cdot (\vec R \cdot \vec A)
$$
Este valor $\alpha$ en realidad está comparando las tangentes de ambos vectores (con el especial cuidado de no dividir por 0), si $\alpha$ es mayor que 0, entonces la tangente del ángulo formado por el vector de referencia y el candidato anterior es mayor que la del nuevo candidato, esto significa que el nuevo candidato tiene un ángulo menor, por lo que su giro es "menos anti horario" que el anterior, haciendo que sea un mejor candidato para la capsula convexa. Esto se ve mediante la siguiente identidad mostrada anteriormente:
$$
tan(\theta_1) > tan(\theta_2)
\newline
\frac{||(\vec R × \vec B)||}{(\vec R \cdot \vec A)} > \frac{||(\vec R × \vec B)||}{(\vec R \cdot \vec B)}
\newline
||(\vec R × \vec A)|| \cdot (\vec R \cdot \vec B)  > ||(\vec R × \vec B)|| \cdot (\vec R \cdot \vec A)
\newline
||(\vec R × \vec A)|| \cdot (\vec R \cdot \vec B)  - ||(\vec R × \vec B)|| \cdot (\vec R \cdot \vec A) > 0
\newline
\Rightarrow \alpha > 0
$$
Si el valor de $\alpha$ es 0, entonces se debe de cumplir que el producto cruz del vector de referencia con ambos vectores sea 0, esto sucede si y solo si, hay 3 puntos colineales, puesto que el seno del ángulo debe ser 0 (asumiendo que no hay puntos duplicados). La otra posibilidad es que el producto punto con ambos vectores sea 0, lo que también implica colinealidad, porque anteriormente verificamos que se cumple que el giro es hacia la misma dirección, entonces necesariamente ambos vectores son perpendiculares al de referencia en la misma dirección. Para elegir entre uno de estos puntos colineales, se escoge aquel que esté más lejos, y se determina mediante la operación `magnitud2` que es simplemente el producto punto de un vector consigo mismo, lo que resulta en su magnitud al cuadrado. Si uno ya es mayor/menor que otro, entonces al cuadrado lo seguirá siendo, por lo que esto permite ahorrar el cálculo de la raíz cuadrada involucrada en el cálculo de la magnitud.
## Herramientas necesarias

### g++
Es necesario tener instalado el compilador GNU g++ versión 14.2.0, el cual se puede instalar mediante [MSYS2](https://www.msys2.org/) en Windows o mediante el gestor de paquetes que corresponda en Linux:


Debian / Ubuntu / Pop!_OS / Linux Mint
```bash
sudo apt update
sudo apt install build-essential
```
Arch Linux / Manjaro
```bash
sudo pacman -S --needed base-devel
```
Fedora / RHEL / CentOS (8+) / Rocky Linux / AlmaLinux
```bash
sudo dnf groupinstall "Development Tools"
``` 
CentOS 7
```bash
sudo yum groupinstall "Development Tools"
```
openSUSE
```bash
sudo zypper install -t pattern devel_basis
```
Gentoo
```bash
sudo emerge --ask sys-devel/gcc sys-devel/make sys-devel/binutils
```
Void Linux
```bash
sudo xbps-install -S base-devel
```
Alpine Linux
```bash
sudo apk add build-base
```

En macOS se puede obtener mediante [Homebrew](https://brew.sh/)
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
brew install make gcc g++
```
### CMake
Para compilar esta librería se necesita CMake 3.31, este se puede descargar desde [la página de CMake](https://cmake.org/download/) o mediante el gestor de paquetes (no se recomienda, pues no se puede asegurar la versión correcta de CMake).\
Si se está en Windows podría ser necesario agregar la carpeta `bin` de la instalación de CMake a la variable de entorno `$PATH` de forma manual.

## Configuración

Esta libería se debe compilar en Windows con el generador `MinGW Makefiles` y en Linux/macOs con el generador `Unix Makefiles` usando el compilador GNU g++ version 14.2.0\
Para ello se deben configurar las siguientes variables de entorno:
+ CC: Ruta al compilador de lenguaje C, por defecto con una instalación estándar de MSYS2 es `C:\msys64\ucrt64\bin\gcc.exe`, en linux `/usr/bin/gcc`.
+ CXX: Ruta al compilador de lenguaje C++, por defecto con una instalación estándar de MSYS2 es `C:\msys64\ucrt64\bin\g++.exe`, en linux `/usr/bin/g++`.
+ CMAKE_GENERATOR: `"MinGW Makefiles"` o `"Unix Makefiles"` según corresponda.

Para dejar estas variables configuradas durante la sesión actual de terminal se debe ingresar lo siguiente en su terminal de preferencia.

### cmd
```
> set CC=C:\msys64\ucrt64\bin\gcc.exe
> set CXX=C:\msys64\ucrt64\bin\g++.exe
> set CMAKE_GENERATOR="MinGW Makefiles"
```
### powershell
```pwsh
> $env:CC="C:\msys64\ucrt64\bin\gcc.exe"
> $env:CXX="C:\msys64\ucrt64\bin\g++.exe"
> $env:CMAKE_GENERATOR="MinGW Makefiles"
```
### bash
```bash
$ export CC=/usr/bin/gcc
$ export CXX=/usr/bin/g++
$ export CMAKE_GENERATOR="Unix Makefiles"
```

De no configurarse dichas variables de entorno, se pueden también configurar para una invocación única de CMake mediante los siguientes argumentos:
```bash
$ cmake -DCC=/usr/bin/gcc -DCXX=/usr/bin/g++ -DCMAKE_GENERATOR="Unix Makefiles" <comando>
```
(Reemplazar los valores de cada variable según el sistema operativo que corresponda).

# Compilación
Habiendo hecho la configuración basta con ejecutar los siguientes comandos en una terminal estando en la carpeta raíz del projecto:
```bash
$ cmake -S . -B build/release
$ cmake --build build/release
```
Esto generará las librerías estáticas en `build/src` con los nombres `libpunto`, `libvector` y `libpoligono` con la extensión que corresponda y también el archivo
`Tarea1.exe`. Adicionalmente este comando compilará los tests.

Notar que si se desea hacer debugging o revisar el porcentaje de coverage es necesario configurar la flag `CMAKE_BUILD_TYPE` con el valor `Debug` para compilar la librería con los simbolos correspondientes de la siguiente manera:
```bash
$ cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug
$ cmake --build build/debug
```
Esto creara la librería en la carpeta `/build/debug/src` y los archivos con extension `gcda` y `gcno` creados por gcov

# Tests
Los tests se encuentran en `test/punto_test.cc`, `test/vector_test.cc` y `test/poligono_test.cc`, una vez se compila el proyecto, se generan ejecutables con los nombres anteriores en `build/release/test/` o `build/debug/test` los cuales pueden ejecutarse estando en la carpeta correspondiente con el comando:
```bash
$ ctest
```
O alternativamente desde la carpeta raíz del proyecto con
```bash
$ ctest --test-dir ./build/debug/test/
```
(Usar \\ en vez de / en windows)

## Coverage
Si se desea ver el porcentaje de coverage del código se necesita instalar python3.9+ y el paquete [gcovr](https://github.com/gcovr/gcovr) mediante el comando
```bash
$ python -m pip install gcovr
``` 
Una vez se hace la build y se corren los tests al menos una vez hay que ir al archivo `gcovr.cfg` y cambiar el valor de la llave `gcovr-executable` a la ruta de la herramienta `gcov` que viene junto con el compilador `gcc/g++`, su equivalente en el compilador `clang` es `llvm-cov gcov`. Una vez hecho esto, ejecutar el comando
```bash
$ gcovr
```
En la raíz del proyecto lo que generará un archivo `coverage.html` en la carpeta `build` con los detalles de coverage en una página web.


Por conveniencia se dejan los scripts `coverage.sh` y `coverage.ps1` que al ejecutarse, según el sistema operativo que corresponda, correran los comandos necesarios de `cmake`, `ctest` y `gcovr`. \
Notar que este script asume que las variables de entorno ya están configuradas correctamente.