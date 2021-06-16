/**
 *	@file	vector3_fwd.hpp
 *
 *	@brief	Vector3 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_VECTOR3_FWD_HPP
#define BKSGE_CORE_MATH_FWD_VECTOR3_FWD_HPP

#include <bksge/core/math/fwd/vector_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Vector3 = Vector<T, 3>;

using Vector3f = Vector3<float>;

}	// namespace math

using math::Vector3;
using math::Vector3f;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_VECTOR3_FWD_HPP
