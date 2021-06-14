/**
 *	@file	enable_if.hpp
 *
 *	@brief	enable_if の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_ENABLE_IF_HPP
#define BKSGE_FND_TYPE_TRAITS_ENABLE_IF_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief	コンパイル時条件式が真の場合のみ有効な型。
 *
 *	@tparam	Condition	条件式
 *	@tparam	T			条件式が真の場合の型
 *
 *	enable_ifは、Conditionがtrueの場合のみ、型Tをメンバ型typeとして定義する。
 *	そうでなければenable_ifは、メンバ型typeを持たない。
 *
 *	enable_ifは、SFINAEと組み合わせて使用する。
 *	関数のパラメータ、戻り値型、デフォルトテンプレートパラメータ等のいずれかで
 *	enable_ifのメンバ型typeを使用することにより、テンプレートの置き換え失敗が発生し、
 *	SFINAEによってその関数がオーバーロード解決の候補から除外される。
 */
using std::enable_if;

template <bool Condition, typename T = void>
using enable_if_t = typename enable_if<Condition, T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_ENABLE_IF_HPP
