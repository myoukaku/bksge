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
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/tuple/tie.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/algorithm/sort.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <functional>
#include <vector>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

//#define BKSGE_DXMATH_TEST

#if defined(BKSGE_DXMATH_TEST)
#include <directxmath.h>
using namespace DirectX;

namespace
{

template <typename T>
XMVECTOR ToXMVECTOR(bksge::math::Vector3<T> const& vec)
{
	return XMVectorSet((float)vec[0], (float)vec[1], (float)vec[2], 0.0f);
}

template <typename T>
XMVECTOR ToXMVECTOR(bksge::math::Vector4<T> const& vec)
{
	return XMVectorSet((float)vec[0], (float)vec[1], (float)vec[2], (float)vec[3]);
}

template <typename T>
XMVECTOR ToXMVECTOR(bksge::math::Scale3<T> const& vec)
{
	return XMVectorSet((float)vec[0], (float)vec[1], (float)vec[2], 0.0f);
}

template <typename T>
bksge::math::Matrix4x4<T> ToMatrix4x4(XMMATRIX const& mat)
{
	return bksge::math::Matrix4x4<T>
	{
		bksge::math::Vector4<T>
		{
			(T)XMVectorGetX(mat.r[0]),
			(T)XMVectorGetY(mat.r[0]),
			(T)XMVectorGetZ(mat.r[0]),
			(T)XMVectorGetW(mat.r[0]),
		},
		bksge::math::Vector4<T>
		{
			(T)XMVectorGetX(mat.r[1]),
			(T)XMVectorGetY(mat.r[1]),
			(T)XMVectorGetZ(mat.r[1]),
			(T)XMVectorGetW(mat.r[1]),
		},
		bksge::math::Vector4<T>
		{
			(T)XMVectorGetX(mat.r[2]),
			(T)XMVectorGetY(mat.r[2]),
			(T)XMVectorGetZ(mat.r[2]),
			(T)XMVectorGetW(mat.r[2]),
		},
		bksge::math::Vector4<T>
		{
			(T)XMVectorGetX(mat.r[3]),
			(T)XMVectorGetY(mat.r[3]),
			(T)XMVectorGetZ(mat.r[3]),
			(T)XMVectorGetW(mat.r[3]),
		},
	};
}

template <typename T>
XMMATRIX ToXMMATRIX(bksge::math::Matrix4x4<T> const& mat)
{
	return XMMATRIX(
		ToXMVECTOR(mat[0]),
		ToXMVECTOR(mat[1]),
		ToXMVECTOR(mat[2]),
		ToXMVECTOR(mat[3]));
}

}	// namespace
#endif // defined(BKSGE_DXMATH_TEST)

namespace bksge_math_test
{

namespace matrix4x4_test
{

using Matrix4x4f = bksge::math::Matrix4x4<float>;
using Matrix4x4i = bksge::math::Matrix4x4<int>;
using Vector4f = bksge::math::Vector4<float>;
using Vector4i = bksge::math::Vector4<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathMatrix4x4Test : public ::testing::Test {};
template <typename T>
class MathMatrix4x4FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathMatrix4x4Test, MathTestTypes);
TYPED_TEST_SUITE(MathMatrix4x4FloatTest, MathFloatTestTypes);

TYPED_TEST(MathMatrix4x4Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	static_assert(sizeof(Matrix4x4) == sizeof(T) * 16, "");
	static_assert(bksge::is_default_constructible<Matrix4x4>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Matrix4x4>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Matrix4x4>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m;
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
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m{};
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
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m = {};
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
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, m[3][3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, VectorConstructTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(!bksge::is_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4i, Vector4i, Vector4i, Vector4i, Vector4i>::value, "");
	static_assert( bksge::is_constructible<Matrix4x4, Vector4i, Vector4i, Vector4i, Vector4i>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4i, Vector4i, Vector4i>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4i, Vector4i>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4i>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4f, Vector4f, Vector4f, Vector4f, Vector4f>::value, "");
	static_assert( bksge::is_constructible<Matrix4x4, Vector4f, Vector4f, Vector4f, Vector4f>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4f, Vector4f, Vector4f>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4f, Vector4f>::value, "");
	static_assert(!bksge::is_constructible<Matrix4x4, Vector4f>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4i, Vector4i, Vector4i, Vector4i, Vector4i>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix4x4, Vector4i, Vector4i, Vector4i, Vector4i>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4i, Vector4i, Vector4i>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4i, Vector4i>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4i>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4f, Vector4f, Vector4f, Vector4f, Vector4f>::value, "");
	static_assert( bksge::is_nothrow_constructible<Matrix4x4, Vector4f, Vector4f, Vector4f, Vector4f>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4f, Vector4f, Vector4f>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4f, Vector4f>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Matrix4x4, Vector4f>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert( bksge::is_implicitly_constructible<Matrix4x4, Vector4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4i, Vector4i, Vector4i, Vector4i, Vector4i>::value, "");
	static_assert( bksge::is_implicitly_constructible<Matrix4x4, Vector4i, Vector4i, Vector4i, Vector4i>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4i, Vector4i, Vector4i>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4i, Vector4i>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4i>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4f, Vector4f, Vector4f, Vector4f, Vector4f>::value, "");
	static_assert( bksge::is_implicitly_constructible<Matrix4x4, Vector4f, Vector4f, Vector4f, Vector4f>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4f, Vector4f, Vector4f>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4f, Vector4f>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Matrix4x4, Vector4f>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v1( 1,  2,  3,  4);
		BKSGE_CONSTEXPR_OR_CONST Vector4 v2( 5,  6,  7,  8);
		BKSGE_CONSTEXPR_OR_CONST Vector4 v3( 9, 10, 11, 12);
		BKSGE_CONSTEXPR_OR_CONST Vector4 v4(13, 14, 15, 16);
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m(v1, v2, v3, v4);
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
		BKSGE_CONSTEXPR_EXPECT_EQ(13, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(14, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(15, m[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(16, m[3][3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m
		{
			Vector4{10, 11, 12, 13},
			Vector4{20, 21, 22, 23},
			Vector4{30, 31, 32, 33},
			Vector4{40, 41, 42, 43},
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
		BKSGE_CONSTEXPR_EXPECT_EQ(40, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(41, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, m[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(43, m[3][3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m =
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
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
		BKSGE_CONSTEXPR_EXPECT_EQ(41, m[3][0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, m[3][1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(43, m[3][2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(44, m[3][3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, CopyConstructTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

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

	BKSGE_CONSTEXPR_OR_CONST Matrix4x4  m1
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
		Vector4{41, 42, 43, 44},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4  m2{m1};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4i m3{m2};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4f m4{m2};

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
	BKSGE_CONSTEXPR_EXPECT_EQ(41, m3[3][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(42, m3[3][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(43, m3[3][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(44, m3[3][3]);

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
	BKSGE_CONSTEXPR_EXPECT_EQ(41, m4[3][0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(42, m4[3][1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(43, m4[3][2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(44, m4[3][3]);
}

TYPED_TEST(MathMatrix4x4Test, CopyAssignTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix4x4  m1
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
		Vector4{41, 42, 43, 44},
	};
	Matrix4x4  m2;

	EXPECT_EQ(Vector4(11, 12, 13, 14), m1[0]);
	EXPECT_EQ(Vector4(21, 22, 23, 24), m1[1]);
	EXPECT_EQ(Vector4(31, 32, 33, 34), m1[2]);
	EXPECT_EQ(Vector4(41, 42, 43, 44), m1[3]);

	EXPECT_EQ(Vector4(0, 0, 0, 0), m2[0]);
	EXPECT_EQ(Vector4(0, 0, 0, 0), m2[1]);
	EXPECT_EQ(Vector4(0, 0, 0, 0), m2[2]);
	EXPECT_EQ(Vector4(0, 0, 0, 0), m2[3]);

	m1 = Matrix4x4
	{
		Vector4{51, 52, 53, 54},
		Vector4{61, 62, 63, 64},
		Vector4{71, 72, 73, 74},
		Vector4{81, 82, 83, 84},
	};

	EXPECT_EQ(Vector4(51, 52, 53, 54), m1[0]);
	EXPECT_EQ(Vector4(61, 62, 63, 64), m1[1]);
	EXPECT_EQ(Vector4(71, 72, 73, 74), m1[2]);
	EXPECT_EQ(Vector4(81, 82, 83, 84), m1[3]);

	m2 = Matrix4x4i
	{
		Vector4{ 1,  2,  3,  4},
		Vector4{ 5,  6,  7,  8},
		Vector4{ 9, 10, 11, 12},
		Vector4{13, 14, 15, 16},
	};

	EXPECT_EQ(Vector4( 1,  2,  3,  4), m2[0]);
	EXPECT_EQ(Vector4( 5,  6,  7,  8), m2[1]);
	EXPECT_EQ(Vector4( 9, 10, 11, 12), m2[2]);
	EXPECT_EQ(Vector4(13, 14, 15, 16), m2[3]);

	m1 = m2 = Matrix4x4f
	{
		Vector4{10, 11, 12, 13},
		Vector4{20, 21, 22, 23},
		Vector4{30, 31, 32, 33},
		Vector4{40, 41, 42, 43},
	};

	EXPECT_EQ(Vector4(10, 11, 12, 13), m1[0]);
	EXPECT_EQ(Vector4(20, 21, 22, 23), m1[1]);
	EXPECT_EQ(Vector4(30, 31, 32, 33), m1[2]);
	EXPECT_EQ(Vector4(40, 41, 42, 43), m1[3]);

	EXPECT_EQ(Vector4(10, 11, 12, 13), m2[0]);
	EXPECT_EQ(Vector4(20, 21, 22, 23), m2[1]);
	EXPECT_EQ(Vector4(30, 31, 32, 33), m2[2]);
	EXPECT_EQ(Vector4(40, 41, 42, 43), m2[3]);
}

TYPED_TEST(MathMatrix4x4Test, IndexAccessTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix4x4  m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};

		m[0][0] = 50;
		m[1] = Vector4(51, 52, 53, 54);
		m[2][1] = 55;
		m[3][3] = 56;

		EXPECT_EQ(Vector4(50, 12, 13, 14), m[0]);
		EXPECT_EQ(Vector4(51, 52, 53, 54), m[1]);
		EXPECT_EQ(Vector4(31, 55, 33, 34), m[2]);
		EXPECT_EQ(Vector4(41, 42, 43, 56), m[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), m[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), m[3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, AtTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix4x4  m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};

		m.at(0).at(0) = 50;
		m.at(1) = Vector4(51, 52, 53, 54);
		m.at(2).at(1) = 55;
		m.at(3).at(3) = 56;

		EXPECT_EQ(Vector4(50, 12, 13, 14), m.at(0));
		EXPECT_EQ(Vector4(51, 52, 53, 54), m.at(1));
		EXPECT_EQ(Vector4(31, 55, 33, 34), m.at(2));
		EXPECT_EQ(Vector4(41, 42, 43, 56), m.at(3));
		EXPECT_THROW((void)m.at(0).at(4), std::out_of_range);
		EXPECT_THROW((void)m.at(4), std::out_of_range);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), m.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), m.at(2));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), m.at(3));
		EXPECT_THROW((void)m.at(0).at(4), std::out_of_range);
		EXPECT_THROW((void)m.at(4), std::out_of_range);
	}
}

TYPED_TEST(MathMatrix4x4Test, DataTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix4x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
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
		++p;
		EXPECT_EQ(Vector4(41, 42, 43, 44), *p);

		EXPECT_EQ(Vector4(51, 52, 53, 54), m[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), m[1]);
		EXPECT_EQ(Vector4(61, 62, 63, 64), m[2]);
		EXPECT_EQ(Vector4(41, 42, 43, 44), m[3]);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Matrix4x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};
		BKSGE_STATIC_CONSTEXPR auto p = m.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), p[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), p[3]);
	}
#endif
}

TYPED_TEST(MathMatrix4x4Test, IteratorTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// begin, end (non const)
	{
		Matrix4x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
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
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector4(41, 42, 43, 44), *it);
		it++;
		EXPECT_TRUE(it == m.end());

		EXPECT_EQ(Vector4(51, 52, 53, 54), m[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), m[1]);
		EXPECT_EQ(Vector4(61, 62, 63, 64), m[2]);
		EXPECT_EQ(Vector4(41, 42, 43, 44), m[3]);
	}
	// begin, end (const)
	{
		Matrix4x4 const m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};
		auto it = m.begin();
		EXPECT_TRUE(it != m.end());

		EXPECT_EQ(Vector4(11, 12, 13, 14), it[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), it[1]);
		EXPECT_EQ(Vector4(31, 32, 33, 34), it[2]);
		EXPECT_EQ(Vector4(41, 42, 43, 44), it[3]);

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
		EXPECT_TRUE(it != m.end());
		EXPECT_EQ(Vector4(41, 42, 43, 44), *it);
		++it;
		EXPECT_TRUE(it == m.end());
	}
	// cbegin, cend
	{
		Matrix4x4 const m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};
		auto it = m.cbegin();
		EXPECT_TRUE(it != m.cend());

		EXPECT_EQ(Vector4(11, 12, 13, 14), it[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), it[1]);
		EXPECT_EQ(Vector4(31, 32, 33, 34), it[2]);
		EXPECT_EQ(Vector4(41, 42, 43, 44), it[3]);

		EXPECT_EQ(Vector4(11, 12, 13, 14), *it++);
		EXPECT_TRUE(it != m.cend());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *++it);
		EXPECT_TRUE(it != m.cend());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *it++);
		EXPECT_TRUE(it != m.cend());
		EXPECT_EQ(Vector4(41, 42, 43, 44), *it++);
		EXPECT_TRUE(it == m.cend());
	}
#if !defined(BKSGE_GCC)
	// begin, end (constexpr)
	{
		BKSGE_STATIC_CONSTEXPR Matrix4x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};
		BKSGE_CONSTEXPR_OR_CONST auto it = m.begin();
		BKSGE_CONSTEXPR_EXPECT_TRUE(it != m.end());

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), it[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), it[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), it[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), it[3]);

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
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 != m.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), *it5);
		BKSGE_CONSTEXPR_OR_CONST auto it6 = it5 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it6 == m.end());
	}
#endif
}

TYPED_TEST(MathMatrix4x4Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// rbegin, rend (non const)
	{
		Matrix4x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};
		auto it = m.rbegin();
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(41, 42, 43, 44), *it);
		*it++ = Vector4{51, 52, 53, 54};
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *it);
		*++it = Vector4{61, 62, 63, 64};
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(61, 62, 63, 64), *it);
		it++;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(11, 12, 13, 14), *it);
		it++;
		EXPECT_TRUE(it == m.rend());

		EXPECT_EQ(Vector4(11, 12, 13, 14), m[0]);
		EXPECT_EQ(Vector4(61, 62, 63, 64), m[1]);
		EXPECT_EQ(Vector4(31, 32, 33, 34), m[2]);
		EXPECT_EQ(Vector4(51, 52, 53, 54), m[3]);
	}
	// rbegin, rend (const)
	{
		Matrix4x4 const m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};
		auto it = m.rbegin();
		EXPECT_TRUE(it != m.rend());

		EXPECT_EQ(Vector4(41, 42, 43, 44), it[0]);
		EXPECT_EQ(Vector4(31, 32, 33, 34), it[1]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), it[2]);
		EXPECT_EQ(Vector4(11, 12, 13, 14), it[3]);

		EXPECT_EQ(Vector4(41, 42, 43, 44), *it++);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(21, 22, 23, 24), *++it);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *--it);
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(31, 32, 33, 34), *it--);
		EXPECT_TRUE(it != m.rend());
		it += 2;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(21, 22, 23, 24), *it);
		it -= 2;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(41, 42, 43, 44), *it);
		it += 3;
		EXPECT_TRUE(it != m.rend());
		EXPECT_EQ(Vector4(11, 12, 13, 14), *it);
		++it;
		EXPECT_TRUE(it == m.rend());
	}
	// crbegin, crend
	{
		Matrix4x4 const m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};
		auto it = m.crbegin();
		EXPECT_TRUE(it != m.crend());

		EXPECT_EQ(Vector4(41, 42, 43, 44), it[0]);
		EXPECT_EQ(Vector4(31, 32, 33, 34), it[1]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), it[2]);
		EXPECT_EQ(Vector4(11, 12, 13, 14), it[3]);

		EXPECT_EQ(Vector4(41, 42, 43, 44), *it++);
		EXPECT_TRUE(it != m.crend());
		EXPECT_EQ(Vector4(21, 22, 23, 24), *++it);
		EXPECT_TRUE(it != m.crend());
		EXPECT_EQ(Vector4(21, 22, 23, 24), *it++);
		EXPECT_TRUE(it != m.crend());
		EXPECT_EQ(Vector4(11, 12, 13, 14), *it++);
		EXPECT_TRUE(it == m.crend());
	}
#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201603)
	// rbegin, rend (constexpr)
	{
		BKSGE_CXX17_STATIC_CONSTEXPR Matrix4x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = m.rbegin();
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it != m.rend());

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), it[0]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), it[1]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), it[2]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), it[3]);

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), *it);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it2 != m.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), *it2);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it3 != m.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), *it3);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), *it4);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 != m.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), *it5);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it6 = it5 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it6 == m.rend());
	}
#endif
}

TYPED_TEST(MathMatrix4x4Test, EmptyTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	Matrix4x4 m1{};
	const           Matrix4x4 m2{};
	BKSGE_CONSTEXPR Matrix4x4 m3{};
	EXPECT_FALSE(m1.empty());
	EXPECT_FALSE(m2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(m3.empty());
}

TYPED_TEST(MathMatrix4x4Test, SizeTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	Matrix4x4 m1{};
	const           Matrix4x4 m2{};
	BKSGE_CONSTEXPR Matrix4x4 m3{};
	EXPECT_EQ(4u, m1.size());
	EXPECT_EQ(4u, m2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, m3.size());
}

TYPED_TEST(MathMatrix4x4Test, MaxSizeTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	Matrix4x4 m1{};
	const           Matrix4x4 m2{};
	BKSGE_CONSTEXPR Matrix4x4 m3{};
	EXPECT_EQ(4u, m1.max_size());
	EXPECT_EQ(4u, m2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, m3.max_size());
}

TYPED_TEST(MathMatrix4x4Test, NameAccessTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix4x4 m1
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};
		EXPECT_EQ(Vector4(11, 12, 13, 14), m1.x());
		EXPECT_EQ(Vector4(21, 22, 23, 24), m1.y());
		EXPECT_EQ(Vector4(31, 32, 33, 34), m1.z());
		EXPECT_EQ(Vector4(41, 42, 43, 44), m1.w());
		EXPECT_EQ(11, m1.x().x());
		EXPECT_EQ(12, m1.x().y());
		EXPECT_EQ(13, m1.x().z());
		EXPECT_EQ(14, m1.x().w());
		EXPECT_EQ(41, m1.w().x());
		EXPECT_EQ(42, m1.w().y());
		EXPECT_EQ(43, m1.w().z());
		EXPECT_EQ(44, m1.w().w());
		m1.x() = Vector4{0, 1, 2, 3};
		m1.z() = Vector4{4, 5, 6, 7};

		EXPECT_EQ(Vector4( 0,  1,  2,  3), m1[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), m1[1]);
		EXPECT_EQ(Vector4( 4,  5,  6,  7), m1[2]);
		EXPECT_EQ(Vector4(41, 42, 43, 44), m1[3]);

		m1.x().y() = -1;
		m1.y().x() = -2;
		m1.w().z() = -3;

		EXPECT_EQ(Vector4( 0, -1,  2,  3), m1[0]);
		EXPECT_EQ(Vector4(-2, 22, 23, 24), m1[1]);
		EXPECT_EQ(Vector4( 4,  5,  6,  7), m1[2]);
		EXPECT_EQ(Vector4(41, 42, -3, 44), m1[3]);
	}

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2
		{
			Vector4{51, 52, 53, 54},
			Vector4{61, 62, 63, 64},
			Vector4{71, 72, 73, 74},
			Vector4{81, 82, 83, 84},
		};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(51, 52, 53, 54), m2.x());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(61, 62, 63, 64), m2.y());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(71, 72, 73, 74), m2.z());
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(81, 82, 83, 84), m2.w());
		BKSGE_CONSTEXPR_EXPECT_EQ(51, m2.x().x());
		BKSGE_CONSTEXPR_EXPECT_EQ(52, m2.x().y());
		BKSGE_CONSTEXPR_EXPECT_EQ(53, m2.x().z());
		BKSGE_CONSTEXPR_EXPECT_EQ(54, m2.x().w());
		BKSGE_CONSTEXPR_EXPECT_EQ(81, m2.w().x());
		BKSGE_CONSTEXPR_EXPECT_EQ(82, m2.w().y());
		BKSGE_CONSTEXPR_EXPECT_EQ(83, m2.w().z());
		BKSGE_CONSTEXPR_EXPECT_EQ(84, m2.w().w());
	}
}

TYPED_TEST(MathMatrix4x4Test, SwizzleTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
		Vector4{41, 42, 43, 44},
	};

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2{m.wxzy()};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), m2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), m2[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m2{m.xxw()};
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), m2[2]);
	}
}

TYPED_TEST(MathMatrix4x4Test, SwapTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix4x4 m1
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
		Vector4{41, 42, 43, 44},
	};
	Matrix4x4 m2
	{
		Vector4{51, 52, 53, 54},
		Vector4{61, 62, 63, 64},
		Vector4{71, 72, 73, 74},
		Vector4{81, 82, 83, 84},
	};

	EXPECT_EQ(Vector4(11, 12, 13, 14), m1[0]);
	EXPECT_EQ(Vector4(21, 22, 23, 24), m1[1]);
	EXPECT_EQ(Vector4(31, 32, 33, 34), m1[2]);
	EXPECT_EQ(Vector4(41, 42, 43, 44), m1[3]);
	EXPECT_EQ(Vector4(51, 52, 53, 54), m2[0]);
	EXPECT_EQ(Vector4(61, 62, 63, 64), m2[1]);
	EXPECT_EQ(Vector4(71, 72, 73, 74), m2[2]);
	EXPECT_EQ(Vector4(81, 82, 83, 84), m2[3]);

	m1.swap(m2);

	EXPECT_EQ(Vector4(51, 52, 53, 54), m1[0]);
	EXPECT_EQ(Vector4(61, 62, 63, 64), m1[1]);
	EXPECT_EQ(Vector4(71, 72, 73, 74), m1[2]);
	EXPECT_EQ(Vector4(81, 82, 83, 84), m1[3]);
	EXPECT_EQ(Vector4(11, 12, 13, 14), m2[0]);
	EXPECT_EQ(Vector4(21, 22, 23, 24), m2[1]);
	EXPECT_EQ(Vector4(31, 32, 33, 34), m2[2]);
	EXPECT_EQ(Vector4(41, 42, 43, 44), m2[3]);

	swap(m1, m2);

	EXPECT_EQ(Vector4(11, 12, 13, 14), m1[0]);
	EXPECT_EQ(Vector4(21, 22, 23, 24), m1[1]);
	EXPECT_EQ(Vector4(31, 32, 33, 34), m1[2]);
	EXPECT_EQ(Vector4(41, 42, 43, 44), m1[3]);
	EXPECT_EQ(Vector4(51, 52, 53, 54), m2[0]);
	EXPECT_EQ(Vector4(61, 62, 63, 64), m2[1]);
	EXPECT_EQ(Vector4(71, 72, 73, 74), m2[2]);
	EXPECT_EQ(Vector4(81, 82, 83, 84), m2[3]);
}

TYPED_TEST(MathMatrix4x4Test, PlusMinusTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix4x4 m1
		{
			Vector4{-11,  12,  13,  14},
			Vector4{ 21,  22, -23,  24},
			Vector4{ 31, -32,  33,  34},
			Vector4{ 41,  42,  43, -44},
		};
		Matrix4x4 m2 = +m1;
		Matrix4x4 m3 = -m1;

		EXPECT_EQ(Vector4(-11,  12,  13,  14), m2[0]);
		EXPECT_EQ(Vector4( 21,  22, -23,  24), m2[1]);
		EXPECT_EQ(Vector4( 31, -32,  33,  34), m2[2]);
		EXPECT_EQ(Vector4( 41,  42,  43, -44), m2[3]);
		EXPECT_EQ(Vector4( 11, -12, -13, -14), m3[0]);
		EXPECT_EQ(Vector4(-21, -22,  23, -24), m3[1]);
		EXPECT_EQ(Vector4(-31,  32, -33, -34), m3[2]);
		EXPECT_EQ(Vector4(-41, -42, -43,  44), m3[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
		{
			Vector4{-11,  12,  13,  14},
			Vector4{ 21,  22, -23,  24},
			Vector4{ 31, -32,  33,  34},
			Vector4{ 41,  42,  43, -44},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2 = +m1;
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m3 = -m1;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-11,  12,  13,  14), m2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 21,  22, -23,  24), m2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 31, -32,  33,  34), m2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 41,  42,  43, -44), m2[3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 11, -12, -13, -14), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-21, -22,  23, -24), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-31,  32, -33, -34), m3[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-41, -42, -43,  44), m3[3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, AddTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix4x4 += Matrix4x4
	{
		Matrix4x4 m1;

		Matrix4x4 t = m1 += Matrix4x4
		{
			Vector4{ 1,  2,  3,  4},
			Vector4{ 5,  6,  7,  8},
			Vector4{ 9, 10, 11, 12},
			Vector4{13, 14, 15, 16},
		};

		EXPECT_EQ(Vector4( 1,  2,  3,  4), m1[0]);
		EXPECT_EQ(Vector4( 5,  6,  7,  8), m1[1]);
		EXPECT_EQ(Vector4( 9, 10, 11, 12), m1[2]);
		EXPECT_EQ(Vector4(13, 14, 15, 16), m1[3]);
		EXPECT_EQ(t, m1);
	}

	// Matrix4x4 + Matrix4x4 -> Matrix4x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
		{
			Vector4{-21,  22,  23,  30},
			Vector4{ 24, -25,  26,  31},
			Vector4{ 27,  28, -29,  32},
			Vector4{-33,  34,  35, -36},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2
		{
			Vector4{ 31,  32, -33,  40},
			Vector4{ 34, -35,  36, -41},
			Vector4{-37,  38,  39,  42},
			Vector4{-43,  44, -45,  46},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m3 = m1 + m2;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 10,  54, -10,  70), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 58, -60,  62, -10), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-10,  66,  10,  74), m3[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-76,  78, -10,  10), m3[3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, SubTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix4x4 -= Matrix4x4
	{
		Matrix4x4 m1;
		Matrix4x4 t = m1 -= Matrix4x4
		{
			Vector4{ 1,  2,  3,  4},
			Vector4{ 5,  6,  7,  8},
			Vector4{ 9, 10, 11, 12},
			Vector4{13, 14, 15, 16},
		};

		EXPECT_EQ(Vector4( -1,  -2,  -3,  -4), m1[0]);
		EXPECT_EQ(Vector4( -5,  -6,  -7,  -8), m1[1]);
		EXPECT_EQ(Vector4( -9, -10, -11, -12), m1[2]);
		EXPECT_EQ(Vector4(-13, -14, -15, -16), m1[3]);
		EXPECT_EQ(t, m1);
	}

	// Matrix4x4 - Matrix4x4 -> Matrix4x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
		{
			Vector4{10, 11, 12, 13},
			Vector4{20, 21, 22, 23},
			Vector4{30, 31, 32, 33},
			Vector4{40, 41, 42, 43},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2
		{
			Vector4{0, 9, 1, 2},
			Vector4{8, 4, 7, 9},
			Vector4{6, 5, 3, 1},
			Vector4{4, 8, 5, 0},
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m3 = m1 - m2;

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(10, 2, 11, 11), m3[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(12, 17, 15, 14), m3[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(24, 26, 29, 32), m3[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(36, 33, 37, 43), m3[3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, MulScalarTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix4x4 *= スカラー
	{
		Matrix4x4 m1
		{
			Vector4{ 1,  2,  3,  4},
			Vector4{ 5,  6,  7,  8},
			Vector4{ 9, 10, 11, 12},
			Vector4{13, 14, 15, 16},
		};
		{
			Matrix4x4 t = (m1 *= 2);
			EXPECT_EQ(Vector4( 2,  4,  6,  8), m1[0]);
			EXPECT_EQ(Vector4(10, 12, 14, 16), m1[1]);
			EXPECT_EQ(Vector4(18, 20, 22, 24), m1[2]);
			EXPECT_EQ(Vector4(26, 28, 30, 32), m1[3]);
			EXPECT_EQ(t, m1);
		}
		{
			Matrix4x4 t = (m1 *= 2.5);
			EXPECT_EQ(Vector4( 5, 10, 15, 20), m1[0]);
			EXPECT_EQ(Vector4(25, 30, 35, 40), m1[1]);
			EXPECT_EQ(Vector4(45, 50, 55, 60), m1[2]);
			EXPECT_EQ(Vector4(65, 70, 75, 80), m1[3]);
			EXPECT_EQ(t, m1);
		}
	}

	// Matrix4x4 * スカラー -> Matrix4x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
		{
			Vector4{10, 12, 14, 16},
			Vector4{20, 22, 24, 26},
			Vector4{30, 32, 34, 36},
			Vector4{40, 42, 44, 46},
		};
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x4 t = m1 * 3;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 30,  36,  42,  48), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 60,  66,  72,  78), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 90,  96, 102, 108), t[2]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(120, 126, 132, 138), t[3]);
		}
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x4 t = m1 * 2.5;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 25,  30,  35,  40), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 50,  55,  60,  65), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 75,  80,  85,  90), t[2]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(100, 105, 110, 115), t[3]);
		}
		// スカラー * Matrix4x4 -> Matrix4x4
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x4 t = 4 * m1;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 40,  48,  56,  64), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 80,  88,  96, 104), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(120, 128, 136, 144), t[2]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(160, 168, 176, 184), t[3]);
		}
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x4 t = -1.5 * m1;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-15, -18, -21, -24), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-30, -33, -36, -39), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-45, -48, -51, -54), t[2]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-60, -63, -66, -69), t[3]);
		}
	}
}

TYPED_TEST(MathMatrix4x4Test, MulMatrixTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Matrix4x3 = bksge::math::Matrix4x3<T>;
	using Matrix3x4 = bksge::math::Matrix3x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Matrix4x4 *= Matrix4x4
	{
		Matrix4x4 m
		{
			Vector4{  2,  4,  6,  8 },
			Vector4{ 10, 12, 14, 16 },
			Vector4{ 18, 20, 22, 24 },
			Vector4{ 26, 28, 30, 32 },
		};

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
		{
			Vector4{  11, -12,  13,  14 },
			Vector4{  21,  22, -23,  24 },
			Vector4{ -31,  32,  33,  34 },
			Vector4{  41,  42,  43, -44 },
		};

		auto t = m *= m1;
		static_assert(bksge::is_same<decltype(t), Matrix4x4>::value, "");
		EXPECT_EQ(Vector4( 248,  592,  476, -24), m[0]);
		EXPECT_EQ(Vector4( 584, 1264, 1004, 200), m[1]);
		EXPECT_EQ(Vector4( 920, 1936, 1532, 424), m[2]);
		EXPECT_EQ(Vector4(1256, 2608, 2060, 648), m[3]);
		EXPECT_EQ(t, m);
	}

	// Matrix4x4 * Matrix4x4 -> Matrix4x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
		{
			Vector4{  15,   3,  -7,   4 },
			Vector4{  11,   4,  12,  -8 },
			Vector4{   2,   6,  13,  10 },
			Vector4{   1,  14,   9,   5 },
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2
		{
			Vector4{   1,   2,   3,   4 },
			Vector4{   5,   6,   7,   8 },
			Vector4{   9,  10, -11, -12 },
			Vector4{  13, -14,  15,  16 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), Matrix4x4 const>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(  19,  -78,  203,  232), t1[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(  35,  278, -191, -196), t1[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 279,   30,   55,   60), t1[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 217,  106,   77,   88), t1[3]);

		BKSGE_CONSTEXPR_OR_CONST auto t2 = m2 * m1;
		static_assert(bksge::is_same<decltype(t2), Matrix4x4 const>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(  47,   85,   92,   38), t2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 163,  193,  200,   82), t2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 211, -167, -194, -214), t2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(  87,  297,   80,  394), t2[3]);
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

	// Matrix3x4 * Matrix4x4 -> Matrix3x4
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix3x4 m1
		{
			Vector4{ 11, 12, 13, 14 },
			Vector4{ 21, 22, 23, 24 },
			Vector4{ 31, 32, 33, 34 },
		};
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2
		{
			Vector4{  1,  2,  3,  4 },
			Vector4{  5,  6,  7,  8 },
			Vector4{  9, 10, 11, 12 },
			Vector4{ 13, 14, 15, 16 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t1 = m1 * m2;
		static_assert(bksge::is_same<decltype(t1), const Matrix3x4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 370, 420, 470, 520), t1[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 650, 740, 830, 920), t1[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 930,1060,1190,1320), t1[2]);
	}
}

TYPED_TEST(MathMatrix4x4Test, MulVectorTest)
{
	using Matrix4x4 = bksge::math::Matrix4x4<TypeParam>;
	using Vector4 = bksge::math::Vector4<TypeParam>;

	Vector4 v { 1, 2, 3, 4 };

	// Vector4 *= Matrix4x4
	{
		Matrix4x4 const m
		{
			Vector4{ 11, 12, 13, 14 },
			Vector4{ 21, 22, 23, 24 },
			Vector4{ 31, 32, 33, 34 },
			Vector4{ 41, 42, 43, 44 },
		};

		auto t = v *= m;
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		EXPECT_EQ(Vector4(310, 320, 330, 340), v);
		EXPECT_EQ(t, v);
	}

	// Vector4 * Matrix4x4 -> Vector4
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v2 { -5, 6, 7, 8 };
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m
		{
			Vector4{   1,  -2,   3,   4 },
			Vector4{   5,   6,   7,   8 },
			Vector4{   9,  10, -11, -12 },
			Vector4{  13, -14,  15,  16 },
		};

		BKSGE_CONSTEXPR_OR_CONST auto t = v2 * m;
		static_assert(bksge::is_same<decltype(t), const Vector4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(192, 4, 70, 72), t);
	}
}

TYPED_TEST(MathMatrix4x4Test, DivScalarTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// Matrix4x4 /= スカラー
	{
		Matrix4x4 m1
		{
			Vector4{10, 12, 14, 16},
			Vector4{18, 20, 22, 24},
			Vector4{26, 28, 30, 32},
			Vector4{34, 36, 38, 40},
		};

		{
			Matrix4x4 t = (m1 /= 2);
			EXPECT_EQ(Vector4( 5,  6,  7,  8), m1[0]);
			EXPECT_EQ(Vector4( 9, 10, 11, 12), m1[1]);
			EXPECT_EQ(Vector4(13, 14, 15, 16), m1[2]);
			EXPECT_EQ(Vector4(17, 18, 19, 20), m1[3]);
			EXPECT_EQ(t, m1);
		}
		{
			Matrix4x4 t = (m1 /= 0.5);
			EXPECT_EQ(Vector4(10, 12, 14, 16), m1[0]);
			EXPECT_EQ(Vector4(18, 20, 22, 24), m1[1]);
			EXPECT_EQ(Vector4(26, 28, 30, 32), m1[2]);
			EXPECT_EQ(Vector4(34, 36, 38, 40), m1[3]);
			EXPECT_EQ(t, m1);
		}
	}

	// Matrix4x4 / スカラー
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
		{
			Vector4{10, 12, 14, 16},
			Vector4{20, 22, 24, 26},
			Vector4{30, 32, 34, 36},
			Vector4{40, 42, 44, 46},
		};

		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x4 t = m1 / 2;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 5,  6,  7,  8), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(10, 11, 12, 13), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(15, 16, 17, 18), t[2]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(20, 21, 22, 23), t[3]);
		}
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x4 t = m1 / 0.25;
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 40,  48,  56,  64), t[0]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 80,  88,  96, 104), t[1]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(120, 128, 136, 144), t[2]);
			BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(160, 168, 176, 184), t[3]);
		}
	}
}

TYPED_TEST(MathMatrix4x4Test, CompareTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix4x4  m1
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
		Vector4{41, 42, 43, 44},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4  m2
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
		Vector4{41, 42, 43, 44},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4  m3
	{
		Vector4{10, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
		Vector4{41, 42, 43, 44},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4  m4
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 23, 23, 24},
		Vector4{31, 32, 33, 34},
		Vector4{41, 42, 43, 44},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4  m5
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, -33, 34},
		Vector4{41, 42, 43, 44},
	};
	BKSGE_CONSTEXPR_OR_CONST Matrix4x4  m6
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
		Vector4{41, 42, 43, 45},
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

TYPED_TEST(MathMatrix4x4Test, OutputStreamTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix4x4 const m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};
		std::stringstream ss;
		ss << m;
		EXPECT_EQ("{ { 11, 12, 13, 14 }, { 21, 22, 23, 24 }, { 31, 32, 33, 34 }, { 41, 42, 43, 44 } }", ss.str());
	}
	{
		Matrix4x4 const m
		{
			Vector4{51, 52, 53, 54},
			Vector4{61, 62, 63, 64},
			Vector4{71, 72, 73, 74},
			Vector4{81, 82, 83, 84},
		};
		std::wstringstream ss;
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

TYPED_TEST(MathMatrix4x4Test, TupleGetTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		Matrix4x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};

		EXPECT_EQ(Vector4(11, 12, 13, 14), bksge::get<0>(m));
		EXPECT_EQ(Vector4(21, 22, 23, 24), bksge::get<1>(m));
		EXPECT_EQ(Vector4(31, 32, 33, 34), bksge::get<2>(m));
		EXPECT_EQ(Vector4(41, 42, 43, 44), bksge::get<3>(m));

		bksge::get<0>(m) = Vector4{51, 52, 53, 54};
		bksge::get<3>(m) = Vector4{61, 62, 63, 64};

		EXPECT_EQ(Vector4(51, 52, 53, 54), m[0]);
		EXPECT_EQ(Vector4(21, 22, 23, 24), m[1]);
		EXPECT_EQ(Vector4(31, 32, 33, 34), m[2]);
		EXPECT_EQ(Vector4(61, 62, 63, 64), m[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m
		{
			Vector4{11, 12, 13, 14},
			Vector4{21, 22, 23, 24},
			Vector4{31, 32, 33, 34},
			Vector4{41, 42, 43, 44},
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), bksge::get<0>(m));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), bksge::get<1>(m));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), bksge::get<2>(m));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), bksge::get<3>(m));
	}
}

TYPED_TEST(MathMatrix4x4Test, TupleSizeTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;

	static_assert(bksge::tuple_size<Matrix4x4>::value == 4, "");
}

TYPED_TEST(MathMatrix4x4Test, ZeroTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x4::Zero();
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 0, 0), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 0, 0), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 0, 0), m[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 0, 0), m[3]);
	}
	{
		const auto m = Matrix4x4::Zero();
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		EXPECT_EQ(Vector4(0, 0, 0, 0), m[0]);
		EXPECT_EQ(Vector4(0, 0, 0, 0), m[1]);
		EXPECT_EQ(Vector4(0, 0, 0, 0), m[2]);
		EXPECT_EQ(Vector4(0, 0, 0, 0), m[3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, IdentityTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x4::Identity();
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 0, 0, 0), m[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 1, 0, 0), m[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 1, 0), m[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 0, 1), m[3]);
	}
	{
		const auto m = Matrix4x4::Identity();
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		EXPECT_EQ(Vector4(1, 0, 0, 0), m[0]);
		EXPECT_EQ(Vector4(0, 1, 0, 0), m[1]);
		EXPECT_EQ(Vector4(0, 0, 1, 0), m[2]);
		EXPECT_EQ(Vector4(0, 0, 0, 1), m[3]);
	}
}

TYPED_TEST(MathMatrix4x4Test, TransposedTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
	{
		Vector4{ 11, 12, 13, 14 },
		Vector4{ 21, 22, 23, 24 },
		Vector4{ 31, 32, 33, 34 },
		Vector4{ 41, 42, 43, 44 },
	};

	BKSGE_CONSTEXPR_OR_CONST auto m2 = Transposed(m1);
	static_assert(bksge::is_same<decltype(m2), Matrix4x4 const>::value, "");
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 21, 31, 41), m2[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(12, 22, 32, 42), m2[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(13, 23, 33, 43), m2[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(14, 24, 34, 44), m2[3]);

	BKSGE_CONSTEXPR_OR_CONST auto m3 = Transposed(m2);
	static_assert(bksge::is_same<decltype(m3), Matrix4x4 const>::value, "");
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(11, 12, 13, 14), m3[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(21, 22, 23, 24), m3[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(31, 32, 33, 34), m3[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(41, 42, 43, 44), m3[3]);

	BKSGE_CONSTEXPR_EXPECT_EQ(m1, m3);
}

TYPED_TEST(MathMatrix4x4Test, ResizedTest)
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
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2 = bksge::math::Resized<4, 4>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
		{
			Vector4{ 1, 2, 3, 0 },
			Vector4{ 4, 5, 6, 0 },
			Vector4{ 7, 8, 9, 0 },
			Vector4{ 0, 0, 0, 1 },
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

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2 = bksge::math::Resized<4, 4>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
		{
			Vector4{ 10, 11, 12, 0 },
			Vector4{ 20, 21, 22, 0 },
			Vector4{ 30, 31, 32, 0 },
			Vector4{ 40, 41, 42, 1 },
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

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2 = bksge::math::Resized<4, 4>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
		{
			Vector4{ 10, 11, 12, 13 },
			Vector4{ 20, 21, 22, 23 },
			Vector4{ 30, 31, 32, 33 },
			Vector4{  0,  0,  0,  1 },
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

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2 = bksge::math::Resized<4, 4>(m1);

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
		{
			Vector4{ 11, 12, 13, 14 },
			Vector4{ 21, 22, 23, 24 },
			Vector4{ 31, 32, 33, 34 },
			Vector4{ 41, 42, 43, 44 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m2);
	}
}

TYPED_TEST(MathMatrix4x4Test, InversedTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m
		{
			Vector4{  1,  0,  1,  2 },
			Vector4{ -1,  1,  1,  1 },
			Vector4{  1, -1,  0,  1 },
			Vector4{  1,  1, -1, -2 },
		};

		BKSGE_CXX14_CONSTEXPR_OR_CONST auto m_inv = Inversed(m);
		static_assert(bksge::is_same<decltype(m_inv), Matrix4x4 const>::value, "");

		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Vector4( 1, -1, -1,  0), m_inv[0]);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Vector4(-1,  2,  2,  1), m_inv[1]);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Vector4( 4, -5, -7, -2), m_inv[2]);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Vector4(-2,  3,  4,  1), m_inv[3]);

		// 逆行列の逆行列はもとの行列にもどる
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto m_inv_inv = Inversed(m_inv);
		static_assert(bksge::is_same<decltype(m_inv_inv), Matrix4x4 const>::value, "");
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(m, m_inv_inv);

		// 行列とその逆行列をかけると単位行列になる
		BKSGE_CXX14_CONSTEXPR_OR_CONST auto m2 = m * m_inv;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Matrix4x4::Identity(), m2);

		BKSGE_CXX14_CONSTEXPR_OR_CONST auto m3 = m_inv * m;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(Matrix4x4::Identity(), m3);
	}
}

TYPED_TEST(MathMatrix4x4Test, DeterminantTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m1
	{
		Vector4{  3,  1,  1,  2 },
		Vector4{  5,  1,  3,  4 },
		Vector4{  2,  0,  1,  0 },
		Vector4{  1,  3,  2,  1 },
	};

	BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m2
	{
		Vector4{  1, -2,  3,  2 },
		Vector4{ -2,  2,  0,  2 },
		Vector4{  2,  4, -1, -2 },
		Vector4{  3,  5, -7, -6 },
	};

	BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m3
	{
		Vector4{  2,  0,  0,  0 },
		Vector4{  1,  2,  1, -2 },
		Vector4{ -3, -1,  1,  2 },
		Vector4{  1,  0,  0, -1 },
	};

	BKSGE_CONSTEXPR_EXPECT_EQ(TypeParam( -22), Determinant(m1));
	BKSGE_CONSTEXPR_EXPECT_EQ(TypeParam(-102), Determinant(m2));
	BKSGE_CONSTEXPR_EXPECT_EQ(TypeParam(  -6), Determinant(m3));

	// XMMatrixDeterminant と同じかどうかをテストします。
#if defined(BKSGE_DXMATH_TEST)
	EXPECT_EQ(XMVectorGetX(XMMatrixDeterminant(ToXMMATRIX(m1))), Determinant(m1));
	EXPECT_EQ(XMVectorGetX(XMMatrixDeterminant(ToXMMATRIX(m2))), Determinant(m2));
	EXPECT_EQ(XMVectorGetX(XMMatrixDeterminant(ToXMMATRIX(m3))), Determinant(m3));
#endif
}

TYPED_TEST(MathMatrix4x4Test, MakeTranslationTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// XMMatrixTranslation と同じかどうかをテストします。

	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 trans(3, 4, 5);
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x4::MakeTranslation(trans);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
		{
			Vector4{ 1,  0,  0,  0 },
			Vector4{ 0,  1,  0,  0 },
			Vector4{ 0,  0,  1,  0 },
			Vector4{ 3,  4,  5,  1 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m);

#if defined(BKSGE_DXMATH_TEST)
		EXPECT_EQ(ToMatrix4x4<T>(XMMatrixTranslationFromVector(ToXMVECTOR(trans))), m);
#endif
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x4::MakeTranslation(Vector3{-4, 5, -6});
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
		{
			Vector4{  1,  0,  0,  0 },
			Vector4{  0,  1,  0,  0 },
			Vector4{  0,  0,  1,  0 },
			Vector4{ -4,  5, -6,  1 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m);

#if defined(BKSGE_DXMATH_TEST)
		EXPECT_EQ(ToMatrix4x4<T>(XMMatrixTranslation(-4, 5, -6)), m);
#endif
	}
	{
		const auto m = Matrix4x4::MakeTranslation(1, 2, 3);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		const Matrix4x4 expected
		{
			Vector4{  1,  0,  0,  0 },
			Vector4{  0,  1,  0,  0 },
			Vector4{  0,  0,  1,  0 },
			Vector4{  1,  2,  3,  1 },
		};

		EXPECT_EQ(expected, m);

#if defined(BKSGE_DXMATH_TEST)
		EXPECT_EQ(ToMatrix4x4<T>(XMMatrixTranslation(1, 2, 3)), m);
#endif
	}
}

TYPED_TEST(MathMatrix4x4Test, MakeScaleTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Scale3 = bksge::math::Scale3<T>;

	// XMMatrixScaling と同じかどうかをテストします。

	{
		BKSGE_CONSTEXPR_OR_CONST Scale3 scale(2, 3, 4);
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x4::MakeScale(scale);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
		{
			Vector4{ 2,  0,  0,  0 },
			Vector4{ 0,  3,  0,  0 },
			Vector4{ 0,  0,  4,  0 },
			Vector4{ 0,  0,  0,  1 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m);

#if defined(BKSGE_DXMATH_TEST)
		EXPECT_EQ(ToMatrix4x4<T>(XMMatrixScalingFromVector(ToXMVECTOR(scale))), m);
#endif
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x4::MakeScale(Scale3{ 5, -4, 3 });
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
		{
			Vector4{ 5,  0,  0,  0 },
			Vector4{ 0, -4,  0,  0 },
			Vector4{ 0,  0,  3,  0 },
			Vector4{ 0,  0,  0,  1 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m);

#if defined(BKSGE_DXMATH_TEST)
		EXPECT_EQ(ToMatrix4x4<T>(XMMatrixScaling(5, -4, 3)), m);
#endif
	}
	{
		const auto m = Matrix4x4::MakeScale(1, 2, 3);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		const Matrix4x4 expected
		{
			Vector4{ 1,  0,  0,  0 },
			Vector4{ 0,  2,  0,  0 },
			Vector4{ 0,  0,  3,  0 },
			Vector4{ 0,  0,  0,  1 },
		};

		EXPECT_EQ(expected, m);

#if defined(BKSGE_DXMATH_TEST)
		EXPECT_EQ(ToMatrix4x4<T>(XMMatrixScaling(1, 2, 3)), m);
#endif
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, MakeRotationXTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	double const error = 0.000001;

	// XMMatrixRotationX と同じかどうかをテストします。

	{
		auto const m = Matrix4x4::MakeRotationX(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		EXPECT_EQ(Matrix4x4::Identity(), m);
#if defined(BKSGE_DXMATH_TEST)
		EXPECT_EQ(ToMatrix4x4<T>(XMMatrixRotationX((float)bksge::degrees_to_radians(0))), m);
#endif
	}
	{
		auto const m = Matrix4x4::MakeRotationX(bksge::degrees_to_radians(30));
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixRotationX((float)bksge::degrees_to_radians(30)));
#else
		Matrix4x4 const expected
		{
			Vector4{ 1.0000000,  0.0000000, 0.0000000, 0.0000000 },
			Vector4{ 0.0000000,  0.8660253, 0.5000000, 0.0000000 },
			Vector4{ 0.0000000, -0.5000000, 0.8660253, 0.0000000 },
			Vector4{ 0.0000000,  0.0000000, 0.0000000, 1.0000000 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		auto const m = Matrix4x4::MakeRotationX(bksge::degrees_to_radians(90));
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixRotationX((float)bksge::degrees_to_radians(90)));
#else
		Matrix4x4 const expected
		{
			Vector4{ 1.0000000,  0.0000000, 0.0000000, 0.0000000 },
			Vector4{ 0.0000000,  0.0000000, 1.0000000, 0.0000000 },
			Vector4{ 0.0000000, -1.0000000, 0.0000000, 0.0000000 },
			Vector4{ 0.0000000,  0.0000000, 0.0000000, 1.0000000 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, MakeRotationYTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	double const error = 0.000001;

	// XMMatrixRotationY と同じかどうかをテストします。

	{
		auto const m = Matrix4x4::MakeRotationY(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		EXPECT_EQ(Matrix4x4::Identity(), m);
#if defined(BKSGE_DXMATH_TEST)
		EXPECT_EQ(ToMatrix4x4<T>(XMMatrixRotationY((float)bksge::degrees_to_radians(0))), m);
#endif
	}
	{
		auto const m = Matrix4x4::MakeRotationY(bksge::degrees_to_radians(45));
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixRotationY((float)bksge::degrees_to_radians(45)));
#else
		Matrix4x4 const expected
		{
			Vector4{ 0.7071067,  0.0000000, -0.7071067, 0.0000000 },
			Vector4{ 0.0000000,  1.0000000,  0.0000000, 0.0000000 },
			Vector4{ 0.7071067,  0.0000000,  0.7071067, 0.0000000 },
			Vector4{ 0.0000000,  0.0000000,  0.0000000, 1.0000000 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		auto const m = Matrix4x4::MakeRotationY(bksge::degrees_to_radians(90));
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixRotationY((float)bksge::degrees_to_radians(90)));
#else
		Matrix4x4 const expected
		{
			Vector4{ 0.0000000,  0.0000000, -1.0000000,  0.0000000 },
			Vector4{ 0.0000000,  1.0000000,  0.0000000,  0.0000000 },
			Vector4{ 1.0000000,  0.0000000,  0.0000000,  0.0000000 },
			Vector4{ 0.0000000,  0.0000000,  0.0000000,  1.0000000 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, MakeRotationZTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	double const error = 0.000001;

	// XMMatrixRotationZ と同じかどうかをテストします。

	{
		auto const m = Matrix4x4::MakeRotationZ(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");
		EXPECT_EQ(Matrix4x4::Identity(), m);
#if defined(BKSGE_DXMATH_TEST)
		EXPECT_EQ(ToMatrix4x4<T>(XMMatrixRotationZ((float)bksge::degrees_to_radians(0))), m);
#endif
	}
	{
		auto const m = Matrix4x4::MakeRotationZ(bksge::degrees_to_radians(60));
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixRotationZ((float)bksge::degrees_to_radians(60)));
#else
		Matrix4x4 const expected
		{
			Vector4{  0.5000000,  0.8660253,  0.0000000, 0.0000000 },
			Vector4{ -0.8660253,  0.5000000,  0.0000000, 0.0000000 },
			Vector4{  0.0000000,  0.0000000,  1.0000000, 0.0000000 },
			Vector4{  0.0000000,  0.0000000,  0.0000000, 1.0000000 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		auto const m = Matrix4x4::MakeRotationZ(bksge::degrees_to_radians(90));
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixRotationZ((float)bksge::degrees_to_radians(90)));
#else
		Matrix4x4 const expected
		{
			Vector4{ 0.0000000,  1.0000000,  0.0000000, 0.0000000 },
			Vector4{-1.0000000,  0.0000000,  0.0000000, 0.0000000 },
			Vector4{ 0.0000000,  0.0000000,  1.0000000, 0.0000000 },
			Vector4{ 0.0000000,  0.0000000,  0.0000000, 1.0000000 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, MakeRotationTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	double const error = 0.000001;

	// XMMatrixRotationAxis と同じかどうかをテストします。

	{
		auto const axis = Vector3(1, 2, 3);
		auto const r = bksge::degrees_to_radians(90);
		auto const m = Matrix4x4::MakeRotation(axis, r);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixRotationAxis(ToXMVECTOR(axis), (float)r));
#else
		Matrix4x4 const expected
		{
			Vector4{ 0.0714285,  0.9446408, -0.3202367, 0.0000000 },
			Vector4{-0.6589265,  0.2857142,  0.6958326, 0.0000000 },
			Vector4{ 0.7488081,  0.1613101,  0.6428570, 0.0000000 },
			Vector4{ 0.0000000,  0.0000000,  0.0000000, 1.0000000 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		auto const axis = Vector3(-1, 1, 10);
		auto const r = bksge::degrees_to_radians(120);
		auto const m = Matrix4x4::MakeRotation(axis, r);

#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixRotationAxis(ToXMVECTOR(axis), (float)r));
#else
		Matrix4x4 const expected
		{
			Vector4{-0.4852941,  0.8427870, -0.2328081, 0.0000000 },
			Vector4{-0.8721988, -0.4852941,  0.0613095, 0.0000000 },
			Vector4{-0.0613095,  0.2328081,  0.9705884, 0.0000000 },
			Vector4{ 0.0000000,  0.0000000,  0.0000000, 1.0000000 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
}

TYPED_TEST(MathMatrix4x4Test, MakeShearTest)
{
	using Matrix4x4 = bksge::math::Matrix4x4<TypeParam>;
	using Vector4 = bksge::math::Vector4<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x4::MakeShear(4, 5, 6);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
		{
			Vector4{ 1,  5,  6,  0 },
			Vector4{ 4,  1,  6,  0 },
			Vector4{ 4,  5,  1,  0 },
			Vector4{ 0,  0,  0,  1 },
		};

		BKSGE_CONSTEXPR_EXPECT_EQ(expected, m);
	}
	{
		const auto m = Matrix4x4::MakeShear(-1, 2, -3);
		static_assert(bksge::is_same<decltype(m), Matrix4x4 const>::value, "");

		const Matrix4x4 expected
		{
			Vector4{  1,  2, -3,  0 },
			Vector4{ -1,  1, -3,  0 },
			Vector4{ -1,  2,  1,  0 },
			Vector4{  0,  0,  0,  1 },
		};

		EXPECT_EQ(expected, m);
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, MakeOrthographicTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// XMMatrixOrthographicOffCenterLH と同じかどうかをテストします。

	{
		BKSGE_CONSTEXPR_OR_CONST T left   = 0;
		BKSGE_CONSTEXPR_OR_CONST T right  = 400;
		BKSGE_CONSTEXPR_OR_CONST T top    = 300;
		BKSGE_CONSTEXPR_OR_CONST T bottom = 0;
		BKSGE_CONSTEXPR_OR_CONST T nearz  = 1;
		BKSGE_CONSTEXPR_OR_CONST T farz   = 1000;

		BKSGE_CONSTEXPR_OR_CONST double error = 0.0001;
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m =
			Matrix4x4::MakeOrthographic(left, right, bottom, top, nearz, farz);
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
			{
				Vector4{  0.005,  0,           0,        0 },
				Vector4{  0,      0.00666667,  0,        0 },
				Vector4{  0,      0,           0.001001, 0 },
				Vector4{ -1,     -1,          -0.001001, 1 },
			};

			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
		}

#if defined(BKSGE_DXMATH_TEST)
		{
			Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixOrthographicOffCenterLH(left, right, bottom, top, nearz, farz));
			EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
			EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
			EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
			EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
			EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
			EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
			EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
			EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
			EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
			EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
			EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
			EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
			EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
			EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
			EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
			EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
		}
#endif
	}
	{
		const T left   = -300;
		const T right  = 300;
		const T top    = 100;
		const T bottom = -100;
		const T nearz  = 0.1f;
		const T farz   = 100;

		const double error = 0.0001;
		const Matrix4x4 m =
			Matrix4x4::MakeOrthographic(left, right, bottom, top, nearz, farz);
		{
			const Matrix4x4 expected
			{
				Vector4{  0.00333333, 0,     0,        0 },
				Vector4{  0,          0.01,  0,        0 },
				Vector4{  0,          0,     0.010010, 0 },
				Vector4{ -0,         -0,    -0.001001, 1 },
			};

			EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
			EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
			EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
			EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
			EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
			EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
			EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
			EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
			EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
			EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
			EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
			EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
			EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
			EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
			EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
			EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
		}
#if defined(BKSGE_DXMATH_TEST)
		{
			Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixOrthographicOffCenterLH(left, right, bottom, top, nearz, farz));
			EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
			EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
			EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
			EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
			EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
			EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
			EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
			EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
			EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
			EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
			EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
			EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
			EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
			EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
			EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
			EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
		}
#endif
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, MakeFrustumTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// XMMatrixPerspectiveOffCenterLH と同じかどうかをテストします。

	{
		BKSGE_CONSTEXPR_OR_CONST T left   = 0;
		BKSGE_CONSTEXPR_OR_CONST T right  = 400;
		BKSGE_CONSTEXPR_OR_CONST T bottom = 0;
		BKSGE_CONSTEXPR_OR_CONST T top    = 300;
		BKSGE_CONSTEXPR_OR_CONST T nearz  = 1;
		BKSGE_CONSTEXPR_OR_CONST T farz   = 1000;
		BKSGE_CONSTEXPR_OR_CONST double error = 0.00000001;
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 m =
			Matrix4x4::MakeFrustum(left, right, bottom, top, nearz, farz);
		{
			BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
			{
				Vector4{  0.005,  0,                     0,                   0 },
				Vector4{  0,      0.0066666666666666671, 0,                   0 },
				Vector4{ -1,     -1,                     1.0010010004043579,  1 },
				Vector4{  0,      0,                    -1.0010010004043579,  0 },
			};

			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
			BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
		}
#if defined(BKSGE_DXMATH_TEST)
		{
			Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixPerspectiveOffCenterLH(left, right, bottom, top, nearz, farz));
			EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
			EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
			EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
			EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
			EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
			EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
			EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
			EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
			EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
			EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
			EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
			EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
			EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
			EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
			EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
			EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
		}
#endif
	}
	{
		const T left   = -960;
		const T right  =  960;
		const T bottom = -540;
		const T top    =  540;
		const T nearz  = 0.001f;
		const T farz   = 1000;
		const double error = 0.000001;
		const Matrix4x4 m =
			Matrix4x4::MakeFrustum(left, right, bottom, top, nearz, farz);
		{
			const Matrix4x4 expected
			{
				Vector4{  0.0000010416667161431785, 0,                     0,                   0 },
				Vector4{  0,                        0.0000018518519398100, 0,                   0 },
				Vector4{  0,                        0,                     1.0000009536743164,  1 },
				Vector4{  0,                        0,                    -0.0010000009788200,  0 },
			};

			EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
			EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
			EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
			EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
			EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
			EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
			EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
			EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
			EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
			EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
			EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
			EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
			EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
			EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
			EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
			EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
		}
#if defined(BKSGE_DXMATH_TEST)
		{
			Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixPerspectiveOffCenterLH(left, right, bottom, top, nearz, farz));
			EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
			EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
			EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
			EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
			EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
			EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
			EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
			EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
			EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
			EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
			EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
			EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
			EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
			EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
			EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
			EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
		}
#endif
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, MakePerspectiveTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	// XMMatrixPerspectiveFovLH と同じかどうかをテストします。

	double const error = 0.000001;
	{
		T const fovy = bksge::degrees_to_radians(45.0f);
		T const aspect = 4.0f / 3.0f;
		T const zn = 1;
		T const zf = 10;
		Matrix4x4 const m = Matrix4x4::MakePerspective(fovy, aspect, zn, zf);
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixPerspectiveFovLH(fovy, aspect, zn, zf));
#else
		Matrix4x4 const expected
		{
			Vector4{ 1.81066006185294, 0,                   0,                  0 },
			Vector4{ 0,                2.4142134877530865,  0,                  0 },
			Vector4{ 0,                0,                   1.111111164093017,  1 },
			Vector4{ 0,                0,                  -1.111111164093017,  0 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		T const fovy = bksge::degrees_to_radians(60.0f);
		T const aspect = 16.0f / 9.0f;
		T const zn = 0.5f;
		T const zf = 5000;
		Matrix4x4 const m = Matrix4x4::MakePerspective(fovy, aspect, zn, zf);
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixPerspectiveFovLH(fovy, aspect, zn, zf));
#else
		Matrix4x4 const expected
		{
			Vector4{ 0.97427853921501106, 0,                   0,               0 },
			Vector4{ 0,                   1.7320507492870254,  0,               0 },
			Vector4{ 0,                   0,                   1.0001000165939, 1 },
			Vector4{ 0,                   0,                  -0.5000500082969, 0 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, MakeViewTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// XMMatrixLookAtLH と同じかどうかをテストします。

	double const error = 0.0001;
	{
		Vector3 const eye(1, 2, 3);
		Vector3 const at(4, 5, 6);
		Vector3 const up(0, 1, 0);
		Vector3 const direction = at - eye;
		Matrix4x4 const m = Matrix4x4::MakeView(eye, direction, up);
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixLookAtLH(
			ToXMVECTOR(eye),
			ToXMVECTOR(at),
			ToXMVECTOR(up)));
#else
		Matrix4x4 const expected
		{
			Vector4{  0.707107f, -0.408248f,  0.57735f, 0 },
			Vector4{  0,          0.816497f,  0.57735f, 0 },
			Vector4{ -0.707107f, -0.408248f,  0.57735f, 0 },
			Vector4{  1.41421f,   0,         -3.4641f,  1 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		Vector3 const eye(12, 7, -1);
		Vector3 const at(-5, 41, 1);
		Vector3 const up(0, 0, 1);
		Vector3 const direction = at - eye;
		Matrix4x4 const m = Matrix4x4::MakeView(eye, direction, up);
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixLookAtLH(
			ToXMVECTOR(eye),
			ToXMVECTOR(at),
			ToXMVECTOR(up)));
#else
		Matrix4x4 const expected
		{
			Vector4{  -0.894427f,  0.0234969f, -0.446596f,  0 },
			Vector4{  -0.447214f, -0.0469938f,  0.893192f,  0 },
			Vector4{  -0,          0.998619f,   0.0525407f, 0 },
			Vector4{  13.8636f,    1.04561f,   -0.840651f,  1 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, MakeLookAtTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// XMMatrixLookAtLH と同じかどうかをテストします。

	double const error = 0.0001;
	{
		Vector3 const eye(1, 2, 3);
		Vector3 const at(4, 5, 6);
		Vector3 const up(0, 1, 0);
		Matrix4x4 const m = Matrix4x4::MakeLookAt(eye, at, up);
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixLookAtLH(
			ToXMVECTOR(eye),
			ToXMVECTOR(at),
			ToXMVECTOR(up)));
#else
		Matrix4x4 const expected
		{
			Vector4{  0.707107f, -0.408248f,  0.57735f, 0 },
			Vector4{  0,          0.816497f,  0.57735f, 0 },
			Vector4{ -0.707107f, -0.408248f,  0.57735f, 0 },
			Vector4{  1.41421f,   0,         -3.4641f,  1 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		Vector3 const eye(12, 7, -1);
		Vector3 const at(-5, 41, 1);
		Vector3 const up(0, 0, 1);
		Matrix4x4 const m = Matrix4x4::MakeLookAt(eye, at, up);
#if defined(BKSGE_DXMATH_TEST)
		Matrix4x4 const expected = ToMatrix4x4<T>(XMMatrixLookAtLH(
			ToXMVECTOR(eye),
			ToXMVECTOR(at),
			ToXMVECTOR(up)));
#else
		Matrix4x4 const expected
		{
			Vector4{  -0.894427f,  0.0234969f, -0.446596f,  0 },
			Vector4{  -0.447214f, -0.0469938f,  0.893192f,  0 },
			Vector4{  -0,          0.998619f,   0.0525407f, 0 },
			Vector4{  13.8636f,    1.04561f,   -0.840651f,  1 },
		};
#endif

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
}

TYPED_TEST(MathMatrix4x4Test, MakeViewportTest)
{
	using Matrix4x4 = bksge::math::Matrix4x4<TypeParam>;
	using Vector4 = bksge::math::Vector4<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 mat =
			Matrix4x4::MakeViewport(0, 0, 640, 480);
		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected
		{
			Vector4{ 320,    0, 0, 0 },
			Vector4{   0, -240, 0, 0 },
			Vector4{   0,    0, 1, 0 },
			Vector4{ 320,  240, 0, 1 },
		};
		BKSGE_CONSTEXPR_EXPECT_EQ(expected, mat);
	}
	{
		const Matrix4x4 mat =
			Matrix4x4::MakeViewport(10, 20, 800, 600);
		const Matrix4x4 expected
		{
			Vector4{ 400,    0, 0, 0 },
			Vector4{   0, -300, 0, 0 },
			Vector4{   0,    0, 1, 0 },
			Vector4{ 410,  320, 0, 1 },
		};
		EXPECT_EQ(expected, mat);
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, ComposeTest)
{
	using Matrix4x4  = bksge::math::Matrix4x4<TypeParam>;
	using Matrix3x3  = bksge::math::Matrix3x3<TypeParam>;
	using Vector3    = bksge::math::Vector3<TypeParam>;
	using Scale3     = bksge::math::Scale3<TypeParam>;
	using Quaternion = bksge::math::Quaternion<TypeParam>;

	// MakeScale() * MakeRotation() * MakeTranslation() と同じ値になるかどうかテスト

	BKSGE_CONSTEXPR_OR_CONST double error = 0.00001;

	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 trans(1, 2, 3);
		BKSGE_CONSTEXPR_OR_CONST Scale3 scale(4, 5, 6);
		BKSGE_CONSTEXPR_OR_CONST Matrix3x3 rotation = Matrix3x3::Identity();
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x4::Compose(trans, scale, rotation);

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::Identity() *
			Matrix4x4::MakeTranslation(trans);

		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 trans(7, 8, 9);
		BKSGE_CONSTEXPR_OR_CONST Scale3 scale(10, 11, 12);
		BKSGE_CONSTEXPR_OR_CONST Quaternion rotation = Quaternion::Identity();
		BKSGE_CONSTEXPR_OR_CONST auto m = Matrix4x4::Compose(trans, scale, rotation);

		BKSGE_CONSTEXPR_OR_CONST Matrix4x4 expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::Identity() *
			Matrix4x4::MakeTranslation(trans);

		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		BKSGE_CONSTEXPR_EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		const Vector3 trans {10, 20, 30};
		const Scale3 scale {2, 3, 4};
		const auto angle = bksge::degrees_to_radians(90);
		const auto rotation = Quaternion::MakeRotationX(angle);
		const auto m = Matrix4x4::Compose(trans, scale, rotation);

		const Matrix4x4 expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::MakeRotationX(angle) *
			Matrix4x4::MakeTranslation(trans);

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		const Vector3 trans(-2, 1.5, 42);
		const Scale3 scale(2, -1, 2.5);
		const auto angle = bksge::degrees_to_radians(120);
		const auto rotation = Matrix3x3::MakeRotationY(angle);
		const auto m = Matrix4x4::Compose(trans, scale, rotation);

		const Matrix4x4 expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::MakeRotationY(angle) *
			Matrix4x4::MakeTranslation(trans);

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		const Vector3 trans(10, -7.5, -1);
		const Scale3 scale(3, 3.5, 4);
		const auto angle = bksge::degrees_to_radians(45);
		const auto rotation = Quaternion::MakeRotationZ(angle);
		const auto m = Matrix4x4::Compose(trans, scale, rotation);

		const Matrix4x4 expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::MakeRotationZ(angle) *
			Matrix4x4::MakeTranslation(trans);

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
	{
		const Vector3 trans(-1, 2, 3);
		const Scale3 scale(4, -5, 6);
		const Vector3 axis(7, 8, -9);
		const auto angle = bksge::degrees_to_radians(30);
		const auto rotation = Quaternion::MakeRotation(axis, angle);
		const auto m = Matrix4x4::Compose(trans, scale, rotation);

		const Matrix4x4 expected =
			Matrix4x4::MakeScale(scale) *
			Matrix4x4::MakeRotation(axis, angle) *
			Matrix4x4::MakeTranslation(trans);

		EXPECT_NEAR((double)expected[0][0], (double)m[0][0], error);
		EXPECT_NEAR((double)expected[0][1], (double)m[0][1], error);
		EXPECT_NEAR((double)expected[0][2], (double)m[0][2], error);
		EXPECT_NEAR((double)expected[0][3], (double)m[0][3], error);
		EXPECT_NEAR((double)expected[1][0], (double)m[1][0], error);
		EXPECT_NEAR((double)expected[1][1], (double)m[1][1], error);
		EXPECT_NEAR((double)expected[1][2], (double)m[1][2], error);
		EXPECT_NEAR((double)expected[1][3], (double)m[1][3], error);
		EXPECT_NEAR((double)expected[2][0], (double)m[2][0], error);
		EXPECT_NEAR((double)expected[2][1], (double)m[2][1], error);
		EXPECT_NEAR((double)expected[2][2], (double)m[2][2], error);
		EXPECT_NEAR((double)expected[2][3], (double)m[2][3], error);
		EXPECT_NEAR((double)expected[3][0], (double)m[3][0], error);
		EXPECT_NEAR((double)expected[3][1], (double)m[3][1], error);
		EXPECT_NEAR((double)expected[3][2], (double)m[3][2], error);
		EXPECT_NEAR((double)expected[3][3], (double)m[3][3], error);
	}
}

TYPED_TEST(MathMatrix4x4FloatTest, DecomposeTest)
{
	using Matrix4x4 = bksge::math::Matrix4x4<TypeParam>;
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;
	using Vector3 = bksge::math::Vector3<TypeParam>;
	using Scale3 = bksge::math::Scale3<TypeParam>;

	{
		const Vector3 trans_expected(-42, 0, 10.5);
		const Scale3 scale_expected(4, 2.5, 1);
		const Matrix3x3 rotation_expected = Matrix3x3::MakeRotationX(bksge::degrees_to_radians(180));
		const Matrix4x4 m = Matrix4x4::Compose(trans_expected, scale_expected, rotation_expected);

		auto const t = Matrix4x4::Decompose(m);
		auto const trans    = bksge::get<0>(t);
		auto const scale    = bksge::get<1>(t);
		auto const rotation = bksge::get<2>(t);

		EXPECT_EQ(trans_expected,    trans);
		EXPECT_EQ(scale_expected,    scale);
		EXPECT_EQ(rotation_expected, rotation);
	}
	{
		const Vector3 trans_expected(10, 20, 30);
		const Scale3 scale_expected(2, 3, 4);
		const Matrix3x3 rotation_expected = Matrix3x3::MakeRotationY(bksge::degrees_to_radians(90));
		const Matrix4x4 m =
			Matrix4x4::MakeScale(scale_expected) *
			bksge::math::Resized<4, 4>(rotation_expected) *
			Matrix4x4::MakeTranslation(trans_expected);

		Vector3 trans;
		Scale3 scale;
		Matrix3x3 rotation;
		bksge::tie(trans, scale, rotation) = Matrix4x4::Decompose(m);

		EXPECT_EQ(trans_expected,    trans);
		EXPECT_EQ(scale_expected,    scale);
		EXPECT_EQ(rotation_expected, rotation);
	}
}

TYPED_TEST(MathMatrix4x4Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	Matrix4x4 const v
	{
		Vector4{11, 12, 13, 14},
		Vector4{21, 22, 23, 24},
		Vector4{31, 32, 33, 34},
		Vector4{41, 42, 43, 44},
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

TYPED_TEST(MathMatrix4x4Test, HashTest)
{
	using T = TypeParam;
	using Matrix4x4 = bksge::math::Matrix4x4<T>;
	using Vector4 = bksge::math::Vector4<T>;

	std::hash<Matrix4x4> h;

	Matrix4x4 const m1
	{
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 0, 0},
	};

	Matrix4x4 const m2
	{
		Vector4{1, 0, 0, 0},
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 0, 0},
	};

	Matrix4x4 const m3
	{
		Vector4{0, 0, 0, 0},
		Vector4{0, 1, 0, 0},
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 0, 0},
	};

	Matrix4x4 const m4
	{
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 1, 0},
		Vector4{0, 0, 0, 0},
	};

	Matrix4x4 const m5
	{
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 0, 0},
		Vector4{0, 0, 0, 1},
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

}	// namespace matrix4x4_test

}	// namespace bksge_math_test
