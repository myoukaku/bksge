/**
 *	@file	is_integer_impl.hpp
 *
 *	@brief	is_integer 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_IS_INTEGER_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_IS_INTEGER_IMPL_HPP

#include <bksge/fnd/cmath/isfinite.hpp>
#include <bksge/fnd/cmath/trunc.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
is_integer_impl(FloatType x) BKSGE_NOEXCEPT
{
	return bksge::isfinite(x) && (bksge::trunc(x) == x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_IS_INTEGER_IMPL_HPP
