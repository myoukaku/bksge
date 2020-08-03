/**
 *	@file	less.hpp
 *
 *	@brief	less クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_LESS_HPP
#define BKSGE_FND_FUNCTIONAL_LESS_HPP

#include <bksge/fnd/functional/detail/less_builtin_ptr_cmp.hpp>
#include <bksge/fnd/concepts/totally_ordered_with.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>

namespace bksge
{

/**
 *	@brief	左辺が右辺より小さいかの比較を行う関数オブジェクト
 *
 *	@tparam	T
 */
template <typename T = void>
struct less
{
	using result_type          = bool;
	using first_argument_type  = T;
	using second_argument_type = T;

	BKSGE_CONSTEXPR bool operator()(T const& lhs, T const& rhs) const
	{
		return lhs < rhs;
	}
};

/**
 *	@brief	less のテンプレート引数がvoid (デフォルト)の場合の特殊化
 */
template <>
struct less<void>
{
	using is_transparent = void;

	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& lhs, U&& rhs) const
	-> decltype(bksge::forward<T>(lhs) < bksge::forward<U>(rhs))
	{
		return bksge::forward<T>(lhs) < bksge::forward<U>(rhs);
	}
};

namespace ranges
{

/**
 *	@brief	ranges::less
 */
struct less
{
private:
	template <typename T, typename U
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			detail::less_builtin_ptr_cmp_t<T, U>::value
		>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires detail::less_builtin_ptr_cmp<T, U>
#endif
	static BKSGE_CXX14_CONSTEXPR bool impl(bksge::detail::overload_priority<1>, T&& t, U&& u)
		BKSGE_NOEXCEPT_IF_EXPR(bksge::declval<T>() < bksge::declval<U>())
	{
#ifdef __cpp_lib_is_constant_evaluated
		if (std::is_constant_evaluated())
		{
			return t < u;
		}
#endif
		auto x = reinterpret_cast<std::uintptr_t>(
			static_cast<const volatile void*>(bksge::forward<T>(t)));
		auto y = reinterpret_cast<std::uintptr_t>(
			static_cast<const volatile void*>(bksge::forward<U>(u)));
		return x < y;
	}

	template <typename T, typename U
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<
			bksge::totally_ordered_with<T, U>::value
		>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires bksge::totally_ordered_with<T, U>
#endif
	static BKSGE_CONSTEXPR bool impl(bksge::detail::overload_priority<0>, T&& t, U&& u)
		BKSGE_NOEXCEPT_IF_EXPR(bksge::declval<T>() < bksge::declval<U>())
	{
		return bksge::forward<T>(t) < bksge::forward<U>(u);
	}

public:
	template <typename T, typename U>
	BKSGE_CONSTEXPR auto operator()(T&& t, U&& u) const
		BKSGE_NOEXCEPT_IF_EXPR(impl(bksge::detail::overload_priority<1>{}, bksge::forward<T>(t), bksge::forward<U>(u)))
	->decltype(impl(bksge::detail::overload_priority<1>{}, bksge::forward<T>(t), bksge::forward<U>(u)))
	{
		return impl(bksge::detail::overload_priority<1>{}, bksge::forward<T>(t), bksge::forward<U>(u));
	}

	using is_transparent = void;
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_LESS_HPP
