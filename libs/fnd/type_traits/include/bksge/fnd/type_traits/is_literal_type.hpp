/**
 *	@file	is_literal_type.hpp
 *
 *	@brief	is_literal_type の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_LITERAL_TYPE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_LITERAL_TYPE_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	型Tがリテラル型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型remove_all_extents<T>::typeは、完全型か、void(cv修飾を含む)でなければならない
 *
 *	is_literal_typeは、型Tがリテラル型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	リテラル型とは、以下のいずれかの条件を満たす型である：
 *	・スカラー型
 *	・リテラル型への参照
 *	・リテラル型の配列
 *	・以下の全ての特性を持つクラス型(cv修飾を含む)
 *		・トリビアルなデストラクタを持つ
 *		・全てのコンストラクタが、定数式で初期化できること
 *		・集成体であること、もしくは一つ以上のconstexprコンストラクタ、もしくはコピー／ムーブコンストラクタ以外のコンストラクタテンプレートを持っていること
 *		・全てのデータメンバおよび基本クラスがリテラル型であること
 *	・(cv修飾を含む)void (C++14から)
 *
 *	リテラル型は、constexpr関数のパラメータおよび戻り値の型に対する制約として使用されている。
 */
template <typename T>
struct is_literal_type;

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_literal_type_v = is_literal_type<T>::value;

#endif

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_literal_type_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_LITERAL_TYPE_HPP
