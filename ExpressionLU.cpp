#include "ExpressionLU.h"
#include <iostream>


ExpressionLU::ExpressionLU(const ExpressionMatrix& a)
	: mL(a.dimensions().first, a.dimensions().second),
	mU(a)
{
	decompose();
}

void ExpressionLU::decompose()
{
	const auto [rows, cols] = mU.dimensions();
	mL = ExpressionMatrix(Matrix::identity(rows));

	for (size_t k = 0; k < rows - 1; k++)
	{
		const std::string pivot = mU(k, k);
		if (pivot == "0.0")
		{
			std::cout << "Zero pivot, aborting.\n";
			break;
		}
		// These updating of rows can be parallelized 
		for (size_t j = k + 1; j < rows; j++)
		{
			const std::string factor = "(("+ mU(j, k) + ") / (" + pivot + "))";
			mL(j, k) = factor;
			for (size_t i = 0; i < cols; i++)
				mU(j, i) = "(" + mU(j, i) + " - ((" + mU(k, i) + ") * " + factor + "))";
		}
	}
}

std::string ExpressionLU::determinant() const
{
	std::cout << "LU\n " << mU << std::endl;
	// det(A) = det(L)det(U), det(L) = 1
	std::string determinant = "1";
	const size_t size = mU.dimensions().first;
	for (size_t i = 0; i < size; i++)
		determinant += " * (" + mU(i, i) + ")";
	return determinant;
}