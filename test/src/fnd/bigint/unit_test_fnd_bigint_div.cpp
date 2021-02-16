/**
 *	@file	unit_test_fnd_bigint_div.cpp
 *
 *	@brief	bigint::operator/=(), operator/(bigint, bigint) のテスト
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
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded");
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant
BKSGE_WARNING_DISABLE_MSVC(4244);	// conversion from '...' to '...', possible loss of data
BKSGE_WARNING_DISABLE_MSVC(4245);	// conversion from '...' to '...', signed/unsigned mismatch
BKSGE_WARNING_DISABLE_MSVC(4308);	// negative integral constant converted to unsigned type

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool DivTest()
{
	{
		BigInt1 x{100};
		VERIFY(x == 100);

		x /= BigInt2{2};
		VERIFY(x == 50);

		x /= BigInt2{2};
		VERIFY(x == 25);

		x /= BigInt2{2};
		VERIFY(x == 12);

		x /= BigInt2{2};
		VERIFY(x == 6);

		x /= BigInt2{2};
		VERIFY(x == 3);

		x /= BigInt2{2};
		VERIFY(x == 1);

		x /= BigInt2{2};
		VERIFY(x == 0);

		x /= BigInt2{2};
		VERIFY(x == 0);
	}
	if (bksge::numeric_limits<BigInt1>::is_signed)
	{
		BigInt1 x(-256);
		VERIFY(x == -256);

		x /= BigInt2{2};
		VERIFY(x == -128);

		x /= -2;
		VERIFY(x == 64);

		x /= -4;
		VERIFY(x == -16);

		x /= BigInt2{4};
		VERIFY(x == -4);

		x /= BigInt2{5};
		VERIFY(x == 0);

		x /= -1;
		VERIFY(x == 0);
	}
	{
		BigInt1 x{0xffff};
		VERIFY(x == 0xffff);

		x /= x;
		VERIFY(x == 1);
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool DivFloatTest()
{
	{
		BigInt x{10};
		VERIFY(x == 10);

		x /= 0.5f;
		VERIFY(x == 20);

		x /= 1.5;
		VERIFY(x == 13);

		x /= 0.001L;
		VERIFY(x == 13000);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Div2Test()
{
	{
		auto x = BigInt1( 6) / BigInt2( 1);
		VERIFY(x == 6);
	}
	{
		auto x = BigInt1( 6) / BigInt2( 2);
		VERIFY(x == 3);
	}
	{
		auto x = BigInt1( 6) / BigInt2( 3);
		VERIFY(x == 2);
	}
	{
		auto x = BigInt1( 6) / BigInt2(-3);
		if (bksge::numeric_limits<BigInt1>::is_signed &&
			bksge::numeric_limits<BigInt2>::is_signed)
		{
			VERIFY(x == -2);
		}
		//else
		//{
		//	VERIFY(x == 0);
		//}
	}
	{
		auto x = BigInt1(-6) / BigInt2( 3);
		if (bksge::numeric_limits<BigInt1>::is_signed &&
			bksge::numeric_limits<BigInt2>::is_signed)
		{
			VERIFY(x == -2);
		}
	}
	{
		auto x = BigInt1(-6) / BigInt2(-3);
		if (bksge::numeric_limits<BigInt1>::is_signed &&
			bksge::numeric_limits<BigInt2>::is_signed)
		{
			VERIFY(x == 2);
		}
	}
	{
		auto x = BigInt1( 6) / BigInt2( 4);
		VERIFY(x == 1);
	}
	{
		auto x = BigInt1( 6) / BigInt2( 6);
		VERIFY(x == 1);
	}
	{
		auto x = BigInt1( 6) / BigInt2( 7);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt1{0x10000} / BigInt2{2};
		VERIFY(x == 0x8000);
	}
	{
		auto x = BigInt1{0xffff} / BigInt2{2};
		VERIFY(x == 0x7fff);
	}
	return true;
}


template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool Div2FloatTest()
{
	{
		auto x = BigInt{10} / 2.5f;
		static_assert(bksge::is_same<float, decltype(x)>::value, "");
		VERIFY(x == 4.0f);
	}
	{
		auto x = BigInt{3} / 1.5;
		static_assert(bksge::is_same<double, decltype(x)>::value, "");
		VERIFY(x == 2.0);
	}
	{
		auto x = BigInt{5} / 0.1L;
		static_assert(bksge::is_same<long double, decltype(x)>::value, "");
		VERIFY(x == 50.0L);
	}
	{
		auto x = 0.5f / BigInt{2};
		static_assert(bksge::is_same<float, decltype(x)>::value, "");
		VERIFY(x == 0.25f);
	}
	{
		auto x = 2.5 / BigInt{2};
		static_assert(bksge::is_same<double, decltype(x)>::value, "");
		VERIFY(x == 1.25);
	}
	{
		auto x = -35.0L / BigInt{10};
		static_assert(bksge::is_same<long double, decltype(x)>::value, "");
		VERIFY(x == -3.5L);
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Div2LargeTest()
{
	{
		auto x = BigInt1{"8634445089577309591046007474873433396354"} /
			-BigInt2{"9509431914"};
		VERIFY(x == BigInt1{"-907987476819249835058654742987"});
	}
	{
		auto x = -BigInt1{"1310755439459119173246996027623904894831"} /
			BigInt2{"84526411745918709879"};
		VERIFY(x == BigInt1{"-15507051729572655735"});
	}
	{
		auto x = -BigInt1{"38533568648101411188584683464222001686976831106787"} /
			-BigInt2{"504164348379621718380998627378"};
		VERIFY(x == BigInt1{"76430570253425985552"});
	}
	return true;
}

template <typename BigInt1, typename BigInt2>
inline BKSGE_CXX14_CONSTEXPR bool Div2LargeUnsignedTest()
{
	{
		auto x = BigInt1{"8634445089577309591046007474873433396354"} /
			BigInt2{"9509431914"};
		VERIFY(x == BigInt1{"907987476819249835058654742987"});
	}
	{
		auto x = BigInt1{"1310755439459119173246996027623904894831"} /
			BigInt2{"84526411745918709879"};
		VERIFY(x == BigInt1{"15507051729572655735"});
	}
	{
		auto x = BigInt1{"38533568648101411188584683464222001686976831106787"} /
			BigInt2{"504164348379621718380998627378"};
		VERIFY(x == BigInt1{"76430570253425985552"});
	}
	return true;
}

GTEST_TEST(BigIntTest, DivTest)
{
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::int32_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::int64_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::uint32_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::uint64_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((DivTest<bksge::bigint,     bksge::uint1024_t>()));
//	EXPECT_TRUE((DivTest<bksge::int32_t,    bksge::bigint>()));
//	EXPECT_TRUE((DivTest<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((DivTest<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((DivTest<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((DivTest<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((DivTest<bksge::int1024_t,  bksge::bigint>()));
//	EXPECT_TRUE((DivTest<bksge::uint32_t,   bksge::bigint>()));
//	EXPECT_TRUE((DivTest<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((DivTest<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((DivTest<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((DivTest<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((DivTest<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::int64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::uint64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::uint512_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((DivTest<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((DivFloatTest<bksge::bigint>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::int32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::int64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::uint32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::uint64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::uint128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((DivFloatTest<bksge::uint1024_t>()));

	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::int32_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::int64_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::int128_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::int256_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::int512_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::int1024_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::uint32_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::uint64_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::uint128_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::uint256_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::uint512_t>()));
	EXPECT_TRUE((Div2Test<bksge::bigint,     bksge::uint1024_t>()));
	EXPECT_TRUE((Div2Test<bksge::int32_t,    bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::int64_t,    bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::int128_t,   bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::int256_t,   bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::int512_t,   bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::int1024_t,  bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::uint32_t,   bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::uint64_t,   bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::uint128_t,  bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::uint256_t,  bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::uint512_t,  bksge::bigint>()));
	EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::bigint>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::int32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::int64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::int128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::int256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::int512_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::int1024_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint32_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint64_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint128_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::uint32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint256_t, bksge::uint1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::uint32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::int32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::int64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::int128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::uint32_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::uint64_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::uint128_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2Test<bksge::uint1024_t, bksge::uint1024_t>()));

	EXPECT_TRUE((Div2FloatTest<bksge::bigint>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::int32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::int64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::int128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::int256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::int512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::int1024_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::uint32_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::uint64_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::uint128_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::uint256_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::uint512_t>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((Div2FloatTest<bksge::uint1024_t>()));

	EXPECT_TRUE((Div2LargeTest<bksge::bigint, bksge::bigint>()));
	EXPECT_TRUE((Div2LargeTest<bksge::bigint, bksge::int256_t>()));
	EXPECT_TRUE((Div2LargeTest<bksge::bigint, bksge::int512_t>()));
	EXPECT_TRUE((Div2LargeTest<bksge::bigint, bksge::int1024_t>()));
	EXPECT_TRUE((Div2LargeUnsignedTest<bksge::bigint, bksge::uint256_t>()));
	EXPECT_TRUE((Div2LargeUnsignedTest<bksge::bigint, bksge::uint512_t>()));
	EXPECT_TRUE((Div2LargeUnsignedTest<bksge::bigint, bksge::uint1024_t>()));

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeTest<bksge::int256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeTest<bksge::int256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeTest<bksge::int256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::int256_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::int256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::int256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeTest<bksge::int512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeTest<bksge::int512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeTest<bksge::int512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::int512_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::int512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::int512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeTest<bksge::int1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeTest<bksge::int1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeTest<bksge::int1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::int1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::int1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::int1024_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint256_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint256_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint256_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint256_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint256_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint256_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint512_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint512_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint512_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint512_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint512_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint512_t, bksge::uint1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint1024_t, bksge::int256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint1024_t, bksge::int512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint1024_t, bksge::int1024_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint1024_t, bksge::uint256_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint1024_t, bksge::uint512_t>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((Div2LargeUnsignedTest<bksge::uint1024_t, bksge::uint1024_t>()));
}

GTEST_TEST(BigIntTest, DivByZeroTest)
{
	{
		bksge::bigint x{0xFFFFFFFF};
		EXPECT_THROW(x /= 0, bksge::overflow_error);
		EXPECT_THROW(x /= 0.0f, bksge::overflow_error);
		EXPECT_THROW(x /= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 0xFFFFFFFF);
	}
	{
		bksge::int128_t x{1};
		EXPECT_THROW(x /= 0, bksge::overflow_error);
		EXPECT_THROW(x /= 0.0f, bksge::overflow_error);
		EXPECT_THROW(x /= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 1);
	}
	{
		bksge::int256_t x{2};
		EXPECT_THROW(x /= 0, bksge::overflow_error);
		EXPECT_THROW(x /= 0.0f, bksge::overflow_error);
		EXPECT_THROW(x /= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 2);
	}
	{
		bksge::int512_t x{3};
		EXPECT_THROW(x /= 0, bksge::overflow_error);
		EXPECT_THROW(x /= 0.0f, bksge::overflow_error);
		EXPECT_THROW(x /= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 3);
	}
	{
		bksge::int1024_t x{4};
		EXPECT_THROW(x /= 0, bksge::overflow_error);
		EXPECT_THROW(x /= 0.0f, bksge::overflow_error);
		EXPECT_THROW(x /= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 4);
	}
	{
		bksge::uint128_t x{1};
		EXPECT_THROW(x /= 0, bksge::overflow_error);
		EXPECT_THROW(x /= 0.0f, bksge::overflow_error);
		EXPECT_THROW(x /= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 1);
	}
	{
		bksge::uint256_t x{2};
		EXPECT_THROW(x /= 0, bksge::overflow_error);
		EXPECT_THROW(x /= 0.0f, bksge::overflow_error);
		EXPECT_THROW(x /= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 2);
	}
	{
		bksge::uint512_t x{3};
		EXPECT_THROW(x /= 0, bksge::overflow_error);
		EXPECT_THROW(x /= 0.0f, bksge::overflow_error);
		EXPECT_THROW(x /= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 3);
	}
	{
		bksge::uint1024_t x{4};
		EXPECT_THROW(x /= 0, bksge::overflow_error);
		EXPECT_THROW(x /= 0.0f, bksge::overflow_error);
		EXPECT_THROW(x /= bksge::bigint(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::int1024_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint128_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint256_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint512_t(0), bksge::overflow_error);
		EXPECT_THROW(x /= bksge::uint1024_t(0), bksge::overflow_error);
		EXPECT_EQ(x, 4);
	}

	EXPECT_THROW(bksge::bigint(0) / 0, bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) / bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) / bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) / bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) / bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) / bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) / bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) / bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) / bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(0) / bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) / 0, bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) / bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) / bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) / bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) / bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) / bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) / bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) / bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) / bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::bigint(-1) / bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) / 0, bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) / bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) / bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) / bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) / bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) / bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) / bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) / bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) / bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int128_t(-2) / bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) / 0, bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) / bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) / bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) / bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) / bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) / bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) / bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) / bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) / bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int256_t(3) / bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) / 0, bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) / bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) / bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) / bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) / bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) / bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) / bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) / bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) / bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int512_t(-4) / bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) / 0, bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) / bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) / bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) / bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) / bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) / bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) / bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) / bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) / bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::int1024_t(5) / bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) / 0, bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) / bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) / bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) / bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) / bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) / bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) / bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) / bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) / bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint128_t(2) / bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) / 0, bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) / bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) / bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) / bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) / bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) / bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) / bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) / bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) / bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint256_t(3) / bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) / 0, bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) / bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) / bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) / bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) / bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) / bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) / bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) / bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) / bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint512_t(4) / bksge::uint1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) / 0, bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) / bksge::bigint(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) / bksge::int128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) / bksge::int256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) / bksge::int512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) / bksge::int1024_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) / bksge::uint128_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) / bksge::uint256_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) / bksge::uint512_t(0), bksge::overflow_error);
	EXPECT_THROW(bksge::uint1024_t(5) / bksge::uint1024_t(0), bksge::overflow_error);
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
