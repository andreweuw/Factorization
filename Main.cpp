#include <iostream>

#include "EigenDecomposition.h"
#include "Matrix.h"
#include "LU.h"

static void test(const Matrix& m, const std::vector<double>& y) {
    std::cout << m << std::endl;

    const LU lu(m);
    const auto x = lu.solve(y);
    std::cout << "X: ";
    for (size_t i = 0; i < m.dimensions().first; i++) {
        std::cout << x[i] << " ";
    }
    std::cout << '\n';

    std::cout << "Determinant by raw computation/Leibniz: " << m.determinant() << '\n';
    auto eigen = EigenDecomposition(m);
}

int main()
{
     test(Matrix({ {1,1}, {2, 1} }), { 4,-6 });
     /*std::cout << "-------------------------------\n";
     test(Matrix({ {1,1,-1},{1,-2,3},{2,3,3} }), { 4,-6, 7 });*/
     //std::cout << "-------------------------------\n";
     //test(Matrix({ {1,1,-1, 5},{1,-2,3, 3},{2,3,3, 5} ,{2,3,3, -1} }), { 4,-6, 7,1 });
};
