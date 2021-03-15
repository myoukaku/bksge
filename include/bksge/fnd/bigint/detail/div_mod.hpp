/**
 *	@file	div_mod.hpp
 *
 *	@brief	div_mod 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_DIV_MOD_HPP
#define BKSGE_FND_BIGINT_DETAIL_DIV_MOD_HPP

#include <bksge/fnd/bigint/detail/make_sized_unsigned.hpp>
#include <bksge/fnd/bigint/detail/compare.hpp>
#include <bksge/fnd/bigint/detail/get_digits.hpp>
#include <bksge/fnd/bigint/detail/construct_from_iterator.hpp>
#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/bigint/detail/to_arithmetic.hpp>
#include <bksge/fnd/bigint/detail/multiply.hpp>
#include <bksge/fnd/bigint/detail/add.hpp>
#include <bksge/fnd/bigint/detail/sub.hpp>
#include <bksge/fnd/bigint/detail/shift_left.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename VectorType>
inline BKSGE_CXX14_CONSTEXPR VectorType
div_mod(VectorType const& lhs, VectorType const& rhs, VectorType* out_remainder)
{
	namespace ranges = bksge::ranges;
	using element_type = ranges::range_value_t<VectorType>;
	using double_element_type = make_sized_unsigned_t<sizeof(element_type)*2>;

	auto const c = bigint_algo::compare(lhs, rhs);

	// lhs < rhs
	if (c < 0)
	{
		if (out_remainder != nullptr)
		{
			*out_remainder = lhs;
		}
		return {0};
	}

	// lhs == rhs
	if (c == 0)
	{
		if (out_remainder != nullptr)
		{
			*out_remainder = VectorType{0};
		}
		return {1};
	}

	auto const NA = bigint_algo::get_digits(lhs);
	auto const NB = bigint_algo::get_digits(rhs);

	// ----- ステップ 1. A ÷ B の桁数を求める ----- //
	bksge::size_t D = NA - NB;
	// digit_a_partial : A の上 NB 桁を取り出したもの
	auto digit_a_partial = bigint_algo::construct_from_iterator<VectorType>(lhs.begin() + D, lhs.end());
	if (bigint_algo::compare(digit_a_partial, rhs) >= 0)
	{
		// (A の上 NB 桁) が B 以上だったら...？
		D += 1;
	}

	if (D == 0)
	{
		if (out_remainder != nullptr)
		{
			*out_remainder = lhs;
		}
		return {0};
	}

	// lhs と rhs が整数で表現可能な場合は整数で計算する
	if (D <= 2 && NA <= 2 && NB <= 2)
	{
		auto x = bigint_algo::to_arithmetic<double_element_type>(lhs);
		auto y = bigint_algo::to_arithmetic<double_element_type>(rhs);
		if (out_remainder != nullptr)
		{
			*out_remainder = bigint_algo::construct_from_integral<VectorType>(x % y);
		}
		return bigint_algo::construct_from_integral<VectorType>(x / y);
	}

	// ----- ステップ 2. A ÷ B を筆算で求める ----- //
	auto remainder = bigint_algo::construct_from_iterator<VectorType>(lhs.begin() + (D - 1), lhs.end());

	auto quotient = bigint_algo::construct_from_size<VectorType>(D);

	for (auto i = D; i > 0; --i)
	{
		bksge::size_t index = i - 1;

		if (NB <= 2 && bigint_algo::get_digits(remainder) <= 2)
		{
			// remainder と rhs が整数で表現可能な場合は整数で計算する
			auto x = bigint_algo::to_arithmetic<double_element_type>(remainder);
			auto y = bigint_algo::to_arithmetic<double_element_type>(rhs);
			quotient[index] = static_cast<element_type>(x / y);
		}
		else
		{
			// remainder / rhs をバイナリサーチで探す
			double_element_type left = 1;
			double_element_type right = bksge::numeric_limits<element_type>::max();
			right++;

			while (right - left > 1)
			{
				double_element_type mid = (left + right) / 2;
				auto x = bigint_algo::multiply(rhs, mid);
				if (bigint_algo::compare(x, remainder) > 0)
				{
					right = mid;
				}
				else
				{
					left = mid;
				}
			}
			quotient[index] = static_cast<element_type>(left);
		}

		auto x_result = bigint_algo::multiply(rhs, quotient[index]);
		bigint_algo::sub(remainder, x_result);
		if (index >= 1)
		{
			// 新しく (index-1) の位が降りてくる
			remainder = bigint_algo::shift_left(remainder, 1);
			bigint_algo::add(remainder, lhs[index - 1]);
		}
	}

	if (out_remainder != nullptr)
	{
		*out_remainder = remainder;
	}

	return quotient;
}

template <
	typename VectorType,
	BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
>
inline BKSGE_CXX14_CONSTEXPR VectorType
div_mod(VectorType const& lhs, Integral rhs, VectorType* out_remainder)
{
	return div_mod(lhs, bigint_algo::construct_from_integral<VectorType>(rhs), out_remainder);
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_DIV_MOD_HPP
