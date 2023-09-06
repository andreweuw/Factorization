#include <iostream>

#include "Matrix.h"
#include "LU.h"

int main()
{
    // Matrix m({ {1.0, 2.0, 3.0}, {4.0, 5, 6}, {7, 8, 10} });
    // Matrix m({ {3,3}, {12, 18} });
    // Matrix m({ {-1,0, 3}, {-2, -2, 7}, {-5, 0, 20} });
    Matrix m({ {1,1,-1},{1,-2,3},{2,3,1} });
    std::cout << m << std::endl;


    LU lu(m);
    auto x = lu.solve({ 4,-6,7 });


    std::cout << "X:" << x[0] << "," << x[1] << "," << x[2] << std::endl;
    std::cout << "Determinant: " << lu.determinant() << std::endl;
};