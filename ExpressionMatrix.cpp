#include "ExpressionMatrix.h"

#include <cassert>
#include <format>
#include <iostream>

#include "LU.h"
#include "ExpressionLU.h"

ExpressionMatrix::ExpressionMatrix(size_t rows, size_t cols) : mRows(rows), mCols(cols)
{
    assert(mRows > 0 && "Number of rows should be greater than zero.");
    assert(mCols > 0 && "Number of columns should be greater than zero.");

    // Create a vector of vectors and initialize all elements to zero
    mData = std::vector(mRows, std::vector(mCols, std::string("0")));
}

std::string ExpressionMatrix::determinant() const
{
    assert(mRows == mCols && "Determinant can only be computed for square matrix.");

    const ExpressionLU lu(*this);
    return lu.determinant();
}
ExpressionMatrix::ExpressionMatrix(const ExpressionMatrix& other) : mData(other.mData), mRows(other.mRows), mCols(other.mCols)
{
    std::cout << "Copy constructor \n";
}

ExpressionMatrix::ExpressionMatrix(const Matrix& other) : ExpressionMatrix(other.dimensions().first, other.dimensions().second)
{
    for (size_t i = 0; i < mRows; ++i)
        for (size_t j = 0; j < mCols; ++j)
            this->mData[i][j] = std::format("{:.1f}", other(i, j));// std::to_string(other(i, j));
}

ExpressionMatrix::ExpressionMatrix(const std::vector<std::vector<std::string>>& data) : mData(data), mRows(data.size()), mCols(data[0].size())
{
    assert(mRows > 0 && "Number of rows should be greater than zero.");
    mCols = data[0].size();

    // Check if all rows have the same number of columns
    for (const auto& row : data)
        assert(row.size() == mCols && "All rows must have the same number of columns.");
}

std::string& ExpressionMatrix::operator()(const size_t row, const size_t col)
{
    return mData[row][col];
}

const std::string& ExpressionMatrix::operator()(const size_t row, const size_t col) const
{
    return mData[row][col];
}

std::ostream& operator<<(std::ostream& os, const ExpressionMatrix& m)
{
    for (size_t i = 0; i < m.mRows; ++i) {
        os << m(i, 0);
        for (size_t j = 1; j < m.mCols; ++j)
            os << ";" << m(i, j);
        os << ";;\n";
    }
    return os;
}

std::pair<size_t, size_t> ExpressionMatrix::dimensions() const
{
    return { mRows, mCols };
}

ExpressionMatrix ExpressionMatrix::eye(const size_t dimension, const std::string& value)
{
    ExpressionMatrix identity(dimension, dimension);
    for (size_t i = 0; i < dimension; i++)
        identity(i, i) = value;
    return identity;
}


ExpressionMatrix ExpressionMatrix::operator-(const ExpressionMatrix& other) const
{
    const auto thisDimensions = this->dimensions();
    const auto otherDimensions = other.dimensions();
    std::cout << "Subbing " << thisDimensions.first << "X" << thisDimensions.second << " to " << otherDimensions.first << "X" << otherDimensions.second << '\n';

    ExpressionMatrix added(*this);
    for (size_t i = 0; i < added.mRows; ++i)
        for (size_t j = 0; j < added.mCols; ++j)
            if (other(i, j) != "0")
				added(i, j) += " - " + other(i, j);
    return added;
}

ExpressionMatrix& ExpressionMatrix::operator-=(const ExpressionMatrix& other)
{
    return *this = this->operator-(other);
}

ExpressionMatrix ExpressionMatrix::operator*(const ExpressionMatrix& other) const
{
    const auto thisDimensions = this->dimensions();
    const auto otherDimensions = other.dimensions();
    std::cout << "Multiply " << thisDimensions.first << "X" << thisDimensions.second << " by " << otherDimensions.first << "X" << otherDimensions.second << '\n';
    assert(thisDimensions.second == otherDimensions.first && "The columns of first matrix have to be the same as rows of the right one.");

    ExpressionMatrix multiplied(thisDimensions.first, otherDimensions.second);
    for (size_t i = 0; i < multiplied.mRows; ++i)
        for (size_t j = 0; j < multiplied.mCols; ++j)
            for (size_t k = 0; k < mCols; ++k)
                multiplied(i, j) = "(" + multiplied(i, j) + " + " + this->mData[i][k] + " * " + other(k, j) + ")";
    return multiplied;
}

ExpressionMatrix& ExpressionMatrix::operator*=(const ExpressionMatrix& other)
{
    return *this = this->operator*(other);
}