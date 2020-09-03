/**
 *	@file	input_iterator.hpp
 *
 *	@brief	input_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INPUT_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INPUT_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/concepts/detail/iter_concept.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept input_iterator =
	bksge::input_or_output_iterator<Iter> &&
	bksge::indirectly_readable<Iter> &&
	requires { typename bksge::detail::iter_concept<Iter>; } &&
	bksge::derived_from<bksge::detail::iter_concept<Iter>, bksge::input_iterator_tag>;

template <typename Iter>
using is_input_iterator = bksge::bool_constant<input_iterator<Iter>>;

#else

namespace detail
{

template <typename Iter>
struct input_iterator_impl
{
private:
	template <typename I2>
	static auto test(int) -> bksge::conjunction<
		bksge::input_or_output_iterator<I2>,
		bksge::indirectly_readable<I2>,
		bksge::derived_from<bksge::detail::iter_concept<I2>, bksge::input_iterator_tag>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using input_iterator =
	typename detail::input_iterator_impl<Iter>::type;

template <typename Iter>
using is_input_iterator = input_iterator<Iter>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INPUT_ITERATOR_HPP
