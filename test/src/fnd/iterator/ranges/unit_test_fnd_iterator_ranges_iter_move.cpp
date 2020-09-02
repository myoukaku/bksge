/**
 *	@file	unit_test_fnd_iterator_ranges_iter_move.cpp
 *
 *	@brief	ranges::iter_move のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/ranges/iter_move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace ranges_iter_move_test
{

struct X
{
	int value;

	BKSGE_CXX14_CONSTEXPR X(int i): value(i) { }

	X(const X&) = default;
	X& operator=(const X&) = default;

	BKSGE_CXX14_CONSTEXPR X(X&& x)
		: value(x.value)
	{
		x.value = -2;
	}

	BKSGE_CXX14_CONSTEXPR X& operator=(X&& x)
	{
		value = x.value;
		x.value = -1;
		return *this;
	}
};

struct CustomIterator
{
	X* m_p;
	BKSGE_CXX14_CONSTEXPR CustomIterator(X* p): m_p(p) {}
	BKSGE_CXX14_CONSTEXPR X&& operator*() const { return static_cast<X&&>(*m_p); }
};

struct CustomIterator2
{
	X* m_p;
	BKSGE_CXX14_CONSTEXPR CustomIterator2(X* p): m_p(p) {}
	BKSGE_CXX14_CONSTEXPR X&& operator*() const;
};

inline BKSGE_CXX14_CONSTEXPR X&&
iter_move(CustomIterator2 const& i)
{
	return static_cast<X&&>(*i.m_p);
}

template <typename It>
inline BKSGE_CXX14_CONSTEXPR bool
test_X(int i, int j)
{
	X x1{i}, x2{j};
	bksge::ranges::iter_move(It(&x1)); // no-op
	x1 = bksge::ranges::iter_move(It(&x2));
	return x1.value == j && x2.value == -1;
}

GTEST_TEST(IteratorTest, IterMoveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_X<X*>(1, 2));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_X<X*>(3, 4));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_X<CustomIterator>(1, 2));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_X<CustomIterator>(3, 4));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_X<CustomIterator2>(1, 2));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_X<CustomIterator2>(3, 4));
}

}	// namespace ranges_iter_move_test

}	// namespace bksge_iterator_test
