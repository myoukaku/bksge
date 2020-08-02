/**
 *	@file	bidirectional_range.hpp
 *
 *	@brief	bidirectional_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_BIDIRECTIONAL_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_BIDIRECTIONAL_RANGE_HPP

#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/iterator/concepts/bidirectional_iterator.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept bidirectional_range =
	ranges::forward_range<T> &&
	bksge::bidirectional_iterator<ranges::iterator_t<T>>;

#else

template <typename T>
struct bidirectional_range_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		ranges::forward_range<U>,
		bksge::bidirectional_iterator<ranges::iterator_t<U>>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using bidirectional_range = typename bidirectional_range_impl<T>::type;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_BIDIRECTIONAL_RANGE_HPP
