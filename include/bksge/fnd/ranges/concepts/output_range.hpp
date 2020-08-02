/**
 *	@file	output_range.hpp
 *
 *	@brief	output_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_OUTPUT_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_OUTPUT_RANGE_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/iterator/concepts/output_iterator.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Range, typename T>
concept output_range =
	ranges::range<Range> &&
	bksge::output_iterator<ranges::iterator_t<Range>, T>;

#else

template <typename Range, typename T>
struct output_range_impl
{
private:
	template <typename R, typename U>
	static auto test(int) -> bksge::conjunction<
		ranges::range<R>,
		bksge::output_iterator<ranges::iterator_t<R>, U>
	>;

	template <typename R, typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Range, T>(0));
};

template <typename Range, typename T>
using output_range = typename output_range_impl<Range, T>::type;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_OUTPUT_RANGE_HPP
