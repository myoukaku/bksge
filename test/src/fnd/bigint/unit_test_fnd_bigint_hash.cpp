/**
 *	@file	unit_test_fnd_bigint_hash.cpp
 *
 *	@brief	hash<bigint> のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/bigint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_bigint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline BKSGE_CXX14_CONSTEXPR bool HashTest()
{
	{
		BigInt v1 = 0;
		BigInt v2 = 1;

		bksge::hash<BigInt> h{};
		VERIFY(h(v1) == h(v1));
		VERIFY(h(v2) == h(v2));
		VERIFY(h(v1) != h(v2));

		v2 = 0;
		VERIFY(h(v1) == h(v2));

		v1 = 0xffffffffffffffff;
		v2 = 0xfffffffffffffffe;
		VERIFY(h(v1) != h(v2));

		v1 = 0x0000000100000000;
		v2 = 0x0000000000000001;
		VERIFY(h(v1) != h(v2));

		v1 = 0xffffffffffffffff;
		v2 = 0xffffffffffffffff;
		VERIFY(h(v1) == h(v2));

		v1 =  1;
		v2 = -1;
		VERIFY(h(v1) != h(v2));

		v1 = -1;
		v2 = -1;
		VERIFY(h(v1) == h(v2));
	}
	return true;
}

GTEST_TEST(BigIntTest, HashTest)
{
	EXPECT_TRUE(HashTest<bksge::bigint>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(HashTest<bksge::int128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(HashTest<bksge::int256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(HashTest<bksge::int512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(HashTest<bksge::int1024_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(HashTest<bksge::uint128_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(HashTest<bksge::uint256_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(HashTest<bksge::uint512_t>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(HashTest<bksge::uint1024_t>());
}

#undef VERIFY

}	// namespace bksge_bigint_test
