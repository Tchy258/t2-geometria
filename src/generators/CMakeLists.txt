add_library(at_least_three_colinear_points_strategy at_least_three_colinear_points_strategy.cpp)
target_include_directories(at_least_three_colinear_points_strategy PUBLIC ${PROJECT_INCLUDE_DIR}/generators)
target_include_directories(at_least_three_colinear_points_strategy PUBLIC ${PROJECT_INCLUDE_DIR})

add_library(non_colinear_points_strategy non_colinear_points_strategy.cpp)
target_include_directories(non_colinear_points_strategy PUBLIC ${PROJECT_INCLUDE_DIR}/generators)
target_include_directories(non_colinear_points_strategy PUBLIC ${PROJECT_INCLUDE_DIR})

add_library(completely_random_points_strategy completely_random_points_strategy.cpp)
target_include_directories(completely_random_points_strategy PUBLIC ${PROJECT_INCLUDE_DIR}/generators)
target_include_directories(completely_random_points_strategy PUBLIC ${PROJECT_INCLUDE_DIR})

add_library(hull_percentage_strategy hull_percentage_strategy.cpp)
target_include_directories(hull_percentage_strategy PUBLIC ${PROJECT_INCLUDE_DIR}/generators)
target_include_directories(hull_percentage_strategy PUBLIC ${PROJECT_INCLUDE_DIR})
