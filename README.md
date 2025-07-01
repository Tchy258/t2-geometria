# Tarea 2 y 3 Geometría Computacional

Este código corresponde a la Tarea 2 y 3 - Cerradura Convexa de Nicolás Escobar Zarzar alumno del curso CC5502 Geometría Computacional del semestre otoño 2025.
Esta tarea consiste en programar dos algoritmos de cerradura convexa haciendo uso de las clases hechas en la Tarea 1, los algoritmos a implementar son GiftWrapping y Divide and Conquer. Esto se hace mediante la implementación del patrón de diseño _strategy_ usando la clase `ConvexHullStrategy` como base. También se pide diseñar un experimento para determinar para que distribuciones de punto es mejor usar uno u otro, junto con un método que genere una lista aleatoria de n puntos y otro que genere un conjunto de puntos en que un cierto porcentaje de estos forme parte de la cerradura convexa y el resto se distribuya aleatoriamente en el interior, también usando el patrón strategy con la clase `PointGenerationStrategy`.
Fue desarrollada usando Visual Studio Code en Windows usndo [MSYS2](https://www.msys2.org/), pero a continuación se dan las instrucciones para su compilación y ejecución en cualquier entorno de escritorio (Windows, Linux, MacOS).
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
Para compilar este código se necesita CMake 3.31, este se puede descargar desde [la página de CMake](https://cmake.org/download/) o mediante el gestor de paquetes (no se recomienda, pues no se puede asegurar la versión correcta de CMake).\
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
Esto generará las librerías estáticas en `build/release/src` con los nombres `libpunto`, `libvector` y `libpoligono` con la extensión que corresponda y también el archivo
`Tarea2.exe`.También compilará los tests de la tarea anterior.

Adicionalmente se crearan multiples ejecutables en `build/release/src/performance_testers` y sus subcarpetas, los cuales ejecutan los algortimos para formar la cerradura convexa con distintos tipos de datos (`int`, `long long`, `float` y `double`)

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

## Ejecución de pruebas

Para probar los algoritmos de cerradura convexa, se dispone de los ejecutables en las subcarpetas de `build/src/performance_testers` y sus subcarpetas, cada uno de estos corresponde a distintos tipos de datos (`int`, `float`, `double`, `long long`) y a distintas formas de generar un conjunto de puntos para probar los algoritmos:
- `outer_circle`: Estos ejecutables generan un conjunto de puntos delimitados por un círculo, esto se hace para controlar la cantidad de puntos que formarán parte de la cerradura convexa. Uno de estos ejecutables se puede ejectuar de la siguiente manera
```bash
$ ./LLHullTest.exe <veces> <porcentaje en la cerradura> [<cantidad de puntos colineales>] [semilla] [path de salida]
```
Donde `veces` es la cantidad de veces que los algoritmos se deben correr sobre un conjunto (distinto) de tamaño fijo, los tamaños están fijos en 10000, 100000 y 1000000 como solicita el enunciado, `porcentaje en la cerradura` es un valor entre 0.0 y 1.0 que determina el porcentaje de puntos que forman parte del círculo que será la cerradura convexa (o un subconjunto de ella en caso de tener puntos colineales), `cantidad de puntos colineales`, como dice su nombre, es la cantidad de puntos colineales deseada que formarán parte del círculo, por defecto se asume que no hay colineales, `semilla` es la semilla que utilizará el generador de números aleatorios para generar el conjunto de puntos, por defecto la semilla es 123, finalmente `path de salida` es una ruta (ya sea absoluta o relativa) a un archivo en el cual se escribirán los tiempos de ejecución en formato csv.

- `random_points`: Estos ejecutables generan conjuntos de puntos totalmente aleatorios con la sola restricción de tener un valor mínimo y máximo según el tipo de dato. Estos se pueden ejecutar de la forma siguiente
```bash
$ ./LLRandomTest.exe <veces> [semilla] [path de salida]
```
Donde los parámetros `veces`, `semilla` y `path de salida` significan lo mismo que para `outer_circle`

- `random_points/at_least_three_colinear`: Estos ejecutables son similares al anterior, pero aseguran de que habrá al menos 3 puntos colineales en el conjunto de puntos, ya sea como parte de la cerradura o no. Se ejecutan de la misma manera que `random_points`.

- `random_points/non_colinear`: Lo opuesto del anterior, este asegura que no habrá ningún trio de puntos colineales en el conjunto de puntos. Se ejecutan de la misma manera que `random_points`.


Para facilitar la ejecución de estas prueba se dispone de los scripts `run_benchmarks_windows.py` y `run_benchmarks_unix.py` que requieren Python3.11+ y se encargan de correr los algoritmos según la plataforma correspondiente asumiendo que el código ya fue compilado. Estos scripts correran por cada tipo de dato, 5 veces los algoritmos, con porcentajes en la cerradura (si corresponde) de 0.01%, 0.1%, 10%, 30%, 50%, 70% y 100%, con cantidad de puntos colineales (si correponde) de 0, 3 y 10 y con la semilla por defecto 123. Luego guardará los resultados en el directorio actual con el formato `<nombre_del_ejecutable>_<porcentaje_en_la_cerradura>_<colineales>.csv`

## Análisis de datos
En el archivo [convex_hull_analysis.ipynb](convex_hull_analysis.ipynb) se encuentra el código que recolecta toda la información de los archivos csv generados por el script anterior (esperando que estén en una carpeta llamada `data`), los grafica bajo distintos criterios y los guarda en formato svg.
El archivo ANALISIS.pdf contiene un análisis más profundo y detalles de la implementación.
Notar que antes de ejecutar este jupyter notebook es necesario incializar un entorno virtual e instalar las dependencias presentes en `requirements.txt` con los comandos
```bash
$ python -m venv env
$ source ./env/bin/activate # En windows esto es simplemente ./env/Scripts/Activate.ps1
$ pip install -r requirements.txt
```