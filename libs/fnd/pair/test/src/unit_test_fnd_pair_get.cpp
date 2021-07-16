/**
 *	@file	unit_test_fnd_utility_pair_get.cpp
 *
 *	@brief	get のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

namespace bksge_pair_test
{

namespace get_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	using std::get;
	{
		bksge::pair<int, int> p(1, 2);
		int& i1 = get<0>(p);
		VERIFY(i1  == 1);
		i1 = 3;
		int const& i2 = get<1>(p);
		VERIFY(i2  == 2);
		int&& i3 = get<0>(bksge::move(p));
		VERIFY(i3  == 3);
		int&& i4 = get<1>(bksge::move(p));
		VERIFY(i4  == 2);
	}
	{
		bksge::pair<int, int> const p(3, 4);
		int const& i1 = get<0>(p);
		VERIFY(i1  == 3);
		int const& i2 = get<1>(p);
		VERIFY(i2  == 4);
		int const&& i3 = get<0>(bksge::move(p));
		VERIFY(i3  == 3);
		int const&& i4 = get<1>(bksge::move(p));
		VERIFY(i4  == 4);
	}
	{
		bksge::pair<float, int> p(1, 2);
		float& f = get<float>(p);
		VERIFY(f == 1);
		int& i   = get<int>(p);
		VERIFY(i == 2);
	}
	{
		bksge::pair<float, int> p(1, 2);
		float&& f = get<float>(bksge::move(p));
		VERIFY(f == 1);
		int&& i   = get<int>(bksge::move(p));
		VERIFY(i == 2);
	}
	{
		bksge::pair<float, int> const p(1, 2);
		float const& f = get<float>(p);
		VERIFY(f == 1);
		int const& i   = get<int>(p);
		VERIFY(i == 2);
	}
	{
		bksge::pair<float, int> const p(1, 2);
		float const&& f = get<float>(bksge::move(p));
		VERIFY(f == 1);
		int const&& i   = get<int>(bksge::move(p));
		VERIFY(i == 2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, GetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace get_test

}	// namespace bksge_pair_test

BKSGE_WARNING_POP();
