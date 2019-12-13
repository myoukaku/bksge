/**
 *	@file	iszero.hpp
 *
 *	@brief	iszero 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISZERO_HPP
#define BKSGE_FND_CMATH_ISZERO_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	0かどうか調べる
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが±0ならtrue,そうでないならfalse.
 *
 *	@note	ArithmeticTypeが整数型のときはdoubleにキャストしてから調べる。
 */
template <
	typename ArithmeticType,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType>::value
	>::type
>
BKSGE_CONSTEXPR bool
iszero(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::iszero;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/iszero_inl.hpp>

#endif // BKSGE_FND_CMATH_ISZERO_HPP
