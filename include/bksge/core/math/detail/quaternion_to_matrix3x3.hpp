/**
 *	@file	quaternion_to_matrix3x3.hpp
 *
 *	@brief	quaternion_to_matrix3x3 の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_QUATERNION_TO_MATRIX3X3_HPP
#define BKSGE_CORE_MATH_DETAIL_QUATERNION_TO_MATRIX3X3_HPP

#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/quaternion.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR Matrix<T, 3, 3>
quaternion_to_matrix3x3_impl(T xx, T xy, T xz, T xw, T yy, T yz, T yw, T zz, T zw) BKSGE_NOEXCEPT
{
	return
	{
		{ 1 - yy - zz, xy + zw,     xz - yw },
		{ xy - zw,     1 - xx - zz, yz + xw },
		{ xz + yw,     yz - xw,     1 - xx - yy },
	};
}

template <typename T>
inline BKSGE_CONSTEXPR Matrix<T, 3, 3>
quaternion_to_matrix3x3(Quaternion<T> const& q) BKSGE_NOEXCEPT
{
	return quaternion_to_matrix3x3_impl(
		2 * q.x() * q.x(),
		2 * q.x() * q.y(),
		2 * q.x() * q.z(),
		2 * q.x() * q.w(),
		2 * q.y() * q.y(),
		2 * q.y() * q.z(),
		2 * q.y() * q.w(),
		2 * q.z() * q.z(),
		2 * q.z() * q.w());
}

}	// namespace detail

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_DETAIL_QUATERNION_TO_MATRIX3X3_HPP
