/**
 *	@file	is_destructible.hpp
 *
 *	@brief	is_destructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが破棄可能か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_destructibleは、型Tが破棄可能であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	実行時に評価されない文脈で、オブジェクト型Tに対する式 declval<T&>().~T() が
 *	有効であれば破棄可能、そうでなければ破棄できないと判断される。
 *	以下、オブジェクト型に含まれない型の場合の判断について記載する：
 *	・Tがvoidの場合は破棄できない
 *	・Tが参照型の場合は破棄可能
 *	・Tが関数型の場合は破棄できない
 */
template <typename T>
struct is_destructible
	: public detail::constant_wrapper<
		std::is_destructible<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_destructible_v = is_destructible<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_DESTRUCTIBLE_HPP
