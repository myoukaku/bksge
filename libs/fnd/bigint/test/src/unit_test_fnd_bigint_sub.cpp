/**
 *	@file	unit_test_fnd_bigint_sub.cpp
 *
 *	@brief	bigint::operator-=(), operator-(bigint, bigint) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <cstdint>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded");
BKSGE_WARNING_DISABLE_CLANG("-Wsign-compare");
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant
BKSGE_WARNING_DISABLE_MSVC(4245);	// conversion from '...' to '...', signed/unsigned mismatch
BKSGE_WARNING_DISABLE_MSVC(4308);	// negative integral constant converted to unsigned type

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	BigInt1 x = 9630;
	VERIFY(x == 9630);

	x -= 0;
	VERIFY(x == 9630);

	x -= 5248;
	VERIFY(x == 4382);

	x -= BigInt2{3758};
	VERIFY(x == 624);

	x -= 623;
	VERIFY(x == 1);

	x -= 2;
	VERIFY(x == -1);

	x -= BigInt2{12};
	VERIFY(x == -13);

	x -= -30;
	VERIFY(x == 17);

	x -= BigInt2(45);
	VERIFY(x == -28);

	x -= x;
	VERIFY(x == 0);

	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool SubFloatTest()
{
	BigInt x{10000};
	VERIFY(x == 10000);

	x -= 0.5f;
	VERIFY(x == 10000);

	x -= 2.5;
	VERIFY(x ==  9998);

	x -= 3.5L;
	VERIFY(x ==  9995);

	x -= 123.456;
	VERIFY(x ==  9872);

	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Sub2Test()
{
	{
		auto x = BigInt1{0} - BigInt2{0};
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1{1} - BigInt2{0};
		VERIFY(x == 1);
	}
	{
		auto x = BigInt1{5} - BigInt2{2};
		VERIFY(x == 3);
	}
	{
		auto x = BigInt1{1000} - BigInt2{1};
		VERIFY(x == 999);
	}
	{
		auto x = BigInt1{1000} - BigInt2{999};
		VERIFY(x == 1);
	}
	{
		auto x = BigInt1{1000} - BigInt2{1000};
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1{1000} - BigInt2{1001};
		VERIFY(x == -1);
	}
	{
		auto x = BigInt1( 2) - BigInt2( 5);
		VERIFY(x == -3);
	}
	{
		auto x = BigInt1( 2) - (-5);
		VERIFY(x == 7);
	}
	{
		auto x = -2 - BigInt2( 5);
		VERIFY(x == -7);
	}
	{
		auto x = BigInt1(-2) - BigInt2(-5);
		if (std::numeric_limits<BigInt1>::is_signed &&
			std::numeric_limits<BigInt2>::is_signed)
		{
			VERIFY(x == 3);
		}
	}
	{
		auto x = BigInt1{256} - BigInt2{1};
		VERIFY(x == 255);
	}
	{
		auto x = BigInt1{0x10000} - BigInt2{1};
		VERIFY(x == 0xffff);
	}
	{
		auto x = BigInt1{0x1000000} - BigInt2{1};
		VERIFY(x == 0xffffff);
	}
	{
		auto x = BigInt1{0x1000000} - BigInt2{0xffffff};
		VERIFY(x == 1);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Sub2LargeTest()
{
	{
		auto x = BigInt1{"8427663852327746832635939785432364562824"} -
			     BigInt2{"7567723894568827633575594573939298395955"};
		VERIFY(x == BigInt1{"859939957758919199060345211493066166869"});
	}
	{
		auto x = BigInt1{"4831358420296681146974351689067644777329"} -
			     BigInt2{"8250655382930189933211483422173351786903"};
		if (std::numeric_limits<BigInt1>::is_signed)
		{
			VERIFY(x == BigInt1{"-3419296962633508786237131733105707009574"});
		}
	}
	{
		auto x = BigInt1{"0x1000000000000000000000000000000000000000000000"} -
			     BigInt2{1};
		VERIFY(x == BigInt1{"0xfffffffffffffffffffffffffffffffffffffffffffff"});
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool Sub2FloatTest()
{
	{
		auto x = BigInt{0} - 0.0f;
		static_assert(bksge::is_same<float, decltype(x)>::value, "");
		VERIFY(x == 0.0f);
	}
	{
		auto x = BigInt{1} - 2.5f;
		static_assert(bksge::is_same<float, decltype(x)>::value, "");
		VERIFY(x == -1.5f);
	}
	{
		auto x = 3.5f - BigInt{4};
		static_assert(bksge::is_same<float, decltype(x)>::value, "");
		VERIFY(x == -0.5f);
	}
	{
		auto x = BigInt{1} - (-2.5);
		static_assert(bksge::is_same<double, decltype(x)>::value, "");
		VERIFY(x == 3.5);
	}
	{
		auto x = -3.5 - BigInt{4};
		static_assert(bksge::is_same<double, decltype(x)>::value, "");
		VERIFY(x == -7.5);
	}
	return true;
}

GTEST_TEST(BigIntTest, SubTest)
{
	EXPECT_TRUE((SubTest<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     std::int32_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     std::int64_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     std::uint32_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     std::uint64_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((SubTest<bksge::bigint,     bksge::uint1024_t>()));
//	EXPECT_TRUE((SubTest<std::int32_t,    bksge::bigint>()));
//	EXPECT_TRUE((SubTest<std::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((SubTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((SubTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((SubTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((SubTest<bksge::int1024_t,  bksge::bigint>()));
//	EXPECT_TRUE((SubTest<std::uint32_t,   bksge::bigint>()));
//	EXPECT_TRUE((SubTest<std::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((SubTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((SubTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((SubTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((SubTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, std::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, std::uint32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubTest<std::int32_t, std::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, std::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, std::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int128_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int128_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int256_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int256_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int512_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int512_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int1024_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int1024_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, std::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, std::uint32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubTest<std::uint32_t, std::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, std::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, std::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<std::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint128_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint128_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint256_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint256_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint512_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint512_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint1024_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint1024_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((SubTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((SubFloatTest<bksge::bigint>()));
//	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<std::int32_t>()));
//	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<std::int64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<bksge::int1024_t>()));
//	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<std::uint32_t>()));
//	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<std::uint64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<bksge::uint128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((SubFloatTest<bksge::uint1024_t>()));

	EXPECT_TRUE((Sub2Test<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     std::int32_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     std::int64_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     std::uint32_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     std::uint64_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((Sub2Test<bksge::bigint,     bksge::uint1024_t>()));
	EXPECT_TRUE((Sub2Test<std::int32_t,    bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<std::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<std::uint32_t,   bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<std::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((Sub2Test<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<std::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, std::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, std::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2Test<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((Sub2FloatTest<bksge::bigint>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<std::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<std::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<std::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<std::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Sub2FloatTest<bksge::uint1024_t>()));

	EXPECT_TRUE((Sub2LargeTest<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::bigint,     bksge::uint1024_t>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((Sub2LargeTest<bksge::uint1024_t, bksge::bigint>()));

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int256_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int512_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint256_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint512_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Sub2LargeTest<bksge::uint1024_t, bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
