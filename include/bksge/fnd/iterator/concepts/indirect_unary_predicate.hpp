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
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
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

template <typename F, typename I>
using is_indirect_unary_predicate = bksge::bool_constant<indirect_unary_predicate<F, I>>;

#else

namespace detail
{

template <typename F, typename I>
struct indirect_unary_predicate_impl
{
private:
	template <typename F2, typename I2,
		typename = bksge::enable_if_t<bksge::conjunction<
			bksge::indirectly_readable<I2>,
			bksge::copy_constructible<F2>,
			bksge::predicate<F2&, bksge::iter_value_t<I2>&>,
			bksge::predicate<F2&, bksge::iter_reference_t<I2>>,
			bksge::predicate<F2&, bksge::iter_common_reference_t<I2>>
		>::value>
	>
	static auto test(int) -> bksge::true_type;

	template <typename F2, typename I2>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<F, I>(0));
};

}	// namespace detail

template <typename F, typename I>
using indirect_unary_predicate =
	typename detail::indirect_unary_predicate_impl<F, I>::type;

template <typename F, typename I>
using is_indirect_unary_predicate = indirect_unary_predicate<F, I>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_INDIRECT_UNARY_PREDICATE_HPP
