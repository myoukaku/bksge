/**
 *	@file	matrix3x3_to_quaternion.hpp
 *
 *	@brief	matrix3x3_to_quaternion の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_MATRIX3X3_TO_QUATERNION_HPP
#define BKSGE_CORE_MATH_DETAIL_MATRIX3X3_TO_QUATERNION_HPP

#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/quaternion.hpp>
#include <bksge/fnd/algorithm/ranges/max_element.hpp>
#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/iterator/ranges/distance.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR Quaternion<T>
matrix3x3_to_quaternion(Matrix<T, 3, 3> const& m) BKSGE_NOEXCEPT
{
	// 最大成分を検索
	T const elem[] =
	{
		 m[0][0] - m[1][1] - m[2][2] + T(1),	// x
		-m[0][0] + m[1][1] - m[2][2] + T(1),	// y
		-m[0][0] - m[1][1] + m[2][2] + T(1),	// z
		 m[0][0] + m[1][1] + m[2][2] + T(1),	// w
	};

	auto const max_it = bksge::ranges::max_element(elem);

	if (*max_it < 0)
	{
		// 引数の行列に間違いあり！
		return Quaternion<T>::Identity();
	}

	// 最大要素の値を算出
	auto const v = bksge::sqrt(*max_it) * 0.5f;
	auto const mult = 0.25f / v;

	switch (bksge::ranges::distance(elem, max_it))
	{
	case 0: // x
		return
		{
			v,
			(m[0][1] + m[1][0]) * mult,
			(m[2][0] + m[0][2]) * mult,
			(m[1][2] - m[2][1]) * mult,
		};
	case 1: // y
		return
		{
			(m[0][1] + m[1][0]) * mult,
			v,
			(m[1][2] + m[2][1]) * mult,
			(m[2][0] - m[0][2]) * mult,
		};
	case 2: // z
		return
		{
			(m[2][0] + m[0][2]) * mult,
			(m[1][2] + m[2][1]) * mult,
			v,
			(m[0][1] - m[1][0]) * mult,
		};
	case 3: // w
		return
		{
			(m[1][2] - m[2][1]) * mult,
			(m[2][0] - m[0][2]) * mult,
			(m[0][1] - m[1][0]) * mult,
			v,
		};
	default:
		// ここには来るはずがない
		return Quaternion<T>::Identity();
	}
}

}	// namespace detail

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_DETAIL_MATRIX3X3_TO_QUATERNION_HPP
