/**
 *	@file	is_convertible.hpp
 *
 *	@brief	is_convertible の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_CONVERTIBLE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_CONVERTIBLE_HPP

namespace bksge
{

/**
 *	@brief	型Fromから型Toに変換可能か調べる。
 *
 *	@tparam		From	変換元の型
 *	@tparam		To		変換先の型
 *
 *	@require	型Fromと型Toは完全型であるか、void(cv修飾を含む)か、要素数不明の配列型でなければならない
 *
 *	is_convertibleは、型Fromから型Toに変換可能であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename From, typename To>
struct is_convertible;

}	// namespace bksge

#include <bksge/fnd/type_traits/inl/is_convertible_inl.hpp>

#endif // BKSGE_FND_TYPE_TRAITS_IS_CONVERTIBLE_HPP
