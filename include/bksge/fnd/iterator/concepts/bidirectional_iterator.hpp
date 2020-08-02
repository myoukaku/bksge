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
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept bidirectional_iterator =
	bksge::forward_iterator<Iter> &&
	bksge::derived_from<bksge::detail::iter_concept<Iter>, bksge::bidirectional_iterator_tag> &&
	requires(Iter i)
	{
		{ --i } -> bksge::same_as<Iter&>;
		{ i-- } -> bksge::same_as<Iter>;
	};

#else

namespace detail
{

template <typename Iter>
struct bidirectional_iterator_impl
{
private:
	template <typename I2>
	static auto test(int) -> bksge::conjunction<
		bksge::forward_iterator<I2>,
		bksge::derived_from_t<bksge::detail::iter_concept<I2>, bksge::bidirectional_iterator_tag>,
		bksge::same_as_t<decltype(--bksge::declval<I2&>()),   I2&>,
		bksge::same_as_t<decltype(  bksge::declval<I2&>()--), I2>
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

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_BIDIRECTIONAL_ITERATOR_HPP
