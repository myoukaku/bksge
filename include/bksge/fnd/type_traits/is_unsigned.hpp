/**
 *	@file	is_unsigned.hpp
 *
 *	@brief	is_unsigned の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_UNSIGNED_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_UNSIGNED_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが符号なし算術型かを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_unsignedは、型Tが符号なし算術型(cv修飾を許容する) であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	符号なし算術型と見なす条件は以下：
 *	is_arithmetic<T>::value == trueの場合、
 *	integral_constant<bool, T(0) < T(-1)>::valueの結果を真偽の結果とする。
 *	そうでなければ偽の結果とする。
 */
template <typename T>
struct is_unsigned
	: public detail::constant_wrapper<
		std::is_unsigned<T>
	>
{};

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_UNSIGNED_HPP
