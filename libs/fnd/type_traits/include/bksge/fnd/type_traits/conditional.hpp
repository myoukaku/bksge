/**
 *	@file	conditional.hpp
 *
 *	@brief	conditional の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_CONDITIONAL_HPP
#define BKSGE_FND_TYPE_TRAITS_CONDITIONAL_HPP

#include <type_traits>

namespace bksge
{

/**
 *	@brief		コンパイル時条件式
 *
 *	@tparam		B	条件式
 *	@tparam		T	条件式がtrueの時の型
 *	@tparam		F	条件式がfalseの時の型
 *
 *	conditionalは、条件式Bがtrueであれば型Tを、そうでなければ型Fを、メンバ型typeとして定義する。
 */
using std::conditional;

/**
 *	@brief	conditionalのエイリアステンプレート
 */
template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_CONDITIONAL_HPP
