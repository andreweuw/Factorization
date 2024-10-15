#pragma once
#include "Matrix.h"
#include <vector>

class LU
{
private:
    Matrix mL, mU;

    void decompose();

public:
    explicit LU(const Matrix& a);

    [[nodiscard]] std::vector<double> solve(const std::vector<double>& b) const;

    [[nodiscard]] double determinant() const;
};

