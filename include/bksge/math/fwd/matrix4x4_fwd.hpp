/**
 *	@file	matrix4x4_fwd.hpp
 *
 *	@brief	Matrix4x4 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_MATRIX4X4_FWD_HPP
#define BKSGE_MATH_FWD_MATRIX4X4_FWD_HPP

#include <bksge/math/fwd/matrix_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Matrix4x4 = Matrix<T, 4, 4>;

}	// namespace math

using math::Matrix4x4;

using Matrix4x4f = Matrix4x4<float>;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_MATRIX4X4_FWD_HPP
