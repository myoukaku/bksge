/**
 *	@file	unit_test_fnd_algorithm_ranges_partition.cpp
 *
 *	@brief	ranges::partition のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/partition.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_partition_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct IsEven
{
	constexpr bool operator()(int a) const
	{
		return a%2==0;
	}
};

struct IsOdd
{
	constexpr bool operator()(int a) const
	{
		return a%2==1;
	}
};

template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 3,1,4,1,5,9,2,6,5,3 };
		test_range<int, IterWrap> rx(x);
		auto res = ranges::partition(rx, IsEven{});
		VERIFY(res.begin() == ranges::next(rx.begin(), 3));
		VERIFY(res.end()   == rx.end());
	}
	{
		int x[] = { 3,1,4,1,5,9,2,6,5,3 };
		test_range<int, IterWrap> rx(x);
		auto res = ranges::partition(rx, IsOdd{});
		VERIFY(res.begin() == ranges::next(rx.begin(), 7));
		VERIFY(res.end()   == rx.end());
	}
	{
		int x[] = { 1,3,5,7,9 };
		test_range<int, IterWrap> rx(x);
		auto res = ranges::partition(rx, IsEven{});
		VERIFY(res.begin() == ranges::next(rx.begin(), 0));
		VERIFY(res.end()   == rx.end());
	}
	{
		int x[] = { 1,3,5,7,9 };
		test_range<int, IterWrap> rx(x);
		auto res = ranges::partition(rx, IsOdd{});
		VERIFY(res.begin() == rx.end());
		VERIFY(res.end()   == rx.end());
	}
	{
		int x[] = { 1,3,5,7,9 };
		test_range<int, IterWrap> rx(x);
		auto res = ranges::partition(rx.begin(), rx.begin(), IsOdd{});
		VERIFY(res.begin() == rx.begin());
		VERIFY(res.end()   == rx.begin());
	}
	return true;
}

struct X
{
	int i;
};

template <template <typename> class IterWrap>
inline bool test02()
{
	namespace ranges = bksge::ranges;
	{
		X x[] = { {1},{2},{3},{4},{5},{6},{7},{8},{9} };
		test_range<X, IterWrap> rx(x);
		auto res = ranges::partition(rx, [](int a) { return a%2==0; }, &X::i);
		VERIFY(res.begin() == ranges::next(rx.begin(), 4));
		VERIFY(res.end()   == rx.end());
	}
	return true;
}

inline bool test03()
{
	namespace ranges = bksge::ranges;
	{
		std::vector<int> x {};
		auto res = ranges::partition(x, [](int a) { return a%2==0; });
		VERIFY(res.begin() == x.begin());
		VERIFY(res.end()   == x.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesPartitionTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<bidirectional_iterator_wrapper>());
	EXPECT_TRUE(test02<forward_iterator_wrapper>());
	EXPECT_TRUE(test02<bidirectional_iterator_wrapper>());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_partition_test

}	// namespace bksge_algorithm_test
