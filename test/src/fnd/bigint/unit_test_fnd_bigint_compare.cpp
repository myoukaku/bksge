/**
 *	@file	unit_test_fnd_bigint_compare.cpp
 *
 *	@brief	operator==(bigint, bigint) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool CompareSignedTest()
{
	{
		BigInt1 x1 = -2;

		VERIFY((x1 == -1) == false);
		VERIFY((x1 == -2) == true);
		VERIFY((x1 == -3) == false);
		VERIFY((-1 == x1) == false);
		VERIFY((-2 == x1) == true);
		VERIFY((-3 == x1) == false);

		VERIFY((x1 != -1) == true);
		VERIFY((x1 != -2) == false);
		VERIFY((x1 != -3) == true);
		VERIFY((-1 != x1) == true);
		VERIFY((-2 != x1) == false);
		VERIFY((-3 != x1) == true);

		VERIFY((x1 <  -1) == true);
		VERIFY((x1 <  -2) == false);
		VERIFY((x1 <  -3) == false);
		VERIFY((-1 <  x1) == false);
		VERIFY((-2 <  x1) == false);
		VERIFY((-3 <  x1) == true);

		VERIFY((x1 >  -1) == false);
		VERIFY((x1 >  -2) == false);
		VERIFY((x1 >  -3) == true);
		VERIFY((-1 >  x1) == true);
		VERIFY((-2 >  x1) == false);
		VERIFY((-3 >  x1) == false);

		VERIFY((x1 <= -1) == true);
		VERIFY((x1 <= -2) == true);
		VERIFY((x1 <= -3) == false);
		VERIFY((-1 <= x1) == false);
		VERIFY((-2 <= x1) == true);
		VERIFY((-3 <= x1) == true);

		VERIFY((x1 >= -1) == false);
		VERIFY((x1 >= -2) == true);
		VERIFY((x1 >= -3) == true);
		VERIFY((-1 >= x1) == true);
		VERIFY((-2 >= x1) == true);
		VERIFY((-3 >= x1) == false);
	}
	{
		BigInt1 x1 = -12345;
		BigInt2 x2 = -12345;
		BigInt2 x3 = -12340;
		BigInt2 x4 = -12346;
		BigInt2 x5 =   1234;
		BigInt2 x6 =-123456;

		VERIFY((x1 == x1) == true);
		VERIFY((x1 == x2) == true);
		VERIFY((x1 == x3) == false);
		VERIFY((x1 == x4) == false);
		VERIFY((x1 == x5) == false);
		VERIFY((x1 == x6) == false);

		VERIFY((x1 != x1) == false);
		VERIFY((x1 != x2) == false);
		VERIFY((x1 != x3) == true);
		VERIFY((x1 != x4) == true);
		VERIFY((x1 != x5) == true);
		VERIFY((x1 != x6) == true);

		VERIFY((x1 <  x1) == false);
		VERIFY((x1 <  x2) == false);
		VERIFY((x1 <  x3) == true);
		VERIFY((x1 <  x4) == false);
		VERIFY((x1 <  x5) == true);
		VERIFY((x1 <  x6) == false);

		VERIFY((x1 >  x1) == false);
		VERIFY((x1 >  x2) == false);
		VERIFY((x1 >  x3) == false);
		VERIFY((x1 >  x4) == true);
		VERIFY((x1 >  x5) == false);
		VERIFY((x1 >  x6) == true);

		VERIFY((x1 <= x1) == true);
		VERIFY((x1 <= x2) == true);
		VERIFY((x1 <= x3) == true);
		VERIFY((x1 <= x4) == false);
		VERIFY((x1 <= x5) == true);
		VERIFY((x1 <= x6) == false);

		VERIFY((x1 >= x1) == true);
		VERIFY((x1 >= x2) == true);
		VERIFY((x1 >= x3) == false);
		VERIFY((x1 >= x4) == true);
		VERIFY((x1 >= x5) == false);
		VERIFY((x1 >= x6) == true);
	}
	{
		BigInt1 x1 = -1;
		VERIFY((x1 < 0) == true);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool CompareSignedLargeTest()
{
	{
		BigInt1 x1 {"314159265358979323846264338327950288419716939937510"};
		BigInt2 x2 {"314159265358979323846264338327950288419716939937510"};
		BigInt2 x3 {"414159265358979323846264338327950288419716939937510"};
		BigInt2 x4 {"-314159265358979323846264338327950288419716939937510"};
		BigInt2 x5 {"3141592653589793238462643383279502884197169399375101"};
		BigInt2 x6 {"-9999999999999999999999999999999999999999999999999999"};

		VERIFY((x1 == x1) == true);
		VERIFY((x1 == x2) == true);
		VERIFY((x1 == x3) == false);
		VERIFY((x1 == x4) == false);
		VERIFY((x1 == x5) == false);
		VERIFY((x1 == x6) == false);

		VERIFY((x1 != x1) == false);
		VERIFY((x1 != x2) == false);
		VERIFY((x1 != x3) == true);
		VERIFY((x1 != x4) == true);
		VERIFY((x1 != x5) == true);
		VERIFY((x1 != x6) == true);

		VERIFY((x1 <  x1) == false);
		VERIFY((x1 <  x2) == false);
		VERIFY((x1 <  x3) == true);
		VERIFY((x1 <  x4) == false);
		VERIFY((x1 <  x5) == true);
		VERIFY((x1 <  x6) == false);

		VERIFY((x1 >  x1) == false);
		VERIFY((x1 >  x2) == false);
		VERIFY((x1 >  x3) == false);
		VERIFY((x1 >  x4) == true);
		VERIFY((x1 >  x5) == false);
		VERIFY((x1 >  x6) == true);

		VERIFY((x1 <= x1) == true);
		VERIFY((x1 <= x2) == true);
		VERIFY((x1 <= x3) == true);
		VERIFY((x1 <= x4) == false);
		VERIFY((x1 <= x5) == true);
		VERIFY((x1 <= x6) == false);

		VERIFY((x1 >= x1) == true);
		VERIFY((x1 >= x2) == true);
		VERIFY((x1 >= x3) == false);
		VERIFY((x1 >= x4) == true);
		VERIFY((x1 >= x5) == false);
		VERIFY((x1 >= x6) == true);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool CompareUnsignedTest()
{
	{
		BigInt1 x1 = 2;

		VERIFY((x1 == 1) == false);
		VERIFY((x1 == 2) == true);
		VERIFY((x1 == 3) == false);
		VERIFY((1 == x1) == false);
		VERIFY((2 == x1) == true);
		VERIFY((3 == x1) == false);

		VERIFY((x1 != 1) == true);
		VERIFY((x1 != 2) == false);
		VERIFY((x1 != 3) == true);
		VERIFY((1 != x1) == true);
		VERIFY((2 != x1) == false);
		VERIFY((3 != x1) == true);

		VERIFY((x1 <  1) == false);
		VERIFY((x1 <  2) == false);
		VERIFY((x1 <  3) == true);
		VERIFY((1 <  x1) == true);
		VERIFY((2 <  x1) == false);
		VERIFY((3 <  x1) == false);

		VERIFY((x1 >  1) == true);
		VERIFY((x1 >  2) == false);
		VERIFY((x1 >  3) == false);
		VERIFY((1 >  x1) == false);
		VERIFY((2 >  x1) == false);
		VERIFY((3 >  x1) == true);

		VERIFY((x1 <= 1) == false);
		VERIFY((x1 <= 2) == true);
		VERIFY((x1 <= 3) == true);
		VERIFY((1 <= x1) == true);
		VERIFY((2 <= x1) == true);
		VERIFY((3 <= x1) == false);

		VERIFY((x1 >= 1) == true);
		VERIFY((x1 >= 2) == true);
		VERIFY((x1 >= 3) == false);
		VERIFY((1 >= x1) == false);
		VERIFY((2 >= x1) == true);
		VERIFY((3 >= x1) == true);
	}
	{
		BigInt1 x1 = -1;
		VERIFY((x1 < 0) == false);
	}
	{
		BigInt1 x1 {"123456789012345678"};
		BigInt2 x2 {"123456789012345678"};
		BigInt2 x3 {"123456789012345677"};
		BigInt2 x4 {"123456789012345679"};

		VERIFY((x1 == x1) == true);
		VERIFY((x1 == x2) == true);
		VERIFY((x1 == x3) == false);
		VERIFY((x1 == x4) == false);

		VERIFY((x1 != x1) == false);
		VERIFY((x1 != x2) == false);
		VERIFY((x1 != x3) == true);
		VERIFY((x1 != x4) == true);

		VERIFY((x1 < x1) == false);
		VERIFY((x1 < x2) == false);
		VERIFY((x1 < x3) == false);
		VERIFY((x1 < x4) == true);

		VERIFY((x1 > x1) == false);
		VERIFY((x1 > x2) == false);
		VERIFY((x1 > x3) == true);
		VERIFY((x1 > x4) == false);

		VERIFY((x1 <= x1) == true);
		VERIFY((x1 <= x2) == true);
		VERIFY((x1 <= x3) == false);
		VERIFY((x1 <= x4) == true);

		VERIFY((x1 >= x1) == true);
		VERIFY((x1 >= x2) == true);
		VERIFY((x1 >= x3) == true);
		VERIFY((x1 >= x4) == false);
	}
	return true;
}

GTEST_TEST(BigIntTest, CompareTest)
{
	EXPECT_TRUE((CompareSignedTest<bksge::bigint, bksge::bigint>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareSignedTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareSignedTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareSignedTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareSignedTest<bksge::int1024_t, bksge::int1024_t>()));

	EXPECT_TRUE((CompareSignedLargeTest<bksge::bigint, bksge::bigint>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareSignedLargeTest<bksge::int128_t, bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((CompareSignedLargeTest<bksge::int256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((CompareSignedLargeTest<bksge::int512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((CompareSignedLargeTest<bksge::int1024_t, bksge::int1024_t>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareUnsignedTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareUnsignedTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareUnsignedTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((CompareUnsignedTest<bksge::uint1024_t, bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
