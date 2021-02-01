/**
 *	@file	isfinite_impl.hpp
 *
 *	@brief	isfinite 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ISFINITE_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ISFINITE_IMPL_HPP

#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
isfinite_impl(FloatType x) BKSGE_NOEXCEPT
{
#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isfinite(x);
#else
	return !bksge::isinf(x) && !bksge::isnan(x);
#endif
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ISFINITE_IMPL_HPP
