/**
 *	@file	unit_test_fnd_complex_pow.cpp
 *
 *	@brief	pow のテスト
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

namespace pow_test
{

template <typename T>
void PowTest(double error)
{
	using complex = bksge::complex<T>;

	// (1)
	{
		auto x = complex(T(1.0), T(1.0));
		auto y = complex(T(1.0), T(1.0));
		EXPECT_EQ(bksge::pow(x, y), bksge::exp(y * bksge::log(x)));
	}
	{
		auto x = complex(T(1.0), T(2.0));
		auto y = complex(T(3.0), T(4.0));
		EXPECT_EQ(bksge::pow(x, y), bksge::exp(y * bksge::log(x)));
	}
	{
		auto x = complex(T(-1.0), T( 2.0));
		auto y = complex(T( 3.0), T(-4.0));
		EXPECT_EQ(bksge::pow(x, y), bksge::exp(y * bksge::log(x)));
	}
	// (2)
	{
		auto x = complex(T(1.0), T(2.0));
		auto y = T(3);
		EXPECT_EQ(bksge::pow(x, y), bksge::exp(y * bksge::log(x)));
	}
	// (3)
	{
		auto x = T(2);
		auto y = complex(T(-3.0), T(4.0));
		EXPECT_TRUE(IsNear(bksge::pow(x, y), bksge::exp(y * bksge::log(x)), error));
	}
	// (4)
	{
		auto x = complex(T(1.0), T(2.0));
		auto y = bksge::complex<float>(T(3.0), T(4.0));
		using ret_type = decltype(bksge::pow(x, y));
		EXPECT_TRUE(IsNear(bksge::pow(x, y), ret_type(bksge::exp(complex(y) * bksge::log(x))), error));
	}
	{
		auto x = complex(T(1.0), T(2.0));
		auto y = bksge::complex<double>(T(3.0), T(4.0));
		using ret_type = decltype(bksge::pow(x, y));
		EXPECT_TRUE(IsNear(bksge::pow(x, y), ret_type(bksge::exp(complex(y) * bksge::log(x))), error));
	}
	{
		auto x = complex(T(1.0), T(2.0));
		auto y = bksge::complex<long double>(T(3.0), T(4.0));
		using ret_type = decltype(bksge::pow(x, y));
		EXPECT_TRUE(IsNear(bksge::pow(x, y), ret_type(bksge::exp(complex(y) * bksge::log(x))), error));
	}
	// (5)
	{
		auto x = complex(T(1.0), T(2.0));
		auto y = float(3);
		using ret_type = decltype(bksge::pow(x, y));
		EXPECT_TRUE(IsNear(bksge::pow(x, y), ret_type(bksge::exp(T(y) * bksge::log(x))), error));
	}
	{
		auto x = complex(T(1.0), T(2.0));
		auto y = double(3);
		using ret_type = decltype(bksge::pow(x, y));
		EXPECT_TRUE(IsNear(bksge::pow(x, y), ret_type(bksge::exp(T(y) * bksge::log(x))), error));
	}
	{
		auto x = complex(T(1.0), T(2.0));
		auto y = (long double)3;
		using ret_type = decltype(bksge::pow(x, y));
		EXPECT_TRUE(IsNear(bksge::pow(x, y), bksge::exp(y * (ret_type)bksge::log(x)), error));
	}
	// (6)
	{
		auto x = float(3);
		auto y = complex(T(1.0), T(2.0));
		using ret_type = decltype(bksge::pow(x, y));
		EXPECT_TRUE(IsNear(bksge::pow(x, y), ret_type(bksge::exp(y * bksge::log((T)x))), error));
	}
	{
		auto x = double(3);
		auto y = complex(T(1.0), T(2.0));
		using ret_type = decltype(bksge::pow(x, y));
		EXPECT_TRUE(IsNear(bksge::pow(x, y), ret_type(bksge::exp(y * bksge::log((T)x))), error));
	}
	{
		auto x = (long double)3;
		auto y = complex(T(1.0), T(2.0));
		using ret_type = decltype(bksge::pow(x, y));
		EXPECT_TRUE(IsNear(bksge::pow(x, y), ret_type(bksge::exp(y * bksge::log((T)x))), error));
	}
}

GTEST_TEST(ComplexTest, PowTest)
{
	PowTest<float>      (0.00001);
	PowTest<double>     (0.00000000000001);
	PowTest<long double>(0.00000000000001);
}

}	// namespace pow_test

}	// namespace bksge_complex_test
