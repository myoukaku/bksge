/**
 *	@file	is_eq.hpp
 *
 *	@brief	is_eq の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_IS_EQ_HPP
#define BKSGE_FND_COMPARE_IS_EQ_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::is_eq;

}	// namespace bksge

#else

#include <bksge/fnd/compare/partial_ordering.hpp>

namespace bksge
{

constexpr bool
is_eq(bksge::partial_ordering cmp) noexcept
{
	return cmp == 0;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_IS_EQ_HPP
