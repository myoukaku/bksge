/**
 *	@file	modf_impl.hpp
 *
 *	@brief	modf 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_MODF_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_MODF_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/copysign.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
modf_unchecked(T x, T* iptr) BKSGE_NOEXCEPT
{
	return std::modf(x, iptr);
}

template <typename FloatType>
inline BKSGE_CXX14_CONSTEXPR FloatType
modf_impl(FloatType x, FloatType* iptr) BKSGE_NOEXCEPT
{
	if (bksge::iszero(x))
	{
		*iptr = x;
		return x;
	}

	if (bksge::isinf(x))
	{
		*iptr = x;
		return bksge::copysign(FloatType(0), x);
	}

	if (bksge::isnan(x))
	{
		*iptr = x;
		return x;
	}

	return modf_unchecked(x, iptr);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_MODF_IMPL_HPP
