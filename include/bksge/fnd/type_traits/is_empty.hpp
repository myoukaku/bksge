/**
 *	@file	is_empty.hpp
 *
 *	@brief	is_empty の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_EMPTY_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_EMPTY_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが空のクラスか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型Tが非共用体のクラスである場合、その型は完全型でなければならない
 *
 *	is_emptyは、型Tが空のクラスであるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	空のクラスであるとは、以下の全ての条件を満たす型である（cv修飾を含む）：
 *	・クラス型である
 *	・共用型でない
 *	・長さ0のビットフィールド以外に、非静的データメンバを持たない
 *	・仮想メンバ関数を持たない
 *	・仮想基底クラスを持たない
 *	・空のクラスでない基底クラスを持たない
 */
template <typename T>
struct is_empty
	: public detail::constant_wrapper<
		std::is_empty<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_EMPTY_HPP
