﻿/**
 *	@file	is_null_pointer.hpp
 *
 *	@brief	is_null_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NULL_POINTER_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NULL_POINTER_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_null_pointer) && (__cpp_lib_is_null_pointer >= 201309)

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>

namespace bksge
{

template <typename T>
struct is_null_pointer
	: public detail::constant_wrapper<
		std::is_null_pointer<T>
	>
{};

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/is_same.hpp>
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
	: public bksge::is_same<
		bksge::remove_cv_t<T>, bksge::nullptr_t
	>
{};

}	// namespace bksge

#endif

namespace bksge
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_null_pointer_v = is_null_pointer<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_NULL_POINTER_HPP
