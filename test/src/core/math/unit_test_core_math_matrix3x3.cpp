/**
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
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/fnd/cmath/degrees_to_radians.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"
#include "math_test_utility.hpp"

namespace bksge_math_test
{

namespace matrix3x3_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Matrix3x3f = bksge::math::Matrix3x3<float>;
using Matrix3x3i = bksge::math::Matrix3x3<int>;


using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathMatrix3x3Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathMatrix3x3Test, MathTestTypes);

TYPED_TEST(MathMatrix3x3Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	static_assert(sizeof(Matrix3x3) == sizeof(T) * 3 * 3, "");
	static_assert(bksge::is_default_constructible<Matrix3x3>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Matrix3x3>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Matrix3x3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][2]);
	}
}

TYPED_TEST(MathMatrix3x3Test, Vector3ConstructTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(!bksge::is_constructible<Matrix3x3, Vector3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( bksge::is_constructible<Matrix3x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x3, Vector3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix3x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, Vector3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( bksge::is_implicitly_constructible<Matrix3x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, Vector3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
		};
		BKSGE_CONSTEXPR_EXPECT_EQ( 0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 1, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 2, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 5, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 6, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 8, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 9, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[2][2]);
	}

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 v(
			Vector3(11, 12, 13),
			Vector3(21, 22, 23),
			Vector3(31, 32, 33)
		);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(21, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(22, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(23, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(31, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(33, v[2][2]);
	}
}

TYPED_TEST(MathMatrix3x3Test, Value1ConstructTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	static_assert(!bksge::is_constructible<Matrix3x3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x3, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x3, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x3, T, T>::value, "");
	static_assert( bksge::is_constructible<Matrix3x3, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x3, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x3, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x3, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix3x3, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x3, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 v{7};
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2][2]);
	}
}

TYPED_TEST(MathMatrix3x3Test, CopyConstructTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	static_assert(bksge::is_constructible<Matrix3x3,  Matrix3x3  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x3,  Matrix3x3i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x3,  Matrix3x3f const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x3i, Matrix3x3  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x3i, Matrix3x3i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x3i, Matrix3x3f const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x3f, Matrix3x3  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x3f, Matrix3x3i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix3x3f, Matrix3x3f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Matrix3x3,  Matrix3x3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x3,  Matrix3x3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x3,  Matrix3x3f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x3i, Matrix3x3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x3i, Matrix3x3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x3i, Matrix3x3f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x3f, Matrix3x3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x3f, Matrix3x3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix3x3f, Matrix3x3f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Matrix3x3,  Matrix3x3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3,  Matrix3x3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3,  Matrix3x3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3i, Matrix3x3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3i, Matrix3x3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3i, Matrix3x3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3f, Matrix3x3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3f, Matrix3x3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix3x3f, Matrix3x3f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Matrix3x3 v1{
		{ 0,  1,  2},
		{ 4,  5,  6},
		{ 8,  9, 10},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x3  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x3i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x3f v4{v2};

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, v2[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, v2[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, v2[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, v2[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, v2[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, v2[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, v2[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, v2[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(10, v2[2][2]);

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, v3[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, v3[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, v3[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, v3[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, v3[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, v3[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, v3[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, v3[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(10, v3[2][2]);

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, v4[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, v4[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, v4[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, v4[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, v4[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, v4[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, v4[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, v4[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(10, v4[2][2]);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool FromQuaternionTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Quaternion = bksge::math::Quaternion<T>;
	using Vector3 = bksge::math::Vector3<T>;

	const double error = 0.000001;

	{
		auto q = Quaternion::Identity();
		Matrix3x3 m(q);
		auto expected = Matrix3x3::Identity();

		VERIFY(expected == m);
	}
	{
		const auto angle = bksge::degrees_to_radians(30);
		const auto q = Quaternion::MakeRotationX(angle);
		const Matrix3x3 m(q);
		const auto expected = Matrix3x3::MakeRotationX(angle);
		VERIFY(IsNear(expected, m, error));
	}
	{
		const auto angle = bksge::degrees_to_radians(45);
		const auto q = Quaternion::MakeRotationY(angle);
		const Matrix3x3 m(q);
		const auto expected = Matrix3x3::MakeRotationY(angle);
		VERIFY(IsNear(expected, m, error));
	}
	{
		const auto angle = bksge::degrees_to_radians(60);
		const auto q = Quaternion::MakeRotationZ(angle);
		const Matrix3x3 m(q);
		const auto expected = Matrix3x3::MakeRotationZ(angle);
		VERIFY(IsNear(expected, m, error));
	}
	{
		const Vector3 axis{1, 2, 3};
		const auto angle = bksge::degrees_to_radians(90);
		const auto q = Quaternion::MakeRotation(axis, angle);
		const Matrix3x3 m(q);
		const auto expected = Matrix3x3::MakeRotation(axis, angle);
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, FromQuaternionTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(FromQuaternionTest<TypeParam>());
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix3x3 v{
		{ 0,  1,  2},
		{ 4,  5,  6},
		{ 8,  9, 10},
	};
	VERIFY(v[0] == Vector3{ 0,  1,  2});
	VERIFY(v[1] == Vector3{ 4,  5,  6});
	VERIFY(v[2] == Vector3{ 8,  9, 10});

	v = Matrix3x3(
		{-2, 3, -4},
		{-2, 3, -4},
		{-2, 3, -4}
	);
	VERIFY(v[0] == Vector3{-2, 3, -4});
	VERIFY(v[1] == Vector3{-2, 3, -4});
	VERIFY(v[2] == Vector3{-2, 3, -4});

	v = Matrix3x3i(
		{ 3, -4,  5},
		{ 7,  8,  9},
		{11, 12, 13}
	);
	VERIFY(v[0] == Vector3{ 3, -4,  5});
	VERIFY(v[1] == Vector3{ 7,  8,  9});
	VERIFY(v[2] == Vector3{11, 12, 13});

	// 自己代入
	v = v;
	VERIFY(v[0] == Vector3{ 3, -4,  5});
	VERIFY(v[1] == Vector3{ 7,  8,  9});
	VERIFY(v[2] == Vector3{11, 12, 13});

	// 多重代入
	Matrix3x3 v2;
	v2 = v = Matrix3x3f(
		{11,12,13},
		{21,22,23},
		{31,32,33}
	);
	VERIFY(v[0] == Vector3{11,12,13});
	VERIFY(v[1] == Vector3{21,22,23});
	VERIFY(v[2] == Vector3{31,32,33});
	VERIFY(v2[0] == Vector3{11,12,13});
	VERIFY(v2[1] == Vector3{21,22,23});
	VERIFY(v2[2] == Vector3{31,32,33});

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathMatrix3x3Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix3x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
		};
		VERIFY(v[0] == Vector3( 0,  1,  2));
		VERIFY(v[1] == Vector3( 4,  5,  6));
		VERIFY(v[2] == Vector3( 8,  9, 10));

		v[0] = Vector3(21,22,23);

		VERIFY(v[0] == Vector3(21, 22, 23));
		VERIFY(v[1] == Vector3( 4,  5,  6));
		VERIFY(v[2] == Vector3( 8,  9, 10));
	}
	{
		Matrix3x3 const v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
		};
		VERIFY(v[0] == Vector3( 0,  1,  2));
		VERIFY(v[1] == Vector3( 4,  5,  6));
		VERIFY(v[2] == Vector3( 8,  9, 10));
	}
	return true;
}

TYPED_TEST(MathMatrix3x3Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix3x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
		};
		VERIFY(v.at(0) == Vector3( 0,  1,  2));
		VERIFY(v.at(1) == Vector3( 4,  5,  6));
		VERIFY(v.at(2) == Vector3( 8,  9, 10));

		v.at(0) = Vector3(21,22,23);

		VERIFY(v.at(0) == Vector3(21, 22, 23));
		VERIFY(v.at(1) == Vector3( 4,  5,  6));
		VERIFY(v.at(2) == Vector3( 8,  9, 10));
	}
	{
		Matrix3x3 const v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
		};
		VERIFY(v.at(0) == Vector3( 0,  1,  2));
		VERIFY(v.at(1) == Vector3( 4,  5,  6));
		VERIFY(v.at(2) == Vector3( 8,  9, 10));
	}
	return true;
}

TYPED_TEST(MathMatrix3x3Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;
	{
		Matrix3x3 v;
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
	{
		Matrix3x3 const v;
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix3x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
		};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == Vector3( 0,  1,  2));
		*p = Vector3(5);
		++p;
		VERIFY(*p == Vector3( 4,  5,  6));
		p++;
		VERIFY(*p == Vector3( 8,  9, 10));
		*p = Vector3(6);

		VERIFY(v == Matrix3x3{
			{ 5,  5,  5},
			{ 4,  5,  6},
			{ 6,  6,  6}});
	}
	{
		Matrix3x3 const v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
		};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == Vector3( 0,  1,  2));
		++p;
		VERIFY(*p == Vector3( 4,  5,  6));
		p++;
		VERIFY(*p == Vector3( 8,  9, 10));
	}
	return true;
}

TYPED_TEST(MathMatrix3x3Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// begin, end (non const)
	{
		Matrix3x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
		};
		auto it = v.begin();
		VERIFY(it != v.end());
		VERIFY(*it == Vector3{ 0,  1,  2});
		*it++ = Vector3{5};
		VERIFY(it != v.end());
		VERIFY(*it == Vector3{ 4,  5,  6});
		*++it = Vector3{6};
		VERIFY(it != v.end());
		VERIFY(*it == Vector3{ 6,  6,  6});
		it++;
		VERIFY(it == v.end());

		VERIFY(v == Matrix3x3(
			{ 5,  5,  5},
			{ 4,  5,  6},
			{ 6,  6,  6}));
	}
	// begin, end (const)
	{
		Matrix3x3 const v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
		};
		auto it = v.begin();
		VERIFY(it != v.end());

		VERIFY(it[0] == Vector3{ 0,  1,  2});
		VERIFY(it[1] == Vector3{ 4,  5,  6});
		VERIFY(it[2] == Vector3{ 8,  9, 10});

		VERIFY(*it++ == Vector3{ 0,  1,  2});
		VERIFY(it != v.end());
		VERIFY(*++it == Vector3{ 8,  9, 10});
		VERIFY(it != v.end());
		VERIFY(*it++ == Vector3{ 8,  9, 10});
		VERIFY(it == v.end());
	}
	// cbegin, cend
	{
		Matrix3x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
		};
		auto it = v.cbegin();
		VERIFY(it != v.cend());

		VERIFY(it[0] == Vector3{ 0,  1,  2});
		VERIFY(it[1] == Vector3{ 4,  5,  6});
		VERIFY(it[2] == Vector3{ 8,  9, 10});

		VERIFY(*it++ == Vector3{ 0,  1,  2});
		VERIFY(it != v.cend());
		VERIFY(*++it == Vector3{ 8,  9, 10});
		VERIFY(it != v.cend());
		VERIFY(*it++ == Vector3{ 8,  9, 10});
		VERIFY(it == v.cend());
	}
	return true;
}

TYPED_TEST(MathMatrix3x3Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// rbegin, rend (non const)
	{
		Matrix3x3 v{
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		auto it = v.rbegin();
		VERIFY(it != v.rend());
		VERIFY(*it == Vector3{12, 13, 14});
		*it++ = Vector3{5};
		VERIFY(it != v.rend());
		VERIFY(*it == Vector3{ 8,  9, 10});
		*++it = Vector3{6};
		VERIFY(it != v.rend());
		VERIFY(*it == Vector3{ 6,  6,  6});
		it++;
		VERIFY(it == v.rend());

		VERIFY(v == Matrix3x3(
			{ 6,  6,  6},
			{ 8,  9, 10},
			{ 5,  5,  5}));
	}
	// rbegin, rend (const)
	{
		Matrix3x3 const v{
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		auto it = v.rbegin();
		VERIFY(it != v.rend());

		VERIFY(it[0] == Vector3{12, 13, 14});
		VERIFY(it[1] == Vector3{ 8,  9, 10});
		VERIFY(it[2] == Vector3{ 4,  5,  6});

		VERIFY(*it++ == Vector3{12, 13, 14});
		VERIFY(it != v.rend());
		VERIFY(*++it == Vector3{ 4,  5,  6});
		VERIFY(it != v.rend());
		VERIFY(*it++ == Vector3{ 4,  5,  6});
		VERIFY(it == v.rend());
	}
	// crbegin, crend
	{
		Matrix3x3 v{
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		auto it = v.crbegin();
		VERIFY(it != v.crend());

		VERIFY(it[0] == Vector3{12, 13, 14});
		VERIFY(it[1] == Vector3{ 8,  9, 10});
		VERIFY(it[2] == Vector3{ 4,  5,  6});

		VERIFY(*it++ == Vector3{12, 13, 14});
		VERIFY(it != v.crend());
		VERIFY(*++it == Vector3{ 4,  5,  6});
		VERIFY(it != v.crend());
		VERIFY(*it++ == Vector3{ 4,  5,  6});
		VERIFY(it == v.crend());
	}
	return true;
}

TYPED_TEST(MathMatrix3x3Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	Matrix3x3 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathMatrix3x3Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	Matrix3x3 v1{};
	VERIFY(v1.size() == 3);
	return true;
}

TYPED_TEST(MathMatrix3x3Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	Matrix3x3 v1{};
	VERIFY(v1.max_size() == 3);
	return true;
}

TYPED_TEST(MathMatrix3x3Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix3x3 v =
		{
			{11,12,13},
			{21,22,23},
			{31,32,33},
		};
		VERIFY(v.x() == Vector3{11,12,13});
		VERIFY(v.y() == Vector3{21,22,23});
		VERIFY(v.z() == Vector3{31,32,33});

		v.x() = Vector3{0,1,2};
		v.y().x() = -1;

		VERIFY(v.x() == Vector3{ 0, 1, 2});
		VERIFY(v.y() == Vector3{-1,22,23});
		VERIFY(v.z() == Vector3{31,32,33});
		VERIFY(v[0] == Vector3{ 0, 1, 2});
		VERIFY(v[1] == Vector3{-1,22,23});
		VERIFY(v[2] == Vector3{31,32,33});
	}
	{
		Matrix3x3 const v =
		{
			{11,12,13},
			{21,22,23},
			{31,32,33},
		};
		VERIFY(v.x() == Vector3{11,12,13});
		VERIFY(v.y() == Vector3{21,22,23});
		VERIFY(v.z() == Vector3{31,32,33});
	}
	return true;
}

TYPED_TEST(MathMatrix3x3Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	//using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix3x3 const v1 =
	{
		{11,12,13},
		{21,22,23},
		{31,32,33},
	};

	{
		auto const v2 = v1.yzx();
		//static_assert(bksge::is_same<decltype(v2), Matrix3x3 const>::value, "");
		VERIFY(v2[0] == Vector3{21, 22, 23});
		VERIFY(v2[1] == Vector3{31, 32, 33});
		VERIFY(v2[2] == Vector3{11, 12, 13});
	}
	{
		auto const v2 = v1.zyzx();
		//static_assert(bksge::is_same<decltype(v2), Matrix4x3 const>::value, "");
		VERIFY(v2[0] == Vector3{31, 32, 33});
		VERIFY(v2[1] == Vector3{21, 22, 23});
		VERIFY(v2[2] == Vector3{31, 32, 33});
		VERIFY(v2[3] == Vector3{11, 12, 13});
	}
	return true;
}

TYPED_TEST(MathMatrix3x3Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix3x3 v1 =
	{
		{11,12,13},
		{21,22,23},
		{31,32,33},
	};

	Matrix3x3 v2 =
	{
		{51,52,53},
		{61,62,63},
		{71,72,73},
	};

	v1.swap(v2);

	VERIFY(v1[0] == Vector3{51,52,53});
	VERIFY(v1[1] == Vector3{61,62,63});
	VERIFY(v1[2] == Vector3{71,72,73});
	VERIFY(v2[0] == Vector3{11,12,13});
	VERIFY(v2[1] == Vector3{21,22,23});
	VERIFY(v2[2] == Vector3{31,32,33});

	bksge::ranges::swap(v1, v2);

	VERIFY(v1[0] == Vector3{11,12,13});
	VERIFY(v1[1] == Vector3{21,22,23});
	VERIFY(v1[2] == Vector3{31,32,33});
	VERIFY(v2[0] == Vector3{51,52,53});
	VERIFY(v2[1] == Vector3{61,62,63});
	VERIFY(v2[2] == Vector3{71,72,73});

	return true;
}

TYPED_TEST(MathMatrix3x3Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix3x3 const v1
		{
			{ 0, -1,  2},
			{ 4,  5, -6},
			{-8,  9, 10},
		};
		auto const v2 = +v1;
		auto const v3 = -v1;
		static_assert(bksge::is_same<decltype(v2), Matrix3x3 const>::value, "");
		static_assert(bksge::is_same<decltype(v3), Matrix3x3 const>::value, "");

		VERIFY(v2[0] ==  Vector3{ 0, -1,  2});
		VERIFY(v2[1] ==  Vector3{ 4,  5, -6});
		VERIFY(v2[2] ==  Vector3{-8,  9, 10});
		VERIFY(v3[0] == -Vector3{ 0, -1,  2});
		VERIFY(v3[1] == -Vector3{ 4,  5, -6});
		VERIFY(v3[2] == -Vector3{-8,  9, 10});
	}
	return true;
}

TYPED_TEST(MathMatrix3x3Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix3x3 += Matrix3x3
	{
		Matrix3x3 v;

		auto t = (v += Matrix3x3(
			{ 0, -1,  2},
			{ 4,  5, -6},
			{-8,  9, 10}
		));
		static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
		VERIFY(t[0] == Vector3( 0, -1,  2));
		VERIFY(t[1] == Vector3( 4,  5, -6));
		VERIFY(t[2] == Vector3(-8,  9, 10));
		VERIFY(v == t);
	}
	// Matrix3x3 + Matrix3x3 -> Matrix3x3
	{
		Matrix3x3 const m1
		{
			{-21,  22,  23},
			{ 24, -25,  26},
			{ 27,  28, -29},
		};
		Matrix3x3 const m2
		{
			{ 31,  32, -33},
			{ 34, -35,  36},
			{-37,  38,  39},
		};
		auto m3 = m1 + m2;
		static_assert(bksge::is_same<decltype(m3), Matrix3x3>::value, "");
		VERIFY(m3[0] == Vector3( 10,  54, -10));
		VERIFY(m3[1] == Vector3( 58, -60,  62));
		VERIFY(m3[2] == Vector3(-10,  66,  10));
	}
	return true;
}

TYPED_TEST(MathMatrix3x3Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix3x3 -= Matrix3x3
	{
		Matrix3x3 v;

		auto t = (v -= Matrix3x3(
			{ 0, -1,  2},
			{ 4,  5, -6},
			{-8,  9, 10}
		));
		static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
		VERIFY(t[0] == -Vector3( 0, -1,  2));
		VERIFY(t[1] == -Vector3( 4,  5, -6));
		VERIFY(t[2] == -Vector3(-8,  9, 10));
		VERIFY(v == t);
	}
	// Matrix3x3 - Matrix3x3 -> Matrix3x3
	{
		Matrix3x3 const m1
		{
			{10, 11, 12},
			{20, 21, 22},
			{30, 31, 32},
		};
		Matrix3x3 const m2
		{
			{0, 9, 1},
			{8, 4, 7},
			{6, 5, 3},
		};
		auto m3 = m1 - m2;
		static_assert(bksge::is_same<decltype(m3), Matrix3x3>::value, "");
		VERIFY(m3[0] == Vector3(10,  2, 11));
		VERIFY(m3[1] == Vector3(12, 17, 15));
		VERIFY(m3[2] == Vector3(24, 26, 29));
	}
	return true;
}

TYPED_TEST(MathMatrix3x3Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix3x3 *= スカラー
	{
		Matrix3x3 m1
		{
			{ 1,  2,  3},
			{ 5,  6,  7},
			{ 9, 10, 11},
		};
		{
			auto t = (m1 *= 2);
			static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
			VERIFY(Vector3( 2,  4,  6) == m1[0]);
			VERIFY(Vector3(10, 12, 14) == m1[1]);
			VERIFY(Vector3(18, 20, 22) == m1[2]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
			VERIFY(Vector3( 5, 10, 15) == m1[0]);
			VERIFY(Vector3(25, 30, 35) == m1[1]);
			VERIFY(Vector3(45, 50, 55) == m1[2]);
			VERIFY(t == m1);
		}
	}

	// Matrix3x3 * スカラー -> Matrix3x3
	{
		Matrix3x3 const m1
		{
			{10, 12, 14},
			{20, 22, 24},
			{30, 32, 34},
		};
		{
			auto t = m1 * 3;
			static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
			VERIFY(Vector3( 30,  36,  42) == t[0]);
			VERIFY(Vector3( 60,  66,  72) == t[1]);
			VERIFY(Vector3( 90,  96, 102) == t[2]);
		}
		{
			auto t = m1 * 2.5;
			static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
			VERIFY(Vector3( 25,  30,  35) == t[0]);
			VERIFY(Vector3( 50,  55,  60) == t[1]);
			VERIFY(Vector3( 75,  80,  85) == t[2]);
		}
		// スカラー * Matrix3x3 -> Matrix3x3
		{
			auto t = 4 * m1;
			static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
			VERIFY(Vector3( 40,  48,  56) == t[0]);
			VERIFY(Vector3( 80,  88,  96) == t[1]);
			VERIFY(Vector3(120, 128, 136) == t[2]);
		}
		{
			auto t = -1.5 * m1;
			static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
			VERIFY(Vector3(-15, -18, -21) == t[0]);
			VERIFY(Vector3(-30, -33, -36) == t[1]);
			VERIFY(Vector3(-45, -48, -51) == t[2]);
		}
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulMatrixTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix3x3 *= Matrix3x3
	{
		Matrix3x3 m
		{
			{  2,  4,  6 },
			{ 10, 12, 14 },
			{ 18, 20, 22 },
		};

		Matrix3x3 m1
		{
			{  11, -12,  13 },
			{  21,  22, -23 },
			{ -31,  32,  33 },
		};

		auto t = (m *= m1);
		static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
		VERIFY(Vector3(-80, 256, 132) == m[0]);
		VERIFY(Vector3(-72, 592, 316) == m[1]);
		VERIFY(Vector3(-64, 928, 500) == m[2]);
		VERIFY(t == m);
	}

	// Matrix3x3 * Matrix3x3 -> Matrix3x3
	{
		Matrix3x3 const m1
		{
			{ 15, 3, -7 },
			{ 11, 4, 12 },
			{  2, 6, 13 },
		};
		Matrix3x3 const m2
		{
			{ 1,  2,  3 },
			{ 5,  6,  7 },
			{ 9, 10,-11 },
		};

		auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), Matrix3x3>::value, "");
		VERIFY(Vector3(-33, -22, 143) == t1[0]);
		VERIFY(Vector3(139, 166, -71) == t1[1]);
		VERIFY(Vector3(149, 170, -95) == t1[2]);

		auto t2 = m2 * m1;
		static_assert(bksge::is_same<decltype(t2), Matrix3x3>::value, "");
		VERIFY(Vector3( 43, 29,  56) == t2[0]);
		VERIFY(Vector3(155, 81, 128) == t2[1]);
		VERIFY(Vector3(223,  1, -86) == t2[2]);
	}

	// Matrix3x3 * Matrix3x4 -> Matrix3x4
	{
		Matrix3x3 const m1
		{
			{  1,  2,  3 },
			{  5,  6,  7 },
			{  9, 10, 11 },
		};
		Matrix3x4 const m2
		{
			{ 11, 12, 13, 14 },
			{ 21, 22, 23, 24 },
			{ 31, 32, 33, 34 },
		};

		auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), Matrix3x4>::value, "");
		VERIFY(Vector4(146, 152, 158, 164) == t1[0]);
		VERIFY(Vector4(398, 416, 434, 452) == t1[1]);
		VERIFY(Vector4(650, 680, 710, 740) == t1[2]);
	}

	// Matrix4x3 * Matrix3x3 -> Matrix4x3
	{
		Matrix4x3 const m1
		{
			{ 11, 12, 13 },
			{ 21, 22, 23 },
			{ 31, 32, 33 },
			{ 41, 42, 43 },
		};
		Matrix3x3 const m2
		{
			{  1,  2,  3 },
			{  5,  6,  7 },
			{  9, 10, 11 },
		};

		auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), Matrix4x3>::value, "");
		VERIFY(Vector3(188, 224, 260) == t1[0]);
		VERIFY(Vector3(338, 404, 470) == t1[1]);
		VERIFY(Vector3(488, 584, 680) == t1[2]);
		VERIFY(Vector3(638, 764, 890) == t1[3]);
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, MulMatrixTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulMatrixTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulVectorTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Vector3 *= Matrix3x3
	{
		Vector3 v { 1, 2, 3 };

		const Matrix3x3 m
		{
			{ 11, 12, 13 },
			{ 21, 22, 23 },
			{ 31, 32, 33 },
		};

		auto t = (v *= m);
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(Vector3(146, 152, 158) == v);
		VERIFY(t == v);
	}

	// Vector3 * Matrix3x3 -> Vector3
	{
		Vector3 const v2 { -5, 6, 7 };
		Matrix3x3 const m
		{
			{ 1, -2,  3 },
			{ 5,  6,  7 },
			{ 9, 10,-11 },
		};

		auto t = v2 * m;
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(Vector3(88, 116, -50) == t);
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, MulVectorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulVectorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix3x3 /= スカラー
	{
		Matrix3x3 m1
		{
			{10, 12, 14},
			{18, 20, 22},
			{26, 28, 30},
		};

		{
			auto t = (m1 /= 2);
			static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
			VERIFY(Vector3( 5,  6,  7) == m1[0]);
			VERIFY(Vector3( 9, 10, 11) == m1[1]);
			VERIFY(Vector3(13, 14, 15) == m1[2]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 /= 0.5);
			static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
			VERIFY(Vector3(10, 12, 14) == m1[0]);
			VERIFY(Vector3(18, 20, 22) == m1[1]);
			VERIFY(Vector3(26, 28, 30) == m1[2]);
			VERIFY(t == m1);
		}
	}

	// Matrix3x3 / スカラー
	{
		Matrix3x3 const m1
		{
			Vector3{10, 12, 14},
			Vector3{20, 22, 24},
			Vector3{30, 32, 34},
		};

		{
			auto t = m1 / 2;
			static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
			VERIFY(Vector3( 5,  6,  7) == t[0]);
			VERIFY(Vector3(10, 11, 12) == t[1]);
			VERIFY(Vector3(15, 16, 17) == t[2]);
		}
		{
			auto t = m1 / 0.25;
			static_assert(bksge::is_same<decltype(t), Matrix3x3>::value, "");
			VERIFY(Vector3( 40,  48,  56) == t[0]);
			VERIFY(Vector3( 80,  88,  96) == t[1]);
			VERIFY(Vector3(120, 128, 136) == t[2]);
		}
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	Matrix3x3 const m1
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
	};
	Matrix3x3 const m2
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
	};
	Matrix3x3 const m3
	{
		{10, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
	};
	Matrix3x3 const m4
	{
		{11, 12, 13},
		{21, 23, 23},
		{31, 32, 33},
	};
	Matrix3x3 const m5
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32,-33},
	};

	VERIFY( (m1 == m1));
	VERIFY( (m1 == m2));
	VERIFY(!(m1 == m3));
	VERIFY(!(m1 == m4));
	VERIFY(!(m1 == m5));

	VERIFY(!(m1 != m1));
	VERIFY(!(m1 != m2));
	VERIFY( (m1 != m3));
	VERIFY( (m1 != m4));
	VERIFY( (m1 != m5));

	return true;
}

TYPED_TEST(MathMatrix3x3Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathMatrix3x3Test, OutputStreamTest)
{
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;

	{
		Matrix3x3 const m
		{
			{11, 12, 13},
			{21, 22, 23},
			{31, 32, 33},
		};
		std::stringstream ss;
		ss << m;
		EXPECT_EQ("{ { 11, 12, 13 }, { 21, 22, 23 }, { 31, 32, 33 } }", ss.str());
	}
	{
		Matrix3x3 const m
		{
			{51, 52, 53},
			{61, 62, 63},
			{71, 72, 73},
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

	static_assert(bksge::is_same<typename std::tuple_element<0, Matrix3x3>::type, Vector3>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<1, Matrix3x3>::type, Vector3>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<2, Matrix3x3>::type, Vector3>::value, "");
}

TYPED_TEST(MathMatrix3x3Test, TupleSizeTest)
{
	using T = TypeParam;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	static_assert(std::tuple_size<Matrix3x3>::value == 3, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Matrix3x3 m
		{
			{11, 12, 13},
			{21, 22, 23},
			{31, 32, 33},
		};

		VERIFY(Vector3(11, 12, 13) == bksge::get<0>(m));
		VERIFY(Vector3(21, 22, 23) == bksge::get<1>(m));
		VERIFY(Vector3(31, 32, 33) == bksge::get<2>(m));

		bksge::get<0>(m) = Vector3{51, 52, 53};

		VERIFY(Vector3(51, 52, 53) == m[0]);
		VERIFY(Vector3(21, 22, 23) == m[1]);
		VERIFY(Vector3(31, 32, 33) == m[2]);
	}
	{
		Matrix3x3 const m
		{
			{11, 12, 13},
			{21, 22, 23},
			{31, 32, 33},
		};

		VERIFY(Vector3(11, 12, 13) == bksge::get<0>(m));
		VERIFY(Vector3(21, 22, 23) == bksge::get<1>(m));
		VERIFY(Vector3(31, 32, 33) == bksge::get<2>(m));
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	auto m = Matrix3x3::Zero();
	static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");
	VERIFY(Vector3(0, 0, 0) == m[0]);
	VERIFY(Vector3(0, 0, 0) == m[1]);
	VERIFY(Vector3(0, 0, 0) == m[2]);

	return true;
}

TYPED_TEST(MathMatrix3x3Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IdentityTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	auto m = Matrix3x3::Identity();
	static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");
	VERIFY(Vector3(1, 0, 0) == m[0]);
	VERIFY(Vector3(0, 1, 0) == m[1]);
	VERIFY(Vector3(0, 0, 1) == m[2]);

	return true;
}

TYPED_TEST(MathMatrix3x3Test, IdentityTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IdentityTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TransposedTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix3x3 const m1
	{
		{ 11, 12, 13 },
		{ 21, 22, 23 },
		{ 31, 32, 33 },
	};

	auto m2 = Transposed(m1);
	static_assert(bksge::is_same<decltype(m2), Matrix3x3>::value, "");
	VERIFY(Vector3(11, 21, 31) == m2[0]);
	VERIFY(Vector3(12, 22, 32) == m2[1]);
	VERIFY(Vector3(13, 23, 33) == m2[2]);

	auto m3 = Transposed(m2);
	static_assert(bksge::is_same<decltype(m3), Matrix3x3>::value, "");
	VERIFY(Vector3(11, 12, 13) == m3[0]);
	VERIFY(Vector3(21, 22, 23) == m3[1]);
	VERIFY(Vector3(31, 32, 33) == m3[2]);

	VERIFY(m1 == m3);

	return true;
}

TYPED_TEST(MathMatrix3x3Test, TransposedTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TransposedTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool InversedTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix3x3 const m
	{
		{ 3, 2, 1 },
		{ 1, 3, 1 },
		{ 2, 2, 1 },
	};

	auto m_inv = Inversed(m);
	static_assert(bksge::is_same<decltype(m_inv), Matrix3x3>::value, "");

	VERIFY(Vector3( 1,  0, -1) == m_inv[0]);
	VERIFY(Vector3( 1,  1, -2) == m_inv[1]);
	VERIFY(Vector3(-4, -2,  7) == m_inv[2]);

	// 逆行列の逆行列はもとの行列にもどる
	auto m_inv_inv = Inversed(m_inv);
	static_assert(bksge::is_same<decltype(m_inv_inv), Matrix3x3>::value, "");
	VERIFY(m == m_inv_inv);

	// 行列とその逆行列をかけると単位行列になる
	auto m2 = m * m_inv;
	VERIFY(Matrix3x3::Identity() == m2);

	auto m3 = m_inv * m;
	VERIFY(Matrix3x3::Identity() == m3);

	return true;
}

TYPED_TEST(MathMatrix3x3Test, InversedTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InversedTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DeterminantTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	Matrix3x3 const m1
	{
		{ 1, 0, 2 },
		{ 3, 0, 1 },
		{ 2, 1, 1 },
	};

	Matrix3x3 const m2
	{
		{ 1, 2, 1 },
		{ 2, 1, 0 },
		{ 1, 1, 2 },
	};

	Matrix3x3 const m3
	{
		{  9, -3,  2 },
		{  0,  8, -1 },
		{ -2, -3,  5 },
	};

	VERIFY(T(  5) == Determinant(m1));
	VERIFY(T( -5) == Determinant(m2));
	VERIFY(T(359) == Determinant(m3));

	return true;
}

TYPED_TEST(MathMatrix3x3Test, DeterminantTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DeterminantTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeTranslationTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	{
		auto m = Matrix3x3::MakeTranslation(1, 2);
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{  1,  0,  0 },
			{  0,  1,  0 },
			{  1,  2,  1 },
		};

		VERIFY(expected == m);
	}
	{
		auto m = Matrix3x3::MakeTranslation({3, 4});
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{  1,  0,  0 },
			{  0,  1,  0 },
			{  3,  4,  1 },
		};

		VERIFY(expected == m);
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, MakeTranslationTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MakeTranslationTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeScaleTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	{
		auto m = Matrix3x3::MakeScale({2, 3, 4});
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{ 2,  0,  0 },
			{ 0,  3,  0 },
			{ 0,  0,  4 },
		};

		VERIFY(expected == m);
	}
	{
		auto m = Matrix3x3::MakeScale(5, -4, 3);
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{ 5,  0,  0 },
			{ 0, -4,  0 },
			{ 0,  0,  3 },
		};

		VERIFY(expected == m);
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, MakeScaleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MakeScaleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationXTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	{
		auto m = Matrix3x3::MakeRotationX(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");
		VERIFY(Matrix3x3::Identity() == m);
	}
	{
		auto m = Matrix3x3::MakeRotationX(bksge::degrees_to_radians(30));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{ T(1), T( 0),                   T( 0)                   },
			{ T(0), T( 0.86602538824081421), T( 0.5)                 },
			{ T(0), T(-0.5),                 T( 0.86602538824081421) },
		};
		double error = 0.0000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		auto m = Matrix3x3::MakeRotationX(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{ 1,  0, 0 },
			{ 0,  0, 1 },
			{ 0, -1, 0 },
		};
		double error = 0.0000000000000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, MakeRotationXTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationXTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationYTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	{
		auto m = Matrix3x3::MakeRotationY(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");
		VERIFY(Matrix3x3::Identity() == m);
	}
	{
		auto m = Matrix3x3::MakeRotationY(bksge::degrees_to_radians(45));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{ T(0.70710676908493042), T(0), T(-0.70710676908493042) },
			{ T(0),                   T(1), T( 0)                   },
			{ T(0.70710676908493042), T(0), T( 0.70710676908493042) },
		};
		double error = 0.0000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		auto m = Matrix3x3::MakeRotationY(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{ 0,  0, -1 },
			{ 0,  1,  0 },
			{ 1,  0,  0 },
		};
		double error = 0.0000000000000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, MakeRotationYTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationYTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationZTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	{
		auto m = Matrix3x3::MakeRotationZ(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");
		VERIFY(Matrix3x3::Identity() == m);
	}
	{
		auto m = Matrix3x3::MakeRotationZ(bksge::degrees_to_radians(60));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{ T( 0.5),                 T(0.86602538824081421), T(0) },
			{ T(-0.86602538824081421), T(0.5),                 T(0) },
			{ T( 0),                   T(0),                   T(1) },
		};
		double error = 0.0000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		auto m = Matrix3x3::MakeRotationZ(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{ 0,  1,  0 },
			{-1,  0,  0 },
			{ 0,  0,  1 },
		};
		double error = 0.0000000000000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, MakeRotationZTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationZTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	{
		auto m = Matrix3x3::MakeRotation({1, 2, 3}, bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{ T( 0.07142856717109680), T(0.94464081525802612), T(-0.32023677229881287) },
			{ T(-0.65892654657363892), T(0.28571426868438721), T( 0.69583261013031006) },
			{ T( 0.74880814552307129), T(0.16131016612052917), T( 0.64285707473754883) },
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		auto m = Matrix3x3::MakeRotation({-1, 1, 10}, bksge::degrees_to_radians(120));
		static_assert(bksge::is_same<decltype(m), Matrix3x3>::value, "");

		Matrix3x3 const expected
		{
			{ T(-0.48529410362243652), T( 0.84278708696365356), T(-0.23280812799930573) },
			{ T(-0.87219887971878052), T(-0.48529410362243652), T( 0.06130953878164291) },
			{ T(-0.06130953878164291), T( 0.23280812799930573), T( 0.97058844566345215) },
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, MakeRotationTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeShearTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	{
		auto const m = Matrix3x3::MakeShear(-1, 2, -3);
		static_assert(bksge::is_same<decltype(m), Matrix3x3 const>::value, "");

		Matrix3x3 const expected
		{
			{  1,  2, -3 },
			{ -1,  1, -3 },
			{ -1,  2,  1 },
		};

		VERIFY(expected == m);
	}
	{
		auto const m = Matrix3x3::MakeShear(4, 5, 6);
		static_assert(bksge::is_same<decltype(m), Matrix3x3 const>::value, "");

		Matrix3x3 const expected
		{
			{  1,  5,  6 },
			{  4,  1,  6 },
			{  4,  5,  1 },
		};

		VERIFY(expected == m);
	}

	return true;
}

TYPED_TEST(MathMatrix3x3Test, MakeShearTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MakeShearTest<TypeParam>());
}

TYPED_TEST(MathMatrix3x3Test, SerializeTest)
{
	using namespace bksge::serialization;
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;

	Matrix3x3 const v
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool HashTest()
{
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	Matrix3x3 const v1
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
	};
	Matrix3x3 const v2
	{
		{10, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
	};
	Matrix3x3 const v3
	{
		{11, 12, 13},
		{21, 23, 23},
		{31, 32, 33},
	};
	Matrix3x3 const v4
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32,-33},
	};

	std::hash<Matrix3x3> h;

	VERIFY(h(v1) == h(v1));
	VERIFY(h(v1) != h(v2));
	VERIFY(h(v1) != h(v3));
	VERIFY(h(v1) != h(v4));

	VERIFY(h(v2) != h(v1));
	VERIFY(h(v2) == h(v2));
	VERIFY(h(v2) != h(v3));
	VERIFY(h(v2) != h(v4));

	VERIFY(h(v3) != h(v1));
	VERIFY(h(v3) != h(v2));
	VERIFY(h(v3) == h(v3));
	VERIFY(h(v3) != h(v4));

	VERIFY(h(v4) != h(v1));
	VERIFY(h(v4) != h(v2));
	VERIFY(h(v4) != h(v3));
	VERIFY(h(v4) == h(v4));

	return true;
}

TYPED_TEST(MathMatrix3x3Test, HashTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

#undef VERIFY

}	// namespace matrix3x3_test

}	// namespace bksge_math_test
