/**
 *	@file	unit_test_core_math_color3.cpp
 *
 *	@brief	Color3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/color3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/algorithm/is_unique.hpp>
#include <bksge/fnd/config.hpp>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <functional>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace color3_test
{

using Color3f = bksge::math::Color3<float>;
using Color3i = bksge::math::Color3<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathColor3Test : public ::testing::Test {};
template <typename T>
class MathColor3FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathColor3Test, MathTestTypes);
TYPED_TEST_SUITE(MathColor3FloatTest, MathFloatTestTypes);

TYPED_TEST(MathColor3Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	static_assert(sizeof(Color3) == sizeof(T) * 3, "");
	static_assert(std::is_default_constructible<Color3>::value, "");
	static_assert(std::is_nothrow_default_constructible<Color3>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Color3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
}

TYPED_TEST(MathColor3Test, ValueConstructTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	static_assert(!std::is_constructible<Color3, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<Color3, T, T, T, T>::value, "");
	static_assert( std::is_constructible<Color3, T, T, T>::value, "");
	static_assert(!std::is_constructible<Color3, T, T>::value, "");
	static_assert(!std::is_constructible<Color3, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Color3, T, T, T, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Color3, T, T, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<Color3, T, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Color3, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Color3, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color3, T, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Color3, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color3, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color3, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v(1, 2, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v{4, 5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v = {7, 8, 9};
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(9, v[2]);
	}
}

TYPED_TEST(MathColor3Test, CopyConstructTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	static_assert(std::is_constructible<Color3, Color3 const&>::value, "");
	static_assert(std::is_nothrow_constructible<Color3, Color3 const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color3, Color3 const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Color3 v1{1, 2, 3};
	BKSGE_CONSTEXPR_OR_CONST Color3 v2{v1};

	BKSGE_CONSTEXPR_EXPECT_EQ(1, v1[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v1[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v1[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[2]);
}

TYPED_TEST(MathColor3FloatTest, ConvertConstructTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;
	using Color3u8 = bksge::math::Color3<std::uint8_t>;

	static_assert(std::is_constructible<Color3,   Color3u8 const&>::value, "");
	static_assert(std::is_constructible<Color3u8, Color3   const&>::value, "");
	static_assert(std::is_nothrow_constructible<Color3,   Color3u8 const&>::value, "");
	static_assert(std::is_nothrow_constructible<Color3u8, Color3   const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color3,   Color3u8 const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color3u8, Color3   const&>::value, "");

	BKSGE_CONSTEXPR double error = 0.0000001;
	{
		// TODO constexpr にしたい
		/*BKSGE_CONSTEXPR_OR_CONST*/ Color3u8 v1(0, 128, 255);
		/*BKSGE_CONSTEXPR_OR_CONST*/ Color3  v2(v1);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.00000000000000000, (double)v2[0], error);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.50196078431372548, (double)v2[1], error);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(1.00000000000000000, (double)v2[2], error);
	}
	{
		/*BKSGE_CONSTEXPR_OR_CONST*/ Color3u8 v1(32, 64, 192);
		/*BKSGE_CONSTEXPR_OR_CONST*/ Color3  v2(v1);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.12549019607843137, (double)v2[0], error);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.25098039215686274, (double)v2[1], error);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.75294117647058822, (double)v2[2], error);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3  v1(0.5, 1.0, 0.0);
		BKSGE_CONSTEXPR_OR_CONST Color3u8 v2(v1);
		BKSGE_CONSTEXPR_EXPECT_EQ(127, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(255, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(  0, v2[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3  v1(0.25, 0.75, 0.125);
		BKSGE_CONSTEXPR_OR_CONST Color3u8 v2(v1);
		BKSGE_CONSTEXPR_EXPECT_EQ( 63, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(191, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 31, v2[2]);
	}
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

TYPED_TEST(MathColor3FloatTest, CopyAssignTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	const double error = 0.0000001;

	Color3 v1(0, 1, 2);
	Color3 v2(3, 4, 5);
	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(2, v1[2]);
	EXPECT_EQ(3, v2[0]);
	EXPECT_EQ(4, v2[1]);
	EXPECT_EQ(5, v2[2]);

	v1 = Color3(6, -7, 8);
	v2 = Color3i(128, 255, 64);
	EXPECT_EQ( 6, v1[0]);
	EXPECT_EQ(-7, v1[1]);
	EXPECT_EQ( 8, v1[2]);
	EXPECT_NEAR(0.50196078431372548, (double)v2[0], error);
	EXPECT_NEAR(1.00000000000000000, (double)v2[1], error);
	EXPECT_NEAR(0.25098039215686274, (double)v2[2], error);

	// 自己代入
	v1 = v1;
	v2 = v2;
	EXPECT_EQ( 6, v1[0]);
	EXPECT_EQ(-7, v1[1]);
	EXPECT_EQ( 8, v1[2]);
	EXPECT_NEAR(0.50196078431372548, (double)v2[0], error);
	EXPECT_NEAR(1.00000000000000000, (double)v2[1], error);
	EXPECT_NEAR(0.25098039215686274, (double)v2[2], error);

	// 多重代入
	v1 = v2 = Color3f(4, 5, 6);
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(5, v1[1]);
	EXPECT_EQ(6, v1[2]);
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
	EXPECT_EQ(6, v2[2]);
}

BKSGE_WARNING_POP()

TYPED_TEST(MathColor3Test, IndexAccessTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	{
		Color3 v{1, 2, 3};
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
		BKSGE_CONSTEXPR_OR_CONST Color3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
	}
}

TYPED_TEST(MathColor3Test, AtTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	{
		Color3 v{1, 2, 3};
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
		BKSGE_CONSTEXPR_OR_CONST Color3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.at(2));
		EXPECT_THROW((void)v.at(3), std::out_of_range);
	}
}

TYPED_TEST(MathColor3Test, DataTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	{
		Color3 v{1, 2, 3};
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, *p);
		*p = 5;
		++p;
		EXPECT_EQ(2, *p);
		++p;
		EXPECT_EQ(3, *p);
		*p = 6;

		EXPECT_EQ(Color3(5, 2, 6), v);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Color3 v{1, 2, 3};
		BKSGE_STATIC_CONSTEXPR auto p = v.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, p[2]);
	}
#endif
}

TYPED_TEST(MathColor3Test, IteratorTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	// begin, end (non const)
	{
		Color3 v{1, 2, 3};
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

		EXPECT_EQ(Color3(5, 2, 6), v);
	}
	// begin, end (const)
	{
		const Color3 v{1, 2, 3};
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
		const Color3 v{1, 2, 3};
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
		BKSGE_STATIC_CONSTEXPR Color3 v{1, 2, 3};
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

TYPED_TEST(MathColor3Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	// rbegin, rend (non const)
	{
		Color3 v{1, 2, 3};
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
		const Color3 v{1, 2, 3};
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
		const Color3 v{1, 2, 3};
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
		BKSGE_CXX17_STATIC_CONSTEXPR Color3 v{1, 2, 3};
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

TYPED_TEST(MathColor3Test, EmptyTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	Color3 v1{};
	const           Color3 v2{};
	BKSGE_CONSTEXPR Color3 v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathColor3Test, SizeTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	Color3 v1{};
	const           Color3 v2{};
	BKSGE_CONSTEXPR Color3 v3{};
	EXPECT_EQ(3u, v1.size());
	EXPECT_EQ(3u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, v3.size());
}

TYPED_TEST(MathColor3Test, MaxSizeTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	Color3 v1{};
	const           Color3 v2{};
	BKSGE_CONSTEXPR Color3 v3{};
	EXPECT_EQ(3u, v1.max_size());
	EXPECT_EQ(3u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, v3.max_size());
}

TYPED_TEST(MathColor3Test, NameAccessTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	{
		Color3 v{1, 2, 3};
		EXPECT_EQ(1, v.r());
		EXPECT_EQ(2, v.g());
		EXPECT_EQ(3, v.b());

		v.r() = -3;
		v.g() =  4;
		v.b() = -5;

		EXPECT_EQ(-3, v.r());
		EXPECT_EQ( 4, v.g());
		EXPECT_EQ(-5, v.b());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.r());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.g());
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.b());
	}
}

TYPED_TEST(MathColor3Test, SwizzleTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Color3 v(1, 2, 3);

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 1), v.rrrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 2), v.rrrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 3), v.rrrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 1), v.rrgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 2), v.rrgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 3), v.rrgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 1), v.rrbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 2), v.rrbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 3), v.rrbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 1), v.rgrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 2), v.rgrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 3), v.rgrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 1), v.rggr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 2), v.rggg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 3), v.rggb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 1), v.rgbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 2), v.rgbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 3), v.rgbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 1), v.rbrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 2), v.rbrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 3), v.rbrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 1), v.rbgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 2), v.rbgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 3), v.rbgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 1), v.rbbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 2), v.rbbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 3), v.rbbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 1), v.grrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 2), v.grrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 3), v.grrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 1), v.grgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 2), v.grgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 3), v.grgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 1), v.grbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 2), v.grbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 3), v.grbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 1), v.ggrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 2), v.ggrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 3), v.ggrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 1), v.gggr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 2), v.gggg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 3), v.gggb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 1), v.ggbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 2), v.ggbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 3), v.ggbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 1), v.gbrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 2), v.gbrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 3), v.gbrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 1), v.gbgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 2), v.gbgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 3), v.gbgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 1), v.gbbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 2), v.gbbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 3), v.gbbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 1), v.brrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 2), v.brrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 3), v.brrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 1), v.brgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 2), v.brgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 3), v.brgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 1), v.brbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 2), v.brbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 3), v.brbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 1), v.bgrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 2), v.bgrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 3), v.bgrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 1), v.bggr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 2), v.bggg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 3), v.bggb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 1), v.bgbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 2), v.bgbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 3), v.bgbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 1), v.bbrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 2), v.bbrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 3), v.bbrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 1), v.bbgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 2), v.bbgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 3), v.bbgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 1), v.bbbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 2), v.bbbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 3), v.bbbb());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 1), v.rrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 2), v.rrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 3), v.rrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 1), v.rgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 2), v.rgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 3), v.rgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 1), v.rbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 2), v.rbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 3), v.rbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 1), v.grr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 2), v.grg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 3), v.grb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 1), v.ggr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 2), v.ggg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 3), v.ggb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 1), v.gbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 2), v.gbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 3), v.gbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 1), v.brr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 2), v.brg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 3), v.brb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 1), v.bgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 2), v.bgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 3), v.bgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 1), v.bbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 2), v.bbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 3), v.bbb());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 1), v.rr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 2), v.rg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 3), v.rb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 1), v.gr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 2), v.gg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 3), v.gb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 1), v.br());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 2), v.bg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 3), v.bb());
}

TYPED_TEST(MathColor3Test, SwapTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	Color3 v1{11, 12, 13};
	Color3 v2{21, 22, 23};

	EXPECT_EQ(Color3(11, 12, 13), v1);
	EXPECT_EQ(Color3(21, 22, 23), v2);

	v1.swap(v2);

	EXPECT_EQ(Color3(21, 22, 23), v1);
	EXPECT_EQ(Color3(11, 12, 13), v2);

	swap(v1, v2);

	EXPECT_EQ(Color3(11, 12, 13), v1);
	EXPECT_EQ(Color3(21, 22, 23), v2);
}

TYPED_TEST(MathColor3Test, PlusMinusTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	{
		Color3 v1(-1, 2, -3);
		Color3 v3 = +v1;
		Color3 v4 = -v1;

		EXPECT_EQ(-1, v3[0]);
		EXPECT_EQ( 2, v3[1]);
		EXPECT_EQ(-3, v3[2]);
		EXPECT_EQ( 1, v4[0]);
		EXPECT_EQ(-2, v4[1]);
		EXPECT_EQ( 3, v4[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v2(3, -4, 5);
		BKSGE_CONSTEXPR_OR_CONST Color3 v5 = +v2;
		BKSGE_CONSTEXPR_OR_CONST Color3 v6 = -v2;

		BKSGE_CONSTEXPR_EXPECT_EQ( 3, v5[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-4, v5[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 5, v5[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-3, v6[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v6[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-5, v6[2]);
	}
}

TYPED_TEST(MathColor3Test, AddTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	// Color3 += Color3
	{
		Color3 v;
		Color3 t = (v += Color3(2, 3, -4));
		EXPECT_EQ(Color3(2, 3, -4), v);
		EXPECT_EQ(t, v);
	}

	// Color3 + Color3 -> Color3
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 t =
			Color3(-3, 4, 5) + Color3(0, 2, -1);
		BKSGE_CONSTEXPR_EXPECT_EQ(Color3(-3, 6, 4), t);
	}
}

TYPED_TEST(MathColor3Test, SubTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	// Color3 -= Color3
	{
		Color3 v;
		Color3 t = (v -= Color3(2, 3, -4));
		EXPECT_EQ(Color3(-2, -3, 4), v);
		EXPECT_EQ(t, v);
	}

	// Color3 - Color3 -> Color3
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 t =
			Color3(-3, 4, 5) - Color3(0, 2, -1);
		BKSGE_CONSTEXPR_EXPECT_EQ(Color3(-3, 2, 6), t);
	}
}

TYPED_TEST(MathColor3Test, MulScalarTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	// Color3 *= スカラー
	{
		Color3 v(2, 3, 4);
		{
			Color3 t = (v *= 4);
			EXPECT_EQ(Color3(8, 12, 16), v);
			EXPECT_EQ(t, v);
		}
		{
			Color3 t = (v *= 0.5);
			EXPECT_EQ(Color3(4, 6, 8), v);
			EXPECT_EQ(t, v);
		}
	}

	// Color3 * スカラー -> Color3
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 t = Color3(-3, 42, 5) * -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Color3(12, -168, -20), t);
	}
	{
		const Color3 t = Color3(4, 6, 2) * 2.5;
		EXPECT_EQ(Color3(10, 15, 5), t);
	}
	// スカラー * Color3 -> Color3
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 t = 5 * Color3(7, -8, 9);
		BKSGE_CONSTEXPR_EXPECT_EQ(Color3(35, -40, 45), t);
	}
	{
		const Color3 t = -1.5 * Color3(4, -6, -2);
		EXPECT_EQ(Color3(-6, 9, 3), t);
	}
}

TYPED_TEST(MathColor3Test, MulColor3Test)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	// Color3 *= Color3
	{
		Color3 v(2, 3, 4);

		auto t = (v *= Color3(-1, 2, -3));
		static_assert(std::is_same<decltype(t), Color3>::value, "");
		EXPECT_EQ(Color3(-2, 6, -12), v);
		EXPECT_EQ(t, v);
	}

	// Color3 * Color3 -> Color3
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Color3(-3, 4, 5) * Color3(0, 2, -1);
		static_assert(std::is_same<decltype(t), const Color3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Color3(0, 8, -5), t);
	}
}

TYPED_TEST(MathColor3Test, DivScalarTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	// Color3 /= スカラー
	{
		Color3 v(2, 4, 6);
		{
			Color3 t = (v /= 2);
			EXPECT_EQ(Color3(1, 2, 3), v);
			EXPECT_EQ(t, v);
		}
		{
			Color3 t = (v /= 0.5);
			EXPECT_EQ(Color3(2, 4, 6), v);
			EXPECT_EQ(t, v);
		}
	}

	// Color3 / スカラー -> Color3
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 t = Color3(-4, 8, -12) / -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Color3(1, -2, 3), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 t = Color3(-4, 8, -12) / 0.25;
		BKSGE_CONSTEXPR_EXPECT_EQ(Color3(-16, 32, -48), t);
	}
}

TYPED_TEST(MathColor3Test, DivColor3Test)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	// Color3 /= Color3
	{
		Color3 v(8, 12, 16);

		auto t = (v /= Color3(-1, 2, -4));
		static_assert(std::is_same<decltype(t), Color3>::value, "");
		EXPECT_EQ(Color3(-8, 6, -4), v);
		EXPECT_EQ(t, v);
	}

	// Color3 / Color3 -> Color3
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Color3(-3, 4, 5) / Color3(1, 2, -1);
		static_assert(std::is_same<decltype(t), const Color3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Color3(-3, 2, -5), t);
	}
}

TYPED_TEST(MathColor3Test, CompareTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	BKSGE_CONSTEXPR_OR_CONST Color3 v1(1, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST Color3 v2(1, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST Color3 v3(2, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST Color3 v4(1, 0, 3);
	BKSGE_CONSTEXPR_OR_CONST Color3 v5(1, 2, 2);

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

TYPED_TEST(MathColor3Test, OutputStreamTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	{
		Color3 const v{1, -2, 3};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2, 3 }", ss.str());
	}
	{
		Color3 const v{-10, 9, 8};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9, 8 }", ss.str());
	}
}

TYPED_TEST(MathColor3Test, TupleElementTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	static_assert(std::is_same<typename std::tuple_element<0, Color3>::type, T>::value, "");
	static_assert(std::is_same<typename std::tuple_element<1, Color3>::type, T>::value, "");
	static_assert(std::is_same<typename std::tuple_element<2, Color3>::type, T>::value, "");
}

TYPED_TEST(MathColor3Test, TupleGetTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	{
		Color3 v{1, 2, 3};

		EXPECT_EQ(1, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));

		bksge::get<0>(v) = 5;

		EXPECT_EQ(Color3(5, 2, 3), v);
		EXPECT_EQ(5, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v{1, 2, 3};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::get<2>(v));
	}
}

TYPED_TEST(MathColor3Test, TupleSizeTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	static_assert(std::tuple_size<Color3>::value == 3, "");
}

TYPED_TEST(MathColor3Test, ZeroTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = Color3::Zero();
		static_assert(std::is_same<decltype(v), const Color3>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Color3(0, 0, 0), v);
	}
	{
		const auto v = Color3::Zero();
		static_assert(std::is_same<decltype(v), const Color3>::value, "");
		EXPECT_EQ(Color3(0, 0, 0), v);
	}
}

TYPED_TEST(MathColor3FloatTest, LerpTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ(Color3( 0.0,  0.0,  0.0), Lerp(Color3(0, 0, 0), Color3(10, 20, 30), TypeParam(0.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Color3( 2.5,  5.0,  7.5), Lerp(Color3(0, 0, 0), Color3(10, 20, 30), TypeParam(0.25)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Color3( 5.0, 10.0, 15.0), Lerp(Color3(0, 0, 0), Color3(10, 20, 30), TypeParam(0.50)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Color3( 7.5, 15.0, 22.5), Lerp(Color3(0, 0, 0), Color3(10, 20, 30), TypeParam(0.75)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Color3(10.0, 20.0, 30.0), Lerp(Color3(0, 0, 0), Color3(10, 20, 30), TypeParam(1.00)));
}

TYPED_TEST(MathColor3Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::Color3<T> const v { 1, 2, 3 };

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

TYPED_TEST(MathColor3Test, HashTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	std::hash<Color3> h;

	Color3 const c1(1, 2, 3);
	Color3 const c2(2, 2, 3);
	Color3 const c3(1, 0, 3);
	Color3 const c4(1, 2, 2);

	std::vector<std::size_t> v;
	v.push_back(h(c1));
	v.push_back(h(c2));
	v.push_back(h(c3));
	v.push_back(h(c4));
	std::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(c1));
	std::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace color3_test

}	// namespace bksge_math_test
