/**
 *	@file	unit_test_fnd_utility_pair_make_pair.cpp
 *
 *	@brief	make_pair のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace make_pair_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	{
		auto p = bksge::make_pair(1, 2.5f);
		static_assert(bksge::is_same<decltype(p), bksge::pair<int, float>>::value, "");
		VERIFY(p.first  == 1);
		VERIFY(p.second == 2.5f);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, MakePairTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace make_pair_test

}	// namespace bksge_pair_test
