/**
 *	@file	unit_test_fnd_complex_atanh.cpp
 *
 *	@brief	atanh(complex<T> const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/complex/complex.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/constants.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace bksge_complex_test
{

namespace atanh_test
{

template <typename T>
void AtanhTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	// atanh(conj(z)) == conj(atanh(z))
	// atanh(-z) == -atanh(z)
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::atanh(bksge::conj(z)), bksge::conj(bksge::atanh(z)));
		EXPECT_EQ(bksge::atanh(-z), -bksge::atanh(z));
	}
	{
		auto z = complex(T(-2.0), T(3.0));
		EXPECT_EQ(bksge::atanh(bksge::conj(z)), bksge::conj(bksge::atanh(z)));
		EXPECT_EQ(bksge::atanh(-z), -bksge::atanh(z));
	}
	{
		auto z = complex(T(5.0), T(-4.0));
		EXPECT_EQ(bksge::atanh(bksge::conj(z)), bksge::conj(bksge::atanh(z)));
		EXPECT_EQ(bksge::atanh(-z), -bksge::atanh(z));
	}
	{
		auto z = complex(T(-6.0), T(-5.0));
		EXPECT_EQ(bksge::atanh(bksge::conj(z)), bksge::conj(bksge::atanh(z)));
		EXPECT_EQ(bksge::atanh(-z), -bksge::atanh(z));
	}
	{
		auto z = complex(min, min);
		EXPECT_TRUE(IsEqual(bksge::atanh(bksge::conj(z)), bksge::conj(bksge::atanh(z))));
		EXPECT_TRUE(IsEqual(bksge::atanh(-z), -bksge::atanh(z)));
	}
	{
		auto z = complex(min, max);
		EXPECT_TRUE(IsEqual(bksge::atanh(bksge::conj(z)), bksge::conj(bksge::atanh(z))));
		EXPECT_TRUE(IsEqual(bksge::atanh(-z), -bksge::atanh(z)));
	}
	{
		auto z = complex(max, min);
		EXPECT_TRUE(IsEqual(bksge::atanh(bksge::conj(z)), bksge::conj(bksge::atanh(z))));
		EXPECT_TRUE(IsEqual(bksge::atanh(-z), -bksge::atanh(z)));
	}
	{
		auto z = complex(max, max);
		EXPECT_TRUE(IsEqual(bksge::atanh(bksge::conj(z)), bksge::conj(bksge::atanh(z))));
		EXPECT_TRUE(IsEqual(bksge::atanh(-z), -bksge::atanh(z)));
	}

#if defined(BKSGE_IEC_559_COMPLEX)
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto pi = bksge::pi<T>();

	// If z is (+0,+0), the result is (+0,+0)
	EXPECT_EQ(complex(T(+0.0), T(+0.0)), bksge::atanh(complex(T(+0.0), T(+0.0))));

	// If z is (+0,NaN), the result is (+0,NaN)
	EXPECT_TRUE( bksge::iszero( bksge::atanh(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE(!bksge::signbit(bksge::atanh(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE( bksge::isnan  (bksge::atanh(complex(T(+0.0), nan)).imag()));

	// If z is (+1,+0), the result is (+∞,+0) and FE_DIVBYZERO is raised
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::atanh(complex(T(+1.0), T(+0.0))));

	// If z is (x,+∞) (for any finite positive x), the result is (+0,π/2)
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::atanh(complex(T(+0.0), +inf)));
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::atanh(complex(T(+1.0), +inf)));
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::atanh(complex(T(+2.0), +inf)));
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::atanh(complex(max, +inf)));

	// If z is (x,NaN) (for any finite nonzero x), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(min, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(min, nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(T(-2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(T(-2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(T(-1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(T(-1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(T(+1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(T(+1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(T(+2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(T(+2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(max, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(max, nan)).imag()));

	// If z is (+∞,y) (for any finite positive y), the result is (+0,π/2)
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::atanh(complex(+inf, T(+0.0))));
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::atanh(complex(+inf, T(+1.0))));
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::atanh(complex(+inf, T(+2.0))));
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::atanh(complex(+inf, max)));

	// If z is (+∞,+∞), the result is (+0,π/2)
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::atanh(complex(+inf, +inf)));

	// If z is (+∞,NaN), the result is (+0,NaN)
	EXPECT_TRUE( bksge::iszero (bksge::atanh(complex(+inf, nan)).real()));
	EXPECT_TRUE(!bksge::signbit(bksge::atanh(complex(+inf, nan)).real()));
	EXPECT_TRUE( bksge::isnan  (bksge::atanh(complex(+inf, nan)).imag()));

	// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, min)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, min)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(-2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(-2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(-1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(-1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(-0.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(-0.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(+0.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(+0.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(+1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(+1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(+2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, T(+2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, max)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, max)).imag()));

	// If z is (NaN,+∞), the result is (±0,π/2) (the sign of the real part is unspecified)
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::atanh(complex(nan, +inf)));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::atanh(complex(nan, nan)).imag()));
#endif
}

GTEST_TEST(ComplexTest, AtanhTest)
{
	AtanhTest<float>();
	AtanhTest<double>();
	AtanhTest<long double>();
}

}	// namespace atanh_test

}	// namespace bksge_complex_test
