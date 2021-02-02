/**
 *	@file	unit_test_fnd_cmath_modf.cpp
 *
 *	@brief	modf のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/modf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace floor_test
{

static_assert(bksge::is_same<float,       decltype(bksge::modf(0.0f,  nullptr))>::value, "");
static_assert(bksge::is_same<float,       decltype(bksge::modff(0.0f, nullptr))>::value, "");
static_assert(bksge::is_same<double,      decltype(bksge::modf(0.0,   nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::modf(0.0l,  nullptr))>::value, "");
static_assert(bksge::is_same<long double, decltype(bksge::modfl(0.0l, nullptr))>::value, "");

template <typename T>
void ModfTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	{
		T i;
		auto x = bksge::modf(T(123.5), &i);
		EXPECT_EQ(T(123.0), i);
		EXPECT_EQ(T(  0.5), x);
	}
	{
		T i;
		auto x = bksge::modf(T(-1.25), &i);
		EXPECT_EQ(T(-1.0),  i);
		EXPECT_EQ(T(-0.25), x);
	}
	{
		T i;
		auto x = bksge::modf(T(+0.0), &i);
		EXPECT_EQ(T(+0.0), i);
		EXPECT_EQ(T(+0.0), x);
	}
	{
		T i;
		auto x = bksge::modf(T(-0.0), &i);
		EXPECT_EQ(T(-0.0), i);
		EXPECT_EQ(T(-0.0), x);
	}
	{
		T i;
		auto x = bksge::modf(T(+inf), &i);
		EXPECT_EQ(T(+inf), i);
		EXPECT_EQ(T(+0.0), x);
	}
	{
		T i;
		auto x = bksge::modf(T(-inf), &i);
		EXPECT_EQ(T(-inf), i);
		EXPECT_EQ(T(-0.0), x);
	}
	{
		T i;
		auto x = bksge::modf(T(+nan), &i);
		EXPECT_TRUE(bksge::isnan(i));
		EXPECT_TRUE(bksge::isnan(x));
	}
	{
		T i;
		auto x = bksge::modf(T(-nan), &i);
		EXPECT_TRUE(bksge::isnan(i));
		EXPECT_TRUE(bksge::isnan(x));
	}
}

GTEST_TEST(CMathTest, ModfTest)
{
	ModfTestFloat<float>();
	ModfTestFloat<double>();
	ModfTestFloat<long double>();
}

}	// namespace floor_test

}	// namespace bksge_cmath_test
