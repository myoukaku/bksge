/**
 *	@file	color_fwd.hpp
 *
 *	@brief	Color の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_COLOR_FWD_HPP
#define BKSGE_CORE_MATH_FWD_COLOR_FWD_HPP

#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace math
{

template <typename T, bksge::size_t N>
class Color;

}	// namespace math

using math::Color;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_COLOR_FWD_HPP
