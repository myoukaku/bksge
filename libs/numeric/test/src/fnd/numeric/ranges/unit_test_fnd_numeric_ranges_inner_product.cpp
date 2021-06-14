/**
 *	@file	unit_test_fnd_numeric_ranges_inner_product.cpp
 *
 *	@brief	ranges::inner_product のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/ranges/inner_product.hpp>
#include <bksge/fnd/functional/plus.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_numeric_test
{

namespace ranges_inner_product_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct square
{
	template <typename T>
	constexpr T operator()(T x) const { return x * x; }
};

// inner_product(first1, last1, first2, init)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = bksge::ranges;
	{
		int a1[] = { 1, 2, 3 };
		int a2[] = { 4, 5, 6 };
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::begin(a1), bksge::begin(a2), 0) == 0);
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::begin(a1), bksge::begin(a2), 1) == 1);
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 0) == 32);
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 1) == 33);

		test_container<int, IterWrap> c1(a1);
		test_container<int, IterWrap> c2(a2);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::begin(c1), bksge::begin(c2), 0) == 0);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::begin(c1), bksge::begin(c2), 2) == 2);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1), bksge::begin(c2), 0) == 32);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1), bksge::begin(c2), 2) == 34);

		test_range<int, IterWrap> r1(a1);
		test_range<int, IterWrap> r2(a2);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::begin(r1), bksge::begin(r2), 0) == 0);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::begin(r1), bksge::begin(r2), 3) == 3);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1), bksge::begin(r2), 0) == 32);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1), bksge::begin(r2), 3) == 35);
	}
	return true;
}

// inner_product(first1, last1, first2, init, op1)
// inner_product(first1, last1, first2, init, op1, op2)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = bksge::ranges;
	{
		int a1[] = { 1, 2, 3, 4 };
		int a2[] = { 4, 5, 6, 7 };
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 0, bksge::multiplies<>{}) == 0);
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 1, bksge::multiplies<>{}) == 4*10*18*28);

		test_container<int, IterWrap> c1(a1);
		test_container<int, IterWrap> c2(a2);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1), bksge::begin(c2), 0, bksge::multiplies<>{}, bksge::plus<>{}) == 0);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1), bksge::begin(c2), 1, bksge::multiplies<>{}, bksge::plus<>{}) == 5*7*9*11);

		test_range<int, IterWrap> r1(a1);
		test_range<int, IterWrap> r2(a2);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1), bksge::begin(r2), 0, bksge::plus<>{}, bksge::plus<>{}) ==   5+7+9+11);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1), bksge::begin(r2), 1, bksge::plus<>{}, bksge::plus<>{}) == 1+5+7+9+11);
	}
	return true;
}

// inner_product(first1, last1, first2, init, op1, op2, proj1)
// inner_product(first1, last1, first2, init, op1, op2, proj1, proj2)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = bksge::ranges;
	{
		int a1[] = { 1, 2, 3 };
		int a2[] = { 4, 5, 6 };
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), 0, bksge::plus<>{}, bksge::multiplies<>{}, square{}) == 4+20+54);

		test_container<int, IterWrap> c1(a1);
		test_container<int, IterWrap> c2(a2);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1), bksge::begin(c2), 0, bksge::plus<>{}, bksge::multiplies<>{}, bksge::identity{}, square{}) == 16+50+108);

		test_range<int, IterWrap> r1(a1);
		test_range<int, IterWrap> r2(a2);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1), bksge::begin(r2), 0, bksge::plus<>{}, bksge::multiplies<>{}, square{}, square{}) == 16+100+324);
	}
	return true;
}

// inner_product(first1, last1, first2, last2, init)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = bksge::ranges;
	{
		int a1[] = { 1, 2, 3 };
		int a2[] = { 4, 5, 6 };
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::begin(a1), bksge::begin(a2), bksge::end(a2), 0) == 0);
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::begin(a1), bksge::begin(a2), bksge::end(a2), 1) == 1);
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1),   bksge::begin(a2), bksge::begin(a2), 0) == 0);
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1),   bksge::begin(a2), bksge::begin(a2), 1) == 1);
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1),   bksge::begin(a2), bksge::end(a2), 0) == 32);
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1),   bksge::begin(a2), bksge::end(a2), 1) == 33);

		test_container<int, IterWrap> c1(a1);
		test_container<int, IterWrap> c2(a2);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::begin(c1), bksge::begin(c2), bksge::end(c2), 0) == 0);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::begin(c1), bksge::begin(c2), bksge::end(c2), 2) == 2);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1),   bksge::begin(c2), bksge::begin(c2), 0) == 0);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1),   bksge::begin(c2), bksge::begin(c2), 2) == 2);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1),   bksge::begin(c2), bksge::end(c2), 0) == 32);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1),   bksge::begin(c2), bksge::end(c2), 2) == 34);

		test_range<int, IterWrap> r1(a1);
		test_range<int, IterWrap> r2(a2);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::begin(r1), bksge::begin(r2), bksge::end(r2), 0) == 0);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::begin(r1), bksge::begin(r2), bksge::end(r2), 3) == 3);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1),   bksge::begin(r2), bksge::begin(r2), 0) == 0);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1),   bksge::begin(r2), bksge::begin(r2), 3) == 3);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1),   bksge::begin(r2), bksge::end(r2), 0) == 32);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1),   bksge::begin(r2), bksge::end(r2), 3) == 35);
	}
	return true;
}

// inner_product(first1, last1, first2, last2, init, op1)
// inner_product(first1, last1, first2, last2, init, op1, op2)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = bksge::ranges;
	{
		int a1[] = { 1, 2, 3, 4 };
		int a2[] = { 4, 5, 6, 7 };
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), bksge::end(a2), 0, bksge::multiplies<>{}) == 0);
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), bksge::end(a2), 1, bksge::multiplies<>{}) == 4*10*18*28);

		test_container<int, IterWrap> c1(a1);
		test_container<int, IterWrap> c2(a2);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1), bksge::begin(c2), bksge::end(c2), 0, bksge::multiplies<>{}, bksge::plus<>{}) == 0);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1), bksge::begin(c2), bksge::end(c2), 1, bksge::multiplies<>{}, bksge::plus<>{}) == 5*7*9*11);

		test_range<int, IterWrap> r1(a1);
		test_range<int, IterWrap> r2(a2);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1), bksge::begin(r2), bksge::end(r2), 0, bksge::plus<>{}, bksge::plus<>{}) ==   5+7+9+11);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1), bksge::begin(r2), bksge::end(r2), 1, bksge::plus<>{}, bksge::plus<>{}) == 1+5+7+9+11);
	}
	return true;
}

// inner_product(first1, last1, first2, last2, init, op1, op2, proj1)
// inner_product(first1, last1, first2, last2, init, op1, op2, proj1, proj2)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test06()
{
	namespace ranges = bksge::ranges;
	{
		int a1[] = { 1, 2, 3 };
		int a2[] = { 4, 5, 6 };
		VERIFY(ranges::inner_product(bksge::begin(a1), bksge::end(a1), bksge::begin(a2), bksge::end(a2), 0, bksge::plus<>{}, bksge::multiplies<>{}, square{}) == 4+20+54);

		test_container<int, IterWrap> c1(a1);
		test_container<int, IterWrap> c2(a2);
		VERIFY(ranges::inner_product(bksge::begin(c1), bksge::end(c1), bksge::begin(c2), bksge::end(c2), 0, bksge::plus<>{}, bksge::multiplies<>{}, bksge::identity{}, square{}) == 16+50+108);

		test_range<int, IterWrap> r1(a1);
		test_range<int, IterWrap> r2(a2);
		VERIFY(ranges::inner_product(bksge::begin(r1), bksge::end(r1), bksge::begin(r2), bksge::end(r2), 0, bksge::plus<>{}, bksge::multiplies<>{}, square{}, square{}) == 16+100+324);
	}
	return true;
}

// inner_product(rng1, rng2, init)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test07()
{
	namespace ranges = bksge::ranges;
	{
		int a1[] = { 1, 2, 3 };
		int a2[] = { 4, 5, 6 };
		VERIFY(ranges::inner_product(a1, a2, 0) == 32);
		VERIFY(ranges::inner_product(a1, a2, 1) == 33);

		test_container<int, IterWrap> c1(a1);
		test_container<int, IterWrap> c2(a2);
		VERIFY(ranges::inner_product(c1, c2, 0) == 32);
		VERIFY(ranges::inner_product(c1, c2, 2) == 34);

		test_range<int, IterWrap> r1(a1);
		test_range<int, IterWrap> r2(a2);
		VERIFY(ranges::inner_product(r1, r2, 0) == 32);
		VERIFY(ranges::inner_product(r1, r2, 3) == 35);
	}
	return true;
}

// inner_product(rng1, rng2, init, op1)
// inner_product(rng1, rng2, init, op1, op2)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test08()
{
	namespace ranges = bksge::ranges;
	{
		int a1[] = { 1, 2, 3, 4 };
		int a2[] = { 4, 5, 6, 7 };
		VERIFY(ranges::inner_product(a1, a2, 0, bksge::multiplies<>{}) == 0);
		VERIFY(ranges::inner_product(a1, a2, 1, bksge::multiplies<>{}) == 4*10*18*28);

		test_container<int, IterWrap> c1(a1);
		test_container<int, IterWrap> c2(a2);
		VERIFY(ranges::inner_product(c1, c2, 0, bksge::multiplies<>{}, bksge::plus<>{}) == 0);
		VERIFY(ranges::inner_product(c1, c2, 1, bksge::multiplies<>{}, bksge::plus<>{}) == 5*7*9*11);

		test_range<int, IterWrap> r1(a1);
		test_range<int, IterWrap> r2(a2);
		VERIFY(ranges::inner_product(r1, r2, 0, bksge::plus<>{}, bksge::plus<>{}) ==   5+7+9+11);
		VERIFY(ranges::inner_product(r1, r2, 1, bksge::plus<>{}, bksge::plus<>{}) == 1+5+7+9+11);
	}
	return true;
}

// inner_product(rng1, rng2, init, op1, op2, proj1)
// inner_product(rng1, rng2, init, op1, op2, proj1, proj2)
template <template <typename> class IterWrap>
inline BKSGE_CXX14_CONSTEXPR bool test09()
{
	namespace ranges = bksge::ranges;
	{
		int a1[] = { 1, 2, 3 };
		int a2[] = { 4, 5, 6 };
		VERIFY(ranges::inner_product(a1, a2, 0, bksge::plus<>{}, bksge::multiplies<>{}, square{}) == 4+20+54);

		test_container<int, IterWrap> c1(a1);
		test_container<int, IterWrap> c2(a2);
		VERIFY(ranges::inner_product(c1, c2, 0, bksge::plus<>{}, bksge::multiplies<>{}, bksge::identity{}, square{}) == 16+50+108);

		test_range<int, IterWrap> r1(a1);
		test_range<int, IterWrap> r2(a2);
		VERIFY(ranges::inner_product(r1, r2, 0, bksge::plus<>{}, bksge::multiplies<>{}, square{}, square{}) == 16+100+324);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, RangesInnerProductTest)
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

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test07<input_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test07<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test07<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test07<random_access_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test07<contiguous_iterator_wrapper>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test08<input_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test08<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test08<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test08<random_access_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test08<contiguous_iterator_wrapper>());

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test09<input_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test09<forward_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test09<bidirectional_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test09<random_access_iterator_wrapper>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test09<contiguous_iterator_wrapper>());
}

}	// namespace ranges_inner_product_test

}	// namespace bksge_numeric_test
