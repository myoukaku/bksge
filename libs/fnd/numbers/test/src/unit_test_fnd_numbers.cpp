/**
 *	@file	unit_test_fnd_numbers.cpp
 *
 *	@brief	numbers のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/numbers.hpp>
#include <bksge/fnd/cmath.hpp>
#include <gtest/gtest.h>

namespace bksge_numbers_test
{

static_assert(bksge::e          != 0.0, "");
static_assert(bksge::log2e      != 0.0, "");
static_assert(bksge::log10e     != 0.0, "");
static_assert(bksge::pi         != 0.0, "");
static_assert(bksge::inv_pi     != 0.0, "");
static_assert(bksge::inv_sqrtpi != 0.0, "");
static_assert(bksge::ln2        != 0.0, "");
static_assert(bksge::ln10       != 0.0, "");
static_assert(bksge::sqrt2      != 0.0, "");
static_assert(bksge::sqrt3      != 0.0, "");
static_assert(bksge::inv_sqrt3  != 0.0, "");
static_assert(bksge::egamma     != 0.0, "");
static_assert(bksge::phi        != 0.0, "");

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(bksge::e_v<float>          != 0.0, "");
static_assert(bksge::log2e_v<float>      != 0.0, "");
static_assert(bksge::log10e_v<float>     != 0.0, "");
static_assert(bksge::pi_v<float>         != 0.0, "");
static_assert(bksge::inv_pi_v<float>     != 0.0, "");
static_assert(bksge::inv_sqrtpi_v<float> != 0.0, "");
static_assert(bksge::ln2_v<float>        != 0.0, "");
static_assert(bksge::ln10_v<float>       != 0.0, "");
static_assert(bksge::sqrt2_v<float>      != 0.0, "");
static_assert(bksge::sqrt3_v<float>      != 0.0, "");
static_assert(bksge::inv_sqrt3_v<float>  != 0.0, "");
static_assert(bksge::egamma_v<float>     != 0.0, "");
static_assert(bksge::phi_v<float>        != 0.0, "");

static_assert(bksge::e_v<double>          != 0.0, "");
static_assert(bksge::log2e_v<double>      != 0.0, "");
static_assert(bksge::log10e_v<double>     != 0.0, "");
static_assert(bksge::pi_v<double>         != 0.0, "");
static_assert(bksge::inv_pi_v<double>     != 0.0, "");
static_assert(bksge::inv_sqrtpi_v<double> != 0.0, "");
static_assert(bksge::ln2_v<double>        != 0.0, "");
static_assert(bksge::ln10_v<double>       != 0.0, "");
static_assert(bksge::sqrt2_v<double>      != 0.0, "");
static_assert(bksge::sqrt3_v<double>      != 0.0, "");
static_assert(bksge::inv_sqrt3_v<double>  != 0.0, "");
static_assert(bksge::egamma_v<double>     != 0.0, "");
static_assert(bksge::phi_v<double>        != 0.0, "");

static_assert(bksge::e_v<long double>          != 0.0, "");
static_assert(bksge::log2e_v<long double>      != 0.0, "");
static_assert(bksge::log10e_v<long double>     != 0.0, "");
static_assert(bksge::pi_v<long double>         != 0.0, "");
static_assert(bksge::inv_pi_v<long double>     != 0.0, "");
static_assert(bksge::inv_sqrtpi_v<long double> != 0.0, "");
static_assert(bksge::ln2_v<long double>        != 0.0, "");
static_assert(bksge::ln10_v<long double>       != 0.0, "");
static_assert(bksge::sqrt2_v<long double>      != 0.0, "");
static_assert(bksge::sqrt3_v<long double>      != 0.0, "");
static_assert(bksge::inv_sqrt3_v<long double>  != 0.0, "");
static_assert(bksge::egamma_v<long double>     != 0.0, "");
static_assert(bksge::phi_v<long double>        != 0.0, "");
#endif

template <typename T>
void ETest(double error)
{
	EXPECT_NEAR((double)bksge::e_t<T>(), (double)bksge::exp(T(1)), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::e_v<T>, bksge::e_t<T>());
#endif
}

GTEST_TEST(NumbersTest, ETest)
{
	ETest<float>(0.0);
	ETest<double>(0.0);
	ETest<long double>(0.0);
}

template <typename T>
void Log2eTest(double error)
{
	EXPECT_NEAR((double)bksge::log2e_t<T>(), (double)bksge::log2(bksge::e_t<T>()), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::log2e_v<T>, bksge::log2e_t<T>());
#endif
}

GTEST_TEST(NumbersTest, Log2eTest)
{
	Log2eTest<float>(0.0);
	Log2eTest<double>(0.0);
	Log2eTest<long double>(0.0);
}

template <typename T>
void Log10eTest(double error)
{
	EXPECT_NEAR((double)bksge::log10e_t<T>(), (double)bksge::log10(bksge::e_t<T>()), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::log10e_v<T>, bksge::log10e_t<T>());
#endif
}

GTEST_TEST(NumbersTest, Log10eTest)
{
	Log10eTest<float>(0.0000001);
	Log10eTest<double>(0.0);
	Log10eTest<long double>(0.0);
}

template <typename T>
void PiTest(double error)
{
	EXPECT_NEAR((double)bksge::pi_t<T>(), (double)acos(T(-1)), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::pi_v<T>, bksge::pi_t<T>());
#endif
}

GTEST_TEST(NumbersTest, PiTest)
{
	PiTest<float>(0.0000001);
	PiTest<double>(0.0);
	PiTest<long double>(0.0);
}

template <typename T>
void InvPiTest(double error)
{
	EXPECT_NEAR(1.0, (double)(bksge::inv_pi_t<T>() * bksge::pi_t<T>()), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::inv_pi_v<T>, bksge::inv_pi_t<T>());
#endif
}

GTEST_TEST(NumbersTest, InvPiTest)
{
	InvPiTest<float>(0.0);
	InvPiTest<double>(0.0);
	InvPiTest<long double>(0.0);
}

template <typename T>
void InvSqrtPiTest(double error)
{
	EXPECT_NEAR((double)bksge::inv_sqrtpi_t<T>(), (double)(T(1) / bksge::sqrt(bksge::pi_t<T>())), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::inv_sqrtpi_v<T>, bksge::inv_sqrtpi_t<T>());
#endif
}

GTEST_TEST(NumbersTest, InvSqrtPiTest)
{
	InvSqrtPiTest<float>(0.0000001);
	InvSqrtPiTest<double>(0.0);
	InvSqrtPiTest<long double>(0.0);
}

template <typename T>
void Ln2Test(double error)
{
	EXPECT_NEAR((double)bksge::ln2_t<T>(), (double)bksge::log(T(2)), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::ln2_v<T>, bksge::ln2_t<T>());
#endif
}

GTEST_TEST(NumbersTest, Ln2Test)
{
	Ln2Test<float>(0.0);
	Ln2Test<double>(0.0);
	Ln2Test<long double>(0.0);
}

template <typename T>
void Ln10Test(double error)
{
	EXPECT_NEAR((double)bksge::ln10_t<T>(), (double)bksge::log(T(10)), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::ln10_v<T>, bksge::ln10_t<T>());
#endif
}

GTEST_TEST(NumbersTest, Ln10Test)
{
	Ln10Test<float>(0.0);
	Ln10Test<double>(0.0);
	Ln10Test<long double>(0.0);
}

template <typename T>
void Sqrt2Test(double error)
{
	EXPECT_NEAR((double)bksge::sqrt2_t<T>(), (double)bksge::sqrt(T(2)), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::sqrt2_v<T>, bksge::sqrt2_t<T>());
#endif
}

GTEST_TEST(NumbersTest, Sqrt2Test)
{
	Sqrt2Test<float>(0.0);
	Sqrt2Test<double>(0.0);
	Sqrt2Test<long double>(0.0);
}

template <typename T>
void Sqrt3Test(double error)
{
	EXPECT_NEAR((double)bksge::sqrt3_t<T>(), (double)bksge::sqrt(T(3)), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::sqrt3_v<T>, bksge::sqrt3_t<T>());
#endif
}

GTEST_TEST(NumbersTest, Sqrt3Test)
{
	Sqrt3Test<float>(0.0);
	Sqrt3Test<double>(0.0);
	Sqrt3Test<long double>(0.0);
}

template <typename T>
void InvSqrt3Test(double error)
{
	EXPECT_NEAR((double)bksge::inv_sqrt3_t<T>(), (double)(T(1) / bksge::sqrt(T(3))), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::inv_sqrt3_v<T>, bksge::inv_sqrt3_t<T>());
#endif
}

GTEST_TEST(NumbersTest, InvSqrt3Test)
{
	InvSqrt3Test<float>(0.0000001);
	InvSqrt3Test<double>(0.0000001);
	InvSqrt3Test<long double>(0.0000001);
}

template <typename T>
void EGammaTest(double error)
{
	// TODO オイラー定数を動的に計算する方法がわからない
	EXPECT_NEAR((double)bksge::egamma_t<T>(), 0.5772156649015328606065120900824024310421593359399235988057672348848677267776646709369470632917467495, error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::egamma_v<T>, bksge::egamma_t<T>());
#endif
}

GTEST_TEST(NumbersTest, EGammaTest)
{
	EGammaTest<float>(0.0000001);
	EGammaTest<double>(0.0);
	EGammaTest<long double>(0.0);
}

template <typename T>
void PhiTest(double error)
{
	EXPECT_NEAR((double)bksge::phi_t<T>(), (double)((T(1) + bksge::sqrt(T(5))) / T(2)), error);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)
	EXPECT_EQ(bksge::phi_v<T>, bksge::phi_t<T>());
#endif
}

GTEST_TEST(NumbersTest, PhiTest)
{
	PhiTest<float>(0.0);
	PhiTest<double>(0.0);
	PhiTest<long double>(0.0);
}

}	// namespace bksge_numbers_test
