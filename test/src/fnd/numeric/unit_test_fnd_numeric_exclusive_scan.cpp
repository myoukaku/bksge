/**
 *	@file	unit_test_fnd_numeric_exclusive_scan.cpp
 *
 *	@brief	exclusive_scan のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/exclusive_scan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_numeric_test
{

namespace exclusive_scan_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int out[10] {};
	test_container<int, output_iterator_wrapper> co(out);
	test_container<int, input_iterator_wrapper> ca(a);
	auto end = bksge::exclusive_scan(ca.begin(), ca.end(), co.begin(), 5);
	static_assert(bksge::is_same<decltype(end), decltype(co.begin())>::value, "");
	VERIFY(end.m_ptr == out+10);
	VERIFY(out[0] == 5);
	VERIFY(out[1] == 6);
	VERIFY(out[2] == 8);
	VERIFY(out[3] == 11);
	VERIFY(out[4] == 15);
	VERIFY(out[5] == 20);
	VERIFY(out[6] == 26);
	VERIFY(out[7] == 33);
	VERIFY(out[8] == 41);
	VERIFY(out[9] == 50);

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
	auto end = bksge::exclusive_scan(ca.begin(), ca.end(), co.begin(), 2, func{});
	static_assert(bksge::is_same<decltype(end), decltype(co.begin())>::value, "");
	VERIFY(end.m_ptr == out+10);
	VERIFY(out[0] == 2);
	VERIFY(out[1] == 6);
	VERIFY(out[2] == 16);
	VERIFY(out[3] == 38);
	VERIFY(out[4] == 84);
	VERIFY(out[5] == 178);
	VERIFY(out[6] == 368);
	VERIFY(out[7] == 750);
	VERIFY(out[8] == 1516);
	VERIFY(out[9] == 3050);

	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, ExclusiveScanTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace exclusive_scan_test

}	// namespace bksge_numeric_test
