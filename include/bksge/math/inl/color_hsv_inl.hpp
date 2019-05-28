/**
 *	@file	color_hsv_inl.hpp
 *
 *	@brief	ColorHSV の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_INL_COLOR_HSV_INL_HPP
#define BKSGE_MATH_INL_COLOR_HSV_INL_HPP

#include <bksge/math/color_hsv.hpp>
#include <bksge/math/color3.hpp>
#include <bksge/cmath/clamp.hpp>
#include <bksge/cmath/fmod.hpp>
#include <bksge/config.hpp>
#include <algorithm>

namespace bksge
{

namespace math
{

template <typename T>
template <typename U>
inline BKSGE_CXX14_CONSTEXPR
ColorHSV<T>::ColorHSV(Color3<U> const& rgb)
{
	T const r = rgb.r();
	T const g = rgb.g();
	T const b = rgb.b();
	T const max = std::max({r, g, b});
	T const min = std::min({r, g, b});
	T const d = max - min;

	if (max == min)
	{
		h() = 0;
	}
	else if (max == r)
	{
		h() = ((g - b) / d + T(0)) / T(6);
		if (h() < 0)
		{
			h() += T(1);
		}
	}
	else if (max == g)
	{
		h() = ((b - r) / d + T(2)) / T(6);
	}
	else // if (max == b)
	{
		h() = ((r - g) / d + T(4)) / T(6);
	}

	if (max == 0)
	{
		s() = 0;
	}
	else
	{
		s() = d / max;
	}

	v() = max;
}

template <typename T>
inline ColorHSV<T>::operator Color3<T>() const
{
	auto const normalized_hsv = Normalized(*this);
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

template <typename T>
inline BKSGE_CONSTEXPR auto
ColorHSV<T>::Zero() BKSGE_NOEXCEPT
-> ColorHSV
{
	return ColorHSV{};
}

template <typename T>
inline ColorHSV<T>
Normalized(ColorHSV<T> const& hsv)
{
	auto const tmp_h = bksge::fmod(hsv.h(), T(1));
	return ColorHSV<T>(
		tmp_h < 0 ? tmp_h + T(1) : tmp_h,
		bksge::clamp(hsv.s(), T(0), T(1)),
		bksge::clamp(hsv.v(), T(0), T(1)));
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_MATH_INL_COLOR_HSV_INL_HPP
