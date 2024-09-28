#include "Matrix.h"
#include <cassert>
#include <iostream>
#include "LeibnizDeterminant.h"

using std::ostream;

Matrix::Matrix(size_t rows, size_t cols) : mRows(rows), mCols(cols)
{
    assert(mRows > 0 && "Number of rows should be greater than zero.");
    assert(mCols > 0 && "Number of columns should be greater than zero.");

   // std::cout << "Zero constructor" << std::endl;

    // Create a vector of vectors and initialize all elements to zero
    mData = std::vector<std::vector<double>>(mRows, std::vector<double>(mCols, 0.0));
}

Matrix::Matrix(const Matrix& other) : mData(other.mData), mRows(other.mRows), mCols(other.mCols)
{
    //std::cout << "Copy constructor" << std::endl;
}

Matrix::Matrix(const std::vector<std::vector<double>>& data) : mData(data), mRows(data.size()), mCols(data[0].size()) 
{
    assert(mRows > 0 && "Number of rows should be greater than zero.");

    mCols = data[0].size();

    // Check if all rows have the same number of columns
    for (const auto& row : data) {
        assert(row.size() == mCols && "All rows must have the same number of columns.");
    }

    //std::cout << "Data constructor" << std::endl;
}

Matrix Matrix::identity(size_t dimension)
{
    //std::cout << "Identity creator" << std::endl;
    Matrix identity(dimension, dimension);
    for (size_t i = 0; i < dimension; i++)
    {
        identity.mData[i][i] = 1.0;
    }
    return identity;
}

double Matrix::determinant() const
{
    if (mRows != mCols) {
        std::cout << "Determinant can only be computed for square matrix.";
        return std::numeric_limits<double>::max();
    }

    if (mRows <= 3) {
        // This is super bad and useless but was a nice excercise
        // ofcourse, writing the terms out explicitly would be a lot better.


        double determinant = 0;    
        // walk +1 +1 through the matrix
        size_t count = mRows == 2 ? 1 : 0;
        int i = 0, j = 0;
        while (count++ < mCols) {
            double tmp = 1;

            size_t countt = 0;
            while (countt++ < mCols) {
                tmp *= mData[i++][j++%mCols];   
            }
            i = 0;
            j = count;
            determinant += tmp;
        }

        j = mCols - 1;
        count = mRows == 2 ? 1 : 0;
        while (count++ < mCols) {
            double tmp = 1;
            size_t countt = 0;
            while (countt++ < mCols) {
                tmp *= mData[i++][j--];
                if (j == -1)
                    j = mRows - 1;
            }
            i = 0;
            j = mCols - count -1;
            determinant -= tmp;
        }

        return determinant;
    }
    else {
        return LeibnizDeterminant::determinant(*this);
    }
}

Matrix Matrix::operator*(const Matrix& other)
{
    auto thisDimensions = this->dimensions();
    auto otherDimensions = other.dimensions();
    std::cout << "Multiply " << thisDimensions.first << "X" << thisDimensions.second << " by " << otherDimensions.first << "X" << otherDimensions.second << std::endl;
    assert(thisDimensions.second == otherDimensions.first && "The columns of first matrix have to be the same as rows of the right one.");

    Matrix multiplied(thisDimensions.first, otherDimensions.second);
    for (size_t i = 0; i < multiplied.mRows; ++i)
    {
        for (size_t j = 0; j < multiplied.mCols; ++j)
        {
            for (size_t k = 0; k < mCols; ++k)
            {
                multiplied.mData[i][j] += mData[i][k] * other.mData[k][j];
            }
        }
    }
    return multiplied;
}

Matrix& Matrix::operator*=(const Matrix& other)
{
    return (*this = this->operator*(other));
}

std::pair<size_t, size_t> Matrix::dimensions() const
{
    return { mRows, mCols };
}

bool Matrix::operator==(const Matrix& other) const
{
    return mData == other.mData && mRows == other.mRows && mCols == other.mCols;
}

double& Matrix::operator()(size_t row, size_t col)
{
    // Add bounds checking here if necessary.
    return mData[row][col];
}

const double& Matrix::operator()(size_t row, size_t col) const
{
    // Add bounds checking here if necessary.
    return mData[row][col];
}

ostream& operator<<(ostream& os, const Matrix& m)
{
    for (size_t i = 0; i < m.mRows; ++i) {
        os << m.mData[i][0];
        for (size_t j = 1; j < m.mCols; ++j) {
            os << " " << m.mData[i][j];
        }
        os << std::endl;
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

        //std::cout << "Copy assignment" << std::endl;
    }
    return *this;
}