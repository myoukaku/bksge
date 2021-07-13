/**
 *	@file	unit_test_fnd_algorithm_ranges_nth_element.cpp
 *
 *	@brief	ranges::nth_element のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/ranges/nth_element.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/functional/identity.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace ranges_nth_element_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Iter, typename Sent, typename Comp, typename Proj>
BKSGE_CXX14_CONSTEXPR bool NthElementTest(
	Iter first,
	Iter nth,
	Sent last,
	Comp comp,
	Proj proj)
{
	for (auto i = first; i != nth; ++i)
	{
		for (auto j = nth; j != last; ++j)
		{
			VERIFY(!bksge::invoke(comp,
				bksge::invoke(proj, *j),
				bksge::invoke(proj, *i)));
		}
	}

	return true;
}

template <
	typename Range,
	typename Iter,
	typename Comp = bksge::ranges::less,
	typename Proj = bksge::identity
>
BKSGE_CXX14_CONSTEXPR bool NthElementTest(
	Range&& r,
	Iter nth,
	Comp comp = {},
	Proj proj = {})
{
	return NthElementTest(
		bksge::ranges::begin(r),
		nth,
		bksge::ranges::end(r),
		comp,
		proj);
}

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	for (int i = 0; i < 10; ++i)
	{
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		auto nth = ranges::next(a, i);
		auto it = ranges::nth_element(a, nth);
		VERIFY(it == ranges::end(a));
		VERIFY(NthElementTest(a, nth));
	}
	for (int i = 0; i < 10; ++i)
	{
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		test_range<int, random_access_iterator_wrapper> r(a);
		auto nth = ranges::next(r.begin(), i);
		auto it = ranges::nth_element(r, nth, ranges::greater{});
		VERIFY(it == ranges::end(r));
		VERIFY(NthElementTest(r, nth, ranges::greater{}));
	}
	return true;
}

struct X
{
	int i;
};

inline bool test02()
{
	namespace ranges = bksge::ranges;
	for (int i = 0; i < 5; ++i)
	{
		X a[] { {5},{1},{3},{2},{4} };
		auto nth = ranges::next(a, i);
		auto it = ranges::nth_element(a, nth, {}, &X::i);
		VERIFY(it == ranges::end(a));
		VERIFY(NthElementTest(a, nth, {}, &X::i));
	}

	{
		bksge::vector<int> a = {};
		auto it = ranges::nth_element(a, a.begin());
		VERIFY(it == a.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesNthElementTest)
{
#if defined(BKSGE_MSVC) && (BKSGE_MSVC < 1920)
	EXPECT_TRUE(test01());
#else
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
#endif
	EXPECT_TRUE(test02());
}

}	// namespace ranges_nth_element_test

}	// namespace bksge_algorithm_test
