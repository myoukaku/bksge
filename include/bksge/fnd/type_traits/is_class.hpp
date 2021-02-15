/**
 *	@file	is_class.hpp
 *
 *	@brief	is_class の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_CLASS_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_CLASS_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがクラス型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_classは、型Tがクラス型であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	型Tがunion、enum、enum classの場合、is_classはfalse_typeから派生する。
 */
template <typename T>
struct is_class
	: public detail::constant_wrapper<
		std::is_class<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_class_v = is_class<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_CLASS_HPP
