/**
 *	@file	unit_test_fnd_algorithm_ranges_move.cpp
 *
 *	@brief	ranges::move のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/move.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_move_test
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
		auto res = ranges::move(x, x+7, w);
		VERIFY(res.in  == x+7);
		VERIFY(res.out == w+7);
		int const y[7] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(w, y));
	}
	{
		char const x[5] = { 1, 2, 3, 4, 5 };
		int w[5] = {};
		auto res = ranges::move(x, x+5, w);
		VERIFY(res.in  == x+5);
		VERIFY(res.out == w+5);
		int const y[5] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(w, y));
	}
	{
		Noncopyable x[] = { {1}, {2}, {3} };
		Noncopyable w[3] = {};
		auto res = ranges::move(x, x+3, w);
		VERIFY(res.in  == x+3);
		VERIFY(res.out == w+3);
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
		int w[3] = {};
		test_range<int const, input_iterator_wrapper> rx(x);
		test_range<int, output_iterator_wrapper> rw(w);
		auto res = ranges::move(rx, rw.begin());
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 1, 2, 3 };
		VERIFY(ranges::equal(w, y));
	}
	{
		char const x[] = { 1, 2, 3, 4 };
		int w[4] = {};
		test_range<char const, input_iterator_wrapper> rx(x);
		test_range<int, output_iterator_wrapper> rw(w);
		auto res = ranges::move(rx, rw.begin());
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
		int const y[] = { 1, 2, 3, 4 };
		VERIFY(ranges::equal(w, y));
	}
	{
		Noncopyable x[] = { {4}, {5}, {6}, {7} };
		Noncopyable w[4] = {};
		test_range<Noncopyable, input_iterator_wrapper> rx(x);
		test_range<Noncopyable, output_iterator_wrapper> rw(w);
		auto res = ranges::move(rx, rw.begin());
		VERIFY(res.in  == rx.end());
		VERIFY(res.out == rw.end());
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
		std::vector<int> x = { 1, 2, 3, 4, 5, 6, 7 };
		std::vector<int> w(x.size());
		auto res = ranges::move(x.rbegin(), x.rend(), w.begin());
		VERIFY(res.in  == x.rend());
		VERIFY(res.out == w.end());
		int const y[7] = { 7, 6, 5, 4, 3, 2, 1 };
		VERIFY(ranges::equal(w, y));
	}
	{
		std::list<int> x = { 1, 2, 3, 4, 5, 6, 7 };
		std::list<int> w(x.size());
		auto res = ranges::move(x.rbegin(), x.rend(), w.rbegin());
		VERIFY(res.in  == x.rend());
		VERIFY(res.out == w.rend());
		int const y[7] = { 1, 2, 3, 4, 5, 6, 7 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

inline bool test04()
{
	namespace ranges = bksge::ranges;
	{
		std::vector<int> x = { 1, 2, 3, 4, 5, 6 };
		std::vector<int> w(x.size());
		auto res = ranges::move(x, w.rbegin());
		VERIFY(res.in  == x.end());
		VERIFY(res.out == w.rend());
		int const y[6] = { 6, 5, 4, 3, 2, 1 };
		VERIFY(ranges::equal(w, y));
	}
	{
		std::forward_list<int> x = { 1, 2, 3, 4, 5 };
		std::forward_list<int> w(5);
		auto res = ranges::move(x, w.begin());
		VERIFY(res.in  == x.end());
		VERIFY(res.out == w.end());
		int const y[5] = { 1, 2, 3, 4, 5 };
		VERIFY(ranges::equal(w, y));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMoveTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
}

}	// namespace ranges_move_test

}	// namespace bksge_algorithm_test
