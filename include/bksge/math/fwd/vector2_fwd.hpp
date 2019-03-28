/**
 *	@file	vector2_fwd.hpp
 *
 *	@brief	Vector2 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_VECTOR2_FWD_HPP
#define BKSGE_MATH_FWD_VECTOR2_FWD_HPP

#include <bksge/math/fwd/vector_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Vector2 = Vector<T, 2>;

using Vector2f = Vector2<float>;

}	// namespace math

using math::Vector2;
using math::Vector2f;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_VECTOR2_FWD_HPP
