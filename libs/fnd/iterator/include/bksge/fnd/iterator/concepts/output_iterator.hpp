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
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter, typename T>
concept output_iterator =
	bksge::input_or_output_iterator<Iter> &&
	bksge::indirectly_writable<Iter, T> &&
	requires(Iter i, T&& t) { *i++ = bksge::forward<T>(t); };

#else

namespace detail
{

template <typename Iter, typename T>
struct output_iterator_impl
{
private:
	template <typename I2, typename T2,
		typename = bksge::enable_if_t<bksge::input_or_output_iterator<I2>::value>,
		typename = bksge::enable_if_t<bksge::indirectly_writable<I2, T2>::value>,
		typename = decltype(*std::declval<I2&>()++ = std::declval<T2&&>())
	>
	static auto test(int) -> bksge::true_type;

	template <typename I2, typename T2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter, T>(0));
};

}	// namespace detail

template <typename Iter, typename T>
using output_iterator =
	typename detail::output_iterator_impl<Iter, T>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_OUTPUT_ITERATOR_HPP
