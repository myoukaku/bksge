/**
 *	@file	lrint_impl.hpp
 *
 *	@brief	lrint 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LRINT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LRINT_IMPL_HPP

#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/config.hpp>
#include <cmath>

namespace bksge
{

namespace detail
{

template <typename T>
inline BKSGE_CONSTEXPR long
lrint_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::lrint(x);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR long
lrint_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			0L :
		bksge::isinf(x) ?
			bksge::signbit(x) ?
				std::numeric_limits<long>::min() :
				std::numeric_limits<long>::max() :
		lrint_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LRINT_IMPL_HPP
