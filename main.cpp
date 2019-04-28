#include <iostream>
#include <vector>


#include "infinity_matrix.h"

int main()
{
    try 
    {
        Matrix<int, 0> m;

        for (size_t i = 0; i < 10; i++)
            m[i][i] = i;

        for (size_t i = 0; i < 10; i++)
            m[9 - i][i] = i;
        
        for (size_t i = 1; i < 9; i++) {
            for (size_t j = 1; j < 9; j++)
                std::cout << m[i][j] << " ";
            std::cout << std::endl;
        }

        std::cout << "Num of busy: " << m.get_size() << std::endl;
        m.print_elements();
    }
    catch (...)
    {
        std::cout << "Unknown error" << std::endl;
    }
    
    return 0;
}