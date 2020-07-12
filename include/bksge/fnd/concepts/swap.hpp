/**
 *	@file	swap.hpp
 *
 *	@brief	swap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_SWAP_HPP
#define BKSGE_FND_CONCEPTS_SWAP_HPP

#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/move_constructible.hpp>
#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/concepts/detail/has_adl_swap.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace bksge
{

namespace ranges
{

namespace swap_detail
{

struct swap_fn
{
private:
	template <
		typename T, typename U,
		typename = bksge::enable_if_t<
			has_adl_swap_t<T, U>::value
		>
	>
//	requires has_adl_swap<T, U>
	static BKSGE_CXX14_CONSTEXPR auto
	impl(detail::overload_priority<2>, T&& t, U&& u)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(swap(bksge::forward<T>(t), bksge::forward<U>(u)))

	template <
		typename T, typename U, std::size_t N,
		typename = decltype(bksge::declval<swap_fn const&>()(bksge::declval<T&>(), bksge::declval<U&>()))
	>
//	requires requires(const swap_fn& fn, T& t, U& u)
//	{
//		fn(t, u);
//	}
	static BKSGE_CXX14_CONSTEXPR void
	impl(detail::overload_priority<1>, T (&t)[N], U (&u)[N])
		BKSGE_NOEXCEPT_IF_EXPR(bksge::declval<swap_fn const&>()(*t, *u))
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			swap_fn{}(t[i], u[i]);
		}
	}

	template <
		typename T, typename U,
		typename = bksge::enable_if_t<
			bksge::same_as_t<T, U>::value &&
			bksge::is_lvalue_reference<T>::value &&
			bksge::move_constructible_t<bksge::remove_reference_t<T>>::value &&
			bksge::assignable_from_t<T, bksge::remove_reference_t<T>>::value
		>
	>
//	requires
//		same_as<T, U> &&
//		bksge::is_lvalue_reference<T>::value &&
//		move_constructible<bksge::remove_reference_t<T>> &&
//		assignable_from<T, bksge::remove_reference_t<T>>
	static BKSGE_CXX14_CONSTEXPR void
	impl(detail::overload_priority<0>, T&& t, U&& u)
		BKSGE_NOEXCEPT_IF(
			bksge::is_nothrow_move_constructible<bksge::remove_reference_t<T>>::value &&
			bksge::is_nothrow_move_assignable<bksge::remove_reference_t<T>>::value)
	{
		auto tmp = static_cast<bksge::remove_reference_t<T>&&>(t);
		t = static_cast<bksge::remove_reference_t<T>&&>(u);
		u = static_cast<bksge::remove_reference_t<T>&&>(tmp);
	}

public:
	template <typename T, typename U>
	BKSGE_CXX14_CONSTEXPR auto operator()(T&& t, U&& u) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			impl(detail::overload_priority<2>{}, bksge::forward<T>(t), bksge::forward<U>(u)))
};

}	// namespace swap_detail

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR swap_detail::swap_fn swap{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_CONCEPTS_SWAP_HPP
