/**
 *	@file	forward_range.hpp
 *
 *	@brief	forward_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_FORWARD_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_FORWARD_RANGE_HPP

#include <bksge/fnd/ranges/concepts/input_range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept forward_range =
	ranges::input_range<T> &&
	bksge::forward_iterator<ranges::iterator_t<T>>;

template <typename T>
using is_forward_range = bksge::bool_constant<forward_range<T>>;

#else

template <typename T>
struct forward_range_impl
{
private:
	template <typename U>
	static auto test(int) -> bksge::conjunction<
		ranges::input_range<U>,
		bksge::forward_iterator<ranges::iterator_t<U>>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using forward_range = typename forward_range_impl<T>::type;

template <typename T>
using is_forward_range = forward_range<T>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_FORWARD_RANGE_HPP
