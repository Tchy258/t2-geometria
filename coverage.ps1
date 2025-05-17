cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug
cmake --build build/debug
ctest --test-dir .\build\debug\test
.\build\debug\src\Tarea1.exe
gcovr
Write-Output "Opening coverage results in default browser"
.\build\coverage.html