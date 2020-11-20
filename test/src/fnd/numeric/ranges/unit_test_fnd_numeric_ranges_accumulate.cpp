/**
 *	@file	unit_test_fnd_numeric_ranges_accumulate.cpp
 *
 *	@brief	ranges::accumulate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/ranges/accumulate.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_numeric_test
{

namespace ranges_accumulate_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct square
{
	template <typename T>
	constexpr T operator()(T x) const { return x * x; }
};

// accumulate(first, last, init)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {1,2,3,4,5,6,7,8,9,10};

		test_container<int, IterWrap> c(a);
		VERIFY(ranges::accumulate(c.begin(), c.begin(),  0) ==  0);
		VERIFY(ranges::accumulate(c.begin(), c.begin(), 42) == 42);
		VERIFY(ranges::accumulate(c.begin(), c.end(),  0) == 55);
		VERIFY(ranges::accumulate(c.begin(), c.end(), 42) == 97);

		test_range<int, IterWrap> r(a);
		VERIFY(ranges::accumulate(r.begin(), r.begin(),  0) ==  0);
		VERIFY(ranges::accumulate(r.begin(), r.begin(), 42) == 42);
		VERIFY(ranges::accumulate(r.begin(), r.end(),  0) == 55);
		VERIFY(ranges::accumulate(r.begin(), r.end(), 42) == 97);
	}
	return true;
}

// accumulate(first, last, init, op)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {1,2,3,4,5};

		test_container<int, IterWrap> c(a);
		VERIFY(ranges::accumulate(c.begin(), c.begin(), 0, bksge::multiplies<>{}) == 0);
		VERIFY(ranges::accumulate(c.begin(), c.begin(), 1, bksge::multiplies<>{}) == 1);
		VERIFY(ranges::accumulate(c.begin(), c.end(), 0, bksge::multiplies<>{}) == 0);
		VERIFY(ranges::accumulate(c.begin(), c.end(), 1, bksge::multiplies<>{}) == 120);

		test_range<int, IterWrap> r(a);
		VERIFY(ranges::accumulate(r.begin(), r.begin(), 0, bksge::multiplies<>{}) == 0);
		VERIFY(ranges::accumulate(r.begin(), r.begin(), 1, bksge::multiplies<>{}) == 1);
		VERIFY(ranges::accumulate(r.begin(), r.end(), 0, bksge::multiplies<>{}) == 0);
		VERIFY(ranges::accumulate(r.begin(), r.end(), 1, bksge::multiplies<>{}) == 120);
	}
	return true;
}

// accumulate(first, last, init, op, proj)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {1,2,3,4,5};

		test_container<int, IterWrap> c(a);
		VERIFY(ranges::accumulate(c.begin(), c.begin(), 0, bksge::plus<>{}, square{}) == 0);
		VERIFY(ranges::accumulate(c.begin(), c.begin(), 1, bksge::plus<>{}, square{}) == 1);
		VERIFY(ranges::accumulate(c.begin(), c.end(), 0, bksge::plus<>{}, square{}) == 55);
		VERIFY(ranges::accumulate(c.begin(), c.end(), 1, bksge::plus<>{}, square{}) == 56);

		test_range<int, IterWrap> r(a);
		VERIFY(ranges::accumulate(r.begin(), r.begin(), 0, bksge::plus<>{}, square{}) == 0);
		VERIFY(ranges::accumulate(r.begin(), r.begin(), 1, bksge::plus<>{}, square{}) == 1);
		VERIFY(ranges::accumulate(r.begin(), r.end(), 0, bksge::plus<>{}, square{}) == 55);
		VERIFY(ranges::accumulate(r.begin(), r.end(), 1, bksge::plus<>{}, square{}) == 56);
	}
	return true;
}

// accumulate(rng, init)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {1,2,3,4,5,6,7,8,9,10};
		VERIFY(ranges::accumulate(a,  0) == 55);
		VERIFY(ranges::accumulate(a, 42) == 97);

		test_container<int, IterWrap> c(a);
		VERIFY(ranges::accumulate(c,  0) == 55);
		VERIFY(ranges::accumulate(c, 42) == 97);

		test_range<int, IterWrap> r(a);
		VERIFY(ranges::accumulate(r,  0) == 55);
		VERIFY(ranges::accumulate(r, 42) == 97);
	}
	return true;
}

// accumulate(rng, init, op)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {1,2,3,4,5};
		VERIFY(ranges::accumulate(a, 0, bksge::multiplies<>{}) == 0);
		VERIFY(ranges::accumulate(a, 1, bksge::multiplies<>{}) == 120);

		test_container<int, IterWrap> c(a);
		VERIFY(ranges::accumulate(c, 0, bksge::multiplies<>{}) == 0);
		VERIFY(ranges::accumulate(c, 1, bksge::multiplies<>{}) == 120);

		test_range<int, IterWrap> r(a);
		VERIFY(ranges::accumulate(r, 0, bksge::multiplies<>{}) == 0);
		VERIFY(ranges::accumulate(r, 1, bksge::multiplies<>{}) == 120);
	}
	return true;
}

// accumulate(rng, init, op, proj)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test06()
{
	namespace ranges = bksge::ranges;
	{
		int a[] = {1,2,3,4,5};
		VERIFY(ranges::accumulate(a, 0, bksge::plus<>{}, square{}) == 55);
		VERIFY(ranges::accumulate(a, 1, bksge::plus<>{}, square{}) == 56);

		test_container<int, IterWrap> c(a);
		VERIFY(ranges::accumulate(c, 0, bksge::plus<>{}, square{}) == 55);
		VERIFY(ranges::accumulate(c, 1, bksge::plus<>{}, square{}) == 56);

		test_range<int, IterWrap> r(a);
		VERIFY(ranges::accumulate(r, 0, bksge::plus<>{}, square{}) == 55);
		VERIFY(ranges::accumulate(r, 1, bksge::plus<>{}, square{}) == 56);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, RangesAccumulateTest)
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

}	// namespace ranges_accumulate_test

}	// namespace bksge_numeric_test
