/**
 *	@file	input_range.hpp
 *
 *	@brief	input_range の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_CONCEPTS_INPUT_RANGE_HPP
#define BKSGE_FND_RANGES_CONCEPTS_INPUT_RANGE_HPP

#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept input_range =
	ranges::range<T> &&
	bksge::input_iterator<ranges::iterator_t<T>>;

template <typename T>
using is_input_range = bksge::bool_constant<input_range<T>>;

#else

namespace detail
{

template <typename T>
struct input_range_impl
{
private:
	template <typename U,
		typename = bksge::enable_if_t<ranges::range<U>::value>,
		typename = bksge::enable_if_t<bksge::input_iterator<ranges::iterator_t<U>>::value>
	>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using input_range = typename ranges::detail::input_range_impl<T>::type;

template <typename T>
using is_input_range = input_range<T>;

#endif

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_CONCEPTS_INPUT_RANGE_HPP
