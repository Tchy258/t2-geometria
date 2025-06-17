include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
  punto_test
  punto_test.cc
)
target_include_directories(
  punto_test
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(
  punto_test
  PRIVATE
  punto
  GTest::gtest_main
)

add_executable(
  vector_test
  vector_test.cc
)
target_include_directories(
  vector_test
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(
  vector_test
  PRIVATE
  vector
  GTest::gtest_main
)


add_executable(
  poligono_test
  poligono_test.cc
)
target_include_directories(
  poligono_test
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(
  poligono_test
  PRIVATE
  poligono
  GTest::gtest_main
)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")

  target_compile_options(
    punto_test
    PRIVATE
    --coverage
  )

  target_link_options(
    punto_test
    PRIVATE
    --coverage
  )

  target_compile_options(
    vector_test
    PRIVATE
    --coverage
  )

  target_link_options(
    vector_test
    PRIVATE
    --coverage
  )

  target_compile_options(
    poligono_test
    PRIVATE
    --coverage
  )
  target_link_options(
    poligono_test
    PRIVATE
    --coverage
  )
endif()

include(GoogleTest)
gtest_discover_tests(punto_test)
gtest_discover_tests(vector_test)
gtest_discover_tests(poligono_test)
