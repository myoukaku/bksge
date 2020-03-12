/**
 *	@file	unit_test_core_math_matrix4x3.cpp
 *
 *	@brief	Matrix4x3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/matrix4x3.hpp>
#include <bksge/core/math/matrix4x4.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/matrix3x4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector4.hpp>
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
#include <functional>
#include <tuple>
#include <vector>
#include <sstream>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace matrix4x3_test
{

using Matrix4x3f = bksge::math::Matrix4x3<float>;
using Matrix4x3i = bksge::math::Matrix4x3<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathMatrix4x3Test : public ::testing::Test {};
template <typename T>
class MathMatrix4x3FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathMatrix4x3Test, MathTestTypes);
TYPED_TEST_SUITE(MathMatrix4x3FloatTest, MathFloatTestTypes);

TYPED_TEST(MathMatrix4x3Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

	static_assert(sizeof(Matrix4x3) == sizeof(T) * 12, "");
	static_assert(bksge::is_default_constructible<Matrix4x3>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Matrix4x3>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Matrix4x3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][2]);
	}
}

TYPED_TEST(MathMatrix4x3Test, VectorConstructTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(!bksge::is_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( bksge::is_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( bksge::is_implicitly_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, Vector3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v1( 1,  2,  3);
		BKSGE_CONSTEXPR_OR_CONST Vector3 v2( 4,  5,  6);
		BKSGE_CONSTEXPR_OR_CONST Vector3 v3( 7,  8,  9);
		BKSGE_CONSTEXPR_OR_CONST Vector3 v4(10, 11, 12);
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m(v1, v2, v3, v4);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(9, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, m[3][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m
		{
			Vector3{10, 11, 12},
			Vector3{20, 21, 22},
			Vector3{30, 31, 32},
			Vector3{40, 41, 42},
		};
		BKSGE_CONSTEXPR_EXPECT_EQ(10, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(20, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(21, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(22, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(30, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(31, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(40, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(41, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, m[3][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m =
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		BKSGE_CONSTEXPR_EXPECT_EQ(11, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(21, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(22, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(23, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(31, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(33, m[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(41, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(43, m[3][2]);
	}
}

TYPED_TEST(MathMatrix4x3Test, CopyConstructTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(bksge::is_constructible<Matrix4x3,  Matrix4x3  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x3,  Matrix4x3i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x3,  Matrix4x3f const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x3i, Matrix4x3  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x3i, Matrix4x3i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x3i, Matrix4x3f const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x3f, Matrix4x3  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x3f, Matrix4x3i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x3f, Matrix4x3f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Matrix4x3,  Matrix4x3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x3,  Matrix4x3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x3,  Matrix4x3f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x3i, Matrix4x3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x3i, Matrix4x3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x3i, Matrix4x3f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x3f, Matrix4x3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x3f, Matrix4x3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x3f, Matrix4x3f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Matrix4x3,  Matrix4x3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x3,  Matrix4x3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x3,  Matrix4x3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x3i, Matrix4x3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x3i, Matrix4x3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x3i, Matrix4x3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x3f, Matrix4x3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x3f, Matrix4x3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x3f, Matrix4x3f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Matrix4x3  m1
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3  m2{m1};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3i m3{m2};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3f m4{m2};

	BKSGE_CONSTEXPR_EXPECT_EQ(11, m3[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, m3[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, m3[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(21, m3[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(22, m3[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(23, m3[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(31, m3[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(32, m3[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(33, m3[2][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(41, m3[3][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(42, m3[3][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(43, m3[3][2]);

	BKSGE_CONSTEXPR_EXPECT_EQ(11, m4[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, m4[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, m4[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(21, m4[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(22, m4[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(23, m4[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(31, m4[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(32, m4[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(33, m4[2][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(41, m4[3][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(42, m4[3][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(43, m4[3][2]);
}

TYPED_TEST(MathMatrix4x3Test, CopyAssignTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix4x3  m1
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};
	Matrix4x3  m2;

	EXPECT_EQ(Vector3(11, 12, 13), m1[0]);
	EXPECT_EQ(Vector3(21, 22, 23), m1[1]);
	EXPECT_EQ(Vector3(31, 32, 33), m1[2]);
	EXPECT_EQ(Vector3(41, 42, 43), m1[3]);

	EXPECT_EQ(Vector3(0, 0, 0), m2[0]);
	EXPECT_EQ(Vector3(0, 0, 0), m2[1]);
	EXPECT_EQ(Vector3(0, 0, 0), m2[2]);
	EXPECT_EQ(Vector3(0, 0, 0), m2[3]);

	m1 = Matrix4x3
	{
		Vector3{51, 52, 53},
		Vector3{61, 62, 63},
		Vector3{71, 72, 73},
		Vector3{81, 82, 83},
	};

	EXPECT_EQ(Vector3(51, 52, 53), m1[0]);
	EXPECT_EQ(Vector3(61, 62, 63), m1[1]);
	EXPECT_EQ(Vector3(71, 72, 73), m1[2]);
	EXPECT_EQ(Vector3(81, 82, 83), m1[3]);

	m2 = Matrix4x3i
	{
		Vector3{ 1,  2,  3},
		Vector3{ 5,  6,  7},
		Vector3{ 9, 10, 11},
		Vector3{13, 14, 15},
	};

	EXPECT_EQ(Vector3( 1,  2,  3), m2[0]);
	EXPECT_EQ(Vector3( 5,  6,  7), m2[1]);
	EXPECT_EQ(Vector3( 9, 10, 11), m2[2]);
	EXPECT_EQ(Vector3(13, 14, 15), m2[3]);

	m1 = m2 = Matrix4x3f
	{
		Vector3{10, 11, 12},
		Vector3{20, 21, 22},
		Vector3{30, 31, 32},
		Vector3{40, 41, 42},
	};

	EXPECT_EQ(Vector3(10, 11, 12), m1[0]);
	EXPECT_EQ(Vector3(20, 21, 22), m1[1]);
	EXPECT_EQ(Vector3(30, 31, 32), m1[2]);
	EXPECT_EQ(Vector3(40, 41, 42), m1[3]);

	EXPECT_EQ(Vector3(10, 11, 12), m2[0]);
	EXPECT_EQ(Vector3(20, 21, 22), m2[1]);
	EXPECT_EQ(Vector3(30, 31, 32), m2[2]);
	EXPECT_EQ(Vector3(40, 41, 42), m2[3]);
}

TYPED_TEST(MathMatrix4x3Test, IndexAccessTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix4x3  m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};

		m[0][0] = 50;
		m[1] = Vector3(51, 52, 53);
		m[2][1] = 55;
		m[3][2] = 56;

		EXPECT_EQ(Vector3(50, 12, 13), m[0]);
		EXPECT_EQ(Vector3(51, 52, 53), m[1]);
		EXPECT_EQ(Vector3(31, 55, 33), m[2]);
		EXPECT_EQ(Vector3(41, 42, 56), m[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), m[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), m[3]);
	}
}

TYPED_TEST(MathMatrix4x3Test, AtTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix4x3  m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};

		m.at(0).at(0) = 50;
		m.at(1) = Vector3(51, 52, 53);
		m.at(2).at(1) = 55;
		m.at(3).at(2) = 56;

		EXPECT_EQ(Vector3(50, 12, 13), m.at(0));
		EXPECT_EQ(Vector3(51, 52, 53), m.at(1));
		EXPECT_EQ(Vector3(31, 55, 33), m.at(2));
		EXPECT_EQ(Vector3(41, 42, 56), m.at(3));
		EXPECT_THROW((void)m.at(0).at(3), bksge::out_of_range);
		EXPECT_THROW((void)m.at(4), bksge::out_of_range);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), m.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), m.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), m.at(2));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), m.at(3));
		EXPECT_THROW((void)m.at(0).at(3), bksge::out_of_range);
		EXPECT_THROW((void)m.at(4), bksge::out_of_range);
	}
}

TYPED_TEST(MathMatrix4x3Test, DataTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		auto p = m.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(Vector3(11, 12, 13), *p);
		*p = Vector3{51, 52, 53};
		++p;
		EXPECT_EQ(Vector3(21, 22, 23), *p);
		++p;
		EXPECT_EQ(Vector3(31, 32, 33), *p);
		*p = Vector3{61, 62, 63};
		++p;
		EXPECT_EQ(Vector3(41, 42, 43), *p);

		EXPECT_EQ(Vector3(51, 52, 53), m[0]);
		EXPECT_EQ(Vector3(21, 22, 23), m[1]);
		EXPECT_EQ(Vector3(61, 62, 63), m[2]);
		EXPECT_EQ(Vector3(41, 42, 43), m[3]);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		BKSGE_STATIC_CONSTEXPR auto p = m.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), p[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), p[3]);
	}
#endif
}

TYPED_TEST(MathMatrix4x3Test, IteratorTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// begin, end (non const)
	{
		Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		auto it = m.begin();
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector3(11, 12, 13), *it);
		*it++ = Vector3{51, 52, 53};
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector3(21, 22, 23), *it);
		*++it = Vector3{61, 62, 63};
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector3(61, 62, 63), *it);
		it++;
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector3(41, 42, 43), *it);
		it++;
		EXPECT_TRUE(it == m.end());

		EXPECT_EQ(Vector3(51, 52, 53), m[0]);
		EXPECT_EQ(Vector3(21, 22, 23), m[1]);
		EXPECT_EQ(Vector3(61, 62, 63), m[2]);
		EXPECT_EQ(Vector3(41, 42, 43), m[3]);
	}
	// begin, end (const)
	{
		const Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		auto it = m.begin();
		EXPECT_TRUE(it != m.end());

		EXPECT_EQ(Vector3(11, 12, 13), it[0]);
		EXPECT_EQ(Vector3(21, 22, 23), it[1]);
		EXPECT_EQ(Vector3(31, 32, 33), it[2]);
		EXPECT_EQ(Vector3(41, 42, 43), it[3]);

		EXPECT_EQ(Vector3(11, 12, 13), *it++);
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector3(31, 32, 33), *++it);
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector3(21, 22, 23), *--it);
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector3(21, 22, 23), *it--);
		EXPECT_TRUE(it != m.end());
		it += 2;
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector3(31, 32, 33), *it);
		it -= 2;
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector3(11, 12, 13), *it);
		it += 3;
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector3(41, 42, 43), *it);
		++it;
		EXPECT_TRUE(it == m.end());
	}
	// cbegin, cend
	{
		const Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		auto it = m.cbegin();
		EXPECT_TRUE(it != m.cend());

		EXPECT_EQ(Vector3(11, 12, 13), it[0]);
		EXPECT_EQ(Vector3(21, 22, 23), it[1]);
		EXPECT_EQ(Vector3(31, 32, 33), it[2]);
		EXPECT_EQ(Vector3(41, 42, 43), it[3]);

		EXPECT_EQ(Vector3(11, 12, 13), *it++);
		EXPECT_TRUE(it != m.cend());
		EXPECT_EQ(Vector3(31, 32, 33), *++it);
		EXPECT_TRUE(it != m.cend());
		EXPECT_EQ(Vector3(31, 32, 33), *it++);
		EXPECT_TRUE(it != m.cend());
		EXPECT_EQ(Vector3(41, 42, 43), *it++);
		EXPECT_TRUE(it == m.cend());
	}
#if !defined(BKSGE_GCC)
	// begin, end (constexpr)
	{
		BKSGE_STATIC_CONSTEXPR Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		BKSGE_CONSTEXPR_OR_CONST auto it = m.begin();
		BKSGE_CONSTEXPR_EXPECT_TRUE(it != m.end());

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), it[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), it[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), it[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), it[3]);

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), *it);
		BKSGE_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it2 != m.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), *it2);
		BKSGE_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it3 != m.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), *it3);
		BKSGE_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), *it4);
		BKSGE_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 != m.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), *it5);
		BKSGE_CONSTEXPR_OR_CONST auto it6 = it5 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it6 == m.end());
	}
#endif
}

TYPED_TEST(MathMatrix4x3Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// rbegin, rend (non const)
	{
		Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		auto it = m.rbegin();
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(41, 42, 43), *it);
		*it++ = Vector3{51, 52, 53};
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(31, 32, 33), *it);
		*++it = Vector3{61, 62, 63};
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(61, 62, 63), *it);
		it++;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(11, 12, 13), *it);
		it++;
		EXPECT_TRUE(it == m.rend());

		EXPECT_EQ(Vector3(11, 12, 13), m[0]);
		EXPECT_EQ(Vector3(61, 62, 63), m[1]);
		EXPECT_EQ(Vector3(31, 32, 33), m[2]);
		EXPECT_EQ(Vector3(51, 52, 53), m[3]);
	}
	// rbegin, rend (const)
	{
		const Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		auto it = m.rbegin();
		EXPECT_TRUE(it != m.rend());

		EXPECT_EQ(Vector3(41, 42, 43), it[0]);
		EXPECT_EQ(Vector3(31, 32, 33), it[1]);
		EXPECT_EQ(Vector3(21, 22, 23), it[2]);
		EXPECT_EQ(Vector3(11, 12, 13), it[3]);

		EXPECT_EQ(Vector3(41, 42, 43), *it++);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(21, 22, 23), *++it);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(31, 32, 33), *--it);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(31, 32, 33), *it--);
		EXPECT_TRUE(it != m.rend());
		it += 2;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(21, 22, 23), *it);
		it -= 2;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(41, 42, 43), *it);
		it += 3;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(11, 12, 13), *it);
		++it;
		EXPECT_TRUE(it == m.rend());
	}
	// crbegin, crend
	{
		const Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		auto it = m.crbegin();
		EXPECT_TRUE(it != m.crend());

		EXPECT_EQ(Vector3(41, 42, 43), it[0]);
		EXPECT_EQ(Vector3(31, 32, 33), it[1]);
		EXPECT_EQ(Vector3(21, 22, 23), it[2]);
		EXPECT_EQ(Vector3(11, 12, 13), it[3]);

		EXPECT_EQ(Vector3(41, 42, 43), *it++);
		EXPECT_TRUE(it != m.crend());
		EXPECT_EQ(Vector3(21, 22, 23), *++it);
		EXPECT_TRUE(it != m.crend());
		EXPECT_EQ(Vector3(21, 22, 23), *it++);
		EXPECT_TRUE(it != m.crend());
		EXPECT_EQ(Vector3(11, 12, 13), *it++);
		EXPECT_TRUE(it == m.crend());
	}
#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201603)
	// rbegin, rend (constexpr)
	{
		BKSGE_CXX17_STATIC_CONSTEXPR Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = m.rbegin();
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it != m.rend());

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), it[0]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), it[1]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), it[2]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), it[3]);

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), *it);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it2 != m.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), *it2);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it3 != m.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), *it3);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), *it4);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 != m.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), *it5);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it6 = it5 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it6 == m.rend());
	}
#endif
}

TYPED_TEST(MathMatrix4x3Test, EmptyTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

	Matrix4x3 m1{};
	const           Matrix4x3 m2{};
	BKSGE_CONSTEXPR Matrix4x3 m3{};
	EXPECT_FALSE(m1.empty());
	EXPECT_FALSE(m2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(m3.empty());
}

TYPED_TEST(MathMatrix4x3Test, SizeTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

	Matrix4x3 m1{};
	const           Matrix4x3 m2{};
	BKSGE_CONSTEXPR Matrix4x3 m3{};
	EXPECT_EQ(4u, m1.size());
	EXPECT_EQ(4u, m2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, m3.size());
}

TYPED_TEST(MathMatrix4x3Test, MaxSizeTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

	Matrix4x3 m1{};
	const           Matrix4x3 m2{};
	BKSGE_CONSTEXPR Matrix4x3 m3{};
	EXPECT_EQ(4u, m1.max_size());
	EXPECT_EQ(4u, m2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, m3.max_size());
}

TYPED_TEST(MathMatrix4x3Test, NameAccessTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix4x3 m1
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		EXPECT_EQ(Vector3(11, 12, 13), m1.x());
		EXPECT_EQ(Vector3(21, 22, 23), m1.y());
		EXPECT_EQ(Vector3(31, 32, 33), m1.z());
		EXPECT_EQ(Vector3(41, 42, 43), m1.w());
		EXPECT_EQ(11, m1.x().x());
		EXPECT_EQ(12, m1.x().y());
		EXPECT_EQ(13, m1.x().z());
		EXPECT_EQ(41, m1.w().x());
		EXPECT_EQ(42, m1.w().y());
		EXPECT_EQ(43, m1.w().z());
		m1.x() = Vector3{0, 1, 2};
		m1.z() = Vector3{4, 5, 6};

		EXPECT_EQ(Vector3( 0,  1,  2), m1[0]);
		EXPECT_EQ(Vector3(21, 22, 23), m1[1]);
		EXPECT_EQ(Vector3( 4,  5,  6), m1[2]);
		EXPECT_EQ(Vector3(41, 42, 43), m1[3]);

		m1.x().y() = -1;
		m1.y().x() = -2;
		m1.w().z() = -3;

		EXPECT_EQ(Vector3( 0, -1,  2), m1[0]);
		EXPECT_EQ(Vector3(-2, 22, 23), m1[1]);
		EXPECT_EQ(Vector3( 4,  5,  6), m1[2]);
		EXPECT_EQ(Vector3(41, 42, -3), m1[3]);
	}

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2
		{
			Vector3{51, 52, 53},
			Vector3{61, 62, 63},
			Vector3{71, 72, 73},
			Vector3{81, 82, 83},
		};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(51, 52, 53), m2.x());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(61, 62, 63), m2.y());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(71, 72, 73), m2.z());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(81, 82, 83), m2.w());
		BKSGE_CONSTEXPR_EXPECT_EQ(51, m2.x().x());
		BKSGE_CONSTEXPR_EXPECT_EQ(52, m2.x().y());
		BKSGE_CONSTEXPR_EXPECT_EQ(53, m2.x().z());
		BKSGE_CONSTEXPR_EXPECT_EQ(81, m2.w().x());
		BKSGE_CONSTEXPR_EXPECT_EQ(82, m2.w().y());
		BKSGE_CONSTEXPR_EXPECT_EQ(83, m2.w().z());
	}
}

TYPED_TEST(MathMatrix4x3Test, SwizzleTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2{m.xwyw()};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), m2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), m2[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2{m.wxx()};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), m2[2]);
	}
}

TYPED_TEST(MathMatrix4x3Test, SwapTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix4x3 m1
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};
	Matrix4x3 m2
	{
		Vector3{51, 52, 53},
		Vector3{61, 62, 63},
		Vector3{71, 72, 73},
		Vector3{81, 82, 83},
	};

	EXPECT_EQ(Vector3(11, 12, 13), m1[0]);
	EXPECT_EQ(Vector3(21, 22, 23), m1[1]);
	EXPECT_EQ(Vector3(31, 32, 33), m1[2]);
	EXPECT_EQ(Vector3(41, 42, 43), m1[3]);
	EXPECT_EQ(Vector3(51, 52, 53), m2[0]);
	EXPECT_EQ(Vector3(61, 62, 63), m2[1]);
	EXPECT_EQ(Vector3(71, 72, 73), m2[2]);
	EXPECT_EQ(Vector3(81, 82, 83), m2[3]);

	m1.swap(m2);

	EXPECT_EQ(Vector3(51, 52, 53), m1[0]);
	EXPECT_EQ(Vector3(61, 62, 63), m1[1]);
	EXPECT_EQ(Vector3(71, 72, 73), m1[2]);
	EXPECT_EQ(Vector3(81, 82, 83), m1[3]);
	EXPECT_EQ(Vector3(11, 12, 13), m2[0]);
	EXPECT_EQ(Vector3(21, 22, 23), m2[1]);
	EXPECT_EQ(Vector3(31, 32, 33), m2[2]);
	EXPECT_EQ(Vector3(41, 42, 43), m2[3]);

	swap(m1, m2);

	EXPECT_EQ(Vector3(11, 12, 13), m1[0]);
	EXPECT_EQ(Vector3(21, 22, 23), m1[1]);
	EXPECT_EQ(Vector3(31, 32, 33), m1[2]);
	EXPECT_EQ(Vector3(41, 42, 43), m1[3]);
	EXPECT_EQ(Vector3(51, 52, 53), m2[0]);
	EXPECT_EQ(Vector3(61, 62, 63), m2[1]);
	EXPECT_EQ(Vector3(71, 72, 73), m2[2]);
	EXPECT_EQ(Vector3(81, 82, 83), m2[3]);
}

TYPED_TEST(MathMatrix4x3Test, PlusMinusTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix4x3 m1
		{
			Vector3{-11,  12,  13},
			Vector3{ 21,  22, -23},
			Vector3{ 31, -32,  33},
			Vector3{ 41,  42,  43},
		};
		Matrix4x3 m2 = +m1;
		Matrix4x3 m3 = -m1;

		EXPECT_EQ(Vector3(-11,  12,  13), m2[0]);
		EXPECT_EQ(Vector3( 21,  22, -23), m2[1]);
		EXPECT_EQ(Vector3( 31, -32,  33), m2[2]);
		EXPECT_EQ(Vector3( 41,  42,  43), m2[3]);
		EXPECT_EQ(Vector3( 11, -12, -13), m3[0]);
		EXPECT_EQ(Vector3(-21, -22,  23), m3[1]);
		EXPECT_EQ(Vector3(-31,  32, -33), m3[2]);
		EXPECT_EQ(Vector3(-41, -42, -43), m3[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m1
		{
			Vector3{-11,  12,  13},
			Vector3{ 21,  22, -23},
			Vector3{ 31, -32,  33},
			Vector3{ 41,  42,  43},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2 = +m1;
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m3 = -m1;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-11,  12,  13), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 21,  22, -23), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 31, -32,  33), m2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 41,  42,  43), m2[3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 11, -12, -13), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-21, -22,  23), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-31,  32, -33), m3[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-41, -42, -43), m3[3]);
	}
}

TYPED_TEST(MathMatrix4x3Test, AddTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x3 += Matrix4x3
	{
		Matrix4x3 m1;

		Matrix4x3 t = m1 += Matrix4x3
		{
			Vector3{ 1,  2,  3},
			Vector3{ 5,  6,  7},
			Vector3{ 9, 10, 11},
			Vector3{13, 14, 15},
		};

		EXPECT_EQ(Vector3( 1,  2,  3), m1[0]);
		EXPECT_EQ(Vector3( 5,  6,  7), m1[1]);
		EXPECT_EQ(Vector3( 9, 10, 11), m1[2]);
		EXPECT_EQ(Vector3(13, 14, 15), m1[3]);
		EXPECT_EQ(t, m1);
	}

	// Matrix4x3 + Matrix4x3 -> Matrix4x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m1
		{
			Vector3{-21,  22,  23},
			Vector3{ 24, -25,  26},
			Vector3{ 27,  28, -29},
			Vector3{-33,  34,  35},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2
		{
			Vector3{ 31,  32, -33},
			Vector3{ 34, -35,  36},
			Vector3{-37,  38,  39},
			Vector3{-43,  44, -45},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m3 = m1 + m2;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 10,  54, -10), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 58, -60,  62), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-10,  66,  10), m3[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-76,  78, -10), m3[3]);
	}
}

TYPED_TEST(MathMatrix4x3Test, SubTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x3 -= Matrix4x3
	{
		Matrix4x3 m1;
		Matrix4x3 t = m1 -= Matrix4x3
		{
			Vector3{ 1,  2,  3},
			Vector3{ 5,  6,  7},
			Vector3{ 9, 10, 11},
			Vector3{13, 14, 15},
		};

		EXPECT_EQ(Vector3( -1,  -2,  -3), m1[0]);
		EXPECT_EQ(Vector3( -5,  -6,  -7), m1[1]);
		EXPECT_EQ(Vector3( -9, -10, -11), m1[2]);
		EXPECT_EQ(Vector3(-13, -14, -15), m1[3]);
		EXPECT_EQ(t, m1);
	}

	// Matrix4x3 - Matrix4x3 -> Matrix4x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m1
		{
			Vector3{10, 11, 12},
			Vector3{20, 21, 22},
			Vector3{30, 31, 32},
			Vector3{40, 41, 42},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2
		{
			Vector3{0, 9, 1},
			Vector3{8, 4, 7},
			Vector3{6, 5, 3},
			Vector3{4, 8, 5},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m3 = m1 - m2;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(10,  2, 11), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(12, 17, 15), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(24, 26, 29), m3[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(36, 33, 37), m3[3]);
	}
}

TYPED_TEST(MathMatrix4x3Test, MulScalarTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x3 *= スカラー
	{
		Matrix4x3 m1
		{
			Vector3{ 1,  2,  3},
			Vector3{ 5,  6,  7},
			Vector3{ 9, 10, 11},
			Vector3{13, 14, 15},
		};
		{
			Matrix4x3 t = (m1 *= 2);
			EXPECT_EQ(Vector3( 2,  4,  6), m1[0]);
			EXPECT_EQ(Vector3(10, 12, 14), m1[1]);
			EXPECT_EQ(Vector3(18, 20, 22), m1[2]);
			EXPECT_EQ(Vector3(26, 28, 30), m1[3]);
			EXPECT_EQ(t, m1);
		}
		{
			Matrix4x3 t = (m1 *= 2.5);
			EXPECT_EQ(Vector3( 5, 10, 15), m1[0]);
			EXPECT_EQ(Vector3(25, 30, 35), m1[1]);
			EXPECT_EQ(Vector3(45, 50, 55), m1[2]);
			EXPECT_EQ(Vector3(65, 70, 75), m1[3]);
			EXPECT_EQ(t, m1);
		}
	}

	// Matrix4x3 * スカラー -> Matrix4x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m1
		{
			Vector3{10, 12, 14},
			Vector3{20, 22, 24},
			Vector3{30, 32, 34},
			Vector3{40, 42, 44},
		};
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x3 t = m1 * 3;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 30,  36,  42), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 60,  66,  72), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 90,  96, 102), t[2]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(120, 126, 132), t[3]);
		}
		{
			const Matrix4x3 t = m1 * 2.5;
			EXPECT_EQ(Vector3( 25,  30,  35), t[0]);
			EXPECT_EQ(Vector3( 50,  55,  60), t[1]);
			EXPECT_EQ(Vector3( 75,  80,  85), t[2]);
			EXPECT_EQ(Vector3(100, 105, 110), t[3]);
		}
		// スカラー * Matrix4x3 -> Matrix4x3
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x3 t = 4 * m1;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 40,  48,  56), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 80,  88,  96), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(120, 128, 136), t[2]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(160, 168, 176), t[3]);
		}
		{
			const Matrix4x3 t = -1.5 * m1;
			EXPECT_EQ(Vector3(-15, -18, -21), t[0]);
			EXPECT_EQ(Vector3(-30, -33, -36), t[1]);
			EXPECT_EQ(Vector3(-45, -48, -51), t[2]);
			EXPECT_EQ(Vector3(-60, -63, -66), t[3]);
		}
	}
}

TYPED_TEST(MathMatrix4x3Test, MulMatrixTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix4x3 m
	{
		Vector3{  2,  4,  6 },
		Vector3{ 10, 12, 14 },
		Vector3{ 18, 20, 22 },
		Vector3{ 26, 28, 30 },
	};

	// Matrix4x3 *= Matrix3x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
		{
			Vector3{  11, -12,  13 },
			Vector3{  21,  22, -23 },
			Vector3{ -31,  32,  33 },
		};

		auto t = m *= m1;
		static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
		EXPECT_EQ(Vector3( -80,  256, 132), m[0]);
		EXPECT_EQ(Vector3( -72,  592, 316), m[1]);
		EXPECT_EQ(Vector3( -64,  928, 500), m[2]);
		EXPECT_EQ(Vector3( -56, 1264, 684), m[3]);
		EXPECT_EQ(t, m);
	}

	// Matrix4x3 * Matrix3x3 -> Matrix4x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m1
		{
			Vector3{  15,   3,  -7 },
			Vector3{  11,   4,  12 },
			Vector3{   2,   6,  13 },
			Vector3{   1,  14,   9 },
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2
		{
			Vector3{   1,   2,   3 },
			Vector3{   5,   6,   7 },
			Vector3{   9,  10, -11 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), const Matrix4x3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( -33, -22, 143), t1[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 139, 166, -71), t1[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 149, 170, -95), t1[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 152, 176,   2), t1[3]);
	}

	// Matrix4x4 * Matrix4x3 -> Matrix4x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
		{
			Vector4{  1,  2,  3,  4 },
			Vector4{  5,  6,  7,  8 },
			Vector4{  9, 10, 11, 12 },
			Vector4{ 13, 14, 15, 16 },
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2
		{
			Vector3{ 11, 12, 13 },
			Vector3{ 21, 22, 23 },
			Vector3{ 31, 32, 33 },
			Vector3{ 41, 42, 43 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), const Matrix4x3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 310, 320, 330), t1[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 726, 752, 778), t1[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1142,1184,1226), t1[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1558,1616,1674), t1[3]);
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

TYPED_TEST(MathMatrix4x3Test, MulVectorTest)
{
	using Matrix4x3 = bksge::math::Matrix4x3<TypeParam>;
	using Vector4 = bksge::math::Vector4<TypeParam>;
	using Vector3 = bksge::math::Vector3<TypeParam>;

	// Vector4 * Matrix4x3 -> Vector3
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v { -5, 6, 7, 8 };
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m
		{
			Vector3{   1,  -2,   3 },
			Vector3{   5,   6,   7 },
			Vector3{   9,  10, -11 },
			Vector3{  13, -14,  15 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t = v * m;
		static_assert(bksge::is_same<decltype(t), const Vector3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(192, 4, 70), t);
	}
}

TYPED_TEST(MathMatrix4x3Test, DivScalarTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x3 /= スカラー
	{
		Matrix4x3 m1
		{
			Vector3{10, 12, 14},
			Vector3{18, 20, 22},
			Vector3{26, 28, 30},
			Vector3{34, 36, 38},
		};

		{
			Matrix4x3 t = (m1 /= 2);
			EXPECT_EQ(Vector3( 5,  6,  7), m1[0]);
			EXPECT_EQ(Vector3( 9, 10, 11), m1[1]);
			EXPECT_EQ(Vector3(13, 14, 15), m1[2]);
			EXPECT_EQ(Vector3(17, 18, 19), m1[3]);
			EXPECT_EQ(t, m1);
		}
		{
			Matrix4x3 t = (m1 /= 0.5);
			EXPECT_EQ(Vector3(10, 12, 14), m1[0]);
			EXPECT_EQ(Vector3(18, 20, 22), m1[1]);
			EXPECT_EQ(Vector3(26, 28, 30), m1[2]);
			EXPECT_EQ(Vector3(34, 36, 38), m1[3]);
			EXPECT_EQ(t, m1);
		}
	}

	// Matrix4x3 / スカラー
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m1
		{
			Vector3{10, 12, 14},
			Vector3{20, 22, 24},
			Vector3{30, 32, 34},
			Vector3{40, 42, 44},
		};

		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x3 t = (m1 / 2);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 5,  6,  7), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(10, 11, 12), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(15, 16, 17), t[2]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(20, 21, 22), t[3]);
		}
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x3 t = (m1 / 0.25);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 40,  48,  56), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 80,  88,  96), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(120, 128, 136), t[2]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(160, 168, 176), t[3]);
		}
	}
}

TYPED_TEST(MathMatrix4x3Test, CompareTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix4x3  m1
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3  m2
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3  m3
	{
		Vector3{10, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3  m4
	{
		Vector3{11, 12, 13},
		Vector3{21, 23, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3  m5
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, -33},
		Vector3{41, 42, 43},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3  m6
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 40, 43},
	};

	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 == m1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 == m2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 == m3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 == m4);
	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 == m5);
	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 == m6);

	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 != m1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(m1 != m2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 != m3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 != m4);
	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 != m5);
	BKSGE_CONSTEXPR_EXPECT_TRUE (m1 != m6);
}

TYPED_TEST(MathMatrix4x3Test, OutputStreamTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix4x3 const m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};
		std::stringstream ss;
		ss << m;
		EXPECT_EQ("{ { 11, 12, 13 }, { 21, 22, 23 }, { 31, 32, 33 }, { 41, 42, 43 } }", ss.str());
	}
	{
		Matrix4x3 const m
		{
			Vector3{51, 52, 53},
			Vector3{61, 62, 63},
			Vector3{71, 72, 73},
			Vector3{81, 82, 83},
		};
		std::wstringstream ss;
		ss << m;
		EXPECT_EQ(L"{ { 51, 52, 53 }, { 61, 62, 63 }, { 71, 72, 73 }, { 81, 82, 83 } }", ss.str());
	}
}

TYPED_TEST(MathMatrix4x3Test, TupleElementTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(bksge::is_same<typename std::tuple_element<0, Matrix4x3>::type, Vector3>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<1, Matrix4x3>::type, Vector3>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<2, Matrix4x3>::type, Vector3>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<3, Matrix4x3>::type, Vector3>::value, "");
}

TYPED_TEST(MathMatrix4x3Test, TupleGetTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};

		EXPECT_EQ(Vector3(11, 12, 13), bksge::get<0>(m));
		EXPECT_EQ(Vector3(21, 22, 23), bksge::get<1>(m));
		EXPECT_EQ(Vector3(31, 32, 33), bksge::get<2>(m));
		EXPECT_EQ(Vector3(41, 42, 43), bksge::get<3>(m));

		bksge::get<0>(m) = Vector3{51, 52, 53};
		bksge::get<3>(m) = Vector3{61, 62, 63};

		EXPECT_EQ(Vector3(51, 52, 53), m[0]);
		EXPECT_EQ(Vector3(21, 22, 23), m[1]);
		EXPECT_EQ(Vector3(31, 32, 33), m[2]);
		EXPECT_EQ(Vector3(61, 62, 63), m[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
			Vector3{41, 42, 43},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), bksge::get<0>(m));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), bksge::get<1>(m));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), bksge::get<2>(m));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(41, 42, 43), bksge::get<3>(m));
	}
}

TYPED_TEST(MathMatrix4x3Test, TupleSizeTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

	static_assert(std::tuple_size<Matrix4x3>::value == 4, "");
}

TYPED_TEST(MathMatrix4x3Test, ZeroTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x3::Zero();
		static_assert(bksge::is_same<decltype(m), const Matrix4x3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 0), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 0), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 0), m[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 0), m[3]);
	}
	{
		const auto m = Matrix4x3::Zero();
		static_assert(bksge::is_same<decltype(m), const Matrix4x3>::value, "");
		EXPECT_EQ(Vector3(0, 0, 0), m[0]);
		EXPECT_EQ(Vector3(0, 0, 0), m[1]);
		EXPECT_EQ(Vector3(0, 0, 0), m[2]);
		EXPECT_EQ(Vector3(0, 0, 0), m[3]);
	}
}

TYPED_TEST(MathMatrix4x3Test, IdentityTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x3::Identity();
		static_assert(bksge::is_same<decltype(m), const Matrix4x3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 0, 0), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 1, 0), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 1), m[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 0), m[3]);
	}
	{
		const auto m = Matrix4x3::Identity();
		static_assert(bksge::is_same<decltype(m), const Matrix4x3>::value, "");
		EXPECT_EQ(Vector3(1, 0, 0), m[0]);
		EXPECT_EQ(Vector3(0, 1, 0), m[1]);
		EXPECT_EQ(Vector3(0, 0, 1), m[2]);
		EXPECT_EQ(Vector3(0, 0, 0), m[3]);
	}
}

TYPED_TEST(MathMatrix4x3Test, TransposedTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector4 = bksge::math::Vector4<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m1
	{
		Vector3{ 11, 12, 13 },
		Vector3{ 21, 22, 23 },
		Vector3{ 31, 32, 33 },
		Vector3{ 41, 42, 43 },
	};

	BKSGE_CONSTEXPR_OR_CONST auto m2 = Transposed(m1);
	static_assert(bksge::is_same<decltype(m2), const Matrix3x4>::value, "");
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 21, 31, 41), m2[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(12, 22, 32, 42), m2[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(13, 23, 33, 43), m2[2]);

	const auto m3 = Transposed(m2);
	static_assert(bksge::is_same<decltype(m3), const Matrix4x3>::value, "");
	EXPECT_EQ(Vector3(11, 12, 13), m3[0]);
	EXPECT_EQ(Vector3(21, 22, 23), m3[1]);
	EXPECT_EQ(Vector3(31, 32, 33), m3[2]);
	EXPECT_EQ(Vector3(41, 42, 43), m3[3]);

	EXPECT_EQ(m1, m3);
}

TYPED_TEST(MathMatrix4x3Test, ResizedTest)
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
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2 = bksge::math::Resized<4, 3>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 expected
		{
			Vector3{ 1, 2, 3 },
			Vector3{ 4, 5, 6 },
			Vector3{ 7, 8, 9 },
			Vector3{ 0, 0, 0 },
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

		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2 = bksge::math::Resized<4, 3>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 expected
		{
			Vector3{ 10, 11, 12 },
			Vector3{ 20, 21, 22 },
			Vector3{ 30, 31, 32 },
			Vector3{ 40, 41, 42 },
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

		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2 = bksge::math::Resized<4, 3>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 expected
		{
			Vector3{ 10, 11, 12 },
			Vector3{ 20, 21, 22 },
			Vector3{ 30, 31, 32 },
			Vector3{  0,  0,  0 },
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

		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2 = bksge::math::Resized<4, 3>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 expected
		{
			Vector3{ 11, 12, 13 },
			Vector3{ 21, 22, 23 },
			Vector3{ 31, 32, 33 },
			Vector3{ 41, 42, 43 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m2);
	}
}

TYPED_TEST(MathMatrix4x3Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix4x3 const v
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
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

TYPED_TEST(MathMatrix4x3Test, HashTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	std::hash<Matrix4x3> h;

	Matrix4x3 const m1
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};

	Matrix4x3 const m2
	{
		Vector3{11, 12, 10},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};

	Matrix4x3 const m3
	{
		Vector3{11, 12, 13},
		Vector3{21, 23, 23},
		Vector3{31, 32, 33},
		Vector3{41, 42, 43},
	};

	Matrix4x3 const m4
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{30, 32, 33},
		Vector3{41, 42, 43},
	};

	Matrix4x3 const m5
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
		Vector3{41,-42, 43},
	};

	std::vector<bksge::size_t> v;
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

}	// namespace matrix4x3_test

}	// namespace bksge_math_test
