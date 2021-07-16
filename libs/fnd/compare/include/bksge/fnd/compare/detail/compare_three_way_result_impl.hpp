/**
 *	@file	compare_three_way_result_impl.hpp
 *
 *	@brief	compare_three_way_result_impl の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_COMPARE_THREE_WAY_RESULT_IMPL_HPP
#define BKSGE_FND_COMPARE_DETAIL_COMPARE_THREE_WAY_RESULT_IMPL_HPP

#include <bksge/fnd/concepts/detail/cref.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, typename U>
using cmp3way_res_t =
	decltype(std::declval<T>() <=> std::declval<U>());

// Implementation of std::compare_three_way_result.
// It is undefined for a program to add specializations of
// std::compare_three_way_result, so the std::compare_three_way_result_t
// alias ignores std::compare_three_way_result and uses
// detail::compare_three_way_result_impl directly instead.
template <typename T, typename U>
struct compare_three_way_result_impl
{};

template <typename T, typename U>
requires requires { typename cmp3way_res_t<bksge::detail::cref<T>, bksge::detail::cref<U>>; }
struct compare_three_way_result_impl<T, U>
{
	using type = cmp3way_res_t<bksge::detail::cref<T>, bksge::detail::cref<U>>;
};

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_COMPARE_THREE_WAY_RESULT_IMPL_HPP
