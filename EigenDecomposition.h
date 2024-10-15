#pragma once
#include <vector>

#include "Matrix.h"

/// @brief For a square matrix A of n_n dimensions
/// having n linearly independent eigenvectors q_i,
/// A can be factored as
/// 
/// A = Q /\ Q^-1
/// 
/// where Q is a square n_n matrix where ith column is q_i of A
/// and /\ is n_n diagonal matrix with ith eigen value
/// A must be diagonalizable.
class EigenDecomposition
{
	std::vector<double> mEigenValues;
	Matrix mQ, mA;


	void decompose();

public:

	EigenDecomposition(const Matrix& a);
	static int precedence(const std::string& op);
	static std::vector<std::string> infixToPostFix(const std::vector<std::string>& expression);
};

