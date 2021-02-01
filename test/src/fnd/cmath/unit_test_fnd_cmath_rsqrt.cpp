/**
 *	@file	unit_test_fnd_cmath_rsqrt.cpp
 *
 *	@brief	rsqrt のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/rsqrt.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace rsqrt_test
{

static_assert(bksge::is_same<float,       decltype(bksge::rsqrt(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::rsqrt(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::rsqrt(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::rsqrt(0.0l))>::value, "");

template <typename T>
void RsqrtTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = bksge::numeric_limits<T>::epsilon();

	BKSGE_CONSTEXPR double error = 0.0000001;

	BKSGE_CONSTEXPR_EXPECT_EQ  ( inf,   bksge::rsqrt(T(  0.00)));
	EXPECT_NEAR( 2.0,           (double)bksge::rsqrt(T(  0.25)), error);
	EXPECT_NEAR( 1.0,           (double)bksge::rsqrt(T(  1.00)), error);
	EXPECT_NEAR( 0.66666666666, (double)bksge::rsqrt(T(  2.25)), error);
	EXPECT_NEAR( 0.70710678118, (double)bksge::rsqrt(T(  2.00)), error);
	EXPECT_NEAR( 0.57735026918, (double)bksge::rsqrt(T(  3.00)), error);
	EXPECT_NEAR( 0.1,           (double)bksge::rsqrt(T(100.00)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::rsqrt(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::isinf  (bksge::rsqrt(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::rsqrt(T(+0.0))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::rsqrt(T(-0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::iszero (bksge::rsqrt(+inf)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::signbit(bksge::rsqrt(+inf)));

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::rsqrt(-eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::rsqrt(T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::rsqrt(-inf)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::rsqrt(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::rsqrt(-nan)));
}

template <typename T>
void RsqrtTestSignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR double error = 0.0000001;

	BKSGE_CONSTEXPR_EXPECT_EQ( inf,     bksge::rsqrt(T(  0)));
	EXPECT_NEAR( 1.0,           (double)bksge::rsqrt(T(  1)), error);
	EXPECT_NEAR( 0.70710678118, (double)bksge::rsqrt(T(  2)), error);
	EXPECT_NEAR( 0.57735026918, (double)bksge::rsqrt(T(  3)), error);
	EXPECT_NEAR( 0.1,           (double)bksge::rsqrt(T(100)), error);

	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::rsqrt(T(-1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::rsqrt(T(-2))));
}

template <typename T>
void RsqrtTestUnsignedInt(void)
{
	using R = bksge::float_promote_t<T>;
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<R>::infinity();

	BKSGE_CONSTEXPR double error = 0.0000001;

	BKSGE_CONSTEXPR_EXPECT_EQ  ( inf,   bksge::rsqrt(T(  0)));
	EXPECT_NEAR( 1.0,           (double)bksge::rsqrt(T(  1)), error);
	EXPECT_NEAR( 0.70710678118, (double)bksge::rsqrt(T(  2)), error);
	EXPECT_NEAR( 0.57735026918, (double)bksge::rsqrt(T(  3)), error);
	EXPECT_NEAR( 0.1,           (double)bksge::rsqrt(T(100)), error);
}

GTEST_TEST(CMathTest, RsqrtTest)
{
	RsqrtTestFloat<float>();
	RsqrtTestFloat<double>();
	RsqrtTestFloat<long double>();

//	RsqrtTestSignedInt<int>();
	RsqrtTestSignedInt<signed char>();
//	RsqrtTestSignedInt<short>();
	RsqrtTestSignedInt<long>();
//	RsqrtTestSignedInt<long long>();

	RsqrtTestUnsignedInt<unsigned int>();
//	RsqrtTestUnsignedInt<unsigned char>();
	RsqrtTestUnsignedInt<unsigned short>();
//	RsqrtTestUnsignedInt<unsigned long>();
	RsqrtTestUnsignedInt<unsigned long long>();
}

}	// namespace rsqrt_test

}	// namespace bksge_cmath_test
