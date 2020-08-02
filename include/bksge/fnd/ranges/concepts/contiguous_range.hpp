/**
 *	@file	contiguous_range.hpp
 *
 *	@brief	contiguous_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_CONTIGUOUS_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_CONTIGUOUS_RANGE_HPP

#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/data.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/range_reference_t.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/iterator/concepts/contiguous_iterator.hpp>
#include <bksge/fnd/type_traits/add_pointer.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept contiguous_range =
	ranges::random_access_range<T> &&
	bksge::contiguous_iterator<ranges::iterator_t<T>> &&
	requires(T& t)
	{
		{ ranges::data(t) } -> bksge::same_as<bksge::add_pointer_t<ranges::range_reference_t<T>>>;
	};

#else

template <typename T>
struct contiguous_range_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		ranges::random_access_range<U>,
		bksge::contiguous_iterator<ranges::iterator_t<U>>,
		bksge::same_as_t<decltype(ranges::data(bksge::declval<U&>())), bksge::add_pointer_t<ranges::range_reference_t<U>>>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using contiguous_range = typename contiguous_range_impl<T>::type;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_CONTIGUOUS_RANGE_HPP
