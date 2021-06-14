/**
 *	@file	weak_order.hpp
 *
 *	@brief	weak_order の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_WEAK_ORDER_HPP
#define BKSGE_FND_COMPARE_WEAK_ORDER_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::weak_order;

}	// namespace bksge

#else

#include <bksge/fnd/compare/detail/weak_order_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

inline namespace compare_cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::weak_order_t weak_order{};

}	// inline namespace compare_cpo

}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_WEAK_ORDER_HPP
