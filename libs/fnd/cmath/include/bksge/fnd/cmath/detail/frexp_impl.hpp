/**
 *	@file	frexp_impl.hpp
 *
 *	@brief	frexp 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_FREXP_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_FREXP_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CXX14_CONSTEXPR FloatType
frexp_impl(FloatType x, int* exp) BKSGE_NOEXCEPT
{
	if (bksge::iszero(x))
	{
		*exp = 0;
		return x;
	}

	if (bksge::isinf(x)  ||
		bksge::isnan(x))
	{
		return x;
	}

	return std::frexp(x, exp);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_FREXP_IMPL_HPP
