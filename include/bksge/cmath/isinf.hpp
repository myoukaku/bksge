/**
 *	@file	isinf.hpp
 *
 *	@brief	isinf 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_ISINF_HPP
#define BKSGE_CMATH_ISINF_HPP

#include <bksge/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	∞かどうか調べる
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xが±∞ならtrue,そうでないならfalse.
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
isinf(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::isinf;

}	// namespace bksge

#include <bksge/cmath/inl/isinf_inl.hpp>

#endif // BKSGE_CMATH_ISINF_HPP
