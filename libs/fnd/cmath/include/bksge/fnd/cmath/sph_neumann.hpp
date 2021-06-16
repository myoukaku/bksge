/**
 *	@file	sph_neumann.hpp
 *
 *	@brief	sph_neumann 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_SPH_NEUMANN_HPP
#define BKSGE_FND_CMATH_SPH_NEUMANN_HPP

#include <bksge/fnd/cmath/detail/sph_neumann_impl.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

/**
 *	@brief	第二種球ベッセル関数 (spherical Bessel functions of the second kind)、
 *			球ノイマン関数 (spherical Neumann functions) を求める。
 *
 *	@param	n
 *	@param	x
 *
 *	@return	引数 n, x の第二種球ベッセル関数を返す
 *
 *	x が NaN のとき、NaN を返す
 *	n >= 128 の場合、この関数の呼び出しの効果は実装定義である
 */
template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
inline BKSGE_CXX14_CONSTEXPR bksge::float_promote_t<Arithmetic>
sph_neumann(unsigned int n, Arithmetic x) BKSGE_NOEXCEPT
{
	using type = bksge::float_promote_t<Arithmetic>;
	return detail::sph_neumann_impl(n, static_cast<type>(x));
}

inline BKSGE_CXX14_CONSTEXPR float
sph_neumannf(unsigned int n, float x) BKSGE_NOEXCEPT
{
	return detail::sph_neumann_impl(n, x);
}

inline BKSGE_CXX14_CONSTEXPR long double
sph_neumannl(unsigned int n, long double x) BKSGE_NOEXCEPT
{
	return detail::sph_neumann_impl(n, x);
}

}	// namespace bksge

#endif // BKSGE_FND_CMATH_SPH_NEUMANN_HPP
