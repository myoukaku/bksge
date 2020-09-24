/**
 *	@file	range.hpp
 *
 *	@brief	range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_RANGE_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept range =
	requires(T& t)
	{
		ranges::begin(t);
		ranges::end(t);
	};

template <typename T>
using is_range = bksge::bool_constant<range<T>>;

#else

template <typename T>
struct range_impl
{
private:
	template <typename U,
		typename = decltype(ranges::begin(bksge::declval<U&>())),
		typename = decltype(ranges::end(bksge::declval<U&>()))
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using range = typename range_impl<T>::type;

template <typename T>
using is_range = range<T>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_RANGE_HPP
