/**
 *	@file	color_hsv_fwd.hpp
 *
 *	@brief	ColorHSV の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_COLOR_HSV_FWD_HPP
#define BKSGE_MATH_FWD_COLOR_HSV_FWD_HPP

namespace bksge
{

namespace math
{

template <typename T>
class ColorHSV;

using ColorHSVf = ColorHSV<float>;

}	// namespace math

using math::ColorHSV;
using math::ColorHSVf;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_COLOR_HSV_FWD_HPP
