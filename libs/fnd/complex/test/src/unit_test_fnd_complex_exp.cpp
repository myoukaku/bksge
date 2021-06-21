/**
 *	@file	unit_test_fnd_complex_exp.cpp
 *
 *	@brief	exp(complex<T> const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/complex/complex.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/cmath/signbit.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_complex_test
{

namespace exp_test
{

template <typename T>
void ExpTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	// exp(conj(z)) == conj(exp(z))
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::exp(bksge::conj(z)), bksge::conj(bksge::exp(z)));
	}
	{
		auto z = complex(T(1.0), T(2.0));
		EXPECT_EQ(bksge::exp(bksge::conj(z)), bksge::conj(bksge::exp(z)));
	}
	{
		auto z = complex(T(-2.0), T(3.0));
		EXPECT_EQ(bksge::exp(bksge::conj(z)), bksge::conj(bksge::exp(z)));
	}
	{
		auto z = complex(T(4.0), T(-3.0));
		EXPECT_EQ(bksge::exp(bksge::conj(z)), bksge::conj(bksge::exp(z)));
	}
	{
		auto z = complex(T(-5.0), T(-4.0));
		EXPECT_EQ(bksge::exp(bksge::conj(z)), bksge::conj(bksge::exp(z)));
	}
	{
		auto z = complex(min, min);
		EXPECT_EQ(bksge::exp(bksge::conj(z)), bksge::conj(bksge::exp(z)));
	}
	{
		auto z = complex(min, max);
		EXPECT_EQ(bksge::exp(bksge::conj(z)), bksge::conj(bksge::exp(z)));
	}
	{
		auto z = complex(max, min);
		EXPECT_EQ(bksge::exp(bksge::conj(z)), bksge::conj(bksge::exp(z)));
	}
	{
		auto z = complex(max, max);
		EXPECT_EQ(bksge::exp(bksge::conj(z)), bksge::conj(bksge::exp(z)));
	}

#if defined(BKSGE_IEC_559_COMPLEX)
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	// If z is (±0,+0), the result is (1,+0)
	EXPECT_EQ(complex(T(1.0), T(+0.0)), bksge::exp(complex(T(-0.0), T(+0.0))));
	EXPECT_EQ(complex(T(1.0), T(+0.0)), bksge::exp(complex(T(+0.0), T(+0.0))));

	// If z is (x,+∞) (for any finite x), the result is (NaN,NaN) and FE_INVALID is raised.
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(min, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(min, +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-2.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-2.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-1.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-1.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-0.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-0.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+0.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+0.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+1.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+1.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+2.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+2.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(max, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(max, +inf)).imag()));

	// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised.
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(min, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(min, nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(-0.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+0.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(T(+2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(max, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(max, nan)).imag()));

	// If z is (+∞,+0), the result is (+∞,+0)
	EXPECT_EQ(complex(inf, T(+0.0)), bksge::exp(complex(inf, T(+0.0))));

	// If z is (-∞,y) (for any finite y), the result is +0cis(y)
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::exp(complex(-inf, min)));
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::exp(complex(-inf, T(-2.0))));
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::exp(complex(-inf, T(-1.0))));
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::exp(complex(-inf, T(-0.0))));
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::exp(complex(-inf, T(+0.0))));
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::exp(complex(-inf, T(+1.0))));
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::exp(complex(-inf, T(+2.0))));
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::exp(complex(-inf, max)));

	// If z is (+∞,y) (for any finite nonzero y), the result is +∞cis(y)
	EXPECT_EQ(complex(+inf, +inf), bksge::exp(complex(+inf, T(+1.0))));
	EXPECT_EQ(complex(-inf, +inf), bksge::exp(complex(+inf, T(+2.0))));
	EXPECT_EQ(complex(+inf, -inf), bksge::exp(complex(+inf, T(-1.0))));
	EXPECT_EQ(complex(-inf, -inf), bksge::exp(complex(+inf, T(-2.0))));

	// If z is (-∞,+∞), the result is (±0,±0) (signs are unspecified)
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::exp(complex(-inf, +inf)));

	// If z is (+∞,+∞), the result is (±∞,NaN) and FE_INVALID is raised (the sign of the real part is unspecified)
	EXPECT_TRUE(bksge::isinf(bksge::exp(complex(+inf, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(+inf, +inf)).imag()));

	// If z is (-∞,NaN), the result is (±0,±0) (signs are unspecified)
	EXPECT_EQ(complex(T(0.0), T(0.0)), bksge::exp(complex(-inf, nan)));

	// If z is (+∞,NaN), the result is (±∞,NaN) (the sign of the real part is unspecified)
	EXPECT_TRUE(bksge::isinf(bksge::exp(complex(+inf, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(+inf, nan)).imag()));

	// If z is (NaN,+0), the result is (NaN,+0)
	EXPECT_TRUE(bksge::isnan (bksge::exp(complex(nan, T(+0.0))).real()));
	EXPECT_TRUE(bksge::iszero(bksge::exp(complex(nan, T(+0.0))).imag()));

	// If z is (NaN,y) (for any nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, min)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, min)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, T(-2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, T(-2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, T(-1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, T(-1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, T(+1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, T(+1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, T(+2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, T(+2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, max)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, max)).imag()));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::exp(complex(nan, nan)).imag()));
#endif
}

GTEST_TEST(ComplexTest, ExpTest)
{
	ExpTest<float>();
	ExpTest<double>();
	ExpTest<long double>();
}

}	// namespace exp_test

}	// namespace bksge_complex_test
