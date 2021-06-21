/**
 *	@file	expint_en_cont_frac.hpp
 *
 *	@brief	expint_En_cont_frac 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_EXPINT_EN_CONT_FRAC_HPP
#define BKSGE_FND_CMATH_DETAIL_EXPINT_EN_CONT_FRAC_HPP

#include <bksge/fnd/cmath/abs.hpp>
#include <bksge/fnd/cmath/exp.hpp>
#include <bksge/fnd/stdexcept/runtime_error.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename T>
T
expint_En_cont_frac(unsigned int n, T x)
{
	unsigned int const max_iter = 1000;
	T const eps = std::numeric_limits<T>::epsilon();
	T const fp_min = std::numeric_limits<T>::min();
	int const nm1 = n - 1;
	T b = x + T(n);
	T c = T(1) / fp_min;
	T d = T(1) / b;
	T h = d;
	for (unsigned int i = 1; i <= max_iter; ++i)
	{
		T a = -T(i * (nm1 + i));
		b += T(2);
		d = T(1) / (a * d + b);
		c = b + a / c;
		T const del = c * d;
		h *= del;
		if (bksge::abs(del - T(1)) < eps)
		{
			T const ans = h * bksge::exp(-x);
			return ans;
		}
	}
	bksge::throw_runtime_error("Continued fraction failed in expint_En_cont_frac.");
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_EXPINT_EN_CONT_FRAC_HPP
