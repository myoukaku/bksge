/**
 *	@file	primary_traits_iter.hpp
 *
 *	@brief	primary_traits_iter の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_PRIMARY_TRAITS_ITER_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_PRIMARY_TRAITS_ITER_HPP

#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept primary_traits_iter =
	!bksge::is_pointer<Iter>::value;	// TODO

#else

template <typename Iter>
using primary_traits_iter =
	bksge::negation<bksge::is_pointer<Iter>>;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_PRIMARY_TRAITS_ITER_HPP
