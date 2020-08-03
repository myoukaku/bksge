/**
 *	@file	unit_test_fnd_iterator_prev.cpp
 *
 *	@brief	prev のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4146); // 符号付きの値を代入する変数は、符号付き型にキャストしなければなりません。
BKSGE_WARNING_DISABLE_MSVC(4307); // '+': 整数定数がオーバーフローしました。
BKSGE_WARNING_DISABLE_MSVC(4308); // 負の整数定数が符号なしの型に変換されました。

#include <bksge/fnd/iterator/prev.hpp>
#include <bksge/fnd/iterator/next.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <array>
#include <vector>
#include <list>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_iterator_test
{

namespace prev_test
{

GTEST_TEST(IteratorTest, PrevTest)
{
	{
		int a[] = {0,1,2};

		auto it = bksge::end(a);
		it = bksge::prev(it);
		EXPECT_EQ(2, *it);
		it = bksge::prev(it);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it);
		EXPECT_EQ(0, *it);
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		const int a[] = {0,1,2};

		auto it = bksge::end(a);
		it = bksge::prev(it, 2);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it, -1);
		EXPECT_EQ(2, *it);
		it = bksge::prev(it, 2);
		EXPECT_EQ(0, *it);
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR int a[] = {0, 1, 2, 3, 4};

		BKSGE_CONSTEXPR auto it1 = bksge::end(a);
		BKSGE_CONSTEXPR auto it2 = bksge::prev(it1);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, *it2);
		BKSGE_CONSTEXPR auto it3 = bksge::prev(it2, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, *it3);
		BKSGE_CONSTEXPR auto it4 = bksge::prev(it3, -1);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, *it4);
		BKSGE_CONSTEXPR auto it5 = bksge::prev(it4, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, *it5);
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 == bksge::begin(a));
	}
	{
		const std::vector<float> v {3,1,4,1,5};

		auto it = bksge::end(v);
		it = bksge::prev(it);
		EXPECT_EQ(5, *it);
		it = bksge::prev(it);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it);
		EXPECT_EQ(3, *it);
		EXPECT_TRUE(it == bksge::begin(v));
	}
	{
		std::vector<float> v {3,1,4,1,5};

		auto it = bksge::end(v);
		it = bksge::prev(it, 3);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it, -1);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it, 2);
		EXPECT_EQ(1, *it);
		it = bksge::prev(it, -3);
		EXPECT_EQ(5, *it);
		it = bksge::prev(it, 4);
		EXPECT_EQ(3, *it);
		EXPECT_TRUE(it == bksge::begin(v));
	}
	{
		std::list<int> l {2, 3, 4};

		auto it = bksge::end(l);
		it = bksge::prev(it);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it);
		EXPECT_EQ(3, *it);
		it = bksge::prev(it);
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it == bksge::begin(l));
	}
	{
		const std::list<int> l {2, 3, 4};

		auto it = bksge::end(l);
		it = bksge::prev(it, 2);
		EXPECT_EQ(3, *it);
		it = bksge::prev(it, -1);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it, 2);
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it == bksge::begin(l));
	}
	{
		const std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::end(a);
		it = bksge::prev(it);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it);
		EXPECT_EQ(3, *it);
		it = bksge::prev(it);
		EXPECT_EQ(2, *it);
		it = bksge::prev(it);
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		std::array<float, 4> a{{1, 2, 3, 4}};

		auto it = bksge::end(a);
		it = bksge::prev(it, 2);
		EXPECT_EQ(3, *it);
		it = bksge::prev(it, -1);
		EXPECT_EQ(4, *it);
		it = bksge::prev(it, 3);
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it == bksge::begin(a));
	}
	{
		BKSGE_STATIC_CONSTEXPR std::array<int,5> a {{0, 1, 2, 3, 4}};

		BKSGE_CXX17_CONSTEXPR auto it1 = bksge::end(a);
		BKSGE_CXX17_CONSTEXPR auto it2 = bksge::prev(it1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, *it2);
		BKSGE_CXX17_CONSTEXPR auto it3 = bksge::prev(it2, 2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it3);
		BKSGE_CXX17_CONSTEXPR auto it4 = bksge::prev(it3, -1);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, *it4);
		BKSGE_CXX17_CONSTEXPR auto it5 = bksge::prev(it4, 3);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(0, *it5);
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 == bksge::begin(a));
	}
}

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_random_access_range<int> r(a);
	auto begin = r.begin();
	auto end = r.end();
	auto endi = bksge::ranges::next(begin, end);
	VERIFY(*bksge::ranges::prev(endi) == 9);
	VERIFY( bksge::ranges::prev(begin, 0) == begin);
	VERIFY(*bksge::ranges::prev(endi, 1) == 9);
	VERIFY(*bksge::ranges::prev(endi, 3) == 7);
	VERIFY(*bksge::ranges::prev(begin, -4) == 4);
	VERIFY( bksge::ranges::prev(begin, 0, begin) == begin);
	VERIFY( bksge::ranges::prev(begin, 5, begin) == begin);
	VERIFY( bksge::ranges::prev(begin, -5, begin) == begin);
	VERIFY( bksge::ranges::prev(begin, 0, endi) == begin);
	VERIFY(*bksge::ranges::prev(endi, 5, begin) == 5);
	VERIFY( bksge::ranges::prev(endi, 55, begin) == begin);
	VERIFY( bksge::ranges::prev(endi, 0, endi) == end);
	VERIFY( bksge::ranges::prev(endi, -5, endi) == end);
	VERIFY( bksge::ranges::prev(endi, -55, endi) == end);
	VERIFY( bksge::ranges::prev(endi, 0, begin) == end);
	VERIFY(*bksge::ranges::prev(begin, -5, endi) == 5);
	VERIFY( bksge::ranges::prev(begin, -55, endi) == end);

	return true;
}

BKSGE_CXX14_CONSTEXPR bool test02()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_bidirectional_range<int> r(a);
	auto begin = r.begin();
	auto end = r.end();
	auto endi = bksge::ranges::next(begin, end);
	VERIFY(*bksge::ranges::prev(endi) == 9);
	VERIFY( bksge::ranges::prev(begin, 0) == begin);
	VERIFY(*bksge::ranges::prev(endi, 1) == 9);
	VERIFY(*bksge::ranges::prev(endi, 3) == 7);
	VERIFY(*bksge::ranges::prev(begin, -4) == 4);
	VERIFY( bksge::ranges::prev(begin, 0, begin) == begin);
	VERIFY( bksge::ranges::prev(begin, 5, begin) == begin);
	VERIFY( bksge::ranges::prev(begin, -5, begin) == begin);
	VERIFY( bksge::ranges::prev(begin, 0, endi) == begin);
	VERIFY(*bksge::ranges::prev(endi, 5, begin) == 5);
	VERIFY( bksge::ranges::prev(endi, 55, begin) == begin);
	VERIFY( bksge::ranges::prev(endi, 0, endi) == end);
	VERIFY( bksge::ranges::prev(endi, -5, endi) == end);
	VERIFY( bksge::ranges::prev(endi, -55, endi) == end);
	VERIFY( bksge::ranges::prev(endi, 0, begin) == end);
	VERIFY(*bksge::ranges::prev(begin, -5, endi) == 5);
	VERIFY( bksge::ranges::prev(begin, -55, endi) == end);

	return true;
}

#undef VERIFY

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept can_prev =
	requires(T& t) { bksge::ranges::prev(t); } &&
	requires(T& t) { bksge::ranges::prev(t, 1); } &&
	requires(T& t) { bksge::ranges::prev(t, 1, t); };

static_assert( can_prev<random_access_iterator_wrapper<int>>, "");
static_assert( can_prev<bidirectional_iterator_wrapper<int>>, "");
static_assert(!can_prev<forward_iterator_wrapper<int>>, "");
static_assert(!can_prev<input_iterator_wrapper<int>>, "");
static_assert(!can_prev<output_iterator_wrapper<int>>, "");

#else

template <typename T>
struct can_prev_impl
{
private:
	template <typename U>
	static auto test(int) -> decltype(
		bksge::ranges::prev(bksge::declval<U&>()),
		bksge::ranges::prev(bksge::declval<U&>(), 1),
		bksge::ranges::prev(bksge::declval<U&>(), 1, bksge::declval<U&>()),
		bksge::true_type{});

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using can_prev =
	typename can_prev_impl<T>::type;

static_assert( can_prev<random_access_iterator_wrapper<int>>::value, "");
static_assert( can_prev<bidirectional_iterator_wrapper<int>>::value, "");
static_assert(!can_prev<forward_iterator_wrapper<int>>::value, "");
static_assert(!can_prev<input_iterator_wrapper<int>>::value, "");
static_assert(!can_prev<output_iterator_wrapper<int>>::value, "");

#endif

GTEST_TEST(IteratorTest, RangesPrevTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace prev_test

}	// namespace bksge_iterator_test

BKSGE_WARNING_POP();
