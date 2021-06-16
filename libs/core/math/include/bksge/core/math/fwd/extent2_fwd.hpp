/**
 *	@file	extent2_fwd.hpp
 *
 *	@brief	Extent2 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_EXTENT2_FWD_HPP
#define BKSGE_CORE_MATH_FWD_EXTENT2_FWD_HPP

#include <bksge/core/math/fwd/extent_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Extent2 = Extent<T, 2>;

using Extent2f = Extent2<float>;

}	// namespace math

using math::Extent2;
using math::Extent2f;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_EXTENT2_FWD_HPP
