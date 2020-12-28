
/**
 *	@file	unit_test_fnd_hash_functions_perfect_hash.cpp
 *
 *	@brief	perfect_hash のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/hash_functions/perfect_hash.hpp>
#include <bksge/fnd/hash_functions/djb_hash.hpp>
#include <bksge/fnd/hash_functions/fnv_hash.hpp>
#include <bksge/fnd/hash_functions/murmur_hash_3.hpp>
#include <bksge/fnd/hash_functions/oat_hash.hpp>
#include <bksge/fnd/hash_functions/sax_hash.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/cstddef.hpp>
#include <gtest/gtest.h>

namespace bksge_hash_functions_test
{

namespace perfect_hash_test
{

template <typename T>
class PerfectHashTest : public ::testing::Test {};

using PerfectHashTestTypes =
	::testing::Types<
//		bksge::djb_hash,
		bksge::fnv_hash,
		bksge::murmur_hash_3,
		bksge::oat_hash,
		bksge::sax_hash
	>;

TYPED_TEST_SUITE(PerfectHashTest, PerfectHashTestTypes);

TYPED_TEST(PerfectHashTest, BasicTest)
{
	static const bksge::size_t MAX_NUM = 500;

	bksge::vector<bksge::string> t;
	t.reserve(MAX_NUM);

	for (bksge::size_t i = 0; i < MAX_NUM; i++)
	{
		t.push_back(std::to_string(i));
	}

	bksge::perfect_hash<TypeParam> ph;
	bool r = ph.build(t);
	ASSERT_EQ(true, r);

	// ハッシュ値の範囲はキーの要素数以上
	EXPECT_LE(MAX_NUM, ph.range());

	bksge::vector<int> hash_tbl(ph.range());

	for (bksge::size_t i = 0; i < t.size(); ++i)
	{
		hash_tbl[ph(t[i])]++;
	}

	// 全てのハッシュ値は1回または0回現れるはず
	for (bksge::size_t i = 0; i < ph.range(); i++)
	{
		EXPECT_GE(1, hash_tbl[i]);
	}
}

}	// namespace perfect_hash_test

}	// namespace bksge_hash_functions_test
