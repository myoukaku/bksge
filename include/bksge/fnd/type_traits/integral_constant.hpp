/**
 *	@file	integral_constant.hpp
 *
 *	@brief	integral_constant の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define BKSGE_FND_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include <type_traits>

#if defined(__cpp_lib_integral_constant_callable) && (__cpp_lib_integral_constant_callable >= 201304)

namespace bksge
{

using std::integral_constant;

}	// namespace bksge

#else

#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	整数定数
 *
 *	@tparam	T	定数の型
 *	@tparam	v	定数の値
 *
 *	integral_constant は基本となる整数型と定数を合わせ，型として整数定数を表す。
 */
template <typename T, T v>
struct integral_constant
{
	using value_type = T;
	using type = integral_constant<T, v>;

	BKSGE_STATIC_CONSTEXPR T value = v;

	BKSGE_CONSTEXPR operator value_type() const BKSGE_NOEXCEPT { return value; }
	BKSGE_CONSTEXPR value_type operator()() const BKSGE_NOEXCEPT { return value; }
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
