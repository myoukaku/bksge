/**
 *	@file	unit_test_fnd_complex_log10.cpp
 *
 *	@brief	log10(complex<T> const&) のテスト
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

namespace log10_test
{

template <typename T>
void Log10Test(double error)
{
	using complex = bksge::complex<T>;

	BKSGE_CONSTEXPR auto min = bksge::numeric_limits<T>::lowest();
	BKSGE_CONSTEXPR auto max = bksge::numeric_limits<T>::max();

	// The behavior of this function is equivalent to log(z)/log(T(10)).
	{
		auto z = complex(T(1.0), T(1.0));
		EXPECT_TRUE(IsNear(bksge::log10(z), bksge::log(z)/bksge::log(T(10)), error));
	}
	{
		auto z = complex(T(2.0), T(3.0));
		EXPECT_TRUE(IsNear(bksge::log10(z), bksge::log(z)/bksge::log(T(10)), error));
	}
	{
		auto z = complex(T(3.0), T(2.0));
		EXPECT_TRUE(IsNear(bksge::log10(z), bksge::log(z)/bksge::log(T(10)), error));
	}
	{
		auto z = complex(T(-4.0), T(5.0));
		EXPECT_TRUE(IsNear(bksge::log10(z), bksge::log(z)/bksge::log(T(10)), error));
	}
	{
		auto z = complex(T(-5.0), T(-3.0));
		EXPECT_TRUE(IsNear(bksge::log10(z), bksge::log(z)/bksge::log(T(10)), error));
	}
	{
		auto z = complex(min, min);
		EXPECT_EQ(bksge::log10(z), bksge::log(z)/bksge::log(T(10)));
		//EXPECT_TRUE(IsNear(bksge::log10(z), bksge::log(z)/bksge::log(T(10)), error));
	}
	{
		auto z = complex(min, max);
		EXPECT_EQ(bksge::log10(z), bksge::log(z)/bksge::log(T(10)));
		//EXPECT_TRUE(IsNear(bksge::log10(z), bksge::log(z)/bksge::log(T(10)), error));
	}
	{
		auto z = complex(max, min);
		EXPECT_EQ(bksge::log10(z), bksge::log(z)/bksge::log(T(10)));
		//EXPECT_TRUE(IsNear(bksge::log10(z), bksge::log(z)/bksge::log(T(10)), error));
	}
	{
		auto z = complex(max, max);
		EXPECT_EQ(bksge::log10(z), bksge::log(z)/bksge::log(T(10)));
		//EXPECT_TRUE(IsNear(bksge::log10(z), bksge::log(z)/bksge::log(T(10)), error));
	}
}

GTEST_TEST(ComplexTest, Log10Test)
{
	Log10Test<float>      (0.0000001);
	Log10Test<double>     (0.0000000000001);
	Log10Test<long double>(0.0000000000001);
}

}	// namespace log10_test

}	// namespace bksge_complex_test
