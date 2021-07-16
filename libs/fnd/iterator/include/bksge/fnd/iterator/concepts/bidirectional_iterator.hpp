/**
 *	@file	bidirectional_iterator.hpp
 *
 *	@brief	bidirectional_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/forward_iterator.hpp>
#include <bksge/fnd/iterator/concepts/detail/iter_concept.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept bidirectional_iterator =
	bksge::forward_iterator<Iter> &&
	bksge::derived_from<
		bksge::detail::iter_concept<Iter>,
		bksge::bidirectional_iterator_tag> &&
	requires(Iter i)
	{
		{ --i } -> bksge::same_as<Iter&>;
		{ i-- } -> bksge::same_as<Iter>;
	};

template <typename Iter>
using is_bidirectional_iterator = bksge::bool_constant<bidirectional_iterator<Iter>>;

#else

namespace detail
{

template <typename Iter>
struct bidirectional_iterator_impl
{
private:
	template <typename I2,
		typename = bksge::enable_if_t<
			bksge::forward_iterator<I2>::value
		>,
		typename = bksge::enable_if_t<
			bksge::derived_from<
				bksge::detail::iter_concept<I2>,
				bksge::bidirectional_iterator_tag
			>::value
		>,
		typename T1 = decltype(--std::declval<I2&>()),
		typename T2 = decltype(  std::declval<I2&>()--)
	>
	static auto test(int) -> bksge::conjunction<
		bksge::same_as<T1, I2&>,
		bksge::same_as<T2, I2>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using bidirectional_iterator =
	typename detail::bidirectional_iterator_impl<Iter>::type;

template <typename Iter>
using is_bidirectional_iterator = bidirectional_iterator<Iter>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP
