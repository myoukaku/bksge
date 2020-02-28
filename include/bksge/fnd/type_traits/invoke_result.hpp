/**
 *	@file	invoke_result.hpp
 *
 *	@brief	invoke_result の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INVOKE_RESULT_HPP
#define BKSGE_FND_TYPE_TRAITS_INVOKE_RESULT_HPP

namespace bksge
{

/**
 *	@brief		関数の戻り値の型を取得する。
 *
 *	@tparam		F			関数または関数オブジェクト
 *	@tparam		ArgTypes	引数
 *
 *	@require	型FおよびArgsTypes...パラメータパックの全ての型は完全型であるか、
 *				void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	invoke_resultは、関数または関数オブジェクトの型Fに対して、
 *	ArgTypes...を引数として渡した場合の戻り値の型を、メンバ型typeとして定義する。
 *
 *	関数呼び出しが可能でない場合、メンバ型typeは定義されない。
 *	有効でない関数オブジェクト、引数を指定した場合にコンパイルエラーにならず、
 *	SFINAEが働く。
 */
template <typename F, typename... ArgTypes>
struct invoke_result;

/**
 *	@brief	invoke_resultのエイリアステンプレート
 */
template <typename F, typename... ArgTypes>
using invoke_result_t = typename invoke_result<F, ArgTypes...>::type;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/invoke_result_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_INVOKE_RESULT_HPP
