/**
 *	@file	unit_test_core_math_matrix4x4.cpp
 *
 *	@brief	Matrix4x4 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/matrix4x4.hpp>
#include <bksge/core/math/matrix4x3.hpp>
#include <bksge/core/math/matrix3x4.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/scale3.hpp>
#include <bksge/core/math/quaternion.hpp>
#include <bksge/fnd/cmath/degrees_to_radians.hpp>
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
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/tuple/tie.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"
#include "math_test_utility.hpp"

namespace bksge_math_test
{

namespace matrix4x4_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Matrix4x4f = bksge::math::Matrix4x4<float>;
using Matrix4x4i = bksge::math::Matrix4x4<int>;


using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathMatrix4x4Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathMatrix4x4Test, MathTestTypes);

TYPED_TEST(MathMatrix4x4Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	static_assert(sizeof(Matrix4x4) == sizeof(T) * 4 * 4, "");
	static_assert(bksge::is_default_constructible<Matrix4x4>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Matrix4x4>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Matrix4x4>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3][3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, Vector4ConstructTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(!bksge::is_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_implicitly_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		BKSGE_CONSTEXPR_EXPECT_EQ( 0, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 1, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 2, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 3, v[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 5, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 6, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 7, v[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 8, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 9, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[2][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(14, v[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(15, v[3][3]);
	}

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 v(
			Vector4(11, 12, 13, 14),
			Vector4(21, 22, 23, 24),
			Vector4(31, 32, 33, 34),
			Vector4(41, 42, 43, 44)
		);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(14, v[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(21, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(22, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(23, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(24, v[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(31, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(33, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(34, v[2][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(41, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(43, v[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(44, v[3][3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, Value1ConstructTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	static_assert(!bksge::is_constructible<Matrix4x4, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Matrix4x4, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix4x4, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 v{42};
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[2][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[3][3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, CopyConstructTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	static_assert(bksge::is_constructible<Matrix4x4,  Matrix4x4  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x4,  Matrix4x4i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x4,  Matrix4x4f const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x4i, Matrix4x4  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x4i, Matrix4x4i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x4i, Matrix4x4f const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x4f, Matrix4x4  const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x4f, Matrix4x4i const&>::value, "");
	static_assert(bksge::is_constructible<Matrix4x4f, Matrix4x4f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Matrix4x4,  Matrix4x4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x4,  Matrix4x4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x4,  Matrix4x4f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x4i, Matrix4x4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x4i, Matrix4x4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x4i, Matrix4x4f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x4f, Matrix4x4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x4f, Matrix4x4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Matrix4x4f, Matrix4x4f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Matrix4x4,  Matrix4x4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x4,  Matrix4x4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x4,  Matrix4x4f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x4i, Matrix4x4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x4i, Matrix4x4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x4i, Matrix4x4f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x4f, Matrix4x4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x4f, Matrix4x4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Matrix4x4f, Matrix4x4f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Matrix4x4 v1{
		{ 0,  1,  2,  3},
		{ 4,  5,  6,  7},
		{ 8,  9, 10, 11},
		{12, 13, 14, 15},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4f v4{v2};

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, v2[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, v2[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, v2[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, v2[0][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, v2[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, v2[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, v2[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, v2[1][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, v2[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, v2[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(10, v2[2][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(11, v2[2][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, v2[3][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, v2[3][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(14, v2[3][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(15, v2[3][3]);

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, v3[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, v3[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, v3[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, v3[0][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, v3[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, v3[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, v3[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, v3[1][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, v3[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, v3[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(10, v3[2][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(11, v3[2][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, v3[3][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, v3[3][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(14, v3[3][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(15, v3[3][3]);

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, v4[0][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, v4[0][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, v4[0][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, v4[0][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, v4[1][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, v4[1][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, v4[1][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 7, v4[1][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, v4[2][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, v4[2][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(10, v4[2][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(11, v4[2][3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(12, v4[3][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(13, v4[3][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(14, v4[3][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(15, v4[3][3]);
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix4x4 v{
		{ 0,  1,  2,  3},
		{ 4,  5,  6,  7},
		{ 8,  9, 10, 11},
		{12, 13, 14, 15},
	};
	VERIFY(v[0] == Vector4{ 0,  1,  2,  3});
	VERIFY(v[1] == Vector4{ 4,  5,  6,  7});
	VERIFY(v[2] == Vector4{ 8,  9, 10, 11});
	VERIFY(v[3] == Vector4{12, 13, 14, 15});

	v = Matrix4x4(
		{-2, 3, -4, 5},
		{-2, 3, -4, 5},
		{-2, 3, -4, 5},
		{-2, 3, -4, 5}
	);
	VERIFY(v[0] == Vector4{-2, 3, -4, 5});
	VERIFY(v[1] == Vector4{-2, 3, -4, 5});
	VERIFY(v[2] == Vector4{-2, 3, -4, 5});
	VERIFY(v[3] == Vector4{-2, 3, -4, 5});

	v = Matrix4x4i(
		{ 3, -4,  5, -6},
		{ 7,  8,  9, 10},
		{11, 12, 13, 14},
		{15, 16, 17, 18}
	);
	VERIFY(v[0] == Vector4{ 3, -4,  5, -6});
	VERIFY(v[1] == Vector4{ 7,  8,  9, 10});
	VERIFY(v[2] == Vector4{11, 12, 13, 14});
	VERIFY(v[3] == Vector4{15, 16, 17, 18});

	// 自己代入
	v = v;
	VERIFY(v[0] == Vector4{ 3, -4,  5, -6});
	VERIFY(v[1] == Vector4{ 7,  8,  9, 10});
	VERIFY(v[2] == Vector4{11, 12, 13, 14});
	VERIFY(v[3] == Vector4{15, 16, 17, 18});

	// 多重代入
	Matrix4x4 v2;
	v2 = v = Matrix4x4f(
		{11,12,13,14},
		{21,22,23,24},
		{31,32,33,34},
		{41,42,43,44}
	);
	VERIFY(v[0] == Vector4{11,12,13,14});
	VERIFY(v[1] == Vector4{21,22,23,24});
	VERIFY(v[2] == Vector4{31,32,33,34});
	VERIFY(v[3] == Vector4{41,42,43,44});
	VERIFY(v2[0] == Vector4{11,12,13,14});
	VERIFY(v2[1] == Vector4{21,22,23,24});
	VERIFY(v2[2] == Vector4{31,32,33,34});
	VERIFY(v2[3] == Vector4{41,42,43,44});

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathMatrix4x4Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix4x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		VERIFY(v[0] == Vector4( 0,  1,  2,  3));
		VERIFY(v[1] == Vector4( 4,  5,  6,  7));
		VERIFY(v[2] == Vector4( 8,  9, 10, 11));
		VERIFY(v[3] == Vector4(12, 13, 14, 15));

		v[0] = Vector4(21,22,23,24);
		v[3] = Vector4(31,32,33,34);

		VERIFY(v[0] == Vector4(21, 22, 23, 24));
		VERIFY(v[1] == Vector4( 4,  5,  6,  7));
		VERIFY(v[2] == Vector4( 8,  9, 10, 11));
		VERIFY(v[3] == Vector4(31, 32, 33, 34));
	}
	{
		Matrix4x4 const v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		VERIFY(v[0] == Vector4( 0,  1,  2,  3));
		VERIFY(v[1] == Vector4( 4,  5,  6,  7));
		VERIFY(v[2] == Vector4( 8,  9, 10, 11));
		VERIFY(v[3] == Vector4(12, 13, 14, 15));
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix4x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		VERIFY(v.at(0) == Vector4( 0,  1,  2,  3));
		VERIFY(v.at(1) == Vector4( 4,  5,  6,  7));
		VERIFY(v.at(2) == Vector4( 8,  9, 10, 11));
		VERIFY(v.at(3) == Vector4(12, 13, 14, 15));

		v.at(0) = Vector4(21,22,23,24);
		v.at(3) = Vector4(31,32,33,34);

		VERIFY(v.at(0) == Vector4(21, 22, 23, 24));
		VERIFY(v.at(1) == Vector4( 4,  5,  6,  7));
		VERIFY(v.at(2) == Vector4( 8,  9, 10, 11));
		VERIFY(v.at(3) == Vector4(31, 32, 33, 34));
	}
	{
		Matrix4x4 const v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		VERIFY(v.at(0) == Vector4( 0,  1,  2,  3));
		VERIFY(v.at(1) == Vector4( 4,  5,  6,  7));
		VERIFY(v.at(2) == Vector4( 8,  9, 10, 11));
		VERIFY(v.at(3) == Vector4(12, 13, 14, 15));
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Matrix4x4 = bksge::math::Matrix4x4<TypeParam>;
	{
		Matrix4x4 v;
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
	{
		Matrix4x4 const v;
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix4x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == Vector4( 0,  1,  2,  3));
		*p = Vector4(5);
		++p;
		VERIFY(*p == Vector4( 4,  5,  6,  7));
		p++;
		VERIFY(*p == Vector4( 8,  9, 10, 11));
		*p = Vector4(6);
		++p;
		VERIFY(*p == Vector4(12, 13, 14, 15));

		VERIFY(v == Matrix4x4{
			{ 5,  5,  5,  5},
			{ 4,  5,  6,  7},
			{ 6,  6,  6,  6},
			{12, 13, 14, 15}});
	}
	{
		Matrix4x4 const v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == Vector4( 0,  1,  2,  3));
		++p;
		VERIFY(*p == Vector4( 4,  5,  6,  7));
		p++;
		VERIFY(*p == Vector4( 8,  9, 10, 11));
		++p;
		VERIFY(*p == Vector4(12, 13, 14, 15));
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// begin, end (non const)
	{
		Matrix4x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto it = v.begin();
		VERIFY(it != v.end());
		VERIFY(*it == Vector4{ 0,  1,  2,  3});
		*it++ = Vector4{5};
		VERIFY(it != v.end());
		VERIFY(*it == Vector4{ 4,  5,  6,  7});
		*++it = Vector4{6};
		VERIFY(it != v.end());
		VERIFY(*it == Vector4{ 6,  6,  6,  6});
		it++;
		VERIFY(it != v.end());
		VERIFY(*it == Vector4{12, 13, 14, 15});
		it++;
		VERIFY(it == v.end());

		VERIFY(v == Matrix4x4(
			{ 5,  5,  5,  5},
			{ 4,  5,  6,  7},
			{ 6,  6,  6,  6},
			{12, 13, 14, 15}));
	}
	// begin, end (const)
	{
		Matrix4x4 const v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto it = v.begin();
		VERIFY(it != v.end());

		VERIFY(it[0] == Vector4{ 0,  1,  2,  3});
		VERIFY(it[1] == Vector4{ 4,  5,  6,  7});
		VERIFY(it[2] == Vector4{ 8,  9, 10, 11});
		VERIFY(it[3] == Vector4{12, 13, 14, 15});

		VERIFY(*it++ == Vector4{ 0,  1,  2,  3});
		VERIFY(it != v.end());
		VERIFY(*++it == Vector4{ 8,  9, 10, 11});
		VERIFY(it != v.end());
		VERIFY(*it++ == Vector4{ 8,  9, 10, 11});
		VERIFY(it != v.end());
		VERIFY(*it++ == Vector4{12, 13, 14, 15});
		VERIFY(it == v.end());
	}
	// cbegin, cend
	{
		Matrix4x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto it = v.cbegin();
		VERIFY(it != v.cend());

		VERIFY(it[0] == Vector4{ 0,  1,  2,  3});
		VERIFY(it[1] == Vector4{ 4,  5,  6,  7});
		VERIFY(it[2] == Vector4{ 8,  9, 10, 11});
		VERIFY(it[3] == Vector4{12, 13, 14, 15});

		VERIFY(*it++ == Vector4{ 0,  1,  2,  3});
		VERIFY(it != v.cend());
		VERIFY(*++it == Vector4{ 8,  9, 10, 11});
		VERIFY(it != v.cend());
		VERIFY(*it++ == Vector4{ 8,  9, 10, 11});
		VERIFY(it != v.cend());
		VERIFY(*it++ == Vector4{12, 13, 14, 15});
		VERIFY(it == v.cend());
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// rbegin, rend (non const)
	{
		Matrix4x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto it = v.rbegin();
		VERIFY(it != v.rend());
		VERIFY(*it == Vector4{12, 13, 14, 15});
		*it++ = Vector4{5};
		VERIFY(it != v.rend());
		VERIFY(*it == Vector4{ 8,  9, 10, 11});
		*++it = Vector4{6};
		VERIFY(it != v.rend());
		VERIFY(*it == Vector4{ 6,  6,  6,  6});
		it++;
		VERIFY(it != v.rend());
		VERIFY(*it == Vector4{ 0,  1,  2,  3});
		it++;
		VERIFY(it == v.rend());

		VERIFY(v == Matrix4x4(
			{ 0,  1,  2,  3},
			{ 6,  6,  6,  6},
			{ 8,  9, 10, 11},
			{ 5,  5,  5,  5}));
	}
	// rbegin, rend (const)
	{
		Matrix4x4 const v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto it = v.rbegin();
		VERIFY(it != v.rend());

		VERIFY(it[0] == Vector4{12, 13, 14, 15});
		VERIFY(it[1] == Vector4{ 8,  9, 10, 11});
		VERIFY(it[2] == Vector4{ 4,  5,  6,  7});
		VERIFY(it[3] == Vector4{ 0,  1,  2,  3});

		VERIFY(*it++ == Vector4{12, 13, 14, 15});
		VERIFY(it != v.rend());
		VERIFY(*++it == Vector4{ 4,  5,  6,  7});
		VERIFY(it != v.rend());
		VERIFY(*it++ == Vector4{ 4,  5,  6,  7});
		VERIFY(it != v.rend());
		VERIFY(*it++ == Vector4{ 0,  1,  2,  3});
		VERIFY(it == v.rend());
	}
	// crbegin, crend
	{
		Matrix4x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto it = v.crbegin();
		VERIFY(it != v.crend());

		VERIFY(it[0] == Vector4{12, 13, 14, 15});
		VERIFY(it[1] == Vector4{ 8,  9, 10, 11});
		VERIFY(it[2] == Vector4{ 4,  5,  6,  7});
		VERIFY(it[3] == Vector4{ 0,  1,  2,  3});

		VERIFY(*it++ == Vector4{12, 13, 14, 15});
		VERIFY(it != v.crend());
		VERIFY(*++it == Vector4{ 4,  5,  6,  7});
		VERIFY(it != v.crend());
		VERIFY(*it++ == Vector4{ 4,  5,  6,  7});
		VERIFY(it != v.crend());
		VERIFY(*it++ == Vector4{ 0,  1,  2,  3});
		VERIFY(it == v.crend());
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	Matrix4x4 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathMatrix4x4Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	Matrix4x4 v1{};
	VERIFY(v1.size() == 4);
	return true;
}

TYPED_TEST(MathMatrix4x4Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	Matrix4x4 v1{};
	VERIFY(v1.max_size() == 4);
	return true;
}

TYPED_TEST(MathMatrix4x4Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix4x4 v =
		{
			{11,12,13,14},
			{21,22,23,24},
			{31,32,33,34},
			{41,42,43,44},
		};
		VERIFY(v.x() == Vector4{11,12,13,14});
		VERIFY(v.y() == Vector4{21,22,23,24});
		VERIFY(v.z() == Vector4{31,32,33,34});
		VERIFY(v.w() == Vector4{41,42,43,44});

		v.x() = Vector4{0,1,2,3};
		v.w() = Vector4{4,5,6,7};
		v.y().x() = -1;

		VERIFY(v.x() == Vector4{ 0, 1, 2, 3});
		VERIFY(v.y() == Vector4{-1,22,23,24});
		VERIFY(v.z() == Vector4{31,32,33,34});
		VERIFY(v.w() == Vector4{ 4, 5, 6, 7});
		VERIFY(v[0] == Vector4{ 0, 1, 2, 3});
		VERIFY(v[1] == Vector4{-1,22,23,24});
		VERIFY(v[2] == Vector4{31,32,33,34});
		VERIFY(v[3] == Vector4{ 4, 5, 6, 7});
	}
	{
		Matrix4x4 const v =
		{
			{11,12,13,14},
			{21,22,23,24},
			{31,32,33,34},
			{41,42,43,44},
		};
		VERIFY(v.x() == Vector4{11,12,13,14});
		VERIFY(v.y() == Vector4{21,22,23,24});
		VERIFY(v.z() == Vector4{31,32,33,34});
		VERIFY(v.w() == Vector4{41,42,43,44});
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix4x4 const v1 =
		{
			{11,12,13,14},
			{21,22,23,24},
			{31,32,33,34},
			{41,42,43,44},
		};
		auto const v2 = v1.wxzy();
		//static_assert(bksge::is_same<decltype(v2), Matrix4x4 const>::value, "");
		VERIFY(v2.x() == Vector4{41,42,43,44});
		VERIFY(v2.y() == Vector4{11,12,13,14});
		VERIFY(v2.z() == Vector4{31,32,33,34});
		VERIFY(v2.w() == Vector4{21,22,23,24});
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix4x4 v1 =
	{
		{11,12,13,14},
		{21,22,23,24},
		{31,32,33,34},
		{41,42,43,44},
	};

	Matrix4x4 v2 =
	{
		{51,52,53,54},
		{61,62,63,64},
		{71,72,73,74},
		{81,82,83,84},
	};

	v1.swap(v2);

	VERIFY(v1[0] == Vector4{51,52,53,54});
	VERIFY(v1[1] == Vector4{61,62,63,64});
	VERIFY(v1[2] == Vector4{71,72,73,74});
	VERIFY(v1[3] == Vector4{81,82,83,84});
	VERIFY(v2[0] == Vector4{11,12,13,14});
	VERIFY(v2[1] == Vector4{21,22,23,24});
	VERIFY(v2[2] == Vector4{31,32,33,34});
	VERIFY(v2[3] == Vector4{41,42,43,44});

	bksge::ranges::swap(v1, v2);

	VERIFY(v1[0] == Vector4{11,12,13,14});
	VERIFY(v1[1] == Vector4{21,22,23,24});
	VERIFY(v1[2] == Vector4{31,32,33,34});
	VERIFY(v1[3] == Vector4{41,42,43,44});
	VERIFY(v2[0] == Vector4{51,52,53,54});
	VERIFY(v2[1] == Vector4{61,62,63,64});
	VERIFY(v2[2] == Vector4{71,72,73,74});
	VERIFY(v2[3] == Vector4{81,82,83,84});

	return true;
}

TYPED_TEST(MathMatrix4x4Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix4x4 const v1
		{
			{ 0, -1,  2, -3},
			{ 4,  5, -6, -7},
			{-8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto const v2 = +v1;
		auto const v3 = -v1;
		static_assert(bksge::is_same<decltype(v2), Matrix4x4 const>::value, "");
		static_assert(bksge::is_same<decltype(v3), Matrix4x4 const>::value, "");

		VERIFY(v2[0] ==  Vector4{ 0, -1,  2, -3});
		VERIFY(v2[1] ==  Vector4{ 4,  5, -6, -7});
		VERIFY(v2[2] ==  Vector4{-8,  9, 10, 11});
		VERIFY(v2[3] ==  Vector4{12, 13, 14, 15});
		VERIFY(v3[0] == -Vector4{ 0, -1,  2, -3});
		VERIFY(v3[1] == -Vector4{ 4,  5, -6, -7});
		VERIFY(v3[2] == -Vector4{-8,  9, 10, 11});
		VERIFY(v3[3] == -Vector4{12, 13, 14, 15});
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix4x4 += Matrix4x4
	{
		Matrix4x4 v;

		auto t = (v += Matrix4x4(
			{ 0, -1,  2, -3},
			{ 4,  5, -6, -7},
			{-8,  9, 10, 11},
			{12, 13, 14, 15}
		));
		static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
		VERIFY(t[0] == Vector4( 0, -1,  2, -3));
		VERIFY(t[1] == Vector4( 4,  5, -6, -7));
		VERIFY(t[2] == Vector4(-8,  9, 10, 11));
		VERIFY(t[3] == Vector4(12, 13, 14, 15));
		VERIFY(v == t);
	}
	// Matrix4x4 + Matrix4x4 -> Matrix4x4
	{
		Matrix4x4 const m1
		{
			{-21,  22,  23,  30},
			{ 24, -25,  26,  31},
			{ 27,  28, -29,  32},
			{-33,  34,  35, -36},
		};
		Matrix4x4 const m2
		{
			{ 31,  32, -33,  40},
			{ 34, -35,  36, -41},
			{-37,  38,  39,  42},
			{-43,  44, -45,  46},
		};
		auto m3 = m1 + m2;
		static_assert(bksge::is_same<decltype(m3), Matrix4x4>::value, "");
		VERIFY(m3[0] == Vector4( 10,  54, -10,  70));
		VERIFY(m3[1] == Vector4( 58, -60,  62, -10));
		VERIFY(m3[2] == Vector4(-10,  66,  10,  74));
		VERIFY(m3[3] == Vector4(-76,  78, -10,  10));
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix4x4 -= Matrix4x4
	{
		Matrix4x4 v;

		auto t = (v -= Matrix4x4(
			{ 0, -1,  2, -3},
			{ 4,  5, -6, -7},
			{-8,  9, 10, 11},
			{12, 13, 14, 15}
		));
		static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
		VERIFY(t[0] == -Vector4( 0, -1,  2, -3));
		VERIFY(t[1] == -Vector4( 4,  5, -6, -7));
		VERIFY(t[2] == -Vector4(-8,  9, 10, 11));
		VERIFY(t[3] == -Vector4(12, 13, 14, 15));
		VERIFY(v == t);
	}
	// Matrix4x4 - Matrix4x4 -> Matrix4x4
	{
		Matrix4x4 const m1
		{
			{10, 11, 12, 13},
			{20, 21, 22, 23},
			{30, 31, 32, 33},
			{40, 41, 42, 43},
		};
		Matrix4x4 const m2
		{
			{0, 9, 1, 2},
			{8, 4, 7, 9},
			{6, 5, 3, 1},
			{4, 8, 5, 0},
		};
		auto m3 = m1 - m2;
		static_assert(bksge::is_same<decltype(m3), Matrix4x4>::value, "");
		VERIFY(m3[0] == Vector4(10,  2, 11, 11));
		VERIFY(m3[1] == Vector4(12, 17, 15, 14));
		VERIFY(m3[2] == Vector4(24, 26, 29, 32));
		VERIFY(m3[3] == Vector4(36, 33, 37, 43));
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix4x4 *= スカラー
	{
		Matrix4x4 m1
		{
			{ 1,  2,  3,  4},
			{ 5,  6,  7,  8},
			{ 9, 10, 11, 12},
			{13, 14, 15, 16},
		};
		{
			auto t = (m1 *= 2);
			static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
			VERIFY(Vector4( 2,  4,  6,  8) == m1[0]);
			VERIFY(Vector4(10, 12, 14, 16) == m1[1]);
			VERIFY(Vector4(18, 20, 22, 24) == m1[2]);
			VERIFY(Vector4(26, 28, 30, 32) == m1[3]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
			VERIFY(Vector4( 5, 10, 15, 20) == m1[0]);
			VERIFY(Vector4(25, 30, 35, 40) == m1[1]);
			VERIFY(Vector4(45, 50, 55, 60) == m1[2]);
			VERIFY(Vector4(65, 70, 75, 80) == m1[3]);
			VERIFY(t == m1);
		}
	}

	// Matrix4x4 * スカラー -> Matrix4x4
	{
		Matrix4x4 const m1
		{
			{10, 12, 14, 16},
			{20, 22, 24, 26},
			{30, 32, 34, 36},
			{40, 42, 44, 46},
		};
		{
			auto t = m1 * 3;
			static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
			VERIFY(Vector4( 30,  36,  42,  48) == t[0]);
			VERIFY(Vector4( 60,  66,  72,  78) == t[1]);
			VERIFY(Vector4( 90,  96, 102, 108) == t[2]);
			VERIFY(Vector4(120, 126, 132, 138) == t[3]);
		}
		{
			auto t = m1 * 2.5;
			static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
			VERIFY(Vector4( 25,  30,  35,  40) == t[0]);
			VERIFY(Vector4( 50,  55,  60,  65) == t[1]);
			VERIFY(Vector4( 75,  80,  85,  90) == t[2]);
			VERIFY(Vector4(100, 105, 110, 115) == t[3]);
		}
		// スカラー * Matrix4x4 -> Matrix4x4
		{
			auto t = 4 * m1;
			static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
			VERIFY(Vector4( 40,  48,  56,  64) == t[0]);
			VERIFY(Vector4( 80,  88,  96, 104) == t[1]);
			VERIFY(Vector4(120, 128, 136, 144) == t[2]);
			VERIFY(Vector4(160, 168, 176, 184) == t[3]);
		}
		{
			auto t = -1.5 * m1;
			static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
			VERIFY(Vector4(-15, -18, -21, -24) == t[0]);
			VERIFY(Vector4(-30, -33, -36, -39) == t[1]);
			VERIFY(Vector4(-45, -48, -51, -54) == t[2]);
			VERIFY(Vector4(-60, -63, -66, -69) == t[3]);
		}
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulMatrixTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x4 *= Matrix4x4
	{
		Matrix4x4 m
		{
			{  2,  4,  6,  8 },
			{ 10, 12, 14, 16 },
			{ 18, 20, 22, 24 },
			{ 26, 28, 30, 32 },
		};

		Matrix4x4 const m1
		{
			{  11, -12,  13,  14 },
			{  21,  22, -23,  24 },
			{ -31,  32,  33,  34 },
			{  41,  42,  43, -44 },
		};

		auto t = (m *= m1);
		static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
		VERIFY(Vector4( 248,  592,  476, -24) == m[0]);
		VERIFY(Vector4( 584, 1264, 1004, 200) == m[1]);
		VERIFY(Vector4( 920, 1936, 1532, 424) == m[2]);
		VERIFY(Vector4(1256, 2608, 2060, 648) == m[3]);
		VERIFY(t == m);
	}

	// Matrix4x4 * Matrix4x4 -> Matrix4x4
	{
		Matrix4x4 const m1
		{
			{  15,   3,  -7,   4 },
			{  11,   4,  12,  -8 },
			{   2,   6,  13,  10 },
			{   1,  14,   9,   5 },
		};
		Matrix4x4 const m2
		{
			{   1,   2,   3,   4 },
			{   5,   6,   7,   8 },
			{   9,  10, -11, -12 },
			{  13, -14,  15,  16 },
		};

		auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), Matrix4x4>::value, "");
		VERIFY(Vector4(  19,  -78,  203,  232) == t1[0]);
		VERIFY(Vector4(  35,  278, -191, -196) == t1[1]);
		VERIFY(Vector4( 279,   30,   55,   60) == t1[2]);
		VERIFY(Vector4( 217,  106,   77,   88) == t1[3]);

		auto t2 = m2 * m1;
		static_assert(bksge::is_same<decltype(t2), Matrix4x4>::value, "");
		VERIFY(Vector4(  47,   85,   92,   38) == t2[0]);
		VERIFY(Vector4( 163,  193,  200,   82) == t2[1]);
		VERIFY(Vector4( 211, -167, -194, -214) == t2[2]);
		VERIFY(Vector4(  87,  297,   80,  394) == t2[3]);
	}

	// Matrix4x4 * Matrix4x3 -> Matrix4x3
	{
		Matrix4x4 const m1
		{
			{  1,  2,  3,  4 },
			{  5,  6,  7,  8 },
			{  9, 10, 11, 12 },
			{ 13, 14, 15, 16 },
		};
		Matrix4x3 const m2
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

	// Matrix3x4 * Matrix4x4 -> Matrix3x4
	{
		Matrix3x4 const m1
		{
			{ 11, 12, 13, 14 },
			{ 21, 22, 23, 24 },
			{ 31, 32, 33, 34 },
		};
		Matrix4x4 const m2
		{
			{  1,  2,  3,  4 },
			{  5,  6,  7,  8 },
			{  9, 10, 11, 12 },
			{ 13, 14, 15, 16 },
		};

		auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), Matrix3x4>::value, "");
		VERIFY(Vector4( 370, 420, 470, 520) == t1[0]);
		VERIFY(Vector4( 650, 740, 830, 920) == t1[1]);
		VERIFY(Vector4( 930,1060,1190,1320) == t1[2]);
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MulMatrixTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulMatrixTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulVectorTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Vector4 *= Matrix4x4
	{
		Vector4 v { 1, 2, 3, 4 };
		Matrix4x4 const m
		{
			{ 11, 12, 13, 14 },
			{ 21, 22, 23, 24 },
			{ 31, 32, 33, 34 },
			{ 41, 42, 43, 44 },
		};

		auto t = (v *= m);
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(Vector4(310, 320, 330, 340) == v);
		VERIFY(t == v);
	}

	// Vector4 * Matrix4x4 -> Vector4
	{
		Vector4 const v2 { -5, 6, 7, 8 };
		Matrix4x4 const m
		{
			{  1,  -2,   3,   4 },
			{  5,   6,   7,   8 },
			{  9,  10, -11, -12 },
			{ 13, -14,  15,  16 },
		};

		auto t = v2 * m;
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(Vector4(192, 4, 70, 72) == t);
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MulVectorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulVectorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix4x4 /= スカラー
	{
		Matrix4x4 m1
		{
			{10, 12, 14, 16},
			{18, 20, 22, 24},
			{26, 28, 30, 32},
			{34, 36, 38, 40},
		};

		{
			auto t = (m1 /= 2);
			static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
			VERIFY(Vector4( 5,  6,  7,  8) == m1[0]);
			VERIFY(Vector4( 9, 10, 11, 12) == m1[1]);
			VERIFY(Vector4(13, 14, 15, 16) == m1[2]);
			VERIFY(Vector4(17, 18, 19, 20) == m1[3]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 /= 0.5);
			static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
			VERIFY(Vector4(10, 12, 14, 16) == m1[0]);
			VERIFY(Vector4(18, 20, 22, 24) == m1[1]);
			VERIFY(Vector4(26, 28, 30, 32) == m1[2]);
			VERIFY(Vector4(34, 36, 38, 40) == m1[3]);
			VERIFY(t == m1);
		}
	}

	// Matrix4x4 / スカラー
	{
		Matrix4x4 const m1
		{
			Vector4{10, 12, 14, 16},
			Vector4{20, 22, 24, 26},
			Vector4{30, 32, 34, 36},
			Vector4{40, 42, 44, 46},
		};

		{
			auto t = m1 / 2;
			static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
			VERIFY(Vector4( 5,  6,  7,  8) == t[0]);
			VERIFY(Vector4(10, 11, 12, 13) == t[1]);
			VERIFY(Vector4(15, 16, 17, 18) == t[2]);
			VERIFY(Vector4(20, 21, 22, 23) == t[3]);
		}
		{
			auto t = m1 / 0.25;
			static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
			VERIFY(Vector4( 40,  48,  56,  64) == t[0]);
			VERIFY(Vector4( 80,  88,  96, 104) == t[1]);
			VERIFY(Vector4(120, 128, 136, 144) == t[2]);
			VERIFY(Vector4(160, 168, 176, 184) == t[3]);
		}
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	Matrix4x4 const m1
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
		{41, 42, 43, 44},
	};
	Matrix4x4 const m2
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
		{41, 42, 43, 44},
	};
	Matrix4x4 const m3
	{
		{10, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
		{41, 42, 43, 44},
	};
	Matrix4x4 const m4
	{
		{11, 12, 13, 14},
		{21, 23, 23, 24},
		{31, 32, 33, 34},
		{41, 42, 43, 44},
	};
	Matrix4x4 const m5
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32,-33, 34},
		{41, 42, 43, 44},
	};
	Matrix4x4 const m6
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
		{41, 42, 43, 45},
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

TYPED_TEST(MathMatrix4x4Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathMatrix4x4Test, OutputStreamTest)
{
	using Matrix4x4 = bksge::math::Matrix4x4<TypeParam>;

	{
		Matrix4x4 const m
		{
			{11, 12, 13, 14},
			{21, 22, 23, 24},
			{31, 32, 33, 34},
			{41, 42, 43, 44},
		};
		bksge::stringstream ss;
		ss << m;
		EXPECT_EQ("{ { 11, 12, 13, 14 }, { 21, 22, 23, 24 }, { 31, 32, 33, 34 }, { 41, 42, 43, 44 } }", ss.str());
	}
	{
		Matrix4x4 const m
		{
			{51, 52, 53, 54},
			{61, 62, 63, 64},
			{71, 72, 73, 74},
			{81, 82, 83, 84},
		};
		bksge::wstringstream ss;
		ss << m;
		EXPECT_EQ(L"{ { 51, 52, 53, 54 }, { 61, 62, 63, 64 }, { 71, 72, 73, 74 }, { 81, 82, 83, 84 } }", ss.str());
	}
}

TYPED_TEST(MathMatrix4x4Test, TupleElementTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(bksge::is_same<typename bksge::tuple_element<0, Matrix4x4>::type, Vector4>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<1, Matrix4x4>::type, Vector4>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<2, Matrix4x4>::type, Vector4>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<3, Matrix4x4>::type, Vector4>::value, "");
}

TYPED_TEST(MathMatrix4x4Test, TupleSizeTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	static_assert(bksge::tuple_size<Matrix4x4>::value == 4, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using std::get;

	{
		Matrix4x4 m
		{
			{11, 12, 13, 14},
			{21, 22, 23, 24},
			{31, 32, 33, 34},
			{41, 42, 43, 44},
		};

		VERIFY(Vector4(11, 12, 13, 14) == get<0>(m));
		VERIFY(Vector4(21, 22, 23, 24) == get<1>(m));
		VERIFY(Vector4(31, 32, 33, 34) == get<2>(m));
		VERIFY(Vector4(41, 42, 43, 44) == get<3>(m));

		get<0>(m) = Vector4{51, 52, 53, 54};
		get<3>(m) = Vector4{61, 62, 63, 64};

		VERIFY(Vector4(51, 52, 53, 54) == m[0]);
		VERIFY(Vector4(21, 22, 23, 24) == m[1]);
		VERIFY(Vector4(31, 32, 33, 34) == m[2]);
		VERIFY(Vector4(61, 62, 63, 64) == m[3]);
	}
	{
		Matrix4x4 const m
		{
			{11, 12, 13, 14},
			{21, 22, 23, 24},
			{31, 32, 33, 34},
			{41, 42, 43, 44},
		};

		VERIFY(Vector4(11, 12, 13, 14) == get<0>(m));
		VERIFY(Vector4(21, 22, 23, 24) == get<1>(m));
		VERIFY(Vector4(31, 32, 33, 34) == get<2>(m));
		VERIFY(Vector4(41, 42, 43, 44) == get<3>(m));
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	auto m = Matrix4x4::Zero();
	static_assert(bksge::is_same<decltype(m), Matrix4x4>::value, "");
	VERIFY(Vector4(0, 0, 0, 0) == m[0]);
	VERIFY(Vector4(0, 0, 0, 0) == m[1]);
	VERIFY(Vector4(0, 0, 0, 0) == m[2]);
	VERIFY(Vector4(0, 0, 0, 0) == m[3]);

	return true;
}

TYPED_TEST(MathMatrix4x4Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IdentityTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	auto m = Matrix4x4::Identity();
	static_assert(bksge::is_same<decltype(m), Matrix4x4>::value, "");
	VERIFY(Vector4(1, 0, 0, 0) == m[0]);
	VERIFY(Vector4(0, 1, 0, 0) == m[1]);
	VERIFY(Vector4(0, 0, 1, 0) == m[2]);
	VERIFY(Vector4(0, 0, 0, 1) == m[3]);

	return true;
}

TYPED_TEST(MathMatrix4x4Test, IdentityTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IdentityTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TransposedTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix4x4 const m1
	{
		Vector4{ 11, 12, 13, 14 },
		Vector4{ 21, 22, 23, 24 },
		Vector4{ 31, 32, 33, 34 },
		Vector4{ 41, 42, 43, 44 },
	};

	auto m2 = Transposed(m1);
	static_assert(bksge::is_same<decltype(m2), Matrix4x4>::value, "");
	VERIFY(Vector4(11, 21, 31, 41) == m2[0]);
	VERIFY(Vector4(12, 22, 32, 42) == m2[1]);
	VERIFY(Vector4(13, 23, 33, 43) == m2[2]);
	VERIFY(Vector4(14, 24, 34, 44) == m2[3]);

	auto m3 = Transposed(m2);
	static_assert(bksge::is_same<decltype(m3), Matrix4x4>::value, "");
	VERIFY(Vector4(11, 12, 13, 14) == m3[0]);
	VERIFY(Vector4(21, 22, 23, 24) == m3[1]);
	VERIFY(Vector4(31, 32, 33, 34) == m3[2]);
	VERIFY(Vector4(41, 42, 43, 44) == m3[3]);

	VERIFY(m1 == m3);

	return true;
}

TYPED_TEST(MathMatrix4x4Test, TransposedTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TransposedTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool InversedTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix4x4 const m
	{
		{  1,  0,  1,  2 },
		{ -1,  1,  1,  1 },
		{  1, -1,  0,  1 },
		{  1,  1, -1, -2 },
	};

	auto const m_inv = Inversed(m);
	static_assert(bksge::is_same<decltype(m_inv), Matrix4x4 const>::value, "");

	VERIFY(Vector4( 1, -1, -1,  0) == m_inv[0]);
	VERIFY(Vector4(-1,  2,  2,  1) == m_inv[1]);
	VERIFY(Vector4( 4, -5, -7, -2) == m_inv[2]);
	VERIFY(Vector4(-2,  3,  4,  1) == m_inv[3]);

	// 逆行列の逆行列はもとの行列にもどる
	auto const m_inv_inv = Inversed(m_inv);
	static_assert(bksge::is_same<decltype(m_inv_inv), Matrix4x4 const>::value, "");
	VERIFY(m == m_inv_inv);

	// 行列とその逆行列をかけると単位行列になる
	auto m2 = m * m_inv;
	VERIFY(Matrix4x4::Identity() == m2);

	auto m3 = m_inv * m;
	VERIFY(Matrix4x4::Identity() == m3);

	return true;
}

TYPED_TEST(MathMatrix4x4Test, InversedTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InversedTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DeterminantTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	Matrix4x4 const m1
	{
		{  3,  1,  1,  2 },
		{  5,  1,  3,  4 },
		{  2,  0,  1,  0 },
		{  1,  3,  2,  1 },
	};

	Matrix4x4 const m2
	{
		{  1, -2,  3,  2 },
		{ -2,  2,  0,  2 },
		{  2,  4, -1, -2 },
		{  3,  5, -7, -6 },
	};

	Matrix4x4 const m3
	{
		{  2,  0,  0,  0 },
		{  1,  2,  1, -2 },
		{ -3, -1,  1,  2 },
		{  1,  0,  0, -1 },
	};

	VERIFY(T( -22) == Determinant(m1));
	VERIFY(T(-102) == Determinant(m2));
	VERIFY(T(  -6) == Determinant(m3));

	return true;
}

TYPED_TEST(MathMatrix4x4Test, DeterminantTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DeterminantTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeTranslationTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	{
		auto const m = Matrix4x4::MakeTranslation({3, 4, 5});
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ 1,  0,  0,  0 },
			{ 0,  1,  0,  0 },
			{ 0,  0,  1,  0 },
			{ 3,  4,  5,  1 },
		};

		VERIFY(expected == m);
	}
	{
		auto const m = Matrix4x4::MakeTranslation(-4, 5, -6);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ 1,  0,  0,  0 },
			{ 0,  1,  0,  0 },
			{ 0,  0,  1,  0 },
			{-4,  5, -6,  1 },
		};

		VERIFY(expected == m);
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeTranslationTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MakeTranslationTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeScaleTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	{
		auto m = Matrix4x4::MakeScale(1, 2, 3);
		static_assert(bksge::is_same<decltype(m), Matrix4x4>::value, "");

		Matrix4x4 const expected
		{
			{ 1,  0,  0,  0 },
			{ 0,  2,  0,  0 },
			{ 0,  0,  3,  0 },
			{ 0,  0,  0,  1 },
		};

		VERIFY(expected == m);
	}
	{
		auto m = Matrix4x4::MakeScale({ 5, -4, 3 });
		static_assert(bksge::is_same<decltype(m), Matrix4x4>::value, "");

		Matrix4x4 const expected
		{
			{ 5,  0,  0,  0 },
			{ 0, -4,  0,  0 },
			{ 0,  0,  3,  0 },
			{ 0,  0,  0,  1 },
		};

		VERIFY(expected == m);
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeScaleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MakeScaleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationXTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	{
		auto const m = Matrix4x4::MakeRotationX(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		VERIFY(Matrix4x4::Identity() == m);
	}
	{
		auto const m = Matrix4x4::MakeRotationX(bksge::degrees_to_radians(30));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ T(1.0000000), T( 0.0000000), T( 0.0000000), T(0.0000000) },
			{ T(0.0000000), T( 0.8660253), T( 0.5000000), T(0.0000000) },
			{ T(0.0000000), T(-0.5000000), T( 0.8660253), T(0.0000000) },
			{ T(0.0000000), T( 0.0000000), T( 0.0000000), T(1.0000000) },
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		auto const m = Matrix4x4::MakeRotationX(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ 1,  0, 0, 0 },
			{ 0,  0, 1, 0 },
			{ 0, -1, 0, 0 },
			{ 0,  0, 0, 1 },
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeRotationXTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationXTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationYTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	{
		auto const m = Matrix4x4::MakeRotationY(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		VERIFY(Matrix4x4::Identity() == m);
	}
	{
		auto const m = Matrix4x4::MakeRotationY(bksge::degrees_to_radians(45));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ T(0.7071067), T(0.0000000), T(-0.7071067), T(0.0000000) },
			{ T(0.0000000), T(1.0000000), T( 0.0000000), T(0.0000000) },
			{ T(0.7071067), T(0.0000000), T( 0.7071067), T(0.0000000) },
			{ T(0.0000000), T(0.0000000), T( 0.0000000), T(1.0000000) },
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		auto const m = Matrix4x4::MakeRotationY(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ 0,  0, -1,  0 },
			{ 0,  1,  0,  0 },
			{ 1,  0,  0,  0 },
			{ 0,  0,  0,  1 },
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeRotationYTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationYTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationZTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	{
		auto const m = Matrix4x4::MakeRotationZ(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		VERIFY(Matrix4x4::Identity() == m);
	}
	{
		auto const m = Matrix4x4::MakeRotationZ(bksge::degrees_to_radians(60));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ T( 0.5000000), T( 0.8660253), T( 0.0000000), T(0.0000000) },
			{ T(-0.8660253), T( 0.5000000), T( 0.0000000), T(0.0000000) },
			{ T( 0.0000000), T( 0.0000000), T( 1.0000000), T(0.0000000) },
			{ T( 0.0000000), T( 0.0000000), T( 0.0000000), T(1.0000000) },
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		auto const m = Matrix4x4::MakeRotationZ(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{  0,  1,  0,  0 },
			{ -1,  0,  0,  0 },
			{  0,  0,  1,  0 },
			{  0,  0,  0,  1 },
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeRotationZTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationZTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		auto const axis = Vector3(1, 2, 3);
		auto const r = bksge::degrees_to_radians(90);
		auto const m = Matrix4x4::MakeRotation(axis, r);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ T( 0.0714285), T( 0.9446408), T(-0.3202367), T(0.0000000) },
			{ T(-0.6589265), T( 0.2857142), T( 0.6958326), T(0.0000000) },
			{ T( 0.7488081), T( 0.1613101), T( 0.6428570), T(0.0000000) },
			{ T( 0.0000000), T( 0.0000000), T( 0.0000000), T(1.0000000) },
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		auto const axis = Vector3(-1, 1, 10);
		auto const r = bksge::degrees_to_radians(120);
		auto const m = Matrix4x4::MakeRotation(axis, r);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ T(-0.4852941), T( 0.8427870), T(-0.2328081), T(0.0000000) },
			{ T(-0.8721988), T(-0.4852941), T( 0.0613095), T(0.0000000) },
			{ T(-0.0613095), T( 0.2328081), T( 0.9705884), T(0.0000000) },
			{ T( 0.0000000), T( 0.0000000), T( 0.0000000), T(1.0000000) },
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeRotationTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeShearTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	{
		auto const m = Matrix4x4::MakeShear(-1, 2, -3);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{  1,  2, -3,  0 },
			{ -1,  1, -3,  0 },
			{ -1,  2,  1,  0 },
			{  0,  0,  0,  1 },
		};

		VERIFY(expected == m);
	}
	{
		auto const m = Matrix4x4::MakeShear(4, 5, 6);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{  1,  5,  6,  0 },
			{  4,  1,  6,  0 },
			{  4,  5,  1,  0 },
			{  0,  0,  0,  1 },
		};

		VERIFY(expected == m);
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeShearTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MakeShearTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeOrthographicTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	{
		T left   = 0;
		T right  = 400;
		T top    = 300;
		T bottom = 0;
		T nearz  = 1;
		T farz   = 1000;

		auto const m =
			Matrix4x4::MakeOrthographic(left, right, bottom, top, nearz, farz);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{  T(0.005),  0,             0,            0 },
			{  0,         T(0.00666667), 0,            0 },
			{  0,         0,             T( 0.001001), 0 },
			{ -1,        -1,             T(-0.001001), 1 },
		};

		double error = 0.00000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		T left   = -300;
		T right  = 300;
		T top    = 100;
		T bottom = -100;
		T nearz  = 0.1f;
		T farz   = 100;

		auto const m =
			Matrix4x4::MakeOrthographic(left, right, bottom, top, nearz, farz);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{  T(0.00333333), 0,       0,            0 },
			{  0,             T(0.01), 0,            0 },
			{  0,             0,       T( 0.010010), 0 },
			{ -0,            -0,       T(-0.001001), 1 },
		};

		double error = 0.0000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeOrthographicTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MakeOrthographicTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeFrustumTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	{
		T left   = 0;
		T right  = 400;
		T bottom = 0;
		T top    = 300;
		T nearz  = 1;
		T farz   = 1000;

		auto const m =
			Matrix4x4::MakeFrustum(left, right, bottom, top, nearz, farz);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{  T(0.005),  0,                        0,                       0 },
			{  0,         T(0.0066666666666666671), 0,                       0 },
			{ -1,        -1,                        T( 1.0010010004043579),  1 },
			{  0,         0,                        T(-1.0010010004043579),  0 },
		};

		double error = 0.000000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		T left   = -960;
		T right  =  960;
		T bottom = -540;
		T top    =  540;
		T nearz  = 0.001f;
		T farz   = 1000;

		auto const m =
			Matrix4x4::MakeFrustum(left, right, bottom, top, nearz, farz);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		
		Matrix4x4 const expected
		{
			{  T(0.0000010416667161431785), 0,                        0,                       0 },
			{  0,                           T(0.0000018518519398100), 0,                       0 },
			{  0,                           0,                        T( 1.0000009536743164),  1 },
			{  0,                           0,                        T(-0.0010000009788200),  0 },
		};

		double error = 0.0000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeFrustumTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MakeFrustumTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakePerspectiveTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	{
		T fovy = bksge::degrees_to_radians(45.0f);
		T aspect = 4.0f / 3.0f;
		T zn = 1;
		T zf = 10;

		auto const m = Matrix4x4::MakePerspective(fovy, aspect, zn, zf);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ T(1.81066006185294), 0,                   0,                  0 },
			{ 0,                T(2.4142134877530865),  0,                  0 },
			{ 0,                0,                  T( 1.111111164093017),  1 },
			{ 0,                0,                  T(-1.111111164093017),  0 },
		};

		double error = 0.0000001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		T fovy = bksge::degrees_to_radians(60.0f);
		T aspect = 16.0f / 9.0f;
		T zn = 0.5f;
		T zf = 5000;

		auto const m = Matrix4x4::MakePerspective(fovy, aspect, zn, zf);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ T(0.97427853921501106), 0,                   0,               0 },
			{ 0,                   T(1.7320507492870254),  0,               0 },
			{ 0,                   0,                  T( 1.0001000165939), 1 },
			{ 0,                   0,                  T(-0.5000500082969), 0 },
		};

		double error = 0.000001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakePerspectiveTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakePerspectiveTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeViewTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Vector3 const eye(1, 2, 3);
		Vector3 const at(4, 5, 6);
		Vector3 const up(0, 1, 0);
		Vector3 const direction = at - eye;

		auto const m = Matrix4x4::MakeView(eye, direction, up);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{  0.707107f, -0.408248f,  0.57735f, 0 },
			{  0,          0.816497f,  0.57735f, 0 },
			{ -0.707107f, -0.408248f,  0.57735f, 0 },
			{  1.41421f,   0,         -3.4641f,  1 },
		};

		double const error = 0.00001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		Vector3 const eye(12, 7, -1);
		Vector3 const at(-5, 41, 1);
		Vector3 const up(0, 0, 1);
		Vector3 const direction = at - eye;

		auto const m = Matrix4x4::MakeView(eye, direction, up);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ -0.894427f,  0.0234969f, -0.446596f,  0 },
			{ -0.447214f, -0.0469938f,  0.893192f,  0 },
			{ -0,          0.998619f,   0.0525407f, 0 },
			{ 13.8636f,    1.04561f,   -0.840651f,  1 },
		};

		double const error = 0.0001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeViewTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeViewTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeLookAtTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Vector3 const eye(1, 2, 3);
		Vector3 const at(4, 5, 6);
		Vector3 const up(0, 1, 0);

		auto const m = Matrix4x4::MakeLookAt(eye, at, up);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{  0.707107f, -0.408248f,  0.57735f, 0 },
			{  0,          0.816497f,  0.57735f, 0 },
			{ -0.707107f, -0.408248f,  0.57735f, 0 },
			{  1.41421f,   0,         -3.4641f,  1 },
		};

		double const error = 0.00001;
		VERIFY(IsNear(expected, m, error));
	}
	{
		Vector3 const eye(12, 7, -1);
		Vector3 const at(-5, 41, 1);
		Vector3 const up(0, 0, 1);

		auto const m = Matrix4x4::MakeLookAt(eye, at, up);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ -0.894427f,  0.0234969f, -0.446596f,  0 },
			{ -0.447214f, -0.0469938f,  0.893192f,  0 },
			{ -0,          0.998619f,   0.0525407f, 0 },
			{ 13.8636f,    1.04561f,   -0.840651f,  1 },
		};

		double const error = 0.0001;
		VERIFY(IsNear(expected, m, error));
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeLookAtTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeLookAtTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeViewportTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	{
		auto const mat = Matrix4x4::MakeViewport(0, 0, 640, 480);
		static_assert(bksge::is_same<decltype(mat), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ 320,    0, 0, 0 },
			{   0, -240, 0, 0 },
			{   0,    0, 1, 0 },
			{ 320,  240, 0, 1 },
		};
		VERIFY(expected == mat);
	}
	{
		auto const mat = Matrix4x4::MakeViewport(10, 20, 800, 600);
		static_assert(bksge::is_same<decltype(mat), Matrix4x4 const>::value, "");

		Matrix4x4 const expected
		{
			{ 400,    0, 0, 0 },
			{   0, -300, 0, 0 },
			{   0,    0, 1, 0 },
			{ 410,  320, 0, 1 },
		};
		VERIFY(expected == mat);
	}

	return true;
}

TYPED_TEST(MathMatrix4x4Test, MakeViewportTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MakeViewportTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ComposeTest()
{
	using Matrix4x4  = bksge::math::Matrix4x4<T>;
	using Matrix3x3  = bksge::math::Matrix3x3<T>;
	using Vector3    = bksge::math::Vector3<T>;
	using Scale3     = bksge::math::Scale3<T>;
	using Quaternion = bksge::math::Quaternion<T>;

	// MakeScale() * MakeRotation() * MakeTranslation() と同じ値になるかどうかテスト

	double const error = 0.00001;

	{
		Vector3 trans(1, 2, 3);
		Scale3 scale(4, 5, 6);
		Matrix3x3 rotation = Matrix3x3::Identity();
		auto m = Matrix4x4::Compose(trans, scale, rotation);

		Matrix4x4 const expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::Identity() *
			Matrix4x4::MakeTranslation(trans);
		VERIFY(IsNear(expected, m, error));
	}
	{
		Vector3 trans(7, 8, 9);
		Scale3 scale(10, 11, 12);
		Quaternion rotation = Quaternion::Identity();
		auto m = Matrix4x4::Compose(trans, scale, rotation);

		Matrix4x4 const expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::Identity() *
			Matrix4x4::MakeTranslation(trans);
		VERIFY(IsNear(expected, m, error));
	}
	{
		Vector3 trans {10, 20, 30};
		Scale3 scale {2, 3, 4};
		auto angle = bksge::degrees_to_radians(90);
		auto rotation = Quaternion::MakeRotationX(angle);
		auto m = Matrix4x4::Compose(trans, scale, rotation);

		Matrix4x4 const expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::MakeRotationX(angle) *
			Matrix4x4::MakeTranslation(trans);
		VERIFY(IsNear(expected, m, error));
	}
	{
		Vector3 trans(-2, 1.5, 42);
		Scale3 scale(2, -1, 2.5);
		auto angle = bksge::degrees_to_radians(120);
		auto rotation = Matrix3x3::MakeRotationY(angle);
		auto m = Matrix4x4::Compose(trans, scale, rotation);

		Matrix4x4 const expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::MakeRotationY(angle) *
			Matrix4x4::MakeTranslation(trans);
		VERIFY(IsNear(expected, m, error));
	}
	{
		Vector3 trans(10, -7.5, -1);
		Scale3 scale(3, 3.5, 4);
		auto angle = bksge::degrees_to_radians(45);
		auto rotation = Quaternion::MakeRotationZ(angle);
		auto m = Matrix4x4::Compose(trans, scale, rotation);

		Matrix4x4 const expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::MakeRotationZ(angle) *
			Matrix4x4::MakeTranslation(trans);
		VERIFY(IsNear(expected, m, error));
	}
	{
		Vector3 trans(-1, 2, 3);
		Scale3 scale(4, -5, 6);
		Vector3 axis(7, 8, -9);
		auto angle = bksge::degrees_to_radians(30);
		auto rotation = Quaternion::MakeRotation(axis, angle);
		auto m = Matrix4x4::Compose(trans, scale, rotation);

		Matrix4x4 const expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::MakeRotation(axis, angle) *
			Matrix4x4::MakeTranslation(trans);
		VERIFY(IsNear(expected, m, error));
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, ComposeTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(ComposeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DecomposeTest()
{
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Scale3 = bksge::math::Scale3<T>;
	using std::get;

	{
		const Vector3 trans_expected(-42, 0, 10.5);
		const Scale3 scale_expected(4, 2.5, 1);
		const Matrix3x3 rotation_expected = Matrix3x3::MakeRotationX(bksge::degrees_to_radians(180));
		const Matrix4x4 m = Matrix4x4::Compose(trans_expected, scale_expected, rotation_expected);

		auto const t = Matrix4x4::Decompose(m);
		auto const trans    = get<0>(t);
		auto const scale    = get<1>(t);
		auto const rotation = get<2>(t);

		VERIFY(trans_expected    == trans);
		VERIFY(scale_expected    == scale);
		VERIFY(rotation_expected == rotation);
	}
	{
		const Vector3 trans_expected(10, 20, 30);
		const Scale3 scale_expected(2, 3, 4);
		const Matrix3x3 rotation_expected = Matrix3x3::MakeRotationY(bksge::degrees_to_radians(90));
		const Matrix4x4 m =
			Matrix4x4::MakeScale(scale_expected) *
			Matrix4x4::MakeRotationY(bksge::degrees_to_radians(90)) *
			Matrix4x4::MakeTranslation(trans_expected);

		Vector3 trans;
		Scale3 scale;
		Matrix3x3 rotation;
		bksge::tie(trans, scale, rotation) = Matrix4x4::Decompose(m);

		VERIFY(trans_expected    == trans);
		VERIFY(scale_expected    == scale);
		VERIFY(rotation_expected == rotation);
	}
	return true;
}

TYPED_TEST(MathMatrix4x4Test, DecomposeTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(DecomposeTest<TypeParam>());
}

TYPED_TEST(MathMatrix4x4Test, SerializeTest)
{
	using namespace bksge::serialization;
	using Matrix4x4 = bksge::math::Matrix4x4<TypeParam>;

	Matrix4x4 const v
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
		{41, 42, 43, 44},
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
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	Matrix4x4 const v1
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
		{41, 42, 43, 44},
	};
	Matrix4x4 const v2
	{
		{10, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
		{41, 42, 43, 44},
	};
	Matrix4x4 const v3
	{
		{11, 12, 13, 14},
		{21, 23, 23, 24},
		{31, 32, 33, 34},
		{41, 42, 43, 44},
	};
	Matrix4x4 const v4
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32,-33, 34},
		{41, 42, 43, 44},
	};
	Matrix4x4 const v5
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
		{41, 42, 43,  0},
	};

	std::hash<Matrix4x4> h;

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

TYPED_TEST(MathMatrix4x4Test, HashTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

#undef VERIFY

}	// namespace matrix4x4_test

}	// namespace bksge_math_test
