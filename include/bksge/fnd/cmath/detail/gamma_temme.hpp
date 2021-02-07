/**
 *	@file	gamma_temme.hpp
 *
 *	@brief	gamma_temme 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_GAMMA_TEMME_HPP
#define BKSGE_FND_CMATH_DETAIL_GAMMA_TEMME_HPP

#include <bksge/fnd/cmath/tgamma.hpp>
#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CXX14_CONSTEXPR void
gamma_temme(T mu, T& gam1, T& gam2, T& gampl, T& gammi)
{
	gampl = T(1) / bksge::tgamma(T(1) + mu);
	gammi = T(1) / bksge::tgamma(T(1) - mu);

	if (bksge::abs(mu) < bksge::numeric_limits<T>::epsilon())
	{
		gam1 = -T(bksge::egamma_t<T>());
	}
	else
	{
		gam1 = (gammi - gampl) / (T(2) * mu);
	}

	gam2 = (gammi + gampl) / (T(2));

	return;
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_GAMMA_TEMME_HPP
