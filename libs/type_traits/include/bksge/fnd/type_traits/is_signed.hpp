/**
 *	@file	is_signed.hpp
 *
 *	@brief	is_signed の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_SIGNED_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_SIGNED_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが符号付き算術型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_signedは、型Tが符号付き算術型 (cv修飾を許容する) であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	符号付き算術型と見なす条件は以下：
 *	is_arithmetic<T>::value == trueの場合、
 *	integral_constant<bool, T(-1) < T(0)>::valueの結果を真偽の結果とする。
 *	そうでなければ偽の結果とする。
 */
template <typename T>
struct is_signed
	: public detail::constant_wrapper<
		std::is_signed<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_signed_v = is_signed<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_SIGNED_HPP
