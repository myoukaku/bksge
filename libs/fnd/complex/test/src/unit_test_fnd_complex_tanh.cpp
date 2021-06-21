/**
 *	@file	unit_test_fnd_complex_tanh.cpp
 *
 *	@brief	tanh(complex<T> const&) のテスト
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

namespace tanh_test
{

template <typename T>
void TanhTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	// tanh(conj(z)) == conj(tanh(z))
	// tanh(-z) == -tanh(z)
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::tanh(bksge::conj(z)), bksge::conj(bksge::tanh(z)));
		EXPECT_EQ(bksge::tanh(-z), -bksge::tanh(z));
	}
	{
		auto z = complex(T(-2.0), T(3.0));
		EXPECT_EQ(bksge::tanh(bksge::conj(z)), bksge::conj(bksge::tanh(z)));
		EXPECT_EQ(bksge::tanh(-z), -bksge::tanh(z));
	}
	{
		auto z = complex(T(5.0), T(-4.0));
		EXPECT_EQ(bksge::tanh(bksge::conj(z)), bksge::conj(bksge::tanh(z)));
		EXPECT_EQ(bksge::tanh(-z), -bksge::tanh(z));
	}
	{
		auto z = complex(T(-6.0), T(-5.0));
		EXPECT_EQ(bksge::tanh(bksge::conj(z)), bksge::conj(bksge::tanh(z)));
		EXPECT_EQ(bksge::tanh(-z), -bksge::tanh(z));
	}
	{
		auto z = complex(min, min);
		EXPECT_TRUE(IsEqual(bksge::tanh(bksge::conj(z)), bksge::conj(bksge::tanh(z))));
		EXPECT_TRUE(IsEqual(bksge::tanh(-z), -bksge::tanh(z)));
	}
	{
		auto z = complex(min, max);
		EXPECT_TRUE(IsEqual(bksge::tanh(bksge::conj(z)), bksge::conj(bksge::tanh(z))));
		EXPECT_TRUE(IsEqual(bksge::tanh(-z), -bksge::tanh(z)));
	}
	{
		auto z = complex(max, min);
		EXPECT_TRUE(IsEqual(bksge::tanh(bksge::conj(z)), bksge::conj(bksge::tanh(z))));
		EXPECT_TRUE(IsEqual(bksge::tanh(-z), -bksge::tanh(z)));
	}
	{
		auto z = complex(max, max);
		EXPECT_TRUE(IsEqual(bksge::tanh(bksge::conj(z)), bksge::conj(bksge::tanh(z))));
		EXPECT_TRUE(IsEqual(bksge::tanh(-z), -bksge::tanh(z)));
	}

#if defined(BKSGE_IEC_559_COMPLEX)
	BKSGE_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	BKSGE_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	// If z is (+0,+0), the result is (+0,+0)
	EXPECT_EQ(complex(T(+0.0), T(+0.0)), bksge::tanh(complex(T(+0.0), T(+0.0))));

	// If z is (x,+∞) (for finite non-zero x), the result is (NaN,NaN) and FE_INVALID is raised
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(min, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(min, +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(-2.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(-2.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(-1.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(-1.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(+1.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(+1.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(+2.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(+2.0), +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(max, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(max, +inf)).imag()));

	// If z is (0,+∞) the result is (0,NaN) and FE_INVALID is raised
	EXPECT_TRUE(bksge::iszero(bksge::tanh(complex(T(+0.0), +inf)).real()));
	EXPECT_TRUE(bksge::isnan (bksge::tanh(complex(T(+0.0), +inf)).imag()));

	// If z is (x,NaN) (for finite non-zero x), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(min, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(min, nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(-2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(-2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(-1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(-1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(+1.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(+1.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(+2.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(T(+2.0), nan)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(max, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(max, nan)).imag()));

	// If z is (0,NaN) the result is (0,NaN)
	EXPECT_TRUE(bksge::iszero(bksge::tanh(complex(T(+0.0), nan)).real()));
	EXPECT_TRUE(bksge::isnan (bksge::tanh(complex(T(+0.0), nan)).imag()));

	// If z is (+∞,y) (for any finite positive y), the result is (1,+0)
	EXPECT_EQ(complex(T(+1.0), T(+0.0)), bksge::tanh(complex(+inf, T(+0.0))));
	EXPECT_EQ(complex(T(+1.0), T(+0.0)), bksge::tanh(complex(+inf, T(+1.0))));
	EXPECT_EQ(complex(T(+1.0), T(+0.0)), bksge::tanh(complex(+inf, T(+2.0))));
	EXPECT_EQ(complex(T(+1.0), T(+0.0)), bksge::tanh(complex(+inf, max)));

	// If z is (+∞,+∞), the result is (1,±0) (the sign of the imaginary part is unspecified)
	EXPECT_EQ(complex(T(+1.0), T(0.0)), bksge::tanh(complex(+inf, +inf)));

	// If z is (+∞,NaN), the result is (1,±0) (the sign of the imaginary part is unspecified)
	EXPECT_EQ(complex(T(+1.0), T(0.0)), bksge::tanh(complex(+inf, nan)));

	// If z is (NaN,+0), the result is (NaN,+0)
	EXPECT_TRUE( bksge::isnan  (bksge::tanh(complex(nan, T(+0.0))).real()));
	EXPECT_TRUE( bksge::iszero (bksge::tanh(complex(nan, T(+0.0))).imag()));
	EXPECT_TRUE(!bksge::signbit(bksge::tanh(complex(nan, T(+0.0))).imag()));

	// If z is (NaN,y) (for any non-zero y), the result is (NaN,NaN) and FE_INVALID may be raised
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, min)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, min)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, T(-2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, T(-2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, T(-1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, T(-1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, T(+1.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, T(+1.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, T(+2.0))).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, T(+2.0))).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, max)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, max)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, +inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, +inf)).imag()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, -inf)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, -inf)).imag()));

	// If z is (NaN,NaN), the result is (NaN,NaN)
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, nan)).real()));
	EXPECT_TRUE(bksge::isnan(bksge::tanh(complex(nan, nan)).imag()));
#endif
}

GTEST_TEST(ComplexTest, TanhTest)
{
	TanhTest<float>();
	TanhTest<double>();
	TanhTest<long double>();
}

}	// namespace tanh_test

}	// namespace bksge_complex_test
