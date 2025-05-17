#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug
cmake --build build/debug
ctest --test-dir ./build/debug/test
chmod +x ./build/debug/src/Tarea1
./build/debug/src/Tarea1
gcovr

if [ -n "$DISPLAY" ] || [ -n "$WAYLAND_DISPLAY" ] || [[ "$XDG_SESSION_TYPE" == "x11" || "$XDG_SESSION_TYPE" == "wayland" ]]; then
    echo "Graphical session detected."
    if which xdg-open > /dev/null 2>&1; then
        echo "Opening results on default browser"
        xdg-open ./build/coverage.html
    else
        echo "xdg-open is not installed, please manually open ./build/coverage.html"
    fi
else
    echo "TTY or non-graphical session detected. Coverage details available on ./build/coverage.html"
fi

