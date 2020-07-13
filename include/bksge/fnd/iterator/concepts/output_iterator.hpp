/**
 *	@file	output_iterator.hpp
 *
 *	@brief	output_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter, typename T>
concept output_iterator =
	bksge::input_or_output_iterator<Iter> &&
	bksge::indirectly_writable<Iter, T> &&
	requires(Iter i, T&& t) { *i++ = bksge::forward<T>(t); };

#endif

namespace detail
{

template <typename Iter, typename T>
struct output_iterator_t_impl
{
private:
	template <typename I2, typename T2,
		typename = decltype(*bksge::declval<I2&>()++ = bksge::declval<T2&&>())
	>
	static auto test(int) -> bksge::conjunction<
		bksge::input_or_output_iterator_t<I2>,
		bksge::indirectly_writable_t<I2, T2>
	>;

	template <typename I2, typename T2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter, T>(0));
};

}	// namespace detail

template <typename Iter, typename T>
using output_iterator_t =
	typename detail::output_iterator_t_impl<Iter, T>::type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP
