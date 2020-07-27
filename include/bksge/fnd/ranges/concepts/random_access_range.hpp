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
#include <bksge/fnd/type_traits/conjunction.hpp>
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

#else

template <typename T>
struct random_access_range_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		ranges::bidirectional_range<U>,
		bksge::random_access_iterator_t<ranges::iterator_t<U>>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using random_access_range = typename random_access_range_impl<T>::type;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_RANDOM_ACCESS_RANGE_HPP
