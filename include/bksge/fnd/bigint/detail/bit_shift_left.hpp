/**
 *	@file	bit_shift_left.hpp
 *
 *	@brief	bit_shift_left 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_BIT_SHIFT_LEFT_HPP
#define BKSGE_FND_BIGINT_DETAIL_BIT_SHIFT_LEFT_HPP

#include <bksge/fnd/bigint/detail/make_sized_unsigned.hpp>
#include <bksge/fnd/bigint/detail/div_mod.hpp>
#include <bksge/fnd/bigint/detail/is_zero.hpp>
#include <bksge/fnd/bigint/detail/to_arithmetic.hpp>
#include <bksge/fnd/bigint/detail/lo.hpp>
#include <bksge/fnd/bigint/detail/hi.hpp>
#include <bksge/fnd/bigint/detail/resize.hpp>
#include <bksge/fnd/bigint/detail/shift_left.hpp>
#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename VectorType>
inline BKSGE_CXX14_CONSTEXPR void
bit_shift_left(VectorType& lhs, VectorType const& rhs)
{
	namespace ranges = bksge::ranges;
	using element_type = ranges::range_value_t<VectorType>;
	using double_element_type = make_sized_unsigned_t<sizeof(element_type)*2>;

	auto const element_bits = bksge::bitsof<element_type>();
	VectorType rem {};
	VectorType quo = bigint_algo::div_mod(rhs, element_bits, &rem);

	if (!bigint_algo::is_zero(rem))
	{
		auto shift = bigint_algo::to_arithmetic<double_element_type>(rem);
		double_element_type carry = 0;
		auto const N = ranges::size(lhs);
		bksge::size_t i = 0;
		for (; i < N; ++i)
		{
			auto const t = carry + (double_element_type(lhs[i]) << shift);
			lhs[i] = bigint_algo::lo<element_type>(t);
			carry  = bigint_algo::hi<element_type>(t);
		}

		if (carry != 0)
		{
			bigint_algo::resize(lhs, N + 1);
			lhs[i] = bigint_algo::lo<element_type>(carry);
		}
	}

	if (!bigint_algo::is_zero(quo))
	{
		auto offset = bigint_algo::to_arithmetic<bksge::size_t>(quo);
		bigint_algo::shift_left(lhs, offset);
	}
}

template <
	typename VectorType,
	BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
>
inline BKSGE_CXX14_CONSTEXPR void
bit_shift_left(VectorType& lhs, Integral rhs)
{
	return bit_shift_left(lhs, bigint_algo::construct_from_integral<VectorType>(rhs));
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_BIT_SHIFT_LEFT_HPP
