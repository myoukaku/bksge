/**
 *	@file	is_default_constructible.hpp
 *
 *	@brief	is_default_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	型Tがデフォルト構築可能か調べる。
 *
 *	@tparam		T		チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_default_constructibleは、型Tがデフォルトコンストラクト可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	is_constructible<T>::value == trueの時に、デフォルト構築可能であると判断される。
 */
template <typename T>
struct is_default_constructible;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_default_constructible_v = is_default_constructible<T>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_default_constructible_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
