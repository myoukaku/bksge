/**
 *	@file	is_nothrow_convertible.hpp
 *
 *	@brief	is_nothrow_convertible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief		型Fromから型Toに例外を投げずに暗黙的に変換可能か調べる。
 *
 *	@tparam		From	変換元の型
 *	@tparam		To		変換先の型
 *
 *	@require	型Fromと型Toは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_nothrow_convertibleは、型Fromから型Toに例外を投げずに暗黙的に変換可能であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	return文による型変換、および非explicitなコンストラクタによる型変換は、暗黙的に変換可能であるとみなされる。
 *	explicitなコンストラクタによる明示的な型変換は、暗黙的に変換可能であるとは見なされない。
 */
template <typename From, typename To>
struct is_nothrow_convertible;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename From, typename To>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_nothrow_convertible_v = is_nothrow_convertible<From, To>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_nothrow_convertible_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_HPP
