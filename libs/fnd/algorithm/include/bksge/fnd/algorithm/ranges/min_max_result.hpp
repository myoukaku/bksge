/**
 *	@file	min_max_result.hpp
 *
 *	@brief	ranges::min_max_result の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_MIN_MAX_RESULT_HPP
#define BKSGE_FND_ALGORITHM_RANGES_MIN_MAX_RESULT_HPP

#include <bksge/fnd/concepts/convertible_to.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

template <typename T>
struct min_max_result
{
	BKSGE_NO_UNIQUE_ADDRESS T min;
	BKSGE_NO_UNIQUE_ADDRESS T max;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename T2>
	requires bksge::convertible_to<T const&, T2>
#else
	template <typename T2,
		typename = bksge::enable_if_t<
			bksge::convertible_to<T const&, T2>::value
		>
	>
#endif
	BKSGE_CXX14_CONSTEXPR operator min_max_result<T2>() const&
	{
		return { min, max };
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <typename T2>
	requires bksge::convertible_to<T, T2>
#else
	template <typename T2,
		typename = bksge::enable_if_t<
			bksge::convertible_to<T, T2>::value
		>
	>
#endif
	BKSGE_CXX14_CONSTEXPR operator min_max_result<T2>() &&
	{
		return { std::move(min), std::move(max) };
	}
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_MIN_MAX_RESULT_HPP
