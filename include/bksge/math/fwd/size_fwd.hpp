/**
 *	@file	size_fwd.hpp
 *
 *	@brief	Size の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MATH_FWD_SIZE_FWD_HPP
#define BKSGE_MATH_FWD_SIZE_FWD_HPP

#include <cstddef>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
class Size;

}	// namespace math

using math::Size;

}	// namespace bksge

#endif // BKSGE_MATH_FWD_SIZE_FWD_HPP
