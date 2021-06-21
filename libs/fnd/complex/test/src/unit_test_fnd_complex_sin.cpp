/**
 *	@file	unit_test_fnd_complex_sin.cpp
 *
 *	@brief	sin(complex<T> const&) のテスト
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

namespace sin_test
{

template <typename T>
void SinTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	auto const i = complex(T(0.0), T(1.0));

	// sin(z) == -i * sinh(i*z)
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::sin(z), -i * bksge::sinh(i * z));
	}
	{
		auto z = complex(T(2.0), T(-3.0));
		EXPECT_EQ(bksge::sin(z), -i * bksge::sinh(i * z));
	}
	{
		auto z = complex(T(-4.0), T(3.0));
		EXPECT_EQ(bksge::sin(z), -i * bksge::sinh(i * z));
	}
	{
		auto z = complex(T(-5.0), T(-4.0));
		EXPECT_EQ(bksge::sin(z), -i * bksge::sinh(i * z));
	}
	{
		auto z = complex(min, min);
		auto t = bksge::sinh(i * z);
//		EXPECT_EQ(bksge::sin(z), -i * t);
		EXPECT_TRUE(IsEqual(bksge::sin(z), complex(t.imag(), -t.real())));
	}
	{
		auto z = complex(min, max);
		auto t = bksge::sinh(i * z);
//		EXPECT_EQ(bksge::sin(z), -i * t);
		EXPECT_TRUE(IsEqual(bksge::sin(z), complex(t.imag(), -t.real())));
	}
	{
		auto z = complex(max, min);
		auto t = bksge::sinh(i * z);
//		EXPECT_EQ(bksge::sin(z), -i * t);
		EXPECT_TRUE(IsEqual(bksge::sin(z), complex(t.imag(), -t.real())));
	}
	{
		auto z = complex(max, max);
		auto t = bksge::sinh(i * z);
//		EXPECT_EQ(bksge::sin(z), -i * t);
		EXPECT_TRUE(IsEqual(bksge::sin(z), complex(t.imag(), -t.real())));
	}
}

GTEST_TEST(ComplexTest, SinTest)
{
	SinTest<float>();
	SinTest<double>();
	SinTest<long double>();
}

}	// namespace sin_test

}	// namespace bksge_complex_test
