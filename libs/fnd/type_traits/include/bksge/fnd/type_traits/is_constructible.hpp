/**
 *	@file	is_constructible.hpp
 *
 *	@brief	is_constructible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	型Tのコンストラクタ呼出しが適格か調べる。
 *
 *	@tparam		T		チェックする型
 *	@tparam		Args...	パラメータパック
 *
 *	@require	型TおよびパラメータパックArgs...のすべての型は、完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない。
 *
 *	is_constructibleは、T obj(std::declval<Args>()...);の形式の変数定義が適格であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	注意：MSVC2013では、std::is_constructibleが正しい値を返さないうえに、
 *	Expression SFINAE が実装されていないので、完璧なis_constructibleを実装することは不可能。
 *	できるだけ正しい値を返すようにする。
 *	MSVC2015 Update1 ではExpression SFINAEが部分的に実装されたので、
 *	自前で実装することはおそらく可能。 : TODO
 */
template <typename T, typename... Args>
struct is_constructible;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename... Args>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_constructible_v = is_constructible<T, Args...>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_constructible_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
