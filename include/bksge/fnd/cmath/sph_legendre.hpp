/**
 *	@file	sph_legendre.hpp
 *
 *	@brief	sph_legendre 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SPH_LEGENDRE_HPP
#define BKSGE_FND_CMATH_SPH_LEGENDRE_HPP

#include <bksge/fnd/cmath/detail/sph_legendre_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	球面調和関数 (spherical harmonic function) の θ 成分を求める
 *
 *	@param	l
 *	@param	m
 *	@param	theta
 *
 *	@return	引数 l, m, theta の球面調和関数の θ 成分を求める
 *
 *	theta が NaN のとき、NaN を返す
 *	l >= 128 の場合、この関数の呼び出しの効果は実装定義である
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic>
sph_legendre(unsigned int l, unsigned int m, Arithmetic theta) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::sph_legendre_impl(l, m, static_cast<type>(theta));
}

inline BKSGE_CXX14_CONSTEXPR float
sph_legendref(unsigned int l, unsigned int m, float theta) BKSGE_NOEXCEPT
{
	return detail::sph_legendre_impl(l, m, theta);
}

inline BKSGE_CXX14_CONSTEXPR long double
sph_legendrel(unsigned int l, unsigned int m, long double theta) BKSGE_NOEXCEPT
{
	return detail::sph_legendre_impl(l, m, theta);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_SPH_LEGENDRE_HPP
