﻿/**
 *	@file	is_rvalue_reference.hpp
 *
 *	@brief	is_rvalue_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが右辺値参照型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_rvalue_referenceは、型Tが右辺値参照型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_rvalue_reference
	: public detail::constant_wrapper<
		std::is_rvalue_reference<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
