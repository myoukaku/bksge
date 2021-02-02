/**
 *	@file	isless_impl.hpp
 *
 *	@brief	isless 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ISLESS_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ISLESS_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
isless_impl(FloatType x, FloatType y) BKSGE_NOEXCEPT
{
#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isless(x, y);
#else
	return !bksge::isnan(x) && !bksge::isnan(y) && (x < y);
#endif
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ISLESS_IMPL_HPP
