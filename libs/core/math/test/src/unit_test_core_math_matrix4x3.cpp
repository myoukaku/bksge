/**
 *	@file	unit_test_core_math_matrix4x3.cpp
 *
 *	@brief	Matrix4x3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/matrix4x3.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/matrix3x4.hpp>
#include <bksge/core/math/matrix4x4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"
#include "math_test_utility.hpp"

namespace bksge_math_test
{

namespace matrix4x3_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Matrix4x3f = bksge::math::Matrix4x3<float>;
using Matrix4x3i = bksge::math::Matrix4x3<int>;


using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathMatrix4x3Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathMatrix4x3Test, MathTestTypes);

TYPED_TEST(MathMatrix4x3Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

	static_assert(sizeof(Matrix4x3) == sizeof(T) * 4 * 3, "");
	static_assert(bksge::is_default_constructible<Matrix4x3>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Matrix4x3>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Matrix4x3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][2]);
	}
}

TYPED_TEST(MathMatrix4x3Test, Vector3ConstructTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(!bksge::is_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( bksge::is_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert( bksge::is_implicitly_constructible<Matrix4x3, Vector3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, Vector3, Vector3, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, Vector3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
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
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(14, v[3][2]);
	}

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 v(
			Vector3(11, 12, 13),
			Vector3(21, 22, 23),
			Vector3(31, 32, 33),
			Vector3(41, 42, 43)
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
		BKSGE_CONSTEXPR_EXPECT_EQ(41, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(43, v[3][2]);
	}
}

TYPED_TEST(MathMatrix4x3Test, Value1ConstructTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

	static_assert(!bksge::is_constructible<Matrix4x3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x3, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x3, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Matrix4x3, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x3, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x3, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix4x3, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x3, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x3 v{12};
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3][2]);
	}
}

TYPED_TEST(MathMatrix4x3Test, CopyConstructTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

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

	BKSGE_CONSTEXPR_OR_CONST Matrix4x3 v1{
		{ 0,  1,  2},
		{ 4,  5,  6},
		{ 8,  9, 10},
		{12, 13, 14},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x3f v4{v2};

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, v2[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, v2[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, v2[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, v2[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, v2[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, v2[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, v2[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, v2[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(10, v2[2][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, v2[3][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, v2[3][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(14, v2[3][2]);

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, v3[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, v3[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, v3[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, v3[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, v3[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, v3[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, v3[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, v3[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(10, v3[2][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, v3[3][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, v3[3][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(14, v3[3][2]);

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, v4[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, v4[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, v4[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, v4[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, v4[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, v4[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, v4[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, v4[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(10, v4[2][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, v4[3][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, v4[3][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(14, v4[3][2]);
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix4x3 v{
		{ 0,  1,  2},
		{ 4,  5,  6},
		{ 8,  9, 10},
		{12, 13, 14},
	};
	VERIFY(v[0] == Vector3{ 0,  1,  2});
	VERIFY(v[1] == Vector3{ 4,  5,  6});
	VERIFY(v[2] == Vector3{ 8,  9, 10});
	VERIFY(v[3] == Vector3{12, 13, 14});

	v = Matrix4x3(
		{-2, 3, -4},
		{-2, 3, -4},
		{-2, 3, -4},
		{-2, 3, -4}
	);
	VERIFY(v[0] == Vector3{-2, 3, -4});
	VERIFY(v[1] == Vector3{-2, 3, -4});
	VERIFY(v[2] == Vector3{-2, 3, -4});
	VERIFY(v[3] == Vector3{-2, 3, -4});

	v = Matrix4x3i(
		{ 3, -4,  5},
		{ 7,  8,  9},
		{11, 12, 13},
		{15, 16, 17}
	);
	VERIFY(v[0] == Vector3{ 3, -4,  5});
	VERIFY(v[1] == Vector3{ 7,  8,  9});
	VERIFY(v[2] == Vector3{11, 12, 13});
	VERIFY(v[3] == Vector3{15, 16, 17});

	// 自己代入
	v = v;
	VERIFY(v[0] == Vector3{ 3, -4,  5});
	VERIFY(v[1] == Vector3{ 7,  8,  9});
	VERIFY(v[2] == Vector3{11, 12, 13});
	VERIFY(v[3] == Vector3{15, 16, 17});

	// 多重代入
	Matrix4x3 v2;
	v2 = v = Matrix4x3f(
		{11,12,13},
		{21,22,23},
		{31,32,33},
		{41,42,43}
	);
	VERIFY(v[0] == Vector3{11,12,13});
	VERIFY(v[1] == Vector3{21,22,23});
	VERIFY(v[2] == Vector3{31,32,33});
	VERIFY(v[3] == Vector3{41,42,43});
	VERIFY(v2[0] == Vector3{11,12,13});
	VERIFY(v2[1] == Vector3{21,22,23});
	VERIFY(v2[2] == Vector3{31,32,33});
	VERIFY(v2[3] == Vector3{41,42,43});

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathMatrix4x3Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix4x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		VERIFY(v[0] == Vector3( 0,  1,  2));
		VERIFY(v[1] == Vector3( 4,  5,  6));
		VERIFY(v[2] == Vector3( 8,  9, 10));
		VERIFY(v[3] == Vector3(12, 13, 14));

		v[0] = Vector3(21,22,23);
		v[3] = Vector3(31,32,33);

		VERIFY(v[0] == Vector3(21, 22, 23));
		VERIFY(v[1] == Vector3( 4,  5,  6));
		VERIFY(v[2] == Vector3( 8,  9, 10));
		VERIFY(v[3] == Vector3(31, 32, 33));
	}
	{
		Matrix4x3 const v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		VERIFY(v[0] == Vector3( 0,  1,  2));
		VERIFY(v[1] == Vector3( 4,  5,  6));
		VERIFY(v[2] == Vector3( 8,  9, 10));
		VERIFY(v[3] == Vector3(12, 13, 14));
	}
	return true;
}

TYPED_TEST(MathMatrix4x3Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix4x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		VERIFY(v.at(0) == Vector3( 0,  1,  2));
		VERIFY(v.at(1) == Vector3( 4,  5,  6));
		VERIFY(v.at(2) == Vector3( 8,  9, 10));
		VERIFY(v.at(3) == Vector3(12, 13, 14));

		v.at(0) = Vector3(21,22,23);
		v.at(3) = Vector3(31,32,33);

		VERIFY(v.at(0) == Vector3(21, 22, 23));
		VERIFY(v.at(1) == Vector3( 4,  5,  6));
		VERIFY(v.at(2) == Vector3( 8,  9, 10));
		VERIFY(v.at(3) == Vector3(31, 32, 33));
	}
	{
		Matrix4x3 const v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		VERIFY(v.at(0) == Vector3( 0,  1,  2));
		VERIFY(v.at(1) == Vector3( 4,  5,  6));
		VERIFY(v.at(2) == Vector3( 8,  9, 10));
		VERIFY(v.at(3) == Vector3(12, 13, 14));
	}
	return true;
}

TYPED_TEST(MathMatrix4x3Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Matrix4x3 = bksge::math::Matrix4x3<TypeParam>;
	{
		Matrix4x3 v;
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
	{
		Matrix4x3 const v;
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix4x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
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
		++p;
		VERIFY(*p == Vector3(12, 13, 14));

		VERIFY(v == Matrix4x3{
			{ 5,  5,  5},
			{ 4,  5,  6},
			{ 6,  6,  6},
			{12, 13, 14}});
	}
	{
		Matrix4x3 const v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == Vector3( 0,  1,  2));
		++p;
		VERIFY(*p == Vector3( 4,  5,  6));
		p++;
		VERIFY(*p == Vector3( 8,  9, 10));
		++p;
		VERIFY(*p == Vector3(12, 13, 14));
	}
	return true;
}

TYPED_TEST(MathMatrix4x3Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// begin, end (non const)
	{
		Matrix4x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
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
		VERIFY(it != v.end());
		VERIFY(*it == Vector3{12, 13, 14});
		it++;
		VERIFY(it == v.end());

		VERIFY(v == Matrix4x3(
			{ 5,  5,  5},
			{ 4,  5,  6},
			{ 6,  6,  6},
			{12, 13, 14}));
	}
	// begin, end (const)
	{
		Matrix4x3 const v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		auto it = v.begin();
		VERIFY(it != v.end());

		VERIFY(it[0] == Vector3{ 0,  1,  2});
		VERIFY(it[1] == Vector3{ 4,  5,  6});
		VERIFY(it[2] == Vector3{ 8,  9, 10});
		VERIFY(it[3] == Vector3{12, 13, 14});

		VERIFY(*it++ == Vector3{ 0,  1,  2});
		VERIFY(it != v.end());
		VERIFY(*++it == Vector3{ 8,  9, 10});
		VERIFY(it != v.end());
		VERIFY(*it++ == Vector3{ 8,  9, 10});
		VERIFY(it != v.end());
		VERIFY(*it++ == Vector3{12, 13, 14});
		VERIFY(it == v.end());
	}
	// cbegin, cend
	{
		Matrix4x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		auto it = v.cbegin();
		VERIFY(it != v.cend());

		VERIFY(it[0] == Vector3{ 0,  1,  2});
		VERIFY(it[1] == Vector3{ 4,  5,  6});
		VERIFY(it[2] == Vector3{ 8,  9, 10});
		VERIFY(it[3] == Vector3{12, 13, 14});

		VERIFY(*it++ == Vector3{ 0,  1,  2});
		VERIFY(it != v.cend());
		VERIFY(*++it == Vector3{ 8,  9, 10});
		VERIFY(it != v.cend());
		VERIFY(*it++ == Vector3{ 8,  9, 10});
		VERIFY(it != v.cend());
		VERIFY(*it++ == Vector3{12, 13, 14});
		VERIFY(it == v.cend());
	}
	return true;
}

TYPED_TEST(MathMatrix4x3Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// rbegin, rend (non const)
	{
		Matrix4x3 v{
			{ 0,  1,  2},
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
		VERIFY(it != v.rend());
		VERIFY(*it == Vector3{ 0,  1,  2});
		it++;
		VERIFY(it == v.rend());

		VERIFY(v == Matrix4x3(
			{ 0,  1,  2},
			{ 6,  6,  6},
			{ 8,  9, 10},
			{ 5,  5,  5}));
	}
	// rbegin, rend (const)
	{
		Matrix4x3 const v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		auto it = v.rbegin();
		VERIFY(it != v.rend());

		VERIFY(it[0] == Vector3{12, 13, 14});
		VERIFY(it[1] == Vector3{ 8,  9, 10});
		VERIFY(it[2] == Vector3{ 4,  5,  6});
		VERIFY(it[3] == Vector3{ 0,  1,  2});

		VERIFY(*it++ == Vector3{12, 13, 14});
		VERIFY(it != v.rend());
		VERIFY(*++it == Vector3{ 4,  5,  6});
		VERIFY(it != v.rend());
		VERIFY(*it++ == Vector3{ 4,  5,  6});
		VERIFY(it != v.rend());
		VERIFY(*it++ == Vector3{ 0,  1,  2});
		VERIFY(it == v.rend());
	}
	// crbegin, crend
	{
		Matrix4x3 v{
			{ 0,  1,  2},
			{ 4,  5,  6},
			{ 8,  9, 10},
			{12, 13, 14},
		};
		auto it = v.crbegin();
		VERIFY(it != v.crend());

		VERIFY(it[0] == Vector3{12, 13, 14});
		VERIFY(it[1] == Vector3{ 8,  9, 10});
		VERIFY(it[2] == Vector3{ 4,  5,  6});
		VERIFY(it[3] == Vector3{ 0,  1,  2});

		VERIFY(*it++ == Vector3{12, 13, 14});
		VERIFY(it != v.crend());
		VERIFY(*++it == Vector3{ 4,  5,  6});
		VERIFY(it != v.crend());
		VERIFY(*it++ == Vector3{ 4,  5,  6});
		VERIFY(it != v.crend());
		VERIFY(*it++ == Vector3{ 0,  1,  2});
		VERIFY(it == v.crend());
	}
	return true;
}

TYPED_TEST(MathMatrix4x3Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	Matrix4x3 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathMatrix4x3Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	Matrix4x3 v1{};
	VERIFY(v1.size() == 4);
	return true;
}

TYPED_TEST(MathMatrix4x3Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	Matrix4x3 v1{};
	VERIFY(v1.max_size() == 4);
	return true;
}

TYPED_TEST(MathMatrix4x3Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix4x3 v =
		{
			{11,12,13},
			{21,22,23},
			{31,32,33},
			{41,42,43},
		};
		VERIFY(v.x() == Vector3{11,12,13});
		VERIFY(v.y() == Vector3{21,22,23});
		VERIFY(v.z() == Vector3{31,32,33});
		VERIFY(v.w() == Vector3{41,42,43});

		v.x() = Vector3{0,1,2};
		v.w() = Vector3{4,5,6};
		v.y().x() = -1;

		VERIFY(v.x() == Vector3{ 0, 1, 2});
		VERIFY(v.y() == Vector3{-1,22,23});
		VERIFY(v.z() == Vector3{31,32,33});
		VERIFY(v.w() == Vector3{ 4, 5, 6});
		VERIFY(v[0] == Vector3{ 0, 1, 2});
		VERIFY(v[1] == Vector3{-1,22,23});
		VERIFY(v[2] == Vector3{31,32,33});
		VERIFY(v[3] == Vector3{ 4, 5, 6});
	}
	{
		Matrix4x3 const v =
		{
			{11,12,13},
			{21,22,23},
			{31,32,33},
			{41,42,43},
		};
		VERIFY(v.x() == Vector3{11,12,13});
		VERIFY(v.y() == Vector3{21,22,23});
		VERIFY(v.z() == Vector3{31,32,33});
		VERIFY(v.w() == Vector3{41,42,43});
	}
	return true;
}

TYPED_TEST(MathMatrix4x3Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix4x3 const v1 =
		{
			{11,12,13},
			{21,22,23},
			{31,32,33},
			{41,42,43},
		};
		auto const v2 = v1.wxzy();
		//static_assert(bksge::is_same<decltype(v2), Matrix4x3 const>::value, "");
		VERIFY(v2.x() == Vector3{41,42,43});
		VERIFY(v2.y() == Vector3{11,12,13});
		VERIFY(v2.z() == Vector3{31,32,33});
		VERIFY(v2.w() == Vector3{21,22,23});
	}
	return true;
}

TYPED_TEST(MathMatrix4x3Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix4x3 v1 =
	{
		{11,12,13},
		{21,22,23},
		{31,32,33},
		{41,42,43},
	};

	Matrix4x3 v2 =
	{
		{51,52,53},
		{61,62,63},
		{71,72,73},
		{81,82,83},
	};

	v1.swap(v2);

	VERIFY(v1[0] == Vector3{51,52,53});
	VERIFY(v1[1] == Vector3{61,62,63});
	VERIFY(v1[2] == Vector3{71,72,73});
	VERIFY(v1[3] == Vector3{81,82,83});
	VERIFY(v2[0] == Vector3{11,12,13});
	VERIFY(v2[1] == Vector3{21,22,23});
	VERIFY(v2[2] == Vector3{31,32,33});
	VERIFY(v2[3] == Vector3{41,42,43});

	bksge::ranges::swap(v1, v2);

	VERIFY(v1[0] == Vector3{11,12,13});
	VERIFY(v1[1] == Vector3{21,22,23});
	VERIFY(v1[2] == Vector3{31,32,33});
	VERIFY(v1[3] == Vector3{41,42,43});
	VERIFY(v2[0] == Vector3{51,52,53});
	VERIFY(v2[1] == Vector3{61,62,63});
	VERIFY(v2[2] == Vector3{71,72,73});
	VERIFY(v2[3] == Vector3{81,82,83});

	return true;
}

TYPED_TEST(MathMatrix4x3Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	{
		Matrix4x3 const v1
		{
			{ 0, -1,  2},
			{ 4,  5, -6},
			{-8,  9, 10},
			{12, 13, 14},
		};
		auto const v2 = +v1;
		auto const v3 = -v1;
		static_assert(bksge::is_same<decltype(v2), Matrix4x3 const>::value, "");
		static_assert(bksge::is_same<decltype(v3), Matrix4x3 const>::value, "");

		VERIFY(v2[0] ==  Vector3{ 0, -1,  2});
		VERIFY(v2[1] ==  Vector3{ 4,  5, -6});
		VERIFY(v2[2] ==  Vector3{-8,  9, 10});
		VERIFY(v2[3] ==  Vector3{12, 13, 14});
		VERIFY(v3[0] == -Vector3{ 0, -1,  2});
		VERIFY(v3[1] == -Vector3{ 4,  5, -6});
		VERIFY(v3[2] == -Vector3{-8,  9, 10});
		VERIFY(v3[3] == -Vector3{12, 13, 14});
	}
	return true;
}

TYPED_TEST(MathMatrix4x3Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x3 += Matrix4x3
	{
		Matrix4x3 v;

		auto t = (v += Matrix4x3(
			{ 0, -1,  2},
			{ 4,  5, -6},
			{-8,  9, 10},
			{12, 13, 14}
		));
		static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
		VERIFY(t[0] == Vector3( 0, -1,  2));
		VERIFY(t[1] == Vector3( 4,  5, -6));
		VERIFY(t[2] == Vector3(-8,  9, 10));
		VERIFY(t[3] == Vector3(12, 13, 14));
		VERIFY(v == t);
	}
	// Matrix4x3 + Matrix4x3 -> Matrix4x3
	{
		Matrix4x3 const m1
		{
			{-21,  22,  23},
			{ 24, -25,  26},
			{ 27,  28, -29},
			{-33,  34,  35},
		};
		Matrix4x3 const m2
		{
			{ 31,  32, -33},
			{ 34, -35,  36},
			{-37,  38,  39},
			{-43,  44, -45},
		};
		auto m3 = m1 + m2;
		static_assert(bksge::is_same<decltype(m3), Matrix4x3>::value, "");
		VERIFY(m3[0] == Vector3( 10,  54, -10));
		VERIFY(m3[1] == Vector3( 58, -60,  62));
		VERIFY(m3[2] == Vector3(-10,  66,  10));
		VERIFY(m3[3] == Vector3(-76,  78, -10));
	}
	return true;
}

TYPED_TEST(MathMatrix4x3Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x3 -= Matrix4x3
	{
		Matrix4x3 v;

		auto t = (v -= Matrix4x3(
			{ 0, -1,  2},
			{ 4,  5, -6},
			{-8,  9, 10},
			{12, 13, 14}
		));
		static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
		VERIFY(t[0] == -Vector3( 0, -1,  2));
		VERIFY(t[1] == -Vector3( 4,  5, -6));
		VERIFY(t[2] == -Vector3(-8,  9, 10));
		VERIFY(t[3] == -Vector3(12, 13, 14));
		VERIFY(v == t);
	}
	// Matrix4x3 - Matrix4x3 -> Matrix4x3
	{
		Matrix4x3 const m1
		{
			{10, 11, 12},
			{20, 21, 22},
			{30, 31, 32},
			{40, 41, 42},
		};
		Matrix4x3 const m2
		{
			{0, 9, 1},
			{8, 4, 7},
			{6, 5, 3},
			{4, 8, 5},
		};
		auto m3 = m1 - m2;
		static_assert(bksge::is_same<decltype(m3), Matrix4x3>::value, "");
		VERIFY(m3[0] == Vector3(10,  2, 11));
		VERIFY(m3[1] == Vector3(12, 17, 15));
		VERIFY(m3[2] == Vector3(24, 26, 29));
		VERIFY(m3[3] == Vector3(36, 33, 37));
	}
	return true;
}

TYPED_TEST(MathMatrix4x3Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x3 *= スカラー
	{
		Matrix4x3 m1
		{
			{ 1,  2,  3},
			{ 5,  6,  7},
			{ 9, 10, 11},
			{13, 14, 15},
		};
		{
			auto t = (m1 *= 2);
			static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
			VERIFY(Vector3( 2,  4,  6) == m1[0]);
			VERIFY(Vector3(10, 12, 14) == m1[1]);
			VERIFY(Vector3(18, 20, 22) == m1[2]);
			VERIFY(Vector3(26, 28, 30) == m1[3]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
			VERIFY(Vector3( 5, 10, 15) == m1[0]);
			VERIFY(Vector3(25, 30, 35) == m1[1]);
			VERIFY(Vector3(45, 50, 55) == m1[2]);
			VERIFY(Vector3(65, 70, 75) == m1[3]);
			VERIFY(t == m1);
		}
	}

	// Matrix4x3 * スカラー -> Matrix4x3
	{
		Matrix4x3 const m1
		{
			{10, 12, 14},
			{20, 22, 24},
			{30, 32, 34},
			{40, 42, 44},
		};
		{
			auto t = m1 * 3;
			static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
			VERIFY(Vector3( 30,  36,  42) == t[0]);
			VERIFY(Vector3( 60,  66,  72) == t[1]);
			VERIFY(Vector3( 90,  96, 102) == t[2]);
			VERIFY(Vector3(120, 126, 132) == t[3]);
		}
		{
			auto t = m1 * 2.5;
			static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
			VERIFY(Vector3( 25,  30,  35) == t[0]);
			VERIFY(Vector3( 50,  55,  60) == t[1]);
			VERIFY(Vector3( 75,  80,  85) == t[2]);
			VERIFY(Vector3(100, 105, 110) == t[3]);
		}
		// スカラー * Matrix4x3 -> Matrix4x3
		{
			auto t = 4 * m1;
			static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
			VERIFY(Vector3( 40,  48,  56) == t[0]);
			VERIFY(Vector3( 80,  88,  96) == t[1]);
			VERIFY(Vector3(120, 128, 136) == t[2]);
			VERIFY(Vector3(160, 168, 176) == t[3]);
		}
		{
			auto t = -1.5 * m1;
			static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
			VERIFY(Vector3(-15, -18, -21) == t[0]);
			VERIFY(Vector3(-30, -33, -36) == t[1]);
			VERIFY(Vector3(-45, -48, -51) == t[2]);
			VERIFY(Vector3(-60, -63, -66) == t[3]);
		}
	}

	return true;
}

TYPED_TEST(MathMatrix4x3Test, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulMatrixTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x3 *= Matrix3x3
	{
		Matrix4x3 m1
		{
			{  2,  4,  6 },
			{ 10, 12, 14 },
			{ 18, 20, 22 },
			{ 26, 28, 30 },
		};

		Matrix3x3 m2
		{
			{  11, -12,  13 },
			{  21,  22, -23 },
			{ -31,  32,  33 },
		};

		auto t = (m1 *= m2);
		static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
		VERIFY(Vector3( -80,  256, 132) == m1[0]);
		VERIFY(Vector3( -72,  592, 316) == m1[1]);
		VERIFY(Vector3( -64,  928, 500) == m1[2]);
		VERIFY(Vector3( -56, 1264, 684) == m1[3]);
		VERIFY(t == m1);
	}

	// Matrix4x3 * Matrix3x3 -> Matrix4x3
	{
		Matrix4x3 m1
		{
			{  15,   3,  -7 },
			{  11,   4,  12 },
			{   2,   6,  13 },
			{   1,  14,   9 },
		};
		Matrix3x3 m2
		{
			{   1,   2,   3 },
			{   5,   6,   7 },
			{   9,  10, -11 },
		};

		auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), Matrix4x3>::value, "");
		VERIFY(Vector3( -33, -22, 143) == t1[0]);
		VERIFY(Vector3( 139, 166, -71) == t1[1]);
		VERIFY(Vector3( 149, 170, -95) == t1[2]);
		VERIFY(Vector3( 152, 176,   2) == t1[3]);
	}

	// Matrix4x4 * Matrix4x3 -> Matrix4x3
	{
		Matrix4x4 m1
		{
			{  1,  2,  3,  4 },
			{  5,  6,  7,  8 },
			{  9, 10, 11, 12 },
			{ 13, 14, 15, 16 },
		};
		Matrix4x3 m2
		{
			{ 11, 12, 13 },
			{ 21, 22, 23 },
			{ 31, 32, 33 },
			{ 41, 42, 43 },
		};

		auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), Matrix4x3>::value, "");
		VERIFY(Vector3( 310, 320, 330) == t1[0]);
		VERIFY(Vector3( 726, 752, 778) == t1[1]);
		VERIFY(Vector3(1142,1184,1226) == t1[2]);
		VERIFY(Vector3(1558,1616,1674) == t1[3]);
	}

	// Matrix3x4 * Matrix4x3 -> Matrix3x3
	// Matrix4x3 * Matrix3x4 -> Matrix4x4
	{
		Matrix3x4 m1
		{
			{  1,  2,  3,  4 },
			{  5,  6,  7,  8 },
			{  9, 10, 11, 12 },
		};
		Matrix4x3 m2
		{
			{ 11, 12, 13 },
			{ 21, 22, 23 },
			{ 31, 32, 33 },
			{ 41, 42, 43 },
		};

		auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), Matrix3x3>::value, "");
		VERIFY(Vector3( 310, 320, 330) == t1[0]);
		VERIFY(Vector3( 726, 752, 778) == t1[1]);
		VERIFY(Vector3(1142,1184,1226) == t1[2]);

		auto t2 = m2 * m1;
		static_assert(bksge::is_same<decltype(t2), Matrix4x4>::value, "");
		VERIFY(Vector4(188, 224, 260, 296) == t2[0]);
		VERIFY(Vector4(338, 404, 470, 536) == t2[1]);
		VERIFY(Vector4(488, 584, 680, 776) == t2[2]);
		VERIFY(Vector4(638, 764, 890,1016) == t2[3]);
	}

	return true;
}

TYPED_TEST(MathMatrix4x3Test, MulMatrixTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulMatrixTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulVectorTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Vector4 * Matrix4x3 -> Vector3
	{
		Vector4 v { -5, 6, 7, 8 };
		Matrix4x3 m
		{
			{   1,  -2,   3 },
			{   5,   6,   7 },
			{   9,  10, -11 },
			{  13, -14,  15 },
		};

		auto t = v * m;
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(Vector3(192, 4, 70) == t);
	}

	return true;
}

TYPED_TEST(MathMatrix4x3Test, MulVectorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulVectorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x3 /= スカラー
	{
		Matrix4x3 m1
		{
			{10, 12, 14},
			{18, 20, 22},
			{26, 28, 30},
			{34, 36, 38},
		};

		{
			auto t = (m1 /= 2);
			static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
			VERIFY(Vector3( 5,  6,  7) == m1[0]);
			VERIFY(Vector3( 9, 10, 11) == m1[1]);
			VERIFY(Vector3(13, 14, 15) == m1[2]);
			VERIFY(Vector3(17, 18, 19) == m1[3]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 /= 0.5);
			static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
			VERIFY(Vector3(10, 12, 14) == m1[0]);
			VERIFY(Vector3(18, 20, 22) == m1[1]);
			VERIFY(Vector3(26, 28, 30) == m1[2]);
			VERIFY(Vector3(34, 36, 38) == m1[3]);
			VERIFY(t == m1);
		}
	}

	// Matrix4x3 / スカラー
	{
		Matrix4x3 const m1
		{
			Vector3{10, 12, 14},
			Vector3{20, 22, 24},
			Vector3{30, 32, 34},
			Vector3{40, 42, 44},
		};

		{
			auto t = m1 / 2;
			static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
			VERIFY(Vector3( 5,  6,  7) == t[0]);
			VERIFY(Vector3(10, 11, 12) == t[1]);
			VERIFY(Vector3(15, 16, 17) == t[2]);
			VERIFY(Vector3(20, 21, 22) == t[3]);
		}
		{
			auto t = m1 / 0.25;
			static_assert(bksge::is_same<decltype(t), Matrix4x3>::value, "");
			VERIFY(Vector3( 40,  48,  56) == t[0]);
			VERIFY(Vector3( 80,  88,  96) == t[1]);
			VERIFY(Vector3(120, 128, 136) == t[2]);
			VERIFY(Vector3(160, 168, 176) == t[3]);
		}
	}

	return true;
}

TYPED_TEST(MathMatrix4x3Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

	Matrix4x3 const m1
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
		{41, 42, 43},
	};
	Matrix4x3 const m2
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
		{41, 42, 43},
	};
	Matrix4x3 const m3
	{
		{10, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
		{41, 42, 43},
	};
	Matrix4x3 const m4
	{
		{11, 12, 13},
		{21, 23, 23},
		{31, 32, 33},
		{41, 42, 43},
	};
	Matrix4x3 const m5
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32,-33},
		{41, 42, 43},
	};
	Matrix4x3 const m6
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
		{41, 40, 43},
	};

	VERIFY( (m1 == m1));
	VERIFY( (m1 == m2));
	VERIFY(!(m1 == m3));
	VERIFY(!(m1 == m4));
	VERIFY(!(m1 == m5));
	VERIFY(!(m1 == m6));

	VERIFY(!(m1 != m1));
	VERIFY(!(m1 != m2));
	VERIFY( (m1 != m3));
	VERIFY( (m1 != m4));
	VERIFY( (m1 != m5));
	VERIFY( (m1 != m6));

	return true;
}

TYPED_TEST(MathMatrix4x3Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathMatrix4x3Test, OutputStreamTest)
{
	using Matrix4x3 = bksge::math::Matrix4x3<TypeParam>;

	{
		Matrix4x3 const m
		{
			{11, 12, 13},
			{21, 22, 23},
			{31, 32, 33},
			{41, 42, 43},
		};
		bksge::stringstream ss;
		ss << m;
		EXPECT_EQ("{ { 11, 12, 13 }, { 21, 22, 23 }, { 31, 32, 33 }, { 41, 42, 43 } }", ss.str());
	}
	{
		Matrix4x3 const m
		{
			{51, 52, 53},
			{61, 62, 63},
			{71, 72, 73},
			{81, 82, 83},
		};
		bksge::wstringstream ss;
		ss << m;
		EXPECT_EQ(L"{ { 51, 52, 53 }, { 61, 62, 63 }, { 71, 72, 73 }, { 81, 82, 83 } }", ss.str());
	}
}

TYPED_TEST(MathMatrix4x3Test, TupleElementTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(bksge::is_same<typename bksge::tuple_element<0, Matrix4x3>::type, Vector3>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<1, Matrix4x3>::type, Vector3>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<2, Matrix4x3>::type, Vector3>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<3, Matrix4x3>::type, Vector3>::value, "");
}

TYPED_TEST(MathMatrix4x3Test, TupleSizeTest)
{
	using T = TypeParam;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

	static_assert(bksge::tuple_size<Matrix4x3>::value == 4, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using std::get;

	{
		Matrix4x3 m
		{
			{11, 12, 13},
			{21, 22, 23},
			{31, 32, 33},
			{41, 42, 43},
		};

		VERIFY(Vector3(11, 12, 13) == get<0>(m));
		VERIFY(Vector3(21, 22, 23) == get<1>(m));
		VERIFY(Vector3(31, 32, 33) == get<2>(m));
		VERIFY(Vector3(41, 42, 43) == get<3>(m));

		get<0>(m) = Vector3{51, 52, 53};
		get<3>(m) = Vector3{61, 62, 63};

		VERIFY(Vector3(51, 52, 53) == m[0]);
		VERIFY(Vector3(21, 22, 23) == m[1]);
		VERIFY(Vector3(31, 32, 33) == m[2]);
		VERIFY(Vector3(61, 62, 63) == m[3]);
	}
	{
		Matrix4x3 const m
		{
			{11, 12, 13},
			{21, 22, 23},
			{31, 32, 33},
			{41, 42, 43},
		};

		VERIFY(Vector3(11, 12, 13) == get<0>(m));
		VERIFY(Vector3(21, 22, 23) == get<1>(m));
		VERIFY(Vector3(31, 32, 33) == get<2>(m));
		VERIFY(Vector3(41, 42, 43) == get<3>(m));
	}

	return true;
}

TYPED_TEST(MathMatrix4x3Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	auto m = Matrix4x3::Zero();
	static_assert(bksge::is_same<decltype(m), Matrix4x3>::value, "");
	VERIFY(Vector3(0, 0, 0) == m[0]);
	VERIFY(Vector3(0, 0, 0) == m[1]);
	VERIFY(Vector3(0, 0, 0) == m[2]);
	VERIFY(Vector3(0, 0, 0) == m[3]);

	return true;
}

TYPED_TEST(MathMatrix4x3Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IdentityTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector3 = bksge::math::Vector3<T>;

	auto m = Matrix4x3::Identity();
	static_assert(bksge::is_same<decltype(m), Matrix4x3>::value, "");
	VERIFY(Vector3(1, 0, 0) == m[0]);
	VERIFY(Vector3(0, 1, 0) == m[1]);
	VERIFY(Vector3(0, 0, 1) == m[2]);
	VERIFY(Vector3(0, 0, 0) == m[3]);

	return true;
}

TYPED_TEST(MathMatrix4x3Test, IdentityTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IdentityTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TransposedTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix4x3 const m1
	{
		{ 11, 12, 13 },
		{ 21, 22, 23 },
		{ 31, 32, 33 },
		{ 41, 42, 43 },
	};

	auto m2 = Transposed(m1);
	static_assert(bksge::is_same<decltype(m2), Matrix3x4>::value, "");
	VERIFY(Vector4(11, 21, 31, 41) == m2[0]);
	VERIFY(Vector4(12, 22, 32, 42) == m2[1]);
	VERIFY(Vector4(13, 23, 33, 43) == m2[2]);

	auto m3 = Transposed(m2);
	static_assert(bksge::is_same<decltype(m3), Matrix4x3>::value, "");
	VERIFY(Vector3(11, 12, 13) == m3[0]);
	VERIFY(Vector3(21, 22, 23) == m3[1]);
	VERIFY(Vector3(31, 32, 33) == m3[2]);
	VERIFY(Vector3(41, 42, 43) == m3[3]);

	VERIFY(m1 == m3);

	return true;
}

TYPED_TEST(MathMatrix4x3Test, TransposedTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TransposedTest<TypeParam>());
}

TYPED_TEST(MathMatrix4x3Test, SerializeTest)
{
	using namespace bksge::serialization;
	using Matrix4x3 = bksge::math::Matrix4x3<TypeParam>;

	Matrix4x3 const v
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
		{41, 42, 43},
	};

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool HashTest()
{
	using Matrix4x3 = bksge::math::Matrix4x3<T>;

	Matrix4x3 const v1
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
		{41, 42, 43},
	};
	Matrix4x3 const v2
	{
		{10, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
		{41, 42, 43},
	};
	Matrix4x3 const v3
	{
		{11, 12, 13},
		{21, 23, 23},
		{31, 32, 33},
		{41, 42, 43},
	};
	Matrix4x3 const v4
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32,-33},
		{41, 42, 43},
	};
	Matrix4x3 const v5
	{
		{11, 12, 13},
		{21, 22, 23},
		{31, 32, 33},
		{41, 42, 44},
	};

	bksge::hash<Matrix4x3> h;

	VERIFY(h(v1) == h(v1));
	VERIFY(h(v1) != h(v2));
	VERIFY(h(v1) != h(v3));
	VERIFY(h(v1) != h(v4));
	VERIFY(h(v1) != h(v5));

	VERIFY(h(v2) != h(v1));
	VERIFY(h(v2) == h(v2));
	VERIFY(h(v2) != h(v3));
	VERIFY(h(v2) != h(v4));
	VERIFY(h(v2) != h(v5));

	VERIFY(h(v3) != h(v1));
	VERIFY(h(v3) != h(v2));
	VERIFY(h(v3) == h(v3));
	VERIFY(h(v3) != h(v4));
	VERIFY(h(v3) != h(v5));

	VERIFY(h(v4) != h(v1));
	VERIFY(h(v4) != h(v2));
	VERIFY(h(v4) != h(v3));
	VERIFY(h(v4) == h(v4));
	VERIFY(h(v4) != h(v5));

	VERIFY(h(v5) != h(v1));
	VERIFY(h(v5) != h(v2));
	VERIFY(h(v5) != h(v3));
	VERIFY(h(v5) != h(v4));
	VERIFY(h(v5) == h(v5));

	return true;
}

TYPED_TEST(MathMatrix4x3Test, HashTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

#undef VERIFY

}	// namespace matrix4x3_test

}	// namespace bksge_math_test
