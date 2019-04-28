
#define BOOST_TEST_MODULE test_module
#include <boost/test/unit_test.hpp>
#include "infinity_matrix.h"

#define MATRIX_DEFAULT_VALUE -1

BOOST_AUTO_TEST_SUITE(matrix_test_suite)

    BOOST_AUTO_TEST_CASE(correct_value_contain_test_0)
    {
        Matrix<int, -1> m;
        const size_t range = 100;
        for(size_t i = 0; i < range; i++)
        {
            for(size_t j = 0; j < range; j++)
                m[i][j] = i*j;
        }

        for(size_t i = 0; i < range; i++)
        {
            for(size_t j = 0; j < range; j++)
                BOOST_CHECK(m[i][j] == i*j);
        }

    }

    BOOST_AUTO_TEST_CASE(correct_value_contain_test_1)
    {
        Matrix<int, -1> m;
        const size_t range = 25;
        for(size_t i = 0; i < range; i++)
                m[i][i] = 3*i;

        for(size_t i = 0; i < range; i++)
            m[i][i] = i*i;

        for(size_t i = 0; i < range; i++)
        {
            for(size_t j = 0; j < range; j++)
            {
                if(i == j)
                    BOOST_CHECK(m[i][j] == i*i);
                else
                    BOOST_CHECK(m[i][j] == MATRIX_DEFAULT_VALUE);
            }
        }
    }

    BOOST_AUTO_TEST_CASE(correct_matrix_size_0)
    {
        Matrix<int, -1> m;
        const size_t range = 25;
        for(size_t i = 0; i < range; i++)
            m[i][i] = 3*i;

        m[0][0]; // need to trigger transfer from buffer to matrix
        BOOST_CHECK(m.get_size() == range);
    }

    BOOST_AUTO_TEST_CASE(correct_matrix_size_1)
    {
        Matrix<int, -1> m;
        const size_t range = 25;
        for(size_t i = 0; i < range; i++)
            m[i][i] = 3*i;

        for(size_t i = 0; i < range; i++)
            m[i][i] = MATRIX_DEFAULT_VALUE;

        m[0][0]; // need to trigger transfer from buffer to matrix
        BOOST_CHECK(m.get_size() == 0);
    }

BOOST_AUTO_TEST_SUITE_END()
