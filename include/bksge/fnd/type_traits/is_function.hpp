/**
 *	@file	is_function.hpp
 *
 *	@brief	is_function の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_FUNCTION_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_FUNCTION_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが関数型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_functionは、型Tが関数型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_function
	: public detail::constant_wrapper<
		std::is_function<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_FUNCTION_HPP
