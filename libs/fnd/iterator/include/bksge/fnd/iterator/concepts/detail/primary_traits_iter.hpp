/**
 *	@file	primary_traits_iter.hpp
 *
 *	@brief	primary_traits_iter の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_PRIMARY_TRAITS_ITER_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_PRIMARY_TRAITS_ITER_HPP

#include <bksge/fnd/iterator/concepts/detail/is_iterator_traits_specialized.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept primary_traits_iter =
	!detail::is_iterator_traits_specialized<Iter>::value;

#else

template <typename Iter>
using primary_traits_iter =
	bksge::bool_constant<!detail::is_iterator_traits_specialized<Iter>::value>;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_PRIMARY_TRAITS_ITER_HPP
