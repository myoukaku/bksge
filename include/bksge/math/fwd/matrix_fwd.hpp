/**
 *	@file	matrix_fwd.hpp
 *
 *	@brief	Matrix の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_MATRIX_FWD_HPP
#define BKSGE_MATH_FWD_MATRIX_FWD_HPP

#include <cstddef>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N, std::size_t M>
class Matrix;

}	// namespace math

using math::Matrix;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_MATRIX_FWD_HPP
