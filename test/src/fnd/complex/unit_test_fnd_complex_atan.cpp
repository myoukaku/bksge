/**
 *	@file	unit_test_fnd_complex_atan.cpp
 *
 *	@brief	atan(complex<T> const&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/complex/complex.hpp>
#include <bksge/fnd/cmath/isinf.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

namespace bksge_complex_test
{

namespace atan_test
{

template <typename T>
void AtanTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	auto const i = complex(T(0.0), T(1.0));

	// atan(z) == -i * atanh(i*z)
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::atan(z), -i * bksge::atanh(i * z));
	}
	{
		auto z = complex(T(2.0), T(-3.0));
		EXPECT_EQ(bksge::atan(z), -i * bksge::atanh(i * z));
	}
	{
		auto z = complex(T(-4.0), T(3.0));
		EXPECT_EQ(bksge::atan(z), -i * bksge::atanh(i * z));
	}
	{
		auto z = complex(T(-5.0), T(-4.0));
		EXPECT_EQ(bksge::atan(z), -i * bksge::atanh(i * z));
	}
	{
		auto z = complex(min, min);
		EXPECT_EQ(bksge::atan(z), -i * bksge::atanh(i * z));
	}
	{
		auto z = complex(min, max);
		EXPECT_EQ(bksge::atan(z), -i * bksge::atanh(i * z));
	}
	{
		auto z = complex(max, min);
		EXPECT_EQ(bksge::atan(z), -i * bksge::atanh(i * z));
	}
	{
		auto z = complex(max, max);
		EXPECT_EQ(bksge::atan(z), -i * bksge::atanh(i * z));
	}
}

GTEST_TEST(ComplexTest, AtanTest)
{
	AtanTest<float>();
	AtanTest<double>();
	AtanTest<long double>();
}

}	// namespace atan_test

}	// namespace bksge_complex_test
