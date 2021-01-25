/**
 *	@file	unit_test_fnd_complex_asinh.cpp
 *
 *	@brief	asinh(complex<T> const&) のテスト
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

namespace asinh_test
{

template <typename T>
void AsinhTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	// asinh(conj(z)) == conj(asinh(z))
	// asinh(-z) == -asinh(z)
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::asinh(bksge::conj(z)), bksge::conj(bksge::asinh(z)));
		EXPECT_EQ(bksge::asinh(-z), -bksge::asinh(z));
	}
	{
		auto z = complex(T(-2.0), T(3.0));
		EXPECT_EQ(bksge::asinh(bksge::conj(z)), bksge::conj(bksge::asinh(z)));
		EXPECT_EQ(bksge::asinh(-z), -bksge::asinh(z));
	}
	{
		auto z = complex(T(-4.0), T(3.0));
		EXPECT_EQ(bksge::asinh(bksge::conj(z)), bksge::conj(bksge::asinh(z)));
		EXPECT_EQ(bksge::asinh(-z), -bksge::asinh(z));
	}
	{
		auto z = complex(T(5.0), T(-4.0));
		EXPECT_EQ(bksge::asinh(bksge::conj(z)), bksge::conj(bksge::asinh(z)));
		EXPECT_EQ(bksge::asinh(-z), -bksge::asinh(z));
	}
	{
		auto z = complex(min, min);
		EXPECT_TRUE(IsEqual(bksge::asinh(bksge::conj(z)), bksge::conj(bksge::asinh(z))));
		EXPECT_TRUE(IsEqual(bksge::asinh(-z), -bksge::asinh(z)));
	}
	{
		auto z = complex(min, max);
		EXPECT_TRUE(IsEqual(bksge::asinh(bksge::conj(z)), bksge::conj(bksge::asinh(z))));
		EXPECT_TRUE(IsEqual(bksge::asinh(-z), -bksge::asinh(z)));
	}
	{
		auto z = complex(max, min);
		EXPECT_TRUE(IsEqual(bksge::asinh(bksge::conj(z)), bksge::conj(bksge::asinh(z))));
		EXPECT_TRUE(IsEqual(bksge::asinh(-z), -bksge::asinh(z)));
	}
	{
		auto z = complex(max, max);
		EXPECT_TRUE(IsEqual(bksge::asinh(bksge::conj(z)), bksge::conj(bksge::asinh(z))));
		EXPECT_TRUE(IsEqual(bksge::asinh(-z), -bksge::asinh(z)));
	}

#if defined(BKSGE_IEC_559_COMPLEX)
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();
	BKSGE_CONSTEXPR auto pi = bksge::pi<T>();

	// If z is (+0,+0), the result is (+0,+0)
	EXPECT_EQ(complex(T(+0.0), T(+0.0)), bksge::asinh(complex(T(+0.0), T(+0.0))));

	// If z is (x,+∞) (for any positive finite x), the result is (+∞,π/2)
	EXPECT_EQ(complex(+inf, pi/2), bksge::asinh(complex(T(+0.0), +inf)));
	EXPECT_EQ(complex(+inf, pi/2), bksge::asinh(complex(T(+1.0), +inf)));
	EXPECT_EQ(complex(+inf, pi/2), bksge::asinh(complex(T(+2.0), +inf)));
	EXPECT_EQ(complex(+inf, pi/2), bksge::asinh(complex(max,     +inf)));

	// If z is (x,NaN) (for any finite x), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(min,     nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(min,     nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(-2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(-2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(-1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(-1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(-0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(-0.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(+0.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(+1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(+1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(+2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(T(+2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(max,     nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(max,     nan)).imag()));

	// If z is (+∞,y) (for any positive finite y), the result is (+∞,+0)
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::asinh(complex(+inf, T(+0.0))));
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::asinh(complex(+inf, T(+1.0))));
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::asinh(complex(+inf, T(+2.0))));
	EXPECT_EQ(complex(+inf, T(+0.0)), bksge::asinh(complex(+inf, max)));

	// If z is (+∞,+∞), the result is (+∞,π/4)
	EXPECT_EQ(complex(+inf, pi/4), bksge::asinh(complex(+inf, +inf)));

	// If z is (+∞,NaN), the result is (+∞,NaN)
	EXPECT_TRUE(+inf ==      bksge::asinh(complex(+inf, nan)).real());
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(+inf, nan)).imag()));

	// If z is (NaN,+0), the result is (NaN,+0)
	EXPECT_TRUE( bksge::isnan  (bksge::asinh(complex(nan, T(+0.0))).real()));
	EXPECT_TRUE( bksge::iszero (bksge::asinh(complex(nan, T(+0.0))).imag()));
	EXPECT_TRUE(!bksge::signbit(bksge::asinh(complex(nan, T(+0.0))).imag()));

	// If z is (NaN,y) (for any finite nonzero y), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, min)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, min)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, T(-2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, T(-2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, T(-1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, T(-1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, T(+1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, T(+1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, T(+2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, T(+2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, max)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, max)).imag()));

	// If z is (NaN,+∞), the result is (±∞,NaN) (the sign of the real part is unspecified)
	EXPECT_TRUE(bksge::isinf(bksge::asinh(complex(nan, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, +inf)).imag()));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::asinh(complex(nan, nan)).imag()));
#endif
}

GTEST_TEST(ComplexTest, AsinhTest)
{
	AsinhTest<float>();
	AsinhTest<double>();
	AsinhTest<long double>();
}

}	// namespace asinh_test

}	// namespace bksge_complex_test
