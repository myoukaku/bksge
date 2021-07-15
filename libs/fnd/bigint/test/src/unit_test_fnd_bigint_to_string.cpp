/**
 *	@file	unit_test_fnd_bigint_to_string.cpp
 *
 *	@brief	to_string(bigint) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4146);	// unary minus operator applied to unsigned type, result still unsigned
BKSGE_WARNING_DISABLE_MSVC(4245);	// conversion from '...' to '...', signed/unsigned mismatch

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool ToStringTest()
{
	{
		BigInt x = 0;
		VERIFY(bksge::to_string( x) == "0");
		VERIFY(bksge::to_string(-x) == "0");
	}
	{
		BigInt x = 1;
		VERIFY(bksge::to_string( x) == "1");
		VERIFY(bksge::to_string(-x) == "-1");
	}
	{
		BigInt x = 1234567;
		VERIFY(bksge::to_string( x) == "1234567");
		VERIFY(bksge::to_string(-x) == "-1234567");
	}
	{
		BigInt x = -1234567890;
		VERIFY(bksge::to_string( x) == "-1234567890");
		VERIFY(bksge::to_string(-x) == "1234567890");
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool ToStringUnsignedTest()
{
	{
		BigInt x = 0;
		VERIFY(bksge::to_string( x) == "0");
		VERIFY(bksge::to_string(-x) == "0");
	}
	{
		BigInt x = 1;
		VERIFY(bksge::to_string(x) == "1");
	}
	{
		BigInt x = -1;
		switch (sizeof(BigInt))
		{
		case  1:	VERIFY(bksge::to_string(x) == "255"); break;
		case  2:	VERIFY(bksge::to_string(x) == "65535"); break;
		case  4:	VERIFY(bksge::to_string(x) == "4294967295"); break;
		case  8:	VERIFY(bksge::to_string(x) == "18446744073709551615"); break;
		case 16:	VERIFY(bksge::to_string(x) == "340282366920938463463374607431768211455"); break;
		case 32:	VERIFY(bksge::to_string(x) == "115792089237316195423570985008687907853269984665640564039457584007913129639935"); break;
		case 64:	VERIFY(bksge::to_string(x) == "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084095"); break;
		case 128:	VERIFY(bksge::to_string(x) == "179769313486231590772930519078902473361797697894230657273430081157732675805500963132708477322407536021120113879871393357658789768814416622492847430639474124377767893424865485276302219601246094119453082952085005768838150682342462881473913110540827237163350510684586298239947245938479716304835356329624224137215"); break;
		default:	VERIFY(false); break;
		}
	}
	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool ToStringLargeTest()
{
	{
		BigInt x{"12345678900987654321"};
		VERIFY(bksge::to_string( x) == "12345678900987654321");
		VERIFY(bksge::to_string(-x) == "-12345678900987654321");
	}
	{
		BigInt x{"100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"};
		VERIFY(bksge::to_string( x) == "100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
		VERIFY(bksge::to_string(-x) == "-100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	}
	{
		BigInt x = 0xfffffffffffffff;
		VERIFY(bksge::to_string(x) == "1152921504606846975");
		x *= x;
		VERIFY(bksge::to_string(x) == "1329227995784915870597964051066650625");
		x *= x;
		VERIFY(bksge::to_string(x) == "1766847064778384323453315337279363090369463762983877456457806055812890625");
		x *= 10000000000;
		VERIFY(bksge::to_string(x) == "17668470647783843234533153372793630903694637629838774564578060558128906250000000000");
	}
	return true;
}

GTEST_TEST(BigIntTest, ToStringTest)
{
	EXPECT_TRUE(ToStringTest<bksge::bigint>());
	EXPECT_TRUE(ToStringTest<std::int64_t>());
	EXPECT_TRUE(ToStringTest<bksge::int128_t>());
	EXPECT_TRUE(ToStringTest<bksge::int256_t>());
	EXPECT_TRUE(ToStringTest<bksge::int512_t>());
	EXPECT_TRUE(ToStringTest<bksge::int1024_t>());

	EXPECT_TRUE(ToStringUnsignedTest<std::uint64_t>());
	EXPECT_TRUE(ToStringUnsignedTest<bksge::uint128_t>());
	EXPECT_TRUE(ToStringUnsignedTest<bksge::uint256_t>());
	EXPECT_TRUE(ToStringUnsignedTest<bksge::uint512_t>());
	EXPECT_TRUE(ToStringUnsignedTest<bksge::uint1024_t>());

	EXPECT_TRUE(ToStringLargeTest<bksge::bigint>());
	EXPECT_TRUE(ToStringLargeTest<bksge::int1024_t>());
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
