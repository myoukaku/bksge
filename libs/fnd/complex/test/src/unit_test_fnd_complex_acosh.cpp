/**
 *	@file	unit_test_fnd_complex_acosh.cpp
 *
 *	@brief	acosh(complex<T> const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/complex/complex.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/numbers.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace bksge_complex_test
{

namespace acosh_test
{

template <typename T>
void AcoshTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	// acosh(conj(z)) == conj(acosh(z))
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::acosh(bksge::conj(z)), bksge::conj(bksge::acosh(z)));
	}
	{
		auto z = complex(T(-2.0), T(3.0));
		EXPECT_EQ(bksge::acosh(bksge::conj(z)), bksge::conj(bksge::acosh(z)));
	}
	{
		auto z = complex(T(5.0), T(-4.0));
		EXPECT_EQ(bksge::acosh(bksge::conj(z)), bksge::conj(bksge::acosh(z)));
	}
	{
		auto z = complex(T(-6.0), T(-5.0));
		EXPECT_EQ(bksge::acosh(bksge::conj(z)), bksge::conj(bksge::acosh(z)));
	}
	{
		auto z = complex(min, min);
		EXPECT_EQ(bksge::acosh(bksge::conj(z)), bksge::conj(bksge::acosh(z)));
	}
	{
		auto z = complex(min, max);
		EXPECT_EQ(bksge::acosh(bksge::conj(z)), bksge::conj(bksge::acosh(z)));
	}
	{
		auto z = complex(max, min);
		EXPECT_EQ(bksge::acosh(bksge::conj(z)), bksge::conj(bksge::acosh(z)));
	}
	{
		auto z = complex(max, max);
		EXPECT_EQ(bksge::acosh(bksge::conj(z)), bksge::conj(bksge::acosh(z)));
	}

#if defined(BKSGE_IEC_559_COMPLEX)
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto pi = bksge::pi_t<T>();

	// If z is (±0,+0), the result is (+0,π/2)
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::acosh(complex(T(-0.0), T(+0.0))));
	EXPECT_EQ(complex(T(+0.0), pi/2), bksge::acosh(complex(T(+0.0), T(+0.0))));

	// If z is (x,+∞) (for any finite x), the result is (+∞,π/2)
	EXPECT_EQ(complex(+inf, pi/2), bksge::acosh(complex(min, +inf)));
	EXPECT_EQ(complex(+inf, pi/2), bksge::acosh(complex(T(-2.0), +inf)));
	EXPECT_EQ(complex(+inf, pi/2), bksge::acosh(complex(T(-1.0), +inf)));
	EXPECT_EQ(complex(+inf, pi/2), bksge::acosh(complex(T(-0.0), +inf)));
	EXPECT_EQ(complex(+inf, pi/2), bksge::acosh(complex(T(+0.0), +inf)));
	EXPECT_EQ(complex(+inf, pi/2), bksge::acosh(complex(T(+1.0), +inf)));
	EXPECT_EQ(complex(+inf, pi/2), bksge::acosh(complex(T(+2.0), +inf)));
	EXPECT_EQ(complex(+inf, pi/2), bksge::acosh(complex(max, +inf)));

	// If z is (x,NaN) (for finite non-zero x), the result is (NaN,NaN) and FE_INVALID may be raised.
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(min, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(min, nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(T(-2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(T(-2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(T(-1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(T(-1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(T(+1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(T(+1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(T(+2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(T(+2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(max, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(max, nan)).imag()));

	// If z is (0,NaN) the result is (NaN,π/2)
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(T(-0.0), nan)).real()));
	EXPECT_TRUE(pi/2 ==      bksge::acosh(complex(T(-0.0), nan)).imag());
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE(pi/2 ==      bksge::acosh(complex(T(+0.0), nan)).imag());

	// If z is (-∞,y) (for any positive finite y), the result is (+∞,π)
	EXPECT_EQ(complex(+inf, pi), bksge::acosh(complex(-inf, T(+0.0))));
	EXPECT_EQ(complex(+inf, pi), bksge::acosh(complex(-inf, T(+1.0))));
	EXPECT_EQ(complex(+inf, pi), bksge::acosh(complex(-inf, T(+2.0))));
	EXPECT_EQ(complex(+inf, pi), bksge::acosh(complex(-inf, max)));

	// If z is (+∞,y) (for any positive finite y), the result is (+∞,+0)
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::acosh(complex(+inf, T(+0.0))));
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::acosh(complex(+inf, T(+1.0))));
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::acosh(complex(+inf, T(+2.0))));
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::acosh(complex(+inf, max)));

	// If z is (-∞,+∞), the result is (+∞,3π/4)
	EXPECT_EQ(complex(+inf, pi*3/4), bksge::acosh(complex(-inf, +inf)));

	// If z is (±∞,NaN), the result is (+∞,NaN)
	EXPECT_TRUE(+inf ==     (bksge::acosh(complex(-inf, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(-inf, nan)).imag()));
	EXPECT_TRUE(+inf ==     (bksge::acosh(complex(+inf, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(+inf, nan)).imag()));

	// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised.
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, min)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, min)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(-2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(-2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(-1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(-1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(-0.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(-0.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(+0.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(+0.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(+1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(+1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(+2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, T(+2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, max)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, max)).imag()));

	// If z is (NaN,+∞), the result is (+∞,NaN)
	EXPECT_TRUE(+inf ==     (bksge::acosh(complex(nan, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, +inf)).imag()));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acosh(complex(nan, nan)).imag()));
#endif
}

GTEST_TEST(ComplexTest, AcoshTest)
{
	AcoshTest<float>();
	AcoshTest<double>();
	AcoshTest<long double>();
}

}	// namespace acosh_test

}	// namespace bksge_complex_test
