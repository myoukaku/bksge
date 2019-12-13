/**
 *	@file	vector3.hpp
 *
 *	@brief	Vector3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_VECTOR3_HPP
#define BKSGE_CORE_MATH_VECTOR3_HPP

#include <bksge/core/math/fwd/vector3_fwd.hpp>
#include <bksge/core/math/vector.hpp>

namespace bksge
{

namespace math
{

/**
 *	@brief	外積
 */
template <typename T>
inline BKSGE_CONSTEXPR Vector3<T>
Cross(Vector3<T> const& v1, Vector3<T> const& v2) BKSGE_NOEXCEPT
{
	return Vector3<T>
	{
		(v1.y() * v2.z()) - (v1.z() * v2.y()),
		(v1.z() * v2.x()) - (v1.x() * v2.z()),
		(v1.x() * v2.y()) - (v1.y() * v2.x()),
	};
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_VECTOR3_HPP
