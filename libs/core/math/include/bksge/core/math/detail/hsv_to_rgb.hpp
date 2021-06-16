/**
 *	@file	hsv_to_rgb.hpp
 *
 *	@brief	hsv_to_rgb の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_HSV_TO_RGB_HPP
#define BKSGE_CORE_MATH_DETAIL_HSV_TO_RGB_HPP

#include <bksge/core/math/color_hsv.hpp>
#include <bksge/core/math/color3.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR Color3<T>
hsv_to_rgb(ColorHSV<T> const& hsv)
{
	auto const normalized_hsv = Normalized(hsv);
	T const h = normalized_hsv.h();
	T const s = normalized_hsv.s();
	T const v = normalized_hsv.v();

	if (s == 0)
	{
		return { v, v, v };
	}

	auto const i = static_cast<int>(h * 6);
	T const f = h * 6 - i;
	T const p = v * (1 - s);
	T const q = v * (1 - f * s);
	T const t = v * (1 - (1 - f) * s);

	switch (i)
	{
	case 0: return { v, t, p };
	case 1: return { q, v, p };
	case 2: return { p, v, t };
	case 3: return { p, q, v };
	case 4: return { t, p, v };
	case 5: return { v, p, q };
	}

	return {};
}

}	// namespace detail

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_DETAIL_HSV_TO_RGB_HPP
