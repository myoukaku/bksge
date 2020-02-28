/**
 *	@file	is_void.hpp
 *
 *	@brief	is_void の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_VOID_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_VOID_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tがvoidかを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_voidは、型Tがvoid(cv修飾を許容する)であれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_void
	: public detail::constant_wrapper<
		std::is_void<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_VOID_HPP
