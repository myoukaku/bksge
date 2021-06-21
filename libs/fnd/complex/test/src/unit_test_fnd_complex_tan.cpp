/**
 *	@file	unit_test_fnd_complex_tan.cpp
 *
 *	@brief	tan(complex<T> const&) のテスト
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

namespace tan_test
{

template <typename T>
void TanTest()
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = std::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = std::numeric_limits<T>::max();

	auto const i = complex(T(0.0), T(1.0));

	// tan(z) == -i * tanh(i*z)
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::tan(z), -i * bksge::tanh(i * z));
	}
	{
		auto z = complex(T(2.0), T(-3.0));
		EXPECT_EQ(bksge::tan(z), -i * bksge::tanh(i * z));
	}
	{
		auto z = complex(T(-4.0), T(3.0));
		EXPECT_EQ(bksge::tan(z), -i * bksge::tanh(i * z));
	}
	{
		auto z = complex(T(-5.0), T(-4.0));
		EXPECT_EQ(bksge::tan(z), -i * bksge::tanh(i * z));
	}
	{
		auto z = complex(min, min);
		EXPECT_TRUE(IsEqual(bksge::tan(z), -i * bksge::tanh(i * z)));
	}
	{
		auto z = complex(min, max);
		EXPECT_TRUE(IsEqual(bksge::tan(z), -i * bksge::tanh(i * z)));
	}
	{
		auto z = complex(max, min);
		EXPECT_TRUE(IsEqual(bksge::tan(z), -i * bksge::tanh(i * z)));
	}
	{
		auto z = complex(max, max);
		EXPECT_TRUE(IsEqual(bksge::tan(z), -i * bksge::tanh(i * z)));
	}
}

GTEST_TEST(ComplexTest, TanTest)
{
	TanTest<float>();
	TanTest<double>();
	TanTest<long double>();
}

}	// namespace tan_test

}	// namespace bksge_complex_test
