/**
 *	@file	unit_test_fnd_numeric_ranges_adjacent_difference.cpp
 *
 *	@brief	ranges::adjacent_difference のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/ranges/adjacent_difference.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/functional/minus.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_numeric_test
{

namespace ranges_adjacent_difference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct square
{
	template <typename T>
	constexpr T operator()(T x) const { return x * x; }
};

// adjacent_difference(first, last, result)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		auto ret = ranges::adjacent_difference(bksge::begin(a), bksge::begin(a), bksge::begin(b));
		VERIFY(ret.in  == bksge::begin(a));
		VERIFY(ret.out == bksge::begin(b));
		VERIFY(b[0] == 0);
		VERIFY(b[1] == 0);
		VERIFY(b[2] == 0);
		VERIFY(b[3] == 0);
		VERIFY(b[4] == 0);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		auto ret = ranges::adjacent_difference(bksge::begin(a), bksge::end(a), bksge::begin(b));
		VERIFY(ret.in  == bksge::end(a));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] ==  3);
		VERIFY(b[1] == -2);
		VERIFY(b[2] ==  3);
		VERIFY(b[3] == -3);
		VERIFY(b[4] ==  4);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_container<int, IterWrap> c(a);
		auto ret = ranges::adjacent_difference(bksge::begin(c), bksge::end(c), bksge::begin(b));
		VERIFY(ret.in  == bksge::end(c));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] ==  3);
		VERIFY(b[1] == -2);
		VERIFY(b[2] ==  3);
		VERIFY(b[3] == -3);
		VERIFY(b[4] ==  4);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_range<int, IterWrap> ra(a);
		test_range<int, output_iterator_wrapper> rb(b);
		auto ret = ranges::adjacent_difference(bksge::begin(ra), bksge::end(ra), bksge::begin(rb));
		VERIFY(ret.in  == bksge::end(ra));
		VERIFY(ret.out == bksge::end(rb));
		VERIFY(b[0] ==  3);
		VERIFY(b[1] == -2);
		VERIFY(b[2] ==  3);
		VERIFY(b[3] == -3);
		VERIFY(b[4] ==  4);
	}
	return true;
}

// adjacent_difference(first, last, result, op)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		auto ret = ranges::adjacent_difference(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::plus<>{});
		VERIFY(ret.in  == bksge::end(a));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] == 3);
		VERIFY(b[1] == 4);
		VERIFY(b[2] == 5);
		VERIFY(b[3] == 5);
		VERIFY(b[4] == 6);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_container<int, IterWrap> c(a);
		auto ret = ranges::adjacent_difference(bksge::begin(c), bksge::end(c), bksge::begin(b), bksge::plus<>{});
		VERIFY(ret.in  == bksge::end(c));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] == 3);
		VERIFY(b[1] == 4);
		VERIFY(b[2] == 5);
		VERIFY(b[3] == 5);
		VERIFY(b[4] == 6);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_range<int, IterWrap> ra(a);
		test_range<int, output_iterator_wrapper> rb(b);
		auto ret = ranges::adjacent_difference(bksge::begin(ra), bksge::end(ra), bksge::begin(rb), bksge::plus<>{});
		VERIFY(ret.in  == bksge::end(ra));
		VERIFY(ret.out == bksge::end(rb));
		VERIFY(b[0] == 3);
		VERIFY(b[1] == 4);
		VERIFY(b[2] == 5);
		VERIFY(b[3] == 5);
		VERIFY(b[4] == 6);
	}
	return true;
}

// adjacent_difference(first, last, result, op, proj)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		auto ret = ranges::adjacent_difference(bksge::begin(a), bksge::end(a), bksge::begin(b), bksge::minus<>{}, square{});
		VERIFY(ret.in  == bksge::end(a));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] ==   9);
		VERIFY(b[1] ==  -8);
		VERIFY(b[2] ==  15);
		VERIFY(b[3] == -15);
		VERIFY(b[4] ==  24);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_container<int, IterWrap> c(a);
		auto ret = ranges::adjacent_difference(bksge::begin(c), bksge::end(c), bksge::begin(b), bksge::minus<>{}, square{});
		VERIFY(ret.in  == bksge::end(c));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] ==   9);
		VERIFY(b[1] ==  -8);
		VERIFY(b[2] ==  15);
		VERIFY(b[3] == -15);
		VERIFY(b[4] ==  24);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_range<int, IterWrap> ra(a);
		test_range<int, output_iterator_wrapper> rb(b);
		auto ret = ranges::adjacent_difference(bksge::begin(ra), bksge::end(ra), bksge::begin(rb), bksge::minus<>{}, square{});
		VERIFY(ret.in  == bksge::end(ra));
		VERIFY(ret.out == bksge::end(rb));
		VERIFY(b[0] ==   9);
		VERIFY(b[1] ==  -8);
		VERIFY(b[2] ==  15);
		VERIFY(b[3] == -15);
		VERIFY(b[4] ==  24);
	}
	return true;
}

// adjacent_difference(rng, result)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		auto ret = ranges::adjacent_difference(a, bksge::begin(b));
		VERIFY(ret.in  == bksge::end(a));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] ==  3);
		VERIFY(b[1] == -2);
		VERIFY(b[2] ==  3);
		VERIFY(b[3] == -3);
		VERIFY(b[4] ==  4);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_container<int, IterWrap> c(a);
		auto ret = ranges::adjacent_difference(c, bksge::begin(b));
		VERIFY(ret.in  == bksge::end(c));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] ==  3);
		VERIFY(b[1] == -2);
		VERIFY(b[2] ==  3);
		VERIFY(b[3] == -3);
		VERIFY(b[4] ==  4);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_range<int, IterWrap> ra(a);
		test_range<int, output_iterator_wrapper> rb(b);
		auto ret = ranges::adjacent_difference(ra, bksge::begin(rb));
		VERIFY(ret.in  == bksge::end(ra));
		VERIFY(ret.out == bksge::end(rb));
		VERIFY(b[0] ==  3);
		VERIFY(b[1] == -2);
		VERIFY(b[2] ==  3);
		VERIFY(b[3] == -3);
		VERIFY(b[4] ==  4);
	}
	return true;
}

// adjacent_difference(rng, result, op)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		auto ret = ranges::adjacent_difference(a, bksge::begin(b), bksge::plus<>{});
		VERIFY(ret.in  == bksge::end(a));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] == 3);
		VERIFY(b[1] == 4);
		VERIFY(b[2] == 5);
		VERIFY(b[3] == 5);
		VERIFY(b[4] == 6);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_container<int, IterWrap> c(a);
		auto ret = ranges::adjacent_difference(c, bksge::begin(b), bksge::plus<>{});
		VERIFY(ret.in  == bksge::end(c));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] == 3);
		VERIFY(b[1] == 4);
		VERIFY(b[2] == 5);
		VERIFY(b[3] == 5);
		VERIFY(b[4] == 6);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_range<int, IterWrap> ra(a);
		test_range<int, output_iterator_wrapper> rb(b);
		auto ret = ranges::adjacent_difference(ra, bksge::begin(rb), bksge::plus<>{});
		VERIFY(ret.in  == bksge::end(ra));
		VERIFY(ret.out == bksge::end(rb));
		VERIFY(b[0] == 3);
		VERIFY(b[1] == 4);
		VERIFY(b[2] == 5);
		VERIFY(b[3] == 5);
		VERIFY(b[4] == 6);
	}
	return true;
}

// adjacent_difference(rng, result, op, proj)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test06()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		auto ret = ranges::adjacent_difference(a, bksge::begin(b), bksge::minus<>{}, square{});
		VERIFY(ret.in  == bksge::end(a));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] ==   9);
		VERIFY(b[1] ==  -8);
		VERIFY(b[2] ==  15);
		VERIFY(b[3] == -15);
		VERIFY(b[4] ==  24);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_container<int, IterWrap> c(a);
		auto ret = ranges::adjacent_difference(c, bksge::begin(b), bksge::minus<>{}, square{});
		VERIFY(ret.in  == bksge::end(c));
		VERIFY(ret.out == bksge::end(b));
		VERIFY(b[0] ==   9);
		VERIFY(b[1] ==  -8);
		VERIFY(b[2] ==  15);
		VERIFY(b[3] == -15);
		VERIFY(b[4] ==  24);
	}
	{
		int a[] = {3,1,4,1,5};
		int b[5] {};
		test_range<int, IterWrap> ra(a);
		test_range<int, output_iterator_wrapper> rb(b);
		auto ret = ranges::adjacent_difference(ra, bksge::begin(rb), bksge::minus<>{}, square{});
		VERIFY(ret.in  == bksge::end(ra));
		VERIFY(ret.out == bksge::end(rb));
		VERIFY(b[0] ==   9);
		VERIFY(b[1] ==  -8);
		VERIFY(b[2] ==  15);
		VERIFY(b[3] == -15);
		VERIFY(b[4] ==  24);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, RangesAdjacentDifferenceTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<input_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<random_access_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01<contiguous_iterator_wrapper>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02<input_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02<random_access_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02<contiguous_iterator_wrapper>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03<input_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03<random_access_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03<contiguous_iterator_wrapper>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04<input_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04<random_access_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test04<contiguous_iterator_wrapper>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05<input_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05<random_access_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test05<contiguous_iterator_wrapper>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06<input_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06<random_access_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test06<contiguous_iterator_wrapper>());
}

}	// namespace ranges_adjacent_difference_test

}	// namespace bksge_numeric_test
