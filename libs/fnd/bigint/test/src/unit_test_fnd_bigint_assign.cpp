/**
 *	@file	unit_test_fnd_bigint_assign.cpp
 *
 *	@brief	bigint::operator=() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_CLANG("-Wsign-compare");
BKSGE_WARNING_DISABLE_MSVC(4245);	// conversion from '...' to '...', signed/unsigned mismatch

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool AssignCopyTest()
{
	BigInt x1{};
	VERIFY(x1 == 0);

	BigInt const x2(334);
	x1 = x2;
	VERIFY(x1 == 334);

	BigInt const x3("12345");
	x1 = x3;
	VERIFY(x1 == 12345);

	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool AssignMoveTest()
{
	BigInt x1{};
	VERIFY(x1 == 0);

	x1 = BigInt(334);
	VERIFY(x1 == 334);

	x1 = BigInt("123456");
	VERIFY(x1 == 123456);

	return true;
}

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool AssignIntTest()
{
	BigInt x1{};
	VERIFY(x1 == 0);

	x1 = (signed char)(-2);
	VERIFY(x1 == -2);

	x1 = (signed short)(-3);
	VERIFY(x1 == -3);

	x1 = (signed int)(-4);
	VERIFY(x1 == -4);

	x1 = (signed long)(-5);
	VERIFY(x1 == -5);

	x1 = (signed long long)(-6);
	VERIFY(x1 == -6);

	x1 = (unsigned char)(2);
	VERIFY(x1 == 2);

	x1 = (unsigned short)(3);
	VERIFY(x1 == 3);

	x1 = (unsigned int)(4);
	VERIFY(x1 == 4);

	x1 = (unsigned long)(5);
	VERIFY(x1 == 5);

	x1 = (unsigned long long)(6);
	VERIFY(x1 == 6);

	return true;
}

GTEST_TEST(BigIntTest, AssignTest)
{
	EXPECT_TRUE(AssignCopyTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCopyTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCopyTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCopyTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCopyTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCopyTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCopyTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCopyTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignCopyTest<bksge::uint1024_t>());

	EXPECT_TRUE(AssignMoveTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignMoveTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignMoveTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignMoveTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignMoveTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignMoveTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignMoveTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignMoveTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignMoveTest<bksge::uint1024_t>());

	EXPECT_TRUE(AssignIntTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIntTest<std::int64_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIntTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIntTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIntTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIntTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIntTest<std::uint64_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIntTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIntTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIntTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AssignIntTest<bksge::uint1024_t>());

	{
		bksge::bigint x{1};
		EXPECT_THROW(x = bksge::bigint{"ab"}, bksge::runtime_error);
		EXPECT_EQ(x, 1);
	}
	{
		bksge::bigint x{-2};
		EXPECT_THROW(x = bksge::bigint{"0b2"}, bksge::runtime_error);
		EXPECT_EQ(x, -2);
	}
	{
		bksge::int128_t x{3};
		EXPECT_THROW(x = bksge::int128_t{"0787"}, bksge::runtime_error);
		EXPECT_EQ(x, 3);
	}
	{
		bksge::int256_t x{-4};
		EXPECT_THROW(x = bksge::int256_t{"0xEFG"}, bksge::runtime_error);
		EXPECT_EQ(x, -4);
	}
	{
		bksge::int512_t x{5};
		EXPECT_THROW(x = bksge::int512_t{" "}, bksge::runtime_error);
		EXPECT_EQ(x, 5);
	}
	{
		bksge::int1024_t x{-6};
		EXPECT_THROW(x = bksge::int1024_t{"0xZZZ"}, bksge::runtime_error);
		EXPECT_EQ(x, -6);
	}
	{
		bksge::uint128_t x{7};
		EXPECT_THROW(x = bksge::uint128_t{"0787"}, bksge::runtime_error);
		EXPECT_EQ(x, 7);
	}
	{
		bksge::uint256_t x{8};
		EXPECT_THROW(x = bksge::uint256_t{"0xEFG"}, bksge::runtime_error);
		EXPECT_EQ(x, 8);
	}
	{
		bksge::uint512_t x{9};
		EXPECT_THROW(x = bksge::uint512_t{" "}, bksge::runtime_error);
		EXPECT_EQ(x, 9);
	}
	{
		bksge::uint1024_t x{10};
		EXPECT_THROW(x = bksge::uint1024_t{"0xZZZ"}, bksge::runtime_error);
		EXPECT_EQ(x, 10);
	}
}

#undef VERIFY

}	// namespace bksge_bigint_test

BKSGE_WARNING_POP();
