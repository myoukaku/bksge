/**
 *	@file	has_iterator_concept.hpp
 *
 *	@brief	has_iterator_concept の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_HAS_ITERATOR_CONCEPT_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_HAS_ITERATOR_CONCEPT_HPP

#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

namespace detail
{

template <typename T, typename = void>
struct has_iterator_concept
	: public bksge::false_type {};

template <typename T>
struct has_iterator_concept<T, bksge::void_t<typename T::iterator_concept>>
	: public bksge::true_type {};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_HAS_ITERATOR_CONCEPT_HPP
