/**
 *	@file	extent3_fwd.hpp
 *
 *	@brief	Extent3 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_EXTENT3_FWD_HPP
#define BKSGE_CORE_MATH_FWD_EXTENT3_FWD_HPP

#include <bksge/core/math/fwd/extent_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Extent3 = Extent<T, 3>;

using Extent3f = Extent3<float>;

}	// namespace math

using math::Extent3;
using math::Extent3f;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_EXTENT3_FWD_HPP
