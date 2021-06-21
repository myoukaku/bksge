/**
 *	@file	unit_test_fnd_cmath_frexp.cpp
 *
 *	@brief	frexp のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/frexp.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace frexp_test
{

static_assert(bksge::is_same<float,       decltype(bksge::frexp(0.0f,  nullptr))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::frexpf(0.0f, nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::frexp(0.0,   nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::frexp(0,     nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::frexp(0.0l,  nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::frexpl(0.0l, nullptr))>::value, "");

template <typename T>
void FrexpTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	{
		int exp;
		auto x = bksge::frexp(T(0.125), &exp);
		EXPECT_EQ(T(0.5), x);
		EXPECT_EQ(-2,     exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(0.25), &exp);
		EXPECT_EQ(T(0.5), x);
		EXPECT_EQ(-1,     exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(0.5), &exp);
		EXPECT_EQ(T(0.5), x);
		EXPECT_EQ(0,      exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(1.0), &exp);
		EXPECT_EQ(T(0.5), x);
		EXPECT_EQ(1,      exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(1.5), &exp);
		EXPECT_EQ(T(0.75), x);
		EXPECT_EQ(1,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(2.0), &exp);
		EXPECT_EQ(T(0.5), x);
		EXPECT_EQ(2,      exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(2.5), &exp);
		EXPECT_EQ(T(0.625), x);
		EXPECT_EQ(2,        exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(3.0), &exp);
		EXPECT_EQ(T(0.75), x);
		EXPECT_EQ(2,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(4.0), &exp);
		EXPECT_EQ(T(0.5), x);
		EXPECT_EQ(3,      exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(5.0), &exp);
		EXPECT_EQ(T(0.625), x);
		EXPECT_EQ(3,        exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-0.125), &exp);
		EXPECT_EQ(T(-0.5), x);
		EXPECT_EQ(-2,      exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-0.5), &exp);
		EXPECT_EQ(T(-0.5), x);
		EXPECT_EQ(0,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-1.0), &exp);
		EXPECT_EQ(T(-0.5), x);
		EXPECT_EQ(1,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-2.0), &exp);
		EXPECT_EQ(T(-0.5), x);
		EXPECT_EQ(2,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-4.0), &exp);
		EXPECT_EQ(T(-0.5), x);
		EXPECT_EQ(3,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(+0.0), &exp);
		EXPECT_EQ(T(+0.0), x);
		EXPECT_EQ(0,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-0.0), &exp);
		EXPECT_EQ(T(-0.0), x);
		EXPECT_EQ(0,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(+inf), &exp);
		EXPECT_EQ(T(+inf), x);
		//EXPECT_EQ(0,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-inf), &exp);
		EXPECT_EQ(T(-inf), x);
		//EXPECT_EQ(0,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(+nan), &exp);
		EXPECT_TRUE(bksge::isnan(x));
		//EXPECT_EQ(0,       exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-nan), &exp);
		EXPECT_TRUE(bksge::isnan(x));
		//EXPECT_EQ(0,       exp);
	}
}

template <typename T>
void FrexpTestSignedInt(void)
{
	{
		int exp;
		auto x = bksge::frexp(T(1), &exp);
		EXPECT_EQ(0.5, x);
		EXPECT_EQ(1,   exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(2), &exp);
		EXPECT_EQ(0.5, x);
		EXPECT_EQ(2,   exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(3), &exp);
		EXPECT_EQ(0.75, x);
		EXPECT_EQ(2,    exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(4), &exp);
		EXPECT_EQ(0.5, x);
		EXPECT_EQ(3,   exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(5), &exp);
		EXPECT_EQ(0.625, x);
		EXPECT_EQ(3,     exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-1), &exp);
		EXPECT_EQ(-0.5, x);
		EXPECT_EQ(1,    exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-2), &exp);
		EXPECT_EQ(-0.5, x);
		EXPECT_EQ(2,    exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(-4), &exp);
		EXPECT_EQ(-0.5, x);
		EXPECT_EQ(3,    exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(0), &exp);
		EXPECT_EQ(0.0, x);
		EXPECT_EQ(0,   exp);
	}
}

template <typename T>
void FrexpTestUnsignedInt(void)
{
	{
		int exp;
		auto x = bksge::frexp(T(1), &exp);
		EXPECT_EQ(0.5, x);
		EXPECT_EQ(1,   exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(2), &exp);
		EXPECT_EQ(0.5, x);
		EXPECT_EQ(2,   exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(3), &exp);
		EXPECT_EQ(0.75, x);
		EXPECT_EQ(2,    exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(4), &exp);
		EXPECT_EQ(0.5, x);
		EXPECT_EQ(3,   exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(5), &exp);
		EXPECT_EQ(0.625, x);
		EXPECT_EQ(3,     exp);
	}
	{
		int exp;
		auto x = bksge::frexp(T(0), &exp);
		EXPECT_EQ(0.0, x);
		EXPECT_EQ(0,   exp);
	}
}

GTEST_TEST(CMathTest, FrexpTest)
{
	FrexpTestFloat<float>();
	FrexpTestFloat<double>();
	FrexpTestFloat<long double>();

//	FrexpTestSignedInt<int>();
	FrexpTestSignedInt<signed char>();
//	FrexpTestSignedInt<short>();
	FrexpTestSignedInt<long>();
//	FrexpTestSignedInt<long long>();

	FrexpTestUnsignedInt<unsigned int>();
//	FrexpTestUnsignedInt<unsigned char>();
	FrexpTestUnsignedInt<unsigned short>();
//	FrexpTestUnsignedInt<unsigned long>();
	FrexpTestUnsignedInt<unsigned long long>();
}

}	// namespace frexp_test

}	// namespace bksge_cmath_test
