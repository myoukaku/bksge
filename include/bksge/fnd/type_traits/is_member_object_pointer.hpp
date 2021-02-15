/**
 *	@file	is_member_object_pointer.hpp
 *
 *	@brief	is_member_object_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがデータメンバへのポインタか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_member_object_pointerは、型Tがデータメンバへのポインタであるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	メンバ関数へのポインタはデータメンバへのポインタではない。
 *	staticなデータメンバへのポインタはデータメンバへのポインタではない。
 */
template <typename T>
struct is_member_object_pointer
	: public detail::constant_wrapper<
		std::is_member_object_pointer<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_member_object_pointer_v = is_member_object_pointer<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP
