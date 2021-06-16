/**
 *	@file	color3_fwd.hpp
 *
 *	@brief	Color3 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_COLOR3_FWD_HPP
#define BKSGE_CORE_MATH_FWD_COLOR3_FWD_HPP

#include <bksge/core/math/fwd/color_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Color3 = Color<T, 3>;

using Color3f = Color3<float>;

}	// namespace math

using math::Color3;
using math::Color3f;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_COLOR3_FWD_HPP
