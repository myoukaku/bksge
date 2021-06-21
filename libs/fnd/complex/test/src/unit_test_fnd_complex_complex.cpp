/**
 *	@file	unit_test_fnd_complex_complex.cpp
 *
 *	@brief	complex のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/complex/complex.hpp>
#include <bksge/fnd/cmath/fabs.hpp>
#include <bksge/fnd/cmath/isnan.hpp>
#include <bksge/fnd/cmath/iszero.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"
#include "complex_test_utility.hpp"

BKSGE_WARNING_DISABLE_MSVC(4056);

namespace bksge_complex_test
{

namespace complex_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using complexf = bksge::complex<float>;
using complexd = bksge::complex<double>;
using complexl = bksge::complex<long double>;

using ComplexTestTypes = ::testing::Types<int, float, double, long double>;
using ComplexTestFloatTypes = ::testing::Types<float, double, long double>;

template <typename T>
class ComplexTest : public ::testing::Test {};
template <typename T>
class ComplexFloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(ComplexTest, ComplexTestTypes);
TYPED_TEST_SUITE(ComplexFloatTest, ComplexTestFloatTypes);

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ValueCtorTest()
{
	using complex = bksge::complex<T>;
	// (1) complex(const T& re = T(), const T& im = T())
	{
		complex const c;
		VERIFY(c.real() == T(0));
		VERIFY(c.imag() == T(0));
	}
	{
		complex const c{};
		VERIFY(c.real() == T(0));
		VERIFY(c.imag() == T(0));
	}
	{
		complex const c={};
		VERIFY(c.real() == T(0));
		VERIFY(c.imag() == T(0));
	}
	{
		complex const c(T(1));
		VERIFY(c.real() == T(1));
		VERIFY(c.imag() == T(0));
	}
	{
		complex const c{T(-2), T(3)};
		VERIFY(c.real() == T(-2));
		VERIFY(c.imag() == T(3));
	}
	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyCtorTest()
{
	using complex = bksge::complex<T>;
	// (2) complex(const complex& other)
	{
		complex const c1(3, -4);
		complex const c2(c1);
		VERIFY(c2.real() == T(3));
		VERIFY(c2.imag() == T(-4));
	}
	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ConvertCtorTest()
{
	using complex = bksge::complex<T>;
	// (3) complex(const complex<X>& other);
	{
		complexf const c1(3, -4);
		complex  const c2(c1);
		VERIFY(c2.real() == T(3));
		VERIFY(c2.imag() == T(-4));
	}
	{
		complexd const c1(4, 5);
		complex  const c2(c1);
		VERIFY(c2.real() == T(4));
		VERIFY(c2.imag() == T(5));
	}
	{
		complexl const c1(-5, -6);
		complex  const c2(c1);
		VERIFY(c2.real() == T(-5));
		VERIFY(c2.imag() == T(-6));
	}
	return true;
}

TYPED_TEST(ComplexTest, CtorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ValueCtorTest<TypeParam>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyCtorTest<TypeParam>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ConvertCtorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ValueAssignTest()
{
	using complex = bksge::complex<T>;
	// complex& operator=(const T& x);
	{
		complex c(1, 2);
		VERIFY(c.real() == T(1));
		VERIFY(c.imag() == T(2));
		auto t = c = T(3);
		static_assert(bksge::is_same<decltype(t), complex>::value, "");
		VERIFY(c.real() == T(3));
		VERIFY(c.imag() == T(0));
		VERIFY(t == c);
	}
	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using complex = bksge::complex<T>;
	// complex& operator=(const complex& cx);
	{
		complex c(1, 2);
		VERIFY(c.real() == T(1));
		VERIFY(c.imag() == T(2));
		auto t = c = complex(3, 4);
		static_assert(bksge::is_same<decltype(t), complex>::value, "");
		VERIFY(c.real() == T(3));
		VERIFY(c.imag() == T(4));
		VERIFY(t == c);
	}
	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ConvertAssignTest()
{
	using complex = bksge::complex<T>;
	// complex& operator=(const complex<X>& cx);
	{
		complex c(1, 2);
		VERIFY(c.real() == T(1));
		VERIFY(c.imag() == T(2));
		auto t1 = c = complexf(3, 4);
		static_assert(bksge::is_same<decltype(t1), complex>::value, "");
		VERIFY(c.real() == T(3));
		VERIFY(c.imag() == T(4));
		VERIFY(t1 == c);
		auto t2 = c = complexd(5, 6);
		static_assert(bksge::is_same<decltype(t2), complex>::value, "");
		VERIFY(c.real() == T(5));
		VERIFY(c.imag() == T(6));
		VERIFY(t2 == c);
		auto t3 = c = complexl(7, 8);
		static_assert(bksge::is_same<decltype(t3), complex>::value, "");
		VERIFY(c.real() == T(7));
		VERIFY(c.imag() == T(8));
		VERIFY(t3 == c);
	}
	return true;
}

TYPED_TEST(ComplexTest, AssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ValueAssignTest<TypeParam>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ConvertAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool RealImagTest()
{
	using complex = bksge::complex<T>;
	// complex& operator=(const complex<X>& cx);
	{
		complex c(1, 2);
		VERIFY(c.real() == T(1));
		VERIFY(c.imag() == T(2));
		VERIFY(bksge::real(c) == T(1));
		VERIFY(bksge::imag(c) == T(2));
		c.real(3);
		c.imag(4);
		VERIFY(c.real() == T(3));
		VERIFY(c.imag() == T(4));
		VERIFY(bksge::real(c) == T(3));
		VERIFY(bksge::imag(c) == T(4));
	}
	VERIFY(bksge::real(T(2)) == T(2));
	VERIFY(bksge::imag(T(2)) == T(0));
	return true;
}

TYPED_TEST(ComplexTest, RealImagTest)
{
	using T = TypeParam;
	using complex = bksge::complex<T>;

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RealImagTest<T>());

	// Array-oriented access
	{
		complex z(2, 3);
		auto x = reinterpret_cast<T(&)[2]>(z)[0];
		auto y = reinterpret_cast<T(&)[2]>(z)[1];
		EXPECT_EQ(x, z.real());
		EXPECT_EQ(y, z.imag());
	}
	{
		complex a[] =
		{
			{1, 2},
			{3, 4},
			{5, 6},
		};

		auto x0 = reinterpret_cast<T*>(a)[2*0 + 0];
		auto y0 = reinterpret_cast<T*>(a)[2*0 + 1];
		auto x1 = reinterpret_cast<T*>(a)[2*1 + 0];
		auto y1 = reinterpret_cast<T*>(a)[2*1 + 1];
		auto x2 = reinterpret_cast<T*>(a)[2*2 + 0];
		auto y2 = reinterpret_cast<T*>(a)[2*2 + 1];
		EXPECT_EQ(x0, a[0].real());
		EXPECT_EQ(y0, a[0].imag());
		EXPECT_EQ(x1, a[1].real());
		EXPECT_EQ(y1, a[1].imag());
		EXPECT_EQ(x2, a[2].real());
		EXPECT_EQ(y2, a[2].imag());
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool UnaryPlusMinusTest()
{
	using complex = bksge::complex<T>;

	{
		complex const c1(1, -2);

		// complex operator+(const complex<T>& val);
		auto c2 = +c1;
		static_assert(bksge::is_same<decltype(c2), complex>::value, "");
		VERIFY(c2.real() == T(1));
		VERIFY(c2.imag() == T(-2));

		// complex operator-(const complex<T>& val);
		auto c3 = -c1;
		static_assert(bksge::is_same<decltype(c3), complex>::value, "");
		VERIFY(c3.real() == T(-1));
		VERIFY(c3.imag() == T(2));
	}
	return true;
}

TYPED_TEST(ComplexTest, UnaryPlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(UnaryPlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddAssignTest()
{
	using complex = bksge::complex<T>;
	// complex& operator+=(const T& other);
	{
		complex c(1, 2);
		auto t = c += 3;
		static_assert(bksge::is_same<decltype(t), complex>::value, "");
		VERIFY(c.real() == T(4));
		VERIFY(c.imag() == T(2));
		VERIFY(t == c);
	}
	// complex& operator+=(const complex<X>& other);
	{
		complex c(1, 2);
		auto t1 = c += complexf(3, 4);
		static_assert(bksge::is_same<decltype(t1), complex>::value, "");
		VERIFY(c.real() == T(4));
		VERIFY(c.imag() == T(6));
		VERIFY(t1 == c);
		auto t2 = c += complexd(-1, 3);
		static_assert(bksge::is_same<decltype(t2), complex>::value, "");
		VERIFY(c.real() == T(3));
		VERIFY(c.imag() == T(9));
		VERIFY(t2 == c);
		auto t3 = c += complexl(2, -2);
		static_assert(bksge::is_same<decltype(t3), complex>::value, "");
		VERIFY(c.real() == T(5));
		VERIFY(c.imag() == T(7));
		VERIFY(t3 == c);
	}
	return true;
}

TYPED_TEST(ComplexTest, AddAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubAssignTest()
{
	using complex = bksge::complex<T>;
	// complex& operator-=(const T& other);
	{
		complex c(1, 2);
		auto t = c -= 3;
		static_assert(bksge::is_same<decltype(t), complex>::value, "");
		VERIFY(c.real() == T(-2));
		VERIFY(c.imag() == T(2));
		VERIFY(t == c);
	}
	// complex& operator-=(const complex<X>& other);
	{
		complex c(1, 2);
		auto t1 = c -= complexf(3, 4);
		static_assert(bksge::is_same<decltype(t1), complex>::value, "");
		VERIFY(c.real() == T(-2));
		VERIFY(c.imag() == T(-2));
		VERIFY(t1 == c);
		auto t2 = c -= complexd(-1, 3);
		static_assert(bksge::is_same<decltype(t2), complex>::value, "");
		VERIFY(c.real() == T(-1));
		VERIFY(c.imag() == T(-5));
		VERIFY(t2 == c);
		auto t3 = c -= complexl(2, -1);
		static_assert(bksge::is_same<decltype(t3), complex>::value, "");
		VERIFY(c.real() == T(-3));
		VERIFY(c.imag() == T(-4));
		VERIFY(t3 == c);
	}
	return true;
}

TYPED_TEST(ComplexTest, SubAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulAssignTest()
{
	using complex = bksge::complex<T>;
	// complex& operator*=(const T& other);
	{
		complex c(2, 3);
		auto t = c *= 3;
		static_assert(bksge::is_same<decltype(t), complex>::value, "");
		VERIFY(c.real() == T(6));
		VERIFY(c.imag() == T(9));
		VERIFY(t == c);
	}
	// complex& operator*=(const complex<X>& other);
	{
		complex c(1, 2);
		auto t1 = c *= complexf(3, 4);
		static_assert(bksge::is_same<decltype(t1), complex>::value, "");
		VERIFY(c.real() == T(-5));	// (1*3)-(2*4)
		VERIFY(c.imag() == T(10));	// (1*4)+(2*3)
		VERIFY(t1 == c);
		auto t2 = c *= complexd(-1, 3);
		static_assert(bksge::is_same<decltype(t2), complex>::value, "");
		VERIFY(c.real() == T(-25));	// (-5*-1)-(10*3)
		VERIFY(c.imag() == T(-25));	// (-5*3)+(10*-1)
		VERIFY(t2 == c);
		auto t3 = c *= complexl(2, -1);
		static_assert(bksge::is_same<decltype(t3), complex>::value, "");
		VERIFY(c.real() == T(-75));	// (-25*2)-(-25*-1)
		VERIFY(c.imag() == T(-25));	// (-25*-1)+(-25*2)
		VERIFY(t3 == c);
	}
	return true;
}

TYPED_TEST(ComplexTest, MulAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivAssignTest()
{
	using complex = bksge::complex<T>;

	double error = 0.0000001;

	// complex& operator/=(const T& other);
	{
		complex c(4, 6);
		auto t = c /= 2;
		static_assert(bksge::is_same<decltype(t), complex>::value, "");
		VERIFY(c.real() == T(2));
		VERIFY(c.imag() == T(3));
		VERIFY(t == c);
	}
	// complex& operator/=(const complex<X>& other);
	{
		complex c(2, 3);
		auto t = c /= complexf(4, 5);
		static_assert(bksge::is_same<decltype(t), complex>::value, "");
		VERIFY(IsNear(c.real(), T(0.560975609756097561), error));
		VERIFY(IsNear(c.imag(), T(0.048780487804878048), error));
		VERIFY(t == c);
	}
	{
		complex c(-3, 4);
		auto t = c /= complexd(5, -6);
		static_assert(bksge::is_same<decltype(t), complex>::value, "");
		VERIFY(IsNear(c.real(), T(-0.639344262295081967), error));
		VERIFY(IsNear(c.imag(), T( 0.032786885245901639), error));
		VERIFY(t == c);
	}
	{
		complex c(4, -5);
		auto t = c /= complexl(-6, -7);
		static_assert(bksge::is_same<decltype(t), complex>::value, "");
		VERIFY(IsNear(c.real(), T(0.129411764705882353), error));
		VERIFY(IsNear(c.imag(), T(0.682352941176470588), error));
		VERIFY(t == c);
	}
	return true;
}

TYPED_TEST(ComplexFloatTest, DivAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using complex = bksge::complex<T>;
	// complex<T> operator+(const complex<T>& lhs, const complex<T>& rhs);
	{
		auto c = complex(1, 2) + complex(3, 4);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(c.real() == T(4));
		VERIFY(c.imag() == T(6));
	}
	// complex<T> operator+(const complex<T>& lhs, const T& rhs);
	{
		auto c = complex(2, 3) + T(4);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(c.real() == T(6));
		VERIFY(c.imag() == T(3));
	}
	// complex<T> operator+(const T& lhs, const complex<T>& rhs);
	{
		auto c = T(3) + complex(4, 5);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(c.real() == T(7));
		VERIFY(c.imag() == T(5));
	}
	return true;
}

TYPED_TEST(ComplexTest, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using complex = bksge::complex<T>;
	// complex<T> operator-(const complex<T>& lhs, const complex<T>& rhs);
	{
		auto c = complex(4, 5) - complex(2, 1);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(c.real() == T(2));
		VERIFY(c.imag() == T(4));
	}
	// complex<T> operator-(const complex<T>& lhs, const T& rhs);
	{
		auto c = complex(5, 6) - T(1);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(c.real() == T(4));
		VERIFY(c.imag() == T(6));
	}
	// complex<T> operator-(const T& lhs, const complex<T>& rhs);
	{
		auto c = T(2) - complex(6, 7);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(c.real() == T(-4));
		VERIFY(c.imag() == T(-7));
	}
	return true;
}

TYPED_TEST(ComplexTest, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulTest()
{
	using complex = bksge::complex<T>;
	// complex<T> operator*(const complex<T>& lhs, const complex<T>& rhs);
	{
		auto c = complex(1, 2) * complex(3, 4);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(c.real() == T(-5));
		VERIFY(c.imag() == T(10));
	}
	// complex<T> operator*(const complex<T>& lhs, const T& rhs);
	{
		auto c = complex(3, 1) * T(4);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(c.real() == T(12));
		VERIFY(c.imag() == T(4));
	}
	// complex<T> operator*(const T& lhs, const complex<T>& rhs);
	{
		auto c = T(5) * complex(1, 5);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(c.real() == T(5));
		VERIFY(c.imag() == T(25));
	}
	return true;
}

TYPED_TEST(ComplexTest, MulTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivTest()
{
	using complex = bksge::complex<T>;

	auto const max = std::numeric_limits<T>::max();
	double const error = 0.0000001;

	// complex<T> operator/(const complex<T>& lhs, const complex<T>& rhs);
	{
		auto c = complex(1, 2) / complex(3, 4);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(IsNear(c.real(), T(0.44), error));
		VERIFY(IsNear(c.imag(), T(0.08), error));
	}
	{
		auto c = complex(1, 2) / complex(4, -3);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(IsNear(c.real(), T(-0.08), error));
		VERIFY(IsNear(c.imag(), T( 0.44), error));
	}
	{
		auto c = complex(1, 0) / complex(max/2, max/2);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(!bksge::iszero(c.real()));
		VERIFY(!bksge::iszero(c.imag()));
		VERIFY(!bksge::isnan(c.real()));
		VERIFY(!bksge::isnan(c.imag()));
	}
	// complex<T> operator/(const complex<T>& lhs, const T& rhs);
	{
		auto c = complex(3, 1) / T(4);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(IsNear(c.real(), T(0.75), error));
		VERIFY(IsNear(c.imag(), T(0.25), error));
	}
	// complex<T> operator/(const T& lhs, const complex<T>& rhs);
	{
		auto c = T(5) / complex(1, 5);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(IsNear(c.real(), T(0.192307692307692308), error));
		VERIFY(IsNear(c.imag(), T(-0.961538461538461539), error));
	}
	return true;
}

template <typename T>
inline bool DivTest2()
{
	using complex = bksge::complex<T>;

	auto const nan = std::numeric_limits<T>::quiet_NaN();
	auto const inf = std::numeric_limits<T>::infinity();
	{
		auto c = complex(1, 2) / complex(inf, inf);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(bksge::isnan(c.real()));
		VERIFY(bksge::isnan(c.imag()));
	}
	{
		auto c = complex(1, 0) / complex(inf, nan);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(bksge::isnan(c.real()));
		VERIFY(bksge::isnan(c.imag()));
	}
	{
		auto c = complex(1, 2) / complex(0, 0);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(bksge::isnan(c.real()));
		VERIFY(bksge::isnan(c.imag()));
	}
	{
		auto c = complex(inf, nan) / complex(1, 2);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(bksge::isnan(c.real()));
		VERIFY(bksge::isnan(c.imag()));
	}
	{
		auto c = complex(1, 2) / complex(nan, 1);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(bksge::isnan(c.real()));
		VERIFY(bksge::isnan(c.imag()));
	}
	{
		auto c = complex(1, 2) / complex(1, nan);
		static_assert(bksge::is_same<decltype(c), complex>::value, "");
		VERIFY(bksge::isnan(c.real()));
		VERIFY(bksge::isnan(c.imag()));
	}
	return true;
}

TYPED_TEST(ComplexFloatTest, DivTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivTest<TypeParam>());
	EXPECT_TRUE(DivTest2<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ComparisonTest()
{
	using complex = bksge::complex<T>;
	complex const c1{1,2};
	complex const c2{1,2};
	complex const c3{-1,2};
	complex const c4{1,3};

	VERIFY( (c1 == c1));
	VERIFY( (c1 == c2));
	VERIFY(!(c1 == c3));
	VERIFY(!(c1 == c4));

	VERIFY(!(c1 != c1));
	VERIFY(!(c1 != c2));
	VERIFY( (c1 != c3));
	VERIFY( (c1 != c4));

	VERIFY( (complex(2,0) == T(2)));
	VERIFY(!(complex(2,1) == T(2)));
	VERIFY(!(complex(2,0) == T(3)));

	VERIFY(!(complex(2,0) != T(2)));
	VERIFY( (complex(2,1) != T(2)));
	VERIFY( (complex(2,0) != T(3)));

	VERIFY( (T(2) == complex(2,0)));
	VERIFY(!(T(2) == complex(2,1)));
	VERIFY(!(T(3) == complex(2,0)));

	VERIFY(!(T(2) != complex(2,0)));
	VERIFY( (T(2) != complex(2,1)));
	VERIFY( (T(3) != complex(2,0)));

	return true;
}

TYPED_TEST(ComplexTest, ComparisonTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ComparisonTest<TypeParam>());
}

TYPED_TEST(ComplexTest, OutputStreamTest)
{
	using complex = bksge::complex<TypeParam>;

	{
		complex const c{1,2};
		bksge::stringstream ss;
		ss << c;
		EXPECT_EQ("(1,2)", ss.str());
	}
	{
		complex const c{-3,4};
		bksge::wstringstream ss;
		ss << c;
		EXPECT_EQ(L"(-3,4)", ss.str());
	}
}

TYPED_TEST(ComplexTest, InputStreamTest)
{
	using complex = bksge::complex<TypeParam>;

	{
		bksge::stringstream ss;
		ss << "(1,2)";

		complex c;
		ss >> c;
		EXPECT_TRUE(c == complex(1,2));
	}
	{
		bksge::stringstream ss;
		ss << "3";

		complex c;
		ss >> c;
		EXPECT_TRUE(c == complex(3,0));
	}
	{
		bksge::wstringstream ss;
		ss << L"(-4)";

		complex c;
		ss >> c;
		EXPECT_TRUE(c == complex(-4,0));
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AbsTest()
{
	using complex = bksge::complex<T>;

	auto const max = std::numeric_limits<T>::max();
	double const error = 0.0000001;
	{
		complex const c{1,2};
		VERIFY(IsNear(bksge::abs(c), T(2.2360679774997897), error));
	}
	{
		complex const c{-2,3};
		VERIFY(IsNear(bksge::abs(c), T(3.60555127546398929), error));
	}
	{
		complex const c{0,0};
		VERIFY(IsNear(bksge::abs(c), T(0), error));
	}
	{
		complex const c{max,0};
		VERIFY(IsNear(bksge::abs(c), T(max), error));
	}
	{
		complex const c{0,max};
		VERIFY(IsNear(bksge::abs(c), T(max), error));
	}
	{
		auto const l = max / 2;
		complex const c{l,l};
		VERIFY(IsNear(bksge::abs(c), T(l * 1.4142135623730952), error));
	}
	return true;
}
TYPED_TEST(ComplexFloatTest, AbsTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(AbsTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ArgTest()
{
	using complex = bksge::complex<T>;

	double error = 0.0000001;
	{
		complex const c{1,0};
		VERIFY(IsNear(bksge::arg(c), T(0), error));
	}
	{
		complex const c{0,1};
		VERIFY(IsNear(bksge::arg(c), T(1.57079632679), error));
	}
	{
		complex const c{-1,0};
		VERIFY(IsNear(bksge::arg(c), T(3.14159265358), error));
	}
	{
		VERIFY(IsNear(bksge::arg(T(2)), T(0), error));
	}
	{
		VERIFY(IsNear(bksge::arg(T(-2)), T(3.14159265358), error));
	}
	{
		VERIFY(IsNear(bksge::arg(3), 0.0, error));
	}
	{
		VERIFY(IsNear(bksge::arg(-3), 3.14159265358, error));
	}
	return true;
}
TYPED_TEST(ComplexFloatTest, ArgTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ArgTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NormTest()
{
	using complex = bksge::complex<T>;

	{
		complex const c{1,0};
		VERIFY(bksge::norm(c) == T(1));
	}
	{
		complex const c{2,-3};
		VERIFY(bksge::norm(c) == T(13));
	}
	{
		complex const c{-3,-4};
		VERIFY(bksge::norm(c) == T(25));
	}
	{
		VERIFY(bksge::norm(T(3)) == T(9));
	}
	return true;
}
TYPED_TEST(ComplexTest, NormTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NormTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ConjTest()
{
	using complex = bksge::complex<T>;

	{
		complex const c{1,0};
		VERIFY(bksge::conj(c) == complex(1, 0));
	}
	{
		complex const c{2,3};
		VERIFY(bksge::conj(c) == complex(2,-3));
	}
	{
		complex const c{-3,-4};
		VERIFY(bksge::conj(c) == complex(-3, 4));
	}
	{
		VERIFY(bksge::conj(T(3)) == complex(3,0));
	}
	return true;
}
TYPED_TEST(ComplexFloatTest, ConjTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ConjTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ProjTest()
{
	using complex = bksge::complex<T>;

	auto inf = std::numeric_limits<T>::infinity();
	{
		complex const c{1, 2};
		VERIFY(bksge::proj(c) == complex(1, 2));
	}
	{
		complex const c{-2, 3};
		VERIFY(bksge::proj(c) == complex(-2, 3));
	}
	{
		complex const c{inf, 3};
		VERIFY(bksge::proj(c) == complex(inf, 0));
	}
	{
		complex const c{inf, -3};
		VERIFY(bksge::proj(c) == complex(inf, -0));
	}
	{
		complex const c{0, -inf};
		VERIFY(bksge::proj(c) == complex(inf, -0));
	}
	{
		VERIFY(bksge::proj(T(3)) == complex(3, 0));
	}
	return true;
}
TYPED_TEST(ComplexFloatTest, ProjTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ProjTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PolarTest()
{
	using complex = bksge::complex<T>;

	const T half_pi = T(1.57079632679);
	const double error = 0.0000001;
	VERIFY(IsNear(bksge::polar(T(1), half_pi * T(0.0)), complex( 1, 0), error));
	VERIFY(IsNear(bksge::polar(T(1), half_pi * T(1.0)), complex( 0, 1), error));
	VERIFY(IsNear(bksge::polar(T(1), half_pi * T(2.0)), complex(-1, 0), error));
	VERIFY(IsNear(bksge::polar(T(1), half_pi * T(3.0)), complex( 0,-1), error));

	return true;
}
TYPED_TEST(ComplexFloatTest, PolarTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(PolarTest<TypeParam>());
}

inline BKSGE_CXX14_CONSTEXPR bool LiteralsTest()
{
#if defined(BKSGE_USE_STD_COMPLEX)
#define COMPLEX_LITERALS_NAMESPACE std
#else
#define COMPLEX_LITERALS_NAMESPACE bksge
#endif
	{
		using namespace COMPLEX_LITERALS_NAMESPACE::literals::complex_literals;
		auto c = 1.0if;
		static_assert(bksge::is_same<decltype(c), bksge::complex<float>>::value, "");
		VERIFY(c.real() == 0.0f);
		VERIFY(c.imag() == 1.0f);
	}
	{
		using namespace COMPLEX_LITERALS_NAMESPACE::literals;
		auto c = 2.0f+3.0if;
		static_assert(bksge::is_same<decltype(c), bksge::complex<float>>::value, "");
		VERIFY(c.real() == 2.0f);
		VERIFY(c.imag() == 3.0f);
	}
	{
		using namespace COMPLEX_LITERALS_NAMESPACE::complex_literals;
		auto c = 2.0i;
		static_assert(bksge::is_same<decltype(c), bksge::complex<double>>::value, "");
		VERIFY(c.real() == 0.0);
		VERIFY(c.imag() == 2.0);
	}
	{
		using namespace COMPLEX_LITERALS_NAMESPACE::literals::complex_literals;
		auto c = 3.0-1.0i;
		static_assert(bksge::is_same<decltype(c), bksge::complex<double>>::value, "");
		VERIFY(c.real() ==  3.0);
		VERIFY(c.imag() == -1.0);
	}
	{
		using namespace COMPLEX_LITERALS_NAMESPACE::literals;
		auto c = -3.0il;
		static_assert(bksge::is_same<decltype(c), bksge::complex<long double>>::value, "");
		VERIFY(c.real() ==  0.0);
		VERIFY(c.imag() == -3.0);
	}
	{
		using namespace COMPLEX_LITERALS_NAMESPACE::complex_literals;
		auto c = -4.0l+2.0il;
		static_assert(bksge::is_same<decltype(c), bksge::complex<long double>>::value, "");
		VERIFY(c.real() == -4.0);
		VERIFY(c.imag() ==  2.0);
	}
	return true;
}

GTEST_TEST(ComplexTest, LiteralsTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(LiteralsTest());
}

}	// namespace complex_test

}	// namespace bksge_complex_test
