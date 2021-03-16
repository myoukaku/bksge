/**
 *	@file	multiply_float.hpp
 *
 *	@brief	multiply_float 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_MULTIPLY_FLOAT_HPP
#define BKSGE_FND_BIGINT_DETAIL_MULTIPLY_FLOAT_HPP

#include <bksge/fnd/bigint/detail/bit_shift_left.hpp>
#include <bksge/fnd/bigint/detail/bit_shift_right.hpp>
#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/bigint/detail/decompose_floating_point.hpp>
#include <bksge/fnd/bigint/detail/multiply.hpp>
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

// 多倍長整数に浮動小数点数を乗算する
//
// 整数にキャストしてから掛けたり、多倍長整数に変換してから掛けるのはうまくいかない。
// 理由は numeric_limits<uint64_t>::max() を超える値が来る可能性があるためと、
// 小数点以下の値が反映されないため。
// そこで、
// (1)浮動小数点数を仮数と指数に分解
// (2)仮数を多倍長整数に変換してから乗算
// (3)指数のぶんビットシフト
// という手順で計算する
template <typename VectorType, BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
inline BKSGE_CXX14_CONSTEXPR VectorType
multiply_float(VectorType const& lhs, Float rhs)
{
	bksge::uint64_t fraction {};
	bksge::int64_t exponent {};
	decompose_floating_point(rhs, &fraction, &exponent, nullptr);

	auto vec = bigint_algo::construct_from_integral<VectorType>(fraction);
	auto result = bigint_algo::multiply(lhs, vec);
	if (exponent < 0)
	{
		bigint_algo::bit_shift_right(result, -exponent);
	}
	else
	{
		bigint_algo::bit_shift_left(result, exponent);
	}
	return result;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_MULTIPLY_FLOAT_HPP
