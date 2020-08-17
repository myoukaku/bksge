/**
 *	@file	unit_test_fnd_ranges_subrange.cpp
 *
 *	@brief	ranges::subrange のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/views/subrange.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/size.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/sized_range.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/assert.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_ranges_test
{

namespace subrange_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	int x[] ={1, 2, 3, 4, 5};
	using Range = test_bidirectional_sized_range<int>;
	Range r{x};
	ranges::subrange<
		ranges::iterator_t<Range>,
		ranges::sentinel_t<Range>,
		ranges::subrange_kind::sized> sr = r;

	VERIFY(!sr.empty());
	int const a1[] = { 1, 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a1));
	VERIFY(sr.size() == 5);

	sr = sr.next();
	VERIFY(!sr.empty());
	int const a2[] = { 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a2));
	VERIFY(sr.size() == 4);

	sr = bksge::move(sr).next(2);
	VERIFY(!sr.empty());
	int const a3[] = { 4, 5 };
	VERIFY(ranges::equal(sr, a3));
	VERIFY(sr.size() == 2);

	sr = sr.prev(2);
	VERIFY(!sr.empty());
	int const a4[] = { 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a4));
	VERIFY(sr.size() == 4);

	sr = sr.prev();
	VERIFY(!sr.empty());
	int const a5[] = { 1, 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a5));
	VERIFY(sr.size() == 5);

	sr.advance(1);
	VERIFY(!sr.empty());
	int const a6[] = { 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a6));
	VERIFY(sr.size() == 4);

	sr.advance(-1);
	VERIFY(!sr.empty());
	int const a7[] = { 1, 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a7));
	VERIFY(sr.size() == 5);

	sr = r;
	sr.advance(5);
	VERIFY(sr.empty());
	VERIFY(sr.size() == 0);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	int x[] ={1, 2, 3, 4, 5};
	using Range = test_bidirectional_range<int>;
	Range r{x};
	ranges::subrange<
		ranges::iterator_t<Range>,
		ranges::sentinel_t<Range>> sr = r;

	VERIFY(!sr.empty());
	int const a1[] = { 1, 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a1));

	sr = sr.next();
	VERIFY(!sr.empty());
	int const a2[] = { 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a2));

	sr = bksge::move(sr).next(2);
	VERIFY(!sr.empty());
	int const a3[] = { 4, 5 };
	VERIFY(ranges::equal(sr, a3));

	sr = sr.prev(2);
	VERIFY(!sr.empty());
	int const a4[] = { 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a4));

	sr = sr.prev();
	VERIFY(!sr.empty());
	int const a5[] = { 1, 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a5));

	sr.advance(1);
	VERIFY(!sr.empty());
	int const a6[] = { 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a6));

	sr.advance(-1);
	VERIFY(!sr.empty());
	int const a7[] = { 1, 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a7));

	sr = r;
	sr.advance(5);
	VERIFY(sr.empty());

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	int x[] ={1, 2, 3, 4, 5};
	using Range = test_forward_sized_range<int>;
	Range r{x};
	ranges::subrange<
		ranges::iterator_t<Range>,
		ranges::sentinel_t<Range>,
		ranges::subrange_kind::sized> sr = r;

	VERIFY(!sr.empty());
	int const a1[] = { 1, 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a1));
	VERIFY(sr.size() == 5);

	sr = sr.next();
	VERIFY(!sr.empty());
	int const a2[] = { 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a2));
	VERIFY(sr.size() == 4);

	sr = bksge::move(sr).next(2);
	VERIFY(!sr.empty());
	int const a3[] = { 4, 5 };
	VERIFY(ranges::equal(sr, a3));
	VERIFY(sr.size() == 2);

	sr = r;
	sr.advance(1);
	VERIFY(!sr.empty());
	int const a6[] = { 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a6));
	VERIFY(sr.size() == 4);

	sr = r;
	sr.advance(5);
	VERIFY(sr.empty());
	VERIFY(sr.size() == 0);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = bksge::ranges;
	int x[] ={1, 2, 3, 4, 5};
	using Range = test_forward_range<int>;
	Range r{x};
	ranges::subrange<
		ranges::iterator_t<Range>,
		ranges::sentinel_t<Range>> sr = r;

	VERIFY(!sr.empty());
	int const a1[] = { 1, 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a1));

	sr = sr.next();
	VERIFY(!sr.empty());
	int const a2[] = { 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a2));

	sr = bksge::move(sr).next(2);
	VERIFY(!sr.empty());
	int const a3[] = { 4, 5 };
	VERIFY(ranges::equal(sr, a3));

	sr = r;
	sr.advance(1);
	VERIFY(!sr.empty());
	int const a6[] = { 2, 3, 4, 5 };
	VERIFY(ranges::equal(sr, a6));

	sr = r;
	sr.advance(5);
	VERIFY(sr.empty());

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test05()
{
	int a[] = {1,2,3,4,5};
	bksge::ranges::subrange<int*> sr(a);
	std::pair<int*, int*> p = sr;
	VERIFY(p.first  == a);
	VERIFY(p.second == a+5);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test06()
{
	using S1 = bksge::ranges::subrange<int*>;
	using S2 = bksge::ranges::subrange<long*, void*>;

	static_assert(std::tuple_size<S1>::value == 2, "");
	static_assert(std::tuple_size<S2>::value == 2, "");

	static_assert(bksge::is_same<bksge::tuple_element_t<0, S1>, int*>::value, "");
	static_assert(bksge::is_same<bksge::tuple_element_t<1, S1>, int*>::value, "");

	static_assert(bksge::is_same<bksge::tuple_element_t<0, const S1>, int*>::value, "");
	static_assert(bksge::is_same<bksge::tuple_element_t<1, const S1>, int*>::value, "");

	static_assert(bksge::is_same<bksge::tuple_element_t<0, S2>, long*>::value, "");
	static_assert(bksge::is_same<bksge::tuple_element_t<1, S2>, void*>::value, "");

	static_assert(bksge::is_same<bksge::tuple_element_t<0, const S2>, long*>::value, "");
	static_assert(bksge::is_same<bksge::tuple_element_t<1, const S2>, void*>::value, "");

	int a[] = {1,2,3,4,5};
	S1 s1(a);
	using bksge::ranges::get;
	static_assert(bksge::is_same<decltype(get<0>(s1)), int*>::value, "");
	static_assert(bksge::is_same<decltype(get<1>(s1)), int*>::value, "");
	const S1 c1(a);
	static_assert(bksge::is_same<decltype(get<0>(c1)), int*>::value, "");
	static_assert(bksge::is_same<decltype(get<1>(c1)), int*>::value, "");
	S2 s2;
	static_assert(bksge::is_same<decltype(get<0>(s2)), long*>::value, "");
	static_assert(bksge::is_same<decltype(get<1>(s2)), void*>::value, "");
	const S2 c2;
	static_assert(bksge::is_same<decltype(get<0>(c2)), long*>::value, "");
	static_assert(bksge::is_same<decltype(get<1>(c2)), void*>::value, "");

	VERIFY(get<0>(s1) == a);
	VERIFY(get<1>(s1) == a+5);
	VERIFY(get<0>(c1) == a);
	VERIFY(get<1>(c1) == a+5);
	VERIFY(get<0>(bksge::move(s1)) == a);
	VERIFY(get<1>(bksge::move(s1)) == a+5);
	VERIFY(get<0>(bksge::move(c1)) == a);
	VERIFY(get<1>(bksge::move(c1)) == a+5);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test07()
{
	int a[] = {1,2,3,4,5};
	{
		bksge::ranges::subrange<int*> sr(a);
		VERIFY(sr.front() == 1);
		VERIFY(sr.back()  == 5);
		VERIFY(sr[1]      == 2);
		VERIFY(sr[2]      == 3);
		VERIFY(sr.data()  == a);
		sr.front() = 11;
		sr.back()  = 12;
		sr[1]      = 13;
	}
	{
		bksge::ranges::subrange<int*> const sr(a);
		VERIFY(sr.front() == 11);
		VERIFY(sr.back()  == 12);
		VERIFY(sr[1]      == 13);
		VERIFY(sr[2]      == 3);
		VERIFY(sr.data()  == a);
	}
	return true;
}

BKSGE_CXX14_CONSTEXPR bool test_deduction()
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	using bksge::ranges::get;
	// Iterator, Sentinel
	{
		int a[] = {1,2,3};
		bksge::ranges::subrange sr(a, a+1);
		static_assert(bksge::is_same<bksge::tuple_element_t<0, decltype(sr)>, int*>::value, "");
		static_assert(bksge::is_same<bksge::tuple_element_t<1, decltype(sr)>, int*>::value, "");
		VERIFY(get<0>(sr) == a);
		VERIFY(get<1>(sr) == a+1);
		VERIFY(sr.size() == 1);
	}
	// Iterator, Sentinel, Size
	{
		int a[] = {1,2,3};
		bksge::ranges::subrange sr(a, a+2, 2);
		static_assert(bksge::is_same<bksge::tuple_element_t<0, decltype(sr)>, int*>::value, "");
		static_assert(bksge::is_same<bksge::tuple_element_t<1, decltype(sr)>, int*>::value, "");
		VERIFY(get<0>(sr) == a);
		VERIFY(get<1>(sr) == a+2);
		VERIFY(sr.size() == 2);
	}
	// Range
	{
		int a[] = {1,2,3};
		bksge::ranges::subrange sr(a);
		static_assert(bksge::is_same<bksge::tuple_element_t<0, decltype(sr)>, int*>::value, "");
		static_assert(bksge::is_same<bksge::tuple_element_t<1, decltype(sr)>, int*>::value, "");
		VERIFY(get<0>(sr) == a);
		VERIFY(get<1>(sr) == a+3);
		VERIFY(sr.size() == 3);
	}
	// Range, Size
	{
		int a[] = {1,2,3};
		bksge::ranges::subrange sr(a, 3);
		static_assert(bksge::is_same<bksge::tuple_element_t<0, decltype(sr)>, int*>::value, "");
		static_assert(bksge::is_same<bksge::tuple_element_t<1, decltype(sr)>, int*>::value, "");
		VERIFY(get<0>(sr) == a);
		VERIFY(get<1>(sr) == a+3);
		VERIFY(sr.size() == 3);
	}
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SubrangeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test07());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_deduction());
}

}	// namespace subrange_test

}	// namespace bksge_ranges_test
