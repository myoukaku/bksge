/**
 *	@file	unit_test_core_math_matrix3x4.cpp
 *
 *	@brief	Matrix3x4 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/matrix3x4.hpp>
#include <bksge/core/math/matrix4x3.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/core/math/matrix4x4.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
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

namespace matrix3x4_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Matrix3x4f = bksge::math::Matrix3x4<float>;
using Matrix3x4i = bksge::math::Matrix3x4<int>;


using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathMatrix3x4Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathMatrix3x4Test, MathTestTypes);

TYPED_TEST(MathMatrix3x4Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

	static_assert(sizeof(Matrix3x4) == sizeof(T) * 3 * 4, "");
	static_assert(bksge::is_default_constructible<Matrix3x4>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Matrix3x4>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Matrix3x4>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 v;
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
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 v{};
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
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 v = {};
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
	}
}

TYPED_TEST(MathMatrix3x4Test, Vector4ConstructTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(!bksge::is_constructible<Matrix3x4, Vector4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_constructible<Matrix3x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, Vector4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix3x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, Vector4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_implicitly_constructible<Matrix3x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, Vector4>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
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
	}

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 v(
			Vector4(11, 12, 13, 14),
			Vector4(21, 22, 23, 24),
			Vector4(31, 32, 33, 34)
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
	}
}

TYPED_TEST(MathMatrix3x4Test, Value1ConstructTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

	static_assert(!bksge::is_constructible<Matrix3x4, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x4, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x4, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Matrix3x4, T, T>::value, "");
	static_assert( bksge::is_constructible<Matrix3x4, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix3x4, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix3x4, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix3x4, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 v{32};
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[0][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[0][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[0][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[0][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[1][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[1][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[1][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[1][3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[2][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[2][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[2][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(32, v[2][3]);
	}
}

TYPED_TEST(MathMatrix3x4Test, CopyConstructTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

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

	BKSGE_CONSTEXPR_OR_CONST Matrix3x4 v1{
		{ 0,  1,  2,  3},
		{ 4,  5,  6,  7},
		{ 8,  9, 10, 11},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x4  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x4i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Matrix3x4f v4{v2};

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
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix3x4 v{
		{ 0,  1,  2,  3},
		{ 4,  5,  6,  7},
		{ 8,  9, 10, 11},
	};
	VERIFY(v[0] == Vector4{ 0,  1,  2,  3});
	VERIFY(v[1] == Vector4{ 4,  5,  6,  7});
	VERIFY(v[2] == Vector4{ 8,  9, 10, 11});

	v = Matrix3x4(
		{-2, 3, -4, 5},
		{-2, 3, -4, 5},
		{-2, 3, -4, 5}
	);
	VERIFY(v[0] == Vector4{-2, 3, -4, 5});
	VERIFY(v[1] == Vector4{-2, 3, -4, 5});
	VERIFY(v[2] == Vector4{-2, 3, -4, 5});

	v = Matrix3x4i(
		{ 3, -4,  5, -6},
		{ 7,  8,  9, 10},
		{11, 12, 13, 14}
	);
	VERIFY(v[0] == Vector4{ 3, -4,  5, -6});
	VERIFY(v[1] == Vector4{ 7,  8,  9, 10});
	VERIFY(v[2] == Vector4{11, 12, 13, 14});

	// 自己代入
	v = v;
	VERIFY(v[0] == Vector4{ 3, -4,  5, -6});
	VERIFY(v[1] == Vector4{ 7,  8,  9, 10});
	VERIFY(v[2] == Vector4{11, 12, 13, 14});

	// 多重代入
	Matrix3x4 v2;
	v2 = v = Matrix3x4f(
		{11,12,13,14},
		{21,22,23,24},
		{31,32,33,34}
	);
	VERIFY(v[0] == Vector4{11,12,13,14});
	VERIFY(v[1] == Vector4{21,22,23,24});
	VERIFY(v[2] == Vector4{31,32,33,34});
	VERIFY(v2[0] == Vector4{11,12,13,14});
	VERIFY(v2[1] == Vector4{21,22,23,24});
	VERIFY(v2[2] == Vector4{31,32,33,34});

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathMatrix3x4Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix3x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
		};
		VERIFY(v[0] == Vector4( 0,  1,  2,  3));
		VERIFY(v[1] == Vector4( 4,  5,  6,  7));
		VERIFY(v[2] == Vector4( 8,  9, 10, 11));

		v[0] = Vector4(21,22,23,24);

		VERIFY(v[0] == Vector4(21, 22, 23, 24));
		VERIFY(v[1] == Vector4( 4,  5,  6,  7));
		VERIFY(v[2] == Vector4( 8,  9, 10, 11));
	}
	{
		Matrix3x4 const v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
		};
		VERIFY(v[0] == Vector4( 0,  1,  2,  3));
		VERIFY(v[1] == Vector4( 4,  5,  6,  7));
		VERIFY(v[2] == Vector4( 8,  9, 10, 11));
	}
	return true;
}

TYPED_TEST(MathMatrix3x4Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix3x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
		};
		VERIFY(v.at(0) == Vector4( 0,  1,  2,  3));
		VERIFY(v.at(1) == Vector4( 4,  5,  6,  7));
		VERIFY(v.at(2) == Vector4( 8,  9, 10, 11));

		v.at(0) = Vector4(21,22,23,24);

		VERIFY(v.at(0) == Vector4(21, 22, 23, 24));
		VERIFY(v.at(1) == Vector4( 4,  5,  6,  7));
		VERIFY(v.at(2) == Vector4( 8,  9, 10, 11));
	}
	{
		Matrix3x4 const v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
		};
		VERIFY(v.at(0) == Vector4( 0,  1,  2,  3));
		VERIFY(v.at(1) == Vector4( 4,  5,  6,  7));
		VERIFY(v.at(2) == Vector4( 8,  9, 10, 11));
	}
	return true;
}

TYPED_TEST(MathMatrix3x4Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Matrix3x4 = bksge::math::Matrix3x4<TypeParam>;
	{
		Matrix3x4 v;
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
	{
		Matrix3x4 const v;
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix3x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
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

		VERIFY(v == Matrix3x4{
			{ 5,  5,  5,  5},
			{ 4,  5,  6,  7},
			{ 6,  6,  6,  6}});
	}
	{
		Matrix3x4 const v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
		};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == Vector4( 0,  1,  2,  3));
		++p;
		VERIFY(*p == Vector4( 4,  5,  6,  7));
		p++;
		VERIFY(*p == Vector4( 8,  9, 10, 11));
	}
	return true;
}

TYPED_TEST(MathMatrix3x4Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// begin, end (non const)
	{
		Matrix3x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
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
		VERIFY(it == v.end());

		VERIFY(v == Matrix3x4(
			{ 5,  5,  5,  5},
			{ 4,  5,  6,  7},
			{ 6,  6,  6,  6}));
	}
	// begin, end (const)
	{
		Matrix3x4 const v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
		};
		auto it = v.begin();
		VERIFY(it != v.end());

		VERIFY(it[0] == Vector4{ 0,  1,  2,  3});
		VERIFY(it[1] == Vector4{ 4,  5,  6,  7});
		VERIFY(it[2] == Vector4{ 8,  9, 10, 11});

		VERIFY(*it++ == Vector4{ 0,  1,  2,  3});
		VERIFY(it != v.end());
		VERIFY(*++it == Vector4{ 8,  9, 10, 11});
		VERIFY(it != v.end());
		VERIFY(*it++ == Vector4{ 8,  9, 10, 11});
		VERIFY(it == v.end());
	}
	// cbegin, cend
	{
		Matrix3x4 v{
			{ 0,  1,  2,  3},
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
		};
		auto it = v.cbegin();
		VERIFY(it != v.cend());

		VERIFY(it[0] == Vector4{ 0,  1,  2,  3});
		VERIFY(it[1] == Vector4{ 4,  5,  6,  7});
		VERIFY(it[2] == Vector4{ 8,  9, 10, 11});

		VERIFY(*it++ == Vector4{ 0,  1,  2,  3});
		VERIFY(it != v.cend());
		VERIFY(*++it == Vector4{ 8,  9, 10, 11});
		VERIFY(it != v.cend());
		VERIFY(*it++ == Vector4{ 8,  9, 10, 11});
		VERIFY(it == v.cend());
	}
	return true;
}

TYPED_TEST(MathMatrix3x4Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// rbegin, rend (non const)
	{
		Matrix3x4 v{
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
		VERIFY(it == v.rend());

		VERIFY(v == Matrix3x4(
			{ 6,  6,  6,  6},
			{ 8,  9, 10, 11},
			{ 5,  5,  5,  5}));
	}
	// rbegin, rend (const)
	{
		Matrix3x4 const v{
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto it = v.rbegin();
		VERIFY(it != v.rend());

		VERIFY(it[0] == Vector4{12, 13, 14, 15});
		VERIFY(it[1] == Vector4{ 8,  9, 10, 11});
		VERIFY(it[2] == Vector4{ 4,  5,  6,  7});

		VERIFY(*it++ == Vector4{12, 13, 14, 15});
		VERIFY(it != v.rend());
		VERIFY(*++it == Vector4{ 4,  5,  6,  7});
		VERIFY(it != v.rend());
		VERIFY(*it++ == Vector4{ 4,  5,  6,  7});
		VERIFY(it == v.rend());
	}
	// crbegin, crend
	{
		Matrix3x4 v{
			{ 4,  5,  6,  7},
			{ 8,  9, 10, 11},
			{12, 13, 14, 15},
		};
		auto it = v.crbegin();
		VERIFY(it != v.crend());

		VERIFY(it[0] == Vector4{12, 13, 14, 15});
		VERIFY(it[1] == Vector4{ 8,  9, 10, 11});
		VERIFY(it[2] == Vector4{ 4,  5,  6,  7});

		VERIFY(*it++ == Vector4{12, 13, 14, 15});
		VERIFY(it != v.crend());
		VERIFY(*++it == Vector4{ 4,  5,  6,  7});
		VERIFY(it != v.crend());
		VERIFY(*it++ == Vector4{ 4,  5,  6,  7});
		VERIFY(it == v.crend());
	}
	return true;
}

TYPED_TEST(MathMatrix3x4Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	Matrix3x4 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathMatrix3x4Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	Matrix3x4 v1{};
	VERIFY(v1.size() == 3);
	return true;
}

TYPED_TEST(MathMatrix3x4Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	Matrix3x4 v1{};
	VERIFY(v1.max_size() == 3);
	return true;
}

TYPED_TEST(MathMatrix3x4Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix3x4 v =
		{
			{11,12,13,14},
			{21,22,23,24},
			{31,32,33,34},
		};
		VERIFY(v.x() == Vector4{11,12,13,14});
		VERIFY(v.y() == Vector4{21,22,23,24});
		VERIFY(v.z() == Vector4{31,32,33,34});

		v.x() = Vector4{0,1,2,3};
		v.y().x() = -1;

		VERIFY(v.x() == Vector4{ 0, 1, 2, 3});
		VERIFY(v.y() == Vector4{-1,22,23,24});
		VERIFY(v.z() == Vector4{31,32,33,34});
		VERIFY(v[0] == Vector4{ 0, 1, 2, 3});
		VERIFY(v[1] == Vector4{-1,22,23,24});
		VERIFY(v[2] == Vector4{31,32,33,34});
	}
	{
		Matrix3x4 const v =
		{
			{11,12,13,14},
			{21,22,23,24},
			{31,32,33,34},
		};
		VERIFY(v.x() == Vector4{11,12,13,14});
		VERIFY(v.y() == Vector4{21,22,23,24});
		VERIFY(v.z() == Vector4{31,32,33,34});
	}
	return true;
}

TYPED_TEST(MathMatrix3x4Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	//using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix3x4 const m
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
	};

	{
		auto m2 = m.yzx();
		//static_assert(bksge::is_same<decltype(m2), Matrix3x4>::value, "");
		VERIFY(Vector4(21, 22, 23, 24) == m2[0]);
		VERIFY(Vector4(31, 32, 33, 34) == m2[1]);
		VERIFY(Vector4(11, 12, 13, 14) == m2[2]);
	}
	{
		auto m2 = m.xyzx();
		//static_assert(bksge::is_same<decltype(m2), Matrix4x4>::value, "");
		VERIFY(Vector4(11, 12, 13, 14) == m2[0]);
		VERIFY(Vector4(21, 22, 23, 24) == m2[1]);
		VERIFY(Vector4(31, 32, 33, 34) == m2[2]);
		VERIFY(Vector4(11, 12, 13, 14) == m2[3]);
	}
	return true;
}

TYPED_TEST(MathMatrix3x4Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix3x4 v1 =
	{
		{11,12,13,14},
		{21,22,23,24},
		{31,32,33,34},
	};

	Matrix3x4 v2 =
	{
		{51,52,53,54},
		{61,62,63,64},
		{71,72,73,74},
	};

	v1.swap(v2);

	VERIFY(v1[0] == Vector4{51,52,53,54});
	VERIFY(v1[1] == Vector4{61,62,63,64});
	VERIFY(v1[2] == Vector4{71,72,73,74});
	VERIFY(v2[0] == Vector4{11,12,13,14});
	VERIFY(v2[1] == Vector4{21,22,23,24});
	VERIFY(v2[2] == Vector4{31,32,33,34});

	bksge::ranges::swap(v1, v2);

	VERIFY(v1[0] == Vector4{11,12,13,14});
	VERIFY(v1[1] == Vector4{21,22,23,24});
	VERIFY(v1[2] == Vector4{31,32,33,34});
	VERIFY(v2[0] == Vector4{51,52,53,54});
	VERIFY(v2[1] == Vector4{61,62,63,64});
	VERIFY(v2[2] == Vector4{71,72,73,74});

	return true;
}

TYPED_TEST(MathMatrix3x4Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	{
		Matrix3x4 const v1
		{
			{ 0, -1,  2, -3},
			{ 4,  5, -6, -7},
			{-8,  9, 10, 11},
		};
		auto const v2 = +v1;
		auto const v3 = -v1;
		static_assert(bksge::is_same<decltype(v2), Matrix3x4 const>::value, "");
		static_assert(bksge::is_same<decltype(v3), Matrix3x4 const>::value, "");

		VERIFY(v2[0] ==  Vector4{ 0, -1,  2, -3});
		VERIFY(v2[1] ==  Vector4{ 4,  5, -6, -7});
		VERIFY(v2[2] ==  Vector4{-8,  9, 10, 11});
		VERIFY(v3[0] == -Vector4{ 0, -1,  2, -3});
		VERIFY(v3[1] == -Vector4{ 4,  5, -6, -7});
		VERIFY(v3[2] == -Vector4{-8,  9, 10, 11});
	}
	return true;
}

TYPED_TEST(MathMatrix3x4Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix3x4 += Matrix3x4
	{
		Matrix3x4 v;

		auto t = (v += Matrix3x4(
			{ 0, -1,  2, -3},
			{ 4,  5, -6, -7},
			{-8,  9, 10, 11}
		));
		static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
		VERIFY(t[0] == Vector4( 0, -1,  2, -3));
		VERIFY(t[1] == Vector4( 4,  5, -6, -7));
		VERIFY(t[2] == Vector4(-8,  9, 10, 11));
		VERIFY(v == t);
	}
	// Matrix3x4 + Matrix3x4 -> Matrix3x4
	{
		Matrix3x4 const m1
		{
			{-21,  22,  23,  30},
			{ 24, -25,  26,  31},
			{ 27,  28, -29,  32},
		};
		Matrix3x4 const m2
		{
			{ 31,  32, -33,  40},
			{ 34, -35,  36, -41},
			{-37,  38,  39,  42},
		};
		auto m3 = m1 + m2;
		static_assert(bksge::is_same<decltype(m3), Matrix3x4>::value, "");
		VERIFY(m3[0] == Vector4( 10,  54, -10,  70));
		VERIFY(m3[1] == Vector4( 58, -60,  62, -10));
		VERIFY(m3[2] == Vector4(-10,  66,  10,  74));
	}
	return true;
}

TYPED_TEST(MathMatrix3x4Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix3x4 -= Matrix3x4
	{
		Matrix3x4 v;

		auto t = (v -= Matrix3x4(
			{ 0, -1,  2, -3},
			{ 4,  5, -6, -7},
			{-8,  9, 10, 11}
		));
		static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
		VERIFY(t[0] == -Vector4( 0, -1,  2, -3));
		VERIFY(t[1] == -Vector4( 4,  5, -6, -7));
		VERIFY(t[2] == -Vector4(-8,  9, 10, 11));
		VERIFY(v == t);
	}
	// Matrix3x4 - Matrix3x4 -> Matrix3x4
	{
		Matrix3x4 const m1
		{
			{10, 11, 12, 13},
			{20, 21, 22, 23},
			{30, 31, 32, 33},
		};
		Matrix3x4 const m2
		{
			{0, 9, 1, 2},
			{8, 4, 7, 9},
			{6, 5, 3, 1},
		};
		auto m3 = m1 - m2;
		static_assert(bksge::is_same<decltype(m3), Matrix3x4>::value, "");
		VERIFY(m3[0] == Vector4(10,  2, 11, 11));
		VERIFY(m3[1] == Vector4(12, 17, 15, 14));
		VERIFY(m3[2] == Vector4(24, 26, 29, 32));
	}
	return true;
}

TYPED_TEST(MathMatrix3x4Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix3x4 *= スカラー
	{
		Matrix3x4 m1
		{
			{ 1,  2,  3,  4},
			{ 5,  6,  7,  8},
			{ 9, 10, 11, 12},
		};
		{
			auto t = (m1 *= 2);
			static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
			VERIFY(Vector4( 2,  4,  6,  8) == m1[0]);
			VERIFY(Vector4(10, 12, 14, 16) == m1[1]);
			VERIFY(Vector4(18, 20, 22, 24) == m1[2]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 *= 2.5);
			static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
			VERIFY(Vector4( 5, 10, 15, 20) == m1[0]);
			VERIFY(Vector4(25, 30, 35, 40) == m1[1]);
			VERIFY(Vector4(45, 50, 55, 60) == m1[2]);
			VERIFY(t == m1);
		}
	}

	// Matrix3x4 * スカラー -> Matrix3x4
	{
		Matrix3x4 const m1
		{
			{10, 12, 14, 16},
			{20, 22, 24, 26},
			{30, 32, 34, 36},
		};
		{
			auto t = m1 * 3;
			static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
			VERIFY(Vector4( 30,  36,  42,  48) == t[0]);
			VERIFY(Vector4( 60,  66,  72,  78) == t[1]);
			VERIFY(Vector4( 90,  96, 102, 108) == t[2]);
		}
		{
			auto t = m1 * 2.5;
			static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
			VERIFY(Vector4( 25,  30,  35,  40) == t[0]);
			VERIFY(Vector4( 50,  55,  60,  65) == t[1]);
			VERIFY(Vector4( 75,  80,  85,  90) == t[2]);
		}
		// スカラー * Matrix3x4 -> Matrix3x4
		{
			auto t = 4 * m1;
			static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
			VERIFY(Vector4( 40,  48,  56,  64) == t[0]);
			VERIFY(Vector4( 80,  88,  96, 104) == t[1]);
			VERIFY(Vector4(120, 128, 136, 144) == t[2]);
		}
		{
			auto t = -1.5 * m1;
			static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
			VERIFY(Vector4(-15, -18, -21, -24) == t[0]);
			VERIFY(Vector4(-30, -33, -36, -39) == t[1]);
			VERIFY(Vector4(-45, -48, -51, -54) == t[2]);
		}
	}

	return true;
}

TYPED_TEST(MathMatrix3x4Test, MulScalarTest)
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

	// Matrix3x4 *= Matrix4x4
	{
		Matrix3x4 m
		{
			{  2,  4,  6,  8 },
			{ 10, 12, 14, 16 },
			{ 18, 20, 22, 24 },
		};

		Matrix4x4 m1
		{
			{  11, -12,  13,  14 },
			{  21,  22, -23,  24 },
			{ -31,  32,  33,  34 },
			{  41,  42,  43, -44 },
		};

		auto t = (m *= m1);
		static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
		VERIFY(Vector4(248,  592,  476, -24) == m[0]);
		VERIFY(Vector4(584, 1264, 1004, 200) == m[1]);
		VERIFY(Vector4(920, 1936, 1532, 424) == m[2]);
		VERIFY(t == m);
	}

	// Matrix3x4 * Matrix4x4 -> Matrix3x4
	{
		Matrix3x4 const m1
		{
			{  15,   3,  -7,   4 },
			{  11,   4,  12,  -8 },
			{   2,   6,  13,  10 },
		};
		Matrix4x4 const m2
		{
			{   1,   2,   3,   4 },
			{   5,   6,   7,   8 },
			{   9,  10, -11, -12 },
			{  13, -14,  15,  16 },
		};

		auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), Matrix3x4>::value, "");
		VERIFY(Vector4(  19,  -78,  203,  232) == t1[0]);
		VERIFY(Vector4(  35,  278, -191, -196) == t1[1]);
		VERIFY(Vector4( 279,   30,   55,   60) == t1[2]);
	}

	// Matrix3x4 * Matrix4x3 -> Matrix3x3
	// Matrix4x3 * Matrix3x4 -> Matrix4x4
	{
		Matrix3x4 const m1
		{
			{  1,  2,  3,  4 },
			{  5,  6,  7,  8 },
			{  9, 10, 11, 12 },
		};
		Matrix4x3 const m2
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

TYPED_TEST(MathMatrix3x4Test, MulMatrixTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulMatrixTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulVectorTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Vector3 * Matrix3x4 -> Vector4
	{
		Vector3 v { 1, 2, 3 };
		Matrix3x4 m
		{
			{   1,  -2,   3,   4 },
			{   5,   6,   7,   8 },
			{   9,  10, -11, -12 },
		};

		auto t = v * m;
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(Vector4(38, 40, -16, -16) == t);
	}

	return true;
}

TYPED_TEST(MathMatrix3x4Test, MulVectorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulVectorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix3x4 /= スカラー
	{
		Matrix3x4 m1
		{
			{10, 12, 14, 16},
			{18, 20, 22, 24},
			{26, 28, 30, 32},
		};

		{
			auto t = (m1 /= 2);
			static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
			VERIFY(Vector4( 5,  6,  7,  8) == m1[0]);
			VERIFY(Vector4( 9, 10, 11, 12) == m1[1]);
			VERIFY(Vector4(13, 14, 15, 16) == m1[2]);
			VERIFY(t == m1);
		}
		{
			auto t = (m1 /= 0.5);
			static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
			VERIFY(Vector4(10, 12, 14, 16) == m1[0]);
			VERIFY(Vector4(18, 20, 22, 24) == m1[1]);
			VERIFY(Vector4(26, 28, 30, 32) == m1[2]);
			VERIFY(t == m1);
		}
	}

	// Matrix3x4 / スカラー
	{
		Matrix3x4 const m1
		{
			Vector4{10, 12, 14, 16},
			Vector4{20, 22, 24, 26},
			Vector4{30, 32, 34, 36},
		};

		{
			auto t = m1 / 2;
			static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
			VERIFY(Vector4( 5,  6,  7,  8) == t[0]);
			VERIFY(Vector4(10, 11, 12, 13) == t[1]);
			VERIFY(Vector4(15, 16, 17, 18) == t[2]);
		}
		{
			auto t = m1 / 0.25;
			static_assert(bksge::is_same<decltype(t), Matrix3x4>::value, "");
			VERIFY(Vector4( 40,  48,  56,  64) == t[0]);
			VERIFY(Vector4( 80,  88,  96, 104) == t[1]);
			VERIFY(Vector4(120, 128, 136, 144) == t[2]);
		}
	}

	return true;
}

TYPED_TEST(MathMatrix3x4Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

	Matrix3x4 const m1
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
	};
	Matrix3x4 const m2
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
	};
	Matrix3x4 const m3
	{
		{10, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
	};
	Matrix3x4 const m4
	{
		{11, 12, 13, 14},
		{21, 23, 23, 24},
		{31, 32, 33, 34},
	};
	Matrix3x4 const m5
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32,-33, 34},
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

TYPED_TEST(MathMatrix3x4Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathMatrix3x4Test, OutputStreamTest)
{
	using Matrix3x4 = bksge::math::Matrix3x4<TypeParam>;

	{
		Matrix3x4 const m
		{
			{11, 12, 13, 14},
			{21, 22, 23, 24},
			{31, 32, 33, 34},
		};
		std::stringstream ss;
		ss << m;
		EXPECT_EQ("{ { 11, 12, 13, 14 }, { 21, 22, 23, 24 }, { 31, 32, 33, 34 } }", ss.str());
	}
	{
		Matrix3x4 const m
		{
			{51, 52, 53, 54},
			{61, 62, 63, 64},
			{71, 72, 73, 74},
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

TYPED_TEST(MathMatrix3x4Test, TupleSizeTest)
{
	using T = TypeParam;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

	static_assert(std::tuple_size<Matrix3x4>::value == 3, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix3x4 m
		{
			{11, 12, 13, 14},
			{21, 22, 23, 24},
			{31, 32, 33, 34},
		};

		VERIFY(Vector4(11, 12, 13, 14) == bksge::get<0>(m));
		VERIFY(Vector4(21, 22, 23, 24) == bksge::get<1>(m));
		VERIFY(Vector4(31, 32, 33, 34) == bksge::get<2>(m));

		bksge::get<0>(m) = Vector4{51, 52, 53, 54};

		VERIFY(Vector4(51, 52, 53, 54) == m[0]);
		VERIFY(Vector4(21, 22, 23, 24) == m[1]);
		VERIFY(Vector4(31, 32, 33, 34) == m[2]);
	}
	{
		Matrix3x4 const m
		{
			{11, 12, 13, 14},
			{21, 22, 23, 24},
			{31, 32, 33, 34},
		};

		VERIFY(Vector4(11, 12, 13, 14) == bksge::get<0>(m));
		VERIFY(Vector4(21, 22, 23, 24) == bksge::get<1>(m));
		VERIFY(Vector4(31, 32, 33, 34) == bksge::get<2>(m));
	}

	return true;
}

TYPED_TEST(MathMatrix3x4Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	auto m = Matrix3x4::Zero();
	static_assert(bksge::is_same<decltype(m), Matrix3x4>::value, "");
	VERIFY(Vector4(0, 0, 0, 0) == m[0]);
	VERIFY(Vector4(0, 0, 0, 0) == m[1]);
	VERIFY(Vector4(0, 0, 0, 0) == m[2]);

	return true;
}

TYPED_TEST(MathMatrix3x4Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IdentityTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	auto m = Matrix3x4::Identity();
	static_assert(bksge::is_same<decltype(m), Matrix3x4>::value, "");
	VERIFY(Vector4(1, 0, 0, 0) == m[0]);
	VERIFY(Vector4(0, 1, 0, 0) == m[1]);
	VERIFY(Vector4(0, 0, 1, 0) == m[2]);

	return true;
}

TYPED_TEST(MathMatrix3x4Test, IdentityTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IdentityTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TransposedTest()
{
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	Matrix3x4 const m1
	{
		{ 11, 12, 13, 14 },
		{ 21, 22, 23, 24 },
		{ 31, 32, 33, 34 },
	};

	auto m2 = Transposed(m1);
	static_assert(bksge::is_same<decltype(m2), Matrix4x3>::value, "");
	VERIFY(Vector3(11, 21, 31) == m2[0]);
	VERIFY(Vector3(12, 22, 32) == m2[1]);
	VERIFY(Vector3(13, 23, 33) == m2[2]);
	VERIFY(Vector3(14, 24, 34) == m2[3]);

	auto m3 = Transposed(m2);
	static_assert(bksge::is_same<decltype(m3), Matrix3x4>::value, "");
	VERIFY(Vector4(11, 12, 13, 14) == m3[0]);
	VERIFY(Vector4(21, 22, 23, 24) == m3[1]);
	VERIFY(Vector4(31, 32, 33, 34) == m3[2]);

	VERIFY(m1 == m3);

	return true;
}

TYPED_TEST(MathMatrix3x4Test, TransposedTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TransposedTest<TypeParam>());
}

TYPED_TEST(MathMatrix3x4Test, SerializeTest)
{
	using namespace bksge::serialization;
	using Matrix3x4 = bksge::math::Matrix3x4<TypeParam>;

	Matrix3x4 const v
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
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
	using Matrix3x4 = bksge::math::Matrix3x4<T>;

	Matrix3x4 const v1
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
	};
	Matrix3x4 const v2
	{
		{10, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32, 33, 34},
	};
	Matrix3x4 const v3
	{
		{11, 12, 13, 14},
		{21, 23, 23, 24},
		{31, 32, 33, 34},
	};
	Matrix3x4 const v4
	{
		{11, 12, 13, 14},
		{21, 22, 23, 24},
		{31, 32,-33, 34},
	};

	std::hash<Matrix3x4> h;

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

TYPED_TEST(MathMatrix3x4Test, HashTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

#undef VERIFY

}	// namespace matrix3x4_test

}	// namespace bksge_math_test
