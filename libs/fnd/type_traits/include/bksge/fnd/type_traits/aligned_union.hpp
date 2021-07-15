/**
 *	@file	aligned_union.hpp
 *
 *	@brief	aligned_union の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_ALIGNED_UNION_HPP
#define BKSGE_FND_TYPE_TRAITS_ALIGNED_UNION_HPP

#include <type_traits>
#include <cstddef>

namespace bksge
{

/**
 *	@brief		アラインメント調整された共用体領域を作る
 *
 *	@tparam		Len			領域サイズ
 *	@tparam		Types...	要素型列
 *
 *	@require	Types...に、1個以上の型が与えられること。
 *
 *	aligned_unionは、領域サイズLen、要素型列Types...で調整した未初期化の共用体領域をメンバ型typeとして定義する。
 *	Types...のいずれかの型が非POD型だとしても、メンバ型typeはPOD型となる(参照：is_pod)。
 *
 *	また、Types...全ての厳格なアラインメント値を、std::size_t型の静的メンバ定数alignment_valueとして定義する。
 */
using std::aligned_union;

/**
 *	@brief	aligned_unionのエイリアステンプレート
 */
template <std::size_t Len, typename... Types>
using aligned_union_t = typename aligned_union<Len, Types...>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_ALIGNED_UNION_HPP
