/**
 *	@file	unit_test_fnd_numeric_transform_inclusive_scan.cpp
 *
 *	@brief	transform_inclusive_scan のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/transform_inclusive_scan.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_numeric_test
{

namespace transform_inclusive_scan_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct func
{
	template <typename T>
	constexpr T operator()(T i) const { return i+1; }
};


inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7};
	int out[7] {};
	test_container<int, output_iterator_wrapper> co(out);
	test_container<int, input_iterator_wrapper> ca(a);
	auto end = bksge::transform_inclusive_scan(ca.begin(), ca.end(), co.begin(),
		bksge::multiplies<>{},
		func{});
	static_assert(bksge::is_same<decltype(end), decltype(co.begin())>::value, "");
	VERIFY(end.m_ptr == out+7);
	VERIFY(out[0] == 2);
	VERIFY(out[1] == (2*3));
	VERIFY(out[2] == (2*3*4));
	VERIFY(out[3] == (2*3*4*5));
	VERIFY(out[4] == (2*3*4*5*6));
	VERIFY(out[5] == (2*3*4*5*6*7));
	VERIFY(out[6] == (2*3*4*5*6*7*8));

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7};
	int out[7] {};
	test_container<int, output_iterator_wrapper> co(out);
	test_container<int, input_iterator_wrapper> ca(a);
	auto end = bksge::transform_inclusive_scan(ca.begin(), ca.end(), co.begin(),
		bksge::multiplies<>{},
		func{},
		3);
	static_assert(bksge::is_same<decltype(end), decltype(co.begin())>::value, "");
	VERIFY(end.m_ptr == out+7);
	VERIFY(out[0] == 3*2);
	VERIFY(out[1] == (3*2*3));
	VERIFY(out[2] == (3*2*3*4));
	VERIFY(out[3] == (3*2*3*4*5));
	VERIFY(out[4] == (3*2*3*4*5*6));
	VERIFY(out[5] == (3*2*3*4*5*6*7));
	VERIFY(out[6] == (3*2*3*4*5*6*7*8));

	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, TransformInclusiveScanTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace transform_inclusive_scan_test

}	// namespace bksge_numeric_test
