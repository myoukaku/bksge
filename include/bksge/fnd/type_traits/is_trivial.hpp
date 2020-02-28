/**
 *	@file	is_trivial.hpp
 *
 *	@brief	is_trivial の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_TRIVIAL_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_TRIVIAL_HPP

namespace bksge
{

/**
 *	@brief	型Tがトリビアル型か調べる。
 *
 *	@tparam		T
 *
 *	@require	型remove_all_extents<T>::typeは完全型であるか、void(cv修飾を含む)でなければならない。
 *
 *	is_trivialは、型Tがトリビアル型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	トリビアル型は、トリビアルコピー可能、かつトリビアルなデフォルトコンストラクタを持つ型、およびそのcv修飾を含む。
 *
 *	スカラ型は、トリビアル型の要件を満たす。トリビアル型の配列は、トリビアル型の要件を満たす。
 */
template <typename T>
struct is_trivial;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_trivial_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_TRIVIAL_HPP
