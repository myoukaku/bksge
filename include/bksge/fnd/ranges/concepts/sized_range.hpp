/**
 *	@file	sized_range.hpp
 *
 *	@brief	sized_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_SIZED_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_SIZED_RANGE_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept sized_range =
	ranges::range<T> &&
	requires(T& t) { ranges::size(t); };

template <typename T>
concept not_sized_range = !sized_range<T>;

template <typename T>
using is_sized_range = bksge::bool_constant<sized_range<T>>;

#else

template <typename T>
struct sized_range_impl
{
private:
	template <typename U,
		typename = bksge::enable_if_t<ranges::range<U>::value>,
		typename = decltype(ranges::size(bksge::declval<U&>()))
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using sized_range = typename sized_range_impl<T>::type;

template <typename T>
using not_sized_range = bksge::negation<sized_range<T>>;

template <typename T>
using is_sized_range = sized_range<T>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_SIZED_RANGE_HPP
