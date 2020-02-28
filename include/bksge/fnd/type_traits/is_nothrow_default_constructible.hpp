/**
 *	@file	is_nothrow_default_constructible.hpp
 *
 *	@brief	is_nothrow_default_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP

namespace bksge
{

/**
 *	@brief	型Tがデフォルト構築でき、かつそのデフォルトコンストラクタが例外を投げないか調べる
 *
 *	@tparam		T		チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_nothrow_default_constructibleは、型Tが例外を投げない保証のもとにデフォルト構築可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	is_nothrow_constructible<T>::value == trueの場合に、例外を投げないデフォルト構築が可能であると判断される。
 */
template <typename T>
struct is_nothrow_default_constructible;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_nothrow_default_constructible_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE_HPP
