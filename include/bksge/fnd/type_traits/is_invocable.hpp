/**
 *	@file	is_invocable.hpp
 *
 *	@brief	is_invocable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_INVOCABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_INVOCABLE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	型Fnが、与えられた型の引数ArgsTypes...で関数呼び出し可能かどうかを調べる。
 *
 *	@tparam		Fn
 *	@tparam		ArgTypes
 *
 *	@require	型FnおよびArgsTypes...パラメータパックの全ての型が、
 *				完全型であるか、void(cv修飾を含む)か、要素数不明の配列型であること。
 *
 *	型Fnに対して引数ArgsTypes...によるINVOKEコンセプトに従った呼び出しが可能であれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename Fn, typename... ArgTypes>
struct is_invocable;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename Fn, typename... ArgTypes>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_invocable_v = is_invocable<Fn, ArgTypes...>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_invocable_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_INVOCABLE_HPP
