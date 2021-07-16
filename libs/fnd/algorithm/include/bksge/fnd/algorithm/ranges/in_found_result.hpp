/**
 *	@file	in_found_result.hpp
 *
 *	@brief	ranges::in_found_result の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_IN_FOUND_RESULT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_IN_FOUND_RESULT_HPP

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <typename Iter>
struct in_found_result
{
	BKSGE_NO_UNIQUE_ADDRESS Iter in;
	bool found;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename Iter2>
	requires bksge::convertible_to<Iter const&, Iter2>
#else
	template <typename Iter2,
		typename = bksge::enable_if_t<
			bksge::convertible_to<Iter const&, Iter2>::value
		>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	operator in_found_result<Iter2>() const&
	{
		return { in, found };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename Iter2>
	requires bksge::convertible_to<Iter, Iter2>
#else
	template <typename Iter2,
		typename = bksge::enable_if_t<
			bksge::convertible_to<Iter, Iter2>::value
		>
	>
#endif
	BKSGE_CXX14_CONSTEXPR
	operator in_found_result<Iter2>()&&
	{
		return { std::move(in), found };
	}
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_IN_FOUND_RESULT_HPP
