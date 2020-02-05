/**
 *	@file	has_iterator_category.hpp
 *
 *	@brief	has_iterator_category の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_TYPE_TRAITS_DETAIL_HAS_ITERATOR_CATEGORY_HPP
#define BKSGE_FND_ITERATOR_TYPE_TRAITS_DETAIL_HAS_ITERATOR_CATEGORY_HPP

#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

namespace detail
{

template <typename, typename = bksge::void_t<>>
struct has_iterator_category
	: public bksge::false_type {};
 
template <typename T>
struct has_iterator_category<T, bksge::void_t<typename T::iterator_category>>
	: public bksge::true_type {};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_TYPE_TRAITS_DETAIL_HAS_ITERATOR_CATEGORY_HPP
