#pragma once
#include "Matrix.h"
#include <vector>

class LU
{
private:
    Matrix mL, mU;

    void decompose();

public:
    LU(const Matrix& A);

    std::vector<double> solve(const std::vector<double>& b) const;

    double determinant() const;
};

