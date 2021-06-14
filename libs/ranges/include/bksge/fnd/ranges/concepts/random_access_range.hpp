/**
 *	@file	random_access_range.hpp
 *
 *	@brief	random_access_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_RANDOM_ACCESS_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_RANDOM_ACCESS_RANGE_HPP

#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/iterator/concepts/random_access_iterator.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept random_access_range =
	ranges::bidirectional_range<T> &&
	bksge::random_access_iterator<ranges::iterator_t<T>>;

template <typename T>
using is_random_access_range = bksge::bool_constant<random_access_range<T>>;

#else

namespace detail
{

template <typename T>
struct random_access_range_impl
{
private:
	template <typename U,
		typename = bksge::enable_if_t<ranges::bidirectional_range<U>::value>,
		typename = bksge::enable_if_t<bksge::random_access_iterator<ranges::iterator_t<U>>::value>
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using random_access_range = typename ranges::detail::random_access_range_impl<T>::type;

template <typename T>
using is_random_access_range = random_access_range<T>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_RANDOM_ACCESS_RANGE_HPP
