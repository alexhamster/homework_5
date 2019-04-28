cmake_minimum_required(VERSION 3.5)
project(homework_5)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(homework_5 main.cpp infinity_matrix.h)

add_executable(test_matrix test_matrix.cpp)

set_target_properties(test_matrix PROPERTIES
         COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

target_link_libraries(test_matrix
        ${Boost_LIBRARIES}
        )

enable_testing()

add_test(ipt test_matrix)