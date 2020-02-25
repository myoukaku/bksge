/**
 *	@file	decay.hpp
 *
 *	@brief	decay の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_DECAY_HPP
#define BKSGE_FND_TYPE_TRAITS_DECAY_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief	配列と関数ポインタに関して、関数テンプレートと同様に推論された型を取得する。
 *
 *	@tparam	T
 *
 *	このクラステンプレートは、関数テンプレートにおける以下の推論ルールを適用する：
 *	・左辺値から右辺値への変換
 *	・配列からポインタへの変換
 *	・関数の左辺値から関数ポインタへの変換
 *
 *	remove_reference<T>::typeした型をUとする。
 *	型Uが配列型U[N]であれば、U*型をメンバ型typeとして定義する。
 *	型Uが関数型R(Args...)であれば、R(*)(Args...)型をメンバ型typeとして定義する。
 *	それ以外の場合は、remove_cv<U>::typeした型を、メンバ型typeとして定義する。
 */
using std::decay;

template <typename T>
using decay_t = typename decay<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_DECAY_HPP
