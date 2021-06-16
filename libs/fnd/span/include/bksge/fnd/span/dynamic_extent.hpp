/**
 *	@file	dynamic_extent.hpp
 *
 *	@brief	dynamic_extent の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SPAN_DYNAMIC_EXTENT_HPP
#define BKSGE_FND_SPAN_DYNAMIC_EXTENT_HPP

#include <bksge/fnd/span/config.hpp>

#if defined(BKSGE_USE_STD_SPAN)

namespace bksge
{

using std::dynamic_extent;

}	// namespace bksge

#else

#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR bksge::size_t
	dynamic_extent = static_cast<bksge::size_t>(-1);

}	// namespace bksge

#endif

#endif // BKSGE_FND_SPAN_DYNAMIC_EXTENT_HPP
