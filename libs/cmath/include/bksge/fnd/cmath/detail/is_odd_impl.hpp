/**
 *	@file	is_odd_impl.hpp
 *
 *	@brief	is_odd 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_IS_ODD_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_IS_ODD_IMPL_HPP

#include <bksge/fnd/cmath/fmod.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR bool
is_odd_impl(FloatType x) BKSGE_NOEXCEPT
{
	return bksge::fmod(bksge::fabs(x), FloatType(2)) == FloatType(1);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_IS_ODD_IMPL_HPP
