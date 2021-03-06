﻿/**
 *	@file	unit_test_fnd_tuple_tuple_head.cpp
 *
 *	@brief	tuple_head のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_head.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace tuple_head_test
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

GTEST_TEST(TupleTest, TupleHeadTest)
{
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int, double, float> t1(1, 2.5, 3.5f);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1, bksge::tuple_head(t1));
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int, double, float> t1(1, 2.5, 3.5f);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1, bksge::tuple_head(bksge::move(t1)));
	}
	{
		BKSGE_CXX14_CONSTEXPR auto t1 = bksge::make_tuple(1, 2, 3, 4, 5.5, 6.5f, 7);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1, bksge::tuple_head(t1));
	}
	{
		BKSGE_CXX14_CONSTEXPR auto t1 = bksge::tuple_head(bksge::make_tuple(1, 2, 3, 4, 5.5, 6.5f, 7));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1, t1);
	}
	{
		auto t1 = bksge::make_tuple(Noncopyable(1), Noncopyable(2), Noncopyable(3));
		EXPECT_EQ(Noncopyable(1), bksge::tuple_head(bksge::move(t1)));
	}
	{
		BKSGE_CXX14_CONSTEXPR auto t1 = bksge::tuple_head(bksge::make_tuple(Noncopyable(1), Noncopyable(2)));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Noncopyable(1), t1);
	}
	{
		bksge::tuple<bksge::string, float> t1("foo", 1.5f);
		EXPECT_EQ(bksge::string("foo"), bksge::tuple_head(t1));
	}
	{
		bksge::tuple<bksge::string, float> t1("foo", 1.5f);
		EXPECT_EQ(bksge::string("foo"), bksge::tuple_head(bksge::move(t1)));
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int> t1(42);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, bksge::tuple_head(t1));
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int> t1(42);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, bksge::tuple_head(bksge::move(t1)));
	}
	{
		BKSGE_CXX14_CONSTEXPR auto t1 = bksge::tuple_head(bksge::make_tuple(42));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, t1);
	}
}

}	// namespace tuple_head_test

}	// namespace bksge_tuple_test
