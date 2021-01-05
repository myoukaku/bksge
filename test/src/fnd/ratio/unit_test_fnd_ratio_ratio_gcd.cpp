/**
 *	@file	unit_test_fnd_ratio_ratio_gcd.cpp
 *
 *	@brief	ratio_gcd のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ratio/ratio_gcd.hpp>
#include <bksge/fnd/ratio/ratio.hpp>
#include <gtest/gtest.h>

GTEST_TEST(RatioTest, RatioGcdTest)
{
	// gcd(1/2, 3/4) = 1/4
	{
		using r1 = bksge::ratio<1, 2>;
		using r2 = bksge::ratio<3, 4>;
		using r = bksge::ratio_gcd<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 4, "");
	}

	// gcd(1/5, 2/5) = 1/5
	{
		using r1 = bksge::ratio<1, 5>;
		using r2 = bksge::ratio<2, 5>;
		using r = bksge::ratio_gcd<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 5, "");
	}

	// gcd(3/5, 2/5) = 1/5
	{
		using r1 = bksge::ratio<3, 5>;
		using r2 = bksge::ratio<2, 5>;
		using r = bksge::ratio_gcd<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 5, "");
	}

	// gcd(2/5, 4/5) = 2/5
	{
		using r1 = bksge::ratio<2, 5>;
		using r2 = bksge::ratio<4, 5>;
		using r = bksge::ratio_gcd<r1, r2>;

		static_assert(r::num == 2, "");
		static_assert(r::den == 5, "");
	}

	// gcd(1/3, 1/4) = 1/12
	{
		using r1 = bksge::ratio<1, 3>;
		using r2 = bksge::ratio<1, 4>;
		using r = bksge::ratio_gcd<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 12, "");
	}
}
