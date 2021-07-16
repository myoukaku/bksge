/**
 *	@file	in_out_out_result.hpp
 *
 *	@brief	ranges::in_out_out_result の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_IN_OUT_OUT_RESULT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_IN_OUT_OUT_RESULT_HPP

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <typename Iter, typename Out1, typename Out2>
struct in_out_out_result
{
	BKSGE_NO_UNIQUE_ADDRESS Iter in;
	BKSGE_NO_UNIQUE_ADDRESS Out1 out1;
	BKSGE_NO_UNIQUE_ADDRESS Out2 out2;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename IIter, typename OOut1, typename OOut2>
	requires
		bksge::convertible_to<const Iter&, IIter> &&
		bksge::convertible_to<const Out1&, OOut1> &&
		bksge::convertible_to<const Out2&, OOut2>
#else
	template <
		typename IIter, typename OOut1, typename OOut2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::convertible_to<const Iter&, IIter>,
			bksge::convertible_to<const Out1&, OOut1>,
			bksge::convertible_to<const Out2&, OOut2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	operator in_out_out_result<IIter, OOut1, OOut2>() const&
	{
		return { in, out1, out2 };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename IIter, typename OOut1, typename OOut2>
	requires
		bksge::convertible_to<Iter, IIter> &&
		bksge::convertible_to<Out1, OOut1> &&
		bksge::convertible_to<Out2, OOut2>
#else
	template <
		typename IIter, typename OOut1, typename OOut2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::convertible_to<Iter, IIter>,
			bksge::convertible_to<Out1, OOut1>,
			bksge::convertible_to<Out2, OOut2>
		>::value>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	operator in_out_out_result<IIter, OOut1, OOut2>() &&
	{
		return { std::move(in), std::move(out1), std::move(out2) };
	}
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_IN_OUT_OUT_RESULT_HPP
