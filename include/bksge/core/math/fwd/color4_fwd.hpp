/**
 *	@file	color4_fwd.hpp
 *
 *	@brief	Color4 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_COLOR4_FWD_HPP
#define BKSGE_CORE_MATH_FWD_COLOR4_FWD_HPP

#include <bksge/core/math/fwd/color_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Color4 = Color<T, 4>;

using Color4f = Color4<float>;

}	// namespace math

using math::Color4;
using math::Color4f;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_COLOR4_FWD_HPP
