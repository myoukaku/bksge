/**
 *	@file	saturate_impl.hpp
 *
 *	@brief	saturate 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_SATURATE_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_SATURATE_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/algorithm/clamp.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
saturate_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		bksge::clamp(x, FloatType(0), FloatType(1));
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_SATURATE_IMPL_HPP
