/**
 *	@file	is_lt.hpp
 *
 *	@brief	is_lt の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_IS_LT_HPP
#define BKSGE_FND_COMPARE_IS_LT_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::is_lt;

}	// namespace bksge

#else

#include <bksge/fnd/compare/partial_ordering.hpp>

namespace bksge
{

constexpr bool
is_lt(bksge::partial_ordering cmp) noexcept
{
	return cmp < 0;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_IS_LT_HPP
