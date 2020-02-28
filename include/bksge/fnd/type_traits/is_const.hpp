/**
 *	@file	is_const.hpp
 *
 *	@brief	is_const の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_CONST_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_CONST_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがconst修飾型か調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_constは、型Tがconst修飾型であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	const修飾型は、const および const volatile を含む。
 *	参照型は、const修飾型でない。
 */
template <typename T>
struct is_const
	: public detail::constant_wrapper<
		std::is_const<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_CONST_HPP
