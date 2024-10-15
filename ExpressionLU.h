#pragma once
#include "ExpressionMatrix.h"

class ExpressionLU
{
private:
    ExpressionMatrix mL, mU;

    void decompose();

public:
    explicit ExpressionLU(const ExpressionMatrix& a);

    //[[nodiscard]] std::vector<double> solve(const std::vector<double>& b) const;

    [[nodiscard]] std::string determinant() const;
};

