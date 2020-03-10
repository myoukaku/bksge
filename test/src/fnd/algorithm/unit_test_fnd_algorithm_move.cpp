/**
 *	@file	unit_test_fnd_algorithm_move.cpp
 *
 *	@brief	move のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/move.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <array>
#include <iterator>

namespace bksge_algorithm_test
{

namespace move_test
{

struct noncopyable
{
public:
	noncopyable()
		: value(0)
	{}

	noncopyable(int v)
		: value(v)
	{
	}

	noncopyable(noncopyable&& rhs)
		: value(bksge::move(rhs.value))
	{
		rhs.value = -1;
	}
	
	noncopyable& operator=(noncopyable&& rhs)
	{
		value = bksge::move(rhs.value);
		rhs.value = -1;
		return *this;
	}

	int get() const { return value; }

private:
	noncopyable(noncopyable const&) = delete;
	noncopyable& operator=(noncopyable const&) = delete;

	int value;
};

GTEST_TEST(AlgorithmTest, MoveTest)
{
	{
		noncopyable a1[] =
		{
			noncopyable(1),
			noncopyable(2),
			noncopyable(3),
		};

		noncopyable a2[3];

		auto it = bksge::move(bksge::begin(a1), bksge::end(a1), bksge::begin(a2));

		EXPECT_EQ(1, a2[0].get());
		EXPECT_EQ(2, a2[1].get());
		EXPECT_EQ(3, a2[2].get());
		EXPECT_TRUE(it == bksge::end(a2));
	}
	{
		std::array<noncopyable, 4> a1 =
		{{
			noncopyable(4),
			noncopyable(5),
			noncopyable(6),
			noncopyable(7),
		}};

		noncopyable a2[5];

		auto it = bksge::move(bksge::begin(a1), bksge::end(a1), bksge::begin(a2));

		EXPECT_EQ(4, a2[0].get());
		EXPECT_EQ(5, a2[1].get());
		EXPECT_EQ(6, a2[2].get());
		EXPECT_EQ(7, a2[3].get());
		EXPECT_EQ(0, a2[4].get());
		EXPECT_TRUE(it == bksge::begin(a2) + 4);
	}
	{
		bksge::vector<noncopyable> v;
		v.emplace_back(noncopyable(5));
		v.emplace_back(noncopyable(6));
		v.emplace_back(noncopyable(7));
		v.emplace_back(noncopyable(8));
		v.emplace_back(noncopyable(9));

		bksge::list<noncopyable> l;

		bksge::move(bksge::begin(v), bksge::end(v), std::back_inserter(l));

		auto it = l.begin();
		EXPECT_EQ(5, (*it++).get());
		EXPECT_EQ(6, (*it++).get());
		EXPECT_EQ(7, (*it++).get());
		EXPECT_EQ(8, (*it++).get());
		EXPECT_EQ(9, (*it++).get());
		EXPECT_TRUE(it == l.end());
	}
}

}	// namespace move_test

}	// namespace bksge_algorithm_test
