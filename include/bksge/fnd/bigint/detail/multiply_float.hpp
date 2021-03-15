/**
 *	@file	multiply_float.hpp
 *
 *	@brief	multiply_float 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_MULTIPLY_FLOAT_HPP
#define BKSGE_FND_BIGINT_DETAIL_MULTIPLY_FLOAT_HPP

#include <bksge/fnd/bigint/detail/make_sized_unsigned.hpp>
#include <bksge/fnd/bigint/detail/multiply.hpp>
#include <bksge/fnd/bigint/detail/construct_from_float.hpp>
#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/bigint/detail/get_digits.hpp>
#include <bksge/fnd/bigint/detail/add.hpp>
#include <bksge/fnd/bigint/detail/shift_left.hpp>
#include <bksge/fnd/cmath/modf.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

namespace multiply_float_detail
{

template <typename VectorType, BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
inline BKSGE_CXX14_CONSTEXPR VectorType
multiply_float_fraction(VectorType const& lhs, Float rhs)
{
	namespace ranges = bksge::ranges;
	using element_type = ranges::range_value_t<VectorType>;
	using double_element_type = make_sized_unsigned_t<sizeof(element_type)*2>;

	auto const N = bigint_algo::get_digits(lhs);
	VectorType result {0};

	for (bksge::size_t i = 0; i < N; ++i)
	{
		auto t = bigint_algo::construct_from_integral<VectorType>(
			static_cast<double_element_type>(lhs[i] * rhs));
		bigint_algo::add(result, bigint_algo::shift_left(t, i));
	}

	return result;
}

}	// namespace multiply_float_detail

template <typename VectorType, BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
inline BKSGE_CXX14_CONSTEXPR VectorType
multiply_float(VectorType const& lhs, Float rhs)
{
	// (1) rhs を整数部と小数部にわける
	// (2) 整数部は多倍長整数にして乗算する
	// (3) 小数部はそのまま乗算する
	// (4) (2)と(3)を加算する

	Float integ;
	Float frac = bksge::modf(rhs, &integ);
	auto tmp1 = bigint_algo::multiply(lhs, bigint_algo::construct_from_float<VectorType>(integ));
	auto tmp2 = multiply_float_detail::multiply_float_fraction(lhs, frac);
	bigint_algo::add(tmp1, tmp2);
	return tmp1;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_MULTIPLY_FLOAT_HPP
