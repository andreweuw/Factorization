#include "EigenDecomposition.h"
#include <iostream>

#include "ExpressionMatrix.h"
#include <stack>

EigenDecomposition::EigenDecomposition(const Matrix& a) : mA(a)
{
	decompose();
}

void EigenDecomposition::decompose()
{
	const auto [rows, cols] = mA.dimensions();
	/// A = 
	///		1 0
	///		1 3
	/// 
	/// Q =
	///		a b
	///		c d
	/// 
	/// ----------------------------------------
	///		-1
	/// a b    *  1 0   *  a b	=	x 0  / * Q
	/// c d		  1 3	   c d      0 y
	/// ----------------------------------------
	///	1 0  *  a b  =  a b  *  x 0
	/// 1 3     c d     c d     0 y
	/// ----------------------------------------
	/// 1 0  *  a  =  ax
	/// 1 3     c     cx
	///
	///	1 0  *  b  =  by
	/// 1 3     d  =  dy
	/// ----------------------------------------
	///	a = a     b = b
	///	    c         d
	/// ----------------------------------------
	///	Aa = xa
	///	Ab = yb
	/// ----------------------------------------
	///	Au = lambda u
	///                   T
	///	... lambda = [x, y]  eigenvalues
	///				  T
	///	... u = [a, b]	eigenvectors
	/// ----------------------------------------
	///	/ - lambda u
	///	(A - lambda I) u = 0
	/// ----------------------------------------
	/// Q ... non-singular -> u ... non-zero =>
	///	det(A - lambda I) = 0
	std::cout << mA << '\n';
	Matrix identity = Matrix::identity(cols);
	// Naive Idea:
	 
	// express the determinant polynomial where lambdas are the unknowns
	// to do that, we need a matrix, which has strings as values and build the
	// determinant string with appropriate operators. Then, we need to simplify the string
	// by unpacking of parentheses and summing appropriate polynomials in their vector space.
	// Then, the roots of this polynomial must be found with respect to the lambdas.
	ExpressionMatrix A = ExpressionMatrix(mA);
	ExpressionMatrix lambdaI = ExpressionMatrix(identity);
	lambdaI *= ExpressionMatrix::eye(cols, "a");
	std::cout << A << '\n';
	std::cout << lambdaI << '\n';
	auto aMinusLambdaI = A - lambdaI;
	std::cout << "aMinusLambdaI: " << aMinusLambdaI << '\n';
	std::cout << "Determinant: " << aMinusLambdaI.determinant() << '\n';
}

int EigenDecomposition::precedence(const std::string& op) {
	if (op == "+" || op == "-") return 1;
	if (op == "*" || op == "/") return 2;
	return 0;
}

std::vector<std::string> EigenDecomposition::infixToPostFix(const std::vector<std::string>& expression) {
	if (expression.size() <= 1) return expression;

	std::vector<std::string> result;
	std::stack<std::string> s;

	for (const std::string& part : expression) {
		if (precedence(part) > 0) {
			while (!s.empty() && precedence(s.top()) >= precedence(part)) {
				result.push_back(s.top());
				s.pop();
			}
			s.push(part);
		}
		else if (part == ")") {
			std::string x = s.top();
			s.pop();
			while (x != "(") {
				result.push_back(x);
				x = s.top();
				s.pop();
			}
		}
		else if (part == "(") {
			s.push(part);
		}
		else {
			result.push_back(part);
		}
	}

	while (!s.empty()) {
		result.push_back(s.top());
		s.pop();
	}

	return result;
}

