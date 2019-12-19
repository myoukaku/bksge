﻿/**
 *	@file	unit_test_core_math_matrix3x3.cpp
 *
 *	@brief	Matrix3x3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/matrix3x4.hpp>
#include <bksge/core/math/matrix4x3.hpp>
#include <bksge/core/math/matrix4x4.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/scale3.hpp>
#include <bksge/core/math/scale2.hpp>
#include <bksge/core/math/quaternion.hpp>
#include <bksge/fnd/cmath/degrees_to_radians.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include "constexpr_test.hpp"

namespace bksge_math_test
{

namespace matrix3x3_test
{

using Matrix3x3f = bksge::math::Matrix3x3<float>;
using Matrix3x3i = bksge::math::Matrix3x3<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathMatrix3x3Test : public ::testing::Test {};
template <typename T>
class MathMatrix3x3FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathMatrix3x3Test, MathTestTypes);
TYPED_TEST_SUITE(MathMatrix3x3FloatTest, MathFloatTestTypes);

TYPED_TEST(MathMatrix3x3Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	static_assert(sizeof(Matrix3x3) == sizeof(T) * 9, "");
	static_assert(std::is_default_constructible<Matrix3x3>::value, "");
	static_assert(std::is_nothrow_default_constructible<Matrix3x3>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Matrix3x3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[2][2]);
	}
}

TYPED_TEST(MathMatrix3x3Test, VectorConstructTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(!std::is_constructible<Matrix3x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( std::is_constructible<Matrix3x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!std::is_constructible<Matrix3x3, Vector3, Vector3>::value, "");
	static_assert(!std::is_constructible<Matrix3x3, Vector3>::value, "");
	static_assert(!std::is_nothrow_constructible<Matrix3x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( std::is_nothrow_constructible<Matrix3x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!std::is_nothrow_constructible<Matrix3x3, Vector3, Vector3>::value, "");
	static_assert(!std::is_nothrow_constructible<Matrix3x3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( bksge::is_implicitly_constructible<Matrix3x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, Vector3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v1(1, 2, 3);
		BKSGE_CONSTEXPR_OR_CONST Vector3 v2(4, 5, 6);
		BKSGE_CONSTEXPR_OR_CONST Vector3 v3(7, 8, 9);
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m(v1, v2, v3);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, m[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, m[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, m[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, m[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, m[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, m[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, m[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, m[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(9, m[2][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m
		{
			Vector3{10, 11, 12},
			Vector3{20, 21, 22},
			Vector3{30, 31, 32},
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
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m =
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
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
	}
}

TYPED_TEST(MathMatrix3x3Test, CopyConstructTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(std::is_constructible<Matrix3x3,  Matrix3x3  const&>::value, "");
	static_assert(std::is_constructible<Matrix3x3,  Matrix3x3i const&>::value, "");
	static_assert(std::is_constructible<Matrix3x3,  Matrix3x3f const&>::value, "");
	static_assert(std::is_constructible<Matrix3x3i, Matrix3x3  const&>::value, "");
	static_assert(std::is_constructible<Matrix3x3i, Matrix3x3i const&>::value, "");
	static_assert(std::is_constructible<Matrix3x3i, Matrix3x3f const&>::value, "");
	static_assert(std::is_constructible<Matrix3x3f, Matrix3x3  const&>::value, "");
	static_assert(std::is_constructible<Matrix3x3f, Matrix3x3i const&>::value, "");
	static_assert(std::is_constructible<Matrix3x3f, Matrix3x3f const&>::value, "");

	static_assert(std::is_nothrow_constructible<Matrix3x3,  Matrix3x3  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Matrix3x3,  Matrix3x3i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Matrix3x3,  Matrix3x3f const&>::value, "");
	static_assert(std::is_nothrow_constructible<Matrix3x3i, Matrix3x3  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Matrix3x3i, Matrix3x3i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Matrix3x3i, Matrix3x3f const&>::value, "");
	static_assert(std::is_nothrow_constructible<Matrix3x3f, Matrix3x3  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Matrix3x3f, Matrix3x3i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Matrix3x3f, Matrix3x3f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Matrix3x3,  Matrix3x3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3,  Matrix3x3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3,  Matrix3x3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3i, Matrix3x3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3i, Matrix3x3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3i, Matrix3x3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3f, Matrix3x3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3f, Matrix3x3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3f, Matrix3x3f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Matrix3x3  m1
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x3  m2{m1};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x3i m3{m2};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x3f m4{m2};

	BKSGE_CONSTEXPR_EXPECT_EQ(11, m3[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, m3[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, m3[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(21, m3[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(22, m3[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(23, m3[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(31, m3[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(32, m3[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(33, m3[2][2]);

	BKSGE_CONSTEXPR_EXPECT_EQ(11, m4[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, m4[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, m4[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(21, m4[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(22, m4[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(23, m4[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(31, m4[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(32, m4[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(33, m4[2][2]);
}

TYPED_TEST(MathMatrix3x3FloatTest, FromQuaternionTest)
{
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;
	using Quaternion = bksge::math::Quaternion<TypeParam>;
	using Vector3 = bksge::math::Vector3<TypeParam>;

	const double error = 0.000001;

	{
		BKSGE_CONSTEXPR_OR_CONST auto q = Quaternion::Identity();
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m(q);
		BKSGE_CONSTEXPR_OR_CONST auto expected = Matrix3x3::Identity();

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m);
	}
	{
		const auto angle = bksge::degrees_to_radians(30);
		const auto q = Quaternion::MakeRotationX(angle);
		const Matrix3x3 m(q);
		const auto expected = Matrix3x3::MakeRotationX(angle);

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
	}
	{
		const auto angle = bksge::degrees_to_radians(45);
		const auto q = Quaternion::MakeRotationY(angle);
		const Matrix3x3 m(q);
		const auto expected = Matrix3x3::MakeRotationY(angle);

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
	}
	{
		const auto angle = bksge::degrees_to_radians(60);
		const auto q = Quaternion::MakeRotationZ(angle);
		const Matrix3x3 m(q);
		const auto expected = Matrix3x3::MakeRotationZ(angle);

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
	}
	{
		const Vector3 axis{1, 2, 3};
		const auto angle = bksge::degrees_to_radians(90);
		const auto q = Quaternion::MakeRotation(axis, angle);
		const Matrix3x3 m(q);
		const auto expected = Matrix3x3::MakeRotation(axis, angle);

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
	}
}

TYPED_TEST(MathMatrix3x3Test, CopyAssignTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix3x3  m1
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
	};
	Matrix3x3  m2;

	EXPECT_EQ(Vector3(11, 12, 13), m1[0]);
	EXPECT_EQ(Vector3(21, 22, 23), m1[1]);
	EXPECT_EQ(Vector3(31, 32, 33), m1[2]);

	EXPECT_EQ(Vector3(0, 0, 0), m2[0]);
	EXPECT_EQ(Vector3(0, 0, 0), m2[1]);
	EXPECT_EQ(Vector3(0, 0, 0), m2[2]);

	m1 = Matrix3x3
	{
		Vector3{51, 52, 53},
		Vector3{61, 62, 63},
		Vector3{71, 72, 73},
	};

	EXPECT_EQ(Vector3(51, 52, 53), m1[0]);
	EXPECT_EQ(Vector3(61, 62, 63), m1[1]);
	EXPECT_EQ(Vector3(71, 72, 73), m1[2]);

	m2 = Matrix3x3i
	{
		Vector3{ 1,  2,  3 },
		Vector3{ 5,  6,  7 },
		Vector3{ 9, 10, 11 },
	};

	EXPECT_EQ(Vector3( 1,  2,  3), m2[0]);
	EXPECT_EQ(Vector3( 5,  6,  7), m2[1]);
	EXPECT_EQ(Vector3( 9, 10, 11), m2[2]);

	m1 = m2 = Matrix3x3f
	{
		Vector3{10, 11, 12},
		Vector3{20, 21, 22},
		Vector3{30, 31, 32},
	};

	EXPECT_EQ(Vector3(10, 11, 12), m1[0]);
	EXPECT_EQ(Vector3(20, 21, 22), m1[1]);
	EXPECT_EQ(Vector3(30, 31, 32), m1[2]);

	EXPECT_EQ(Vector3(10, 11, 12), m2[0]);
	EXPECT_EQ(Vector3(20, 21, 22), m2[1]);
	EXPECT_EQ(Vector3(30, 31, 32), m2[2]);
}

TYPED_TEST(MathMatrix3x3Test, IndexAccessTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix3x3  m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};

		m[0][0] = 50;
		m[1] = Vector3(51, 52, 53);
		m[2][1] = 55;

		EXPECT_EQ(Vector3(50, 12, 13), m[0]);
		EXPECT_EQ(Vector3(51, 52, 53), m[1]);
		EXPECT_EQ(Vector3(31, 55, 33), m[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), m[2]);
	}
}

TYPED_TEST(MathMatrix3x3Test, AtTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix3x3  m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};

		m.at(0).at(0) = 50;
		m.at(1) = Vector3(51, 52, 53);
		m.at(2).at(1) = 55;

		EXPECT_EQ(Vector3(50, 12, 13), m.at(0));
		EXPECT_EQ(Vector3(51, 52, 53), m.at(1));
		EXPECT_EQ(Vector3(31, 55, 33), m.at(2));
		EXPECT_THROW((void)m.at(0).at(3), std::out_of_range);
		EXPECT_THROW((void)m.at(3), std::out_of_range);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), m.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), m.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), m.at(2));
		EXPECT_THROW((void)m.at(0).at(3), std::out_of_range);
		EXPECT_THROW((void)m.at(3), std::out_of_range);
	}
}

TYPED_TEST(MathMatrix3x3Test, DataTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
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

		EXPECT_EQ(Vector3(51, 52, 53), m[0]);
		EXPECT_EQ(Vector3(21, 22, 23), m[1]);
		EXPECT_EQ(Vector3(61, 62, 63), m[2]);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};
		BKSGE_STATIC_CONSTEXPR auto p = m.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), p[2]);
	}
#endif
}

TYPED_TEST(MathMatrix3x3Test, IteratorTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// begin, end (non const)
	{
		Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
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
		EXPECT_TRUE(it == m.end());

		EXPECT_EQ(Vector3(51, 52, 53), m[0]);
		EXPECT_EQ(Vector3(21, 22, 23), m[1]);
		EXPECT_EQ(Vector3(61, 62, 63), m[2]);
	}
	// begin, end (const)
	{
		const Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};
		auto it = m.begin();
		EXPECT_TRUE(it != m.end());

		EXPECT_EQ(Vector3(11, 12, 13), it[0]);
		EXPECT_EQ(Vector3(21, 22, 23), it[1]);
		EXPECT_EQ(Vector3(31, 32, 33), it[2]);

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
		EXPECT_TRUE(it == m.end());
	}
	// cbegin, cend
	{
		const Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};
		auto it = m.cbegin();
		EXPECT_TRUE(it != m.cend());

		EXPECT_EQ(Vector3(11, 12, 13), it[0]);
		EXPECT_EQ(Vector3(21, 22, 23), it[1]);
		EXPECT_EQ(Vector3(31, 32, 33), it[2]);

		EXPECT_EQ(Vector3(11, 12, 13), *it++);
		EXPECT_TRUE(it != m.cend());
		EXPECT_EQ(Vector3(31, 32, 33), *++it);
		EXPECT_TRUE(it != m.cend());
		EXPECT_EQ(Vector3(31, 32, 33), *it++);
		EXPECT_TRUE(it == m.cend());
	}
#if !defined(BKSGE_GCC)
	// begin, end (constexpr)
	{
		BKSGE_STATIC_CONSTEXPR Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};
		BKSGE_CONSTEXPR_OR_CONST auto it = m.begin();
		BKSGE_CONSTEXPR_EXPECT_TRUE(it != m.end());

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), it[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), it[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), it[2]);

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
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 == m.end());
	}
#endif
}

TYPED_TEST(MathMatrix3x3Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// rbegin, rend (non const)
	{
		Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};
		auto it = m.rbegin();
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(31, 32, 33), *it);
		*it++ = Vector3{51, 52, 53};
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(21, 22, 23), *it);
		*++it = Vector3{61, 62, 63};
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(61, 62, 63), *it);
		it++;
		EXPECT_TRUE(it == m.rend());

		EXPECT_EQ(Vector3(61, 62, 63), m[0]);
		EXPECT_EQ(Vector3(21, 22, 23), m[1]);
		EXPECT_EQ(Vector3(51, 52, 53), m[2]);
	}
	// rbegin, rend (const)
	{
		const Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};
		auto it = m.rbegin();
		EXPECT_TRUE(it != m.rend());

		EXPECT_EQ(Vector3(31, 32, 33), it[0]);
		EXPECT_EQ(Vector3(21, 22, 23), it[1]);
		EXPECT_EQ(Vector3(11, 12, 13), it[2]);

		EXPECT_EQ(Vector3(31, 32, 33), *it++);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(11, 12, 13), *++it);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(21, 22, 23), *--it);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(21, 22, 23), *it--);
		EXPECT_TRUE(it != m.rend());
		it += 2;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(11, 12, 13), *it);
		it -= 2;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector3(31, 32, 33), *it);
		it += 3;
		EXPECT_TRUE(it == m.rend());
	}
	// crbegin, crend
	{
		const Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};
		auto it = m.crbegin();
		EXPECT_TRUE(it != m.crend());

		EXPECT_EQ(Vector3(31, 32, 33), it[0]);
		EXPECT_EQ(Vector3(21, 22, 23), it[1]);
		EXPECT_EQ(Vector3(11, 12, 13), it[2]);

		EXPECT_EQ(Vector3(31, 32, 33), *it++);
		EXPECT_TRUE(it != m.crend());
		EXPECT_EQ(Vector3(11, 12, 13), *++it);
		EXPECT_TRUE(it != m.crend());
		EXPECT_EQ(Vector3(11, 12, 13), *it++);
		EXPECT_TRUE(it == m.crend());
	}
#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201603)
	// rbegin, rend (constexpr)
	{
		BKSGE_CXX17_STATIC_CONSTEXPR Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = m.rbegin();
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it != m.rend());

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), it[0]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), it[1]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), it[2]);

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), *it);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it2 != m.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), *it2);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it3 != m.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), *it3);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), *it4);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 == m.rend());
	}
#endif
}

TYPED_TEST(MathMatrix3x3Test, EmptyTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	Matrix3x3 m1{};
	const           Matrix3x3 m2{};
	BKSGE_CONSTEXPR Matrix3x3 m3{};
	EXPECT_FALSE(m1.empty());
	EXPECT_FALSE(m2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(m3.empty());
}

TYPED_TEST(MathMatrix3x3Test, SizeTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	Matrix3x3 m1{};
	const           Matrix3x3 m2{};
	BKSGE_CONSTEXPR Matrix3x3 m3{};
	EXPECT_EQ(3u, m1.size());
	EXPECT_EQ(3u, m2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, m3.size());
}

TYPED_TEST(MathMatrix3x3Test, MaxSizeTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	Matrix3x3 m1{};
	const           Matrix3x3 m2{};
	BKSGE_CONSTEXPR Matrix3x3 m3{};
	EXPECT_EQ(3u, m1.max_size());
	EXPECT_EQ(3u, m2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, m3.max_size());
}

TYPED_TEST(MathMatrix3x3Test, NameAccessTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix3x3 m1
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};
		EXPECT_EQ(Vector3(11, 12, 13), m1.x());
		EXPECT_EQ(Vector3(21, 22, 23), m1.y());
		EXPECT_EQ(Vector3(31, 32, 33), m1.z());
		EXPECT_EQ(11, m1.x().x());
		EXPECT_EQ(12, m1.x().y());
		EXPECT_EQ(13, m1.x().z());
		EXPECT_EQ(31, m1.z().x());
		EXPECT_EQ(32, m1.z().y());
		EXPECT_EQ(33, m1.z().z());
		m1.x() = Vector3{0, 1, 2};
		m1.z() = Vector3{4, 5, 6};

		EXPECT_EQ(Vector3(0, 1, 2), m1[0]);
		EXPECT_EQ(Vector3(21, 22, 23), m1[1]);
		EXPECT_EQ(Vector3(4, 5, 6), m1[2]);

		m1.x().y() = -1;
		m1.y().x() = -2;

		EXPECT_EQ(Vector3( 0, -1,  2), m1[0]);
		EXPECT_EQ(Vector3(-2, 22, 23), m1[1]);
		EXPECT_EQ(Vector3( 4,  5,  6), m1[2]);
	}

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2
		{
			Vector3{51, 52, 53},
			Vector3{61, 62, 63},
			Vector3{71, 72, 73},
		};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(51, 52, 53), m2.x());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(61, 62, 63), m2.y());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(71, 72, 73), m2.z());
		BKSGE_CONSTEXPR_EXPECT_EQ(51, m2.x().x());
		BKSGE_CONSTEXPR_EXPECT_EQ(52, m2.x().y());
		BKSGE_CONSTEXPR_EXPECT_EQ(53, m2.x().z());
		BKSGE_CONSTEXPR_EXPECT_EQ(71, m2.z().x());
		BKSGE_CONSTEXPR_EXPECT_EQ(72, m2.z().y());
		BKSGE_CONSTEXPR_EXPECT_EQ(73, m2.z().z());
	}
}

TYPED_TEST(MathMatrix3x3Test, SwizzleTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
	};

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2{m.yzx()};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), m2[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m2{m.zyzx()};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), m2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), m2[3]);
	}
}

TYPED_TEST(MathMatrix3x3Test, SwapTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix3x3 m1
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
	};
	Matrix3x3 m2
	{
		Vector3{51, 52, 53},
		Vector3{61, 62, 63},
		Vector3{71, 72, 73},
	};

	EXPECT_EQ(Vector3(11, 12, 13), m1[0]);
	EXPECT_EQ(Vector3(21, 22, 23), m1[1]);
	EXPECT_EQ(Vector3(31, 32, 33), m1[2]);
	EXPECT_EQ(Vector3(51, 52, 53), m2[0]);
	EXPECT_EQ(Vector3(61, 62, 63), m2[1]);
	EXPECT_EQ(Vector3(71, 72, 73), m2[2]);

	m1.swap(m2);

	EXPECT_EQ(Vector3(51, 52, 53), m1[0]);
	EXPECT_EQ(Vector3(61, 62, 63), m1[1]);
	EXPECT_EQ(Vector3(71, 72, 73), m1[2]);
	EXPECT_EQ(Vector3(11, 12, 13), m2[0]);
	EXPECT_EQ(Vector3(21, 22, 23), m2[1]);
	EXPECT_EQ(Vector3(31, 32, 33), m2[2]);

	swap(m1, m2);

	EXPECT_EQ(Vector3(11, 12, 13), m1[0]);
	EXPECT_EQ(Vector3(21, 22, 23), m1[1]);
	EXPECT_EQ(Vector3(31, 32, 33), m1[2]);
	EXPECT_EQ(Vector3(51, 52, 53), m2[0]);
	EXPECT_EQ(Vector3(61, 62, 63), m2[1]);
	EXPECT_EQ(Vector3(71, 72, 73), m2[2]);
}

TYPED_TEST(MathMatrix3x3Test, PlusMinusTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix3x3 m1
		{
			Vector3{-11,  12,  13},
			Vector3{ 21,  22, -23},
			Vector3{ 31, -32,  33},
		};
		Matrix3x3 m2 = +m1;
		Matrix3x3 m3 = -m1;

		EXPECT_EQ(Vector3(-11,  12,  13), m2[0]);
		EXPECT_EQ(Vector3( 21,  22, -23), m2[1]);
		EXPECT_EQ(Vector3( 31, -32,  33), m2[2]);
		EXPECT_EQ(Vector3( 11, -12, -13), m3[0]);
		EXPECT_EQ(Vector3(-21, -22,  23), m3[1]);
		EXPECT_EQ(Vector3(-31,  32, -33), m3[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
		{
			Vector3{-11,  12,  13},
			Vector3{ 21,  22, -23},
			Vector3{ 31, -32,  33},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2 = +m1;
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m3 = -m1;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-11,  12,  13), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 21,  22, -23), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 31, -32,  33), m2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 11, -12, -13), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-21, -22,  23), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-31,  32, -33), m3[2]);
	}
}

TYPED_TEST(MathMatrix3x3Test, AddTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix3x3 += Matrix3x3
	{
		Matrix3x3 m1;

		Matrix3x3 t = m1 += Matrix3x3
		{
			Vector3{ 1,  2,  3},
			Vector3{ 5,  6,  7},
			Vector3{ 9, 10, 11},
		};

		EXPECT_EQ(Vector3( 1,  2,  3), m1[0]);
		EXPECT_EQ(Vector3( 5,  6,  7), m1[1]);
		EXPECT_EQ(Vector3( 9, 10, 11), m1[2]);
		EXPECT_EQ(t, m1);
	}

	// Matrix3x3 + Matrix3x3 -> Matrix3x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
		{
			Vector3{-21,  22,  23},
			Vector3{ 24, -25,  26},
			Vector3{ 27,  28, -29},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2
		{
			Vector3{ 31,  32, -33},
			Vector3{ 34, -35,  36},
			Vector3{-37,  38,  39},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m3 = m1 + m2;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 10,  54, -10), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 58, -60,  62), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-10,  66,  10), m3[2]);
	}
}

TYPED_TEST(MathMatrix3x3Test, SubTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix3x3 -= Matrix3x3
	{
		Matrix3x3 m1;
		Matrix3x3 t = m1 -= Matrix3x3
		{
			Vector3{ 1,  2,  3},
			Vector3{ 5,  6,  7},
			Vector3{ 9, 10, 11},
		};

		EXPECT_EQ(Vector3(-1,  -2,  -3), m1[0]);
		EXPECT_EQ(Vector3(-5,  -6,  -7), m1[1]);
		EXPECT_EQ(Vector3(-9, -10, -11), m1[2]);
		EXPECT_EQ(t, m1);
	}

	// Matrix3x3 - Matrix3x3 -> Matrix3x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
		{
			Vector3{10, 11, 12},
			Vector3{20, 21, 22},
			Vector3{30, 31, 32},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2
		{
			Vector3{0, 9, 1},
			Vector3{8, 4, 7},
			Vector3{6, 5, 3},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m3 = m1 - m2;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(10,  2, 11), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(12, 17, 15), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(24, 26, 29), m3[2]);
	}
}

TYPED_TEST(MathMatrix3x3Test, MulScalarTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix3x3 *= スカラー
	{
		Matrix3x3 m1
		{
			Vector3{1,  2,  3},
			Vector3{5,  6,  7},
			Vector3{9, 10, 11},
		};
		{
			Matrix3x3 t = (m1 *= 2);
			EXPECT_EQ(Vector3( 2,  4,  6), m1[0]);
			EXPECT_EQ(Vector3(10, 12, 14), m1[1]);
			EXPECT_EQ(Vector3(18, 20, 22), m1[2]);
			EXPECT_EQ(t, m1);
		}
		{
			Matrix3x3 t = (m1 *= 2.5);
			EXPECT_EQ(Vector3( 5, 10, 15), m1[0]);
			EXPECT_EQ(Vector3(25, 30, 35), m1[1]);
			EXPECT_EQ(Vector3(45, 50, 55), m1[2]);
			EXPECT_EQ(t, m1);
		}
	}

	// Matrix3x3 * スカラー -> Matrix3x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
		{
			Vector3{10, 12, 14},
			Vector3{20, 22, 24},
			Vector3{30, 32, 34},
		};
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix3x3 t = m1 * 3;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(30, 36, 42), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(60, 66, 72), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(90, 96,102), t[2]);
		}
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix3x3 t = m1 * 2.5;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(25, 30, 35), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(50, 55, 60), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(75, 80, 85), t[2]);
		}
		// スカラー * Matrix3x3 -> Matrix3x3
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix3x3 t = 4 * m1;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 40, 48, 56), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 80, 88, 96), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(120,128,136), t[2]);
		}
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix3x3 t = -1.5 * m1;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-15, -18, -21), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-30, -33, -36), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-45, -48, -51), t[2]);
		}
	}
}

TYPED_TEST(MathMatrix3x3Test, MulMatrixTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix3x3 m
	{
		Vector3{  2,  4,  6 },
		Vector3{ 10, 12, 14 },
		Vector3{ 18, 20, 22 },
	};

	// Matrix3x3 *= Matrix3x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
		{
			Vector3{  11, -12,  13 },
			Vector3{  21,  22, -23 },
			Vector3{ -31,  32,  33 },
		};

		auto t = m *= m1;
		static_assert(std::is_same<decltype(t), Matrix3x3>::value, "");
		EXPECT_EQ(Vector3(-80, 256, 132), m[0]);
		EXPECT_EQ(Vector3(-72, 592, 316), m[1]);
		EXPECT_EQ(Vector3(-64, 928, 500), m[2]);
		EXPECT_EQ(t, m);
	}

	// Matrix3x3 * Matrix3x3 -> Matrix3x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
		{
			Vector3{ 15, 3, -7 },
			Vector3{ 11, 4, 12 },
			Vector3{  2, 6, 13 },
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2
		{
			Vector3{ 1,  2,  3 },
			Vector3{ 5,  6,  7 },
			Vector3{ 9, 10,-11 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), const Matrix3x3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-33, -22, 143), t1[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(139, 166, -71), t1[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(149, 170, -95), t1[2]);

		BKSGE_CONSTEXPR_OR_CONST auto t2 = m2 * m1;
		static_assert(std::is_same<decltype(t2), const Matrix3x3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 43, 29,  56), t2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(155, 81, 128), t2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(223,  1, -86), t2[2]);
	}

	// Matrix3x3 * Matrix3x4 -> Matrix3x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
		{
			Vector3{  1,  2,  3 },
			Vector3{  5,  6,  7 },
			Vector3{  9, 10, 11 },
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2
		{
			Vector4{ 11, 12, 13, 14 },
			Vector4{ 21, 22, 23, 24 },
			Vector4{ 31, 32, 33, 34 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), const Matrix3x4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(146, 152, 158, 164), t1[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(398, 416, 434, 452), t1[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(650, 680, 710, 740), t1[2]);
	}

	// Matrix4x3 * Matrix3x3 -> Matrix4x3
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 m1
		{
			Vector3{ 11, 12, 13 },
			Vector3{ 21, 22, 23 },
			Vector3{ 31, 32, 33 },
			Vector3{ 41, 42, 43 },
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2
		{
			Vector3{  1,  2,  3 },
			Vector3{  5,  6,  7 },
			Vector3{  9, 10, 11 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t1 = m1 * m2;
		static_assert(std::is_same<decltype(t1), const Matrix4x3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(188, 224, 260), t1[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(338, 404, 470), t1[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(488, 584, 680), t1[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(638, 764, 890), t1[3]);
	}
}

TYPED_TEST(MathMatrix3x3Test, MulVectorTest)
{
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;
	using Vector3 = bksge::math::Vector3<TypeParam>;

	// Vector3 *= Matrix3x3
	{
		Vector3 v { 1, 2, 3 };

		const Matrix3x3 m
		{
			Vector3{ 11, 12, 13 },
			Vector3{ 21, 22, 23 },
			Vector3{ 31, 32, 33 },
		};

		auto t = v *= m;
		static_assert(std::is_same<decltype(t), Vector3>::value, "");
		EXPECT_EQ(Vector3(146, 152, 158), v);
		EXPECT_EQ(t, v);
	}

	// Vector3 * Matrix3x3 -> Vector3
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v2 { -5, 6, 7 };
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m
		{
			Vector3{ 1, -2,  3 },
			Vector3{ 5,  6,  7 },
			Vector3{ 9, 10,-11 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t = v2 * m;
		static_assert(std::is_same<decltype(t), const Vector3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(88, 116, -50), t);
	}
}

TYPED_TEST(MathMatrix3x3Test, DivScalarTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix3x3 /= スカラー
	{
		Matrix3x3 m1
		{
			Vector3{10, 12, 14},
			Vector3{18, 20, 22},
			Vector3{26, 28, 30},
		};

		{
			Matrix3x3 t = (m1 /= 2);
			EXPECT_EQ(Vector3( 5,  6,  7), m1[0]);
			EXPECT_EQ(Vector3( 9, 10, 11), m1[1]);
			EXPECT_EQ(Vector3(13, 14, 15), m1[2]);
			EXPECT_EQ(t, m1);
		}
		{
			Matrix3x3 t = (m1 /= 0.5);
			EXPECT_EQ(Vector3(10, 12, 14), m1[0]);
			EXPECT_EQ(Vector3(18, 20, 22), m1[1]);
			EXPECT_EQ(Vector3(26, 28, 30), m1[2]);
			EXPECT_EQ(t, m1);
		}
	}

	// Matrix3x3 / スカラー
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
		{
			Vector3{10, 12, 14},
			Vector3{20, 22, 24},
			Vector3{30, 32, 34},
		};

		{
			BKSGE_CONSTEXPR_OR_CONST Matrix3x3 t = m1 / 2;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 5,  6,  7), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(10, 11, 12), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(15, 16, 17), t[2]);
		}
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix3x3 t = m1 / 0.25;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 40,  48,  56), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 80,  88,  96), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(120, 128, 136), t[2]);
		}
	}
}

TYPED_TEST(MathMatrix3x3Test, CompareTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix3x3  m1
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x3  m2
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x3  m3
	{
		Vector3{10, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, 33},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x3  m4
	{
		Vector3{11, 12, 13},
		Vector3{21, 23, 23},
		Vector3{31, 32, 33},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x3  m5
	{
		Vector3{11, 12, 13},
		Vector3{21, 22, 23},
		Vector3{31, 32, -33},
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

TYPED_TEST(MathMatrix3x3Test, OutputStreamTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix3x3 const m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};
		std::stringstream ss;
		ss << m;
		EXPECT_EQ("{ { 11, 12, 13 }, { 21, 22, 23 }, { 31, 32, 33 } }", ss.str());
	}
	{
		Matrix3x3 const m
		{
			Vector3{51, 52, 53},
			Vector3{61, 62, 63},
			Vector3{71, 72, 73},
		};
		std::wstringstream ss;
		ss << m;
		EXPECT_EQ(L"{ { 51, 52, 53 }, { 61, 62, 63 }, { 71, 72, 73 } }", ss.str());
	}
}

TYPED_TEST(MathMatrix3x3Test, TupleElementTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(std::is_same<typename std::tuple_element<0, Matrix3x3>::type, Vector3>::value, "");
	static_assert(std::is_same<typename std::tuple_element<1, Matrix3x3>::type, Vector3>::value, "");
	static_assert(std::is_same<typename std::tuple_element<2, Matrix3x3>::type, Vector3>::value, "");
}

TYPED_TEST(MathMatrix3x3Test, TupleGetTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};

		EXPECT_EQ(Vector3(11, 12, 13), bksge::get<0>(m));
		EXPECT_EQ(Vector3(21, 22, 23), bksge::get<1>(m));
		EXPECT_EQ(Vector3(31, 32, 33), bksge::get<2>(m));

		bksge::get<0>(m) = Vector3{51, 52, 53};

		EXPECT_EQ(Vector3(51, 52, 53), m[0]);
		EXPECT_EQ(Vector3(21, 22, 23), m[1]);
		EXPECT_EQ(Vector3(31, 32, 33), m[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m
		{
			Vector3{11, 12, 13},
			Vector3{21, 22, 23},
			Vector3{31, 32, 33},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), bksge::get<0>(m));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), bksge::get<1>(m));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), bksge::get<2>(m));
	}
}

TYPED_TEST(MathMatrix3x3Test, TupleSizeTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	static_assert(std::tuple_size<Matrix3x3>::value == 3, "");
}

TYPED_TEST(MathMatrix3x3Test, ZeroTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix3x3::Zero();
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 0), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 0), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 0), m[2]);
	}
	{
		const auto m = Matrix3x3::Zero();
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");
		EXPECT_EQ(Vector3(0, 0, 0), m[0]);
		EXPECT_EQ(Vector3(0, 0, 0), m[1]);
		EXPECT_EQ(Vector3(0, 0, 0), m[2]);
	}
}

TYPED_TEST(MathMatrix3x3Test, IdentityTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix3x3::Identity();
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 0, 0), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 1, 0), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 1), m[2]);
	}
	{
		const auto m = Matrix3x3::Identity();
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");
		EXPECT_EQ(Vector3(1, 0, 0), m[0]);
		EXPECT_EQ(Vector3(0, 1, 0), m[1]);
		EXPECT_EQ(Vector3(0, 0, 1), m[2]);
	}
}

TYPED_TEST(MathMatrix3x3Test, TransposedTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
	{
		Vector3{ 11, 12, 13 },
		Vector3{ 21, 22, 23 },
		Vector3{ 31, 32, 33 },
	};

	BKSGE_CONSTEXPR_OR_CONST auto m2 = Transposed(m1);
	static_assert(std::is_same<decltype(m2), const Matrix3x3>::value, "");
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 21, 31), m2[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(12, 22, 32), m2[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(13, 23, 33), m2[2]);

	BKSGE_CONSTEXPR_OR_CONST auto m3 = Transposed(m2);
	static_assert(std::is_same<decltype(m3), const Matrix3x3>::value, "");
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(11, 12, 13), m3[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(21, 22, 23), m3[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(31, 32, 33), m3[2]);

	BKSGE_CONSTEXPR_EXPECT_EQ(m1, m3);
}

TYPED_TEST(MathMatrix3x3Test, ResizedTest)
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
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2 = bksge::math::Resized<3, 3>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 expected
		{
			Vector3{ 1, 2, 3 },
			Vector3{ 4, 5, 6 },
			Vector3{ 7, 8, 9 },
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

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2 = bksge::math::Resized<3, 3>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 expected
		{
			Vector3{ 10, 11, 12 },
			Vector3{ 20, 21, 22 },
			Vector3{ 30, 31, 32 },
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

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2 = bksge::math::Resized<3, 3>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 expected
		{
			Vector3{ 10, 11, 12 },
			Vector3{ 20, 21, 22 },
			Vector3{ 30, 31, 32 },
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

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2 = bksge::math::Resized<3, 3>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 expected
		{
			Vector3{ 11, 12, 13 },
			Vector3{ 21, 22, 23 },
			Vector3{ 31, 32, 33 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m2);
	}
}

TYPED_TEST(MathMatrix3x3Test, InversedTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m
		{
			Vector3{ 3, 2, 1 },
			Vector3{ 1, 3, 1 },
			Vector3{ 2, 2, 1 },
		};

		BKSGE_CXX14_CONSTEXPR_OR_CONST auto m_inv = Inversed(m);
		static_assert(std::is_same<decltype(m_inv), const Matrix3x3>::value, "");

		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Vector3( 1,  0, -1), m_inv[0]);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Vector3( 1,  1, -2), m_inv[1]);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Vector3(-4, -2,  7), m_inv[2]);

		// 逆行列の逆行列はもとの行列にもどる
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto m_inv_inv = Inversed(m_inv);
		static_assert(std::is_same<decltype(m_inv_inv), const Matrix3x3>::value, "");
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(m, m_inv_inv);

		// 行列とその逆行列をかけると単位行列になる
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto m2 = m * m_inv;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Matrix3x3::Identity(), m2);

		BKSGE_CXX14_CONSTEXPR_OR_CONST auto m3 = m_inv * m;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Matrix3x3::Identity(), m3);
	}
}

TYPED_TEST(MathMatrix3x3Test, DeterminantTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m1
	{
		Vector3{ 1, 0, 2 },
		Vector3{ 3, 0, 1 },
		Vector3{ 2, 1, 1 },
	};

	BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m2
	{
		Vector3{ 1, 2, 1 },
		Vector3{ 2, 1, 0 },
		Vector3{ 1, 1, 2 },
	};

	BKSGE_CONSTEXPR_OR_CONST Matrix3x3 m3
	{
		Vector3{  9, -3,  2 },
		Vector3{  0,  8, -1 },
		Vector3{ -2, -3,  5 },
	};

	BKSGE_CONSTEXPR_EXPECT_EQ(TypeParam(  5), Determinant(m1));
	BKSGE_CONSTEXPR_EXPECT_EQ(TypeParam( -5), Determinant(m2));
	BKSGE_CONSTEXPR_EXPECT_EQ(TypeParam(359), Determinant(m3));
}

TYPED_TEST(MathMatrix3x3Test, MakeTranslationTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 trans(3, 4);
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix3x3::MakeTranslation(trans);
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 expected
		{
			Vector3{ 1,  0,  0 },
			Vector3{ 0,  1,  0 },
			Vector3{ 3,  4,  1 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m);
	}
	{
		const auto m = Matrix3x3::MakeTranslation(Vector2{-4, 5});
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");

		const Matrix3x3 expected
		{
			Vector3{  1,  0,  0 },
			Vector3{  0,  1,  0 },
			Vector3{ -4,  5,  1 },
		};

		EXPECT_EQ(expected, m);
	}
	{
		const auto m = Matrix3x3::MakeTranslation(1, 2);
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");

		const Matrix3x3 expected
		{
			Vector3{  1,  0,  0 },
			Vector3{  0,  1,  0 },
			Vector3{  1,  2,  1 },
		};

		EXPECT_EQ(expected, m);
	}
}

TYPED_TEST(MathMatrix3x3Test, MakeScaleTest)
{
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;
	using Vector3 = bksge::math::Vector3<TypeParam>;
	using Scale3 = bksge::math::Scale3<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST Scale3 s(2, 3, 4);
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix3x3::MakeScale(s);
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 expected
		{
			Vector3{ 2,  0,  0 },
			Vector3{ 0,  3,  0 },
			Vector3{ 0,  0,  4 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix3x3::MakeScale(Scale3{ 5, -4, 3 });
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 expected
		{
			Vector3{ 5,  0,  0 },
			Vector3{ 0, -4,  0 },
			Vector3{ 0,  0,  3 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m);
	}
}

TYPED_TEST(MathMatrix3x3FloatTest, MakeRotationXTest)
{
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;

	const double error = 0.0000001;

	{
		auto const m = Matrix3x3::MakeRotationX(bksge::degrees_to_radians(0));
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");
		EXPECT_EQ(Matrix3x3::Identity(), m);
	}
	{
		auto const m = Matrix3x3::MakeRotationX(bksge::degrees_to_radians(30));
		EXPECT_NEAR( 1.00000000000000000, (double)m[0][0], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[0][1], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[0][2], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[1][0], error);
		EXPECT_NEAR( 0.86602538824081421, (double)m[1][1], error);
		EXPECT_NEAR( 0.50000000000000000, (double)m[1][2], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[2][0], error);
		EXPECT_NEAR(-0.50000000000000000, (double)m[2][1], error);
		EXPECT_NEAR( 0.86602538824081421, (double)m[2][2], error);
	}
	{
		auto const m = Matrix3x3::MakeRotationX(bksge::degrees_to_radians(90));
		EXPECT_NEAR( 1.00000000000000000, (double)m[0][0], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[0][1], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[0][2], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[1][0], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[1][1], error);
		EXPECT_NEAR( 1.00000000000000000, (double)m[1][2], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[2][0], error);
		EXPECT_NEAR(-1.00000000000000000, (double)m[2][1], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[2][2], error);
	}
}

TYPED_TEST(MathMatrix3x3FloatTest, MakeRotationYTest)
{
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;

	const double error = 0.0000001;

	{
		auto const m = Matrix3x3::MakeRotationY(bksge::degrees_to_radians(0));
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");
		EXPECT_EQ(Matrix3x3::Identity(), m);
	}
	{
		auto const m = Matrix3x3::MakeRotationY(bksge::degrees_to_radians(45));
		EXPECT_NEAR( 0.70710676908493042, (double)m[0][0], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[0][1], error);
		EXPECT_NEAR(-0.70710676908493042, (double)m[0][2], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[1][0], error);
		EXPECT_NEAR( 1.00000000000000000, (double)m[1][1], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[1][2], error);
		EXPECT_NEAR( 0.70710676908493042, (double)m[2][0], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[2][1], error);
		EXPECT_NEAR( 0.70710676908493042, (double)m[2][2], error);
	}
	{
		auto const m = Matrix3x3::MakeRotationY(bksge::degrees_to_radians(90));
		EXPECT_NEAR( 0.00000000000000000, (double)m[0][0], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[0][1], error);
		EXPECT_NEAR(-1.00000000000000000, (double)m[0][2], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[1][0], error);
		EXPECT_NEAR( 1.00000000000000000, (double)m[1][1], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[1][2], error);
		EXPECT_NEAR( 1.00000000000000000, (double)m[2][0], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[2][1], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[2][2], error);
	}
}

TYPED_TEST(MathMatrix3x3FloatTest, MakeRotationZTest)
{
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;

	const double error = 0.0000001;

	{
		auto const m = Matrix3x3::MakeRotationZ(bksge::degrees_to_radians(0));
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");
		EXPECT_EQ(Matrix3x3::Identity(), m);
	}
	{
		auto const m = Matrix3x3::MakeRotationZ(bksge::degrees_to_radians(60));
		EXPECT_NEAR( 0.50000000000000000, (double)m[0][0], error);
		EXPECT_NEAR( 0.86602538824081421, (double)m[0][1], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[0][2], error);
		EXPECT_NEAR(-0.86602538824081421, (double)m[1][0], error);
		EXPECT_NEAR( 0.50000000000000000, (double)m[1][1], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[1][2], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[2][0], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[2][1], error);
		EXPECT_NEAR( 1.00000000000000000, (double)m[2][2], error);
	}
	{
		auto const m = Matrix3x3::MakeRotationZ(bksge::degrees_to_radians(90));
		EXPECT_NEAR( 0.00000000000000000, (double)m[0][0], error);
		EXPECT_NEAR( 1.00000000000000000, (double)m[0][1], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[0][2], error);
		EXPECT_NEAR(-1.00000000000000000, (double)m[1][0], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[1][1], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[1][2], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[2][0], error);
		EXPECT_NEAR( 0.00000000000000000, (double)m[2][1], error);
		EXPECT_NEAR( 1.00000000000000000, (double)m[2][2], error);
	}
}

TYPED_TEST(MathMatrix3x3FloatTest, MakeRotationTest)
{
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;
	using Vector3 = bksge::math::Vector3<TypeParam>;

	const double error = 0.000001;

	{
		auto const m = Matrix3x3::MakeRotation(Vector3(1, 2, 3), bksge::degrees_to_radians(90));
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");
		EXPECT_NEAR( 0.07142856717109680, (double)m[0][0], error);
		EXPECT_NEAR( 0.94464081525802612, (double)m[0][1], error);
		EXPECT_NEAR(-0.32023677229881287, (double)m[0][2], error);
		EXPECT_NEAR(-0.65892654657363892, (double)m[1][0], error);
		EXPECT_NEAR( 0.28571426868438721, (double)m[1][1], error);
		EXPECT_NEAR( 0.69583261013031006, (double)m[1][2], error);
		EXPECT_NEAR( 0.74880814552307129, (double)m[2][0], error);
		EXPECT_NEAR( 0.16131016612052917, (double)m[2][1], error);
		EXPECT_NEAR( 0.64285707473754883, (double)m[2][2], error);
	}
	{
		auto const m = Matrix3x3::MakeRotation(Vector3(-1, 1, 10), bksge::degrees_to_radians(120));
		EXPECT_NEAR(-0.48529410362243652, (double)m[0][0], error);
		EXPECT_NEAR( 0.84278708696365356, (double)m[0][1], error);
		EXPECT_NEAR(-0.23280812799930573, (double)m[0][2], error);
		EXPECT_NEAR(-0.87219887971878052, (double)m[1][0], error);
		EXPECT_NEAR(-0.48529410362243652, (double)m[1][1], error);
		EXPECT_NEAR( 0.06130953878164291, (double)m[1][2], error);
		EXPECT_NEAR(-0.06130953878164291, (double)m[2][0], error);
		EXPECT_NEAR( 0.23280812799930573, (double)m[2][1], error);
		EXPECT_NEAR( 0.97058844566345215, (double)m[2][2], error);
	}
}

TYPED_TEST(MathMatrix3x3Test, MakeShearTest)
{
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;
	using Vector3 = bksge::math::Vector3<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix3x3::MakeShear(4, 5, 6);
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");

		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 expected
		{
			Vector3{ 1,  5,  6 },
			Vector3{ 4,  1,  6 },
			Vector3{ 4,  5,  1 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m);
	}
	{
		const auto m = Matrix3x3::MakeShear(-1, 2, -3);
		static_assert(std::is_same<decltype(m), const Matrix3x3>::value, "");

		const Matrix3x3 expected
		{
			Vector3{  1,  2, -3 },
			Vector3{ -1,  1, -3 },
			Vector3{ -1,  2,  1 },
		};

		EXPECT_EQ(expected, m);
	}
}

}	// namespace matrix3x3_test

}	// namespace bksge_math_test