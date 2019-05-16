/**
 *	@file	rect_fwd.hpp
 *
 *	@brief	Rect の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_RECT_FWD_HPP
#define BKSGE_MATH_FWD_RECT_FWD_HPP

namespace bksge
{

namespace math
{

template <typename T>
class Rect;

}	// namespace math

using math::Rect;

using Rectf = Rect<float>;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_RECT_FWD_HPP
