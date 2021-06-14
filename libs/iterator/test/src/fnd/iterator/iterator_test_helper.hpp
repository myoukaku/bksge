/**
 *	@file	iterator_test_helper.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_ITERATOR_ITERATOR_TEST_HELPER_HPP
#define UNIT_TEST_FND_ITERATOR_ITERATOR_TEST_HELPER_HPP

#include <gtest/gtest.h>

namespace
{

// Preconditions: i != j, *i == val
template <typename Iterator, typename T>
void trivial_iterator_test(const Iterator i, const Iterator j, T val)
{
	Iterator k;
	EXPECT_TRUE(i == i);
	EXPECT_TRUE(j == j);
	EXPECT_TRUE(i != j);
	EXPECT_EQ(*i, val);

	k = i;
	EXPECT_TRUE(k == k);
	EXPECT_TRUE(k == i);
	EXPECT_TRUE(k != j);
	EXPECT_EQ(*k, val);
}

// Preconditions: *i == v
template <typename Iterator, typename T>
void readable_iterator_test(Iterator i1, T v)
{
	Iterator i2(i1); // Copy Constructible
	auto r1 = *i1;
	auto r2 = *i2;
	T v1 = r1;
	T v2 = r2;
	EXPECT_TRUE(v1 == v);
	EXPECT_TRUE(v2 == v);
}

// Preconditions: *i == v1, *++i == v2
template <typename Iterator, typename T>
void input_iterator_test(Iterator i, T v1, T v2)
{
	Iterator i1(i);

	EXPECT_TRUE(i == i1);
	EXPECT_TRUE(!(i != i1));

	EXPECT_TRUE(*i1 == v1);
	EXPECT_TRUE(*i == v1);
	EXPECT_TRUE(*(i.operator->()) == v1);

	// we cannot test for equivalence of (void)++i & (void)i++
	// as i is only guaranteed to be single pass.
	EXPECT_TRUE(*i++ == v1);

	i1 = i;

	EXPECT_TRUE(i == i1);
	EXPECT_TRUE(!(i != i1));

	EXPECT_EQ(*i1, v2);
	EXPECT_EQ(*i, v2);

	// i is dereferencable, so it must be incrementable.
	++i;
}

template <typename Iterator, typename T>
void forward_iterator_test(Iterator i, T v1, T v2)
{
	input_iterator_test(i, v1, v2);

	Iterator i1 = i, i2 = i;

	EXPECT_TRUE(i == i1++);
	EXPECT_TRUE(i != ++i2);

	trivial_iterator_test(i, i1, v1);
	trivial_iterator_test(i, i2, v1);

	++i;
	EXPECT_TRUE(i == i1);
	EXPECT_TRUE(i == i2);
	++i1;
	++i2;

	trivial_iterator_test(i, i1, v2);
	trivial_iterator_test(i, i2, v2);
}

// Preconditions: *i == v1, *++i == v2
template <typename Iterator, typename T>
void bidirectional_iterator_test(Iterator i, T v1, T v2)
{
	forward_iterator_test(i, v1, v2);

	++i;

	Iterator i1 = i, i2 = i;

	EXPECT_TRUE(i == i1--);
	EXPECT_TRUE(i != --i2);

	trivial_iterator_test(i, i1, v2);
	trivial_iterator_test(i, i2, v2);

	--i;
	EXPECT_TRUE(i == i1);
	EXPECT_TRUE(i == i2);
	++i1;
	++i2;

	trivial_iterator_test(i, i1, v1);
	trivial_iterator_test(i, i2, v1);
}

// Preconditions: [i,i+N) is a valid range
template <typename Iterator, typename TrueVals>
void random_access_iterator_test(Iterator i, int N, TrueVals vals)
{
	if (N >= 2)
	{
		bidirectional_iterator_test(i, vals[0], vals[1]);
	}

	const Iterator j = i;
	int c;

	for (c = 0; c < N - 1; ++c)
	{
		EXPECT_TRUE(i == j + c);
		EXPECT_TRUE(*i == vals[c]);
		EXPECT_TRUE(*i == j[c]);
		EXPECT_TRUE(*i == *(j + c));
		EXPECT_TRUE(*i == *(c + j));
		++i;
		EXPECT_TRUE(i > j);
		EXPECT_TRUE(i >= j);
		EXPECT_TRUE(j <= i);
		EXPECT_TRUE(j < i);
	}

	Iterator k = j + N - 1;
	for (c = 0; c < N - 1; ++c)
	{
		EXPECT_TRUE(i == k - c);
		EXPECT_TRUE(*i == vals[N - 1 - c]);
		EXPECT_TRUE(*i == j[N - 1 - c]);
		Iterator q = k - c;
		EXPECT_TRUE(*i == *q);
		EXPECT_TRUE(i > j);
		EXPECT_TRUE(i >= j);
		EXPECT_TRUE(j <= i);
		EXPECT_TRUE(j < i);
		--i;
	}

	EXPECT_EQ((k - j), (N - 1));
	EXPECT_EQ((j - k), -(N - 1));

	{
		auto t = (k -= (N - 1));
		EXPECT_TRUE(*k == vals[0]);
		EXPECT_TRUE(*t == vals[0]);
	}
	{
		auto t = (k += (N - 1));
		EXPECT_TRUE(*k == vals[N - 1]);
		EXPECT_TRUE(*t == vals[N - 1]);
	}
}

}	// namespace

#endif // UNIT_TEST_FND_ITERATOR_ITERATOR_TEST_HELPER_HPP
