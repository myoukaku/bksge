/**
 *	@file	vector4_fwd.hpp
 *
 *	@brief	Vector4 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_VECTOR4_FWD_HPP
#define BKSGE_MATH_FWD_VECTOR4_FWD_HPP

#include <bksge/math/fwd/vector_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Vector4 = Vector<T, 4>;

using Vector4f = Vector4<float>;

}	// namespace math

using math::Vector4;
using math::Vector4f;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_VECTOR4_FWD_HPP
