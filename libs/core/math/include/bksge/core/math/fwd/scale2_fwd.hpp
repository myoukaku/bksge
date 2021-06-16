/**
 *	@file	scale2_fwd.hpp
 *
 *	@brief	Scale2 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_SCALE2_FWD_HPP
#define BKSGE_CORE_MATH_FWD_SCALE2_FWD_HPP

#include <bksge/core/math/fwd/scale_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Scale2 = Scale<T, 2>;

using Scale2f = Scale2<float>;

}	// namespace math

using math::Scale2;
using math::Scale2f;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_SCALE2_FWD_HPP
