/**
 *	@file	rgb_to_hsv.hpp
 *
 *	@brief	rgb_to_hsv の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_RGB_TO_HSV_HPP
#define BKSGE_CORE_MATH_DETAIL_RGB_TO_HSV_HPP

#include <bksge/core/math/color_hsv.hpp>
#include <bksge/core/math/color3.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR ColorHSV<T>
rgb_to_hsv(Color3<T> const& rgb)
{
	T const r = rgb.r();
	T const g = rgb.g();
	T const b = rgb.b();
	T const max = bksge::max({r, g, b});
	T const min = bksge::min({r, g, b});
	T const d = max - min;

	T h = 0;
	T s = 0;
	T v = 0;

	if (max == min)
	{
		h = 0;
	}
	else if (max == r)
	{
		h = ((g - b) / d + T(0)) / T(6);
		if (h < 0)
		{
			h += T(1);
		}
	}
	else if (max == g)
	{
		h = ((b - r) / d + T(2)) / T(6);
	}
	else // if (max == b)
	{
		h = ((r - g) / d + T(4)) / T(6);
	}

	if (max == 0)
	{
		s = 0;
	}
	else
	{
		s = d / max;
	}

	v = max;

	return { h, s, v };
}

}	// namespace detail

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_DETAIL_RGB_TO_HSV_HPP
