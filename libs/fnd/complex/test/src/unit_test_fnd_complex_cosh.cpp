/**
 *	@file	unit_test_fnd_complex_cosh.cpp
 *
 *	@brief	cosh(complex<T> const&) のテスト
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
#include "complex_test_utility.hpp"

namespace bksge_complex_test
{

namespace cosh_test
{

template <typename T>
void CoshTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	// cosh(conj(z)) == conj(cosh(z))
	// cosh(z) == cosh(-z)
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::cosh(bksge::conj(z)), bksge::conj(bksge::cosh(z)));
		EXPECT_EQ(bksge::cosh(z), bksge::cosh(-z));
	}
	{
		auto z = complex(T(2.0), T(-3.0));
		EXPECT_EQ(bksge::cosh(bksge::conj(z)), bksge::conj(bksge::cosh(z)));
		EXPECT_EQ(bksge::cosh(z), bksge::cosh(-z));
	}
	{
		auto z = complex(T(-4.0), T(3.0));
		EXPECT_EQ(bksge::cosh(bksge::conj(z)), bksge::conj(bksge::cosh(z)));
		EXPECT_EQ(bksge::cosh(z), bksge::cosh(-z));
	}
	{
		auto z = complex(T(-5.0), T(-4.0));
		EXPECT_EQ(bksge::cosh(bksge::conj(z)), bksge::conj(bksge::cosh(z)));
		EXPECT_EQ(bksge::cosh(z), bksge::cosh(-z));
	}
	{
		auto z = complex(min, min);
		EXPECT_EQ(bksge::cosh(bksge::conj(z)), bksge::conj(bksge::cosh(z)));
		EXPECT_EQ(bksge::cosh(z), bksge::cosh(-z));
	}
	{
		auto z = complex(min, max);
		EXPECT_EQ(bksge::cosh(bksge::conj(z)), bksge::conj(bksge::cosh(z)));
		EXPECT_EQ(bksge::cosh(z), bksge::cosh(-z));
	}
	{
		auto z = complex(max, min);
		EXPECT_EQ(bksge::cosh(bksge::conj(z)), bksge::conj(bksge::cosh(z)));
		EXPECT_EQ(bksge::cosh(z), bksge::cosh(-z));
	}
	{
		auto z = complex(max, max);
		EXPECT_EQ(bksge::cosh(bksge::conj(z)), bksge::conj(bksge::cosh(z)));
		EXPECT_EQ(bksge::cosh(z), bksge::cosh(-z));
	}

#if defined(BKSGE_IEC_559_COMPLEX)
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	// If z is (+0,+0), the result is (1,+0)
	EXPECT_EQ(complex(T(+1.0), T(+0.0)), bksge::cosh(complex(T(+0.0), T(+0.0))));

	// If z is (+0,+∞), the result is (NaN,±0) (the sign of the imaginary part is unspecified) and FE_INVALID is raised
	EXPECT_TRUE(bksge::isnan (bksge::cosh(complex(T(+0.0), +inf)).real()));
	EXPECT_TRUE(bksge::iszero(bksge::cosh(complex(T(+0.0), +inf)).imag()));

	// If z is (+0,NaN), the result is (NaN,±0) (the sign of the imaginary part is unspecified)
	EXPECT_TRUE(bksge::isnan (bksge::cosh(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE(bksge::iszero(bksge::cosh(complex(T(+0.0), nan)).imag()));

	// If z is (x,+∞) (for any finite non-zero x), the result is (NaN,NaN) and FE_INVALID is raised
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(min, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(min, +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(-2.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(-2.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(-1.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(-1.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(+1.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(+1.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(+2.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(+2.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(max, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(max, +inf)).imag()));

	// If z is (x,NaN) (for any finite non-zero x), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(min, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(min, nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(-2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(-2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(-1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(-1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(+1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(+1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(+2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(T(+2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(max, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(max, nan)).imag()));

	// If z is (+∞,+0), the result is (+∞,+0)
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::cosh(complex(+inf, T(+0.0))));

	// If z is (+∞,y) (for any finite non-zero y), the result is +∞cis(y)
	EXPECT_EQ(complex(+inf, +inf), bksge::cosh(complex(+inf, T(+1.0))));
	EXPECT_EQ(complex(-inf, +inf), bksge::cosh(complex(+inf, T(+2.0))));
	EXPECT_EQ(complex(+inf, -inf), bksge::cosh(complex(+inf, T(-1.0))));
	EXPECT_EQ(complex(-inf, -inf), bksge::cosh(complex(+inf, T(-2.0))));

	// If z is (+∞,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified) and FE_INVALID is raised
	EXPECT_TRUE(bksge::isinf(bksge::cosh(complex(+inf, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(+inf, +inf)).imag()));

	// If z is (+∞,NaN), the result is (+∞,NaN)
	EXPECT_TRUE( bksge::isinf  (bksge::cosh(complex(+inf, nan)).real()));
	EXPECT_TRUE(!bksge::signbit(bksge::cosh(complex(+inf, nan)).real()));
	EXPECT_TRUE( bksge::isnan  (bksge::cosh(complex(+inf, nan)).imag()));

	// If z is (NaN,+0), the result is (NaN,±0) (the sign of the imaginary part is unspecified)
	EXPECT_TRUE(bksge::isnan (bksge::cosh(complex(nan, T(+0.0))).real()));
	EXPECT_TRUE(bksge::iszero(bksge::cosh(complex(nan, T(+0.0))).imag()));

	// If z is (NaN,+y) (for any finite non-zero y), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, min)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, min)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, T(-2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, T(-2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, T(-1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, T(-1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, T(+1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, T(+1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, T(+2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, T(+2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, max)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, max)).imag()));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::cosh(complex(nan, nan)).imag()));
#endif
}

GTEST_TEST(ComplexTest, CoshTest)
{
	CoshTest<float>();
	CoshTest<double>();
	CoshTest<long double>();
}

}	// namespace cosh_test

}	// namespace bksge_complex_test
