/**
 *	@file	unit_test_fnd_cmath_acosh.cpp
 *
 *	@brief	acosh のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/acosh.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace acosh_test
{

static_assert(bksge::is_same<float,       decltype(bksge::acosh(0.0f))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::acoshf(0.0f))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::acosh(0.0 ))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::acosh(0   ))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::acosh(0.0l))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::acoshl(0.0l))>::value, "");

template <typename T>
void AcoshTestFloat(double error)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto eps = bksge::numeric_limits<T>::epsilon();

	EXPECT_NEAR(0.000000000000000000000, (double)bksge::acosh(T(1.0)), error);
	EXPECT_NEAR(0.962423650119206894995, (double)bksge::acosh(T(1.5)), error);
	EXPECT_NEAR(1.316957896924816708625, (double)bksge::acosh(T(2.0)), error);
	EXPECT_NEAR(1.566799236972411078664, (double)bksge::acosh(T(2.5)), error);
	EXPECT_NEAR(1.762747174039086050465, (double)bksge::acosh(T(3.0)), error);
	EXPECT_NEAR(1.924847300238413789991, (double)bksge::acosh(T(3.5)), error);

	// if the argument is less than 1, FE_INVALID is raised an NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acosh(T(+1.0) - eps)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acosh(T( 0.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acosh(T(-1.0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acosh(-inf)));

	// if the argument is 1, +0 is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(0.0, bksge::acosh(T(+1.0)));

	// if the argument is +∞, +∞ is returned
	BKSGE_CONSTEXPR_EXPECT_EQ(+inf, bksge::acosh(+inf));

	// if the argument is NaN, NaN is returned
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acosh(+nan)));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acosh(-nan)));
}

template <typename T>
void AcoshTestSignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR(0.000000000000000000000, (double)bksge::acosh(T(1)), error);
	EXPECT_NEAR(1.316957896924816708625, (double)bksge::acosh(T(2)), error);
	EXPECT_NEAR(1.762747174039086050465, (double)bksge::acosh(T(3)), error);
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acosh(T( 0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acosh(T(-1))));
}

template <typename T>
void AcoshTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR double error = 0.000000000001;

	EXPECT_NEAR(0.000000000000000000000, (double)bksge::acosh(T(1)), error);
	EXPECT_NEAR(1.316957896924816708625, (double)bksge::acosh(T(2)), error);
	EXPECT_NEAR(1.762747174039086050465, (double)bksge::acosh(T(3)), error);
	BKSGE_CONSTEXPR_EXPECT_TRUE(bksge::isnan(bksge::acosh(T( 0))));
}

GTEST_TEST(CMathTest, AcoshTest)
{
	AcoshTestFloat<float>(0.000001);
	AcoshTestFloat<double>(0.000000000001);
	AcoshTestFloat<long double>(0.000000000001);

	AcoshTestSignedInt<int>();
//	AcoshTestSignedInt<signed char>();
	AcoshTestSignedInt<short>();
//	AcoshTestSignedInt<long>();
	AcoshTestSignedInt<long long>();

	AcoshTestUnsignedInt<unsigned int>();
	AcoshTestUnsignedInt<unsigned char>();
//	AcoshTestUnsignedInt<unsigned short>();
	AcoshTestUnsignedInt<unsigned long>();
//	AcoshTestUnsignedInt<unsigned long long>();
}

}	// namespace acosh_test

}	// namespace bksge_cmath_test
