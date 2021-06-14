/**
 *	@file	isnormal_impl.hpp
 *
 *	@brief	isnormal 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ISNORMAL_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ISNORMAL_IMPL_HPP

#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/issubnormal.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
isnormal_impl(FloatType x) BKSGE_NOEXCEPT
{
#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isnormal(x);
#else
	return
		!bksge::iszero(x)      &&
		!bksge::issubnormal(x) &&
		!bksge::isinf(x)       &&
		!bksge::isnan(x);
#endif
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ISNORMAL_IMPL_HPP
