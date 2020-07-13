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

#endif

template <typename Iter>
struct primary_traits_iter_t
	: public bksge::negation<bksge::is_pointer<Iter>> {};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_PRIMARY_TRAITS_ITER_HPP
