/**
 *	@file	unit_test_fnd_bigint_istream.cpp
 *
 *	@brief	operator>>(istream, bigint) のテスト
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
inline bool IStreamTest()
{
	{
		std::stringstream ss;
		ss << "0";
		BigInt x{};
		ss >> x;
		VERIFY(x == 0);
	}
	{
		std::stringstream ss;
		ss << "1";
		BigInt x{};
		ss >> x;
		VERIFY(x == 1);
	}
	{
		std::stringstream ss;
		ss << "-2";
		BigInt x{};
		ss >> x;
		VERIFY(x == BigInt(-2));
	}
	{
		std::stringstream ss;
		ss << "12345";
		BigInt x{};
		ss >> x;
		VERIFY(x == 12345);
	}
	return true;
}

template <typename BigInt>
inline bool IStreamLargeTest()
{
	{
		std::stringstream ss;
		ss << "0xdeadbeef";
		BigInt x{};
		ss >> x;
		VERIFY(x == 3735928559);
	}
	{
		std::stringstream ss;
		ss << "0777777777";
		BigInt x{};
		ss >> x;
		VERIFY(x == BigInt{"134217727"});
	}
	{
		std::stringstream ss;
		ss << "314159265358979323846264338327950288419716939937510";
		BigInt x = 0;
		ss >> x;
		VERIFY(x == BigInt{"314159265358979323846264338327950288419716939937510"});
	}
	{
		std::stringstream ss;
		ss << "-10000000000000000000000000000000000000000000000000000000000000000000000";
		BigInt x = 0;
		ss >> x;
		VERIFY(x == BigInt{"-10000000000000000000000000000000000000000000000000000000000000000000000"});
	}
	return true;
}

GTEST_TEST(BigIntTest, IStreamTest)
{
	EXPECT_TRUE(IStreamTest<bksge::bigint>());
	EXPECT_TRUE(IStreamTest<bksge::int64_t>());
	EXPECT_TRUE(IStreamTest<bksge::int128_t>());
	EXPECT_TRUE(IStreamTest<bksge::int256_t>());
	EXPECT_TRUE(IStreamTest<bksge::int512_t>());
	EXPECT_TRUE(IStreamTest<bksge::int1024_t>());
	EXPECT_TRUE(IStreamTest<bksge::uint64_t>());
	EXPECT_TRUE(IStreamTest<bksge::uint128_t>());
	EXPECT_TRUE(IStreamTest<bksge::uint256_t>());
	EXPECT_TRUE(IStreamTest<bksge::uint512_t>());
	EXPECT_TRUE(IStreamTest<bksge::uint1024_t>());

	EXPECT_TRUE(IStreamLargeTest<bksge::bigint>());
//	EXPECT_TRUE(IStreamLargeTest<bksge::int128_t>());
	EXPECT_TRUE(IStreamLargeTest<bksge::int256_t>());
	EXPECT_TRUE(IStreamLargeTest<bksge::int512_t>());
	EXPECT_TRUE(IStreamLargeTest<bksge::int1024_t>());
//	EXPECT_TRUE(IStreamLargeTest<bksge::uint128_t>());
	EXPECT_TRUE(IStreamLargeTest<bksge::uint256_t>());
	EXPECT_TRUE(IStreamLargeTest<bksge::uint512_t>());
	EXPECT_TRUE(IStreamLargeTest<bksge::uint1024_t>());
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
