/**
 *	@file	is_nothrow_invocable.hpp
 *
 *	@brief	is_nothrow_invocable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP

namespace bksge
{

/**
 *	@brief	型Fnが、与えられた型の引数ArgsTypes...で関数呼び出し可能であり、
 *			その呼び出しに際して例外を投げないかどうかを調べる。
 *
 *	@tparam		Fn
 *	@tparam		ArgTypes
 *
 *	@require	型FnおよびArgsTypes...パラメータパックの全ての型が、
 *				完全型であるか、void(cv修飾を含む)か、要素数不明の配列型であること。
 *
 *	型Fnに対して引数ArgsTypes...によるINVOKEコンセプトに従った呼び出しが可能であり、
 *	いかなる例外も投げない場合true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename Fn, typename... ArgTypes>
struct is_nothrow_invocable;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_nothrow_invocable_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_NOTHROW_INVOCABLE_HPP
