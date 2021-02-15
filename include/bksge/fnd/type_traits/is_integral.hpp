/**
 *	@file	is_integral.hpp
 *
 *	@brief	is_integral の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_INTEGRAL_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_INTEGRAL_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが整数型かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_integralは、型Tが整数型(cv修飾も許容される)であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	以下のような型が、整数型として判定される：
 *	・bool
 *	・char
 *	・char16_t
 *	・char32_t
 *	・wchar_t
 *	・short
 *	・int
 *	・long
 *	・long long
 *	enumは整数型とは判定されない。
 */
template <typename T>
struct is_integral
	: public detail::constant_wrapper<
		std::is_integral<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_integral_v = is_integral<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_INTEGRAL_HPP
