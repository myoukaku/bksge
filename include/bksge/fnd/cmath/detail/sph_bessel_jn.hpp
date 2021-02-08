/**
 *	@file	sph_bessel_jn.hpp
 *
 *	@brief	sph_bessel_jn 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SPH_BESSEL_JN_HPP
#define BKSGE_FND_CMATH_DETAIL_SPH_BESSEL_JN_HPP

#include <bksge/fnd/cmath/sqrt.hpp>
#include <bksge/fnd/cmath/detail/bessel_jn.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void
sph_bessel_jn(unsigned int n, T x, T& j_n, T& n_n, T& jp_n, T& np_n)
{
	const T nu = T(n) + T(0.5L);

	T J_nu, N_nu, Jp_nu, Np_nu;
	bksge::detail::bessel_jn(nu, x, J_nu, N_nu, Jp_nu, Np_nu);

	const T factor = bksge::sqrt(bksge::pi_t<T>() / 2) / bksge::sqrt(x);

	j_n = factor * J_nu;
	n_n = factor * N_nu;
	jp_n = factor * Jp_nu - j_n / (T(2) * x);
	np_n = factor * Np_nu - n_n / (T(2) * x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SPH_BESSEL_JN_HPP
