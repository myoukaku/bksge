/**
 *	@file	unit_test_fnd_cmath_rint.cpp
 *
 *	@brief	rint のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/rint.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/float_promote.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include <cfenv>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace rint_test
{

static_assert(bksge::is_same<float,       decltype(bksge::rint(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::rintf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::rint(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::rint(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::rint(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::rintl(0.0l))>::value, "");

template <typename T>
inline bksge::float_promote_t<T>
rint_helper(T x, int round_mode)
{
	auto current = std::fegetround();
	std::fesetround(round_mode);
	auto ret = bksge::rint(x);
	std::fesetround(current);
	return ret;
}

template <typename T>
void RIntTestFloat(void)
{
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();

	EXPECT_EQ(T( 0.0), rint_helper(T( 0.0), FE_DOWNWARD));
	EXPECT_EQ(T( 2.0), rint_helper(T( 2.5), FE_DOWNWARD));
	EXPECT_EQ(T(-3.0), rint_helper(T(-2.5), FE_DOWNWARD));
	EXPECT_EQ(T( 3.0), rint_helper(T( 3.5), FE_DOWNWARD));
	EXPECT_EQ(T(-4.0), rint_helper(T(-3.5), FE_DOWNWARD));
	EXPECT_EQ(+inf,    rint_helper(+inf,    FE_DOWNWARD));
	EXPECT_EQ(-inf,    rint_helper(-inf,    FE_DOWNWARD));
	EXPECT_TRUE(bksge::isnan(rint_helper(nan, FE_DOWNWARD)));

	EXPECT_EQ(T( 0.0), rint_helper(T( 0.0), FE_TONEAREST));
	EXPECT_EQ(T( 2.0), rint_helper(T( 2.5), FE_TONEAREST));
	EXPECT_EQ(T(-2.0), rint_helper(T(-2.5), FE_TONEAREST));
	EXPECT_EQ(T( 4.0), rint_helper(T( 3.5), FE_TONEAREST));
	EXPECT_EQ(T(-4.0), rint_helper(T(-3.5), FE_TONEAREST));
	EXPECT_EQ(+inf,    rint_helper(+inf,    FE_TONEAREST));
	EXPECT_EQ(-inf,    rint_helper(-inf,    FE_TONEAREST));
	EXPECT_TRUE(bksge::isnan(rint_helper(nan, FE_TONEAREST)));

	EXPECT_EQ(T( 0.0), rint_helper(T( 0.0), FE_TOWARDZERO));
	EXPECT_EQ(T( 2.0), rint_helper(T( 2.5), FE_TOWARDZERO));
	EXPECT_EQ(T(-2.0), rint_helper(T(-2.5), FE_TOWARDZERO));
	EXPECT_EQ(T( 3.0), rint_helper(T( 3.5), FE_TOWARDZERO));
	EXPECT_EQ(T(-3.0), rint_helper(T(-3.5), FE_TOWARDZERO));
	EXPECT_EQ(+inf,    rint_helper(+inf,    FE_TOWARDZERO));
	EXPECT_EQ(-inf,    rint_helper(-inf,    FE_TOWARDZERO));
	EXPECT_TRUE(bksge::isnan(rint_helper(nan, FE_TOWARDZERO)));

	EXPECT_EQ(T( 0.0), rint_helper(T( 0.0), FE_UPWARD));
	EXPECT_EQ(T( 3.0), rint_helper(T( 2.5), FE_UPWARD));
	EXPECT_EQ(T(-2.0), rint_helper(T(-2.5), FE_UPWARD));
	EXPECT_EQ(T( 4.0), rint_helper(T( 3.5), FE_UPWARD));
	EXPECT_EQ(T(-3.0), rint_helper(T(-3.5), FE_UPWARD));
	EXPECT_EQ(+inf,    rint_helper(+inf,    FE_UPWARD));
	EXPECT_EQ(-inf,    rint_helper(-inf,    FE_UPWARD));
	EXPECT_TRUE(bksge::isnan(rint_helper(nan, FE_UPWARD)));
}

template <typename T>
void RIntTestSignedInt(void)
{
	EXPECT_EQ( 0.0, rint_helper(T( 0), FE_DOWNWARD));
	EXPECT_EQ( 2.0, rint_helper(T( 2), FE_DOWNWARD));
	EXPECT_EQ(-2.0, rint_helper(T(-2), FE_DOWNWARD));
	EXPECT_EQ( 3.0, rint_helper(T( 3), FE_DOWNWARD));
	EXPECT_EQ(-3.0, rint_helper(T(-3), FE_DOWNWARD));

	EXPECT_EQ( 0.0, rint_helper(T( 0), FE_TONEAREST));
	EXPECT_EQ( 2.0, rint_helper(T( 2), FE_TONEAREST));
	EXPECT_EQ(-2.0, rint_helper(T(-2), FE_TONEAREST));
	EXPECT_EQ( 3.0, rint_helper(T( 3), FE_TONEAREST));
	EXPECT_EQ(-3.0, rint_helper(T(-3), FE_TONEAREST));

	EXPECT_EQ( 0.0, rint_helper(T( 0), FE_TOWARDZERO));
	EXPECT_EQ( 2.0, rint_helper(T( 2), FE_TOWARDZERO));
	EXPECT_EQ(-2.0, rint_helper(T(-2), FE_TOWARDZERO));
	EXPECT_EQ( 3.0, rint_helper(T( 3), FE_TOWARDZERO));
	EXPECT_EQ(-3.0, rint_helper(T(-3), FE_TOWARDZERO));

	EXPECT_EQ( 0.0, rint_helper(T( 0), FE_UPWARD));
	EXPECT_EQ( 2.0, rint_helper(T( 2), FE_UPWARD));
	EXPECT_EQ(-2.0, rint_helper(T(-2), FE_UPWARD));
	EXPECT_EQ( 3.0, rint_helper(T( 3), FE_UPWARD));
	EXPECT_EQ(-3.0, rint_helper(T(-3), FE_UPWARD));
}

template <typename T>
void RIntTestUnsignedInt(void)
{
	EXPECT_EQ( 0.0, rint_helper(T( 0), FE_DOWNWARD));
	EXPECT_EQ( 2.0, rint_helper(T( 2), FE_DOWNWARD));
	EXPECT_EQ( 3.0, rint_helper(T( 3), FE_DOWNWARD));

	EXPECT_EQ( 0.0, rint_helper(T( 0), FE_TONEAREST));
	EXPECT_EQ( 2.0, rint_helper(T( 2), FE_TONEAREST));
	EXPECT_EQ( 3.0, rint_helper(T( 3), FE_TONEAREST));

	EXPECT_EQ( 0.0, rint_helper(T( 0), FE_TOWARDZERO));
	EXPECT_EQ( 2.0, rint_helper(T( 2), FE_TOWARDZERO));
	EXPECT_EQ( 3.0, rint_helper(T( 3), FE_TOWARDZERO));

	EXPECT_EQ( 0.0, rint_helper(T( 0), FE_UPWARD));
	EXPECT_EQ( 2.0, rint_helper(T( 2), FE_UPWARD));
	EXPECT_EQ( 3.0, rint_helper(T( 3), FE_UPWARD));
}

GTEST_TEST(CMathTest, RIntTest)
{
	RIntTestFloat<float>();
	RIntTestFloat<double>();
	RIntTestFloat<long double>();

	RIntTestSignedInt<int>();
//	RIntTestSignedInt<signed char>();
	RIntTestSignedInt<short>();
//	RIntTestSignedInt<long>();
	RIntTestSignedInt<long long>();

//	RIntTestUnsignedInt<unsigned int>();
	RIntTestUnsignedInt<unsigned char>();
//	RIntTestUnsignedInt<unsigned short>();
	RIntTestUnsignedInt<unsigned long>();
//	RIntTestUnsignedInt<unsigned long long>();
}

}	// namespace rint_test

}	// namespace bksge_cmath_test
