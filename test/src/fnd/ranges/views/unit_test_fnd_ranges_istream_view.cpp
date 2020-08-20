/**
 *	@file	unit_test_fnd_ranges_istream_view.cpp
 *
 *	@brief	ranges::istream_view のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/istream_view.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_ranges_test
{

namespace istream_view_test
{

GTEST_TEST(RangesTest, IStreamViewTest)
{
	{
		auto ss = std::istringstream{ "0 1  2   3     4" };
		auto v = bksge::ranges::istream_view<int>(ss);
		auto it = v.begin();
		EXPECT_FALSE(it == v.end());
		EXPECT_TRUE (it != v.end());
		EXPECT_EQ(0, *it);
		EXPECT_EQ(1, *++it);
		it++;
		EXPECT_EQ(2, *it);
		++it;
		EXPECT_EQ(3, *it);
		it++;
		EXPECT_EQ(4, *it);
		EXPECT_FALSE(it == v.end());
		EXPECT_TRUE (it != v.end());
		it++;
		EXPECT_TRUE (it == v.end());
		EXPECT_FALSE(it != v.end());
	}
}

}	// namespace istream_view_test

}	// namespace bksge_ranges_test
