/**
 *	@file	in_fun_result.hpp
 *
 *	@brief	ranges::in_fun_result の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_IN_FUN_RESULT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_IN_FUN_RESULT_HPP

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <typename Iter, typename F>
struct in_fun_result
{
	BKSGE_NO_UNIQUE_ADDRESS Iter in;
	BKSGE_NO_UNIQUE_ADDRESS F    fun;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename Iter2, typename F2>
	requires
		bksge::convertible_to<Iter const&, Iter2> &&
		bksge::convertible_to<F const&, F2>
#else
	template <typename Iter2, typename F2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::convertible_to<Iter const&, Iter2>,
			bksge::convertible_to<F const&, F2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR operator in_fun_result<Iter2, F2>() const&
	{
		return { in, fun };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename Iter2, typename F2>
	requires
		bksge::convertible_to<Iter, Iter2> &&
		bksge::convertible_to<F, F2>
#else
	template <typename Iter2, typename F2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::convertible_to<Iter, Iter2>,
			bksge::convertible_to<F, F2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR operator in_fun_result<Iter2, F2>() &&
	{
		return { std::move(in), std::move(fun) };
	}
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_IN_FUN_RESULT_HPP
