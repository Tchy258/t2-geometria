set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_library(punto STATIC punto.cpp)
target_include_directories(punto PUBLIC ${PROJECT_INCLUDE_DIR})

add_library(vector STATIC vector.cpp)
target_include_directories(vector PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(vector PUBLIC punto)

add_library(poligono STATIC poligono.cpp)
target_include_directories(poligono PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(poligono PUBLIC vector)

add_library(gift_wrapping_strategy STATIC gift_wrapping_strategy.cpp)
target_include_directories(gift_wrapping_strategy PUBLIC ${PROJECT_INCLUDE_DIR})
target_link_libraries(gift_wrapping_strategy PUBLIC poligono)

add_executable(Tarea2 main.cpp)
target_link_libraries(Tarea2 PRIVATE poligono)

add_subdirectory(generators)

add_library(hull_tester STATIC hull_tester.cpp)
target_include_directories(hull_tester PUBLIC ${PROJECT_INCLUDE_DIR})
target_include_directories(hull_tester PUBLIC ${PROJECT_INCLUDE_DIR}/generators)
target_link_libraries(hull_tester PUBLIC poligono at_least_three_colinear_points_strategy non_colinear_points_strategy completely_random_points_strategy hull_percentage_strategy)

add_executable(IntegerHullTest integer_hull_test.cpp)
target_link_libraries(IntegerHullTest PRIVATE gift_wrapping_strategy hull_tester)

add_executable(LLHullTest ll_hull_test.cpp)
target_link_libraries(LLHullTest PRIVATE gift_wrapping_strategy hull_tester)

add_executable(DoubleHullTest double_hull_test.cpp)
target_link_libraries(DoubleHullTest PRIVATE gift_wrapping_strategy hull_tester)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(punto PRIVATE --coverage)
    target_link_options(punto PRIVATE --coverage)
    target_compile_options(vector PRIVATE --coverage)
    target_link_options(vector PRIVATE --coverage)
    target_compile_options(poligono PRIVATE --coverage)
    target_link_options(poligono PRIVATE --coverage)
    target_compile_options(gift_wrapping_strategy PRIVATE --coverage)
    target_link_options(gift_wrapping_strategy PRIVATE --coverage)
    target_compile_options(hull_tester PRIVATE --coverage)
    target_link_options(hull_tester PRIVATE --coverage)
    target_compile_options(Tarea2 PRIVATE --coverage)
    target_link_options(Tarea2 PRIVATE --coverage)
    target_compile_options(IntegerHullTest PRIVATE --coverage)
    target_link_options(IntegerHullTest PRIVATE --coverage)
    target_compile_options(LLHullTest PRIVATE --coverage)
    target_link_options(LLHullTest PRIVATE --coverage)
    target_compile_options(DoubleHullTest PRIVATE --coverage)
    target_link_options(DoubleHullTest PRIVATE --coverage)
endif()