/**
 *	@file	unit_test_fnd_complex_log.cpp
 *
 *	@brief	log(complex<T> const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/complex/complex.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_complex_test
{

namespace log_test
{

template <typename T>
void LogTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	// log(conj(z)) == conj(log(z))
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::log(bksge::conj(z)), bksge::conj(bksge::log(z)));
	}
	{
		auto z = complex(T(-2.0), T(3.0));
		EXPECT_EQ(bksge::log(bksge::conj(z)), bksge::conj(bksge::log(z)));
	}
	{
		auto z = complex(T(4.0), T(-2.0));
		EXPECT_EQ(bksge::log(bksge::conj(z)), bksge::conj(bksge::log(z)));
	}
	{
		auto z = complex(T(-5.0), T(-4.0));
		EXPECT_EQ(bksge::log(bksge::conj(z)), bksge::conj(bksge::log(z)));
	}
	{
		auto z = complex(min, min);
		EXPECT_EQ(bksge::log(bksge::conj(z)), bksge::conj(bksge::log(z)));
	}
	{
		auto z = complex(min, max);
		EXPECT_EQ(bksge::log(bksge::conj(z)), bksge::conj(bksge::log(z)));
	}
	{
		auto z = complex(max, min);
		EXPECT_EQ(bksge::log(bksge::conj(z)), bksge::conj(bksge::log(z)));
	}
	{
		auto z = complex(max, max);
		EXPECT_EQ(bksge::log(bksge::conj(z)), bksge::conj(bksge::log(z)));
	}

#if defined(BKSGE_IEC_559_COMPLEX)
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto pi = bksge::pi_t<T>();

	// If z is (-0,+0), the result is (-∞,π) and FE_DIVBYZERO is raised
	EXPECT_EQ(complex(-inf, pi), bksge::log(complex(T(-0.0), T(+0.0))));

	// If z is (+0,+0), the result is (-∞,+0) and FE_DIVBYZERO is raised
	EXPECT_EQ(complex(-inf, T(0)), bksge::log(complex(T(+0.0), T(+0.0))));

	// If z is (x,+∞) (for any finite x), the result is (+∞,π/2)
	EXPECT_EQ(complex(inf, pi/2), bksge::log(complex(min, inf)));
	EXPECT_EQ(complex(inf, pi/2), bksge::log(complex(T(-2.0), inf)));
	EXPECT_EQ(complex(inf, pi/2), bksge::log(complex(T(-1.0), inf)));
	EXPECT_EQ(complex(inf, pi/2), bksge::log(complex(T(-0.0), inf)));
	EXPECT_EQ(complex(inf, pi/2), bksge::log(complex(T(+0.0), inf)));
	EXPECT_EQ(complex(inf, pi/2), bksge::log(complex(T(+1.0), inf)));
	EXPECT_EQ(complex(inf, pi/2), bksge::log(complex(T(+2.0), inf)));
	EXPECT_EQ(complex(inf, pi/2), bksge::log(complex(max, inf)));

	// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(min, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(min, nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(-2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(-2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(-1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(-1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(-0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(-0.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(+0.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(+1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(+1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(+2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(T(+2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(max, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(max, nan)).imag()));

	// If z is (-∞,y) (for any finite positive y), the result is (+∞,π)
	EXPECT_EQ(complex(inf, pi), bksge::log(complex(-inf, T(+0.0))));
	EXPECT_EQ(complex(inf, pi), bksge::log(complex(-inf, T(+1.0))));
	EXPECT_EQ(complex(inf, pi), bksge::log(complex(-inf, T(+2.0))));
	EXPECT_EQ(complex(inf, pi), bksge::log(complex(-inf, max)));

	// If z is (+∞,y) (for any finite positive y), the result is (+∞,+0)
	EXPECT_EQ(complex(inf, T(0)), bksge::log(complex(+inf, T(+0.0))));
	EXPECT_EQ(complex(inf, T(0)), bksge::log(complex(+inf, T(+1.0))));
	EXPECT_EQ(complex(inf, T(0)), bksge::log(complex(+inf, T(+2.0))));
	EXPECT_EQ(complex(inf, T(0)), bksge::log(complex(+inf, max)));

	// If z is (-∞,+∞), the result is (+∞,3π/4)
	EXPECT_EQ(complex(+inf, pi*3/4), bksge::log(complex(-inf, +inf)));

	// If z is (+∞,+∞), the result is (+∞,π/4)
	EXPECT_EQ(complex(+inf, pi/4), bksge::log(complex(+inf, +inf)));

	// If z is (±∞,NaN), the result is (+∞,NaN)
	EXPECT_TRUE( bksge::isinf  (bksge::log(complex(+inf, nan)).real()));
	EXPECT_TRUE(!bksge::signbit(bksge::log(complex(+inf, nan)).real()));
	EXPECT_TRUE( bksge::isnan  (bksge::log(complex(+inf, nan)).imag()));
	EXPECT_TRUE( bksge::isinf  (bksge::log(complex(-inf, nan)).real()));
	EXPECT_TRUE(!bksge::signbit(bksge::log(complex(-inf, nan)).real()));
	EXPECT_TRUE( bksge::isnan  (bksge::log(complex(-inf, nan)).imag()));

	// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, min)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, min)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(-2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(-2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(-1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(-1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(-0.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(-0.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(+0.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(+0.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(+1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(+1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(+2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, T(+2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, max)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, max)).imag()));

	// If z is (NaN,+∞), the result is (+∞,NaN)
	EXPECT_TRUE( bksge::isinf  (bksge::log(complex(nan, +inf)).real()));
	EXPECT_TRUE(!bksge::signbit(bksge::log(complex(nan, +inf)).real()));
	EXPECT_TRUE( bksge::isnan  (bksge::log(complex(nan, +inf)).imag()));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::log(complex(nan, nan)).imag()));
#endif
}

GTEST_TEST(ComplexTest, LogTest)
{
	LogTest<float>();
	LogTest<double>();
	LogTest<long double>();
}

}	// namespace log_test

}	// namespace bksge_complex_test
