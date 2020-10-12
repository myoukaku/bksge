/**
 *	@file	unit_test_fnd_algorithm_shift_left.cpp
 *
 *	@brief	shift_left のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/shift_left.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/algorithm/ranges/equal.hpp>
#include <bksge/fnd/iterator/ranges/next.hpp>
#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_algorithm_test
{

namespace shift_left_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = bksge::shift_left(ranges::begin(x), ranges::end(x), -1);
		VERIFY(ret == ranges::end(x));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = bksge::shift_left(ranges::begin(x), ranges::end(x), 0);
		VERIFY(ret == ranges::end(x));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = bksge::shift_left(ranges::begin(x), ranges::end(x), 1);
		VERIFY(ret == ranges::next(ranges::begin(x), 4));
		VERIFY(x[0] == 2);
		VERIFY(x[1] == 3);
		VERIFY(x[2] == 4);
		VERIFY(x[3] == 5);
//		VERIFY(x[4] == 5);	// undefined
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = bksge::shift_left(ranges::begin(x), ranges::end(x), 2);
		VERIFY(ret == ranges::next(ranges::begin(x), 3));
		VERIFY(x[0] == 3);
		VERIFY(x[1] == 4);
		VERIFY(x[2] == 5);
//		VERIFY(x[3] == 4);	// undefined
//		VERIFY(x[4] == 5);	// undefined
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = bksge::shift_left(ranges::begin(x), ranges::end(x), 3);
		VERIFY(ret == ranges::next(ranges::begin(x), 2));
		VERIFY(x[0] == 4);
		VERIFY(x[1] == 5);
//		VERIFY(x[2] == 3);	// undefined
//		VERIFY(x[3] == 4);	// undefined
//		VERIFY(x[4] == 5);	// undefined
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = bksge::shift_left(ranges::begin(x), ranges::end(x), 4);
		VERIFY(ret == ranges::next(ranges::begin(x), 1));
		VERIFY(x[0] == 5);
//		VERIFY(x[1] == 2);	// undefined
//		VERIFY(x[2] == 3);	// undefined
//		VERIFY(x[3] == 4);	// undefined
//		VERIFY(x[4] == 5);	// undefined
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = bksge::shift_left(ranges::begin(x), ranges::end(x), 5);
		VERIFY(ret == ranges::begin(x));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = bksge::shift_left(ranges::begin(x), ranges::end(x), 6);
		VERIFY(ret == ranges::begin(x));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap> cx(x);
		auto ret = bksge::shift_left(ranges::begin(cx), ranges::end(cx), -1);
		VERIFY(ret == ranges::end(cx));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap> cx(x);
		auto ret = bksge::shift_left(ranges::begin(cx), ranges::end(cx), 0);
		VERIFY(ret == ranges::end(cx));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap> cx(x);
		auto ret = bksge::shift_left(ranges::begin(cx), ranges::end(cx), 1);
		VERIFY(ret == ranges::next(ranges::begin(cx), 4));
		VERIFY(x[0] == 2);
		VERIFY(x[1] == 3);
		VERIFY(x[2] == 4);
		VERIFY(x[3] == 5);
//		VERIFY(x[4] == 5);	// undefined
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap> cx(x);
		auto ret = bksge::shift_left(ranges::begin(cx), ranges::end(cx), 4);
		VERIFY(ret == ranges::next(ranges::begin(cx), 1));
		VERIFY(x[0] == 5);
//		VERIFY(x[1] == 2);	// undefined
//		VERIFY(x[2] == 3);	// undefined
//		VERIFY(x[3] == 4);	// undefined
//		VERIFY(x[4] == 5);	// undefined
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap> cx(x);
		auto ret = bksge::shift_left(ranges::begin(cx), ranges::end(cx), 5);
		VERIFY(ret == ranges::begin(cx));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap> cx(x);
		auto ret = bksge::shift_left(ranges::begin(cx), ranges::end(cx), 6);
		VERIFY(ret == ranges::begin(cx));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct X
{
	int a = -1;
	bool moved_from = false;

	BKSGE_CXX14_CONSTEXPR X() = default;

	BKSGE_CXX14_CONSTEXPR X(int b) : a(b) {}

	X(const X&) = delete;
	X& operator=(const X&) = delete;

	BKSGE_CXX14_CONSTEXPR X(X&& other)
	{
		if (this != &other)
		{
			*this = bksge::move(other);
		}
	}

	BKSGE_CXX14_CONSTEXPR X& operator=(X&& other)
	{
		a = other.a;
		other.moved_from = true;
		moved_from = false;
		return *this;
	}
};

template <int N, template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	for (int n = 0; n < N+5; n++)
	{
		X x[N];
		for (int i = 0; i < N; i++)
		{
			x[i] = X{i};
		}

		test_container<X, IterWrap> cx(x);
		auto out = bksge::shift_left(cx.begin(), cx.end(), n);
		if (n < N)
		{
			VERIFY(out.m_ptr == x+(N-n));
			for (int i = 0; i < N-n; i++)
			{
				VERIFY(x[i].a == n+i);
				VERIFY(!x[i].moved_from);
			}
			for (int i = bksge::max(n, N-n); i < N; i++)
			{
				VERIFY(x[i].moved_from);
			}
		}
		else
		{
			VERIFY(out.m_ptr == x);
			for (int i = 0; i < N; i++)
			{
				VERIFY(x[i].a == i);
				VERIFY(!x[i].moved_from);
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, ShiftLeftTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02<random_access_iterator_wrapper>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test03<23, forward_iterator_wrapper>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test03<23, bidirectional_iterator_wrapper>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test03<23, random_access_iterator_wrapper>()));
}

}	// namespace shift_left_test

}	// namespace bksge_algorithm_test
