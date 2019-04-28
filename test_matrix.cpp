
#define BOOST_TEST_MODULE test_module
#include <boost/test/unit_test.hpp>
#include "infinity_matrix.h"

BOOST_AUTO_TEST_SUITE(matrix_test_suite)

    BOOST_AUTO_TEST_CASE(correct_value_contain_test_0)
    {
        Matrix<int, 0> m;
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
        Matrix<int, 0> m;
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
                    BOOST_CHECK(m[i][j] == 0);
            }
        }
    }

    BOOST_AUTO_TEST_CASE(correct_matrix_size_0)
    {
        Matrix<int, -1> m;
        const size_t range = 25;
        for(size_t i = 0; i < range; i++)
            m[i][i] = 3*i;

        BOOST_CHECK(m.get_size() == range);
    }

    BOOST_AUTO_TEST_CASE(correct_matrix_size_1)
    {
        Matrix<int, -1> m;
        const size_t range = 25;
        for(size_t i = 0; i < range; i++)
            m[i][i] = 3*i;

        for(size_t i = 0; i < range; i++)
            m[i][i] = -1;

        BOOST_CHECK(m.get_size() == 0);
    }

    BOOST_AUTO_TEST_CASE(object_copying_test_0)
    {
        Matrix<int, -1> m;

        m[0][0] = 10;
        m[1][1] = 20;

        Matrix<int, -1> m2(m);

        BOOST_CHECK(m[0][0] == m2[0][0]);
        BOOST_CHECK(m[1][1] == m2[1][1]);

        m[0][0] = 100;
        m[1][1] = 200;

        BOOST_CHECK(m[0][0] != m2[0][0]);
        BOOST_CHECK(m[1][1] != m2[1][1]);

    }

    BOOST_AUTO_TEST_CASE(object_copying_test_1)
    {
        Matrix<int, -1> m;

        m[0][0] = 10;
        m[1][1] = 20;

        Matrix<int, -1> m2;
        m2 = m;

        BOOST_CHECK(m[0][0] == m2[0][0]);
        BOOST_CHECK(m[1][1] == m2[1][1]);

        m[0][0] = 100;
        m[1][1] = 200;

        BOOST_CHECK(m[0][0] != m2[0][0]);
        BOOST_CHECK(m[1][1] != m2[1][1]);
    }

    BOOST_AUTO_TEST_CASE(object_moving_test_0)
    {
        Matrix<int, -1> m;

        m[0][0] = 10;
        m[1][1] = 20;

        Matrix<int, -1> m2(std::move(m));

        BOOST_CHECK(m2[0][0] == 10);
        BOOST_CHECK(m2[1][1] == 20);
        m2[1][1] = 20;
    }

    BOOST_AUTO_TEST_CASE(object_moving_test_1)
    {
        Matrix<int, -1> m;

        m[0][0] = 10;
        m[1][1] = 20;

        Matrix<int, -1> m2;
        m2 = std::move(m);

        BOOST_CHECK(m2[0][0] == 10);
        BOOST_CHECK(m2[1][1] == 20);
        m2[1][1] = 20;
    }



BOOST_AUTO_TEST_SUITE_END()
