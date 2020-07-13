/**
 *	@file	is_void_pointer.hpp
 *
 *	@brief	is_void_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_IS_VOID_POINTER_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_IS_VOID_POINTER_HPP

#include <bksge/fnd/type_traits/remove_pointer.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
using is_void_pointer = bksge::is_void<bksge::remove_pointer_t<T>>;

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_IS_VOID_POINTER_HPP
