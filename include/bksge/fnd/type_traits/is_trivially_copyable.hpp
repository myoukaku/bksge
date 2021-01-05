/**
 *	@file	is_trivially_copyable.hpp
 *
 *	@brief	is_trivially_copyable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP

namespace bksge
{

/**
 *	@brief	型Tがトリビアルコピー可能か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型remove_all_extents<T>::typeは、完全型か、void(cv修飾を含む)でなければならない
 *
 *	is_trivially_copyableは、Tがトリビアルコピー可能な型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	「トリビアルコピー可能な型」とは、「memcpy()可能な型である」と言い換えることもできる。
 *	これに分類される型は、以下の全ての条件を満たす必要がある：
 *	・非トリビアルなコピーコンストラクタを持っていないこと
 *	・非トリビアルなムーブコンストラクタを持っていないこと
 *	・非トリビアルなコピー代入演算子を持っていないこと
 *	・非トリビアルなムーブ代入演算子を持っていないこと
 *	・トリビアルなデストラクタを持っていること
 *	および、これらのconst修飾を含むが、volatile修飾は含まない。
 *
 *	トリビアル(trivial)な特殊関数(コンストラクタ、代入演算子、デストラクタ)とは、
 *	「ユーザー定義されない特殊関数」のことを意味する。
 *
 *	MSVC12では以下のような不具合がある
 *	・非トリビアルなムーブコンストラクタを持っていてもtrueになる
 *	・非トリビアルなムーブ代入演算子を持っていてもtrueになる
 */
template <typename T>
struct is_trivially_copyable;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_trivially_copyable_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_HPP
