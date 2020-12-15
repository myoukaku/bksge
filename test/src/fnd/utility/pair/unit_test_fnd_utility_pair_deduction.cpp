/**
 *	@file	unit_test_fnd_utility_pair_deduction.cpp
 *
 *	@brief	deduction guides のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace deduction_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	{
		bksge::pair p{5, 6u};
		static_assert(bksge::is_same<decltype(p), bksge::pair<int, unsigned int>>::value, "");
		VERIFY(p.first  == 5);
		VERIFY(p.second == 6u);
	}
	{
		float const f = 0.5f;
		int const i = 2;
		bksge::pair p{f, i};
		static_assert(bksge::is_same<decltype(p), bksge::pair<float, int>>::value, "");
		VERIFY(p.first  == 0.5f);
		VERIFY(p.second == 2);
	}
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, DeductionTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test01()));
}

}	// namespace deduction_test

}	// namespace bksge_pair_test
