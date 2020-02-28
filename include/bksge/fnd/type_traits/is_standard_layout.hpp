/**
 *	@file	is_standard_layout.hpp
 *
 *	@brief	is_standard_layout の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがスタンダードレイアウト型か調べる。
 *
 *	@tparam		T
 *
 *	@require	型remove_all_extents<T>::typeは完全型であるか、void(cv修飾を含む)でなければならない。
 *
 *	is_standard_layoutは、型Tがスタンダードレイアウト型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	スタンダードレイアウト型は、以下の全てを満たす型を指す：
 *	・非スタンダードレイアウト型の非静的データメンバもしくは参照を持たない
 *	・仮想関数を持たず、仮想基本クラスを持たない
 *	・非スタンダードレイアウト型の基本クラスを持たない
 *	・最派生クラスに非静的データメンバを持つ場合、基底クラスに非静的データメンバを持たない
 *	・最初の非静的データメンバと同じ基本クラスを持たない
 */
template <typename T>
struct is_standard_layout
	: public detail::constant_wrapper<
		std::is_standard_layout<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_STANDARD_LAYOUT_HPP
