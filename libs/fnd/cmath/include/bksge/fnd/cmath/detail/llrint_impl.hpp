/**
 *	@file	llrint_impl.hpp
 *
 *	@brief	llrint 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CMATH_DETAIL_LLRINT_IMPL_HPP
#define BKSGE_FND_CMATH_DETAIL_LLRINT_IMPL_HPP

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
inline BKSGE_CONSTEXPR long long
llrint_unchecked(T x) BKSGE_NOEXCEPT
{
	return std::llrint(x);
}

template <typename FloatType>
inline BKSGE_CONSTEXPR long long
llrint_impl(FloatType x) BKSGE_NOEXCEPT
{
	return
		bksge::isnan(x) ?
			0LL :
		bksge::isinf(x) ?
			bksge::signbit(x) ?
				std::numeric_limits<long long>::min() :
				std::numeric_limits<long long>::max() :
		llrint_unchecked(x);
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_CMATH_DETAIL_LLRINT_IMPL_HPP
