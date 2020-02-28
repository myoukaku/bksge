﻿/**
 *	@file	is_null_pointer.hpp
 *
 *	@brief	is_null_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NULL_POINTER_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NULL_POINTER_HPP

#include <type_traits>

#if defined(__cpp_lib_is_null_pointer) && (__cpp_lib_is_null_pointer >= 201309)

namespace bksge
{

using std::is_null_pointer;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>

namespace bksge
{

/**
 *	@brief	型Tがnullptr_tか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_null_pointerは、型Tがnullptr_tであれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_null_pointer
	: public std::is_same<
		bksge::remove_cv_t<T>, bksge::nullptr_t
	>
{};

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_IS_NULL_POINTER_HPP
