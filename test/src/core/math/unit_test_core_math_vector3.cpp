﻿/**
 *	@file	unit_test_core_math_vector3.cpp
 *
 *	@brief	Vector3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
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
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <functional>
#include <vector>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace vector3_test
{

using Vector3f = bksge::math::Vector3<float>;
using Vector3i = bksge::math::Vector3<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathVector3Test : public ::testing::Test {};
template <typename T>
class MathVector3FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathVector3Test, MathTestTypes);
TYPED_TEST_SUITE(MathVector3FloatTest, MathFloatTestTypes);

TYPED_TEST(MathVector3Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(sizeof(Vector3) == sizeof(T) * 3, "");
	static_assert(bksge::is_default_constructible<Vector3>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Vector3>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Vector3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
}

TYPED_TEST(MathVector3Test, ValueConstructTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(!bksge::is_constructible<Vector3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Vector3, T, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Vector3, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Vector3, T, T>::value, "");
	static_assert(!bksge::is_constructible<Vector3, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector3, T, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Vector3, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector3, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector3, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector3, T, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Vector3, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector3, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector3, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v(1, 2, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v{4, 5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v = {7, 8, 9};
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(9, v[2]);
	}
}

TYPED_TEST(MathVector3Test, CopyConstructTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(bksge::is_constructible<Vector3,  Vector3  const&>::value, "");
	static_assert(bksge::is_constructible<Vector3,  Vector3i const&>::value, "");
	static_assert(bksge::is_constructible<Vector3,  Vector3f const&>::value, "");
	static_assert(bksge::is_constructible<Vector3i, Vector3  const&>::value, "");
	static_assert(bksge::is_constructible<Vector3i, Vector3i const&>::value, "");
	static_assert(bksge::is_constructible<Vector3i, Vector3f const&>::value, "");
	static_assert(bksge::is_constructible<Vector3f, Vector3  const&>::value, "");
	static_assert(bksge::is_constructible<Vector3f, Vector3i const&>::value, "");
	static_assert(bksge::is_constructible<Vector3f, Vector3f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Vector3,  Vector3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector3,  Vector3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector3,  Vector3f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector3i, Vector3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector3i, Vector3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector3i, Vector3f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector3f, Vector3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector3f, Vector3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector3f, Vector3f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Vector3,  Vector3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector3,  Vector3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector3,  Vector3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector3i, Vector3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector3i, Vector3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector3i, Vector3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector3f, Vector3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector3f, Vector3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector3f, Vector3f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Vector3  v1{1, 2, 3};
	BKSGE_CONSTEXPR_OR_CONST Vector3  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Vector3i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Vector3f v4{v2};

	BKSGE_CONSTEXPR_EXPECT_EQ(1, v1[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v1[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v1[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v3[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v3[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v3[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v4[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v4[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v4[2]);
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

TYPED_TEST(MathVector3Test, CopyAssignTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	Vector3 v1(0, 1, 2);
	Vector3 v2(3, 4, 5);
	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(2, v1[2]);
	EXPECT_EQ(3, v2[0]);
	EXPECT_EQ(4, v2[1]);
	EXPECT_EQ(5, v2[2]);

	v1 = Vector3(6, -7, 8);
	v2 = Vector3i(-9, 10, 11);
	EXPECT_EQ( 6, v1[0]);
	EXPECT_EQ(-7, v1[1]);
	EXPECT_EQ( 8, v1[2]);
	EXPECT_EQ(-9, v2[0]);
	EXPECT_EQ(10, v2[1]);
	EXPECT_EQ(11, v2[2]);

	// 自己代入
	v1 = v1;
	v2 = v2;
	EXPECT_EQ( 6, v1[0]);
	EXPECT_EQ(-7, v1[1]);
	EXPECT_EQ( 8, v1[2]);
	EXPECT_EQ(-9, v2[0]);
	EXPECT_EQ(10, v2[1]);
	EXPECT_EQ(11, v2[2]);

	// 多重代入
	v1 = v2 = Vector3f(4, 5, 6);
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(5, v1[1]);
	EXPECT_EQ(6, v1[2]);
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
	EXPECT_EQ(6, v2[2]);
}

BKSGE_WARNING_POP()

TYPED_TEST(MathVector3Test, IndexAccessTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Vector3 v{1, 2, 3};
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);

		v[0] = -3;
		v[1] =  4;
		v[2] = -5;

		EXPECT_EQ(-3, v[0]);
		EXPECT_EQ( 4, v[1]);
		EXPECT_EQ(-5, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
	}
}

TYPED_TEST(MathVector3Test, AtTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Vector3 v{1, 2, 3};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);

		v.at(0) = -3;
		v.at(1) =  4;
		v.at(2) = -5;

		EXPECT_EQ(-3, v.at(0));
		EXPECT_EQ( 4, v.at(1));
		EXPECT_EQ(-5, v.at(2));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.at(2));
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
}

TYPED_TEST(MathVector3Test, DataTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Vector3 v{1, 2, 3};
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, *p);
		*p = 5;
		++p;
		EXPECT_EQ(2, *p);
		++p;
		EXPECT_EQ(3, *p);
		*p = 6;

		EXPECT_EQ(Vector3(5, 2, 6), v);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Vector3 v{1, 2, 3};
		BKSGE_STATIC_CONSTEXPR auto p = v.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, p[2]);
	}
#endif
}

TYPED_TEST(MathVector3Test, IteratorTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	// begin, end (non const)
	{
		Vector3 v{1, 2, 3};
		auto it = v.begin();
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(1, *it);
		*it++ = 5;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(2, *it);
		*++it = 6;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(6, *it);
		it++;
		EXPECT_TRUE(it == v.end());

		EXPECT_EQ(Vector3(5, 2, 6), v);
	}
	// begin, end (const)
	{
		const Vector3 v{1, 2, 3};
		auto it = v.begin();
		EXPECT_TRUE(it != v.end());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(3, it[2]);

		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(3, *++it);
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(2, *--it);
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(2, *it--);
		EXPECT_TRUE(it != v.end());
		it += 2;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(3, *it);
		it -= 2;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(1, *it);
		it += 3;
		EXPECT_TRUE(it == v.end());
	}
	// cbegin, cend
	{
		const Vector3 v{1, 2, 3};
		auto it = v.cbegin();
		EXPECT_TRUE(it != v.cend());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(3, it[2]);

		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(3, *++it);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it == v.cend());
	}
#if !defined(BKSGE_GCC)
	// begin, end (constexpr)
	{
		BKSGE_STATIC_CONSTEXPR Vector3 v{1, 2, 3};
		BKSGE_CONSTEXPR_OR_CONST auto it = v.begin();
		BKSGE_CONSTEXPR_EXPECT_TRUE(it != v.end());

		BKSGE_CONSTEXPR_EXPECT_EQ(1, it[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, it[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, it[2]);

		BKSGE_CONSTEXPR_EXPECT_EQ(1, *it);
		BKSGE_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it2 != v.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(2, *it2);
		BKSGE_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it3 != v.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(3, *it3);
		BKSGE_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, *it4);
		BKSGE_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 == v.end());
	}
#endif
}

TYPED_TEST(MathVector3Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	// rbegin, rend (non const)
	{
		Vector3 v{1, 2, 3};
		auto it = v.rbegin();
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(3, *it);
		*it++ = 5;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *it);
		*++it = 6;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(6, *it);
		it++;
		EXPECT_TRUE(it == v.rend());

		EXPECT_EQ(6, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(5, v[2]);
	}
	// rbegin, rend (const)
	{
		const Vector3 v{1, 2, 3};
		auto it = v.rbegin();
		EXPECT_TRUE(it != v.rend());

		EXPECT_EQ(3, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(1, it[2]);

		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(1, *++it);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *--it);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *it--);
		EXPECT_TRUE(it != v.rend());
		it += 2;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(1, *it);
		it -= 2;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(3, *it);
		it += 3;
		EXPECT_TRUE(it == v.rend());
	}
	// crbegin, crend
	{
		const Vector3 v{1, 2, 3};
		auto it = v.crbegin();
		EXPECT_TRUE(it != v.crend());

		EXPECT_EQ(3, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(1, it[2]);

		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(1, *++it);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == v.crend());
	}
#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201603) && !defined(BKSGE_GCC)
	// rbegin, rend (constexpr)
	{
		BKSGE_CXX17_STATIC_CONSTEXPR Vector3 v{1, 2, 3};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = v.rbegin();
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it != v.rend());

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, it[0]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, it[1]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, it[2]);

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, *it);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it2 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it2);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it3 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, *it3);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it4);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 == v.rend());
	}
#endif
}

TYPED_TEST(MathVector3Test, EmptyTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	Vector3 v1{};
	const           Vector3 v2{};
	BKSGE_CONSTEXPR Vector3 v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathVector3Test, SizeTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	Vector3 v1{};
	const           Vector3 v2{};
	BKSGE_CONSTEXPR Vector3 v3{};
	EXPECT_EQ(3u, v1.size());
	EXPECT_EQ(3u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, v3.size());
}

TYPED_TEST(MathVector3Test, MaxSizeTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	Vector3 v1{};
	const           Vector3 v2{};
	BKSGE_CONSTEXPR Vector3 v3{};
	EXPECT_EQ(3u, v1.max_size());
	EXPECT_EQ(3u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, v3.max_size());
}

TYPED_TEST(MathVector3Test, NameAccessTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Vector3 v{1, 2, 3};
		EXPECT_EQ(1, v.x());
		EXPECT_EQ(2, v.y());
		EXPECT_EQ(3, v.z());

		v.x() = -3;
		v.y() =  4;
		v.z() = -5;

		EXPECT_EQ(-3, v.x());
		EXPECT_EQ( 4, v.y());
		EXPECT_EQ(-5, v.z());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.x());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.y());
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.z());
	}
}

TYPED_TEST(MathVector3Test, SwizzleTest)
{
	using T = TypeParam;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Vector3 v(1, 2, 3);

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 1), v.xxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 2), v.xxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 3), v.xxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 1), v.xxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 2), v.xxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 3), v.xxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 1), v.xxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 2), v.xxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 3), v.xxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 1), v.xyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 2), v.xyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 3), v.xyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 1), v.xyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 2), v.xyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 3), v.xyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 1), v.xyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 2), v.xyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 3), v.xyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 1), v.xzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 2), v.xzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 3), v.xzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 1), v.xzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 2), v.xzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 3), v.xzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 1), v.xzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 2), v.xzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 3), v.xzzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 1), v.yxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 2), v.yxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 3), v.yxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 1), v.yxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 2), v.yxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 3), v.yxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 1), v.yxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 2), v.yxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 3), v.yxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 1), v.yyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 2), v.yyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 3), v.yyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 1), v.yyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 2), v.yyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 3), v.yyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 1), v.yyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 2), v.yyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 3), v.yyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 1), v.yzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 2), v.yzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 3), v.yzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 1), v.yzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 2), v.yzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 3), v.yzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 1), v.yzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 2), v.yzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 3), v.yzzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 1), v.zxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 2), v.zxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 3), v.zxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 1), v.zxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 2), v.zxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 3), v.zxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 1), v.zxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 2), v.zxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 3), v.zxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 1), v.zyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 2), v.zyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 3), v.zyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 1), v.zyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 2), v.zyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 3), v.zyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 1), v.zyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 2), v.zyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 3), v.zyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 1), v.zzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 2), v.zzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 3), v.zzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 1), v.zzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 2), v.zzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 3), v.zzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 1), v.zzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 2), v.zzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 3), v.zzzz());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 1), v.xxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 2), v.xxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 3), v.xxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 1), v.xyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 2), v.xyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 3), v.xyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 1), v.xzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 2), v.xzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 3), v.xzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 1), v.yxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 2), v.yxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 3), v.yxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 1), v.yyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 2), v.yyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 3), v.yyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 1), v.yzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 2), v.yzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 3), v.yzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 1), v.zxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 2), v.zxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 3), v.zxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 1), v.zyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 2), v.zyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 3), v.zyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 1), v.zzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 2), v.zzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 3), v.zzz());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 1), v.xx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 2), v.xy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 3), v.xz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 1), v.yx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 2), v.yy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 3), v.yz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 1), v.zx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 2), v.zy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 3), v.zz());
}

TYPED_TEST(MathVector3Test, ZeroTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = Vector3::Zero();
		static_assert(bksge::is_same<decltype(v), const Vector3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(0, 0, 0), v);
	}
	{
		const auto v = Vector3::Zero();
		static_assert(bksge::is_same<decltype(v), const Vector3>::value, "");
		EXPECT_EQ(Vector3(0, 0, 0), v);
	}
}

TYPED_TEST(MathVector3Test, SwapTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	Vector3 v1{11, 12, 13};
	Vector3 v2{21, 22, 23};

	EXPECT_EQ(Vector3(11, 12, 13), v1);
	EXPECT_EQ(Vector3(21, 22, 23), v2);

	v1.swap(v2);

	EXPECT_EQ(Vector3(21, 22, 23), v1);
	EXPECT_EQ(Vector3(11, 12, 13), v2);

	swap(v1, v2);

	EXPECT_EQ(Vector3(11, 12, 13), v1);
	EXPECT_EQ(Vector3(21, 22, 23), v2);
}

TYPED_TEST(MathVector3Test, PlusMinusTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Vector3 v1(-1, 2, -3);
		Vector3 v3 = +v1;
		Vector3 v4 = -v1;

		EXPECT_EQ(-1, v3[0]);
		EXPECT_EQ( 2, v3[1]);
		EXPECT_EQ(-3, v3[2]);
		EXPECT_EQ( 1, v4[0]);
		EXPECT_EQ(-2, v4[1]);
		EXPECT_EQ( 3, v4[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v2(3, -4, 5);
		BKSGE_CONSTEXPR_OR_CONST Vector3 v5 = +v2;
		BKSGE_CONSTEXPR_OR_CONST Vector3 v6 = -v2;

		BKSGE_CONSTEXPR_EXPECT_EQ( 3, v5[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-4, v5[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 5, v5[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-3, v6[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v6[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-5, v6[2]);
	}
}

TYPED_TEST(MathVector3Test, AddTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	// Vector3 += Vector3
	{
		Vector3 v;
		Vector3 t = (v += Vector3(2, 3, -4));
		EXPECT_EQ(Vector3(2, 3, -4), v);
		EXPECT_EQ(t, v);
	}

	// Vector3 + Vector3 -> Vector3
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 t =
			Vector3(-3, 4, 5) + Vector3(0, 2, -1);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-3, 6, 4), t);
	}
}

TYPED_TEST(MathVector3Test, SubTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	// Vector3 -= Vector3
	{
		Vector3 v;
		Vector3 t = (v -= Vector3(2, 3, -4));
		EXPECT_EQ(Vector3(-2, -3, 4), v);
		EXPECT_EQ(t, v);
	}

	// Vector3 - Vector3 -> Vector3
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 t =
			Vector3(-3, 4, 5) - Vector3(0, 2, -1);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-3, 2, 6), t);
	}
}

TYPED_TEST(MathVector3Test, MulScalarTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	// Vector3 *= スカラー
	{
		Vector3 v(2, 3, 4);
		{
			Vector3 t = (v *= 4);
			EXPECT_EQ(Vector3(8, 12, 16), v);
			EXPECT_EQ(t, v);
		}
		{
			Vector3 t = (v *= 0.5);
			EXPECT_EQ(Vector3(4, 6, 8), v);
			EXPECT_EQ(t, v);
		}
	}

	// Vector3 * スカラー -> Vector3
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 t = Vector3(-3, 42, 5) * -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(12, -168, -20), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 t = Vector3(4, 6, 2) * 2.5;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(10, 15, 5), t);
	}
	// スカラー * Vector3 -> Vector3
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 t = 5 * Vector3(7, -8, 9);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(35, -40, 45), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 t = -1.5 * Vector3(4, -6, -2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-6, 9, 3), t);
	}
}

TYPED_TEST(MathVector3Test, DivScalarTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	// Vector3 /= スカラー
	{
		Vector3 v(2, 4, 6);
		{
			Vector3 t = (v /= 2);
			EXPECT_EQ(Vector3(1, 2, 3), v);
			EXPECT_EQ(t, v);
		}
		{
			Vector3 t = (v /= 0.5);
			EXPECT_EQ(Vector3(2, 4, 6), v);
			EXPECT_EQ(t, v);
		}
	}

	// Vector3 / スカラー -> Vector3
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 t = Vector3(-4, 8, -12) / -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, -2, 3), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 t = Vector3(-4, 8, -12) / 0.25;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-16, 32, -48), t);
	}
}

TYPED_TEST(MathVector3Test, CompareTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_OR_CONST Vector3 v1(1, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST Vector3 v2(1, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST Vector3 v3(2, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST Vector3 v4(1, 0, 3);
	BKSGE_CONSTEXPR_OR_CONST Vector3 v5(1, 2, 2);

	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v4);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v5);

	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v4);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v5);
}

TYPED_TEST(MathVector3Test, OutputStreamTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Vector3 const v{1, -2, 3};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2, 3 }", ss.str());
	}
	{
		Vector3 const v{-10, 9, 8};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9, 8 }", ss.str());
	}
}

TYPED_TEST(MathVector3Test, TupleElementTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(bksge::is_same<typename bksge::tuple_element<0, Vector3>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<1, Vector3>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<2, Vector3>::type, T>::value, "");
}

TYPED_TEST(MathVector3Test, TupleGetTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	{
		Vector3 v{1, 2, 3};

		EXPECT_EQ(1, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));

		bksge::get<0>(v) = 5;

		EXPECT_EQ(Vector3(5, 2, 3), v);
		EXPECT_EQ(5, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v{1, 2, 3};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::get<2>(v));
	}
}

TYPED_TEST(MathVector3Test, TupleSizeTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(bksge::tuple_size<Vector3>::value == 3, "");
}

TYPED_TEST(MathVector3Test, DotTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 0), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 0), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 0), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 0), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 0), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 0), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 0), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 1, 0, 0), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector3( 1, 0, 0), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector3( 1, 0, 0), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 1, 0, 0), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 1, 0, 0), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 1, 0, 0), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 1, 0, 0), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3(-1, 0, 0), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector3(-1, 0, 0), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector3(-1, 0, 0), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3(-1, 0, 0), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3(-1, 0, 0), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3(-1, 0, 0), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3(-1, 0, 0), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 1, 0), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 1, 0), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 1, 0), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector3( 0, 1, 0), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector3( 0, 1, 0), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 1, 0), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 1, 0), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0,-1, 0), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0,-1, 0), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0,-1, 0), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector3( 0,-1, 0), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector3( 0,-1, 0), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0,-1, 0), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0,-1, 0), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 1), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 1), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 1), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 1), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0, 1), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector3( 0, 0, 1), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector3( 0, 0, 1), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0,-1), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0,-1), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0,-1), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0,-1), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector3( 0, 0,-1), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector3( 0, 0,-1), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector3( 0, 0,-1), Vector3( 0, 0,-1)));
}

TYPED_TEST(MathVector3Test, CrossTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_OR_CONST auto t = Cross(Vector3(0, 0, 0), Vector3(0, 0, 0));
	static_assert(bksge::is_same<decltype(t), const Vector3>::value, "");
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), t);
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0, 0), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0, 0), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0, 0), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0, 0), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0, 0), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0, 0), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 1, 0, 0), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 1, 0, 0), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 1, 0, 0), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 1), Cross(Vector3( 1, 0, 0), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0,-1), Cross(Vector3( 1, 0, 0), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0,-1, 0), Cross(Vector3( 1, 0, 0), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 1, 0), Cross(Vector3( 1, 0, 0), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3(-1, 0, 0), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3(-1, 0, 0), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3(-1, 0, 0), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0,-1), Cross(Vector3(-1, 0, 0), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 1), Cross(Vector3(-1, 0, 0), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 1, 0), Cross(Vector3(-1, 0, 0), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0,-1, 0), Cross(Vector3(-1, 0, 0), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 1, 0), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0,-1), Cross(Vector3( 0, 1, 0), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 1), Cross(Vector3( 0, 1, 0), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 1, 0), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 1, 0), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 1, 0, 0), Cross(Vector3( 0, 1, 0), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-1, 0, 0), Cross(Vector3( 0, 1, 0), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0,-1, 0), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 1), Cross(Vector3( 0,-1, 0), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0,-1), Cross(Vector3( 0,-1, 0), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0,-1, 0), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0,-1, 0), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-1, 0, 0), Cross(Vector3( 0,-1, 0), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 1, 0, 0), Cross(Vector3( 0,-1, 0), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0, 1), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 1, 0), Cross(Vector3( 0, 0, 1), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0,-1, 0), Cross(Vector3( 0, 0, 1), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-1, 0, 0), Cross(Vector3( 0, 0, 1), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 1, 0, 0), Cross(Vector3( 0, 0, 1), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0, 1), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0, 1), Vector3( 0, 0,-1)));

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0,-1), Vector3( 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0,-1, 0), Cross(Vector3( 0, 0,-1), Vector3( 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 1, 0), Cross(Vector3( 0, 0,-1), Vector3(-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 1, 0, 0), Cross(Vector3( 0, 0,-1), Vector3( 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-1, 0, 0), Cross(Vector3( 0, 0,-1), Vector3( 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0,-1), Vector3( 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Cross(Vector3( 0, 0,-1), Vector3( 0, 0,-1)));
}

TYPED_TEST(MathVector3Test, SquaredLengthTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ(  0, SquaredLength(Vector3(0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  9, SquaredLength(Vector3(3, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 16, SquaredLength(Vector3(0, 4, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 25, SquaredLength(Vector3(0, 0,-5)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 14, SquaredLength(Vector3(1, 2, 3)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 14, SquaredLength(Vector3(1, 2,-3)));
	BKSGE_CONSTEXPR_EXPECT_EQ(105, SquaredLength(Vector3(4,-8, 5)));
}

TYPED_TEST(MathVector3Test, LengthTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	const double error = 0.000001;

	EXPECT_EQ(0, Length(Vector3(0, 0, 0)));
	EXPECT_EQ(3, Length(Vector3(3, 0, 0)));
	EXPECT_EQ(4, Length(Vector3(0, 4, 0)));
	EXPECT_EQ(5, Length(Vector3(0, 0,-5)));
	EXPECT_NEAR(3.74165738677, (double)Length(Vector3(1, 2, 3)), error);
	EXPECT_NEAR(3.74165738677, (double)Length(Vector3(1, 2,-3)), error);
	EXPECT_NEAR(10.246950766,  (double)Length(Vector3(4,-8, 5)), error);
}

TYPED_TEST(MathVector3FloatTest, NormalizedTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	EXPECT_EQ(Vector3( 0, 0, 0), Normalized(Vector3(  0,  0,  0)));
	EXPECT_EQ(Vector3( 1, 0, 0), Normalized(Vector3(  1,  0,  0)));
	EXPECT_EQ(Vector3(-1, 0, 0), Normalized(Vector3( -1,  0,  0)));
	EXPECT_EQ(Vector3( 1, 0, 0), Normalized(Vector3( 10,  0,  0)));
	EXPECT_EQ(Vector3(-1, 0, 0), Normalized(Vector3(-10,  0,  0)));
	EXPECT_EQ(Vector3( 0, 1, 0), Normalized(Vector3(  0,  1,  0)));
	EXPECT_EQ(Vector3( 0,-1, 0), Normalized(Vector3(  0, -1,  0)));
	EXPECT_EQ(Vector3( 0, 1, 0), Normalized(Vector3(  0,  5,  0)));
	EXPECT_EQ(Vector3( 0,-1, 0), Normalized(Vector3(  0, -5,  0)));
	EXPECT_EQ(Vector3( 0, 0, 1), Normalized(Vector3(  0,  0,  1)));
	EXPECT_EQ(Vector3( 0, 0,-1), Normalized(Vector3(  0,  0, -1)));
	EXPECT_EQ(Vector3( 0, 0, 1), Normalized(Vector3(  0,  0, 42)));
	EXPECT_EQ(Vector3( 0, 0,-1), Normalized(Vector3(  0,  0,-42)));

	const double error = 0.000001;
	{
		auto const t = Normalized(Vector3(1, 2, 3));
		EXPECT_NEAR( 0.26726124191242440, (double)t.x(), error);
		EXPECT_NEAR( 0.53452248382484879, (double)t.y(), error);
		EXPECT_NEAR( 0.80178372573727319, (double)t.z(), error);
	}
	{
		auto const t = Normalized(Vector3(-4, 5, -6));
		EXPECT_NEAR(-0.45584230583855179, (double)t.x(), error);
		EXPECT_NEAR( 0.56980288229818976, (double)t.y(), error);
		EXPECT_NEAR(-0.68376345875782762, (double)t.z(), error);
	}
}

TYPED_TEST(MathVector3FloatTest, LerpTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0.0,  0.0,  0.0), Lerp(Vector3(0, 0, 0), Vector3(10, 20, 30), TypeParam(0.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 2.5,  5.0,  7.5), Lerp(Vector3(0, 0, 0), Vector3(10, 20, 30), TypeParam(0.25)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 5.0, 10.0, 15.0), Lerp(Vector3(0, 0, 0), Vector3(10, 20, 30), TypeParam(0.50)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 7.5, 15.0, 22.5), Lerp(Vector3(0, 0, 0), Vector3(10, 20, 30), TypeParam(0.75)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(10.0, 20.0, 30.0), Lerp(Vector3(0, 0, 0), Vector3(10, 20, 30), TypeParam(1.00)));
}

TYPED_TEST(MathVector3Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::Vector3<T> const v { 1, 2, -3 };

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

TYPED_TEST(MathVector3Test, HashTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	std::hash<Vector3> h;

	Vector3 const c1(1, 2, 3);
	Vector3 const c2(2, 2, 3);
	Vector3 const c3(1, 0, 3);
	Vector3 const c4(1, 2, 2);

	bksge::vector<bksge::size_t> v;
	v.push_back(h(c1));
	v.push_back(h(c2));
	v.push_back(h(c3));
	v.push_back(h(c4));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(c1));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace vector3_test

}	// namespace bksge_math_test
