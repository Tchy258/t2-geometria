add_executable(IntegerAtLeastThreeColinearTest integer_at_least_three_colinear_test.cpp)
target_link_libraries(IntegerAtLeastThreeColinearTest PRIVATE divide_and_conquer_strategy gift_wrapping_strategy hull_tester)

add_executable(LLAtLeastThreeColinearTest ll_at_least_three_colinear_test.cpp)
target_link_libraries(LLAtLeastThreeColinearTest PRIVATE divide_and_conquer_strategy gift_wrapping_strategy hull_tester)

add_executable(DoubleAtLeastThreeColinearTest double_at_least_three_colinear_test.cpp)
target_link_libraries(DoubleAtLeastThreeColinearTest PRIVATE divide_and_conquer_strategy gift_wrapping_strategy hull_tester)

add_executable(FloatAtLeastThreeColinearTest float_at_least_three_colinear_test.cpp)
target_link_libraries(FloatAtLeastThreeColinearTest PRIVATE divide_and_conquer_strategy gift_wrapping_strategy hull_tester)
