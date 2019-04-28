#include <iostream>
#include <vector>


#include "infinity_matrix.h"
int main()
{

    Matrix m;

    m[10][10] = 10;
    m[10][11] = 20;

    Matrix m2;
    m2 = m;
    std::cout << m2[10][10] << std::endl;
    std::cout << m2[10][11] << std::endl;

    m[10][11] = 1000000;

    std::cout << m2[10][11] << std::endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}