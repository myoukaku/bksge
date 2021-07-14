/**
 *	@file	unit_test_fnd_numeric_midpoint.cpp
 *
 *	@brief	midpoint のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numeric/midpoint.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4307);	// 整数定数がオーバーフローしました。
BKSGE_WARNING_DISABLE_MSVC(4308);	// 負の整数定数が符号なしの型に変換されました。

namespace bksge_numeric_test
{

namespace midpoint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test_floating()
{
	VERIFY(bksge::midpoint(T( 2.0), T( 4.0)) == T( 3.0));
	VERIFY(bksge::midpoint(T( 0.0), T( 0.4)) == T( 0.2));
	VERIFY(bksge::midpoint(T( 0.0), T(-0.0)) == T( 0.0));
	VERIFY(bksge::midpoint(T(-1.0), T(-2.0)) == T(-1.5));
	VERIFY(bksge::midpoint(T( 9e9), T(-9e9)) == T( 0.0));

	using lim = std::numeric_limits<T>;
	VERIFY(bksge::midpoint(lim::min(), lim::min()) == lim::min());
	VERIFY(bksge::midpoint(lim::max(), lim::min()) == lim::max()/2);
	VERIFY(bksge::midpoint(lim::min(), lim::max()) == lim::max()/2);
	VERIFY(bksge::midpoint(lim::max(), lim::max()) == lim::max());

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test_signed_integral()
{
	VERIFY(bksge::midpoint(T( 0), T( 0)) == T( 0));
	VERIFY(bksge::midpoint(T( 1), T( 1)) == T( 1));
	VERIFY(bksge::midpoint(T( 0), T( 1)) == T( 0));
	VERIFY(bksge::midpoint(T( 1), T( 0)) == T( 1));
	VERIFY(bksge::midpoint(T( 0), T( 2)) == T( 1));
	VERIFY(bksge::midpoint(T( 3), T( 2)) == T( 3));
	VERIFY(bksge::midpoint(T(-5), T( 4)) == T(-1));
	VERIFY(bksge::midpoint(T( 5), T(-4)) == T( 1));
	VERIFY(bksge::midpoint(T(-5), T(-4)) == T(-5));
	VERIFY(bksge::midpoint(T(-4), T(-5)) == T(-4));

	T min = std::numeric_limits<T>::min();
	T max = std::numeric_limits<T>::max();
	VERIFY(bksge::midpoint(T(min),   T(max))   == T(-1));
	VERIFY(bksge::midpoint(T(max),   T(min))   == T(0));
	VERIFY(bksge::midpoint(T(max),   T(max))   == T(max));
	VERIFY(bksge::midpoint(T(max),   T(max-1)) == T(max));
	VERIFY(bksge::midpoint(T(max-1), T(max-1)) == T(max-1));
	VERIFY(bksge::midpoint(T(max-1), T(max))   == T(max-1));
	VERIFY(bksge::midpoint(T(max),   T(max-2)) == T(max-1));

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test_unsigned_integral()
{
	VERIFY(bksge::midpoint(T(0), T(0)) == T(0));
	VERIFY(bksge::midpoint(T(0), T(1)) == T(0));
	VERIFY(bksge::midpoint(T(1), T(0)) == T(1));
	VERIFY(bksge::midpoint(T(0), T(2)) == T(1));
	VERIFY(bksge::midpoint(T(3), T(2)) == T(3));

	T max = std::numeric_limits<T>::max();
	VERIFY(bksge::midpoint(T(0),     T(max))   == T(max/2));
	VERIFY(bksge::midpoint(T(max),   T(0))     == T(max/2 + 1));
	VERIFY(bksge::midpoint(T(max),   T(max))   == T(max));
	VERIFY(bksge::midpoint(T(max),   T(max-1)) == T(max));
	VERIFY(bksge::midpoint(T(max-1), T(max-1)) == T(max-1));
	VERIFY(bksge::midpoint(T(max-1), T(max))   == T(max-1));
	VERIFY(bksge::midpoint(T(max),   T(max-2)) == T(max-1));

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool test_pointer()
{
	T a[4]{};
	VERIFY(bksge::midpoint(a, a)   == a);
	VERIFY(bksge::midpoint(a, a+1) == a);
	VERIFY(bksge::midpoint(a, a+2) == a+1);
	VERIFY(bksge::midpoint(a, a+3) == a+1);
	VERIFY(bksge::midpoint(a, a+4) == a+2);
	VERIFY(bksge::midpoint(a+1, a) == a+1);
	VERIFY(bksge::midpoint(a+2, a) == a+1);
	VERIFY(bksge::midpoint(a+3, a) == a+2);
	VERIFY(bksge::midpoint(a+4, a) == a+2);

	return true;
}

#undef VERIFY

GTEST_TEST(NumericTest, MidpointTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_floating<float>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_floating<double>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_floating<long double>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_signed_integral<signed char>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_signed_integral<signed short>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_signed_integral<signed int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_signed_integral<signed long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_signed_integral<signed long long>()));

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_unsigned_integral<unsigned char>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_unsigned_integral<unsigned short>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_unsigned_integral<unsigned int>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_unsigned_integral<unsigned long>()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test_unsigned_integral<unsigned long long>()));

	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((test_pointer<float>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((test_pointer<double>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((test_pointer<char>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((test_pointer<short>()));
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE((test_pointer<int>()));
}

}	// namespace midpoint_test

}	// namespace bksge_numeric_test

BKSGE_WARNING_POP();
