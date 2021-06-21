/**
 *	@file	nextafter_impl.hpp
 *
 *	@brief	nextafter 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_NEXTAFTER_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_NEXTAFTER_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>
#include <limits>

namespace bksge
{

namespace detail
{

template <typename FloatType>
inline BKSGE_CONSTEXPR FloatType
nextafter_impl(FloatType from, FloatType to) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(from) || bksge::isnan(to) ?
			std::numeric_limits<FloatType>::quiet_NaN() :
		std::nextafter(from, to);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_NEXTAFTER_IMPL_HPP
