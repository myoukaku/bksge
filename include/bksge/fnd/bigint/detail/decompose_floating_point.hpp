﻿/**
 *	@file	decompose_floating_point.hpp
 *
 *	@brief	decompose_floating_point 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_DECOMPOSE_FLOATING_POINT_HPP
#define BKSGE_FND_BIGINT_DETAIL_DECOMPOSE_FLOATING_POINT_HPP

#include <bksge/fnd/bigint/detail/make_sized_signed.hpp>
#include <bksge/fnd/bigint/detail/make_sized_unsigned.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/bit/bitsof.hpp>
#include <bksge/fnd/bit/bit_cast.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <BKSGE_REQUIRES_PARAM(bksge::floating_point, Float)>
inline BKSGE_CXX14_CONSTEXPR void
decompose_floating_point(Float value, bksge::uint64_t* out_fraction, bksge::int64_t* out_exponent, bksge::uint64_t* out_sign)
{
	bksge::uint64_t const sign_bits = 1;
	bksge::uint64_t const fraction_bits = bksge::numeric_limits<Float>::digits - 1;
	bksge::uint64_t const exponent_bits = bksge::bitsof<Float>() - 1 - fraction_bits;

	bksge::uint64_t const sign_bit_shift = bksge::bitsof<Float>() - 1;
	bksge::uint64_t const exponent_bit_shift = fraction_bits;
	bksge::uint64_t const fraction_bit_shift = 0;

	bksge::uint64_t const sign_bit_mask      = ((1ULL << sign_bits)     - 1) << sign_bit_shift;
	bksge::uint64_t const exponent_bit_mask  = ((1ULL << exponent_bits) - 1) << exponent_bit_shift;
	bksge::uint64_t const fraction_bit_mask  = ((1ULL << fraction_bits) - 1) << fraction_bit_shift;

	bksge::uint64_t const exponent_bias = bksge::numeric_limits<Float>::max_exponent - 1;
	bksge::uint64_t const fraction_bias = (1ULL << fraction_bits);

	using utype = make_sized_unsigned_t<sizeof(Float)>;
	using stype = make_sized_signed_t<sizeof(Float)>;
	auto v = bksge::bit_cast<utype>(value);
	utype const sign     = (v & sign_bit_mask)     >> sign_bit_shift;
	utype const exponent = (v & exponent_bit_mask) >> exponent_bit_shift;
	utype const fraction = (v & fraction_bit_mask) >> fraction_bit_shift;
	stype const shift = exponent - exponent_bias - fraction_bits;

	if (out_fraction != nullptr)
	{
		*out_fraction = fraction + fraction_bias;
	}

	if (out_exponent != nullptr)
	{
		*out_exponent = shift;
	}

	if (out_sign != nullptr)
	{
		*out_sign = sign;
	}
}

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_DECOMPOSE_FLOATING_POINT_HPP
