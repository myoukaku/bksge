/**
 *	@file	color3_inl.hpp
 *
 *	@brief	Color3 の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_INL_COLOR3_INL_HPP
#define BKSGE_MATH_INL_COLOR3_INL_HPP

#include <bksge/math/color3.hpp>
#include <bksge/math/color_hsv.hpp>

namespace bksge
{

namespace math
{

template <typename T>
template <typename U, typename>
inline BKSGE_CONSTEXPR
Color<T, 3>::Color(Color<U, 3> const& rhs)
	BKSGE_NOEXCEPT_OR_NOTHROW
	: BaseType(color_cast<Color<T, 3>>(rhs).as_array())
{}

template <typename T>
template <typename U>
inline BKSGE_CXX14_CONSTEXPR
Color<T, 3>::Color(ColorHSV<U> const& hsv)
	: Color(HSVtoRGB(hsv))
{
}

}	// namespace math

}	// namespace bksge

#endif // BKSGE_MATH_INL_COLOR3_INL_HPP
