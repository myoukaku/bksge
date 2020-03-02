/**
 *	@file	is_nothrow_invocable_r.hpp
 *
 *	@brief	is_nothrow_invocable_r の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP

namespace bksge
{

/**
 *	@brief	型Fnが、与えられた型の引数ArgsTypes...で関数呼び出し可能であり、
 *			その戻り値型がRに変換可能かつ、その際に例外を投げないかどうかを調べる。
 *
 *	@tparam		R
 *	@tparam		Fn
 *	@tparam		ArgTypes
 *
 *	@require	型R, FnおよびArgsTypes...パラメータパックの全ての型が、
 *				完全型であるか、void(cv修飾を含む)か、要素数不明の配列型であること。
 *
 *	型Fnに対して引数ArgsTypes...によるINVOKEコンセプトに従った呼び出しが可能であり、
 *	その結果となる戻り値の型がRに変換可能かつ、
 *	その呼び出し及び変換に際していかなる例外も投げない場合
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename R, typename Fn, typename... ArgTypes>
struct is_nothrow_invocable_r;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_nothrow_invocable_r_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_R_HPP
