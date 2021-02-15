/**
 *	@file	is_pointer.hpp
 *
 *	@brief	is_pointer の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_POINTER_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_POINTER_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがポインタ型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_pointerは、型Tがポインタ型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	関数へのポインタはポインタ型であるが、staticではないメンバへのポインタは、ポインタ型ではない。
 *	nullptrはポインタ型へ変換できるが，nullptr_t型はポインタ型ではない。
 */
template <typename T>
struct is_pointer
	: public detail::constant_wrapper<
		std::is_pointer<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_pointer_v = is_pointer<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_POINTER_HPP
