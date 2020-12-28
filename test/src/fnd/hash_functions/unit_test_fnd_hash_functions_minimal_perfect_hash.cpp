/**
 *	@file	unit_test_fnd_hash_functions_minimal_perfect_hash.cpp
 *
 *	@brief	minimal_perfect_hash のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/hash_functions/minimal_perfect_hash.hpp>
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

namespace minimal_perfect_hash_test
{

template <typename T>
class MinimalPerfectHashTest : public ::testing::Test {};

using MinimalPerfectHashTestTypes =
	::testing::Types<
//		bksge::djb_hash,
		bksge::fnv_hash,
		bksge::murmur_hash_3,
		bksge::oat_hash,
		bksge::sax_hash
	>;

TYPED_TEST_SUITE(MinimalPerfectHashTest, MinimalPerfectHashTestTypes);

TYPED_TEST(MinimalPerfectHashTest, BasicTest)
{
	static const bksge::size_t MAX_NUM = 500;

	bksge::vector<bksge::string> t;
	t.reserve(MAX_NUM);

	for (bksge::size_t i = 0; i < MAX_NUM; i++)
	{
		t.push_back(std::to_string(i));
	}

	bksge::minimal_perfect_hash<TypeParam> mph;
	bool r = mph.build(t);
	ASSERT_EQ(true, r);

	// ハッシュ値の範囲はキーの要素数に等しい
	EXPECT_EQ(MAX_NUM, mph.range());

	bksge::vector<int> hash_tbl(mph.range());

	for (bksge::size_t i = 0; i < t.size(); ++i)
	{
		hash_tbl[mph(t[i])]++;
	}

	// 全てのハッシュ値はただ1度だけ現れるはず
	for (bksge::size_t i = 0; i < MAX_NUM; i++)
	{
		EXPECT_EQ(1, hash_tbl[i]);
	}
}

}	// namespace minimal_perfect_hash_test

}	// namespace bksge_hash_functions_test
