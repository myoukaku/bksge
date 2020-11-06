/**
 *	@file	weak_order_t.hpp
 *
 *	@brief	weak_order_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_WEAK_ORDER_T_HPP
#define BKSGE_FND_COMPARE_DETAIL_WEAK_ORDER_T_HPP

#include <bksge/fnd/compare/weak_ordering.hpp>
#include <bksge/fnd/compare/compare_three_way.hpp>
#include <bksge/fnd/compare/detail/strong_order_t.hpp>
#include <bksge/fnd/compare/detail/fp_weak_ordering.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
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

template <typename T, typename U>
void weak_order(T&&, U&&) = delete;

class weak_order_t
{
private:
	friend class partial_order_t;
	friend class weak_fallback_t;

private:
	// weak_ordering(weak_order(e, f))
	template <typename T, typename U>
	static BKSGE_CONSTEXPR auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<3>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		bksge::weak_ordering(weak_order(bksge::forward<T>(e), bksge::forward<U>(f))))

	// floating_point
	template <typename T, typename U,
		typename = bksge::enable_if_t<bksge::is_floating_point<bksge::decay_t<T>>::value>>
	static BKSGE_CONSTEXPR bksge::weak_ordering
	impl(T&& e, U&& f, bksge::detail::overload_priority<2>)
		BKSGE_NOEXCEPT
	{
		return detail::fp_weak_ordering(e, f);
	}

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	// weak_ordering(e <=> f)
	template <typename T, typename U>
	static BKSGE_CONSTEXPR auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<1>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		bksge::weak_ordering(bksge::compare_three_way()(bksge::forward<T>(e), bksge::forward<U>(f))))
#endif

	// weak_ordering(strong_order(e, f))
	template <typename T, typename U>
	static BKSGE_CONSTEXPR auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<0>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		bksge::weak_ordering(detail::strong_order_t{}(bksge::forward<T>(e), bksge::forward<U>(f))))

public:
	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& e, U&& f) const
		BKSGE_NOEXCEPT_IF_EXPR(impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<3>{}))
	->decltype((impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<3>{})))
	{
		static_assert(bksge::is_same_as<bksge::decay_t<T>, bksge::decay_t<U>>::value, "");

		return impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<3>{});
	}
};

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_WEAK_ORDER_T_HPP
