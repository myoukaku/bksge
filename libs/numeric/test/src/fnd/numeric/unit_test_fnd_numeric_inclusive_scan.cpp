/**
 *	@file	unit_test_fnd_numeric_inclusive_scan.cpp
 *
 *	@brief	inclusive_scan のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/inclusive_scan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_numeric_test
{

namespace inclusive_scan_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int out[10] {};
	test_container<int, output_iterator_wrapper> co(out);
	test_container<int, input_iterator_wrapper> ca(a);
	auto end = bksge::inclusive_scan(ca.begin(), ca.end(), co.begin());
	static_assert(bksge::is_same<decltype(end), decltype(co.begin())>::value, "");
	VERIFY(end.m_ptr == out+10);
	VERIFY(out[0] == 1);
	VERIFY(out[1] == (1+2));
	VERIFY(out[2] == (1+2+3));
	VERIFY(out[3] == (1+2+3+4));
	VERIFY(out[4] == (1+2+3+4+5));
	VERIFY(out[5] == (1+2+3+4+5+6));
	VERIFY(out[6] == (1+2+3+4+5+6+7));
	VERIFY(out[7] == (1+2+3+4+5+6+7+8));
	VERIFY(out[8] == (1+2+3+4+5+6+7+8+9));
	VERIFY(out[9] == (1+2+3+4+5+6+7+8+9+10));

	return true;
}

struct func
{
	template <typename T>
	constexpr T operator()(T i, T j) const { return 2*i + 2*j; }
};

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int out[10] {};
	test_container<int, output_iterator_wrapper> co(out);
	test_container<int, input_iterator_wrapper> ca(a);
	auto end = bksge::inclusive_scan(ca.begin(), ca.end(), co.begin(), func{});
	static_assert(bksge::is_same<decltype(end), decltype(co.begin())>::value, "");
	VERIFY(end.m_ptr == out+10);
	VERIFY(out[0] == 1);
	VERIFY(out[1] == (2*1+2*2));
	VERIFY(out[2] == (2*6+2*3));
	VERIFY(out[3] == (2*18+2*4));
	VERIFY(out[4] == (2*44+2*5));
	VERIFY(out[5] == (2*98+2*6));
	VERIFY(out[6] == (2*208+2*7));
	VERIFY(out[7] == (2*430+2*8));
	VERIFY(out[8] == (2*876+2*9));
	VERIFY(out[9] == (2*1770+2*10));

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int out[10] {};
	test_container<int, output_iterator_wrapper> co(out);
	test_container<int, input_iterator_wrapper> ca(a);
	auto end = bksge::inclusive_scan(ca.begin(), ca.end(), co.begin(), func{}, 1);
	static_assert(bksge::is_same<decltype(end), decltype(co.begin())>::value, "");
	VERIFY(end.m_ptr == out+10);
	VERIFY(out[0] == 4);
	VERIFY(out[1] == (2*4+2*2));
	VERIFY(out[2] == (2*12+2*3));
	VERIFY(out[3] == (2*30+2*4));
	VERIFY(out[4] == (2*68+2*5));
	VERIFY(out[5] == (2*146+2*6));
	VERIFY(out[6] == (2*304+2*7));
	VERIFY(out[7] == (2*622+2*8));
	VERIFY(out[8] == (2*1260+2*9));
	VERIFY(out[9] == (2*2538+2*10));

	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, InclusiveScanTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace inclusive_scan_test

}	// namespace bksge_numeric_test
