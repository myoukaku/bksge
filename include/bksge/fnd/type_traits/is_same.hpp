/**
 *	@file	is_same.hpp
 *
 *	@brief	is_same の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_SAME_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_SAME_HPP

namespace bksge
{

/**
 *	@brief	2つの型TとUが同じ型か調べる
 *
 *	@tparam	T
 *	@tparam	U
 *
 *	is_sameは、CV修飾子が同じであることを含め型Tと型Uが同じ型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T, typename U>
struct is_same;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_same_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_SAME_HPP
