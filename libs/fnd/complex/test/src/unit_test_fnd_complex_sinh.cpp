/**
 *	@file	unit_test_fnd_complex_sinh.cpp
 *
 *	@brief	sinh(complex<T> const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/complex/complex.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace bksge_complex_test
{

namespace sinh_test
{

template <typename T>
void SinhTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	// sinh(conj(z)) == conj(sinh(z))
	// sinh(z) == -sinh(-z)
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::sinh(bksge::conj(z)), bksge::conj(bksge::sinh(z)));
		EXPECT_EQ(bksge::sinh(z), -bksge::sinh(-z));
	}
	{
		auto z = complex(T(-2.0), T(3.0));
		EXPECT_EQ(bksge::sinh(bksge::conj(z)), bksge::conj(bksge::sinh(z)));
		EXPECT_EQ(bksge::sinh(z), -bksge::sinh(-z));
	}
	{
		auto z = complex(T(5.0), T(-4.0));
		EXPECT_EQ(bksge::sinh(bksge::conj(z)), bksge::conj(bksge::sinh(z)));
		EXPECT_EQ(bksge::sinh(z), -bksge::sinh(-z));
	}
	{
		auto z = complex(T(-5.0), T(-6.0));
		EXPECT_EQ(bksge::sinh(bksge::conj(z)), bksge::conj(bksge::sinh(z)));
		EXPECT_EQ(bksge::sinh(z), -bksge::sinh(-z));
	}
	{
		auto z = complex(min, min);
		EXPECT_EQ(bksge::sinh(bksge::conj(z)), bksge::conj(bksge::sinh(z)));
		EXPECT_EQ(bksge::sinh(z), -bksge::sinh(-z));
	}
	{
		auto z = complex(min, max);
		EXPECT_EQ(bksge::sinh(bksge::conj(z)), bksge::conj(bksge::sinh(z)));
		EXPECT_EQ(bksge::sinh(z), -bksge::sinh(-z));
	}
	{
		auto z = complex(max, min);
		EXPECT_EQ(bksge::sinh(bksge::conj(z)), bksge::conj(bksge::sinh(z)));
		EXPECT_EQ(bksge::sinh(z), -bksge::sinh(-z));
	}
	{
		auto z = complex(max, max);
		EXPECT_EQ(bksge::sinh(bksge::conj(z)), bksge::conj(bksge::sinh(z)));
		EXPECT_EQ(bksge::sinh(z), -bksge::sinh(-z));
	}

#if defined(BKSGE_IEC_559_COMPLEX)
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	// If z is (+0,+0), the result is (+0,+0)
	EXPECT_EQ(complex(T(+0.0), T(+0.0)), bksge::sinh(complex(T(+0.0), T(+0.0))));

	// If z is (+0,+∞), the result is (±0,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
	EXPECT_TRUE(bksge::iszero(bksge::sinh(complex(T(+0.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan (bksge::sinh(complex(T(+0.0), +inf)).imag()));

	// If z is (+0,NaN), the result is (±0,NaN)
	EXPECT_TRUE(bksge::iszero(bksge::sinh(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan (bksge::sinh(complex(T(+0.0), nan)).imag()));

	// If z is (x,+∞) (for any positive finite x), the result is (NaN,NaN) and FE_INVALID is raised
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(T(+1.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(T(+1.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(T(+2.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(T(+2.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(max, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(max, +inf)).imag()));

	// If z is (x,NaN) (for any positive finite x), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(T(+1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(T(+1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(T(+2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(T(+2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(max, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(max, nan)).imag()));

	// If z is (+∞,+0), the result is (+∞,+0)
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::sinh(complex(+inf, T(+0.0))));

	// If z is (+∞,y) (for any positive finite y), the result is +∞cis(y)
	EXPECT_EQ(complex(+inf, +inf), bksge::sinh(complex(+inf, T(+1.0))));
	EXPECT_EQ(complex(-inf, +inf), bksge::sinh(complex(+inf, T(+2.0))));

	// If z is (+∞,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
	EXPECT_TRUE(bksge::isinf(bksge::sinh(complex(+inf, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(+inf, +inf)).imag()));

	// If z is (+∞,NaN), the result is (±∞,NaN) (the sign of the real part is unspecified)
	EXPECT_TRUE(bksge::isinf(bksge::sinh(complex(+inf, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(+inf, nan)).imag()));

	// If z is (NaN,+0), the result is (NaN,+0)
	EXPECT_TRUE( bksge::isnan  (bksge::sinh(complex(nan, T(+0.0))).real()));
	EXPECT_TRUE( bksge::iszero (bksge::sinh(complex(nan, T(+0.0))).imag()));
	EXPECT_TRUE(!bksge::signbit(bksge::sinh(complex(nan, T(+0.0))).imag()));

	// If z is (NaN,y) (for any finite nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, min)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, min)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, T(-2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, T(-2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, T(-1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, T(-1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, T(+1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, T(+1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, T(+2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, T(+2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, max)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, max)).imag()));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::sinh(complex(nan, nan)).imag()));
#endif
}

GTEST_TEST(ComplexTest, SinhTest)
{
	SinhTest<float>();
	SinhTest<double>();
	SinhTest<long double>();
}

}	// namespace sinh_test

}	// namespace bksge_complex_test
