/**
 *	@file	unit_test_core_math_matrix3x4.cpp
 *
 *	@brief	Matrix3x4 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/matrix3x4.hpp>
#include <bksge/core/math/matrix4x4.hpp>
#include <bksge/core/math/matrix4x3.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/fnd/cmath/degrees_to_radians.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <tuple>
#include <functional>
#include <vector>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace matrix3x4_test
{

using Matrix3x4f = bksge::math::Matrix3x4<float>;
using Matrix3x4i = bksge::math::Matrix3x4<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathMatrix3x4Test : public ::testing::Test {};
template <typename T>
class MathMatrix3x4FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathMatrix3x4Test, MathTestTypes);
TYPED_TEST_SUITE(MathMatrix3x4FloatTest, MathFloatTestTypes);

TYPED_TEST(MathMatrix3x4Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

	static_assert(sizeof(Matrix3x4) == sizeof(T) * 12, "");
	static_assert(bksge::is_default_constructible<Matrix3x4>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Matrix3x4>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Matrix3x4>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][3]);
	}
}

TYPED_TEST(MathMatrix3x4Test, VectorConstructTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(!bksge::is_constructible<Matrix3x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_constructible<Matrix3x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix3x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_implicitly_constructible<Matrix3x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, Vector4>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v1(1,  2,  3,  4);
		BKSGE_CONSTEXPR_OR_CONST Vector4 v2(5,  6,  7,  8);
		BKSGE_CONSTEXPR_OR_CONST Vector4 v3(9, 10, 11, 12);
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m(v1, v2, v3);
		BKSGE_CONSTEXPR_EXPECT_EQ( 1, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 2, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 3, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, m[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 5, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 6, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 7, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 8, m[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 9, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, m[2][3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m
		{
			Vector4{10, 11, 12, 13},
			Vector4{20, 21, 22, 23},
			Vector4{30, 31, 32, 33},
		};
		BKSGE_CONSTEXPR_EXPECT_EQ(10, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, m[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(20, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(21, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(22, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(23, m[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(30, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(31, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(33, m[2][3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m =
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		BKSGE_CONSTEXPR_EXPECT_EQ(11, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(14, m[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(21, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(22, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(23, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(24, m[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(31, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(33, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(34, m[2][3]);
	}
}

TYPED_TEST(MathMatrix3x4Test, CopyConstructTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(bksge::is_constructible<Matrix3x4,  Matrix3x4  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x4,  Matrix3x4i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x4,  Matrix3x4f const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x4i, Matrix3x4  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x4i, Matrix3x4i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x4i, Matrix3x4f const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x4f, Matrix3x4  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x4f, Matrix3x4i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x4f, Matrix3x4f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Matrix3x4,  Matrix3x4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x4,  Matrix3x4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x4,  Matrix3x4f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x4i, Matrix3x4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x4i, Matrix3x4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x4i, Matrix3x4f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x4f, Matrix3x4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x4f, Matrix3x4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x4f, Matrix3x4f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Matrix3x4,  Matrix3x4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x4,  Matrix3x4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x4,  Matrix3x4f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x4i, Matrix3x4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x4i, Matrix3x4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x4i, Matrix3x4f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x4f, Matrix3x4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x4f, Matrix3x4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x4f, Matrix3x4f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Matrix3x4  m1
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x4  m2{m1};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x4i m3{m2};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x4f m4{m2};

	BKSGE_CONSTEXPR_EXPECT_EQ(11, m3[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, m3[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, m3[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(14, m3[0][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(21, m3[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(22, m3[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(23, m3[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(24, m3[1][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(31, m3[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(32, m3[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(33, m3[2][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(34, m3[2][3]);

	BKSGE_CONSTEXPR_EXPECT_EQ(11, m4[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, m4[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, m4[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(14, m4[0][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(21, m4[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(22, m4[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(23, m4[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(24, m4[1][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(31, m4[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(32, m4[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(33, m4[2][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(34, m4[2][3]);
}

TYPED_TEST(MathMatrix3x4Test, CopyAssignTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix3x4  m1
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
	};
	Matrix3x4  m2;

	EXPECT_EQ(Vector4(11, 12, 13, 14), m1[0]);
	EXPECT_EQ(Vector4(21, 22, 23, 24), m1[1]);
	EXPECT_EQ(Vector4(31, 32, 33, 34), m1[2]);

	EXPECT_EQ(Vector4(0, 0, 0, 0), m2[0]);
	EXPECT_EQ(Vector4(0, 0, 0, 0), m2[1]);
	EXPECT_EQ(Vector4(0, 0, 0, 0), m2[2]);

	m1 = Matrix3x4
	{
		Vector4{51, 52, 53, 54},
		Vector4{61, 62, 63, 64},
		Vector4{71, 72, 73, 74},
	};

	EXPECT_EQ(Vector4(51, 52, 53, 54), m1[0]);
	EXPECT_EQ(Vector4(61, 62, 63, 64), m1[1]);
	EXPECT_EQ(Vector4(71, 72, 73, 74), m1[2]);

	m2 = Matrix3x4i
	{
		Vector4{1,  2,  3,  4},
		Vector4{5,  6,  7,  8},
		Vector4{9, 10, 11, 12},
	};

	EXPECT_EQ(Vector4(1,  2,  3,  4), m2[0]);
	EXPECT_EQ(Vector4(5,  6,  7,  8), m2[1]);
	EXPECT_EQ(Vector4(9, 10, 11, 12), m2[2]);

	m1 = m2 = Matrix3x4f
	{
		Vector4{10, 11, 12, 13},
		Vector4{20, 21, 22, 23},
		Vector4{30, 31, 32, 33},
	};

	EXPECT_EQ(Vector4(10, 11, 12, 13), m1[0]);
	EXPECT_EQ(Vector4(20, 21, 22, 23), m1[1]);
	EXPECT_EQ(Vector4(30, 31, 32, 33), m1[2]);

	EXPECT_EQ(Vector4(10, 11, 12, 13), m2[0]);
	EXPECT_EQ(Vector4(20, 21, 22, 23), m2[1]);
	EXPECT_EQ(Vector4(30, 31, 32, 33), m2[2]);
}

TYPED_TEST(MathMatrix3x4Test, IndexAccessTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix3x4  m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};

		m[0][0] = 50;
		m[1] = Vector4(51, 52, 53, 54);
		m[2][1] = 55;

		EXPECT_EQ(Vector4(50, 12, 13, 14), m[0]);
		EXPECT_EQ(Vector4(51, 52, 53, 54), m[1]);
		EXPECT_EQ(Vector4(31, 55, 33, 34), m[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), m[2]);
	}
}

TYPED_TEST(MathMatrix3x4Test, AtTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix3x4  m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};

		m.at(0).at(0) = 50;
		m.at(1) = Vector4(51, 52, 53, 54);
		m.at(2).at(1) = 55;

		EXPECT_EQ(Vector4(50, 12, 13, 14), m.at(0));
		EXPECT_EQ(Vector4(51, 52, 53, 54), m.at(1));
		EXPECT_EQ(Vector4(31, 55, 33, 34), m.at(2));
		EXPECT_THROW((void)m.at(0).at(4), bksge::out_of_range);
		EXPECT_THROW((void)m.at(3), bksge::out_of_range);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), m.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), m.at(2));
		EXPECT_THROW((void)m.at(0).at(4), bksge::out_of_range);
		EXPECT_THROW((void)m.at(3), bksge::out_of_range);
	}
}

TYPED_TEST(MathMatrix3x4Test, DataTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		auto p = m.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(Vector4(11, 12, 13, 14), *p);
		*p = Vector4{51, 52, 53, 54};
		++p;
		EXPECT_EQ(Vector4(21, 22, 23, 24), *p);
		++p;
		EXPECT_EQ(Vector4(31, 32, 33, 34), *p);
		*p = Vector4{61, 62, 63, 64};

		EXPECT_EQ(Vector4(51, 52, 53, 54), m[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), m[1]);
		EXPECT_EQ(Vector4(61, 62, 63, 64), m[2]);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		BKSGE_STATIC_CONSTEXPR auto p = m.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), p[2]);
	}
#endif
}

TYPED_TEST(MathMatrix3x4Test, IteratorTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// begin, end (non const)
	{
		Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		auto it = m.begin();
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector4(11, 12, 13, 14), *it);
		*it++ = Vector4{51, 52, 53, 54};
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector4(21, 22, 23, 24), *it);
		*++it = Vector4{61, 62, 63, 64};
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector4(61, 62, 63, 64), *it);
		it++;
		EXPECT_TRUE(it == m.end());

		EXPECT_EQ(Vector4(51, 52, 53, 54), m[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), m[1]);
		EXPECT_EQ(Vector4(61, 62, 63, 64), m[2]);
	}
	// begin, end (const)
	{
		const Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		auto it = m.begin();
		EXPECT_TRUE(it != m.end());

		EXPECT_EQ(Vector4(11, 12, 13, 14), it[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), it[1]);
		EXPECT_EQ(Vector4(31, 32, 33, 34), it[2]);

		EXPECT_EQ(Vector4(11, 12, 13, 14), *it++);
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *++it);
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector4(21, 22, 23, 24), *--it);
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector4(21, 22, 23, 24), *it--);
		EXPECT_TRUE(it != m.end());
		it += 2;
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *it);
		it -= 2;
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector4(11, 12, 13, 14), *it);
		it += 3;
		EXPECT_TRUE(it == m.end());
	}
	// cbegin, cend
	{
		const Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		auto it = m.cbegin();
		EXPECT_TRUE(it != m.cend());

		EXPECT_EQ(Vector4(11, 12, 13, 14), it[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), it[1]);
		EXPECT_EQ(Vector4(31, 32, 33, 34), it[2]);

		EXPECT_EQ(Vector4(11, 12, 13, 14), *it++);
		EXPECT_TRUE(it != m.cend());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *++it);
		EXPECT_TRUE(it != m.cend());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *it++);
		EXPECT_TRUE(it == m.cend());
	}
#if !defined(BKSGE_GCC)
	// begin, end (constexpr)
	{
		BKSGE_STATIC_CONSTEXPR Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		BKSGE_CONSTEXPR_OR_CONST auto it = m.begin();
		BKSGE_CONSTEXPR_EXPECT_TRUE(it != m.end());

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), it[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), it[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), it[2]);

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), *it);
		BKSGE_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it2 != m.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), *it2);
		BKSGE_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it3 != m.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), *it3);
		BKSGE_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), *it4);
		BKSGE_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 == m.end());
	}
#endif
}

TYPED_TEST(MathMatrix3x4Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// rbegin, rend (non const)
	{
		Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		auto it = m.rbegin();
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *it);
		*it++ = Vector4{51, 52, 53, 54};
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(21, 22, 23, 24), *it);
		*++it = Vector4{61, 62, 63, 64};
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(61, 62, 63, 64), *it);
		it++;
		EXPECT_TRUE(it == m.rend());

		EXPECT_EQ(Vector4(61, 62, 63, 64), m[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), m[1]);
		EXPECT_EQ(Vector4(51, 52, 53, 54), m[2]);
	}
	// rbegin, rend (const)
	{
		const Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		auto it = m.rbegin();
		EXPECT_TRUE(it != m.rend());

		EXPECT_EQ(Vector4(31, 32, 33, 34), it[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), it[1]);
		EXPECT_EQ(Vector4(11, 12, 13, 14), it[2]);

		EXPECT_EQ(Vector4(31, 32, 33, 34), *it++);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(11, 12, 13, 14), *++it);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(21, 22, 23, 24), *--it);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(21, 22, 23, 24), *it--);
		EXPECT_TRUE(it != m.rend());
		it += 2;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(11, 12, 13, 14), *it);
		it -= 2;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *it);
		it += 3;
		EXPECT_TRUE(it == m.rend());
	}
	// crbegin, crend
	{
		const Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		auto it = m.crbegin();
		EXPECT_TRUE(it != m.crend());

		EXPECT_EQ(Vector4(31, 32, 33, 34), it[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), it[1]);
		EXPECT_EQ(Vector4(11, 12, 13, 14), it[2]);

		EXPECT_EQ(Vector4(31, 32, 33, 34), *it++);
		EXPECT_TRUE(it != m.crend());
		EXPECT_EQ(Vector4(11, 12, 13, 14), *++it);
		EXPECT_TRUE(it != m.crend());
		EXPECT_EQ(Vector4(11, 12, 13, 14), *it++);
		EXPECT_TRUE(it == m.crend());
	}
#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201603)
	// rbegin, rend (constexpr)
	{
		BKSGE_CXX17_STATIC_CONSTEXPR Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = m.rbegin();
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it != m.rend());

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), it[0]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), it[1]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), it[2]);

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), *it);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it2 != m.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), *it2);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it3 != m.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), *it3);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), *it4);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 == m.rend());
	}
#endif
}

TYPED_TEST(MathMatrix3x4Test, EmptyTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

	Matrix3x4 m1{};
	const           Matrix3x4 m2{};
	BKSGE_CONSTEXPR Matrix3x4 m3{};
	EXPECT_FALSE(m1.empty());
	EXPECT_FALSE(m2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(m3.empty());
}

TYPED_TEST(MathMatrix3x4Test, SizeTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

	Matrix3x4 m1{};
	const           Matrix3x4 m2{};
	BKSGE_CONSTEXPR Matrix3x4 m3{};
	EXPECT_EQ(3u, m1.size());
	EXPECT_EQ(3u, m2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, m3.size());
}

TYPED_TEST(MathMatrix3x4Test, MaxSizeTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

	Matrix3x4 m1{};
	const           Matrix3x4 m2{};
	BKSGE_CONSTEXPR Matrix3x4 m3{};
	EXPECT_EQ(3u, m1.max_size());
	EXPECT_EQ(3u, m2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, m3.max_size());
}

TYPED_TEST(MathMatrix3x4Test, NameAccessTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix3x4 m1
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		EXPECT_EQ(Vector4(11, 12, 13, 14), m1.x());
		EXPECT_EQ(Vector4(21, 22, 23, 24), m1.y());
		EXPECT_EQ(Vector4(31, 32, 33, 34), m1.z());
		EXPECT_EQ(11, m1.x().x());
		EXPECT_EQ(12, m1.x().y());
		EXPECT_EQ(13, m1.x().z());
		EXPECT_EQ(14, m1.x().w());
		m1.x() = Vector4{0, 1, 2, 3};
		m1.z() = Vector4{4, 5, 6, 7};

		EXPECT_EQ(Vector4(0, 1, 2, 3), m1[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), m1[1]);
		EXPECT_EQ(Vector4(4, 5, 6, 7), m1[2]);

		m1.x().y() = -1;
		m1.y().x() = -2;

		EXPECT_EQ(Vector4(0, -1, 2, 3), m1[0]);
		EXPECT_EQ(Vector4(-2, 22, 23, 24), m1[1]);
		EXPECT_EQ(Vector4(4, 5, 6, 7), m1[2]);
	}

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2
		{
			Vector4{51, 52, 53, 54},
			Vector4{61, 62, 63, 64},
			Vector4{71, 72, 73, 74},
		};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(51, 52, 53, 54), m2.x());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(61, 62, 63, 64), m2.y());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(71, 72, 73, 74), m2.z());
		BKSGE_CONSTEXPR_EXPECT_EQ(51, m2.x().x());
		BKSGE_CONSTEXPR_EXPECT_EQ(52, m2.x().y());
		BKSGE_CONSTEXPR_EXPECT_EQ(53, m2.x().z());
		BKSGE_CONSTEXPR_EXPECT_EQ(54, m2.x().w());
		BKSGE_CONSTEXPR_EXPECT_EQ(71, m2.z().x());
		BKSGE_CONSTEXPR_EXPECT_EQ(72, m2.z().y());
		BKSGE_CONSTEXPR_EXPECT_EQ(73, m2.z().z());
		BKSGE_CONSTEXPR_EXPECT_EQ(74, m2.z().w());
	}
}

TYPED_TEST(MathMatrix3x4Test, SwizzleTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
	};

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2{m.yzx()};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m2[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2{m.xyzx()};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), m2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m2[3]);
	}
}

TYPED_TEST(MathMatrix3x4Test, SwapTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix3x4 m1
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
	};
	Matrix3x4 m2
	{
		Vector4{51, 52, 53, 54},
		Vector4{61, 62, 63, 64},
		Vector4{71, 72, 73, 74},
	};

	EXPECT_EQ(Vector4(11, 12, 13, 14), m1[0]);
	EXPECT_EQ(Vector4(21, 22, 23, 24), m1[1]);
	EXPECT_EQ(Vector4(31, 32, 33, 34), m1[2]);
	EXPECT_EQ(Vector4(51, 52, 53, 54), m2[0]);
	EXPECT_EQ(Vector4(61, 62, 63, 64), m2[1]);
	EXPECT_EQ(Vector4(71, 72, 73, 74), m2[2]);

	m1.swap(m2);

	EXPECT_EQ(Vector4(51, 52, 53, 54), m1[0]);
	EXPECT_EQ(Vector4(61, 62, 63, 64), m1[1]);
	EXPECT_EQ(Vector4(71, 72, 73, 74), m1[2]);
	EXPECT_EQ(Vector4(11, 12, 13, 14), m2[0]);
	EXPECT_EQ(Vector4(21, 22, 23, 24), m2[1]);
	EXPECT_EQ(Vector4(31, 32, 33, 34), m2[2]);

	swap(m1, m2);

	EXPECT_EQ(Vector4(11, 12, 13, 14), m1[0]);
	EXPECT_EQ(Vector4(21, 22, 23, 24), m1[1]);
	EXPECT_EQ(Vector4(31, 32, 33, 34), m1[2]);
	EXPECT_EQ(Vector4(51, 52, 53, 54), m2[0]);
	EXPECT_EQ(Vector4(61, 62, 63, 64), m2[1]);
	EXPECT_EQ(Vector4(71, 72, 73, 74), m2[2]);
}

TYPED_TEST(MathMatrix3x4Test, PlusMinusTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix3x4 m1
		{
			Vector4{-11,  12,  13,  14},
			Vector4{ 21,  22, -23,  24},
			Vector4{ 31, -32,  33,  34},
		};
		Matrix3x4 m2 = +m1;
		Matrix3x4 m3 = -m1;

		EXPECT_EQ(Vector4(-11,  12,  13,  14), m2[0]);
		EXPECT_EQ(Vector4( 21,  22, -23,  24), m2[1]);
		EXPECT_EQ(Vector4( 31, -32,  33,  34), m2[2]);
		EXPECT_EQ(Vector4( 11, -12, -13, -14), m3[0]);
		EXPECT_EQ(Vector4(-21, -22,  23, -24), m3[1]);
		EXPECT_EQ(Vector4(-31,  32, -33, -34), m3[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m1
		{
			Vector4{-11,  12,  13,  14},
			Vector4{ 21,  22, -23,  24},
			Vector4{ 31, -32,  33,  34},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2 = +m1;
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m3 = -m1;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-11,  12,  13,  14), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 21,  22, -23,  24), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 31, -32,  33,  34), m2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 11, -12, -13, -14), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-21, -22,  23, -24), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-31,  32, -33, -34), m3[2]);
	}
}

TYPED_TEST(MathMatrix3x4Test, AddTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix3x4 += Matrix3x4
	{
		Matrix3x4 m1;

		Matrix3x4 t = m1 += Matrix3x4
		{
			Vector4{1,  2,  3,  4},
			Vector4{5,  6,  7,  8},
			Vector4{9, 10, 11, 12},
		};

		EXPECT_EQ(Vector4(1,  2,  3,  4), m1[0]);
		EXPECT_EQ(Vector4(5,  6,  7,  8), m1[1]);
		EXPECT_EQ(Vector4(9, 10, 11, 12), m1[2]);
		EXPECT_EQ(t, m1);
	}

	// Matrix3x4 + Matrix3x4 -> Matrix3x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m1
		{
			Vector4{-21,  22,  23,  30},
			Vector4{ 24, -25,  26,  31},
			Vector4{ 27,  28, -29,  32},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2
		{
			Vector4{ 31,  32, -33,  40},
			Vector4{ 34, -35,  36, -41},
			Vector4{-37,  38,  39,  42},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m3 = m1 + m2;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 10,  54, -10,  70), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 58, -60,  62, -10), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-10,  66,  10,  74), m3[2]);
	}
}

TYPED_TEST(MathMatrix3x4Test, SubTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix3x4 -= Matrix3x4
	{
		Matrix3x4 m1;
		Matrix3x4 t = m1 -= Matrix3x4
		{
			Vector4{1,  2,  3,  4},
			Vector4{5,  6,  7,  8},
			Vector4{9, 10, 11, 12},
		};

		EXPECT_EQ(Vector4(-1,  -2,  -3,  -4), m1[0]);
		EXPECT_EQ(Vector4(-5,  -6,  -7,  -8), m1[1]);
		EXPECT_EQ(Vector4(-9, -10, -11, -12), m1[2]);
		EXPECT_EQ(t, m1);
	}

	// Matrix3x4 - Matrix3x4 -> Matrix3x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m1
		{
			Vector4{10, 11, 12, 13},
			Vector4{20, 21, 22, 23},
			Vector4{30, 31, 32, 33},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2
		{
			Vector4{0, 9, 1, 2},
			Vector4{8, 4, 7, 9},
			Vector4{6, 5, 3, 1},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m3 = m1 - m2;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(10,  2, 11, 11), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(12, 17, 15, 14), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(24, 26, 29, 32), m3[2]);
	}
}

TYPED_TEST(MathMatrix3x4Test, MulScalarTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix3x4 *= スカラー
	{
		Matrix3x4 m1
		{
			Vector4{1,  2,  3,  4},
			Vector4{5,  6,  7,  8},
			Vector4{9, 10, 11, 12},
		};
		{
			Matrix3x4 t = (m1 *= 2);
			EXPECT_EQ(Vector4( 2,  4,  6,  8), m1[0]);
			EXPECT_EQ(Vector4(10, 12, 14, 16), m1[1]);
			EXPECT_EQ(Vector4(18, 20, 22, 24), m1[2]);
			EXPECT_EQ(t, m1);
		}
		{
			Matrix3x4 t = (m1 *= 2.5);
			EXPECT_EQ(Vector4( 5, 10, 15, 20), m1[0]);
			EXPECT_EQ(Vector4(25, 30, 35, 40), m1[1]);
			EXPECT_EQ(Vector4(45, 50, 55, 60), m1[2]);
			EXPECT_EQ(t, m1);
		}
	}

	// Matrix3x4 * スカラー -> Matrix3x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m1
		{
			Vector4{10, 12, 14, 16},
			Vector4{20, 22, 24, 26},
			Vector4{30, 32, 34, 36},
		};
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix3x4 t = m1 * 3;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(30, 36, 42, 48), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(60, 66, 72, 78), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(90, 96,102,108), t[2]);
		}
		{
			const Matrix3x4 t = m1 * 2.5;
			EXPECT_EQ(Vector4(25, 30, 35, 40), t[0]);
			EXPECT_EQ(Vector4(50, 55, 60, 65), t[1]);
			EXPECT_EQ(Vector4(75, 80, 85, 90), t[2]);
		}
		// スカラー * Matrix3x4 -> Matrix3x4
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix3x4 t = 4 * m1;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 40, 48, 56, 64), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 80, 88, 96,104), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(120,128,136,144), t[2]);
		}
		{
			const Matrix3x4 t = -1.5 * m1;
			EXPECT_EQ(Vector4(-15, -18, -21, -24), t[0]);
			EXPECT_EQ(Vector4(-30, -33, -36, -39), t[1]);
			EXPECT_EQ(Vector4(-45, -48, -51, -54), t[2]);
		}
	}
}

TYPED_TEST(MathMatrix3x4Test, MulMatrixTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix3x4 m
	{
		Vector4{  2,  4,  6,  8 },
		Vector4{ 10, 12, 14, 16 },
		Vector4{ 18, 20, 22, 24 },
	};

	// Matrix3x4 *= Matrix4x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
		{
			Vector4{  11, -12,  13,  14 },
			Vector4{  21,  22, -23,  24 },
			Vector4{ -31,  32,  33,  34 },
			Vector4{  41,  42,  43, -44 },
		};

		auto t = m *= m1;
		static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
		EXPECT_EQ(Vector4(248,  592,  476, -24), m[0]);
		EXPECT_EQ(Vector4(584, 1264, 1004, 200), m[1]);
		EXPECT_EQ(Vector4(920, 1936, 1532, 424), m[2]);
		EXPECT_EQ(t, m);
	}

	// Matrix3x4 * Matrix4x4 -> Matrix3x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m1
		{
			Vector4{  15,   3,  -7,   4 },
			Vector4{  11,   4,  12,  -8 },
			Vector4{   2,   6,  13,  10 },
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2
		{
			Vector4{   1,   2,   3,   4 },
			Vector4{   5,   6,   7,   8 },
			Vector4{   9,  10, -11, -12 },
			Vector4{  13, -14,  15,  16 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), const Matrix3x4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(  19,  -78,  203,  232), t1[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(  35,  278, -191, -196), t1[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 279,   30,   55,   60), t1[2]);
	}

	// Matrix3x4 * Matrix4x3 -> Matrix3x3
	// Matrix4x3 * Matrix3x4 -> Matrix4x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m1
		{
			Vector4{  1,  2,  3,  4 },
			Vector4{  5,  6,  7,  8 },
			Vector4{  9, 10, 11, 12 },
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2
		{
			Vector3{ 11, 12, 13 },
			Vector3{ 21, 22, 23 },
			Vector3{ 31, 32, 33 },
			Vector3{ 41, 42, 43 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), const Matrix3x3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 310, 320, 330), t1[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 726, 752, 778), t1[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1142,1184,1226), t1[2]);

		BKSGE_CONSTEXPR_OR_CONST auto t2 = m2 * m1;
		static_assert(bksge::is_same<decltype(t2), const Matrix4x4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(188, 224, 260, 296), t2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(338, 404, 470, 536), t2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(488, 584, 680, 776), t2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(638, 764, 890,1016), t2[3]);
	}
}

TYPED_TEST(MathMatrix3x4Test, MulVectorTest)
{
	using Matrix3x4 = bksge::math::Matrix3x4<TypeParam>;
	using Vector3 = bksge::math::Vector3<TypeParam>;
	using Vector4 = bksge::math::Vector4<TypeParam>;

	// Vector3 * Matrix3x4 -> Vector4
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v { 1, 2, 3 };
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m
		{
			Vector4{   1,  -2,   3,   4 },
			Vector4{   5,   6,   7,   8 },
			Vector4{   9,  10, -11, -12 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t = v * m;
		static_assert(bksge::is_same<decltype(t), const Vector4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(38, 40, -16, -16), t);
	}
}

TYPED_TEST(MathMatrix3x4Test, DivScalarTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix3x4 /= スカラー
	{
		Matrix3x4 m1
		{
			Vector4{10, 12, 14, 16},
			Vector4{18, 20, 22, 24},
			Vector4{26, 28, 30, 32},
		};

		{
			Matrix3x4 t = (m1 /= 2);
			EXPECT_EQ(Vector4( 5,  6,  7,  8), m1[0]);
			EXPECT_EQ(Vector4( 9, 10, 11, 12), m1[1]);
			EXPECT_EQ(Vector4(13, 14, 15, 16), m1[2]);
			EXPECT_EQ(t, m1);
		}
		{
			Matrix3x4 t = (m1 /= 0.5);
			EXPECT_EQ(Vector4(10, 12, 14, 16), m1[0]);
			EXPECT_EQ(Vector4(18, 20, 22, 24), m1[1]);
			EXPECT_EQ(Vector4(26, 28, 30, 32), m1[2]);
			EXPECT_EQ(t, m1);
		}
	}

	// Matrix3x4 / スカラー
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m1
		{
			Vector4{10, 12, 14, 16},
			Vector4{20, 22, 24, 26},
			Vector4{30, 32, 34, 36},
		};

		{
			BKSGE_CONSTEXPR_OR_CONST Matrix3x4 t = m1 / 2;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 5,  6,  7,  8), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(10, 11, 12, 13), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(15, 16, 17, 18), t[2]);
		}
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix3x4 t = m1 / 0.25;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 40,  48,  56,  64), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 80,  88,  96, 104), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(120, 128, 136, 144), t[2]);
		}
	}
}

TYPED_TEST(MathMatrix3x4Test, CompareTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix3x4  m1
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x4  m2
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x4  m3
	{
		Vector4{10, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x4  m4
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 23, 23, 24},
		Vector4{31, 32, 33, 34},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x4  m5
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, -33, 34},
	};

	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 == m1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 == m2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 == m3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 == m4);
	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 == m5);

	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 != m1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 != m2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 != m3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 != m4);
	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 != m5);
}

TYPED_TEST(MathMatrix3x4Test, OutputStreamTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix3x4 const m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};
		std::stringstream ss;
		ss << m;
		EXPECT_EQ("{ { 11, 12, 13, 14 }, { 21, 22, 23, 24 }, { 31, 32, 33, 34 } }", ss.str());
	}
	{
		Matrix3x4 const m
		{
			Vector4{51, 52, 53, 54},
			Vector4{61, 62, 63, 64},
			Vector4{71, 72, 73, 74},
		};
		std::wstringstream ss;
		ss << m;
		EXPECT_EQ(L"{ { 51, 52, 53, 54 }, { 61, 62, 63, 64 }, { 71, 72, 73, 74 } }", ss.str());
	}
}

TYPED_TEST(MathMatrix3x4Test, TupleElementTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(bksge::is_same<typename std::tuple_element<0, Matrix3x4>::type, Vector4>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<1, Matrix3x4>::type, Vector4>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<2, Matrix3x4>::type, Vector4>::value, "");
}

TYPED_TEST(MathMatrix3x4Test, TupleGetTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};

		EXPECT_EQ(Vector4(11, 12, 13, 14), bksge::get<0>(m));
		EXPECT_EQ(Vector4(21, 22, 23, 24), bksge::get<1>(m));
		EXPECT_EQ(Vector4(31, 32, 33, 34), bksge::get<2>(m));

		bksge::get<0>(m) = Vector4{51, 52, 53, 54};

		EXPECT_EQ(Vector4(51, 52, 53, 54), m[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), m[1]);
		EXPECT_EQ(Vector4(31, 32, 33, 34), m[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), bksge::get<0>(m));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), bksge::get<1>(m));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), bksge::get<2>(m));
	}
}

TYPED_TEST(MathMatrix3x4Test, TupleSizeTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

	static_assert(std::tuple_size<Matrix3x4>::value == 3, "");
}

TYPED_TEST(MathMatrix3x4Test, ZeroTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix3x4::Zero();
		static_assert(bksge::is_same<decltype(m), const Matrix3x4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 0, 0), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 0, 0), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 0, 0), m[2]);
	}
	{
		const auto m = Matrix3x4::Zero();
		static_assert(bksge::is_same<decltype(m), const Matrix3x4>::value, "");
		EXPECT_EQ(Vector4(0, 0, 0, 0), m[0]);
		EXPECT_EQ(Vector4(0, 0, 0, 0), m[1]);
		EXPECT_EQ(Vector4(0, 0, 0, 0), m[2]);
	}
}

TYPED_TEST(MathMatrix3x4Test, IdentityTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix3x4::Identity();
		static_assert(bksge::is_same<decltype(m), const Matrix3x4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 0, 0, 0), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 1, 0, 0), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 1, 0), m[2]);
	}
	{
		const auto m = Matrix3x4::Identity();
		static_assert(bksge::is_same<decltype(m), const Matrix3x4>::value, "");
		EXPECT_EQ(Vector4(1, 0, 0, 0), m[0]);
		EXPECT_EQ(Vector4(0, 1, 0, 0), m[1]);
		EXPECT_EQ(Vector4(0, 0, 1, 0), m[2]);
	}
}

TYPED_TEST(MathMatrix3x4Test, TransposedTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m1
	{
		Vector4{ 11, 12, 13, 14 },
		Vector4{ 21, 22, 23, 24 },
		Vector4{ 31, 32, 33, 34 },
	};

	BKSGE_CONSTEXPR_OR_CONST auto m2 = Transposed(m1);
	static_assert(bksge::is_same<decltype(m2), const Matrix4x3>::value, "");
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 21, 31), m2[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(12, 22, 32), m2[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(13, 23, 33), m2[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(14, 24, 34), m2[3]);

	const auto m3 = Transposed(m2);
	static_assert(bksge::is_same<decltype(m3), const Matrix3x4>::value, "");
	EXPECT_EQ(Vector4(11, 12, 13, 14), m3[0]);
	EXPECT_EQ(Vector4(21, 22, 23, 24), m3[1]);
	EXPECT_EQ(Vector4(31, 32, 33, 34), m3[2]);

	EXPECT_EQ(m1, m3);
}

TYPED_TEST(MathMatrix3x4Test, ResizedTest)
{
	using Matrix4x4 = bksge::math::Matrix4x4<TypeParam>;
	using Matrix4x3 = bksge::math::Matrix4x3<TypeParam>;
	using Matrix3x4 = bksge::math::Matrix3x4<TypeParam>;
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;
	using Vector4 = bksge::math::Vector4<TypeParam>;
	using Vector3 = bksge::math::Vector3<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
		{
			Vector3{ 1, 2, 3 },
			Vector3{ 4, 5, 6 },
			Vector3{ 7, 8, 9 },
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2 = bksge::math::Resized<3, 4>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 expected
		{
			Vector4{ 1, 2, 3, 0 },
			Vector4{ 4, 5, 6, 0 },
			Vector4{ 7, 8, 9, 0 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m2);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m1
		{
			Vector3{ 10, 11, 12 },
			Vector3{ 20, 21, 22 },
			Vector3{ 30, 31, 32 },
			Vector3{ 40, 41, 42 },
		};

		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2 = bksge::math::Resized<3, 4>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 expected
		{
			Vector4{ 10, 11, 12, 0 },
			Vector4{ 20, 21, 22, 0 },
			Vector4{ 30, 31, 32, 0 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m2);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m1
		{
			Vector4{ 10, 11, 12, 13 },
			Vector4{ 20, 21, 22, 23 },
			Vector4{ 30, 31, 32, 33 },
		};

		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2 = bksge::math::Resized<3, 4>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 expected
		{
			Vector4{ 10, 11, 12, 13 },
			Vector4{ 20, 21, 22, 23 },
			Vector4{ 30, 31, 32, 33 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m2);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
		{
			Vector4{ 11, 12, 13, 14 },
			Vector4{ 21, 22, 23, 24 },
			Vector4{ 31, 32, 33, 34 },
			Vector4{ 41, 42, 43, 44 },
		};

		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2 = bksge::math::Resized<3, 4>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 expected
		{
			Vector4{ 11, 12, 13, 14 },
			Vector4{ 21, 22, 23, 24 },
			Vector4{ 31, 32, 33, 34 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m2);
	}
}

TYPED_TEST(MathMatrix3x4Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix3x4 const v
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
	};

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

TYPED_TEST(MathMatrix3x4Test, HashTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	std::hash<Matrix3x4> h;

	Matrix3x4 const m1
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
	};

	Matrix3x4 const m2
	{
		Vector4{12, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
	};

	Matrix3x4 const m3
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 21, 23, 24},
		Vector4{31, 32, 33, 34},
	};

	Matrix3x4 const m4
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 30},
	};

	Matrix3x4 const m5
	{
		Vector4{31, 32, 33, 34},
		Vector4{21, 22, 23, 24},
		Vector4{11, 12, 13, 14},
	};

	bksge::vector<bksge::size_t> v;
	v.push_back(h(m1));
	v.push_back(h(m2));
	v.push_back(h(m3));
	v.push_back(h(m4));
	v.push_back(h(m5));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(m1));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace matrix3x4_test

}	// namespace bksge_math_test
