/**
 *	@file	unit_test_fnd_tuple_tuple_init.cpp
 *
 *	@brief	tuple_init のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_init.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace tuple_init_test
{

class Noncopyable
{
public:
	BKSGE_CONSTEXPR Noncopyable(int value) : m_value(value) {}

	BKSGE_CONSTEXPR Noncopyable(Noncopyable const& rhs) = delete;

	Noncopyable& operator=(Noncopyable const&) = delete;
	
	BKSGE_CONSTEXPR Noncopyable(Noncopyable&& rhs) : m_value(rhs.m_value) {}

	Noncopyable& operator=(Noncopyable&& rhs);

	BKSGE_CONSTEXPR friend bool operator==(Noncopyable const& lhs, Noncopyable const& rhs)
	{
		return lhs.m_value == rhs.m_value;
	}

private:
	int		m_value;
};

GTEST_TEST(TupleTest, TupleInitTest)
{
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int, double, float> t1(1, 2.5, 3.5f);
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int, double>        t2(1, 2.5);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, bksge::tuple_init(t1));
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int, double, float> t1(1, 2.5, 3.5f);
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int, double>        t2(1, 2.5);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, bksge::tuple_init(bksge::move(t1)));
	}
	{
		BKSGE_CXX14_CONSTEXPR auto t1 = bksge::make_tuple(1, 2, 3, 4, 5.5, 6.5f, 7);
		BKSGE_CXX14_CONSTEXPR auto t2 = bksge::make_tuple(1, 2, 3, 4, 5.5, 6.5f);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, bksge::tuple_init(t1));
	}
	{
		BKSGE_CXX14_CONSTEXPR auto t1 = bksge::tuple_init(bksge::make_tuple(1, 2, 3, 4, 5.5, 6.5f, 7));
		BKSGE_CXX14_CONSTEXPR auto t2 =                   bksge::make_tuple(1, 2, 3, 4, 5.5, 6.5f);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, t1);
	}
	{
		auto t1 = bksge::make_tuple(Noncopyable(1), Noncopyable(2), Noncopyable(3));
		auto t2 = bksge::make_tuple(Noncopyable(1), Noncopyable(2));
		EXPECT_EQ(t2, bksge::tuple_init(bksge::move(t1)));
	}
	{
		BKSGE_CXX14_CONSTEXPR auto t1 = bksge::tuple_init(bksge::make_tuple(Noncopyable(1), Noncopyable(2)));
		BKSGE_CXX14_CONSTEXPR auto t2 =                   bksge::make_tuple(Noncopyable(1));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, t1);
	}
	{
		bksge::tuple<float, std::string> t1(1.5f, "foo");
		bksge::tuple<float>                t2(1.5f);
		EXPECT_EQ(t2, bksge::tuple_init(t1));
	}
	{
		bksge::tuple<float, std::string> t1(1.5f, "foo");
		bksge::tuple<float>                t2(1.5f);
		EXPECT_EQ(t2, bksge::tuple_init(bksge::move(t1)));
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int> t1(42);
		BKSGE_CXX14_CONSTEXPR bksge::tuple<>    t2;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, bksge::tuple_init(t1));
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int> t1(42);
		BKSGE_CXX14_CONSTEXPR bksge::tuple<>    t2;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, bksge::tuple_init(bksge::move(t1)));
	}
	{
		BKSGE_CXX14_CONSTEXPR auto t1 = bksge::tuple_init(bksge::make_tuple(42));
		BKSGE_CXX14_CONSTEXPR auto t2 =                   bksge::make_tuple();
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, t1);
	}
	{
		BKSGE_CONSTEXPR bksge::tuple<> t1;
		BKSGE_CONSTEXPR bksge::tuple<> t2;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, bksge::tuple_init(t1));
	}
	{
		BKSGE_CONSTEXPR bksge::tuple<> t1;
		BKSGE_CONSTEXPR bksge::tuple<> t2;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, bksge::tuple_init(bksge::move(t1)));
	}
	{
		BKSGE_CXX14_CONSTEXPR auto t1 = bksge::tuple_init(bksge::make_tuple());
		BKSGE_CXX14_CONSTEXPR auto t2 =                   bksge::make_tuple();
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(t2, t1);
	}
}

}	// namespace tuple_init_test

}	// namespace bksge_tuple_test
