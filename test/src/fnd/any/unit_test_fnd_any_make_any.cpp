/**
 *	@file	unit_test_fnd_any_make_any.cpp
 *
 *	@brief	make_any のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/any/make_any.hpp>
#include <bksge/fnd/any/any_cast.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/initializer_list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_any_test
{

namespace make_any_test
{

struct combined
{
	bksge::vector<int> v;
	bksge::tuple<int, int> t;
	template <typename... Args>
	combined(bksge::initializer_list<int> il, Args&&... args)
		: v(il), t(bksge::forward<Args>(args)...)
	{
	}
};

GTEST_TEST(AnyTest, MakeAnyTest)
{
	using std::get;

	const int i = 42;
	auto o = bksge::make_any<int>(i);
	int& i2 = bksge::any_cast<int&>(o);
	EXPECT_TRUE(i2 == 42);
	EXPECT_TRUE(&i2 != &i);

	auto o2 = bksge::make_any<bksge::tuple<int, int>>(1, 2);
	bksge::tuple<int, int>& t = bksge::any_cast<bksge::tuple<int, int>&>(o2);
	EXPECT_EQ(get<0>(t), 1);
	EXPECT_EQ(get<1>(t), 2);

	auto o3 = bksge::make_any<bksge::vector<int>>({ 42, 666 });
	bksge::vector<int>& v = bksge::any_cast<bksge::vector<int>&>(o3);
	EXPECT_EQ(v[0], 42);
	EXPECT_EQ(v[1], 666);
	EXPECT_EQ(v.size(), 2u);

	auto o4 = bksge::make_any<combined>({ 42, 666 });
	combined& c = bksge::any_cast<combined&>(o4);
	EXPECT_EQ(c.v[0], 42);
	EXPECT_EQ(c.v[1], 666);
	EXPECT_EQ(c.v.size(), 2u);
	EXPECT_EQ(get<0>(c.t), 0);
	EXPECT_EQ(get<1>(c.t), 0);

	auto o5 = bksge::make_any<combined>({ 1, 2 }, 3, 4);
	combined& c2 = bksge::any_cast<combined&>(o5);
	EXPECT_EQ(c2.v[0], 1);
	EXPECT_EQ(c2.v[1], 2);
	EXPECT_EQ(c2.v.size(), 2u);
	EXPECT_EQ(get<0>(c2.t), 3);
	EXPECT_EQ(get<1>(c2.t), 4);
}

}	// namespace make_any_test

}	// namespace bksge_any_test
