﻿/**
 *	@file	partial_fallback_t.hpp
 *
 *	@brief	partial_fallback_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_PARTIAL_FALLBACK_T_HPP
#define BKSGE_FND_COMPARE_DETAIL_PARTIAL_FALLBACK_T_HPP

#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/detail/partial_order_t.hpp>
#include <bksge/fnd/compare/detail/op_eq_lt.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype((__VA_ARGS__))              \
	{ return __VA_ARGS__; }

class partial_fallback_t
{
private:
	// partial_order(e, f)
	template <typename T, typename U>
	static constexpr auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<1>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		detail::partial_order_t{}(bksge::forward<T>(e), bksge::forward<U>(f)))

	// e == f, e < f
	template <typename T, typename U,
		typename = bksge::enable_if_t<detail::op_eq_lt<T, U>::value>
	>
	static constexpr bksge::partial_ordering
	impl(T&& e, U&& f, bksge::detail::overload_priority<0>)
		noexcept(
			noexcept(bool(bksge::declval<T>() == bksge::declval<U>())) &&
			noexcept(bool(bksge::declval<T>() <  bksge::declval<U>())))
	{
		return
			bksge::forward<T>(e) == bksge::forward<U>(f) ? bksge::partial_ordering::equivalent :
			bksge::forward<T>(e) <  bksge::forward<U>(f) ? bksge::partial_ordering::less       :
			bksge::forward<U>(f) <  bksge::forward<T>(e) ? bksge::partial_ordering::greater    :
				                                           bksge::partial_ordering::unordered;
	}

public:
	template <typename T, typename U>
	constexpr auto operator()(T&& e, U&& f) const
		noexcept(noexcept(impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<1>{})))
	->decltype((impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<1>{})))
	{
		static_assert(bksge::is_same_as<bksge::decay_t<T>, bksge::decay_t<U>>::value, "");

		return impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<1>{});
	}
};

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_PARTIAL_FALLBACK_T_HPP
