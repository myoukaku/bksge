/**
 *	@file	has_value_type.hpp
 *
 *	@brief	has_value_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_HAS_VALUE_TYPE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_HAS_VALUE_TYPE_HPP

#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

namespace detail
{

template <typename, typename = void>
struct has_value_type
	: public bksge::false_type {};
 
template <typename T>
struct has_value_type<T, bksge::void_t<typename T::value_type>>
	: public bksge::true_type {};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_HAS_VALUE_TYPE_HPP
