/**
 *	@file	is_reference.hpp
 *
 *	@brief	is_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_REFERENCE_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_REFERENCE_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが参照型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_referenceは、型Tが左辺値参照型もしくは右辺値参照型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_reference
	: public detail::constant_wrapper<
		std::is_reference<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_REFERENCE_HPP
