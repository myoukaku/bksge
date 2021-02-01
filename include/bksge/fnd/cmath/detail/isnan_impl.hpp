/**
 *	@file	isnan_impl.hpp
 *
 *	@brief	isnan 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ISNAN_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ISNAN_IMPL_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
isnan_impl(FloatType x) BKSGE_NOEXCEPT
{
#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isnan(x);
#else
	return !(x == x);
#endif
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ISNAN_IMPL_HPP
