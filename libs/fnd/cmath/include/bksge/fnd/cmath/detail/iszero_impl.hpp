/**
 *	@file	iszero_impl.hpp
 *
 *	@brief	iszero 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_ISZERO_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_ISZERO_IMPL_HPP

#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
iszero_impl(FloatType x) BKSGE_NOEXCEPT
{
	return x == FloatType(0);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_ISZERO_IMPL_HPP
