#pragma once
/// @brief For a square matrix A of n_n dimensions
/// having n linearly independent eigenvectors q_i,
/// A can be factored as
/// 
/// A = Q/\Q^-1
/// 
/// where Q is a square n_n matrix where ith column is q_i of A
/// and /\ is n_n diagonal matrix with ith eigen value
/// A must be diagonizable
/// 
/// A = 
///		1 0
///		1 3
/// 
/// Q =
///		a b
///		c d
/// 
/// 
///		-1
/// a b    *  1 0   *  a b	=	x 0
/// c d		  1 3	   c d      0 y
class EigenDecomposition
{
};

