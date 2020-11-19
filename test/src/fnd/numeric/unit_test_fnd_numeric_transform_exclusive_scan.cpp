/**
 *	@file	unit_test_fnd_numeric_transform_exclusive_scan.cpp
 *
 *	@brief	transform_exclusive_scan のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/transform_exclusive_scan.hpp>
#include <bksge/fnd/functional/multiplies.hpp>
#include <bksge/fnd/functional/negate.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace bksge_numeric_test
{

namespace transform_exclusive_scan_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1, 2, 3, 4, 5, 6, 7};
	int out[7] {};
	test_container<int, output_iterator_wrapper> co(out);
	test_container<int, input_iterator_wrapper> ca(a);
	auto end = bksge::transform_exclusive_scan(ca.begin(), ca.end(), co.begin(), 5,
		bksge::multiplies<>{},
		bksge::negate<>{});
	static_assert(bksge::is_same<decltype(end), decltype(co.begin())>::value, "");
	VERIFY(end.m_ptr == out+7);
	VERIFY(out[0] == 5);
	VERIFY(out[1] == -5);
	VERIFY(out[2] == 10);
	VERIFY(out[3] == -30);
	VERIFY(out[4] == 120);
	VERIFY(out[5] == -600);
	VERIFY(out[6] == 3600);

	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, TransformExclusiveScanTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace transform_exclusive_scan_test

}	// namespace bksge_numeric_test
