#pragma once
#include <string>
#include <vector>
#include "Matrix.h"

class ExpressionMatrix
{
	std::vector<std::vector<std::string>> mData;
	size_t mRows;
	size_t mCols;

public:
	ExpressionMatrix() = default;
	ExpressionMatrix(size_t rows, size_t cols);
	explicit ExpressionMatrix(const std::vector<std::vector<std::string>>& data);
	ExpressionMatrix(const ExpressionMatrix& other);
	ExpressionMatrix(const Matrix& other);


	std::string determinant() const;

	std::string& operator()(size_t row, size_t col);
	const std::string& operator()(size_t row, size_t col) const;
	friend std::ostream& operator<<(std::ostream&, const ExpressionMatrix&);
	bool operator==(const Matrix& other) const;
	std::pair<size_t, size_t> dimensions() const;
	static ExpressionMatrix eye(size_t dimension, const std::string& value);

	ExpressionMatrix operator-(const ExpressionMatrix& other) const;
	ExpressionMatrix& operator-=(const ExpressionMatrix& other);

	ExpressionMatrix operator*(const ExpressionMatrix& other) const;
	ExpressionMatrix& operator*=(const ExpressionMatrix& other);
};

