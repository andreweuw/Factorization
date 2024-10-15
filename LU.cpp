#include "LU.h"
#include <iostream>

LU::LU(const Matrix& a)
	: mL(a.dimensions().first, a.dimensions().second),
	  mU(a)
{
	decompose();
}

void LU::decompose()
{
	const auto [rows, cols] = mU.dimensions();
	mL = Matrix::identity(rows);

	for (size_t k = 0; k < rows - 1; k++)
	{
		const double pivot = mU(k, k);
		if (pivot == 0.0)
		{
			std::cout << "Zero pivot, aborting.\n";
			break;
		}
		// These updating of rows can be parallelized 
		for (size_t j = k + 1; j < rows; j++)
		{
			const double factor = mU(j, k) / pivot;
			mL(j, k) = factor;
			for (size_t i = 0; i < cols; i++)
				mU(j, i) -= mU(k, i) * factor;
		}
	}
}

std::vector<double> LU::solve(const std::vector<double>& b) const
{
	const size_t bSize = b.size();
	std::vector<double> x(bSize, 0);
	std::vector<double> y(bSize, 0);

	// L y = b, solve for y:
	for (size_t i = 0; i < bSize; i++)
	{
		double ithY = b[i];
		for (size_t j = 0; j < i; j++)
			ithY -= mL(i, j) * y[j];
		
		y[i] = ithY;
	}

	// U x = y, solve for x:
	// Convert the size to signed type because indexes can be negative
	const std::ptrdiff_t bSizeIntType = static_cast<std::ptrdiff_t>(bSize);
	for (std::ptrdiff_t i = bSizeIntType - 1; i >= 0; i--)
	{
		double ithX = y[i];
		for (std::ptrdiff_t j = bSizeIntType - 1; j > i; j--)
			ithX -= mU(i, j) * x[j];
		x[i] = ithX / mU(i, i);
	}

	return x;
}

double LU::determinant() const 
{
	std::cout << "LU\n " << mU << std::endl;
	// det(A) = det(L)det(U), det(L) = 1
	double determinant = 1;
	const size_t size = mU.dimensions().first;
	for (size_t i = 0; i < size; i++)
		determinant *= mU(i, i);
	return determinant;
}