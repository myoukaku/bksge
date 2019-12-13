/**
 *	@file	rect_fwd.hpp
 *
 *	@brief	Rect の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_RECT_FWD_HPP
#define BKSGE_CORE_MATH_FWD_RECT_FWD_HPP

namespace bksge
{

namespace math
{

template <typename T>
class Rect;

using Rectf = Rect<float>;

}	// namespace math

using math::Rect;
using math::Rectf;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_RECT_FWD_HPP
