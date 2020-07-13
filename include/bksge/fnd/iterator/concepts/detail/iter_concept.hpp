/**
 *	@file	iter_concept.hpp
 *
 *	@brief	iter_concept の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_CONCEPT_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_CONCEPT_HPP

#include <bksge/fnd/iterator/concepts/detail/iter_traits.hpp>
#include <bksge/fnd/iterator/concepts/detail/primary_traits_iter.hpp>
#include <bksge/fnd/iterator/concepts/detail/has_iterator_category.hpp>
#include <bksge/fnd/iterator/concepts/detail/has_iterator_concept.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace iter_concept_detail
{

template <typename Iter, typename = void>
struct iter_concept_impl;

// ITER_CONCEPT(I) is ITER_TRAITS(I)::iterator_concept if that is valid.
template <typename Iter>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires requires { typename detail::iter_traits<Iter>::iterator_concept; }
#endif
struct iter_concept_impl<Iter
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	, bksge::enable_if_t<
		has_iterator_concept<detail::iter_traits<Iter>>::value
	>
#endif
>
{
	using type = typename detail::iter_traits<Iter>::iterator_concept;
};

// Otherwise, ITER_TRAITS(I)::iterator_category if that is valid.
template <typename Iter>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires (
	!requires { typename detail::iter_traits<Iter>::iterator_concept; } &&
	 requires { typename detail::iter_traits<Iter>::iterator_category; })
#endif
struct iter_concept_impl<Iter
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	, bksge::enable_if_t<
		!has_iterator_concept<detail::iter_traits<Iter>>::value &&
		 has_iterator_category<detail::iter_traits<Iter>>::value
	>
#endif
>
{
	using type = typename detail::iter_traits<Iter>::iterator_category;
};

// Otherwise, random_access_tag if iterator_traits<I> is not specialized.
template <typename Iter>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires (
	!requires { typename detail::iter_traits<Iter>::iterator_concept; } &&
	!requires { typename detail::iter_traits<Iter>::iterator_category; } &&
	detail::primary_traits_iter<Iter>)
#endif
struct iter_concept_impl<Iter
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	, bksge::enable_if_t<
		!has_iterator_concept<detail::iter_traits<Iter>>::value &&
		!has_iterator_category<detail::iter_traits<Iter>>::value &&
		detail::primary_traits_iter_t<Iter>::value
	>
#endif
>
{
	using type = bksge::random_access_iterator_tag;
};

// Otherwise, there is no ITER_CONCEPT(I) type.
template <typename Iter, typename>
struct iter_concept_impl
{};

}	// namespace iter_concept_detail

// ITER_CONCEPT
template <typename Iter>
using iter_concept = typename iter_concept_detail::iter_concept_impl<Iter>::type;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_CONCEPT_HPP
