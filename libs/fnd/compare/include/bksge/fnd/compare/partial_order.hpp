/**
 *	@file	partial_order.hpp
 *
 *	@brief	partial_order の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_PARTIAL_ORDER_HPP
#define BKSGE_FND_COMPARE_PARTIAL_ORDER_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::partial_order;

}	// namespace bksge

#else

#include <bksge/fnd/compare/detail/partial_order_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

inline namespace compare_cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::partial_order_t partial_order{};

}	// inline namespace compare_cpo

}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_PARTIAL_ORDER_HPP
