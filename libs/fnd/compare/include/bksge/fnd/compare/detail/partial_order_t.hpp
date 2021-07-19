/**
 *	@file	partial_order_t.hpp
 *
 *	@brief	partial_order_t の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_PARTIAL_ORDER_T_HPP
#define BKSGE_FND_COMPARE_DETAIL_PARTIAL_ORDER_T_HPP

#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/compare_three_way.hpp>
#include <bksge/fnd/compare/detail/weak_order_t.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
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

#if defined(BKSGE_MSVC) && (BKSGE_MSVC < 1920)
template <typename T, typename U>
void partial_order(T&&, U&&);
#else
template <typename T, typename U>
void partial_order(T&&, U&&) = delete;
#endif

class partial_order_t
{
private:
	friend class partial_fallback_t;

private:
	// partial_ordering(partial_order(e, f))
	template <typename T, typename U>
	static BKSGE_CONSTEXPR auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<2>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		bksge::partial_ordering(partial_order(std::forward<T>(e), std::forward<U>(f))))

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	// partial_ordering(e <=> f)
	template <typename T, typename U>
	static BKSGE_CONSTEXPR auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<1>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		bksge::partial_ordering(bksge::compare_three_way()(std::forward<T>(e), std::forward<U>(f))))
#endif

	// partial_ordering(weak_order(e, f))
	template <typename T, typename U>
	static BKSGE_CONSTEXPR auto
	impl(T&& e, U&& f, bksge::detail::overload_priority<0>)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		bksge::partial_ordering(detail::weak_order_t{}(std::forward<T>(e), std::forward<U>(f))))

public:
	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& e, U&& f) const
		BKSGE_NOEXCEPT_IF_EXPR(impl(std::forward<T>(e), std::forward<U>(f), bksge::detail::overload_priority<2>{}))
	->decltype((impl(std::forward<T>(e), std::forward<U>(f), bksge::detail::overload_priority<2>{})))
	{
		static_assert(bksge::is_same_as<bksge::decay_t<T>, bksge::decay_t<U>>::value, "");

		return impl(std::forward<T>(e), std::forward<U>(f), bksge::detail::overload_priority<2>{});
	}
};

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_PARTIAL_ORDER_T_HPP
