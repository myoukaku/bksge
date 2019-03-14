/**
 *	@file	matrix4x3_fwd.hpp
 *
 *	@brief	Matrix4x3 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_MATRIX4X3_FWD_HPP
#define BKSGE_MATH_FWD_MATRIX4X3_FWD_HPP

#include <bksge/math/fwd/matrix_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Matrix4x3 = Matrix<T, 4, 3>;

}	// namespace math

using math::Matrix4x3;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_MATRIX4X3_FWD_HPP
