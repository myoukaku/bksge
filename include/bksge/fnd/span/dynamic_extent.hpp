/**
 *	@file	dynamic_extent.hpp
 *
 *	@brief	dynamic_extent の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_DYNAMIC_EXTENT_HPP
#define BKSGE_FND_SPAN_DYNAMIC_EXTENT_HPP

#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <limits>

namespace bksge
{

BKSGE_INLINE_VAR constexpr std::size_t
	dynamic_extent = std::numeric_limits<std::size_t>::max();

}	// namespace bksge

#endif // BKSGE_FND_SPAN_DYNAMIC_EXTENT_HPP
