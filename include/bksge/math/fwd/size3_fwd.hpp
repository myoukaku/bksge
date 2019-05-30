/**
 *	@file	size3_fwd.hpp
 *
 *	@brief	Size3 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_SIZE3_FWD_HPP
#define BKSGE_MATH_FWD_SIZE3_FWD_HPP

#include <bksge/math/fwd/size_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Size3 = Size<T, 3>;

using Size3f = Size3<float>;

}	// namespace math

using math::Size3;
using math::Size3f;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_SIZE3_FWD_HPP
