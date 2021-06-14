/**
 *	@file	has_pointer.hpp
 *
 *	@brief	has_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_HAS_POINTER_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_HAS_POINTER_HPP

#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>

namespace bksge
{

namespace detail
{

template <typename, typename = void>
struct has_pointer
	: public bksge::false_type {};
 
template <typename T>
struct has_pointer<T, bksge::void_t<typename T::pointer>>
	: public bksge::true_type {};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_HAS_POINTER_HPP
