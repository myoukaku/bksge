/**
 *	@file	unit_test_fnd_cmath_almost_equal.cpp
 *
 *	@brief	almost_equal のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/cmath/almost_equal.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_cmath_test
{

namespace almost_equal_test
{

template <typename T>
void AlmostEqualTestFloat(void)
{
	BKSGE_CONSTEXPR auto nan    = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf    = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto max    = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min    = bksge::numeric_limits<T>::min();
	BKSGE_CONSTEXPR auto lowest = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto eps    = bksge::numeric_limits<T>::epsilon();

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0.0) + (eps * T(0)), T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0.0) + (eps * T(1)), T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(0.0) + (eps * T(2)), T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0.0) - (eps * T(0)), T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0.0) - (eps * T(1)), T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(0.0) - (eps * T(2)), T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0.0),              T(0.0) + (eps * T(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0.0),              T(0.0) + (eps * T(1))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(0.0),              T(0.0) + (eps * T(2))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0.0),              T(0.0) - (eps * T(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0.0),              T(0.0) - (eps * T(1))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(0.0),              T(0.0) - (eps * T(2))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(1.0) + (eps * T(0)), T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(1.0) + (eps * T(1)), T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1.0) + (eps * T(2)), T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(1.0) - (eps * T(0)), T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(1.0) - (eps * T(1)), T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1.0) - (eps * T(2)), T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(1.0),              T(1.0) + (eps * T(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(1.0),              T(1.0) + (eps * T(1))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1.0),              T(1.0) + (eps * T(2))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(1.0),              T(1.0) - (eps * T(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(1.0),              T(1.0) - (eps * T(1))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1.0),              T(1.0) - (eps * T(2))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-1.0) + (eps * T(0)), T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-1.0) + (eps * T(1)), T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-1.0) + (eps * T(2)), T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-1.0) - (eps * T(0)), T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-1.0) - (eps * T(1)), T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-1.0) - (eps * T(2)), T(-1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-1.0),              T(-1.0) + (eps * T(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-1.0),              T(-1.0) + (eps * T(1))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-1.0),              T(-1.0) + (eps * T(2))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-1.0),              T(-1.0) - (eps * T(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-1.0),              T(-1.0) - (eps * T(1))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-1.0),              T(-1.0) - (eps * T(2))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0) + (eps * T(0)), T(2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0) + (eps * T(1)), T(2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0) + (eps * T(2)), T(2.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(2.0) + (eps * T(3)), T(2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0) - (eps * T(0)), T(2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0) - (eps * T(1)), T(2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0) - (eps * T(2)), T(2.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(2.0) - (eps * T(3)), T(2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0),              T(2.0) + (eps * T(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0),              T(2.0) + (eps * T(1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0),              T(2.0) + (eps * T(2))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(2.0),              T(2.0) + (eps * T(3))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0),              T(2.0) - (eps * T(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0),              T(2.0) - (eps * T(1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(2.0),              T(2.0) - (eps * T(2))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(2.0),              T(2.0) - (eps * T(3))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0) + (eps * T(0)), T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0) + (eps * T(1)), T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0) + (eps * T(2)), T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-2.0) + (eps * T(3)), T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0) - (eps * T(0)), T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0) - (eps * T(1)), T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0) - (eps * T(2)), T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-2.0) - (eps * T(3)), T(-2.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0),              T(-2.0) + (eps * T(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0),              T(-2.0) + (eps * T(1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0),              T(-2.0) + (eps * T(2))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-2.0),              T(-2.0) + (eps * T(3))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0),              T(-2.0) - (eps * T(0))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0),              T(-2.0) - (eps * T(1))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-2.0),              T(-2.0) - (eps * T(2))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-2.0),              T(-2.0) - (eps * T(3))));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(10.0) + (eps * T(11)), T(10.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(10.0) + (eps * T(12)), T(10.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(10.0) - (eps * T(11)), T(10.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(10.0) - (eps * T(12)), T(10.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(10.0),               T(10.0) + (eps * T(11))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(10.0),               T(10.0) + (eps * T(12))));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(10.0),               T(10.0) - (eps * T(11))));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(10.0),               T(10.0) - (eps * T(12))));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(nan, T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(nan, T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(nan, max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(nan, min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(nan, lowest));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(nan,  nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(nan, -nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(nan,  inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(nan, -inf));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-nan, T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-nan, T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-nan, max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-nan, min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-nan, lowest));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-nan,  nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-nan, -nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-nan,  inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-nan, -inf));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(inf, T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(inf, T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(inf, max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(inf, min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(inf, lowest));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(inf,  nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(inf, -nan));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(inf,  inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(inf, -inf));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-inf, T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-inf, T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-inf, max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-inf, min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-inf, lowest));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-inf,  nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-inf, -nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(-inf,  inf));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(-inf, -inf));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(max, max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, min));
	                EXPECT_FALSE(bksge::almost_equal(max, lowest));		// TODO 計算途中でinfが発生しないようにして、constexprにする
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max,  nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, -nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max,  inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, -inf));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(min, T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, T(1.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, max));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(min, min));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, lowest));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min,  nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, -nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min,  inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, -inf));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(lowest, T(0.0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(lowest, T(1.0)));
	                EXPECT_FALSE(bksge::almost_equal(lowest, max));		// TODO 計算途中でinfが発生しないようにして、constexprにする
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(lowest, min));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(lowest, lowest));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(lowest,  nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(lowest, -nan));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(lowest,  inf));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(lowest, -inf));
}

template <typename T>
void AlmostEqualTestSignedInt(void)
{
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::min();

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0), T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(0), T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(0), T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(0), max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(0), min));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1), T(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(1), T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1), T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1), max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1), min));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-1), T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-1), T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(-1), T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-1), max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(-1), min));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, T(-1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(max, max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, min));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, T(-1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, max));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(min, min));
}

template <typename T>
void AlmostEqualTestUnsignedInt(void)
{
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::min();

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0), T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(0), T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(0), max));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(0), min));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1), T(0)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(T(1), T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1), max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(T(1), min));

	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, T(1)));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(max, max));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(max, min));

	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(min, T(0)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, T(1)));
	BKSGE_CONSTEXPR_EXPECT_FALSE(bksge::almost_equal(min, max));
	BKSGE_CONSTEXPR_EXPECT_TRUE (bksge::almost_equal(min, min));
}

GTEST_TEST(CMathTest, AlmostEqualTest)
{
	AlmostEqualTestFloat<float>();
	AlmostEqualTestFloat<double>();
	AlmostEqualTestFloat<long double>();

	AlmostEqualTestSignedInt<int>();
	AlmostEqualTestSignedInt<signed char>();
//	AlmostEqualTestSignedInt<short>();
	AlmostEqualTestSignedInt<long>();
//	AlmostEqualTestSignedInt<long long>();

	AlmostEqualTestUnsignedInt<unsigned int>();
//	AlmostEqualTestUnsignedInt<unsigned char>();
	AlmostEqualTestUnsignedInt<unsigned short>();
//	AlmostEqualTestUnsignedInt<unsigned long>();
	AlmostEqualTestUnsignedInt<unsigned long long>();
}

}	// namespace almost_equal_test

}	// namespace bksge_cmath_test
