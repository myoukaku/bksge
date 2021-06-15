/**
 *	@file	unit_test_fnd_bigint_to_integral.cpp
 *
 *	@brief	operator Arithmetic() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4146);	// unary minus operator applied to unsigned type, result still unsigned
BKSGE_WARNING_DISABLE_MSVC(4310);	// cast truncates constant value

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool ToIntegralTest()
{
	{
		BigInt const x = 0;
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == 0);
		VERIFY(i16  == 0);
		VERIFY(i32  == 0);
		VERIFY(i64  == 0);
		VERIFY(ui8  == 0);
		VERIFY(ui16 == 0);
		VERIFY(ui32 == 0);
		VERIFY(ui64 == 0);
	}
	{
		BigInt const x = 1;
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == 1);
		VERIFY(i16  == 1);
		VERIFY(i32  == 1);
		VERIFY(i64  == 1);
		VERIFY(ui8  == 1);
		VERIFY(ui16 == 1);
		VERIFY(ui32 == 1);
		VERIFY(ui64 == 1);
	}
	{
		BigInt const x = -1;
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == -1);
		VERIFY(i16  == -1);
		VERIFY(i32  == -1);
		VERIFY(i64  == -1);
		VERIFY(ui8  == 0xff);
		VERIFY(ui16 == 0xffff);
		VERIFY(ui32 == 0xffffffff);
		VERIFY(ui64 == 0xffffffffffffffff);
	}
	{
		BigInt const x = 0xffff;
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == bksge::int8_t (0xff));
		VERIFY(i16  == bksge::int16_t(0xffff));
		VERIFY(i32  == bksge::int32_t(0xffff));
		VERIFY(i64  == bksge::int64_t(0xffff));
		VERIFY(ui8  == bksge::uint8_t (0xff));
		VERIFY(ui16 == bksge::uint16_t(0xffff));
		VERIFY(ui32 == bksge::uint32_t(0xffff));
		VERIFY(ui64 == bksge::uint64_t(0xffff));
	}
	{
		BigInt const x = -0xffff;
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == bksge::int8_t (-0xffff));
		VERIFY(i16  == bksge::int16_t(-0xffff));
		VERIFY(i32  == bksge::int32_t(-0xffff));
		VERIFY(i64  == bksge::int64_t(-0xffff));
		VERIFY(ui8  == bksge::uint8_t (-0xffff));
		VERIFY(ui16 == bksge::uint16_t(-0xffff));
		VERIFY(ui32 == bksge::uint32_t(-0xffff));
		VERIFY(ui64 == bksge::uint64_t(-0xffff));
	}
	{
		BigInt const x = 0xffffffff;
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == bksge::int8_t (0xff));
		VERIFY(i16  == bksge::int16_t(0xffff));
		VERIFY(i32  == bksge::int32_t(0xffffffff));
		VERIFY(i64  == bksge::int64_t(0xffffffff));
		VERIFY(ui8  == bksge::uint8_t (0xff));
		VERIFY(ui16 == bksge::uint16_t(0xffff));
		VERIFY(ui32 == bksge::uint32_t(0xffffffff));
		VERIFY(ui64 == bksge::uint64_t(0xffffffff));
	}
	{
		BigInt const x = -0xffffffff;
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == bksge::int8_t (-0xffffffff));
		VERIFY(i16  == bksge::int16_t(-0xffffffff));
		VERIFY(i32  == bksge::int32_t(-0xffffffff));
		VERIFY(i64  == bksge::int64_t(-0xffffffff));
		VERIFY(ui8  == bksge::uint8_t (-0xffffffff));
		VERIFY(ui16 == bksge::uint16_t(-0xffffffff));
		VERIFY(ui32 == bksge::uint32_t(-0xffffffff));
		VERIFY(ui64 == bksge::uint64_t(-0xffffffff));
	}
	{
		BigInt const x = 0xffffffffffffffff;
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == bksge::int8_t (0xff));
		VERIFY(i16  == bksge::int16_t(0xffff));
		VERIFY(i32  == bksge::int32_t(0xffffffff));
		VERIFY(i64  == bksge::int64_t(0xffffffffffffffff));
		VERIFY(ui8  == bksge::uint8_t (0xff));
		VERIFY(ui16 == bksge::uint16_t(0xffff));
		VERIFY(ui32 == bksge::uint32_t(0xffffffff));
		VERIFY(ui64 == bksge::uint64_t(0xffffffffffffffff));
	}
	{
		BigInt const x = -0xffffffffffffffff;
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == bksge::int8_t (-0xffffffffffffffff));
		VERIFY(i16  == bksge::int16_t(-0xffffffffffffffff));
		VERIFY(i32  == bksge::int32_t(-0xffffffffffffffff));
		VERIFY(i64  == bksge::int64_t(-0xffffffffffffffff));
		VERIFY(ui8  == bksge::uint8_t (-0xffffffffffffffff));
		VERIFY(ui16 == bksge::uint16_t(-0xffffffffffffffff));
		VERIFY(ui32 == bksge::uint32_t(-0xffffffffffffffff));
		VERIFY(ui64 == bksge::uint64_t(-0xffffffffffffffff));
	}
	{
		BigInt const x{"0xffffffffffffffffffffffffffffffff"};
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == bksge::int8_t (0xff));
		VERIFY(i16  == bksge::int16_t(0xffff));
		VERIFY(i32  == bksge::int32_t(0xffffffff));
		VERIFY(i64  == bksge::int64_t(0xffffffffffffffff));
		VERIFY(ui8  == 0xff);
		VERIFY(ui16 == 0xffff);
		VERIFY(ui32 == 0xffffffff);
		VERIFY(ui64 == 0xffffffffffffffff);
	}
	{
		BigInt const x{"-0xffffffffffffffffffffffffffffffff"};
		bksge::int8_t   i8(x);
		bksge::int16_t  i16(x);
		bksge::int32_t  i32(x);
		bksge::int64_t  i64(x);
		bksge::uint8_t  ui8(x);
		bksge::uint16_t ui16(x);
		bksge::uint32_t ui32(x);
		bksge::uint64_t ui64(x);
		VERIFY(i8   == 1);
		VERIFY(i16  == 1);
		VERIFY(i32  == 1);
		VERIFY(i64  == 1);
		VERIFY(ui8  == 1);
		VERIFY(ui16 == 1);
		VERIFY(ui32 == 1);
		VERIFY(ui64 == 1);
	}
	return true;
}

GTEST_TEST(BigIntTest, ToIntegralTest)
{
	EXPECT_TRUE((ToIntegralTest<bksge::bigint>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ToIntegralTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ToIntegralTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ToIntegralTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ToIntegralTest<bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ToIntegralTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ToIntegralTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ToIntegralTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((ToIntegralTest<bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
