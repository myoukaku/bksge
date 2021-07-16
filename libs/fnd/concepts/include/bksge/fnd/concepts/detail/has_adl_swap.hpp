/**
 *	@file	has_adl_swap.hpp
 *
 *	@brief	has_adl_swap の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONCEPTS_DETAIL_HAS_ADL_SWAP_HPP
#define BKSGE_FND_CONCEPTS_DETAIL_HAS_ADL_SWAP_HPP

#include <bksge/fnd/concepts/detail/class_or_enum.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace ranges
{

namespace swap_detail
{

template <typename T> void swap(T&, T&) = delete;
template <typename T, std::size_t N> void swap(T(&)[N], T(&)[N]) = delete;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept has_adl_swap =
	(bksge::detail::class_or_enum<bksge::remove_reference_t<T>> ||
	 bksge::detail::class_or_enum<bksge::remove_reference_t<U>>) &&
	requires(T&& t, U&& u)
	{
		swap(bksge::forward<T>(t), bksge::forward<U>(u));
	};

#else

template <typename T, typename U>
struct has_adl_swap_impl
{
private:
	template <typename T2, typename U2,
		typename = decltype(swap(std::declval<T2>(), std::declval<U2>()))
	>
	static auto test(int) -> bksge::disjunction<
		bksge::detail::class_or_enum<bksge::remove_reference_t<T2>>,
		bksge::detail::class_or_enum<bksge::remove_reference_t<U2>>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
using has_adl_swap = typename has_adl_swap_impl<T, U>::type;

#endif

}	// namespace swap_detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_CONCEPTS_DETAIL_HAS_ADL_SWAP_HPP
