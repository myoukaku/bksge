/**
 *	@file	isinf_impl.hpp
 *
 *	@brief	isinf 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ISINF_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ISINF_IMPL_HPP

#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
isinf_impl(FloatType x) BKSGE_NOEXCEPT
{
#if defined(BKSGE_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isinf(x);
#else
	return
		x ==  bksge::numeric_limits<FloatType>::infinity() ||
		x == -bksge::numeric_limits<FloatType>::infinity();
#endif
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ISINF_IMPL_HPP
