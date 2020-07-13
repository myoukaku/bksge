/**
 *	@file	iter_traits.hpp
 *
 *	@brief	iter_traits の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_TRAITS_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_TRAITS_HPP

#include <bksge/fnd/iterator/concepts/detail/primary_traits_iter.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename Iter, typename T, typename = void>
struct iter_traits_impl
{
	using type = bksge::iterator_traits<Iter>;
};

template <typename Iter, typename T>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires detail::primary_traits_iter<Iter>
#endif
struct iter_traits_impl<Iter, T
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	, bksge::enable_if_t<detail::primary_traits_iter_t<Iter>::value>
#endif
>
{
	using type = T;
};

// ITER_TRAITS
template <typename Iter, typename T = Iter>
using iter_traits = typename iter_traits_impl<Iter, T>::type;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITER_TRAITS_HPP
