/**
 *	@file	isnan.hpp
 *
 *	@brief	isnan 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_ISNAN_HPP
#define BKSGE_FND_CMATH_ISNAN_HPP

#include <bksge/fnd/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	NaNかどうか調べる
 *
 *	@tparam	ArithmeticType	算術型
 *
 *	@param	x	調べる値
 *
 *	@return	xがNaNならtrue,そうでないならfalse.
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
isnan(ArithmeticType x) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::isnan;

}	// namespace bksge

#include <bksge/fnd/cmath/inl/isnan_inl.hpp>

#endif // BKSGE_FND_CMATH_ISNAN_HPP
