/**
 *	@file	unit_test_fnd_config_cxx14.cpp
 *
 *	@brief	
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include <array>

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4189)	// ローカル変数が初期化されましたが、参照されていません
BKSGE_WARNING_DISABLE_CLANG("-Wunused-variable")
BKSGE_WARNING_DISABLE_CLANG("-Wmissing-braces")

namespace bksge_config_cxx14_test
{

GTEST_TEST(ConfigTest, Cxx14AlignedNewTest)
{
#if defined(BKSGE_HAS_CXX14_BINARY_LITERALS)
	int x = 0b1010;
	int y = 0B1111000011001010;

	EXPECT_EQ(10, x);
	EXPECT_EQ(61642, y);
#endif
}

namespace return_type_deduction_test
{

#if defined(BKSGE_HAS_CXX14_RETURN_TYPE_DEDUCTION)
auto f1()
{
	return 42;
}

decltype(auto) f2(int& r)
{
	return r;
}
#endif

GTEST_TEST(ConfigTest, Cxx14ReturnTypeDeductionTest)
{
#if defined(BKSGE_HAS_CXX14_RETURN_TYPE_DEDUCTION)
	int x = f1();
	int& r = f2(x);
	EXPECT_EQ(42, x);
	r = 10;
	EXPECT_EQ(10, x);
#endif
}

}	// namespace return_type_deduction_test

namespace init_captures_test
{

int increment(int x)
{
	return x + 1;
}

GTEST_TEST(ConfigTest, Cxx14InitCapturesTest)
{
#if defined(BKSGE_HAS_CXX14_INIT_CAPTURES)
	{
		auto f = [a = increment(3)](int b) { return a + b; };
		int result = f(2);
		EXPECT_EQ(6, result);
	}
	{
		std::vector<int> v;
		auto f = [x = std::move(v)]{};
	}
	{
		int a = 3;
		auto f = [b = a, &c = a] { (void)b; (void)c; };
		(void)f;
	}
#endif	// defined(BKSGE_HAS_CXX14_INIT_CAPTURES)
}

}	// namespace init_captures_test

GTEST_TEST(ConfigTest, Cxx14GenericLambdasTest)
{
#if defined(BKSGE_HAS_CXX14_GENERIC_LAMBDAS)
	auto plus = [](auto a, auto b) { return a + b; };

	int   result1 = plus(3, 2);
	float result2 = plus(1.5f, 2.5f);

	EXPECT_EQ(5,    result1);
	EXPECT_EQ(4.0f, result2);
#endif	// defined(BKSGE_HAS_CXX14_GENERIC_LAMBDAS)
}

namespace variable_templates_test
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
constexpr T pi = static_cast<T>(3.14159265358979323846);

constexpr float pif = pi<float>;
constexpr double pid = pi<double>;
constexpr long double pild = pi<long double>;

#endif	// defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

}	// namespace variable_templates_test

namespace constexpr_test
{

#if defined(BKSGE_HAS_CXX14_CONSTEXPR)
constexpr int f(int a)
{
	int x = a;

	if (x < 0)
	{
		return -x;
	}

	switch (x)
	{
	case 0: return 10;
	case 1: return 20;
	case 2: return 30;
	default: break;
	}

	for (int i = 0; i < 5; ++i)
	{
		x += i + 1;
	}

	int ar[] ={6, 7, 8};
	for (const int& i : ar)
	{
		x += i;
	}

	while (true)
	{
		x += 9;
		break;
	}

	do
	{
		x += 10;
	}
	while (false);

	return x;
}
#endif

GTEST_TEST(ConfigTest, Cxx14ConstexprTest)
{
#if defined(BKSGE_HAS_CXX14_CONSTEXPR)
	constexpr int x = f(10);
	EXPECT_EQ(65, x);
#endif
}

}	// namespace constexpr_test

GTEST_TEST(ConfigTest, Cxx14AggregateNsdmiTest)
{
	std::array<int, 3> ar1 = {{1, 2, 3}};
	EXPECT_EQ(1, ar1[0]);
	EXPECT_EQ(2, ar1[1]);
	EXPECT_EQ(3, ar1[2]);

#if defined(BKSGE_HAS_CXX14_AGGREGATE_NSDMI)
	std::array<int, 3> ar2 = {1, 2, 3};
	EXPECT_EQ(1, ar2[0]);
	EXPECT_EQ(2, ar2[1]);
	EXPECT_EQ(3, ar2[2]);
#endif
}

#if defined(BKSGE_HAS_CXX14_DEPRECATED)

namespace deprecated_test
{

[[deprecated("please use new_func() function")]]
void old_func() {}

}	// namespace deprecated_test

#endif	// defined(BKSGE_HAS_CXX14_DEPRECATED)

GTEST_TEST(ConfigTest, Cxx14DigitSeparatorsTest)
{
#if defined(BKSGE_HAS_CXX14_DIGIT_SEPARATORS)
	int decimal_value = 123'456'789;
	int octal_value = 012'34'56;
	int hex_value = 0x1'234'5678;
#if defined(BKSGE_HAS_CXX14_BINARY_LITERALS)
	int binary_value = 0b1010'1010'0001;
#endif
	double floating_point_value = 12'345.678'901;
#endif
}

namespace sized_deallocation_test
{

#if defined(BKSGE_HAS_CXX14_SIZED_DEALLOCATION)

// TODO

#endif	// defined(BKSGE_HAS_CXX14_SIZED_DEALLOCATION)

}	// namespace sized_deallocation_test

}	// namespace bksge_config_cxx14_test

BKSGE_WARNING_POP()
