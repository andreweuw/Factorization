#include "Matrix.h"
#include <cassert>
#include <iostream>
#include "LU.h"

using std::ostream;

Matrix::Matrix(const size_t rows, const size_t cols) : mRows(rows), mCols(cols)
{
    assert(mRows > 0 && "Number of rows should be greater than zero.");
    assert(mCols > 0 && "Number of columns should be greater than zero.");

    // Create a vector of vectors and initialize all elements to zero
    mData = std::vector(mRows, std::vector(mCols, 0.0));
}

Matrix::Matrix(const Matrix& other) : mData(other.mData), mRows(other.mRows), mCols(other.mCols)
{
    std::cout << "Copy constructor \n";
}

Matrix::Matrix(const std::vector<std::vector<double>>& data) : mData(data), mRows(data.size()), mCols(data[0].size()) 
{
    assert(mRows > 0 && "Number of rows should be greater than zero.");
    mCols = data[0].size();

    // Check if all rows have the same number of columns
    for (const auto& row : data)
        assert(row.size() == mCols && "All rows must have the same number of columns.");
}

Matrix Matrix::identity(const size_t dimension)
{
    Matrix identity(dimension, dimension);
    for (size_t i = 0; i < dimension; i++)
        identity(i,i) = 1.0;
    return identity;
}

double Matrix::determinant() const
{
    if (mRows != mCols) {
        std::cout << "Determinant can only be computed for square matrix.";
        return std::numeric_limits<double>::max();
    }

    const LU lu(*this);
    return lu.determinant();
    if (mRows <= 3) {
        // This is terrible and useless but was a nice exercise
        // of course, writing the terms out explicitly would be a lot better.
        double determinant = 0;    
        // walk +1 +1 through the matrix
        int count = mRows == 2 ? 1 : 0;
        int i = 0, j = 0;
        while (count++ < mCols) {
            double tmp = 1;
            for (size_t countInner = 0; countInner < mCols; ++countInner)
                tmp *= mData[i++][j++ % mCols];
            i = 0;
            j = count;
            determinant += tmp;
        }

        j = mCols - 1;
        count = mRows == 2 ? 1 : 0;
        while (count++ < mCols) {
            double tmp = 1;
            size_t countInner = 0;
            while (countInner++ < mCols) {
                tmp *= mData [i++][j--];
                if (j == -1)
                    j = mRows - 1;
            }
            i = 0;
            j = mCols - count - 1;
            determinant -= tmp;
        }

        return determinant;
    }

}

Matrix Matrix::operator*(const Matrix& other) const
{
	const auto thisDimensions = this->dimensions();
	const auto otherDimensions = other.dimensions();
    std::cout << "Multiply " << thisDimensions.first << "X" << thisDimensions.second << " by " << otherDimensions.first << "X" << otherDimensions.second << '\n';
    assert(thisDimensions.second == otherDimensions.first && "The columns of first matrix have to be the same as rows of the right one.");

    Matrix multiplied(thisDimensions.first, otherDimensions.second);
    for (size_t i = 0; i < multiplied.mRows; ++i)
        for (size_t j = 0; j < multiplied.mCols; ++j)
            for (size_t k = 0; k < mCols; ++k)
                 multiplied(i,j) += this->mData[i][k] * other(k,j);
    return multiplied;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    return *this = this->operator*(other);
}

Matrix Matrix::operator+(const Matrix& other) const
{
    const auto thisDimensions = this->dimensions();
    const auto otherDimensions = other.dimensions();
    std::cout << "Adding " << thisDimensions.first << "X" << thisDimensions.second << " to " << otherDimensions.first << "X" << otherDimensions.second << '\n';

    Matrix added(*this);
    for (size_t i = 0; i < added.mRows; ++i)
        for (size_t j = 0; j < added.mCols; ++j)
            added(i,j) += other(i,j);
    return added;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    return *this = this->operator+(other);
}

Matrix Matrix::operator-(const Matrix& other) const
{
    const auto thisDimensions = this->dimensions();
    const auto otherDimensions = other.dimensions();
    std::cout << "Subbing " << thisDimensions.first << "X" << thisDimensions.second << " to " << otherDimensions.first << "X" << otherDimensions.second << '\n';

    Matrix added(*this);
    for (size_t i = 0; i < added.mRows; ++i)
        for (size_t j = 0; j < added.mCols; ++j)
            added(i,j) -= other(i,j);
    return added;
}

Matrix& Matrix::operator-=(const Matrix& other)
{
    return *this = this->operator-(other);
}

std::pair<size_t, size_t> Matrix::dimensions() const
{
    return { mRows, mCols };
}

bool Matrix::operator==(const Matrix& other) const
{
    return mData == other.mData && mRows == other.mRows && mCols == other.mCols;
}

double& Matrix::operator()(const size_t row, const size_t col)
{
    return mData[row][col];
}

const double& Matrix::operator()(const size_t row, const size_t col) const
{
    return mData[row][col];
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (size_t i = 0; i < m.mRows; ++i) {
        os << m(i,0);
        for (size_t j = 1; j < m.mCols; ++j)
            os << " " << m(i,j);
        os << '\n';
    }
    return os;
}

// Copy assignment operator
Matrix& Matrix::operator=(const Matrix& other)
{
    if (this != &other) {
        mData = other.mData;
        mRows = other.mRows;
        mCols = other.mCols;
    }
    return *this;
}