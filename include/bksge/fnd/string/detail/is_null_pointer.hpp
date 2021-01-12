/**
 *	@file	is_null_pointer.hpp
 *
 *	@brief	is_null_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_DETAIL_IS_NULL_POINTER_HPP
#define BKSGE_FND_STRING_DETAIL_IS_NULL_POINTER_HPP

#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR bool
is_null_pointer(T* ptr)
{
	return ptr == 0;
}

template <typename T>
inline BKSGE_CONSTEXPR bool
is_null_pointer(T)
{
	return false;
}

inline BKSGE_CONSTEXPR bool
is_null_pointer(bksge::nullptr_t)
{
	return true;
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STRING_DETAIL_IS_NULL_POINTER_HPP
