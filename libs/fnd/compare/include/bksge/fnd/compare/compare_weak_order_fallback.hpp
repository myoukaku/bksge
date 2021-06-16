/**
 *	@file	compare_weak_order_fallback.hpp
 *
 *	@brief	compare_weak_order_fallback の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_COMPARE_WEAK_ORDER_FALLBACK_HPP
#define BKSGE_FND_COMPARE_COMPARE_WEAK_ORDER_FALLBACK_HPP

#include <bksge/fnd/compare/config.hpp>

#if defined(BKSGE_USE_STD_COMPARE)

#include <compare>

namespace bksge
{

using std::compare_weak_order_fallback;

}	// namespace bksge

#else

#include <bksge/fnd/compare/detail/weak_fallback_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

inline namespace compare_cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR
detail::weak_fallback_t compare_weak_order_fallback{};

}	// inline namespace compare_cpo

}	// namespace bksge

#endif

#endif // BKSGE_FND_COMPARE_COMPARE_WEAK_ORDER_FALLBACK_HPP
