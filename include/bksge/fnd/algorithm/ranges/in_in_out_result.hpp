/**
 *	@file	in_in_out_result.hpp
 *
 *	@brief	ranges::in_in_out_result の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_IN_IN_OUT_RESULT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_IN_IN_OUT_RESULT_HPP

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

template <typename Iter1, typename Iter2, typename Out>
struct in_in_out_result
{
	BKSGE_NO_UNIQUE_ADDRESS Iter1 in1;
	BKSGE_NO_UNIQUE_ADDRESS Iter2 in2;
	BKSGE_NO_UNIQUE_ADDRESS Out   out;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename IIter1, typename IIter2, typename OOut>
	requires
		bksge::convertible_to<Iter1 const&, IIter1> &&
		bksge::convertible_to<Iter2 const&, IIter2> &&
		bksge::convertible_to<Out const&, OOut>
#else
	template <
		typename IIter1, typename IIter2, typename OOut,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::convertible_to<Iter1 const&, IIter1>,
			bksge::convertible_to<Iter2 const&, IIter2>,
			bksge::convertible_to<Out const&, OOut>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	operator in_in_out_result<IIter1, IIter2, OOut>() const&
	{
		return { in1, in2, out };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename IIter1, typename IIter2, typename OOut>
	requires
		bksge::convertible_to<Iter1, IIter1> &&
		bksge::convertible_to<Iter2, IIter2> &&
		bksge::convertible_to<Out, OOut>
#else
	template <
		typename IIter1, typename IIter2, typename OOut,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::convertible_to<Iter1, IIter1>,
			bksge::convertible_to<Iter2, IIter2>,
			bksge::convertible_to<Out, OOut>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	operator in_in_out_result<IIter1, IIter2, OOut>() &&
	{
		return { bksge::move(in1), bksge::move(in2), bksge::move(out) };
	}
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_IN_IN_OUT_RESULT_HPP
