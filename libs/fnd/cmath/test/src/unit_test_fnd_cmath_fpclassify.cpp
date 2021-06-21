/**
 *	@file	unit_test_fnd_cmath_fpclassify.cpp
 *
 *	@brief	fpclassify のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/fpclassify.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace fpclassify_test
{

static_assert(bksge::is_same<int, decltype(bksge::fpclassify(0.0f))>::value, "");
static_assert(bksge::is_same<int, decltype(bksge::fpclassify(0.0 ))>::value, "");
static_assert(bksge::is_same<int, decltype(bksge::fpclassify(0.0l))>::value, "");
static_assert(bksge::is_same<int, decltype(bksge::fpclassify(0   ))>::value, "");

template <typename T>
void FpClassifyTestFloat(void)
{
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto denorm_min = std::numeric_limits<T>::denorm_min();

	EXPECT_EQ(FP_INFINITE,  bksge::fpclassify(+inf));
	EXPECT_EQ(FP_INFINITE,  bksge::fpclassify(-inf));
	EXPECT_EQ(FP_NAN,       bksge::fpclassify(+nan));
	EXPECT_EQ(FP_NAN,       bksge::fpclassify(-nan));
	EXPECT_EQ(FP_NORMAL,    bksge::fpclassify(T(+1.0)));
	EXPECT_EQ(FP_NORMAL,    bksge::fpclassify(T(-1.0)));
	EXPECT_EQ(FP_ZERO,      bksge::fpclassify(T(+0.0)));
	EXPECT_EQ(FP_ZERO,      bksge::fpclassify(T(-0.0)));
	EXPECT_EQ(FP_NORMAL,    bksge::fpclassify(min));
	EXPECT_EQ(FP_NORMAL,    bksge::fpclassify(max));
	EXPECT_EQ(FP_NORMAL,    bksge::fpclassify(lowest));
	EXPECT_EQ(FP_SUBNORMAL, bksge::fpclassify( denorm_min));
	EXPECT_EQ(FP_SUBNORMAL, bksge::fpclassify(-denorm_min));
	EXPECT_EQ(FP_SUBNORMAL, bksge::fpclassify( min/2));
	EXPECT_EQ(FP_SUBNORMAL, bksge::fpclassify(-min/2));
}

template <typename T>
void FpClassifyTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	EXPECT_EQ(FP_ZERO,   bksge::fpclassify(T( 0)));
	EXPECT_EQ(FP_NORMAL, bksge::fpclassify(T(-1)));
	EXPECT_EQ(FP_NORMAL, bksge::fpclassify(T( 1)));
	EXPECT_EQ(FP_NORMAL, bksge::fpclassify(T(-2)));
	EXPECT_EQ(FP_NORMAL, bksge::fpclassify(T( 2)));
	EXPECT_EQ(FP_NORMAL, bksge::fpclassify(min));
	EXPECT_EQ(FP_NORMAL, bksge::fpclassify(max));
}

template <typename T>
void FpClassifyTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	EXPECT_EQ(FP_ZERO,   bksge::fpclassify(T( 0)));
	EXPECT_EQ(FP_NORMAL, bksge::fpclassify(T( 1)));
	EXPECT_EQ(FP_NORMAL, bksge::fpclassify(T( 2)));
	EXPECT_EQ(FP_ZERO,   bksge::fpclassify(min));
	EXPECT_EQ(FP_NORMAL, bksge::fpclassify(max));
}

GTEST_TEST(CMathTest, FpClassifyTest)
{
	FpClassifyTestFloat<float>();
	FpClassifyTestFloat<double>();
	FpClassifyTestFloat<long double>();

	FpClassifyTestSignedInt<int>();
	FpClassifyTestSignedInt<signed char>();
	FpClassifyTestSignedInt<short>();
	FpClassifyTestSignedInt<long>();
	FpClassifyTestSignedInt<long long>();

	FpClassifyTestUnsignedInt<unsigned int>();
	FpClassifyTestUnsignedInt<unsigned char>();
	FpClassifyTestUnsignedInt<unsigned short>();
	FpClassifyTestUnsignedInt<unsigned long>();
	FpClassifyTestUnsignedInt<unsigned long long>();
}

}	// namespace fpclassify_test

}	// namespace bksge_cmath_test
