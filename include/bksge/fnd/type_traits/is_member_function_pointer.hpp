/**
 *	@file	is_member_function_pointer.hpp
 *
 *	@brief	is_member_function_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがメンバ関数へのポインタか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_member_function_pointerは、型Tがメンバ関数へのポインタであるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	データメンバへのポインタはメンバ関数へのポインタではない。
 *	staticなメンバ関数へのポインタはメンバ関数へのポインタではない。
 */
template <typename T>
struct is_member_function_pointer
	: public detail::constant_wrapper<
		std::is_member_function_pointer<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_member_function_pointer_v = is_member_function_pointer<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP
