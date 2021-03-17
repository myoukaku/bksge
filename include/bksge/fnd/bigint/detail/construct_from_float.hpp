/**
 *	@file	construct_from_float.hpp
 *
 *	@brief	construct_from_float 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_FLOAT_HPP
#define BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_FLOAT_HPP

#include <bksge/fnd/bigint/detail/bit_shift_right.hpp>
#include <bksge/fnd/bigint/detail/bit_shift_left.hpp>
#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/cmath/decompose_float.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

// 浮動小数点数から多倍長整数に変換する
//
// 単に整数にキャストしてから多倍長整数に変換するのではうまくいかない。
// それは numeric_limits<uint64_t>::max() を超える値が来る可能性があるため。
// そこで、
// (1)浮動小数点数を仮数と指数に分解
// (2)仮数を多倍長整数に変換
// (3)指数のぶんビットシフト
// という手順で計算する
template <typename VectorType, BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
inline BKSGE_CXX14_CONSTEXPR VectorType
construct_from_float(Float value)
{
	auto const t = bksge::decompose_float(value);
	auto const fraction = t.fraction;
	auto const exponent = t.exponent;

	auto vec = bigint_algo::construct_from_integral<VectorType>(fraction);
	if (exponent < 0)
	{
		bigint_algo::bit_shift_right(vec, -exponent);
	}
	else
	{
		bigint_algo::bit_shift_left(vec, exponent);
	}
	return vec;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_CONSTRUCT_FROM_FLOAT_HPP
