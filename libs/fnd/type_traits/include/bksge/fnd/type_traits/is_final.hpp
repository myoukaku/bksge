﻿/**
 *	@file	is_final.hpp
 *
 *	@brief	is_final の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_FINAL_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_FINAL_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	型Tにfinalが付いているかを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tがクラス型である場合、その型は完全型でなければならない
 *
 *	is_finalは、型Tがfinal指定されていればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_final;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_final_v = is_final<T>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_final_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_FINAL_HPP
