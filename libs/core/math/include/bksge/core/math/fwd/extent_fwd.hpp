/**
 *	@file	extent_fwd.hpp
 *
 *	@brief	Extent の前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_FWD_EXTENT_FWD_HPP
#define BKSGE_CORE_MATH_FWD_EXTENT_FWD_HPP

#include <cstddef>

namespace bksge
{

namespace math
{

template <typename T, std::size_t N>
class Extent;

}	// namespace math

using math::Extent;

}	// namespace bksge

#endif // BKSGE_CORE_MATH_FWD_EXTENT_FWD_HPP
