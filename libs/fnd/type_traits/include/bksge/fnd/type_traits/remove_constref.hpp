/**
 *	@file	remove_constref.hpp
 *
 *	@brief	remove_constref の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_REMOVE_CONSTREF_HPP
#define BKSGE_FND_TYPE_TRAITS_REMOVE_CONSTREF_HPP

#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>

namespace bksge
{

/**
 *	@brief		型Tからconst修飾と参照を除去する。
 *
 *	@tparam		T
 */
template <typename T>
struct remove_constref
	: public bksge::remove_const<bksge::remove_reference_t<T>>
{};

/**
 *	@brief	remove_constrefのエイリアステンプレート
 */
template <typename T>
using remove_constref_t = typename remove_constref<T>::type;

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_REMOVE_CONSTREF_HPP
