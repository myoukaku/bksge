/**
 *	@file	in_out_result.hpp
 *
 *	@brief	ranges::in_out_result の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_IN_OUT_RESULT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_IN_OUT_RESULT_HPP

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <typename Iter, typename Out>
struct in_out_result
{
	BKSGE_NO_UNIQUE_ADDRESS Iter in;
	BKSGE_NO_UNIQUE_ADDRESS Out  out;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename Iter2, typename Out2>
	requires
		bksge::convertible_to<Iter const&, Iter2> &&
		bksge::convertible_to<Out const&, Out2>
#else
	template <typename Iter2, typename Out2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::convertible_to<Iter const&, Iter2>,
			bksge::convertible_to<Out const&, Out2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR operator in_out_result<Iter2, Out2>() const&
	{
		return { in, out };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename Iter2, typename Out2>
	requires
		bksge::convertible_to<Iter, Iter2> &&
		bksge::convertible_to<Out, Out2>
#else
	template <typename Iter2, typename Out2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::convertible_to<Iter, Iter2>,
			bksge::convertible_to<Out, Out2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR operator in_out_result<Iter2, Out2>() &&
	{
		return { bksge::move(in), bksge::move(out) };
	}
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_IN_OUT_RESULT_HPP
