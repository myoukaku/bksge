/**
 *	@file	unit_test_fnd_bigint_limits.cpp
 *
 *	@brief	numeric_limits<bigint> のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>
#include <limits>

namespace bksge_bigint_test
{

static_assert(sizeof(bksge::int64_t)   ==   8, "");
static_assert(sizeof(bksge::int128_t)  ==  16, "");
static_assert(sizeof(bksge::int256_t)  ==  32, "");
static_assert(sizeof(bksge::int512_t)  ==  64, "");
static_assert(sizeof(bksge::int1024_t) == 128, "");

static_assert(sizeof(bksge::uint64_t)   ==   8, "");
static_assert(sizeof(bksge::uint128_t)  ==  16, "");
static_assert(sizeof(bksge::uint256_t)  ==  32, "");
static_assert(sizeof(bksge::uint512_t)  ==  64, "");
static_assert(sizeof(bksge::uint1024_t) == 128, "");

static_assert(std::numeric_limits<bksge::bigint    >::is_specialized == true, "");
static_assert(std::numeric_limits<bksge::int128_t  >::is_specialized == true, "");
static_assert(std::numeric_limits<bksge::int256_t  >::is_specialized == true, "");
static_assert(std::numeric_limits<bksge::int512_t  >::is_specialized == true, "");
static_assert(std::numeric_limits<bksge::int1024_t >::is_specialized == true, "");
static_assert(std::numeric_limits<bksge::uint128_t >::is_specialized == true, "");
static_assert(std::numeric_limits<bksge::uint256_t >::is_specialized == true, "");
static_assert(std::numeric_limits<bksge::uint512_t >::is_specialized == true, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::is_specialized == true, "");

static_assert(std::numeric_limits<bksge::bigint    >::digits == INT_MAX, "");
static_assert(std::numeric_limits<bksge::int64_t   >::digits ==   63, "");
static_assert(std::numeric_limits<bksge::int128_t  >::digits ==  127, "");
static_assert(std::numeric_limits<bksge::int256_t  >::digits ==  255, "");
static_assert(std::numeric_limits<bksge::int512_t  >::digits ==  511, "");
static_assert(std::numeric_limits<bksge::int1024_t >::digits == 1023, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::digits ==   64, "");
static_assert(std::numeric_limits<bksge::uint128_t >::digits ==  128, "");
static_assert(std::numeric_limits<bksge::uint256_t >::digits ==  256, "");
static_assert(std::numeric_limits<bksge::uint512_t >::digits ==  512, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::digits == 1024, "");

static_assert(std::numeric_limits<bksge::bigint    >::digits10 == INT_MAX, "");
static_assert(std::numeric_limits<bksge::int64_t   >::digits10 ==  18, "");
static_assert(std::numeric_limits<bksge::int128_t  >::digits10 ==  38, "");
static_assert(std::numeric_limits<bksge::int256_t  >::digits10 ==  76, "");
static_assert(std::numeric_limits<bksge::int512_t  >::digits10 == 153, "");
static_assert(std::numeric_limits<bksge::int1024_t >::digits10 == 307, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::digits10 ==  19, "");
static_assert(std::numeric_limits<bksge::uint128_t >::digits10 ==  38, "");
static_assert(std::numeric_limits<bksge::uint256_t >::digits10 ==  77, "");
static_assert(std::numeric_limits<bksge::uint512_t >::digits10 == 154, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::digits10 == 308, "");

static_assert(std::numeric_limits<bksge::bigint    >::max_digits10 == 0, "");
static_assert(std::numeric_limits<bksge::int64_t   >::max_digits10 == 0, "");
static_assert(std::numeric_limits<bksge::int128_t  >::max_digits10 == 0, "");
static_assert(std::numeric_limits<bksge::int256_t  >::max_digits10 == 0, "");
static_assert(std::numeric_limits<bksge::int512_t  >::max_digits10 == 0, "");
static_assert(std::numeric_limits<bksge::int1024_t >::max_digits10 == 0, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::max_digits10 == 0, "");
static_assert(std::numeric_limits<bksge::uint128_t >::max_digits10 == 0, "");
static_assert(std::numeric_limits<bksge::uint256_t >::max_digits10 == 0, "");
static_assert(std::numeric_limits<bksge::uint512_t >::max_digits10 == 0, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::max_digits10 == 0, "");

static_assert(std::numeric_limits<bksge::bigint    >::is_signed == true, "");
static_assert(std::numeric_limits<bksge::int64_t   >::is_signed == true, "");
static_assert(std::numeric_limits<bksge::int128_t  >::is_signed == true, "");
static_assert(std::numeric_limits<bksge::int256_t  >::is_signed == true, "");
static_assert(std::numeric_limits<bksge::int512_t  >::is_signed == true, "");
static_assert(std::numeric_limits<bksge::int1024_t >::is_signed == true, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::is_signed == false, "");
static_assert(std::numeric_limits<bksge::uint128_t >::is_signed == false, "");
static_assert(std::numeric_limits<bksge::uint256_t >::is_signed == false, "");
static_assert(std::numeric_limits<bksge::uint512_t >::is_signed == false, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::is_signed == false, "");

static_assert(std::numeric_limits<bksge::bigint    >::is_integer == true, "");
static_assert(std::numeric_limits<bksge::int64_t   >::is_integer == true, "");
static_assert(std::numeric_limits<bksge::int128_t  >::is_integer == true, "");
static_assert(std::numeric_limits<bksge::int256_t  >::is_integer == true, "");
static_assert(std::numeric_limits<bksge::int512_t  >::is_integer == true, "");
static_assert(std::numeric_limits<bksge::int1024_t >::is_integer == true, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::is_integer == true, "");
static_assert(std::numeric_limits<bksge::uint128_t >::is_integer == true, "");
static_assert(std::numeric_limits<bksge::uint256_t >::is_integer == true, "");
static_assert(std::numeric_limits<bksge::uint512_t >::is_integer == true, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::is_integer == true, "");

static_assert(std::numeric_limits<bksge::bigint    >::is_exact == true, "");
static_assert(std::numeric_limits<bksge::int64_t   >::is_exact == true, "");
static_assert(std::numeric_limits<bksge::int128_t  >::is_exact == true, "");
static_assert(std::numeric_limits<bksge::int256_t  >::is_exact == true, "");
static_assert(std::numeric_limits<bksge::int512_t  >::is_exact == true, "");
static_assert(std::numeric_limits<bksge::int1024_t >::is_exact == true, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::is_exact == true, "");
static_assert(std::numeric_limits<bksge::uint128_t >::is_exact == true, "");
static_assert(std::numeric_limits<bksge::uint256_t >::is_exact == true, "");
static_assert(std::numeric_limits<bksge::uint512_t >::is_exact == true, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::is_exact == true, "");

static_assert(std::numeric_limits<bksge::bigint    >::radix == 2, "");
static_assert(std::numeric_limits<bksge::int64_t   >::radix == 2, "");
static_assert(std::numeric_limits<bksge::int128_t  >::radix == 2, "");
static_assert(std::numeric_limits<bksge::int256_t  >::radix == 2, "");
static_assert(std::numeric_limits<bksge::int512_t  >::radix == 2, "");
static_assert(std::numeric_limits<bksge::int1024_t >::radix == 2, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::radix == 2, "");
static_assert(std::numeric_limits<bksge::uint128_t >::radix == 2, "");
static_assert(std::numeric_limits<bksge::uint256_t >::radix == 2, "");
static_assert(std::numeric_limits<bksge::uint512_t >::radix == 2, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::radix == 2, "");

static_assert(std::numeric_limits<bksge::bigint    >::min_exponent == 0, "");
static_assert(std::numeric_limits<bksge::int64_t   >::min_exponent == 0, "");
static_assert(std::numeric_limits<bksge::int128_t  >::min_exponent == 0, "");
static_assert(std::numeric_limits<bksge::int256_t  >::min_exponent == 0, "");
static_assert(std::numeric_limits<bksge::int512_t  >::min_exponent == 0, "");
static_assert(std::numeric_limits<bksge::int1024_t >::min_exponent == 0, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::min_exponent == 0, "");
static_assert(std::numeric_limits<bksge::uint128_t >::min_exponent == 0, "");
static_assert(std::numeric_limits<bksge::uint256_t >::min_exponent == 0, "");
static_assert(std::numeric_limits<bksge::uint512_t >::min_exponent == 0, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::min_exponent == 0, "");

static_assert(std::numeric_limits<bksge::bigint    >::min_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::int64_t   >::min_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::int128_t  >::min_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::int256_t  >::min_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::int512_t  >::min_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::int1024_t >::min_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::min_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::uint128_t >::min_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::uint256_t >::min_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::uint512_t >::min_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::min_exponent10 == 0, "");

static_assert(std::numeric_limits<bksge::bigint    >::max_exponent == 0, "");
static_assert(std::numeric_limits<bksge::int64_t   >::max_exponent == 0, "");
static_assert(std::numeric_limits<bksge::int128_t  >::max_exponent == 0, "");
static_assert(std::numeric_limits<bksge::int256_t  >::max_exponent == 0, "");
static_assert(std::numeric_limits<bksge::int512_t  >::max_exponent == 0, "");
static_assert(std::numeric_limits<bksge::int1024_t >::max_exponent == 0, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::max_exponent == 0, "");
static_assert(std::numeric_limits<bksge::uint128_t >::max_exponent == 0, "");
static_assert(std::numeric_limits<bksge::uint256_t >::max_exponent == 0, "");
static_assert(std::numeric_limits<bksge::uint512_t >::max_exponent == 0, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::max_exponent == 0, "");

static_assert(std::numeric_limits<bksge::bigint    >::max_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::int64_t   >::max_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::int128_t  >::max_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::int256_t  >::max_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::int512_t  >::max_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::int1024_t >::max_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::max_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::uint128_t >::max_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::uint256_t >::max_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::uint512_t >::max_exponent10 == 0, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::max_exponent10 == 0, "");

static_assert(std::numeric_limits<bksge::bigint    >::has_infinity == false, "");
static_assert(std::numeric_limits<bksge::int64_t   >::has_infinity == false, "");
static_assert(std::numeric_limits<bksge::int128_t  >::has_infinity == false, "");
static_assert(std::numeric_limits<bksge::int256_t  >::has_infinity == false, "");
static_assert(std::numeric_limits<bksge::int512_t  >::has_infinity == false, "");
static_assert(std::numeric_limits<bksge::int1024_t >::has_infinity == false, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::has_infinity == false, "");
static_assert(std::numeric_limits<bksge::uint128_t >::has_infinity == false, "");
static_assert(std::numeric_limits<bksge::uint256_t >::has_infinity == false, "");
static_assert(std::numeric_limits<bksge::uint512_t >::has_infinity == false, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::has_infinity == false, "");

static_assert(std::numeric_limits<bksge::bigint    >::has_quiet_NaN == false, "");
static_assert(std::numeric_limits<bksge::int64_t   >::has_quiet_NaN == false, "");
static_assert(std::numeric_limits<bksge::int128_t  >::has_quiet_NaN == false, "");
static_assert(std::numeric_limits<bksge::int256_t  >::has_quiet_NaN == false, "");
static_assert(std::numeric_limits<bksge::int512_t  >::has_quiet_NaN == false, "");
static_assert(std::numeric_limits<bksge::int1024_t >::has_quiet_NaN == false, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::has_quiet_NaN == false, "");
static_assert(std::numeric_limits<bksge::uint128_t >::has_quiet_NaN == false, "");
static_assert(std::numeric_limits<bksge::uint256_t >::has_quiet_NaN == false, "");
static_assert(std::numeric_limits<bksge::uint512_t >::has_quiet_NaN == false, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::has_quiet_NaN == false, "");

static_assert(std::numeric_limits<bksge::bigint    >::has_signaling_NaN == false, "");
static_assert(std::numeric_limits<bksge::int64_t   >::has_signaling_NaN == false, "");
static_assert(std::numeric_limits<bksge::int128_t  >::has_signaling_NaN == false, "");
static_assert(std::numeric_limits<bksge::int256_t  >::has_signaling_NaN == false, "");
static_assert(std::numeric_limits<bksge::int512_t  >::has_signaling_NaN == false, "");
static_assert(std::numeric_limits<bksge::int1024_t >::has_signaling_NaN == false, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::has_signaling_NaN == false, "");
static_assert(std::numeric_limits<bksge::uint128_t >::has_signaling_NaN == false, "");
static_assert(std::numeric_limits<bksge::uint256_t >::has_signaling_NaN == false, "");
static_assert(std::numeric_limits<bksge::uint512_t >::has_signaling_NaN == false, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::has_signaling_NaN == false, "");

static_assert(std::numeric_limits<bksge::bigint    >::has_denorm == std::denorm_absent, "");
static_assert(std::numeric_limits<bksge::int64_t   >::has_denorm == std::denorm_absent, "");
static_assert(std::numeric_limits<bksge::int128_t  >::has_denorm == std::denorm_absent, "");
static_assert(std::numeric_limits<bksge::int256_t  >::has_denorm == std::denorm_absent, "");
static_assert(std::numeric_limits<bksge::int512_t  >::has_denorm == std::denorm_absent, "");
static_assert(std::numeric_limits<bksge::int1024_t >::has_denorm == std::denorm_absent, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::has_denorm == std::denorm_absent, "");
static_assert(std::numeric_limits<bksge::uint128_t >::has_denorm == std::denorm_absent, "");
static_assert(std::numeric_limits<bksge::uint256_t >::has_denorm == std::denorm_absent, "");
static_assert(std::numeric_limits<bksge::uint512_t >::has_denorm == std::denorm_absent, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::has_denorm == std::denorm_absent, "");

static_assert(std::numeric_limits<bksge::bigint    >::has_denorm_loss == false, "");
static_assert(std::numeric_limits<bksge::int64_t   >::has_denorm_loss == false, "");
static_assert(std::numeric_limits<bksge::int128_t  >::has_denorm_loss == false, "");
static_assert(std::numeric_limits<bksge::int256_t  >::has_denorm_loss == false, "");
static_assert(std::numeric_limits<bksge::int512_t  >::has_denorm_loss == false, "");
static_assert(std::numeric_limits<bksge::int1024_t >::has_denorm_loss == false, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::has_denorm_loss == false, "");
static_assert(std::numeric_limits<bksge::uint128_t >::has_denorm_loss == false, "");
static_assert(std::numeric_limits<bksge::uint256_t >::has_denorm_loss == false, "");
static_assert(std::numeric_limits<bksge::uint512_t >::has_denorm_loss == false, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::has_denorm_loss == false, "");

static_assert(std::numeric_limits<bksge::bigint    >::is_iec559 == false, "");
static_assert(std::numeric_limits<bksge::int64_t   >::is_iec559 == false, "");
static_assert(std::numeric_limits<bksge::int128_t  >::is_iec559 == false, "");
static_assert(std::numeric_limits<bksge::int256_t  >::is_iec559 == false, "");
static_assert(std::numeric_limits<bksge::int512_t  >::is_iec559 == false, "");
static_assert(std::numeric_limits<bksge::int1024_t >::is_iec559 == false, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::is_iec559 == false, "");
static_assert(std::numeric_limits<bksge::uint128_t >::is_iec559 == false, "");
static_assert(std::numeric_limits<bksge::uint256_t >::is_iec559 == false, "");
static_assert(std::numeric_limits<bksge::uint512_t >::is_iec559 == false, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::is_iec559 == false, "");

static_assert(std::numeric_limits<bksge::bigint    >::is_bounded == false, "");
static_assert(std::numeric_limits<bksge::int64_t   >::is_bounded == true, "");
static_assert(std::numeric_limits<bksge::int128_t  >::is_bounded == true, "");
static_assert(std::numeric_limits<bksge::int256_t  >::is_bounded == true, "");
static_assert(std::numeric_limits<bksge::int512_t  >::is_bounded == true, "");
static_assert(std::numeric_limits<bksge::int1024_t >::is_bounded == true, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::is_bounded == true, "");
static_assert(std::numeric_limits<bksge::uint128_t >::is_bounded == true, "");
static_assert(std::numeric_limits<bksge::uint256_t >::is_bounded == true, "");
static_assert(std::numeric_limits<bksge::uint512_t >::is_bounded == true, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::is_bounded == true, "");

static_assert(std::numeric_limits<bksge::bigint    >::is_modulo == false, "");
static_assert(std::numeric_limits<bksge::int64_t   >::is_modulo == false, "");
static_assert(std::numeric_limits<bksge::int128_t  >::is_modulo == false, "");
static_assert(std::numeric_limits<bksge::int256_t  >::is_modulo == false, "");
static_assert(std::numeric_limits<bksge::int512_t  >::is_modulo == false, "");
static_assert(std::numeric_limits<bksge::int1024_t >::is_modulo == false, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::is_modulo == true, "");
static_assert(std::numeric_limits<bksge::uint128_t >::is_modulo == true, "");
static_assert(std::numeric_limits<bksge::uint256_t >::is_modulo == true, "");
static_assert(std::numeric_limits<bksge::uint512_t >::is_modulo == true, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::is_modulo == true, "");

static_assert(std::numeric_limits<bksge::bigint    >::traps == false, "");
static_assert(std::numeric_limits<bksge::int64_t   >::traps == false, "");
static_assert(std::numeric_limits<bksge::int128_t  >::traps == false, "");
static_assert(std::numeric_limits<bksge::int256_t  >::traps == false, "");
static_assert(std::numeric_limits<bksge::int512_t  >::traps == false, "");
static_assert(std::numeric_limits<bksge::int1024_t >::traps == false, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::traps == false, "");
static_assert(std::numeric_limits<bksge::uint128_t >::traps == false, "");
static_assert(std::numeric_limits<bksge::uint256_t >::traps == false, "");
static_assert(std::numeric_limits<bksge::uint512_t >::traps == false, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::traps == false, "");

static_assert(std::numeric_limits<bksge::bigint    >::tinyness_before == false, "");
static_assert(std::numeric_limits<bksge::int64_t   >::tinyness_before == false, "");
static_assert(std::numeric_limits<bksge::int128_t  >::tinyness_before == false, "");
static_assert(std::numeric_limits<bksge::int256_t  >::tinyness_before == false, "");
static_assert(std::numeric_limits<bksge::int512_t  >::tinyness_before == false, "");
static_assert(std::numeric_limits<bksge::int1024_t >::tinyness_before == false, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::tinyness_before == false, "");
static_assert(std::numeric_limits<bksge::uint128_t >::tinyness_before == false, "");
static_assert(std::numeric_limits<bksge::uint256_t >::tinyness_before == false, "");
static_assert(std::numeric_limits<bksge::uint512_t >::tinyness_before == false, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::tinyness_before == false, "");

static_assert(std::numeric_limits<bksge::bigint    >::round_style == std::round_toward_zero, "");
static_assert(std::numeric_limits<bksge::int64_t   >::round_style == std::round_toward_zero, "");
static_assert(std::numeric_limits<bksge::int128_t  >::round_style == std::round_toward_zero, "");
static_assert(std::numeric_limits<bksge::int256_t  >::round_style == std::round_toward_zero, "");
static_assert(std::numeric_limits<bksge::int512_t  >::round_style == std::round_toward_zero, "");
static_assert(std::numeric_limits<bksge::int1024_t >::round_style == std::round_toward_zero, "");
static_assert(std::numeric_limits<bksge::uint64_t  >::round_style == std::round_toward_zero, "");
static_assert(std::numeric_limits<bksge::uint128_t >::round_style == std::round_toward_zero, "");
static_assert(std::numeric_limits<bksge::uint256_t >::round_style == std::round_toward_zero, "");
static_assert(std::numeric_limits<bksge::uint512_t >::round_style == std::round_toward_zero, "");
static_assert(std::numeric_limits<bksge::uint1024_t>::round_style == std::round_toward_zero, "");

GTEST_TEST(BigIntTest, LimitsTest)
{
	EXPECT_TRUE(std::numeric_limits<bksge::bigint    >::min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::min() == -0x7fffffffffffffff - 1);
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::min() == bksge::int128_t("-0x7fffffffffffffffffffffffffffffff") - 1);
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::min() == bksge::int256_t("-0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff") - 1);
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::min() == bksge::int512_t("-0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff") - 1);
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::min() == bksge::int1024_t("-0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff") - 1);
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::min() == 0);

	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::min() < 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::min() < 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::min() < 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::min() < 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::min() < 0);

	EXPECT_TRUE(std::numeric_limits<bksge::bigint    >::max() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::max() == 0x7fffffffffffffff);
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::max() == bksge::int128_t("0x7fffffffffffffffffffffffffffffff"));
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::max() == bksge::int256_t("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::max() == bksge::int512_t("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::max() == bksge::int1024_t("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::max() == 0xffffffffffffffff);
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::max() == bksge::uint128_t("0xffffffffffffffffffffffffffffffff"));
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::max() == bksge::uint256_t("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::max() == bksge::uint512_t("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::max() == bksge::uint1024_t("0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"));

	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::max() > 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::max() > 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::max() > 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::max() > 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::max() > 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::max() > 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::max() > 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::max() > 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::max() > 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::max() > 0);

	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::min() < std::numeric_limits<bksge::int64_t   >::max());
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::min() < std::numeric_limits<bksge::int128_t  >::max());
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::min() < std::numeric_limits<bksge::int256_t  >::max());
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::min() < std::numeric_limits<bksge::int512_t  >::max());
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::min() < std::numeric_limits<bksge::int1024_t >::max());
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::min() < std::numeric_limits<bksge::uint64_t  >::max());
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::min() < std::numeric_limits<bksge::uint128_t >::max());
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::min() < std::numeric_limits<bksge::uint256_t >::max());
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::min() < std::numeric_limits<bksge::uint512_t >::max());
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::min() < std::numeric_limits<bksge::uint1024_t>::max());

	EXPECT_TRUE(std::numeric_limits<bksge::bigint    >::lowest() == std::numeric_limits<bksge::bigint    >::min());
	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::lowest() == std::numeric_limits<bksge::int64_t   >::min());
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::lowest() == std::numeric_limits<bksge::int128_t  >::min());
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::lowest() == std::numeric_limits<bksge::int256_t  >::min());
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::lowest() == std::numeric_limits<bksge::int512_t  >::min());
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::lowest() == std::numeric_limits<bksge::int1024_t >::min());
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::lowest() == std::numeric_limits<bksge::uint64_t  >::min());
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::lowest() == std::numeric_limits<bksge::uint128_t >::min());
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::lowest() == std::numeric_limits<bksge::uint256_t >::min());
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::lowest() == std::numeric_limits<bksge::uint512_t >::min());
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::lowest() == std::numeric_limits<bksge::uint1024_t>::min());

	EXPECT_TRUE(std::numeric_limits<bksge::bigint    >::epsilon() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::epsilon() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::epsilon() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::epsilon() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::epsilon() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::epsilon() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::epsilon() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::epsilon() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::epsilon() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::epsilon() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::epsilon() == 0);

	EXPECT_TRUE(std::numeric_limits<bksge::bigint    >::round_error() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::round_error() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::round_error() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::round_error() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::round_error() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::round_error() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::round_error() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::round_error() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::round_error() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::round_error() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::round_error() == 0);

	EXPECT_TRUE(std::numeric_limits<bksge::bigint    >::infinity() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::infinity() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::infinity() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::infinity() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::infinity() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::infinity() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::infinity() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::infinity() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::infinity() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::infinity() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::infinity() == 0);

	EXPECT_TRUE(std::numeric_limits<bksge::bigint    >::quiet_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::quiet_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::quiet_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::quiet_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::quiet_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::quiet_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::quiet_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::quiet_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::quiet_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::quiet_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::quiet_NaN() == 0);

	EXPECT_TRUE(std::numeric_limits<bksge::bigint    >::signaling_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::signaling_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::signaling_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::signaling_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::signaling_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::signaling_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::signaling_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::signaling_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::signaling_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::signaling_NaN() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::signaling_NaN() == 0);

	EXPECT_TRUE(std::numeric_limits<bksge::bigint    >::denorm_min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int64_t   >::denorm_min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int128_t  >::denorm_min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int256_t  >::denorm_min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int512_t  >::denorm_min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::int1024_t >::denorm_min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint64_t  >::denorm_min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint128_t >::denorm_min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint256_t >::denorm_min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint512_t >::denorm_min() == 0);
	EXPECT_TRUE(std::numeric_limits<bksge::uint1024_t>::denorm_min() == 0);
}

}	// namespace bksge_bigint_test
