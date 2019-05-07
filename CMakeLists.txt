cmake_minimum_required(VERSION 3.5)

project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(matrix main.cpp infinity_matrix.h)

add_executable(test_matrix test_matrix.cpp)

set_target_properties(matrix test_matrix PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

set_target_properties(test_matrix PROPERTIES
         COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

target_link_libraries(test_matrix
        ${Boost_LIBRARIES}
        )

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT soliaris2012@mail.ru)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(ipt test_matrix)