/**
 *	@file	unit_test_fnd_algorithm_ranges_find_end.cpp
 *
 *	@brief	ranges::find_end のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/find_end.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_find_end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;

	{
		int x[] = {1,2,1,2,3};
		int y[] = {1,2};
		auto res = ranges::find_end(x, x+5, y, y+2);
		VERIFY(res.begin() == x + 2);
		VERIFY(res.end()   == x + 4);
		res = ranges::find_end(x, x+5, y, y+1);
		VERIFY(res.begin() == x + 2);
		VERIFY(res.end()   == x + 3);
		res = ranges::find_end(x, x+5, y, y);
		VERIFY(res.begin() == x + 5);
		VERIFY(res.end()   == x + 5);
	}

	return true;
}

template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;

	{
		int x[] = {1,2,1,2,3,1,2,3,4};
		int y[] = {1,2};
		test_range<int, IterWrap> r1(x);
		test_range<int, IterWrap> r2(y);
		auto res = ranges::find_end(r1, r2);
		VERIFY(res.begin().m_ptr == x + 5);
		VERIFY(res.end().m_ptr   == x + 7);
	}
	{
		int x[] = {1,2,1,2,3,1,2,3,4};
		int y[] = {1,2,3};
		test_range<int, IterWrap> r1(x);
		test_range<int, IterWrap> r2(y);
		auto res = ranges::find_end(r1, r2);
		VERIFY(res.begin().m_ptr == x + 5);
		VERIFY(res.end().m_ptr   == x + 8);
	}
	{
		int x[] = {1,2,1,2,3,1,2,3,4};
		int y[] = {1,2,3,4,5};
		test_range<int, IterWrap> r1(x);
		test_range<int, IterWrap> r2(y);
		auto res = ranges::find_end(r1, r2);
		VERIFY(res.begin().m_ptr == x + 9);
		VERIFY(res.end().m_ptr   == x + 9);
	}

	return true;
}

struct X { int i; };

inline bool test03()
{
	namespace ranges = bksge::ranges;
	using std::get;

	X x[] = { {10}, {11}, {2}, {6}, {8}, {10}, {11} };
	X y[] = { {10}, {11} };
	{
		test_range<X, forward_iterator_wrapper> r(x);
		auto res = ranges::find_end(r, y, {}, &X::i, &X::i);
		VERIFY((*get<0>(res)).i == 10 && get<1>(res) == ranges::end(r));
		res = ranges::find_end(r, r, {}, &X::i, &X::i);
		VERIFY(get<0>(res) == ranges::begin(r) && get<1>(res) == ranges::end(r));
	}
	{
		test_range<X, bidirectional_iterator_wrapper> r(x);
		auto res = ranges::find_end(r, y, {}, &X::i, &X::i);
		VERIFY((*get<0>(res)).i == 10 && get<1>(res) == ranges::end(r));
		res = ranges::find_end(r, r, {}, &X::i, &X::i);
		VERIFY(get<0>(res) == ranges::begin(r) && get<1>(res) == ranges::end(r));
	}
	return true;
}

inline bool test04()
{
	namespace ranges = bksge::ranges;
	using std::get;

	X x[] = { {2}, {2}, {6}, {8}, {10}, {6}, {8}, {11} };
	X y[] = { {6}, {8} };
	int z[] = { 2, 8 };
	int w[] = { 2 };

	VERIFY(get<0>(ranges::find_end(x, y, {}, &X::i, &X::i)) == x+5);
	VERIFY(get<1>(ranges::find_end(x, y, {}, &X::i, &X::i)) == x+7);

	VERIFY(get<0>(ranges::find_end(x, z, {}, &X::i)) == x+8);
	VERIFY(get<1>(ranges::find_end(x, z, {}, &X::i)) == x+8);

	VERIFY(get<0>(ranges::find_end(x, w, {}, &X::i)) == x+1);
	VERIFY(get<1>(ranges::find_end(x, w, {}, &X::i)) == x+2);

	VERIFY(get<0>(ranges::find_end(x, x+6, w, w, {}, &X::i)) == x+6);
	VERIFY(get<1>(ranges::find_end(x, x+6, w, w, {}, &X::i)) == x+6);

	VERIFY(get<0>(ranges::find_end(x, x, w, w+1, {}, &X::i)) == x+0);
	VERIFY(get<1>(ranges::find_end(x, x, w, w+1, {}, &X::i)) == x+0);

	return true;
}

inline bool test05()
{
	namespace ranges = bksge::ranges;

	{
		bksge::vector<int> x { 1,2,3,4,2,3 };
		std::list<int>   y { 2,3 };
		auto res = ranges::find_end(x, y);
		VERIFY(res.begin() == x.begin() + 4);
		VERIFY(res.end()   == x.begin() + 6);
	}
	{
		bksge::vector<int> x { 1,2,3,4,2,3 };
		std::list<int>   y { };
		auto res = ranges::find_end(x, y);
		VERIFY(res.begin() == x.end());
		VERIFY(res.end()   == x.end());
	}
	{
		bksge::vector<int> x { 1,2,3,4,2,3 };
		std::forward_list<int> y { 2,3 };
		auto res = ranges::find_end(x, y);
		VERIFY(res.begin() == x.begin() + 4);
		VERIFY(res.end()   == x.begin() + 6);
	}
	{
		bksge::vector<int> x { 1,2,3,4,2,3 };
		std::forward_list<int> y { };
		auto res = ranges::find_end(x, y);
		VERIFY(res.begin() == x.end());
		VERIFY(res.end()   == x.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFindEndTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02<bidirectional_iterator_wrapper>());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
	EXPECT_TRUE(test05());
}

}	// namespace ranges_find_end_test

}	// namespace bksge_algorithm_test
