/**
 *	@file	unit_test_fnd_iterator_common_iterator.cpp
 *
 *	@brief	common_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/common_iterator.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/cend.hpp>
#include <bksge/fnd/iterator/concepts/sentinel_for.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/iterator/ranges/iter_move.hpp>
#include <bksge/fnd/iterator/ranges/iter_swap.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/cend.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/cstddef/ptrdiff_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace common_iterator_test
{

struct Sentinel1 { operator int* () const { return nullptr; } };

struct Sentinel2
{
	const int* p;
	Sentinel2(const int* p2 = 0) : p(p2) {}
	friend bool operator==(Sentinel2 const& s, const int* p2) { return p2 == s.p; }
	friend bool operator!=(Sentinel2 const& s, const int* p2) { return p2 != s.p; }
	friend bool operator==(const int* p2, Sentinel2 const& s) { return p2 == s.p; }
	friend bool operator!=(const int* p2, Sentinel2 const& s) { return p2 != s.p; }
};

GTEST_TEST(CommonIteratorTest, Test01)
{
	using I = bksge::common_iterator<int*, const int*>;
	static_assert(bksge::is_default_constructible<I>::value, "");
	static_assert(bksge::is_copy_constructible<I>::value, "");
	static_assert(bksge::is_copy_assignable<I>::value, "");
	static_assert(bksge::is_constructible<I, int*>::value, "");
	static_assert(bksge::is_constructible<I, const int*>::value, "");
	static_assert(bksge::is_nothrow_constructible<I, int*>::value, "");
	static_assert(bksge::is_nothrow_constructible<I, const int*>::value, "");

	using K = bksge::common_iterator<int*, Sentinel1>;
	static_assert( bksge::is_constructible<I, const K&>::value, "");
	static_assert(!bksge::is_nothrow_constructible<I, const K&>::value, "");
	static_assert( bksge::is_assignable<I, const K&>::value, "");

	using J = bksge::common_iterator<const int*, Sentinel2>;
	static_assert( bksge::is_constructible<J, const I&>::value, "");
	static_assert(!bksge::is_nothrow_constructible<J, const I&>::value, "");
	static_assert( bksge::is_convertible<const I&, J>::value, "");

	{
		I i;
		K k;
		J j;
		EXPECT_TRUE(i == i);
		EXPECT_TRUE(j == j);
		EXPECT_TRUE(k == k);
	}
	{
		int a[] = {1,2,3};
		I i = &a[0];
		J j = i;
		EXPECT_TRUE(i == i);
		EXPECT_TRUE(j == j);
	}
	{
		Sentinel1 s;
		K k = s;
		I i = k;
		EXPECT_TRUE(i == i);
	}
}

struct Sentinel3 { int limit; };

struct Iterator3
{
	using iterator_category = bksge::input_iterator_tag;
	using value_type = int;
	using difference_type = bksge::ptrdiff_t;
	using reference = const int&;

	const int& operator*() const { return counter; }

	Iterator3& operator++() { ++counter; return *this; }

	Iterator3 operator++(int) { auto i = *this; ++counter; return i; }

	friend bool operator==(Iterator3 const& i, Sentinel3 const& s) { return i.counter == s.limit; }
	friend bool operator!=(Iterator3 const& i, Sentinel3 const& s) { return i.counter != s.limit; }
	friend bool operator==(Sentinel3 const& s, Iterator3 const& i) { return i.counter == s.limit; }
	friend bool operator!=(Sentinel3 const& s, Iterator3 const& i) { return i.counter != s.limit; }

	int counter = 0;
};

GTEST_TEST(CommonIteratorTest, Test02)
{
	static_assert(bksge::is_sentinel_for<Sentinel3, Iterator3>::value, "");

	int out[5] = {};
	bksge::common_iterator<int*, const int*> obegin = bksge::begin(out);
	bksge::common_iterator<int*, const int*> oend = bksge::cend(out);

	Iterator3 i;
	Sentinel3 s{5};
	bksge::common_iterator<Iterator3, Sentinel3> begin = i, end = s;
	EXPECT_TRUE(*(begin.operator->()) == 0);
	while (begin != end)
	{
		*obegin++ = *begin++;
	}

	EXPECT_TRUE(obegin == oend);
	for (int& j : out)
	{
		EXPECT_TRUE(j == (&j - out));
	}
}

GTEST_TEST(CommonIteratorTest, Test03)
{
	int arr[2] ={1, 2};
	bksge::common_iterator<int*, const int*> i = bksge::ranges::begin(arr);
	bksge::common_iterator<int*, const int*> end = bksge::ranges::cend(arr);
	{
		auto e2 = end;
		EXPECT_TRUE(e2 == end);
	}
	EXPECT_TRUE(i != end);
	EXPECT_TRUE((end - i) == 2);
	EXPECT_TRUE((i - end) == -2);
	EXPECT_TRUE((end - end) == 0);
	auto j = i;
	EXPECT_TRUE(j == i);
	EXPECT_TRUE((j - i) == 0);
	j = end;
	EXPECT_TRUE(j != i);
	EXPECT_TRUE(j == end);
	j = bksge::ranges::next(i);
	EXPECT_TRUE(j != i);
	EXPECT_TRUE(j != end);
	EXPECT_TRUE((end - j) == 1);
	EXPECT_TRUE((j - i) == 1);
	EXPECT_TRUE((i - j) == -1);
	++j;
	EXPECT_TRUE(j == end);
	EXPECT_TRUE((end - j) == 0);
	j = i;
	EXPECT_TRUE(j == i);
	EXPECT_TRUE((j - end) == -2);
	EXPECT_TRUE((j - i) == 0);

	try
	{
		struct S { operator const int* () const { throw 1; } };
		i = bksge::common_iterator<int*, S>(S{});
		EXPECT_TRUE(false);
	}
	catch (int)
	{
	}
}

struct X
{
	X(int i) : i(i) {}
	X(X&& x) : i(x.i) { x.i = -1; }
	X& operator=(X&& x) { i = x.i; x.i = 0; return *this; }
	int i;
};

GTEST_TEST(CommonIteratorTest, Test04)
{
	X arr[] = {1, 2};
	bksge::common_iterator<X*, const X*> i(arr), j(arr+1);
	EXPECT_TRUE(i->i == 1);
	EXPECT_TRUE(j->i == 2);
	{
		bksge::common_iterator<X*, const X*> const i2 = i;
		EXPECT_TRUE(i2->i == 1);
		EXPECT_TRUE((*i2).i == 1);
	}

	bksge::ranges::iter_swap(i, j);
	EXPECT_TRUE(arr[0].i == 2);
	EXPECT_TRUE(arr[1].i == 1);

	X x = bksge::ranges::iter_move(i);
	EXPECT_TRUE(arr[0].i == -1);
	EXPECT_TRUE(x.i == 2);
}

struct Iterator4
{
	using iterator_category = bksge::input_iterator_tag;
	using value_type = int;
	using difference_type = bksge::ptrdiff_t;
	using reference = const int&;

	int count = 0;

	Iterator4() noexcept {}
	~Iterator4() noexcept {}
	const int& operator*() const { return count; }
	Iterator4& operator++() { return *this; }
	Iterator4 operator++(int) { return *this; }
};

struct Sentinel4
{
	Sentinel4() noexcept {}
	~Sentinel4() noexcept {}
	friend bool operator==(Iterator4 const&, Sentinel4 const&) { return true; }
	friend bool operator!=(Iterator4 const&, Sentinel4 const&) { return false; }
	friend bool operator==(Sentinel4 const&, Iterator4 const&) { return true; }
	friend bool operator!=(Sentinel4 const&, Iterator4 const&) { return false; }
};

struct Iterator5
{
	using iterator_category = bksge::input_iterator_tag;
	using value_type = int;
	using difference_type = bksge::ptrdiff_t;
	using reference = int;

	Iterator5() noexcept {}
	Iterator5(Iterator4 const&) noexcept {}
	int operator*() const { return 0; }
	Iterator5& operator++() { return *this; }
	Iterator5 operator++(int) { return *this; }
};

struct Sentinel5
{
	Sentinel5() noexcept {}
	Sentinel5(Sentinel4 const&) noexcept {}
	friend bool operator==(Iterator5 const&, Sentinel5 const&) { return true; }
	friend bool operator!=(Iterator5 const&, Sentinel5 const&) { return false; }
	friend bool operator==(Sentinel5 const&, Iterator5 const&) { return true; }
	friend bool operator!=(Sentinel5 const&, Iterator5 const&) { return false; }
};

GTEST_TEST(CommonIteratorTest, Test05)
{
	using CI1 = bksge::common_iterator<Iterator4, Sentinel4>;
	using CI2 = bksge::common_iterator<Iterator5, Sentinel5>;
	static_assert( bksge::is_constructible<CI1, CI1 const&>::value, "");
	static_assert(!bksge::is_constructible<CI1, CI2 const&>::value, "");
	static_assert( bksge::is_constructible<CI2, CI1 const&>::value, "");
	static_assert( bksge::is_constructible<CI2, CI2 const&>::value, "");
	static_assert( bksge::is_nothrow_constructible<CI1, CI1 const&>::value, "");
	static_assert(!bksge::is_nothrow_constructible<CI1, CI2 const&>::value, "");
	static_assert( bksge::is_nothrow_constructible<CI2, CI1 const&>::value, "");
	static_assert( bksge::is_nothrow_constructible<CI2, CI2 const&>::value, "");

	Iterator4 i;
	Sentinel4 s;
	bksge::common_iterator<Iterator4, Sentinel4> b = i;
	bksge::common_iterator<Iterator4, Sentinel4> e = s;
	auto b2 = b;
	auto e2 = e;
	bksge::common_iterator<Iterator5, Sentinel5> b3 = b2;
	bksge::common_iterator<Iterator5, Sentinel5> e3 = e2;
	b3 = b;
	e3 = e;
	EXPECT_TRUE(b == b2);
	EXPECT_TRUE(e == e2);
	EXPECT_TRUE(b == e);
	EXPECT_TRUE(e == b);
	EXPECT_TRUE(*(b3.operator->().operator->()) == 0);
}

}	// namespace common_iterator_test

}	// namespace bksge_iterator_test
