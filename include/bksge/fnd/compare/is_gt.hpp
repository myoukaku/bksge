/**
 *	@file	is_gt.hpp
 *
 *	@brief	is_gt の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_IS_GT_HPP
#define BKSGE_FND_COMPARE_IS_GT_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::is_gt;

}	// namespace bksge

#else

#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

BKSGE_CONSTEXPR bool
is_gt(bksge::partial_ordering cmp) BKSGE_NOEXCEPT
{
	return cmp > 0;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_IS_GT_HPP
