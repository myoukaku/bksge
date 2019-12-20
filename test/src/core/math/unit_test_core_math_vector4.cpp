/**
 *	@file	unit_test_core_math_vector4.cpp
 *
 *	@brief	Vector4 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace vector4_test
{

using Vector4f = bksge::Vector4<float>;
using Vector4i = bksge::Vector4<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathVector4Test : public ::testing::Test {};
template <typename T>
class MathVector4FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathVector4Test, MathTestTypes);
TYPED_TEST_SUITE(MathVector4FloatTest, MathFloatTestTypes);

TYPED_TEST(MathVector4Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	static_assert(sizeof(Vector4) == sizeof(T) * 4, "");
	static_assert(std::is_default_constructible<Vector4>::value, "");
	static_assert(std::is_nothrow_default_constructible<Vector4>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Vector4>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v={};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3]);
	}
}

TYPED_TEST(MathVector4Test, ValueConstructTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	static_assert(!std::is_constructible<Vector4, T, T, T, T, T>::value, "");
	static_assert( std::is_constructible<Vector4, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<Vector4, T, T, T>::value, "");
	static_assert(!std::is_constructible<Vector4, T, T>::value, "");
	static_assert(!std::is_constructible<Vector4, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Vector4, T, T, T, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<Vector4, T, T, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Vector4, T, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Vector4, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Vector4, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector4, T, T, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Vector4, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector4, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector4, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector4, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v(1, 2, 3, 4);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v = {9, 10, 11, 12};
		BKSGE_CONSTEXPR_EXPECT_EQ(9, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3]);
	}
}

TYPED_TEST(MathVector4Test, CopyConstructTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	static_assert(std::is_constructible<Vector4,  Vector4  const&>::value, "");
	static_assert(std::is_constructible<Vector4,  Vector4i const&>::value, "");
	static_assert(std::is_constructible<Vector4,  Vector4f const&>::value, "");
	static_assert(std::is_constructible<Vector4i, Vector4  const&>::value, "");
	static_assert(std::is_constructible<Vector4i, Vector4i const&>::value, "");
	static_assert(std::is_constructible<Vector4i, Vector4f const&>::value, "");
	static_assert(std::is_constructible<Vector4f, Vector4  const&>::value, "");
	static_assert(std::is_constructible<Vector4f, Vector4i const&>::value, "");
	static_assert(std::is_constructible<Vector4f, Vector4f const&>::value, "");

	static_assert(std::is_nothrow_constructible<Vector4,  Vector4  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Vector4,  Vector4i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Vector4,  Vector4f const&>::value, "");
	static_assert(std::is_nothrow_constructible<Vector4i, Vector4  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Vector4i, Vector4i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Vector4i, Vector4f const&>::value, "");
	static_assert(std::is_nothrow_constructible<Vector4f, Vector4  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Vector4f, Vector4i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Vector4f, Vector4f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Vector4,  Vector4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector4,  Vector4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector4,  Vector4f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector4i, Vector4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector4i, Vector4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector4i, Vector4f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector4f, Vector4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector4f, Vector4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector4f, Vector4f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Vector4  v1{1, 2, 3, 4};
	BKSGE_CONSTEXPR_OR_CONST Vector4  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Vector4i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Vector4f v4{v2};

	BKSGE_CONSTEXPR_EXPECT_EQ(1, v1[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v1[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v1[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(4, v1[3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v3[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v3[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v3[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(4, v3[3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v4[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v4[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v4[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(4, v4[3]);
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

TYPED_TEST(MathVector4Test, CopyAssignTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	Vector4 v1(0, 1, 2, -2);
	Vector4 v2(3, 4, 5, 6);
	EXPECT_EQ( 0, v1[0]);
	EXPECT_EQ( 1, v1[1]);
	EXPECT_EQ( 2, v1[2]);
	EXPECT_EQ(-2, v1[3]);
	EXPECT_EQ( 3, v2[0]);
	EXPECT_EQ( 4, v2[1]);
	EXPECT_EQ( 5, v2[2]);
	EXPECT_EQ( 6, v2[3]);

	v1 = Vector4(6, -7, 8, 9);
	v2 = Vector4i(-9, 10, 11, -12);
	EXPECT_EQ(  6, v1[0]);
	EXPECT_EQ( -7, v1[1]);
	EXPECT_EQ(  8, v1[2]);
	EXPECT_EQ(  9, v1[3]);
	EXPECT_EQ( -9, v2[0]);
	EXPECT_EQ( 10, v2[1]);
	EXPECT_EQ( 11, v2[2]);
	EXPECT_EQ(-12, v2[3]);

	// 自己代入
	v1 = v1;
	v2 = v2;
	EXPECT_EQ(  6, v1[0]);
	EXPECT_EQ( -7, v1[1]);
	EXPECT_EQ(  8, v1[2]);
	EXPECT_EQ(  9, v1[3]);
	EXPECT_EQ( -9, v2[0]);
	EXPECT_EQ( 10, v2[1]);
	EXPECT_EQ( 11, v2[2]);
	EXPECT_EQ(-12, v2[3]);

	// 多重代入
	v1 = v2 = Vector4f(4, 5, 6, 7);
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(5, v1[1]);
	EXPECT_EQ(6, v1[2]);
	EXPECT_EQ(7, v1[3]);
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
	EXPECT_EQ(6, v2[2]);
	EXPECT_EQ(7, v2[3]);
}

BKSGE_WARNING_POP()

TYPED_TEST(MathVector4Test, IndexAccessTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	{
		Vector4 v{1, 2, 3, 4};
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_EQ(4, v[3]);

		v[0] = -3;
		v[1] =  4;
		v[2] = -5;
		v[3] =  6;

		EXPECT_EQ(-3, v[0]);
		EXPECT_EQ( 4, v[1]);
		EXPECT_EQ(-5, v[2]);
		EXPECT_EQ( 6, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[3]);
	}
}

TYPED_TEST(MathVector4Test, AtTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	{
		Vector4 v{1, 2, 3, 4};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
		EXPECT_EQ(4, v.at(3));
		EXPECT_THROW((void)v.at(4), std::out_of_range);

		v.at(0) = -3;
		v.at(1) =  4;
		v.at(2) = -5;
		v.at(3) =  6;

		EXPECT_EQ(-3, v.at(0));
		EXPECT_EQ( 4, v.at(1));
		EXPECT_EQ(-5, v.at(2));
		EXPECT_EQ( 6, v.at(3));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.at(2));
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.at(3));
		EXPECT_THROW((void)v.at(4), std::out_of_range);
	}
}

TYPED_TEST(MathVector4Test, DataTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	{
		Vector4 v{1, 2, 3, 4};
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, *p);
		*p = 5;
		++p;
		EXPECT_EQ(2, *p);
		++p;
		EXPECT_EQ(3, *p);
		*p = 6;
		++p;
		EXPECT_EQ(4, *p);

		EXPECT_EQ(Vector4(5, 2, 6, 4), v);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Vector4 v{1, 2, 3, 4};
		BKSGE_STATIC_CONSTEXPR auto p = v.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, p[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, p[3]);
	}
#endif
}

TYPED_TEST(MathVector4Test, IteratorTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	// begin, end (non const)
	{
		Vector4 v{1, 2, 3, 4};
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
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(4, *it);
		it++;
		EXPECT_TRUE(it == v.end());

		EXPECT_EQ(Vector4(5, 2, 6, 4), v);
	}
	// begin, end (const)
	{
		const Vector4 v{1, 2, 3, 4};
		auto it = v.begin();
		EXPECT_TRUE(it != v.end());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(3, it[2]);
		EXPECT_EQ(4, it[3]);

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
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(4, *it);
		++it;
		EXPECT_TRUE(it == v.end());
	}
	// cbegin, cend
	{
		const Vector4 v{1, 2, 3, 4};
		auto it = v.cbegin();
		EXPECT_TRUE(it != v.cend());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(3, it[2]);
		EXPECT_EQ(4, it[3]);

		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(3, *++it);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == v.cend());
	}
#if !defined(BKSGE_GCC)
	// begin, end (constexpr)
	{
		BKSGE_STATIC_CONSTEXPR Vector4 v{1, 2, 3, 4};
		BKSGE_CONSTEXPR_OR_CONST auto it = v.begin();
		BKSGE_CONSTEXPR_EXPECT_TRUE(it != v.end());

		BKSGE_CONSTEXPR_EXPECT_EQ(1, it[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, it[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, it[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, it[3]);

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
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 != v.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(4, *it5);
		BKSGE_CONSTEXPR_OR_CONST auto it6 = it5 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it6 == v.end());
	}
#endif
}

TYPED_TEST(MathVector4Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	// rbegin, rend (non const)
	{
		Vector4 v{1, 2, 3, 4};
		auto it = v.rbegin();
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(4, *it);
		*it++ = 5;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(3, *it);
		*++it = 6;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(6, *it);
		it++;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(1, *it);
		it++;
		EXPECT_TRUE(it == v.rend());

		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(6, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_EQ(5, v[3]);
	}
	// rbegin, rend (const)
	{
		const Vector4 v{1, 2, 3, 4};
		auto it = v.rbegin();
		EXPECT_TRUE(it != v.rend());

		EXPECT_EQ(4, it[0]);
		EXPECT_EQ(3, it[1]);
		EXPECT_EQ(2, it[2]);
		EXPECT_EQ(1, it[3]);

		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *++it);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(3, *--it);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(3, *it--);
		EXPECT_TRUE(it != v.rend());
		it += 2;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *it);
		it -= 2;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(4, *it);
		it += 3;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_TRUE(it == v.rend());
	}
	// crbegin, crend
	{
		const Vector4 v{1, 2, 3, 4};
		auto it = v.crbegin();
		EXPECT_TRUE(it != v.crend());

		EXPECT_EQ(4, it[0]);
		EXPECT_EQ(3, it[1]);
		EXPECT_EQ(2, it[2]);
		EXPECT_EQ(1, it[3]);

		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(2, *++it);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == v.crend());
	}
#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201603) && !defined(BKSGE_GCC)
	// rbegin, rend (constexpr)
	{
		BKSGE_CXX17_STATIC_CONSTEXPR Vector4 v{1, 2, 3, 4};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = v.rbegin();
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it != v.rend());

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, it[0]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, it[1]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, it[2]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, it[3]);

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, *it);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it2 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, *it2);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it3 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it3);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, *it4);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, *it5);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it6 = it5 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it6 == v.rend());
	}
#endif
}

TYPED_TEST(MathVector4Test, EmptyTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	Vector4 v1{};
	const           Vector4 v2{};
	BKSGE_CONSTEXPR Vector4 v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathVector4Test, SizeTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	Vector4 v1{};
	const           Vector4 v2{};
	BKSGE_CONSTEXPR Vector4 v3{};
	EXPECT_EQ(4u, v1.size());
	EXPECT_EQ(4u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, v3.size());
}

TYPED_TEST(MathVector4Test, MaxSizeTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	Vector4 v1{};
	const           Vector4 v2{};
	BKSGE_CONSTEXPR Vector4 v3{};
	EXPECT_EQ(4u, v1.max_size());
	EXPECT_EQ(4u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, v3.max_size());
}

TYPED_TEST(MathVector4Test, NameAccessTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	{
		Vector4 v{1, 2, 3, 4};
		EXPECT_EQ(1, v.x());
		EXPECT_EQ(2, v.y());
		EXPECT_EQ(3, v.z());
		EXPECT_EQ(4, v.w());

		v.x() = -3;
		v.y() =  4;
		v.z() = -5;
		v.w() =  6;

		EXPECT_EQ(-3, v.x());
		EXPECT_EQ( 4, v.y());
		EXPECT_EQ(-5, v.z());
		EXPECT_EQ( 6, v.w());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.x());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.y());
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.z());
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.w());
	}
}

TYPED_TEST(MathVector4Test, SwizzleTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;
	using Vector3 = bksge::Vector3<T>;
	using Vector2 = bksge::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Vector4 v(1, 2, 3, 4);

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 1), v.xxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 2), v.xxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 3), v.xxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 4), v.xxxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 1), v.xxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 2), v.xxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 3), v.xxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 4), v.xxyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 1), v.xxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 2), v.xxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 3), v.xxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 4), v.xxzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 1), v.xxwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 2), v.xxwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 3), v.xxwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 4), v.xxww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 1), v.xyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 2), v.xyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 3), v.xyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 4), v.xyxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 1), v.xyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 2), v.xyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 3), v.xyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 4), v.xyyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 1), v.xyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 2), v.xyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 3), v.xyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 4), v.xyzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 1), v.xywx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 2), v.xywy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 3), v.xywz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 4), v.xyww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 1), v.xzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 2), v.xzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 3), v.xzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 4), v.xzxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 1), v.xzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 2), v.xzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 3), v.xzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 4), v.xzyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 1), v.xzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 2), v.xzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 3), v.xzzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 4), v.xzzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 1), v.xzwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 2), v.xzwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 3), v.xzwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 4), v.xzww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 1), v.xwxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 2), v.xwxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 3), v.xwxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 4), v.xwxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 1), v.xwyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 2), v.xwyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 3), v.xwyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 4), v.xwyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 1), v.xwzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 2), v.xwzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 3), v.xwzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 4), v.xwzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 1), v.xwwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 2), v.xwwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 3), v.xwwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 4), v.xwww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 1), v.yxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 2), v.yxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 3), v.yxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 4), v.yxxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 1), v.yxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 2), v.yxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 3), v.yxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 4), v.yxyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 1), v.yxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 2), v.yxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 3), v.yxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 4), v.yxzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 1), v.yxwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 2), v.yxwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 3), v.yxwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 4), v.yxww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 1), v.yyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 2), v.yyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 3), v.yyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 4), v.yyxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 1), v.yyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 2), v.yyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 3), v.yyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 4), v.yyyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 1), v.yyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 2), v.yyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 3), v.yyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 4), v.yyzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 1), v.yywx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 2), v.yywy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 3), v.yywz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 4), v.yyww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 1), v.yzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 2), v.yzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 3), v.yzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 4), v.yzxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 1), v.yzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 2), v.yzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 3), v.yzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 4), v.yzyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 1), v.yzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 2), v.yzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 3), v.yzzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 4), v.yzzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 1), v.yzwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 2), v.yzwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 3), v.yzwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 4), v.yzww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 1), v.ywxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 2), v.ywxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 3), v.ywxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 4), v.ywxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 1), v.ywyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 2), v.ywyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 3), v.ywyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 4), v.ywyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 1), v.ywzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 2), v.ywzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 3), v.ywzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 4), v.ywzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 1), v.ywwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 2), v.ywwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 3), v.ywwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 4), v.ywww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 1), v.zxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 2), v.zxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 3), v.zxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 4), v.zxxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 1), v.zxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 2), v.zxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 3), v.zxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 4), v.zxyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 1), v.zxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 2), v.zxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 3), v.zxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 4), v.zxzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 1), v.zxwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 2), v.zxwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 3), v.zxwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 4), v.zxww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 1), v.zyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 2), v.zyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 3), v.zyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 4), v.zyxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 1), v.zyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 2), v.zyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 3), v.zyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 4), v.zyyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 1), v.zyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 2), v.zyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 3), v.zyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 4), v.zyzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 1), v.zywx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 2), v.zywy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 3), v.zywz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 4), v.zyww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 1), v.zzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 2), v.zzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 3), v.zzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 4), v.zzxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 1), v.zzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 2), v.zzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 3), v.zzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 4), v.zzyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 1), v.zzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 2), v.zzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 3), v.zzzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 4), v.zzzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 1), v.zzwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 2), v.zzwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 3), v.zzwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 4), v.zzww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 1), v.zwxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 2), v.zwxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 3), v.zwxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 4), v.zwxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 1), v.zwyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 2), v.zwyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 3), v.zwyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 4), v.zwyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 1), v.zwzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 2), v.zwzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 3), v.zwzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 4), v.zwzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 1), v.zwwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 2), v.zwwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 3), v.zwwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 4), v.zwww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 1), v.wxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 2), v.wxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 3), v.wxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 4), v.wxxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 1), v.wxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 2), v.wxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 3), v.wxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 4), v.wxyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 1), v.wxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 2), v.wxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 3), v.wxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 4), v.wxzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 1), v.wxwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 2), v.wxwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 3), v.wxwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 4), v.wxww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 1), v.wyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 2), v.wyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 3), v.wyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 4), v.wyxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 1), v.wyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 2), v.wyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 3), v.wyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 4), v.wyyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 1), v.wyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 2), v.wyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 3), v.wyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 4), v.wyzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 1), v.wywx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 2), v.wywy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 3), v.wywz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 4), v.wyww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 1), v.wzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 2), v.wzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 3), v.wzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 4), v.wzxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 1), v.wzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 2), v.wzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 3), v.wzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 4), v.wzyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 1), v.wzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 2), v.wzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 3), v.wzzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 4), v.wzzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 1), v.wzwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 2), v.wzwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 3), v.wzwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 4), v.wzww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 1), v.wwxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 2), v.wwxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 3), v.wwxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 4), v.wwxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 1), v.wwyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 2), v.wwyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 3), v.wwyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 4), v.wwyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 1), v.wwzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 2), v.wwzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 3), v.wwzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 4), v.wwzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 1), v.wwwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 2), v.wwwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 3), v.wwwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 4), v.wwww());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 1), v.xxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 2), v.xxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 3), v.xxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 4), v.xxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 1), v.xyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 2), v.xyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 3), v.xyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 4), v.xyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 1), v.xzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 2), v.xzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 3), v.xzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 4), v.xzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 1), v.xwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 2), v.xwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 3), v.xwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 4), v.xww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 1), v.yxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 2), v.yxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 3), v.yxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 4), v.yxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 1), v.yyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 2), v.yyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 3), v.yyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 4), v.yyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 1), v.yzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 2), v.yzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 3), v.yzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 4), v.yzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 1), v.ywx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 2), v.ywy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 3), v.ywz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 4), v.yww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 1), v.zxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 2), v.zxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 3), v.zxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 4), v.zxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 1), v.zyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 2), v.zyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 3), v.zyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 4), v.zyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 1), v.zzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 2), v.zzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 3), v.zzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 4), v.zzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 1), v.zwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 2), v.zwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 3), v.zwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 4), v.zww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 1), v.wxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 2), v.wxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 3), v.wxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 4), v.wxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 1), v.wyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 2), v.wyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 3), v.wyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 4), v.wyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 1), v.wzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 2), v.wzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 3), v.wzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 4), v.wzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 1), v.wwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 2), v.wwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 3), v.wwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 4), v.www());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 1), v.xx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 2), v.xy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 3), v.xz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 4), v.xw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 1), v.yx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 2), v.yy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 3), v.yz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 4), v.yw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 1), v.zx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 2), v.zy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 3), v.zz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 4), v.zw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 1), v.wx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 2), v.wy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 3), v.wz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 4), v.ww());
}

TYPED_TEST(MathVector4Test, ZeroTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = Vector4::Zero();
		static_assert(std::is_same<decltype(v), const Vector4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(0, 0, 0, 0), v);
	}
	{
		const auto v = Vector4::Zero();
		static_assert(std::is_same<decltype(v), const Vector4>::value, "");
		EXPECT_EQ(Vector4(0, 0, 0, 0), v);
	}
}

TYPED_TEST(MathVector4Test, SwapTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	Vector4 v1{11, 12, 13, 14};
	Vector4 v2{21, 22, 23, 24};

	EXPECT_EQ(Vector4(11, 12, 13, 14), v1);
	EXPECT_EQ(Vector4(21, 22, 23, 24), v2);

	v1.swap(v2);

	EXPECT_EQ(Vector4(21, 22, 23, 24), v1);
	EXPECT_EQ(Vector4(11, 12, 13, 14), v2);

	swap(v1, v2);

	EXPECT_EQ(Vector4(11, 12, 13, 14), v1);
	EXPECT_EQ(Vector4(21, 22, 23, 24), v2);
}

TYPED_TEST(MathVector4Test, PlusMinusTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	{
		Vector4 v1(-1, 2, -3, 4);
		Vector4 v3 = +v1;
		Vector4 v4 = -v1;

		EXPECT_EQ(-1, v3[0]);
		EXPECT_EQ( 2, v3[1]);
		EXPECT_EQ(-3, v3[2]);
		EXPECT_EQ( 4, v3[3]);
		EXPECT_EQ( 1, v4[0]);
		EXPECT_EQ(-2, v4[1]);
		EXPECT_EQ( 3, v4[2]);
		EXPECT_EQ(-4, v4[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v2(3, -4, 5, -6);
		BKSGE_CONSTEXPR_OR_CONST Vector4 v5 = +v2;
		BKSGE_CONSTEXPR_OR_CONST Vector4 v6 = -v2;

		BKSGE_CONSTEXPR_EXPECT_EQ( 3, v5[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-4, v5[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 5, v5[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-6, v5[3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-3, v6[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v6[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-5, v6[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 6, v6[3]);
	}
}

TYPED_TEST(MathVector4Test, AddTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	// Vector4 += Vector4
	{
		Vector4 v;
		Vector4 t = (v += Vector4(2, 3, -4, 5));
		EXPECT_EQ(Vector4(2, 3, -4, 5), v);
		EXPECT_EQ(t, v);
	}

	// Vector4 + Vector4 -> Vector4
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 t =
			Vector4(-3, 4, 5, 6) + Vector4(0, 2, -1, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-3, 6, 4, 9), t);
	}
}

TYPED_TEST(MathVector4Test, SubTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	// Vector4 -= Vector4
	{
		Vector4 v;
		Vector4 t = (v -= Vector4(2, 3, -4, 5));
		EXPECT_EQ(Vector4(-2, -3, 4, -5), v);
		EXPECT_EQ(t, v);
	}

	// Vector4 - Vector4 -> Vector4
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 t =
			Vector4(-3, 4, 5, 6) - Vector4(0, 2, -1, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-3, 2, 6, 3), t);
	}
}

TYPED_TEST(MathVector4Test, MulScalarTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	// Vector4 *= スカラー
	{
		Vector4 v(2, 3, 4, 5);
		{
			Vector4 t = (v *= 4);
			EXPECT_EQ(Vector4(8, 12, 16, 20), v);
			EXPECT_EQ(t, v);
		}
		{
			Vector4 t = (v *= 0.5);
			EXPECT_EQ(Vector4(4, 6, 8, 10), v);
			EXPECT_EQ(t, v);
		}
	}

	// Vector4 * スカラー -> Vector4
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 t = Vector4(-3, 42, 5, 4) * -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(12, -168, -20, -16), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 t = Vector4(4, 6, 2, -10) * 2.5;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(10, 15, 5, -25), t);
	}
	// スカラー * Vector4 -> Vector4
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 t = 5 * Vector4(7, -8, 9, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(35, -40, 45, 10), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 t = -1.5 * Vector4(4, -6, -2, 8);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-6, 9, 3, -12), t);
	}
}

TYPED_TEST(MathVector4Test, DivScalarTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	// Vector4 /= スカラー
	{
		Vector4 v(2, 4, 6, 8);
		{
			Vector4 t = (v /= 2);
			EXPECT_EQ(Vector4(1, 2, 3, 4), v);
			EXPECT_EQ(t, v);
		}
		{
			Vector4 t = (v /= 0.5);
			EXPECT_EQ(Vector4(2, 4, 6, 8), v);
			EXPECT_EQ(t, v);
		}
	}

	// Vector4 / スカラー -> Vector4
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 t = Vector4(-4, 8, -12, 16) / -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, -2, 3, -4), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 t = Vector4(-4, 8, -12, 16) / 0.25;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-16, 32, -48, 64), t);
	}
}

TYPED_TEST(MathVector4Test, CompareTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	BKSGE_CONSTEXPR_OR_CONST Vector4 v1(1, 2, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Vector4 v2(1, 2, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Vector4 v3(2, 2, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Vector4 v4(1, 0, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Vector4 v5(1, 2, 2, 4);
	BKSGE_CONSTEXPR_OR_CONST Vector4 v6(1, 2, 3, 5);

	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v4);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v5);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v6);

	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v4);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v5);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v6);
}

TYPED_TEST(MathVector4Test, OutputStreamTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	{
		Vector4 const v{1, -2, 3, 4};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2, 3, 4 }", ss.str());
	}
	{
		Vector4 const v{-10, 9, 8, -7};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9, 8, -7 }", ss.str());
	}
}

TYPED_TEST(MathVector4Test, TupleElementTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	static_assert(std::is_same<typename std::tuple_element<0, Vector4>::type, T>::value, "");
	static_assert(std::is_same<typename std::tuple_element<1, Vector4>::type, T>::value, "");
	static_assert(std::is_same<typename std::tuple_element<2, Vector4>::type, T>::value, "");
	static_assert(std::is_same<typename std::tuple_element<3, Vector4>::type, T>::value, "");
}

TYPED_TEST(MathVector4Test, TupleGetTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	{
		Vector4 v{1, 2, 3, 4};

		EXPECT_EQ(1, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));
		EXPECT_EQ(4, bksge::get<3>(v));

		bksge::get<0>(v) = 5;
		bksge::get<3>(v) = 6;

		EXPECT_EQ(Vector4(5, 2, 3, 6), v);
		EXPECT_EQ(5, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));
		EXPECT_EQ(6, bksge::get<3>(v));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v{1, 2, 3, 4};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::get<2>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::get<3>(v));
	}
}

TYPED_TEST(MathVector4Test, TupleSizeTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	static_assert(std::tuple_size<Vector4>::value == 4, "");
}

TYPED_TEST(MathVector4Test, DotTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 0, 0), Vector4( 0, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 0, 0), Vector4( 1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 0, 0), Vector4(-1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 0, 0), Vector4( 0, 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 0, 0), Vector4( 0,-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 0, 0), Vector4( 0, 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 0, 0), Vector4( 0, 0,-1, 0)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 1, 0, 0, 0), Vector4( 0, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector4( 1, 0, 0, 0), Vector4( 1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector4( 1, 0, 0, 0), Vector4(-1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 1, 0, 0, 0), Vector4( 0, 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 1, 0, 0, 0), Vector4( 0,-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 1, 0, 0, 0), Vector4( 0, 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 1, 0, 0, 0), Vector4( 0, 0,-1, 0)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4(-1, 0, 0, 0), Vector4( 0, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector4(-1, 0, 0, 0), Vector4( 1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector4(-1, 0, 0, 0), Vector4(-1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4(-1, 0, 0, 0), Vector4( 0, 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4(-1, 0, 0, 0), Vector4( 0,-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4(-1, 0, 0, 0), Vector4( 0, 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4(-1, 0, 0, 0), Vector4( 0, 0,-1, 0)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 1, 0, 0), Vector4( 0, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 1, 0, 0), Vector4( 1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 1, 0, 0), Vector4(-1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector4( 0, 1, 0, 0), Vector4( 0, 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector4( 0, 1, 0, 0), Vector4( 0,-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 1, 0, 0), Vector4( 0, 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 1, 0, 0), Vector4( 0, 0,-1, 0)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0,-1, 0, 0), Vector4( 0, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0,-1, 0, 0), Vector4( 1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0,-1, 0, 0), Vector4(-1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector4( 0,-1, 0, 0), Vector4( 0, 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector4( 0,-1, 0, 0), Vector4( 0,-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0,-1, 0, 0), Vector4( 0, 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0,-1, 0, 0), Vector4( 0, 0,-1, 0)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 1, 0), Vector4( 0, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 1, 0), Vector4( 1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 1, 0), Vector4(-1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 1, 0), Vector4( 0, 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0, 1, 0), Vector4( 0,-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector4( 0, 0, 1, 0), Vector4( 0, 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector4( 0, 0, 1, 0), Vector4( 0, 0,-1, 0)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0,-1, 0), Vector4( 0, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0,-1, 0), Vector4( 1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0,-1, 0), Vector4(-1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0,-1, 0), Vector4( 0, 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector4( 0, 0,-1, 0), Vector4( 0,-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector4( 0, 0,-1, 0), Vector4( 0, 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector4( 0, 0,-1, 0), Vector4( 0, 0,-1, 0)));
}

TYPED_TEST(MathVector4Test, SquaredLengthTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ(  0, SquaredLength(Vector4(0, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  9, SquaredLength(Vector4(3, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 16, SquaredLength(Vector4(0, 4, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 25, SquaredLength(Vector4(0, 0,-5, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 36, SquaredLength(Vector4(0, 0, 0, 6)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 30, SquaredLength(Vector4(1, 2, 3, 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 30, SquaredLength(Vector4(1,-2, 3, 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 30, SquaredLength(Vector4(1, 2, 3,-4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(109, SquaredLength(Vector4(4,-8, 5, 2)));
}

TYPED_TEST(MathVector4Test, LengthTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	const double error = 0.000001;

	EXPECT_EQ(0, Length(Vector4( 0, 0, 0, 0)));
	EXPECT_EQ(3, Length(Vector4( 3, 0, 0, 0)));
	EXPECT_EQ(3, Length(Vector4(-3, 0, 0, 0)));
	EXPECT_EQ(4, Length(Vector4( 0, 4, 0, 0)));
	EXPECT_EQ(4, Length(Vector4( 0,-4, 0, 0)));
	EXPECT_EQ(5, Length(Vector4( 0, 0, 5, 0)));
	EXPECT_EQ(5, Length(Vector4( 0, 0,-5, 0)));
	EXPECT_EQ(6, Length(Vector4( 0, 0, 0, 6)));
	EXPECT_EQ(6, Length(Vector4( 0, 0, 0,-6)));
	EXPECT_NEAR(5.47722557505, (double)Length(Vector4( 1, 2, 3, 4)), error);
	EXPECT_NEAR(5.47722557505, (double)Length(Vector4( 1,-2,-3, 4)), error);
	EXPECT_NEAR(10.4403065089, (double)Length(Vector4( 4,-8, 5, 2)), error);
}

TYPED_TEST(MathVector4FloatTest, NormalizedTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	EXPECT_EQ(Vector4( 0, 0, 0, 0), Normalized(Vector4(  0,  0,  0,  0)));
	EXPECT_EQ(Vector4( 1, 0, 0, 0), Normalized(Vector4(  1,  0,  0,  0)));
	EXPECT_EQ(Vector4(-1, 0, 0, 0), Normalized(Vector4( -1,  0,  0,  0)));
	EXPECT_EQ(Vector4( 1, 0, 0, 0), Normalized(Vector4( 10,  0,  0,  0)));
	EXPECT_EQ(Vector4(-1, 0, 0, 0), Normalized(Vector4(-10,  0,  0,  0)));
	EXPECT_EQ(Vector4( 0, 1, 0, 0), Normalized(Vector4(  0,  1,  0,  0)));
	EXPECT_EQ(Vector4( 0,-1, 0, 0), Normalized(Vector4(  0, -1,  0,  0)));
	EXPECT_EQ(Vector4( 0, 1, 0, 0), Normalized(Vector4(  0,  5,  0,  0)));
	EXPECT_EQ(Vector4( 0,-1, 0, 0), Normalized(Vector4(  0, -5,  0,  0)));
	EXPECT_EQ(Vector4( 0, 0, 1, 0), Normalized(Vector4(  0,  0,  1,  0)));
	EXPECT_EQ(Vector4( 0, 0,-1, 0), Normalized(Vector4(  0,  0, -1,  0)));
	EXPECT_EQ(Vector4( 0, 0, 1, 0), Normalized(Vector4(  0,  0, 42,  0)));
	EXPECT_EQ(Vector4( 0, 0,-1, 0), Normalized(Vector4(  0,  0,-42,  0)));
	EXPECT_EQ(Vector4( 0, 0, 0, 1), Normalized(Vector4(  0,  0,  0,  3)));
	EXPECT_EQ(Vector4( 0, 0, 0,-1), Normalized(Vector4(  0,  0,  0, -3)));

	const double error = 0.000001;
	{
		auto const t = Normalized(Vector4(1, 2, 3, 4));
		EXPECT_NEAR(0.18257418583505536, (double)t.x(), error);
		EXPECT_NEAR(0.36514837167011072, (double)t.y(), error);
		EXPECT_NEAR(0.54772255750516607, (double)t.z(), error);
		EXPECT_NEAR(0.73029674334022143, (double)t.w(), error);
	}
	{
		auto const t = Normalized(Vector4(-5, 6, 7, -8));
		EXPECT_NEAR(-0.37904902178945171, (double)t.x(), error);
		EXPECT_NEAR( 0.45485882614734202, (double)t.y(), error);
		EXPECT_NEAR( 0.53066863050523239, (double)t.z(), error);
		EXPECT_NEAR(-0.60647843486312270, (double)t.w(), error);
	}
}

TYPED_TEST(MathVector4FloatTest, LerpTest)
{
	using T = TypeParam;
	using Vector4 = bksge::Vector4<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v1 {  0,  0,  0,  0 };
		BKSGE_CONSTEXPR_OR_CONST Vector4 v2 { 10, 20, 30, 40 };

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 0.0,  0.0,  0.0,  0.0), Lerp(v1, v2, 0.00f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 2.5,  5.0,  7.5, 10.0), Lerp(v1, v2, 0.25f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 5.0, 10.0, 15.0, 20.0), Lerp(v1, v2, 0.50f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 7.5, 15.0, 22.5, 30.0), Lerp(v1, v2, 0.75f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(10.0, 20.0, 30.0, 40.0), Lerp(v1, v2, 1.00f));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v1 { -10,  10,  20, -30 };
		BKSGE_CONSTEXPR_OR_CONST Vector4 v2 {  10, -20, -30,  40 };

		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(-10.0,  10.0,  20.0, -30.0), Lerp(v1, v2, 0.00));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( -5.0,   2.5,   7.5, -12.5), Lerp(v1, v2, 0.25));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(  0.0,  -5.0,  -5.0,   5.0), Lerp(v1, v2, 0.50));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(  5.0, -12.5, -17.5,  22.5), Lerp(v1, v2, 0.75));
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector4( 10.0, -20.0, -30.0,  40.0), Lerp(v1, v2, 1.00));
	}
}

TYPED_TEST(MathVector4Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::Vector4<T> const v { 1, -2, 3, -4 };

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

}	// namespace vector4_test

}	// namespace bksge_math_test
