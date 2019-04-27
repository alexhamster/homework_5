#include <iostream>
#include "infinity_matrix.h"
#include <vector>

int main()
{

    Matrix m;

    std::cout << m[10][10] << std::endl;
    m[10][10] = 10;
    m[10][11] = 20;
    std::cout << m[10][11] << std::endl;



    std::cout << "Hello, World!" << std::endl;
    return 0;
}