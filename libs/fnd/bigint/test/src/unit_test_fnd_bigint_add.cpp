/**
 *	@file	unit_test_fnd_bigint_add.cpp
 *
 *	@brief	bigint::operator+=(), operator+(bigint, bigint) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant
BKSGE_WARNING_DISABLE_MSVC(4245);	// conversion from '...' to '...', signed/unsigned mismatch
BKSGE_WARNING_DISABLE_MSVC(4308);	// negative integral constant converted to unsigned type

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	BigInt1 x{};
	VERIFY(x == 0);

	x += 0;
	VERIFY(x == 0);

	x += 1;
	VERIFY(x == 1);

	x += -2;
	VERIFY(x == BigInt1(-1));

	x += 12345;
	VERIFY(x == 12344);

	x += BigInt2{656};
	VERIFY(x == 13000);

	x += BigInt2{123456789};
	VERIFY(x == 123469789);

	x += x;
	VERIFY(x == 246939578);

	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool AddFloatTest()
{
	BigInt x{};
	VERIFY(x == 0);

	x += 0.5f;
	VERIFY(x == 0);

	x += 2.5;
	VERIFY(x == 2);

	x += 3.5L;
	VERIFY(x == 5);

	x += 123.456;
	VERIFY(x == 128);

	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Add2Test()
{
	{
		auto x = BigInt1{0} + BigInt2{0};
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1{1} + BigInt2{0};
		VERIFY(x == 1);
	}
	{
		auto x = BigInt1{2} + BigInt2{3};
		VERIFY(x == 5);
	}
	{
		auto x = BigInt1{2} + (-3);
		using result_type = decltype(x);
		VERIFY(x == result_type(-1));
	}
	{
		auto x = (-2) + BigInt2{3};
		VERIFY(x == 1);
	}
	if (bksge::numeric_limits<BigInt1>::is_signed &&
		bksge::numeric_limits<BigInt2>::is_signed)
	{
		auto x = BigInt1(-2) + BigInt2(-3);
		VERIFY(x == -5);
	}
	{
		auto x = BigInt1{1} + BigInt2{999};
		VERIFY(x == 1000);
	}
	{
		auto x = (-10) + BigInt2{1000};
		VERIFY(x == 990);
	}
	{
		auto x = BigInt1{255} + BigInt2{1};
		VERIFY(x == 256);
	}
	{
		auto x = BigInt1{256} + (-1);
		VERIFY(x == 255);
	}
	{
		auto x = BigInt1{255} + BigInt2{255};
		VERIFY(x == 510);
	}
	{
		auto x = BigInt1{255} + BigInt2{256};
		VERIFY(x == 511);
	}
	{
		auto x = BigInt1{0xffff} + BigInt2{1};
		VERIFY(x == 0x10000);
	}
	{
		auto x = BigInt1{1} + BigInt2{0xffffff};
		VERIFY(x == 0x1000000);
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool Add2FloatTest()
{
	{
		auto x = BigInt{0} + 0.0f;
		static_assert(bksge::is_same<float, decltype(x)>::value, "");
		VERIFY(x == 0.0f);
	}
	{
		auto x = BigInt{1} + 2.5f;
		static_assert(bksge::is_same<float, decltype(x)>::value, "");
		VERIFY(x == 3.5f);
	}
	{
		auto x = 3.5f + BigInt{4};
		static_assert(bksge::is_same<float, decltype(x)>::value, "");
		VERIFY(x == 7.5f);
	}
	{
		auto x = BigInt{1} + (-2.5);
		static_assert(bksge::is_same<double, decltype(x)>::value, "");
		VERIFY(x == -1.5);
	}
	{
		auto x = -3.5 + BigInt{4};
		static_assert(bksge::is_same<double, decltype(x)>::value, "");
		VERIFY(x == 0.5);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Add2LargeTest()
{
	{
		auto x = BigInt1{0xffffffff} + BigInt2{0xffffffff};
		VERIFY(x == 0x1fffffffe);
	}
	{
		auto x = BigInt1{"3565257399734975859457283787877529836964"} +
			     BigInt2{"7966969762968552357477389456772596794377"};
		VERIFY(x == BigInt1{"11532227162703528216934673244650126631341"});
	}
	{
		auto x = BigInt1{"3565257399734975859457283787877529836964"} +
			     BigInt2{"-7966969762968552357477389456772596794377"};
		if (bksge::numeric_limits<BigInt1>::is_signed &&
			bksge::numeric_limits<BigInt2>::is_signed)
		{
			VERIFY(x == BigInt1{"-4401712363233576498020105668895066957413"});
		}
	}
	{
		auto x = BigInt1{"9999999999999999999999999999999999999999999999999"} +
			     BigInt2{1};
		VERIFY(x == BigInt1{"10000000000000000000000000000000000000000000000000"});
	}
	//{
	//	auto x = BigInt1{"0xfffffffffffffffffffffffffffffffffffffffffffff"} +
	//		     BigInt2{1};
	//	VERIFY(x == BigInt1{"0x1000000000000000000000000000000000000000000000"});
	//}
	//{
	//	auto x = BigInt1{1} +
	//		     BigInt2{"0xfffffffffffffffffffffffffffffffffffffffffffff"};
	//	VERIFY(x == BigInt1{"0x1000000000000000000000000000000000000000000000"});
	//}
	return true;
}

GTEST_TEST(BigIntTest, AddTest)
{
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::int32_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::int64_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::uint32_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::uint64_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((AddTest<bksge::bigint,     bksge::uint1024_t>()));
//	EXPECT_TRUE((AddTest<bksge::int32_t,    bksge::bigint>()));
//	EXPECT_TRUE((AddTest<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((AddTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((AddTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((AddTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((AddTest<bksge::int1024_t,  bksge::bigint>()));
//	EXPECT_TRUE((AddTest<bksge::uint32_t,   bksge::bigint>()));
//	EXPECT_TRUE((AddTest<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((AddTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((AddTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((AddTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((AddTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((AddFloatTest<bksge::bigint>()));
//	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::int32_t>()));
//	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::int64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::int1024_t>()));
//	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::uint32_t>()));
//	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::uint64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::uint128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((AddFloatTest<bksge::uint1024_t>()));

	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::int32_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::int64_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::uint32_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::uint64_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((Add2Test<bksge::bigint,     bksge::uint1024_t>()));
	EXPECT_TRUE((Add2Test<bksge::int32_t,    bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::uint32_t,   bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2Test<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((Add2FloatTest<bksge::bigint>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Add2FloatTest<bksge::uint1024_t>()));

	EXPECT_TRUE((Add2LargeTest<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((Add2LargeTest<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((Add2LargeTest<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((Add2LargeTest<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((Add2LargeTest<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((Add2LargeTest<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((Add2LargeTest<bksge::bigint,     bksge::uint1024_t>()));
	EXPECT_TRUE((Add2LargeTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((Add2LargeTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((Add2LargeTest<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((Add2LargeTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((Add2LargeTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((Add2LargeTest<bksge::uint1024_t, bksge::bigint>()));

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int256_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int512_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint256_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint512_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Add2LargeTest<bksge::uint1024_t, bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
