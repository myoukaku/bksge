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
#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<span>)
#include <span>
#endif

#if defined(__cpp_lib_span) && (__cpp_lib_span >= 202002)

namespace bksge
{

using std::dynamic_extent;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <limits>

namespace bksge
{

BKSGE_INLINE_VAR constexpr std::size_t
	dynamic_extent = std::numeric_limits<std::size_t>::max();

}	// namespace bksge

#endif

#endif // BKSGE_FND_SPAN_DYNAMIC_EXTENT_HPP
