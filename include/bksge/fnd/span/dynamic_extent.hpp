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

#if defined(__cpp_lib_span) && (__cpp_lib_span >= 202002) && \
	defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002)

namespace bksge
{

using std::dynamic_extent;

}	// namespace bksge

#else

#include <cstddef>

namespace bksge
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR std::size_t
	dynamic_extent = static_cast<std::size_t>(-1);

}	// namespace bksge

#endif

#endif // BKSGE_FND_SPAN_DYNAMIC_EXTENT_HPP
