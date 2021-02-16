/**
 *	@file	unit_test_fnd_bigint_mul.cpp
 *
 *	@brief	bigint::operator*=(), operator*(bigint, bigint) のテスト
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
BKSGE_WARNING_DISABLE_CLANG("-Wsign-compare");
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant
BKSGE_WARNING_DISABLE_MSVC(4244);	// conversion from '...' to '...', possible loss of data
BKSGE_WARNING_DISABLE_MSVC(4308);	// negative integral constant converted to unsigned type

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool MulTest()
{
	{
		BigInt1 x{1};
		VERIFY(x == 1);

		x *= BigInt2{2};
		VERIFY(x == 2);

		x *= BigInt2{2};
		VERIFY(x == 4);

		x *= BigInt2{12345};
		VERIFY(x == 49380);

		x *= -1;
		VERIFY(x == -49380);

		x *= 0;
		VERIFY(x == 0);
	}
	{
		BigInt1 x{2};
		VERIFY(x == 2);

		x *= x;
		VERIFY(x == 4);

		x *= x;
		VERIFY(x == 16);

		x *= x;
		VERIFY(x == 256);

		x *= x;
		VERIFY(x == 65536);

		x *= x;
		VERIFY(x == 4294967296);
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool MulFloatTest()
{
	{
		BigInt x{10};
		VERIFY(x == 10);

		x *= 2.5f;
		VERIFY(x == 25);

		x *= 0.5;
		VERIFY(x == 12);

		if (bksge::numeric_limits<BigInt>::is_signed)
		{
			x *= -3.5;
			VERIFY(x == -42);
		}
	}
	{
		BigInt x{1000000000};
		VERIFY(x == 1000000000);

		x *= 0.5f;
		VERIFY(x == 500000000);

		x *= 0.25;
		VERIFY(x == 125000000);

		x *= 0.1;
		VERIFY(x == 12500000);
	}
	{
		BigInt x{1000000000};
		VERIFY(x == 1000000000);

		x *= 0.999999999;
		VERIFY(x == 999999999);

		x *= 0.0001;
		VERIFY(x == 99999);
	}
	{
		BigInt x{100000};
		VERIFY(x == 100000);

		x *= 1234.56789;
		VERIFY(x == 123456789);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool MulLargeTest()
{
	{
		BigInt1 x{2};
		VERIFY(x == 2);

		x *= x;
		VERIFY(x == 4);

		x *= x;
		VERIFY(x == 16);

		x *= x;
		VERIFY(x == 256);

		x *= x;
		VERIFY(x == 65536);

		x *= x;
		VERIFY(x == 4294967296);

		x *= x;
		VERIFY(x == BigInt1{"18446744073709551616"});

		x *= x;
		VERIFY(x == BigInt1{"340282366920938463463374607431768211456"});
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Mul2Test()
{
	{
		auto x = BigInt1(2) * BigInt2(3);
		VERIFY(x == 6);
	}
	{
		auto x = BigInt1(2) * -3;
		VERIFY(x == -6);
	}
	{
		auto x = -2 * BigInt2(3);
		VERIFY(x == -6);
	}
	if (bksge::numeric_limits<BigInt1>::is_signed &&
		bksge::numeric_limits<BigInt2>::is_signed)
	{
		auto x = BigInt1(-2) * BigInt2(-3);
		VERIFY(x == 6);
	}
	{
		auto x = BigInt2(-3) * BigInt2( 0);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1( 3) * BigInt2( 0);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1( 0) * BigInt2( 256);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1( 0) * BigInt2(-256);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1{3} * BigInt2{4} * BigInt1{5};
		VERIFY(x == 60);
	}
	{
		auto x = BigInt1{123} * BigInt2{0};
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1{4824} * BigInt2{31};
		VERIFY(x == 149544);
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool Mul2FloatTest()
{
	{
		auto x = BigInt{0} * 0.0f;
		static_assert(bksge::is_same<float, decltype(x)>::value, "");
		VERIFY(x == 0.0f);
	}
	{
		auto x = BigInt{2} * 2.5f;
		static_assert(bksge::is_same<float, decltype(x)>::value, "");
		VERIFY(x == 5.0f);
	}
	{
		auto x = 3.5 * BigInt{4};
		static_assert(bksge::is_same<double, decltype(x)>::value, "");
		VERIFY(x == 14.0);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Mul2LargeTest()
{
	{
		auto x = BigInt1{"49380"} *
			BigInt2{"315921325115052764877243681807"};
		using result_type = decltype(x);
		VERIFY(x == result_type{"15600195034181305529638293007629660"});
	}
	{
		auto x = BigInt1{"36968175473499613142"} *
			BigInt2{"190512936091683569991370045758"};
		using result_type = decltype(x);
		VERIFY(x == result_type{"7042915651408975798024456175730948594979838151636"});
	}
	{
		auto x = -BigInt1{"36968175473499613142"} *
			BigInt2{"190512936091683569991370045758"};
		using result_type = decltype(x);
		if (bksge::numeric_limits<BigInt1>::is_signed)
		{
			VERIFY(x == result_type{"-7042915651408975798024456175730948594979838151636"});
		}
	}
	{
		auto x = BigInt1{"36968175473499613142"} *
			-BigInt2{"190512936091683569991370045758"};
		using result_type = decltype(x);
		if (bksge::numeric_limits<BigInt2>::is_signed)
		{
			VERIFY(x == result_type{"-7042915651408975798024456175730948594979838151636"});
		}
	}
	return true;
}

GTEST_TEST(BigIntTest, MulTest)
{
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::int32_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::int64_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::uint32_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::uint64_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((MulTest<bksge::bigint,     bksge::uint1024_t>()));
//	EXPECT_TRUE((MulTest<bksge::int32_t,    bksge::bigint>()));
//	EXPECT_TRUE((MulTest<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((MulTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((MulTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((MulTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((MulTest<bksge::int1024_t,  bksge::bigint>()));
//	EXPECT_TRUE((MulTest<bksge::uint32_t,   bksge::bigint>()));
//	EXPECT_TRUE((MulTest<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((MulTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((MulTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((MulTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::bigint>()));

//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::int512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::int1024_t, bksge::int64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::int1024_t, bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::int1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::int1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::int1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::int1024_t, bksge::uint64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::int1024_t, bksge::uint128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::int1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::int1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::int1024_t, bksge::uint1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::int32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::int1024_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::uint32_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::int64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::int128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::int256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::int512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::uint64_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::uint128_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::uint256_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::uint512_t>()));
//	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulTest<bksge::uint512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::int64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::uint64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::uint128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((MulFloatTest<bksge::bigint>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::int32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::int64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::uint32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::uint64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::uint128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulFloatTest<bksge::uint1024_t>()));

	EXPECT_TRUE((MulLargeTest<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((MulLargeTest<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((MulLargeTest<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((MulLargeTest<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((MulLargeTest<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((MulLargeTest<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((MulLargeTest<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((MulLargeTest<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((MulLargeTest<bksge::bigint,     bksge::uint1024_t>()));
	EXPECT_TRUE((MulLargeTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((MulLargeTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((MulLargeTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((MulLargeTest<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((MulLargeTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((MulLargeTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((MulLargeTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((MulLargeTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::int512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::int1024_t, bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::int1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::int1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::int1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::int1024_t, bksge::uint128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::int1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::int1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((MulLargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::uint1024_t, bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::uint1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::uint1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::uint1024_t, bksge::uint128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((MulLargeTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::int32_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::int64_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::uint32_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::uint64_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((Mul2Test<bksge::bigint,     bksge::uint1024_t>()));
	EXPECT_TRUE((Mul2Test<bksge::int32_t,    bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::uint32_t,   bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::int32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::int64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::int32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::int64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2Test<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((Mul2FloatTest<bksge::bigint>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Mul2FloatTest<bksge::uint1024_t>()));

	EXPECT_TRUE((Mul2LargeTest<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::bigint,     bksge::uint1024_t>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((Mul2LargeTest<bksge::uint1024_t, bksge::bigint>()));

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int256_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int512_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::int1024_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint256_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint512_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Mul2LargeTest<bksge::uint1024_t, bksge::uint1024_t>()));
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
