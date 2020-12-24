/**
 *	@file	unit_test_fnd_algorithm_ranges_move_backward.cpp
 *
 *	@brief	ranges::move_backward のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/move_backward.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_move_backward_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Noncopyable
{
	int i;

	BKSGE_CXX14_CONSTEXPR Noncopyable() : i(0) {}
	BKSGE_CXX14_CONSTEXPR Noncopyable(int a) : i(a) {}

	BKSGE_CXX14_CONSTEXPR Noncopyable(Noncopyable const&) = delete;
	BKSGE_CXX14_CONSTEXPR Noncopyable& operator=(Noncopyable const&) = delete;

	BKSGE_CXX14_CONSTEXPR Noncopyable(Noncopyable&& other)
		: i(other.i)
	{
		other.i = -1;
	}

	BKSGE_CXX14_CONSTEXPR Noncopyable& operator=(Noncopyable&& other)
	{
		i = other.i;
		other.i = -1;
		return *this;
	}

	friend constexpr bool
	operator==(Noncopyable const& lhs, Noncopyable const& rhs)
	{
		return lhs.i == rhs.i;
	}

	friend constexpr bool
	operator!=(Noncopyable const& lhs, Noncopyable const& rhs)
	{
		return !(lhs == rhs);
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int const x[7] = { 1, 2, 3, 4, 5, 6, 7 };
		int w[7] = {};
		auto res = ranges::move_backward(x, x+7, ranges::end(w));
		VERIFY(res.in  == x+7);
		VERIFY(res.out == w+0);
		int const y[7] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(w, y));
	}
	{
		char const x[4] = { 1, 2, 3, 4 };
		int w[5] = {};
		auto res = ranges::move_backward(x, x+4, ranges::end(w));
		VERIFY(res.in  == x+4);
		VERIFY(res.out == w+1);
		int const y[5] = { 0, 1, 2, 3, 4 };
		VERIFY(ranges::equal(w, y));
	}
	{
		Noncopyable x[] = { {1}, {2}, {3} };
		Noncopyable w[3] = {};
		auto res = ranges::move_backward(x, x+3, ranges::end(w));
		VERIFY(res.in  == x+3);
		VERIFY(res.out == w+0);
		Noncopyable a[] = { {1}, {2}, {3} };
		Noncopyable b[] = { {-1}, {-1}, {-1} };
		VERIFY(ranges::equal(w, a));
		VERIFY(ranges::equal(x, b));
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int const x[] = { 1, 2, 3 };
		int w[5] = {};
		test_range<int const, bidirectional_iterator_wrapper> rx(x);
		test_range<int, bidirectional_iterator_wrapper> rw(w);
		auto res = ranges::move_backward(rx, ranges::next(rw.begin(), 5));
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == ranges::next(rw.begin(), 2));
		int const y[] = { 0, 0, 1, 2, 3 };
		VERIFY(ranges::equal(w, y));
	}
	{
		char const x[] = { 1, 2, 3, 4 };
		int w[4] = {};
		test_range<char const, bidirectional_iterator_wrapper> rx(x);
		test_range<int, bidirectional_iterator_wrapper> rw(w);
		auto res = ranges::move_backward(rx, ranges::next(rw.begin(), 4));
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.begin());
		int const y[] = { 1, 2, 3, 4 };
		VERIFY(ranges::equal(w, y));
	}
	{
		Noncopyable x[] = { {4}, {5}, {6}, {7} };
		Noncopyable w[4] = {};
		test_range<Noncopyable, bidirectional_iterator_wrapper> rx(x);
		test_range<Noncopyable, bidirectional_iterator_wrapper> rw(w);
		auto res = ranges::move_backward(rx, ranges::next(rw.begin(), 4));
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.begin());
		Noncopyable a[] = { {4}, {5}, {6}, {7} };
		Noncopyable b[] = { {-1}, {-1}, {-1}, {-1} };
		VERIFY(ranges::equal(w, a));
		VERIFY(ranges::equal(x, b));
	}
	return true;
}

inline bool test03()
{
	namespace ranges = bksge::ranges;
	{
		bksge::vector<int> x = { 1, 2, 3, 4, 5, 6, 7 };
		bksge::vector<int> w(x.size());
		auto res = ranges::move_backward(x.rbegin(), x.rend(), w.end());
		VERIFY(res.in  == x.rend());
		VERIFY(res.out == w.begin());
		int const y[7] = { 7, 6, 5, 4, 3, 2, 1 };
		VERIFY(ranges::equal(w, y));
	}
	{
		bksge::list<int> x = { 1, 2, 3, 4, 5, 6, 7 };
		bksge::list<int> w(x.size());
		auto res = ranges::move_backward(x.rbegin(), x.rend(), w.rend());
		VERIFY(res.in  == x.rend());
		VERIFY(res.out == w.rbegin());
		int const y[7] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline bool test04()
{
	namespace ranges = bksge::ranges;
	{
		bksge::vector<int> x = { 1, 2, 3, 4, 5, 6 };
		bksge::vector<int> w(x.size());
		auto res = ranges::move_backward(x, w.rend());
		VERIFY(res.in  == x.end());
		VERIFY(res.out == w.rbegin());
		int const y[6] = { 6, 5, 4, 3, 2, 1 };
		VERIFY(ranges::equal(w, y));
	}
	{
		bksge::list<int> x = { 1, 2, 3, 4, 5 };
		bksge::list<int> w(5);
		auto res = ranges::move_backward(x, w.end());
		VERIFY(res.in  == x.end());
		VERIFY(res.out == w.begin());
		int const y[5] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMoveBackwardTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
}

}	// namespace ranges_move_backward_test

}	// namespace bksge_algorithm_test
