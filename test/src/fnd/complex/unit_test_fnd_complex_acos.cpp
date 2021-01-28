/**
 *	@file	unit_test_fnd_complex_acos.cpp
 *
 *	@brief	acos(complex<T> const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/complex/complex.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace bksge_complex_test
{

namespace acos_test
{

template <typename T>
void AcosTest(double error)
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto pi = bksge::pi_t<T>();

	// acos(conj(z)) == conj(acos(z))
	// acos(z) == π - acos(-z)
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::acos(bksge::conj(z)), bksge::conj(bksge::acos(z)));
		EXPECT_TRUE(IsNear(bksge::acos(z), pi - bksge::acos(-z), error));
	}
	{
		auto z = complex(T(2.0), T(-3.0));
		EXPECT_EQ(bksge::acos(bksge::conj(z)), bksge::conj(bksge::acos(z)));
		EXPECT_TRUE(IsNear(bksge::acos(z), pi - bksge::acos(-z), error));
	}
	{
		auto z = complex(T(-4.0), T(3.0));
		EXPECT_EQ(bksge::acos(bksge::conj(z)), bksge::conj(bksge::acos(z)));
		EXPECT_TRUE(IsNear(bksge::acos(z), pi - bksge::acos(-z), error));
	}
	{
		auto z = complex(T(-5.0), T(-4.0));
		EXPECT_EQ(bksge::acos(bksge::conj(z)), bksge::conj(bksge::acos(z)));
		EXPECT_TRUE(IsNear(bksge::acos(z), pi - bksge::acos(-z), error));
	}
	{
		auto z = complex(min, min);
		EXPECT_EQ(bksge::acos(bksge::conj(z)), bksge::conj(bksge::acos(z)));
		EXPECT_EQ(bksge::acos(z), pi - bksge::acos(-z));
	}
	{
		auto z = complex(min, max);
		EXPECT_EQ(bksge::acos(bksge::conj(z)), bksge::conj(bksge::acos(z)));
		EXPECT_EQ(bksge::acos(z), pi - bksge::acos(-z));
	}
	{
		auto z = complex(max, min);
		EXPECT_EQ(bksge::acos(bksge::conj(z)), bksge::conj(bksge::acos(z)));
		EXPECT_EQ(bksge::acos(z), pi - bksge::acos(-z));
	}
	{
		auto z = complex(max, max);
		EXPECT_EQ(bksge::acos(bksge::conj(z)), bksge::conj(bksge::acos(z)));
		EXPECT_EQ(bksge::acos(z), pi - bksge::acos(-z));
	}

#if defined(BKSGE_IEC_559_COMPLEX)
	BKSGE_CONSTEXPR auto nan = bksge::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = bksge::numeric_limits<T>::infinity();

	// If z is (±0,+0), the result is (π/2,-0)
	EXPECT_EQ(complex(pi/2, T(-0.0)), bksge::acos(complex(T(-0.0), T(+0.0))));
	EXPECT_EQ(complex(pi/2, T(-0.0)), bksge::acos(complex(T(+0.0), T(+0.0))));

	// If z is (±0,NaN), the result is (π/2,NaN)
	EXPECT_TRUE(pi/2 ==     (bksge::acos(complex(T(-0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(T(-0.0), nan)).imag()));
	EXPECT_TRUE(pi/2 ==     (bksge::acos(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(T(+0.0), nan)).imag()));

	// If z is (x,+∞) (for any finite x), the result is (π/2,-∞)
	EXPECT_EQ(complex(pi/2, -inf), bksge::acos(complex(min, +inf)));
	EXPECT_EQ(complex(pi/2, -inf), bksge::acos(complex(T(-2.0), +inf)));
	EXPECT_EQ(complex(pi/2, -inf), bksge::acos(complex(T(-1.0), +inf)));
	EXPECT_EQ(complex(pi/2, -inf), bksge::acos(complex(T(-0.0), +inf)));
	EXPECT_EQ(complex(pi/2, -inf), bksge::acos(complex(T(+0.0), +inf)));
	EXPECT_EQ(complex(pi/2, -inf), bksge::acos(complex(T(+1.0), +inf)));
	EXPECT_EQ(complex(pi/2, -inf), bksge::acos(complex(T(+2.0), +inf)));
	EXPECT_EQ(complex(pi/2, -inf), bksge::acos(complex(max, +inf)));

	// If z is (x,NaN) (for any nonzero finite x), the result is (NaN,NaN) and FE_INVALID may be raised.
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(min, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(min, nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(T(-2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(T(-2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(T(-1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(T(-1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(T(+1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(T(+1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(T(+2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(T(+2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(max, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(max, nan)).imag()));

	// If z is (-∞,y) (for any positive finite y), the result is (π,-∞)
	EXPECT_EQ(complex(pi, -inf), bksge::acos(complex(-inf, T(+0.0))));
	EXPECT_EQ(complex(pi, -inf), bksge::acos(complex(-inf, T(+1.0))));
	EXPECT_EQ(complex(pi, -inf), bksge::acos(complex(-inf, T(+2.0))));
	EXPECT_EQ(complex(pi, -inf), bksge::acos(complex(-inf, max)));

	// If z is (+∞,y) (for any positive finite y), the result is (+0,-∞)
	EXPECT_EQ(complex(T(+0.0), -inf), bksge::acos(complex(+inf, T(+0.0))));
	EXPECT_EQ(complex(T(+0.0), -inf), bksge::acos(complex(+inf, T(+1.0))));
	EXPECT_EQ(complex(T(+0.0), -inf), bksge::acos(complex(+inf, T(+2.0))));
	EXPECT_EQ(complex(T(+0.0), -inf), bksge::acos(complex(+inf, max)));

	// If z is (-∞,+∞), the result is (3π/4,-∞)
	EXPECT_EQ(complex(pi*3/4, -inf), bksge::acos(complex(-inf, +inf)));

	// If z is (+∞,+∞), the result is (π/4,-∞)
	EXPECT_EQ(complex(pi/4, -inf), bksge::acos(complex(+inf, +inf)));

	// If z is (±∞,NaN), the result is (NaN,±∞) (the sign of the imaginary part is unspecified)
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(+inf, nan)).real()));
	EXPECT_TRUE(bksge::isinf(bksge::acos(complex(+inf, nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(-inf, nan)).real()));
	EXPECT_TRUE(bksge::isinf(bksge::acos(complex(-inf, nan)).imag()));

	// If z is (NaN,y) (for any finite y), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, min)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, min)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(-2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(-2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(-1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(-1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(-0.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(-0.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(+0.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(+0.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(+1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(+1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(+2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, T(+2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, max)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, max)).imag()));

	// If z is (NaN,+∞), the result is (NaN,-∞)
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, +inf)).real()));
	EXPECT_TRUE(-inf ==     (bksge::acos(complex(nan, +inf)).imag()));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::acos(complex(nan, nan)).imag()));
#endif
}

GTEST_TEST(ComplexTest, AcosTest)
{
	AcosTest<float>      (0.00001);
	AcosTest<double>     (0.00000000000001);
	AcosTest<long double>(0.00000000000001);
}

}	// namespace acos_test

}	// namespace bksge_complex_test
