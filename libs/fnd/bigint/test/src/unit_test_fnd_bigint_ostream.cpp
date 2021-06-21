/**
 *	@file	unit_test_fnd_bigint_ostream.cpp
 *
 *	@brief	operator<<(ostream, bigint) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline bool OStreamTest()
{
	{
		BigInt const x = 0;
		std::stringstream ss;
		ss << x;
		VERIFY(ss.str() == "0");
	}
	{
		BigInt const x = 123;
		std::stringstream ss;
		ss << x;
		VERIFY(ss.str() == "123");
	}
	{
		BigInt const x = -123;
		std::stringstream ss;
		ss << x;
		VERIFY(ss.str() == "-123");
	}
	{
		BigInt const x = 629968538327;
		std::stringstream ss;
		ss << x;
		VERIFY(ss.str() == "629968538327");
	}
	{
		BigInt const x = -629968538327;
		std::stringstream ss;
		ss << x;
		VERIFY(ss.str() == "-629968538327");
	}
	{
		BigInt const x = 0;
		std::wstringstream ss;
		ss << x;
		VERIFY(ss.str() == L"0");
	}
	{
		BigInt const x(45678);
		std::wstringstream ss;
		ss << x;
		VERIFY(ss.str() == L"45678");
	}
	{
		BigInt const x(-45678);
		std::wstringstream ss;
		ss << x;
		VERIFY(ss.str() == L"-45678");
	}
	{
		BigInt const x(700637945306);
		std::wstringstream ss;
		ss << x;
		VERIFY(ss.str() == L"700637945306");
	}
	{
		BigInt const x(-700637945306);
		std::wstringstream ss;
		ss << x;
		VERIFY(ss.str() == L"-700637945306");
	}
	return true;
}

template <typename BigInt>
inline bool OStreamUnsignedTest()
{
	{
		BigInt const x = 0;
		std::stringstream ss;
		ss << x;
		VERIFY(ss.str() == "0");
	}
	{
		BigInt const x = 123;
		std::stringstream ss;
		ss << x;
		VERIFY(ss.str() == "123");
	}
	{
		BigInt const x = 1000000000;
		std::stringstream ss;
		ss << x;
		VERIFY(ss.str() == "1000000000");
	}
	return true;
}

template <typename BigInt>
inline bool OStreamLargeTest()
{
	{
		BigInt const x{"314159265358979323846264338327950288419716939937510"};
		std::stringstream ss;
		ss << x;
		VERIFY(ss.str() == "314159265358979323846264338327950288419716939937510");
	}
	{
		BigInt const x{"-385335686481014111885846834642220016869768311067870000000000"};
		std::wstringstream ss;
		ss << x;
		VERIFY(ss.str() == L"-385335686481014111885846834642220016869768311067870000000000");
	}
	return true;
}

GTEST_TEST(BigIntTest, OStreamTest)
{
	EXPECT_TRUE(OStreamTest<bksge::bigint>());
	EXPECT_TRUE(OStreamTest<bksge::int64_t>());
	EXPECT_TRUE(OStreamTest<bksge::int128_t>());
	EXPECT_TRUE(OStreamTest<bksge::int256_t>());
	EXPECT_TRUE(OStreamTest<bksge::int512_t>());
	EXPECT_TRUE(OStreamTest<bksge::int1024_t>());

	EXPECT_TRUE(OStreamUnsignedTest<bksge::uint64_t>());
	EXPECT_TRUE(OStreamUnsignedTest<bksge::uint128_t>());
	EXPECT_TRUE(OStreamUnsignedTest<bksge::uint256_t>());
	EXPECT_TRUE(OStreamUnsignedTest<bksge::uint512_t>());
	EXPECT_TRUE(OStreamUnsignedTest<bksge::uint1024_t>());

	EXPECT_TRUE(OStreamLargeTest<bksge::bigint>());
//	EXPECT_TRUE(OStreamLargeTest<bksge::int128_t>());
	EXPECT_TRUE(OStreamLargeTest<bksge::int256_t>());
	EXPECT_TRUE(OStreamLargeTest<bksge::int512_t>());
	EXPECT_TRUE(OStreamLargeTest<bksge::int1024_t>());
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
