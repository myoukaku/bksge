﻿/**
 *	@file	input_or_output_iterator.hpp
 *
 *	@brief	input_or_output_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INPUT_OR_OUTPUT_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INPUT_OR_OUTPUT_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/weakly_incrementable.hpp>
#include <bksge/fnd/iterator/concepts/detail/can_reference.hpp>
#include <bksge/fnd/iterator/concepts/detail/is_void_pointer.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept input_or_output_iterator =
	requires(Iter i) { { *i } -> bksge::detail::can_reference; } &&
	bksge::weakly_incrementable<Iter>;

#else

namespace detail
{

template <typename Iter>
struct input_or_output_iterator_impl
{
private:
	template <typename I2, typename = bksge::enable_if_t<!bksge::detail::is_void_pointer<I2>::value>>
	static auto test(int) -> bksge::conjunction<
		bksge::detail::can_reference<decltype(*bksge::declval<I2&>())>,
		bksge::weakly_incrementable<I2>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using input_or_output_iterator =
	typename detail::input_or_output_iterator_impl<Iter>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INPUT_OR_OUTPUT_ITERATOR_HPP