/**
 *	@file	size2_fwd.hpp
 *
 *	@brief	Size2 の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_SIZE2_FWD_HPP
#define BKSGE_MATH_FWD_SIZE2_FWD_HPP

#include <bksge/math/fwd/size_fwd.hpp>

namespace bksge
{

namespace math
{

template <typename T>
using Size2 = Size<T, 2>;

}	// namespace math

using math::Size2;

using Size2f = Size2<float>;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_SIZE2_FWD_HPP
