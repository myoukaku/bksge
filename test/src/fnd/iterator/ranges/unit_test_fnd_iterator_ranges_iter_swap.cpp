/**
 *	@file	unit_test_fnd_iterator_ranges_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/ranges/iter_swap.hpp>
#include <bksge/fnd/concepts/swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace ranges_iter_swap_test
{

struct X
{
	int value;

	BKSGE_CXX14_CONSTEXPR X(int i): value(i) { }

	X(const X&) = delete;
	X& operator=(const X&) = delete;

	BKSGE_CXX14_CONSTEXPR X(X&& x)
		: value(x.value)
	{
		x.value = -1;
	}

	BKSGE_CXX14_CONSTEXPR X& operator=(X&& x)
	{
		value = x.value;
		x.value = -2;
		return *this;
	}
};

struct CustomIterator0
{
	using value_type = X;
	X* m_p;
	BKSGE_CXX14_CONSTEXPR CustomIterator0(X* p): m_p(p) {}
	BKSGE_CXX14_CONSTEXPR X& operator*() const { return *m_p; }
};

struct CustomIterator1
{
	using value_type = X;
	X* m_p;
	BKSGE_CXX14_CONSTEXPR CustomIterator1(X* p): m_p(p) {}
	BKSGE_CXX14_CONSTEXPR X&& operator*() const { return static_cast<X&&>(*m_p); }
};

struct CustomIterator2
{
	X* m_p;
	BKSGE_CXX14_CONSTEXPR CustomIterator2(X* p): m_p(p) {}
};

inline BKSGE_CXX14_CONSTEXPR void
iter_swap(CustomIterator2 const& i, CustomIterator2 const& j)
{
	bksge::ranges::swap(*i.m_p, *j.m_p);
}

template <typename It>
inline BKSGE_CXX14_CONSTEXPR bool
test(int i, int j)
{
	X x1{i};
	X x2{j};
	bksge::ranges::iter_swap(It(&x1), It(&x2));
	return x1.value == j && x2.value == i;
}

GTEST_TEST(IteratorTest, IterSwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<CustomIterator0>(1, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<CustomIterator0>(3, 4)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<CustomIterator1>(5, 6)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<CustomIterator1>(7, 8)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<CustomIterator2>(1, 2)));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test<CustomIterator2>(3, 4)));
}

}	// namespace ranges_iter_swap_test

}	// namespace bksge_iterator_test
