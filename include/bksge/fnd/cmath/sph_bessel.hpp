/**
 *	@file	sph_bessel.hpp
 *
 *	@brief	sph_bessel 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SPH_BESSEL_HPP
#define BKSGE_FND_CMATH_SPH_BESSEL_HPP

#include <bksge/fnd/cmath/detail/sph_bessel_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	第一種球ベッセル関数 (spherical Bessel functions of the first kind) を計算する。
 *
 *	@param	n
 *	@param	x
 *
 *	@return	引数 n, x の第一種球ベッセル関数を返す
 *
 *	x が NaN のとき、NaN を返す
 *	n >= 128 の場合、この関数の呼び出しの効果は実装定義である
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic>
sph_bessel(unsigned int n, Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::sph_bessel_impl(n, static_cast<type>(x));
}

inline BKSGE_CXX14_CONSTEXPR float
sph_besself(unsigned int n, float x) BKSGE_NOEXCEPT
{
	return detail::sph_bessel_impl(n, x);
}

inline BKSGE_CXX14_CONSTEXPR long double
sph_bessell(unsigned int n, long double x) BKSGE_NOEXCEPT
{
	return detail::sph_bessel_impl(n, x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_SPH_BESSEL_HPP
