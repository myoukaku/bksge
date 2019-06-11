/**
 *	@file	fmod.hpp
 *
 *	@brief	fmod 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CMATH_FMOD_HPP
#define BKSGE_CMATH_FMOD_HPP

#include <bksge/type_traits/float_promote.hpp>
#include <bksge/config.hpp>
#include <type_traits>

namespace bksge
{

namespace cmath
{

/**
 *	@brief	剰余を求めます
 *
 *	@tparam	ArithmeticType1	算術型
 *	@tparam	ArithmeticType2	算術型
 *
 *	@param	x
 *	@param	y
 *
 *	@return	x / y の余り。符号はxの符号と同じです。
 *
 *	x が ±0  かつ、y が 0   でない場合、±0 を返す。
 *	x が ±∞ かつ、y が NaN でない場合、NaN を返す。
 *	y が ±0  かつ、x が NaN でない場合、NaN を返す。
 *	y が ±∞ かつ、x が 有限の値の場合、x をそのまま返す。
 *	x か y の少なくともどちらかがNaNの場合、NaNを返す。
 */
template <
	typename ArithmeticType1,
	typename ArithmeticType2,
	typename = typename std::enable_if<
		std::is_arithmetic<ArithmeticType1>::value &&
		std::is_arithmetic<ArithmeticType2>::value
	>::type
>
BKSGE_CONSTEXPR bksge::float_promote_t<ArithmeticType1, ArithmeticType2>
fmod(ArithmeticType1 x, ArithmeticType2 y) BKSGE_NOEXCEPT;

}	// namespace cmath

using cmath::fmod;

}	// namespace bksge

#include <bksge/cmath/inl/fmod_inl.hpp>

#endif // BKSGE_CMATH_FMOD_HPP
