/**
 *	@file	matrix3x3_fwd.hpp
 *
 *	@brief	Matrix3x3 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_MATRIX3X3_FWD_HPP
#define BKSGE_CORE_MATH_FWD_MATRIX3X3_FWD_HPP

#include <bksge/core/math/fwd/matrix_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Matrix3x3 = Matrix<T, 3, 3>;

using Matrix3x3f = Matrix3x3<float>;

}	// namespace math

using math::Matrix3x3;
using math::Matrix3x3f;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_MATRIX3X3_FWD_HPP
