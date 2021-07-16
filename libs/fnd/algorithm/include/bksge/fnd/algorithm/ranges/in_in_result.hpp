/**
 *	@file	in_in_result.hpp
 *
 *	@brief	ranges::in_in_result の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_IN_IN_RESULT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_IN_IN_RESULT_HPP

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <typename Iter1, typename Iter2>
struct in_in_result
{
	BKSGE_NO_UNIQUE_ADDRESS Iter1 in1;
	BKSGE_NO_UNIQUE_ADDRESS Iter2 in2;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename IIter1, typename IIter2>
	requires
		bksge::convertible_to<Iter1 const&, IIter1> &&
		bksge::convertible_to<Iter2 const&, IIter2>
#else
	template <typename IIter1, typename IIter2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::convertible_to<Iter1 const&, IIter1>,
			bksge::convertible_to<Iter2 const&, IIter2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR operator in_in_result<IIter1, IIter2>() const&
	{
		return { in1, in2 };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename IIter1, typename IIter2>
	requires
		bksge::convertible_to<Iter1, IIter1> &&
		bksge::convertible_to<Iter2, IIter2>
#else
	template <typename IIter1, typename IIter2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::convertible_to<Iter1, IIter1>,
			bksge::convertible_to<Iter2, IIter2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR operator in_in_result<IIter1, IIter2>() &&
	{
		return { std::move(in1), std::move(in2) };
	}
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_IN_IN_RESULT_HPP
