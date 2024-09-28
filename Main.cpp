#include <iostream>

#include "Matrix.h"
#include "LU.h"

static void test(Matrix m, const std::vector<double> y) {
    std::cout << m << std::endl;

    LU lu(m);
    auto x = lu.solve(y);
    std::cout << "X: ";
    for (size_t i = 0; i < m.dimensions().first; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Determinant by LU decomposition: " << lu.determinant() << std::endl;
    std::cout << "Determinant by raw computation/Leibniz: " << m.determinant() << std::endl;
}

int main()
{
     test(Matrix({ {3,3}, {12, 18} }), { 4,-6 });
     test(Matrix({ {1,1,-1},{1,-2,3},{2,3,3} }), { 4,-6, 7 });
};
