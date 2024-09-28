#pragma once
#include <vector>
#include <ostream>

class Matrix
{
private:
	std::vector<std::vector<double>> mData;
	size_t mRows;
	size_t mCols;

public:
	Matrix(size_t rows, size_t cols);
	Matrix(const std::vector<std::vector<double>>& data);
	Matrix(const Matrix& other);
	static Matrix identity(size_t dimension);
	std::pair<size_t, size_t> dimensions() const;
	double determinant() const;

	Matrix operator*(const Matrix& other);
	Matrix& operator*=(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	double& operator()(size_t row, size_t col);
	const double& operator()(size_t row, size_t col) const;
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
	bool operator==(const Matrix& other) const;
};