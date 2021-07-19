﻿/**
 *	@file	strong_fallback_t.hpp
 *
 *	@brief	strong_fallback_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_STRONG_FALLBACK_T_HPP
#define BKSGE_FND_COMPARE_DETAIL_STRONG_FALLBACK_T_HPP

#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/compare/detail/strong_order_t.hpp>
#include <bksge/fnd/compare/detail/op_eq_lt.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype((__VA_ARGS__))              \
	{ return __VA_ARGS__; }

class strong_fallback_t
{
private:
	// strong_order(e, f)
	template <typename T, typename U>
	static BKSGE_CONSTEXPR auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<1>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		detail::strong_order_t{}(std::forward<T>(e), std::forward<U>(f)))

	// e == f, e < f
	template <typename T, typename U,
		typename = bksge::enable_if_t<detail::op_eq_lt<T, U>::value>
	>
	static BKSGE_CONSTEXPR bksge::strong_ordering
	impl(T&& e, U&& f, bksge::detail::overload_priority<0>)
		BKSGE_NOEXCEPT_IF(
			BKSGE_NOEXCEPT_EXPR(bool(std::declval<T>() == std::declval<U>())) &&
			BKSGE_NOEXCEPT_EXPR(bool(std::declval<T>() <  std::declval<U>())))
	{
		return
			std::forward<T>(e) == std::forward<U>(f) ? bksge::strong_ordering::equal :
			std::forward<T>(e) <  std::forward<U>(f) ? bksge::strong_ordering::less  :
				                                       bksge::strong_ordering::greater;
	}

public:
	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& e, U&& f) const
		BKSGE_NOEXCEPT_IF_EXPR(impl(std::forward<T>(e), std::forward<U>(f), bksge::detail::overload_priority<1>{}))
	->decltype((impl(std::forward<T>(e), std::forward<U>(f), bksge::detail::overload_priority<1>{})))
	{
		static_assert(bksge::is_same_as<bksge::decay_t<T>, bksge::decay_t<U>>::value, "");

		return impl(std::forward<T>(e), std::forward<U>(f), bksge::detail::overload_priority<1>{});
	}
};

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_STRONG_FALLBACK_T_HPP
