/**
 *	@file	unit_test_fnd_complex_asin.cpp
 *
 *	@brief	asin(complex<T> const&) のテスト
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
#include "complex_test_utility.hpp"

namespace bksge_complex_test
{

namespace asin_test
{

template <typename T>
void AsinTest(double error)
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();
	BKSGE_CONSTEXPR auto pi = bksge::pi_t<T>();

	auto const i = complex(T(0.0), T(1.0));

	// asin(z) == -i * asinh(i*z)
	// asin(z) = acos(-z) - π/2
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::asin(z), -i * bksge::asinh(i * z));
		EXPECT_TRUE(IsNear(bksge::asin(z), bksge::acos(-z) - pi/2, error));
	}
	{
		auto z = complex(T(2.0), T(-3.0));
		EXPECT_EQ(bksge::asin(z), -i * bksge::asinh(i * z));
		EXPECT_TRUE(IsNear(bksge::asin(z), bksge::acos(-z) - pi/2, error));
	}
	{
		auto z = complex(T(-4.0), T(3.0));
		EXPECT_EQ(bksge::asin(z), -i * bksge::asinh(i * z));
		EXPECT_TRUE(IsNear(bksge::asin(z), bksge::acos(-z) - pi/2, error));
	}
	{
		auto z = complex(T(-5.0), T(-4.0));
		auto t = bksge::asinh(i * z);
		EXPECT_EQ(bksge::asin(z), -i * t);
		EXPECT_EQ(bksge::asin(z), complex(t.imag(), -t.real()));
		EXPECT_TRUE(IsNear(bksge::asin(z), bksge::acos(-z) - pi/2, error));
	}
	{
		auto z = complex(min, min);
		auto t = bksge::asinh(i * z);
//		EXPECT_EQ(bksge::asin(z), -i * t);
		EXPECT_TRUE(IsEqual(bksge::asin(z), complex(t.imag(), -t.real())));
	}
	{
		auto z = complex(min, max);
		auto t = bksge::asinh(i * z);
//		EXPECT_EQ(bksge::asin(z), -i * t);
		EXPECT_TRUE(IsEqual(bksge::asin(z), complex(t.imag(), -t.real())));
	}
	{
		auto z = complex(max, min);
		auto t = bksge::asinh(i * z);
//		EXPECT_EQ(bksge::asin(z), -i * t);
		EXPECT_TRUE(IsEqual(bksge::asin(z), complex(t.imag(), -t.real())));
	}
	{
		auto z = complex(max, max);
		auto t = bksge::asinh(i * z);
//		EXPECT_EQ(bksge::asin(z), -i * t);
		EXPECT_TRUE(IsEqual(bksge::asin(z), complex(t.imag(), -t.real())));
	}
}

GTEST_TEST(ComplexTest, AsinTest)
{
	AsinTest<float>      (0.00001);
	AsinTest<double>     (0.00000000000001);
	AsinTest<long double>(0.00000000000001);
}

}	// namespace asin_test

}	// namespace bksge_complex_test
