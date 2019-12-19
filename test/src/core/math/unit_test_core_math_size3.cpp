﻿/**
 *	@file	unit_test_core_math_size3.cpp
 *
 *	@brief	Size3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/size3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/scale3.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_math_test
{

namespace size3_test
{

using Size3f = bksge::math::Size3<float>;
using Size3i = bksge::math::Size3<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;

template <typename T>
class MathSize3Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathSize3Test, MathTestTypes);

TYPED_TEST(MathSize3Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	static_assert(sizeof(Size3) == sizeof(T) * 3, "");
	static_assert(std::is_default_constructible<Size3>::value, "");
	static_assert(std::is_nothrow_default_constructible<Size3>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Size3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
}

TYPED_TEST(MathSize3Test, ValueConstructTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	static_assert(!std::is_constructible<Size3, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<Size3, T, T, T, T>::value, "");
	static_assert( std::is_constructible<Size3, T, T, T>::value, "");
	static_assert(!std::is_constructible<Size3, T, T>::value, "");
	static_assert(!std::is_constructible<Size3, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Size3, T, T, T, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Size3, T, T, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<Size3, T, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Size3, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Size3, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Size3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Size3, T, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Size3, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Size3, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Size3, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v(1, 2, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v{4, 5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v = {7, 8, 9};
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(9, v[2]);
	}
}

TYPED_TEST(MathSize3Test, CopyConstructTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	static_assert(std::is_constructible<Size3,  Size3  const&>::value, "");
	static_assert(std::is_constructible<Size3,  Size3i const&>::value, "");
	static_assert(std::is_constructible<Size3,  Size3f const&>::value, "");
	static_assert(std::is_constructible<Size3i, Size3  const&>::value, "");
	static_assert(std::is_constructible<Size3i, Size3i const&>::value, "");
	static_assert(std::is_constructible<Size3i, Size3f const&>::value, "");
	static_assert(std::is_constructible<Size3f, Size3  const&>::value, "");
	static_assert(std::is_constructible<Size3f, Size3i const&>::value, "");
	static_assert(std::is_constructible<Size3f, Size3f const&>::value, "");

	static_assert(std::is_nothrow_constructible<Size3,  Size3  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size3,  Size3i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size3,  Size3f const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size3i, Size3  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size3i, Size3i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size3i, Size3f const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size3f, Size3  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size3f, Size3i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size3f, Size3f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Size3,  Size3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size3,  Size3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size3,  Size3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size3i, Size3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size3i, Size3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size3i, Size3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size3f, Size3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size3f, Size3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size3f, Size3f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Size3  v1{1, 2, 3};
	BKSGE_CONSTEXPR_OR_CONST Size3  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Size3i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Size3f v4{v2};

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

TYPED_TEST(MathSize3Test, CopyAssignTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	Size3 v1(0, 1, 2);
	Size3 v2(3, 4, 5);
	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(2, v1[2]);
	EXPECT_EQ(3, v2[0]);
	EXPECT_EQ(4, v2[1]);
	EXPECT_EQ(5, v2[2]);

	v1 = Size3(6, -7, 8);
	v2 = Size3i(-9, 10, 11);
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
	v1 = v2 = Size3f(4, 5, 6);
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(5, v1[1]);
	EXPECT_EQ(6, v1[2]);
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
	EXPECT_EQ(6, v2[2]);
}

BKSGE_WARNING_POP()

TYPED_TEST(MathSize3Test, IndexAccessTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	{
		Size3 v{1, 2, 3};
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
		BKSGE_CONSTEXPR_OR_CONST Size3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
	}
}

TYPED_TEST(MathSize3Test, AtTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	{
		Size3 v{1, 2, 3};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
		EXPECT_THROW((void)v.at(3), std::out_of_range);

		v.at(0) = -3;
		v.at(1) =  4;
		v.at(2) = -5;

		EXPECT_EQ(-3, v.at(0));
		EXPECT_EQ( 4, v.at(1));
		EXPECT_EQ(-5, v.at(2));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.at(2));
		EXPECT_THROW((void)v.at(3), std::out_of_range);
	}
}

TYPED_TEST(MathSize3Test, DataTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	{
		Size3 v{1, 2, 3};
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, *p);
		*p = 5;
		++p;
		EXPECT_EQ(2, *p);
		++p;
		EXPECT_EQ(3, *p);
		*p = 6;

		EXPECT_EQ(Size3(5, 2, 6), v);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Size3 v{1, 2, 3};
		BKSGE_STATIC_CONSTEXPR auto p = v.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, p[2]);
	}
#endif
}

TYPED_TEST(MathSize3Test, IteratorTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	// begin, end (non const)
	{
		Size3 v{1, 2, 3};
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

		EXPECT_EQ(Size3(5, 2, 6), v);
	}
	// begin, end (const)
	{
		const Size3 v{1, 2, 3};
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
		const Size3 v{1, 2, 3};
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
		BKSGE_STATIC_CONSTEXPR Size3 v{1, 2, 3};
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

TYPED_TEST(MathSize3Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	// rbegin, rend (non const)
	{
		Size3 v{1, 2, 3};
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
		const Size3 v{1, 2, 3};
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
		const Size3 v{1, 2, 3};
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
		BKSGE_CXX17_STATIC_CONSTEXPR Size3 v{1, 2, 3};
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

TYPED_TEST(MathSize3Test, EmptyTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	Size3 v1{};
	const           Size3 v2{};
	BKSGE_CONSTEXPR Size3 v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathSize3Test, SizeTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	Size3 v1{};
	const           Size3 v2{};
	BKSGE_CONSTEXPR Size3 v3{};
	EXPECT_EQ(3u, v1.size());
	EXPECT_EQ(3u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, v3.size());
}

TYPED_TEST(MathSize3Test, MaxSizeTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	Size3 v1{};
	const           Size3 v2{};
	BKSGE_CONSTEXPR Size3 v3{};
	EXPECT_EQ(3u, v1.max_size());
	EXPECT_EQ(3u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, v3.max_size());
}

TYPED_TEST(MathSize3Test, NameAccessTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	{
		Size3 v{1, 2, 3};
		EXPECT_EQ(1, v.w());
		EXPECT_EQ(2, v.h());
		EXPECT_EQ(3, v.d());

		v.w() = -3;
		v.h() =  4;
		v.d() = -5;

		EXPECT_EQ(-3, v.w());
		EXPECT_EQ( 4, v.h());
		EXPECT_EQ(-5, v.d());
	}
	{
		Size3 v{1, 2, 3};
		EXPECT_EQ(1, v.width());
		EXPECT_EQ(2, v.height());
		EXPECT_EQ(3, v.depth());

		v.width()  = -3;
		v.height() =  4;
		v.depth()  = -5;

		EXPECT_EQ(-3, v.width());
		EXPECT_EQ( 4, v.height());
		EXPECT_EQ(-5, v.depth());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.w());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.d());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.width());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.height());
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.depth());
	}
}

TYPED_TEST(MathSize3Test, SwizzleTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Size3 v(1, 2, 3);

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 1), v.wwww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 2), v.wwwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 3), v.wwwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 1), v.wwhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 2), v.wwhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 3), v.wwhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 1), v.wwdw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 2), v.wwdh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 3), v.wwdd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 1), v.whww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 2), v.whwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 3), v.whwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 1), v.whhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 2), v.whhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 3), v.whhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 1), v.whdw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 2), v.whdh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 3), v.whdd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 1), v.wdww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 2), v.wdwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 3), v.wdwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 1), v.wdhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 2), v.wdhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 3), v.wdhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 1), v.wddw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 2), v.wddh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 3), v.wddd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 1), v.hwww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 2), v.hwwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 3), v.hwwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 1), v.hwhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 2), v.hwhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 3), v.hwhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 1), v.hwdw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 2), v.hwdh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 3), v.hwdd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 1), v.hhww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 2), v.hhwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 3), v.hhwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 1), v.hhhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 2), v.hhhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 3), v.hhhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 1), v.hhdw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 2), v.hhdh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 3), v.hhdd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 1), v.hdww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 2), v.hdwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 3), v.hdwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 1), v.hdhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 2), v.hdhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 3), v.hdhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 1), v.hddw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 2), v.hddh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 3), v.hddd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 1), v.dwww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 2), v.dwwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 3), v.dwwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 1), v.dwhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 2), v.dwhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 3), v.dwhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 1), v.dwdw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 2), v.dwdh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 3), v.dwdd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 1), v.dhww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 2), v.dhwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 3), v.dhwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 1), v.dhhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 2), v.dhhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 3), v.dhhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 1), v.dhdw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 2), v.dhdh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 3), v.dhdd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 1), v.ddww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 2), v.ddwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 3), v.ddwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 1), v.ddhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 2), v.ddhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 3), v.ddhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 1), v.dddw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 2), v.dddh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 3), v.dddd());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 1), v.www());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 2), v.wwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 3), v.wwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 1), v.whw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 2), v.whh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 3), v.whd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 1), v.wdw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 2), v.wdh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 3), v.wdd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 1), v.hww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 2), v.hwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 3), v.hwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 1), v.hhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 2), v.hhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 3), v.hhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 1), v.hdw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 2), v.hdh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 3), v.hdd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 1), v.dww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 2), v.dwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 3), v.dwd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 1), v.dhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 2), v.dhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 3), v.dhd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 1), v.ddw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 2), v.ddh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 3), v.ddd());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 1), v.ww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 2), v.wh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 3), v.wd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 1), v.hw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 2), v.hh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 3), v.hd());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 1), v.dw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 2), v.dh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 3), v.dd());
}

TYPED_TEST(MathSize3Test, SwapTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	Size3 v1{11, 12, 13};
	Size3 v2{21, 22, 23};

	EXPECT_EQ(Size3(11, 12, 13), v1);
	EXPECT_EQ(Size3(21, 22, 23), v2);

	v1.swap(v2);

	EXPECT_EQ(Size3(21, 22, 23), v1);
	EXPECT_EQ(Size3(11, 12, 13), v2);

	swap(v1, v2);

	EXPECT_EQ(Size3(11, 12, 13), v1);
	EXPECT_EQ(Size3(21, 22, 23), v2);
}

TYPED_TEST(MathSize3Test, PlusMinusTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	{
		Size3 v1(-1, 2, -3);
		Size3 v3 = +v1;
		Size3 v4 = -v1;

		EXPECT_EQ(-1, v3[0]);
		EXPECT_EQ( 2, v3[1]);
		EXPECT_EQ(-3, v3[2]);
		EXPECT_EQ( 1, v4[0]);
		EXPECT_EQ(-2, v4[1]);
		EXPECT_EQ( 3, v4[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v2(3, -4, 5);
		BKSGE_CONSTEXPR_OR_CONST Size3 v5 = +v2;
		BKSGE_CONSTEXPR_OR_CONST Size3 v6 = -v2;

		BKSGE_CONSTEXPR_EXPECT_EQ( 3, v5[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-4, v5[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 5, v5[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-3, v6[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v6[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-5, v6[2]);
	}
}

TYPED_TEST(MathSize3Test, AddTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	// Size3 += Size3
	{
		Size3 v;
		Size3 t = (v += Size3(2, 3, -4));
		EXPECT_EQ(Size3(2, 3, -4), v);
		EXPECT_EQ(t, v);
	}

	// Size3 + Size3 -> Size3
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 t =
			Size3(-3, 4, 5) + Size3(0, 2, -1);
		BKSGE_CONSTEXPR_EXPECT_EQ(Size3(-3, 6, 4), t);
	}
}

TYPED_TEST(MathSize3Test, SubTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	// Size3 -= Size3
	{
		Size3 v;
		Size3 t = (v -= Size3(2, 3, -4));
		EXPECT_EQ(Size3(-2, -3, 4), v);
		EXPECT_EQ(t, v);
	}

	// Size3 - Size3 -> Size3
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 t =
			Size3(-3, 4, 5) - Size3(0, 2, -1);
		BKSGE_CONSTEXPR_EXPECT_EQ(Size3(-3, 2, 6), t);
	}
}

TYPED_TEST(MathSize3Test, MulScalarTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	// Size3 *= スカラー
	{
		Size3 v(2, 3, 4);
		{
			Size3 t = (v *= 4);
			EXPECT_EQ(Size3(8, 12, 16), v);
			EXPECT_EQ(t, v);
		}
		{
			Size3 t = (v *= 0.5);
			EXPECT_EQ(Size3(4, 6, 8), v);
			EXPECT_EQ(t, v);
		}
	}

	// Size3 * スカラー -> Size3
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 t = Size3(-3, 42, 5) * -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Size3(12, -168, -20), t);
	}
	{
		const Size3 t = Size3(4, 6, 2) * 2.5;
		EXPECT_EQ(Size3(10, 15, 5), t);
	}
	// スカラー * Size3 -> Size3
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 t = 5 * Size3(7, -8, 9);
		BKSGE_CONSTEXPR_EXPECT_EQ(Size3(35, -40, 45), t);
	}
	{
		const Size3 t = -1.5 * Size3(4, -6, -2);
		EXPECT_EQ(Size3(-6, 9, 3), t);
	}
}

TYPED_TEST(MathSize3Test, MulScaleTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;
	using Scale3 = bksge::math::Scale3<T>;

	// Size3 *= Scale3
	{
		Size3 v(2, 3, 4);
		{
			Size3 t = (v *= Scale3(4, 5, 6));
			EXPECT_EQ(Size3(8, 15, 24), v);
			EXPECT_EQ(t, v);
		}
	}

	// Size3 * Scale3 -> Size3
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 t = Size3(-3, 2, 5) * Scale3(-4, -5, 8);
		BKSGE_CONSTEXPR_EXPECT_EQ(Size3(12, -10, 40), t);
	}
}

TYPED_TEST(MathSize3Test, DivScalarTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	// Size3 /= スカラー
	{
		Size3 v(2, 4, 6);
		{
			Size3 t = (v /= 2);
			EXPECT_EQ(Size3(1, 2, 3), v);
			EXPECT_EQ(t, v);
		}
		{
			Size3 t = (v /= 0.5);
			EXPECT_EQ(Size3(2, 4, 6), v);
			EXPECT_EQ(t, v);
		}
	}

	// Size3 / スカラー -> Size3
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 t = Size3(-4, 8, -12) / -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Size3(1, -2, 3), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 t = Size3(-4, 8, -12) / 0.25;
		BKSGE_CONSTEXPR_EXPECT_EQ(Size3(-16, 32, -48), t);
	}
}

TYPED_TEST(MathSize3Test, CompareTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	BKSGE_CONSTEXPR_OR_CONST Size3 v1(1, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST Size3 v2(1, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST Size3 v3(2, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST Size3 v4(1, 0, 3);
	BKSGE_CONSTEXPR_OR_CONST Size3 v5(1, 2, 2);

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

TYPED_TEST(MathSize3Test, OutputStreamTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	{
		Size3 const v{1, -2, 3};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2, 3 }", ss.str());
	}
	{
		Size3 const v{-10, 9, 8};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9, 8 }", ss.str());
	}
}

TYPED_TEST(MathSize3Test, TupleElementTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	static_assert(std::is_same<typename std::tuple_element<0, Size3>::type, T>::value, "");
	static_assert(std::is_same<typename std::tuple_element<1, Size3>::type, T>::value, "");
	static_assert(std::is_same<typename std::tuple_element<2, Size3>::type, T>::value, "");
}

TYPED_TEST(MathSize3Test, TupleGetTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	{
		Size3 v{1, 2, 3};

		EXPECT_EQ(1, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));

		bksge::get<0>(v) = 5;

		EXPECT_EQ(Size3(5, 2, 3), v);
		EXPECT_EQ(5, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size3 v{1, 2, 3};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::get<2>(v));
	}
}

TYPED_TEST(MathSize3Test, TupleSizeTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	static_assert(std::tuple_size<Size3>::value == 3, "");
}

TYPED_TEST(MathSize3Test, ZeroTest)
{
	using T = TypeParam;
	using Size3 = bksge::math::Size3<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = Size3::Zero();
		static_assert(std::is_same<decltype(v), const Size3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Size3(0, 0, 0), v);
	}
	{
		const auto v = Size3::Zero();
		static_assert(std::is_same<decltype(v), const Size3>::value, "");
		EXPECT_EQ(Size3(0, 0, 0), v);
	}
}

}	// namespace size3_test

}	// namespace bksge_math_test