/**
 *	@file	indirect_unary_predicate.hpp
 *
 *	@brief	indirect_unary_predicate の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_INDIRECT_UNARY_PREDICATE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_INDIRECT_UNARY_PREDICATE_HPP

#include <bksge/fnd/iterator/concepts/indirectly_readable.hpp>
#include <bksge/fnd/iterator/iter_value_t.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/iter_common_reference_t.hpp>
#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/concepts/predicate.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename F, typename I>
concept indirect_unary_predicate =
	bksge::indirectly_readable<I> &&
	bksge::copy_constructible<F> &&
	bksge::predicate<F&, bksge::iter_value_t<I>&> &&
	bksge::predicate<F&, bksge::iter_reference_t<I>> &&
	bksge::predicate<F&, bksge::iter_common_reference_t<I>>;

#endif

namespace detail
{

template <typename F, typename I>
struct indirect_unary_predicate_t_impl
{
private:
	template <typename F2, typename I2>
	static auto test(int) -> bksge::conjunction<
		bksge::indirectly_readable_t<I2>,
		bksge::copy_constructible_t<F2>,
		bksge::predicate_t<F2&, bksge::iter_value_t<I2>&>,
		bksge::predicate_t<F2&, bksge::iter_reference_t<I2>>,
		bksge::predicate_t<F2&, bksge::iter_common_reference_t<I2>>
	>;

	template <typename F2, typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<F, I>(0));
};

}	// namespace detail

template <typename F, typename I>
using indirect_unary_predicate_t =
	typename detail::indirect_unary_predicate_t_impl<F, I>::type;

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECT_UNARY_PREDICATE_HPP
