/**
 *	@file	is_pod.hpp
 *
 *	@brief	is_pod の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_POD_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_POD_HPP

namespace bksge
{

/**
 *	@brief	型TがPOD型(Plane Old Data)か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	@require	型remove_all_extents<T>::typeは、完全型か、void(cv修飾を含む)でなければならない
 *
 *	is_podは、型TがPOD型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	POD型であるとは、以下のいずれかの条件を満たす型である（cv修飾を含む）：
 *	・スカラー型
 *	・以下の全ての特性を持つクラス型
 *		・トリビアル型
 *		・スタンダードレイアウト型
 *		・非POD型のデータメンバを持っていない
 *	・POD型の配列
 *
 *	MSVC12では以下のような不具合がある
 *	・基底クラスを持っているとfalseになる(C++11以前の定義)
 *	・非トリビアルなムーブ代入演算子を持っていてもtrueになる
 */
template <typename T>
struct is_pod;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_pod_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_POD_HPP
