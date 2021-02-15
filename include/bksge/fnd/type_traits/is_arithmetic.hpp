/**
 *	@file	is_arithmetic.hpp
 *
 *	@brief	is_arithmetic の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_IS_ARITHMETIC_HPP
#define BKSGE_FND_TYPE_TRAITS_IS_ARITHMETIC_HPP

#include <bksge/fnd/type_traits/detail/constant_wrapper.hpp>
#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

/**
 *	@brief	型Tが算術型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_arithmeticは、型Tが算術型であればtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *	算術型は、整数型、浮動小数点型、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_arithmetic
	: public detail::constant_wrapper<
		std::is_arithmetic<T>
	>
{};

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
bool is_arithmetic_v = is_arithmetic<T>::value;

#endif

}	// namespace bksge

#endif // BKSGE_FND_TYPE_TRAITS_IS_ARITHMETIC_HPP
