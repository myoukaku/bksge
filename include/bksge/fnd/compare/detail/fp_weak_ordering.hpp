/**
 *	@file	fp_weak_ordering.hpp
 *
 *	@brief	fp_weak_ordering の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_FP_WEAK_ORDERING_HPP
#define BKSGE_FND_COMPARE_DETAIL_FP_WEAK_ORDERING_HPP

#include <bksge/fnd/compare/weak_ordering.hpp>
#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/is_lt.hpp>
#include <bksge/fnd/compare/is_gt.hpp>
#include <bksge/fnd/compare/is_eq.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, T)>
BKSGE_CXX14_CONSTEXPR bksge::weak_ordering
fp_weak_ordering(T e, T f)
{
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON) && \
	!defined(_MSC_VER)
	// Returns an integer with the same sign as the argument, and magnitude
	// indicating the classification: zero=1 subnorm=2 norm=3 inf=4 nan=5
	/*auto __cat = [](T fp) -> int {
		const int __sign = __builtin_signbit(fp) ? -1 : 1;
		if (__builtin_isnormal(fp))
			return (fp == 0 ? 1 : 3) * __sign;
		if (__builtin_isnan(fp))
			return 5 * __sign;
		if (int __inf = __builtin_isinf_sign(fp))
			return 4 * __inf;
		return 2 * __sign;
	};*/

	auto po = e <=> f;

	if (bksge::is_lt(po))
	{
		return bksge::weak_ordering::less;
	}
	else if (bksge::is_gt(po))
	{
		return bksge::weak_ordering::greater;
	}
	else if (po == bksge::partial_ordering::equivalent)
	{
		return bksge::weak_ordering::equivalent;
	}
	else  // unordered, at least one argument is NaN
	{
		// return -1 for negative nan, +1 for positive nan, 0 otherwise.
		auto isnan_sign = [](T fp) -> int
		{
			return bksge::isnan(fp) ?
				bksge::signbit(fp) ? -1 : 1
				: 0;
		};

		auto ord = isnan_sign(e) <=> isnan_sign(f);

		if (bksge::is_eq(ord))
		{
			return bksge::weak_ordering::equivalent;
		}
		else if (bksge::is_lt(ord))
		{
			return bksge::weak_ordering::less;
		}
		else
		{
			return bksge::weak_ordering::greater;
		}
	}

#else

	if (e < f)
	{
		return bksge::weak_ordering::less;
	}
	else if (e > f)
	{
		return bksge::weak_ordering::greater;
	}
	else if (e == f)
	{
		return bksge::weak_ordering::equivalent;
	}
	else  // unordered, at least one argument is NaN
	{
		auto isnan_sign = [](T fp) -> int
		{
			return bksge::isnan(fp) ?
				bksge::signbit(fp) ? -1 : 1
				: 0;
		};

		auto e2 = isnan_sign(e);
		auto f2 = isnan_sign(f);
		if (e2 == f2)
		{
			return bksge::weak_ordering::equivalent;
		}
		else if (e2 < f2)
		{
			return bksge::weak_ordering::less;
		}
		else
		{
			return bksge::weak_ordering::greater;
		}
	}

#endif
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_FP_WEAK_ORDERING_HPP
