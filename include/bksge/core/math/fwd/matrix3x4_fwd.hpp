/**
 *	@file	matrix3x4_fwd.hpp
 *
 *	@brief	Matrix3x4 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_MATRIX3X4_FWD_HPP
#define BKSGE_CORE_MATH_FWD_MATRIX3X4_FWD_HPP

#include <bksge/core/math/fwd/matrix_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Matrix3x4 = Matrix<T, 3, 4>;

using Matrix3x4f = Matrix3x4<float>;

}	// namespace math

using math::Matrix3x4;
using math::Matrix3x4f;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_MATRIX3X4_FWD_HPP
