add_executable(IntegerNonColinearTest integer_non_colinear_test.cpp)
target_link_libraries(IntegerNonColinearTest PRIVATE divide_and_conquer_strategy gift_wrapping_strategy hull_tester)

add_executable(LLNonColinearTest ll_non_colinear_test.cpp)
target_link_libraries(LLNonColinearTest PRIVATE divide_and_conquer_strategy gift_wrapping_strategy hull_tester)

add_executable(DoubleNonColinearTest double_non_colinear_test.cpp)
target_link_libraries(DoubleNonColinearTest PRIVATE divide_and_conquer_strategy gift_wrapping_strategy hull_tester)

add_executable(FloatNonColinearTest float_non_colinear_test.cpp)
target_link_libraries(FloatNonColinearTest PRIVATE divide_and_conquer_strategy gift_wrapping_strategy hull_tester)
