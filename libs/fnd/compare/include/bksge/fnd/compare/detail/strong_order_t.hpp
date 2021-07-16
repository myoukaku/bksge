/**
 *	@file	strong_order_t.hpp
 *
 *	@brief	strong_order_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_STRONG_ORDER_T_HPP
#define BKSGE_FND_COMPARE_DETAIL_STRONG_ORDER_T_HPP

#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/compare/compare_three_way.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
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

#if defined(BKSGE_MSVC) && (BKSGE_MSVC < 1920)
template <typename T, typename U>
void strong_order(T&&, U&&);
#else
template <typename T, typename U>
void strong_order(T&&, U&&) = delete;
#endif

class strong_order_t
{
private:
	friend class weak_order_t;
	friend class strong_fallback_t;

private:
	// strong_ordering(strong_order(e, f))
	template <typename T, typename U>
	static BKSGE_CONSTEXPR auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<2>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		bksge::strong_ordering(strong_order(bksge::forward<T>(e), bksge::forward<U>(f))))

#if 0
	// floating_point
	template <typename T, typename U>
	requires bksge::floating_point<bksge::decay_t<T>>
	static BKSGE_CONSTEXPR bksge::strong_ordering
	impl(T&& e, U&& f, bksge::detail::overload_priority<2>)
		BKSGE_NOEXCEPT
	{
		// 未実装
		return detail::fp_strong_order(e, f);
	}
#endif

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	// strong_ordering(e <=> f)
	template <typename T, typename U>
	static BKSGE_CONSTEXPR auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<0>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		bksge::strong_ordering(bksge::compare_three_way()(bksge::forward<T>(e), bksge::forward<U>(f))))
#endif

public:
	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& e, U&& f) const
		BKSGE_NOEXCEPT_IF_EXPR(impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<2>{}))
	->decltype((impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<2>{})))
	{
		static_assert(bksge::is_same_as<bksge::decay_t<T>, bksge::decay_t<U>>::value, "");

		return impl(bksge::forward<T>(e), bksge::forward<U>(f), bksge::detail::overload_priority<2>{});
	}
};

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_STRONG_ORDER_T_HPP
