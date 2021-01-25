/**
 *	@file	unit_test_fnd_complex_sqrt.cpp
 *
 *	@brief	sqrt(complex<T> const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/complex/complex.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_complex_test
{

namespace sqrt_test
{

template <typename T>
void SqrtTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	// sqrt(conj(z)) == conj(sqrt(z))
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::sqrt(bksge::conj(z)), bksge::conj(bksge::sqrt(z)));
	}
	{
		auto z = complex(T(2.0), T(3.0));
		EXPECT_EQ(bksge::sqrt(bksge::conj(z)), bksge::conj(bksge::sqrt(z)));
	}
	{
		auto z = complex(T(-3.0), T(2.0));
		EXPECT_EQ(bksge::sqrt(bksge::conj(z)), bksge::conj(bksge::sqrt(z)));
	}
	{
		auto z = complex(T(5.0), T(-4.0));
		EXPECT_EQ(bksge::sqrt(bksge::conj(z)), bksge::conj(bksge::sqrt(z)));
	}
	{
		auto z = complex(T(-2.0), T(-3.0));
		EXPECT_EQ(bksge::sqrt(bksge::conj(z)), bksge::conj(bksge::sqrt(z)));
	}
	{
		auto z = complex(min, min);
		EXPECT_EQ(bksge::sqrt(bksge::conj(z)), bksge::conj(bksge::sqrt(z)));
	}
	{
		auto z = complex(min, max);
		EXPECT_EQ(bksge::sqrt(bksge::conj(z)), bksge::conj(bksge::sqrt(z)));
	}
	{
		auto z = complex(max, min);
		EXPECT_EQ(bksge::sqrt(bksge::conj(z)), bksge::conj(bksge::sqrt(z)));
	}
	{
		auto z = complex(max, max);
		EXPECT_EQ(bksge::sqrt(bksge::conj(z)), bksge::conj(bksge::sqrt(z)));
	}

#if defined(BKSGE_IEC_559_COMPLEX)
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	// If z is (±0,+0), the result is (+0,+0)
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::sqrt(complex(T(-0.0), T(+0.0))));
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::sqrt(complex(T(+0.0), T(+0.0))));

	// If z is (x,+∞), the result is (+∞,+∞) even if x is NaN
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(min, +inf)));
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(T(-2.0), +inf)));
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(T(-1.0), +inf)));
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(T(-0.0), +inf)));
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(T(+0.0), +inf)));
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(T(+1.0), +inf)));
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(T(+2.0), +inf)));
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(max, +inf)));
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(-inf, +inf)));
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(+inf, +inf)));
	EXPECT_EQ(complex(+inf, +inf), bksge::sqrt(complex(nan, +inf)));

	// If z is (x,NaN), the result is (NaN,NaN) (unless x is ±∞) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(min, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(min, nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(-2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(-2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(-1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(-1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(-0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(-0.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(+0.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(+1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(+1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(+2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(T(+2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(max, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(max, nan)).imag()));

	// If z is (-∞,y), the result is (+0,+∞) for finite positive y
	EXPECT_EQ(complex(T(0.0), +inf), bksge::sqrt(complex(-inf, T(+0.0))));
	EXPECT_EQ(complex(T(0.0), +inf), bksge::sqrt(complex(-inf, T(+1.0))));
	EXPECT_EQ(complex(T(0.0), +inf), bksge::sqrt(complex(-inf, T(+2.0))));
	EXPECT_EQ(complex(T(0.0), +inf), bksge::sqrt(complex(-inf, max)));

	// If z is (+∞,y), the result is (+∞,+0) for finite positive y
	EXPECT_EQ(complex(+inf, T(0.0)), bksge::sqrt(complex(+inf, T(+0.0))));
	EXPECT_EQ(complex(+inf, T(0.0)), bksge::sqrt(complex(+inf, T(+1.0))));
	EXPECT_EQ(complex(+inf, T(0.0)), bksge::sqrt(complex(+inf, T(+2.0))));
	EXPECT_EQ(complex(+inf, T(0.0)), bksge::sqrt(complex(+inf, max)));

	// If z is (-∞,NaN), the result is (NaN,∞) (sign of imaginary part unspecified)
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(-inf, nan)).real()));
	EXPECT_TRUE(bksge::isinf(bksge::sqrt(complex(-inf, nan)).imag()));

	// If z is (+∞,NaN), the result is (+∞,NaN)
	EXPECT_TRUE(bksge::isinf(bksge::sqrt(complex(+inf, nan)).real()));
	EXPECT_TRUE(!bksge::signbit(bksge::sqrt(complex(+inf, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(+inf, nan)).imag()));

	// If z is (NaN,y), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, min)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, min)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(-2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(-2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(-1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(-1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(-0.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(-0.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(+0.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(+0.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(+1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(+1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(+2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, T(+2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, max)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, max)).imag()));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sqrt(complex(nan, nan)).imag()));
#endif
}

GTEST_TEST(ComplexTest, SqrtTest)
{
	SqrtTest<float>();
	SqrtTest<double>();
	SqrtTest<long double>();
}

}	// namespace sqrt_test

}	// namespace bksge_complex_test
