/**
 *	@file	unit_test_fnd_bigint_common_type.cpp
 *
 *	@brief	common_type<bigint, bigint> のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <cstdint>

namespace bksge_bigint_test
{

#define BKSGE_BIGINT_COMMON_TYPE_TEST(R, T1, T2)	\
	static_assert(bksge::is_same<R, bksge::common_type_t<T1, T2>>::value, "")

BKSGE_BIGINT_COMMON_TYPE_TEST(float,       std::int32_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      std::int32_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, std::int32_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       std::int64_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      std::int64_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, std::int64_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       bksge::int128_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      bksge::int128_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, bksge::int128_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       bksge::int256_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      bksge::int256_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, bksge::int256_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       bksge::int512_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      bksge::int512_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, bksge::int512_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       bksge::int1024_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      bksge::int1024_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, bksge::int1024_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       std::uint32_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      std::uint32_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, std::uint32_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       std::uint64_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      std::uint64_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, std::uint64_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       bksge::uint128_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      bksge::uint128_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, bksge::uint128_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       bksge::uint256_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      bksge::uint256_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, bksge::uint256_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       bksge::uint512_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      bksge::uint512_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, bksge::uint512_t, long double);
BKSGE_BIGINT_COMMON_TYPE_TEST(float,       bksge::uint1024_t, float);
BKSGE_BIGINT_COMMON_TYPE_TEST(double,      bksge::uint1024_t, double);
BKSGE_BIGINT_COMMON_TYPE_TEST(long double, bksge::uint1024_t, long double);

BKSGE_BIGINT_COMMON_TYPE_TEST(std::int32_t,    std::int32_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::int32_t,    std::int32_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::int32_t,    std::int32_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint32_t,   std::int32_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::int64_t,    std::int32_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint64_t,   std::int32_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   std::int32_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  std::int32_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   std::int32_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  std::int32_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   std::int32_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  std::int32_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  std::int32_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, std::int32_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint32_t,   std::uint32_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint32_t,   std::uint32_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint32_t,   std::uint32_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint32_t,   std::uint32_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::int64_t,    std::uint32_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint64_t,   std::uint32_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   std::uint32_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  std::uint32_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   std::uint32_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  std::uint32_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   std::uint32_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  std::uint32_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  std::uint32_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, std::uint32_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(std::int64_t,    std::int64_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::int64_t,    std::int64_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::int64_t,    std::int64_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::int64_t,    std::int64_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::int64_t,    std::int64_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint64_t,   std::int64_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   std::int64_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  std::int64_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   std::int64_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  std::int64_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   std::int64_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  std::int64_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  std::int64_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, std::int64_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint64_t,   std::uint64_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint64_t,   std::uint64_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint64_t,   std::uint64_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint64_t,   std::uint64_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint64_t,   std::uint64_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(std::uint64_t,   std::uint64_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   std::uint64_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  std::uint64_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   std::uint64_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  std::uint64_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   std::uint64_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  std::uint64_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  std::uint64_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, std::uint64_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   bksge::int128_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   bksge::int128_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   bksge::int128_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   bksge::int128_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   bksge::int128_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   bksge::int128_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int128_t,   bksge::int128_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  bksge::int128_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::int128_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::int128_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int128_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::int128_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int128_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::int128_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  bksge::uint128_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  bksge::uint128_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  bksge::uint128_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  bksge::uint128_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  bksge::uint128_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  bksge::uint128_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  bksge::uint128_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint128_t,  bksge::uint128_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::uint128_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint128_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::uint128_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint128_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::uint128_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint128_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::int256_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::int256_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::int256_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::int256_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::int256_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::int256_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::int256_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::int256_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int256_t,   bksge::int256_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::int256_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int256_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::int256_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int256_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::int256_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint256_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint256_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint256_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint256_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint256_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint256_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint256_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint256_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint256_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint256_t,  bksge::uint256_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::uint256_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint256_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::uint256_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint256_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int512_t,   bksge::int512_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::int512_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int512_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::int512_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint512_t,  bksge::uint512_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::uint512_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint512_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::int1024_t,  bksge::int1024_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::int1024_t, bksge::uint1024_t);

BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, std::int16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, std::uint16_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, std::int32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, std::uint32_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, std::int64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, std::uint64_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, bksge::int128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, bksge::uint128_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, bksge::int256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, bksge::uint256_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, bksge::int512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, bksge::uint512_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, bksge::int1024_t);
BKSGE_BIGINT_COMMON_TYPE_TEST(bksge::uint1024_t, bksge::uint1024_t, bksge::uint1024_t);

#undef BKSGE_BIGINT_COMMON_TYPE_TEST

}	// namespace bksge_bigint_test
