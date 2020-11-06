/**
 *	@file	weak_fallback_t.hpp
 *
 *	@brief	weak_fallback_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_WEAK_FALLBACK_T_HPP
#define BKSGE_FND_COMPARE_DETAIL_WEAK_FALLBACK_T_HPP

#include <bksge/fnd/compare/weak_ordering.hpp>
#include <bksge/fnd/compare/detail/weak_order_t.hpp>
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

class weak_fallback_t
{
private:
	// weak_order(e, f)
	template <typename T, typename U>
	static BKSGE_CONSTEXPR auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<1>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		detail::weak_order_t{}(bksge::forward<T>(e), bksge::forward<U>(f)))

	// e == f, e < f
	template <typename T, typename U,
		typename = bksge::enable_if_t<detail::op_eq_lt<T, U>::value>
	>
	static BKSGE_CONSTEXPR bksge::weak_ordering
	impl(T&& e, U&& f, bksge::detail::overload_priority<0>)
		BKSGE_NOEXCEPT_IF(
			BKSGE_NOEXCEPT_EXPR(bool(bksge::declval<T>() == bksge::declval<U>())) &&
			BKSGE_NOEXCEPT_EXPR(bool(bksge::declval<T>() <  bksge::declval<U>())))
	{
		return
			bksge::forward<T>(e) == bksge::forward<U>(f) ? bksge::weak_ordering::equivalent :
			bksge::forward<T>(e) <  bksge::forward<U>(f) ? bksge::weak_ordering::less       :
				                                           bksge::weak_ordering::greater;
	}

public:
	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& e, U&& f) const
		BKSGE_NOEXCEPT_IF_EXPR(impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<1>{}))
	->decltype((impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<1>{})))
	{
		static_assert(bksge::is_same_as<bksge::decay_t<T>, bksge::decay_t<U>>::value, "");

		return impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<1>{});
	}
};

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_WEAK_FALLBACK_T_HPP
