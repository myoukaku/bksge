/**
 *	@file	nexttoward_impl.hpp
 *
 *	@brief	nexttoward 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_NEXTTOWARD_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_NEXTTOWARD_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
nexttoward_impl(FloatType from, long double to) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(from) || bksge::isnan(to) ?
			bksge::numeric_limits<FloatType>::quiet_NaN() :
		std::nexttoward(from, to);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_NEXTTOWARD_IMPL_HPP
