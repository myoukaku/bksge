/**
 *	@file	bit_shift_right.hpp
 *
 *	@brief	bit_shift_right 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_BIT_SHIFT_RIGHT_HPP
#define BKSGE_FND_BIGINT_DETAIL_BIT_SHIFT_RIGHT_HPP

#include <bksge/fnd/bigint/detail/make_sized_unsigned.hpp>
#include <bksge/fnd/bigint/detail/div_mod.hpp>
#include <bksge/fnd/bigint/detail/is_zero.hpp>
#include <bksge/fnd/bigint/detail/to_arithmetic.hpp>
#include <bksge/fnd/bigint/detail/compare.hpp>
#include <bksge/fnd/bigint/detail/shift_right.hpp>
#include <bksge/fnd/bigint/detail/remove_leading_zeros.hpp>
#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/ranges/range_value_t.hpp>
#include <bksge/fnd/ranges/size.hpp>
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
inline BKSGE_CXX14_CONSTEXPR void
bit_shift_right(VectorType& lhs, VectorType const& rhs)
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
		for (bksge::size_t i = N; i > 0; --i)
		{
			auto const t = (double_element_type(lhs[i-1]) << element_bits >> shift);
			lhs[i-1] = static_cast<element_type>(carry + (t >> element_bits));
			carry    = static_cast<element_type>(t);
		}
	}

	if (!bigint_algo::is_zero(quo))
	{
		if (bigint_algo::compare(quo, bksge::numeric_limits<bksge::size_t>::max()) > 0)
		{
			lhs = {0};
			return;
		}
		auto offset = bigint_algo::to_arithmetic<bksge::size_t>(quo);
		auto N = bksge::min(offset, ranges::size(lhs));
		bigint_algo::shift_right(lhs, N);
	}

	bigint_algo::remove_leading_zeros(lhs);
}

template <
	typename VectorType,
	BKSGE_REQUIRES_PARAM(bksge::integral, Integral)
>
inline BKSGE_CXX14_CONSTEXPR void
bit_shift_right(VectorType& lhs, Integral rhs)
{
	return bit_shift_right(lhs, bigint_algo::construct_from_integral<VectorType>(rhs));
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_BIT_SHIFT_RIGHT_HPP
