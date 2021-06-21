/**
 *	@file	unit_test_fnd_complex_cos.cpp
 *
 *	@brief	cos(complex<T> const&) のテスト
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

namespace cos_test
{

template <typename T>
void CosTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	auto const i = complex(T(0.0), T(1.0));

	// cos(z) == cosh(i*z)
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::cos(z), bksge::cosh(i * z));
	}
	{
		auto z = complex(T(2.0), T(-3.0));
		EXPECT_EQ(bksge::cos(z), bksge::cosh(i * z));
	}
	{
		auto z = complex(T(-4.0), T(3.0));
		EXPECT_EQ(bksge::cos(z), bksge::cosh(i * z));
	}
	{
		auto z = complex(T(-5.0), T(-4.0));
		EXPECT_EQ(bksge::cos(z), bksge::cosh(i * z));
	}
	{
		auto z = complex(min, min);
		EXPECT_EQ(bksge::cos(z), bksge::cosh(i * z));
	}
	{
		auto z = complex(min, max);
		EXPECT_EQ(bksge::cos(z), bksge::cosh(i * z));
	}
	{
		auto z = complex(max, min);
		EXPECT_EQ(bksge::cos(z), bksge::cosh(i * z));
	}
	{
		auto z = complex(max, max);
		EXPECT_EQ(bksge::cos(z), bksge::cosh(i * z));
	}
}

GTEST_TEST(ComplexTest, CosTest)
{
	CosTest<float>();
	CosTest<double>();
	CosTest<long double>();
}

}	// namespace cos_test

}	// namespace bksge_complex_test
