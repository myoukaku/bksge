/**
 *	@file	fmod.hpp
 *
 *	@brief	fmod 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_FMOD_HPP
#define BKSGE_FND_CMATH_FMOD_HPP

#include <bksge/fnd/cmath/detail/fmod_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	剰余を求めます
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
inline BKSGE_CONSTEXPR float
fmod(float x, float y) BKSGE_NOEXCEPT
{
	return detail::fmod_impl(x, y);
}

inline BKSGE_CONSTEXPR float
fmodf(float x, float y) BKSGE_NOEXCEPT
{
	return detail::fmod_impl(x, y);
}

inline BKSGE_CONSTEXPR double
fmod(double x, double y) BKSGE_NOEXCEPT
{
	return detail::fmod_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
fmod(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::fmod_impl(x, y);
}

inline BKSGE_CONSTEXPR long double
fmodl(long double x, long double y) BKSGE_NOEXCEPT
{
	return detail::fmod_impl(x, y);
}

template <
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic1),
	BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic2)
>
inline BKSGE_CONSTEXPR bksge::float_promote_t<Arithmetic1, Arithmetic2>
fmod(Arithmetic1 x, Arithmetic2 y) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::fmod_impl(static_cast<type>(x), static_cast<type>(y));
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_FMOD_HPP
