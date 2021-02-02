/**
 *	@file	rint_impl.hpp
 *
 *	@brief	rint 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_RINT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_RINT_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR T
rint_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::rint(x);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
rint_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) || bksge::isinf(x) || bksge::iszero(x) ?
			x :
		rint_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_RINT_IMPL_HPP
