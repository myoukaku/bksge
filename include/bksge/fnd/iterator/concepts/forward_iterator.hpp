/**
 *	@file	forward_iterator.hpp
 *
 *	@brief	forward_iterator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_FORWARD_ITERATOR_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_FORWARD_ITERATOR_HPP

#include <bksge/fnd/iterator/concepts/input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/incrementable.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/concepts/detail/iter_concept.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept forward_iterator =
	bksge::input_iterator<Iter> &&
	bksge::derived_from<bksge::detail::iter_concept<Iter>, bksge::forward_iterator_tag> &&
	bksge::incrementable<Iter> &&
	bksge::sentinel_for<Iter, Iter>;

#else

namespace detail
{

template <typename Iter>
struct forward_iterator_impl
{
private:
	template <typename I2>
	static auto test(int) -> bksge::conjunction<
		bksge::input_iterator<I2>,
		bksge::derived_from<bksge::detail::iter_concept<I2>, bksge::forward_iterator_tag>,
		bksge::incrementable<I2>,
		bksge::sentinel_for<I2, I2>
	>;

	template <typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace detail

template <typename Iter>
using forward_iterator =
	typename detail::forward_iterator_impl<Iter>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_FORWARD_ITERATOR_HPP
