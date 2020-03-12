/**
 *	@file	unit_test_core_math_color4.cpp
 *
 *	@brief	Color4 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/color4.hpp>
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
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <vector>
#include <functional>
#include <tuple>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace color4_test
{

using Color4f = bksge::math::Color4<float>;
using Color4i = bksge::math::Color4<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathColor4Test : public ::testing::Test {};
template <typename T>
class MathColor4FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathColor4Test, MathTestTypes);
TYPED_TEST_SUITE(MathColor4FloatTest, MathFloatTestTypes);

TYPED_TEST(MathColor4Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	static_assert(sizeof(Color4) == sizeof(T) * 4, "");
	static_assert(bksge::is_default_constructible<Color4>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Color4>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Color4>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v={};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3]);
	}
}

TYPED_TEST(MathColor4Test, ValueConstructTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	static_assert(!bksge::is_constructible<Color4, T, T, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Color4, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Color4, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Color4, T, T>::value, "");
	static_assert(!bksge::is_constructible<Color4, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color4, T, T, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Color4, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color4, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color4, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color4, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color4, T, T, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Color4, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color4, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color4, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color4, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v(1, 2, 3, 4);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v = {9, 10, 11, 12};
		BKSGE_CONSTEXPR_EXPECT_EQ(9, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3]);
	}
}

TYPED_TEST(MathColor4Test, CopyConstructTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	static_assert(bksge::is_constructible<Color4, Color4 const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4, Color4 const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4, Color4 const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Color4  v1{1, 2, 3, 4};
	BKSGE_CONSTEXPR_OR_CONST Color4  v2{v1};

	BKSGE_CONSTEXPR_EXPECT_EQ(1, v1[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v1[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v1[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(4, v1[3]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[3]);
}

TYPED_TEST(MathColor4FloatTest, ConvertConstructTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;
	using Color4u8 = bksge::math::Color4<bksge::uint8_t>;

	static_assert(bksge::is_constructible<Color4,   Color4u8 const&>::value, "");
	static_assert(bksge::is_constructible<Color4u8, Color4   const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4,   Color4u8 const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4u8, Color4   const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4,   Color4u8 const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4u8, Color4   const&>::value, "");

	BKSGE_CONSTEXPR double error = 0.0000001;
	{
		// TODO constexpr にしたい
		/*BKSGE_CONSTEXPR_OR_CONST*/ Color4u8 v1(0, 128, 255, 160);
		/*BKSGE_CONSTEXPR_OR_CONST*/ Color4   v2(v1);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.00000000000000000, (double)v2[0], error);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.50196078431372548, (double)v2[1], error);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(1.00000000000000000, (double)v2[2], error);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.62745100259780884, (double)v2[3], error);
	}
	{
		/*BKSGE_CONSTEXPR_OR_CONST*/ Color4u8 v1(32, 64, 192, 225);
		/*BKSGE_CONSTEXPR_OR_CONST*/ Color4   v2(v1);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.12549019607843137, (double)v2[0], error);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.25098039215686274, (double)v2[1], error);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.75294117647058822, (double)v2[2], error);
		/*BKSGE_CONSTEXPR_*/EXPECT_NEAR(0.88235294818878174, (double)v2[3], error);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4   v1(0.5, 1.0, 0.0, 0.25);
		BKSGE_CONSTEXPR_OR_CONST Color4u8 v2(v1);
		BKSGE_CONSTEXPR_EXPECT_EQ(127, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(255, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(  0, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 63, v2[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4   v1(0.25, 0.75, 0.125, 0.375);
		BKSGE_CONSTEXPR_OR_CONST Color4u8 v2(v1);
		BKSGE_CONSTEXPR_EXPECT_EQ( 63, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(191, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 31, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 95, v2[3]);
	}
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

TYPED_TEST(MathColor4FloatTest, CopyAssignTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	const double error = 0.0000001;

	Color4 v1(0, 1, 2, -2);
	Color4 v2(3, 4, 5, 6);
	EXPECT_EQ( 0, v1[0]);
	EXPECT_EQ( 1, v1[1]);
	EXPECT_EQ( 2, v1[2]);
	EXPECT_EQ(-2, v1[3]);
	EXPECT_EQ( 3, v2[0]);
	EXPECT_EQ( 4, v2[1]);
	EXPECT_EQ( 5, v2[2]);
	EXPECT_EQ( 6, v2[3]);

	v1 = Color4(6, -7, 8, 9);
	v2 = Color4i(16, 32, 64, 128);
	EXPECT_EQ( 6, v1[0]);
	EXPECT_EQ(-7, v1[1]);
	EXPECT_EQ( 8, v1[2]);
	EXPECT_EQ( 9, v1[3]);
	EXPECT_NEAR(0.06274510174989700, (double)v2[0], error);
	EXPECT_NEAR(0.12549019607843137, (double)v2[1], error);
	EXPECT_NEAR(0.25098039215686274, (double)v2[2], error);
	EXPECT_NEAR(0.50196078431372548, (double)v2[3], error);

	// 自己代入
	v1 = v1;
	v2 = v2;
	EXPECT_EQ( 6, v1[0]);
	EXPECT_EQ(-7, v1[1]);
	EXPECT_EQ( 8, v1[2]);
	EXPECT_EQ( 9, v1[3]);
	EXPECT_NEAR(0.06274510174989700, (double)v2[0], error);
	EXPECT_NEAR(0.12549019607843137, (double)v2[1], error);
	EXPECT_NEAR(0.25098039215686274, (double)v2[2], error);
	EXPECT_NEAR(0.50196078431372548, (double)v2[3], error);

	// 多重代入
	v1 = v2 = Color4f(4, 5, 6, 7);
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

TYPED_TEST(MathColor4Test, IndexAccessTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	{
		Color4 v{1, 2, 3, 4};
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
		BKSGE_CONSTEXPR_OR_CONST Color4 v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[3]);
	}
}

TYPED_TEST(MathColor4Test, AtTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	{
		Color4 v{1, 2, 3, 4};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
		EXPECT_EQ(4, v.at(3));
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);

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
		BKSGE_CONSTEXPR_OR_CONST Color4 v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.at(2));
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.at(3));
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
}

TYPED_TEST(MathColor4Test, DataTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	{
		Color4 v{1, 2, 3, 4};
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

		EXPECT_EQ(Color4(5, 2, 6, 4), v);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Color4 v{1, 2, 3, 4};
		BKSGE_STATIC_CONSTEXPR auto p = v.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, p[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, p[3]);
	}
#endif
}

TYPED_TEST(MathColor4Test, IteratorTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	// begin, end (non const)
	{
		Color4 v{1, 2, 3, 4};
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

		EXPECT_EQ(Color4(5, 2, 6, 4), v);
	}
	// begin, end (const)
	{
		const Color4 v{1, 2, 3, 4};
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
		const Color4 v{1, 2, 3, 4};
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
		BKSGE_STATIC_CONSTEXPR Color4 v{1, 2, 3, 4};
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

TYPED_TEST(MathColor4Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	// rbegin, rend (non const)
	{
		Color4 v{1, 2, 3, 4};
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
		const Color4 v{1, 2, 3, 4};
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
		const Color4 v{1, 2, 3, 4};
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
		BKSGE_CXX17_STATIC_CONSTEXPR Color4 v{1, 2, 3, 4};
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

TYPED_TEST(MathColor4Test, EmptyTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	Color4 v1{};
	const           Color4 v2{};
	BKSGE_CONSTEXPR Color4 v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathColor4Test, SizeTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	Color4 v1{};
	const           Color4 v2{};
	BKSGE_CONSTEXPR Color4 v3{};
	EXPECT_EQ(4u, v1.size());
	EXPECT_EQ(4u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, v3.size());
}

TYPED_TEST(MathColor4Test, MaxSizeTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	Color4 v1{};
	const           Color4 v2{};
	BKSGE_CONSTEXPR Color4 v3{};
	EXPECT_EQ(4u, v1.max_size());
	EXPECT_EQ(4u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, v3.max_size());
}

TYPED_TEST(MathColor4Test, NameAccessTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	{
		Color4 v{1, 2, 3, 4};
		EXPECT_EQ(1, v.r());
		EXPECT_EQ(2, v.g());
		EXPECT_EQ(3, v.b());
		EXPECT_EQ(4, v.a());

		v.r() = -3;
		v.g() =  4;
		v.b() = -5;
		v.a() =  6;

		EXPECT_EQ(-3, v.r());
		EXPECT_EQ( 4, v.g());
		EXPECT_EQ(-5, v.b());
		EXPECT_EQ( 6, v.a());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.r());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.g());
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.b());
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.a());
	}
}

TYPED_TEST(MathColor4Test, SwizzleTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Color4 v(1, 2, 3, 4);

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 1), v.rrrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 2), v.rrrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 3), v.rrrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 4), v.rrra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 1), v.rrgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 2), v.rrgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 3), v.rrgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 4), v.rrga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 1), v.rrbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 2), v.rrbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 3), v.rrbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 4), v.rrba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 1), v.rrar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 2), v.rrag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 3), v.rrab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 4), v.rraa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 1), v.rgrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 2), v.rgrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 3), v.rgrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 4), v.rgra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 1), v.rggr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 2), v.rggg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 3), v.rggb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 4), v.rgga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 1), v.rgbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 2), v.rgbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 3), v.rgbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 4), v.rgba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 1), v.rgar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 2), v.rgag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 3), v.rgab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 4), v.rgaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 1), v.rbrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 2), v.rbrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 3), v.rbrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 4), v.rbra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 1), v.rbgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 2), v.rbgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 3), v.rbgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 4), v.rbga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 1), v.rbbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 2), v.rbbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 3), v.rbbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 4), v.rbba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 1), v.rbar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 2), v.rbag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 3), v.rbab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 4), v.rbaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 1), v.rarr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 2), v.rarg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 3), v.rarb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 4), v.rara());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 1), v.ragr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 2), v.ragg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 3), v.ragb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 4), v.raga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 1), v.rabr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 2), v.rabg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 3), v.rabb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 4), v.raba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 1), v.raar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 2), v.raag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 3), v.raab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 4), v.raaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 1), v.grrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 2), v.grrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 3), v.grrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 4), v.grra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 1), v.grgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 2), v.grgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 3), v.grgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 4), v.grga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 1), v.grbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 2), v.grbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 3), v.grbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 4), v.grba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 1), v.grar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 2), v.grag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 3), v.grab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 4), v.graa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 1), v.ggrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 2), v.ggrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 3), v.ggrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 4), v.ggra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 1), v.gggr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 2), v.gggg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 3), v.gggb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 4), v.ggga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 1), v.ggbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 2), v.ggbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 3), v.ggbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 4), v.ggba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 1), v.ggar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 2), v.ggag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 3), v.ggab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 4), v.ggaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 1), v.gbrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 2), v.gbrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 3), v.gbrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 4), v.gbra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 1), v.gbgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 2), v.gbgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 3), v.gbgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 4), v.gbga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 1), v.gbbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 2), v.gbbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 3), v.gbbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 4), v.gbba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 1), v.gbar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 2), v.gbag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 3), v.gbab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 4), v.gbaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 1), v.garr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 2), v.garg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 3), v.garb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 4), v.gara());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 1), v.gagr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 2), v.gagg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 3), v.gagb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 4), v.gaga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 1), v.gabr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 2), v.gabg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 3), v.gabb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 4), v.gaba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 1), v.gaar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 2), v.gaag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 3), v.gaab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 4), v.gaaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 1), v.brrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 2), v.brrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 3), v.brrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 4), v.brra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 1), v.brgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 2), v.brgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 3), v.brgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 4), v.brga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 1), v.brbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 2), v.brbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 3), v.brbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 4), v.brba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 1), v.brar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 2), v.brag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 3), v.brab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 4), v.braa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 1), v.bgrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 2), v.bgrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 3), v.bgrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 4), v.bgra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 1), v.bggr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 2), v.bggg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 3), v.bggb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 4), v.bgga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 1), v.bgbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 2), v.bgbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 3), v.bgbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 4), v.bgba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 1), v.bgar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 2), v.bgag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 3), v.bgab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 4), v.bgaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 1), v.bbrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 2), v.bbrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 3), v.bbrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 4), v.bbra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 1), v.bbgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 2), v.bbgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 3), v.bbgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 4), v.bbga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 1), v.bbbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 2), v.bbbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 3), v.bbbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 4), v.bbba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 1), v.bbar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 2), v.bbag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 3), v.bbab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 4), v.bbaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 1), v.barr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 2), v.barg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 3), v.barb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 4), v.bara());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 1), v.bagr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 2), v.bagg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 3), v.bagb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 4), v.baga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 1), v.babr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 2), v.babg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 3), v.babb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 4), v.baba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 1), v.baar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 2), v.baag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 3), v.baab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 4), v.baaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 1), v.arrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 2), v.arrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 3), v.arrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 4), v.arra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 1), v.argr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 2), v.argg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 3), v.argb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 4), v.arga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 1), v.arbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 2), v.arbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 3), v.arbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 4), v.arba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 1), v.arar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 2), v.arag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 3), v.arab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 4), v.araa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 1), v.agrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 2), v.agrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 3), v.agrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 4), v.agra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 1), v.aggr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 2), v.aggg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 3), v.aggb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 4), v.agga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 1), v.agbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 2), v.agbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 3), v.agbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 4), v.agba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 1), v.agar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 2), v.agag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 3), v.agab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 4), v.agaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 1), v.abrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 2), v.abrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 3), v.abrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 4), v.abra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 1), v.abgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 2), v.abgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 3), v.abgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 4), v.abga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 1), v.abbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 2), v.abbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 3), v.abbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 4), v.abba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 1), v.abar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 2), v.abag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 3), v.abab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 4), v.abaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 1), v.aarr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 2), v.aarg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 3), v.aarb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 4), v.aara());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 1), v.aagr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 2), v.aagg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 3), v.aagb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 4), v.aaga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 1), v.aabr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 2), v.aabg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 3), v.aabb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 4), v.aaba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 1), v.aaar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 2), v.aaag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 3), v.aaab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 4), v.aaaa());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 1), v.rrr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 2), v.rrg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 3), v.rrb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 4), v.rra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 1), v.rgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 2), v.rgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 3), v.rgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 4), v.rga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 1), v.rbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 2), v.rbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 3), v.rbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 4), v.rba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 1), v.rar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 2), v.rag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 3), v.rab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 4), v.raa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 1), v.grr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 2), v.grg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 3), v.grb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 4), v.gra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 1), v.ggr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 2), v.ggg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 3), v.ggb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 4), v.gga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 1), v.gbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 2), v.gbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 3), v.gbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 4), v.gba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 1), v.gar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 2), v.gag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 3), v.gab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 4), v.gaa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 1), v.brr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 2), v.brg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 3), v.brb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 4), v.bra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 1), v.bgr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 2), v.bgg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 3), v.bgb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 4), v.bga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 1), v.bbr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 2), v.bbg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 3), v.bbb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 4), v.bba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 1), v.bar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 2), v.bag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 3), v.bab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 4), v.baa());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 1), v.arr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 2), v.arg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 3), v.arb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 4), v.ara());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 1), v.agr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 2), v.agg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 3), v.agb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 4), v.aga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 1), v.abr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 2), v.abg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 3), v.abb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 4), v.aba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 1), v.aar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 2), v.aag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 3), v.aab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 4), v.aaa());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 1), v.rr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 2), v.rg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 3), v.rb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 4), v.ra());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 1), v.gr());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 2), v.gg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 3), v.gb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 4), v.ga());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 1), v.br());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 2), v.bg());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 3), v.bb());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 4), v.ba());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 1), v.ar());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 2), v.ag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 3), v.ab());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 4), v.aa());
}

TYPED_TEST(MathColor4Test, SwapTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	Color4 v1{11, 12, 13, 14};
	Color4 v2{21, 22, 23, 24};

	EXPECT_EQ(Color4(11, 12, 13, 14), v1);
	EXPECT_EQ(Color4(21, 22, 23, 24), v2);

	v1.swap(v2);

	EXPECT_EQ(Color4(21, 22, 23, 24), v1);
	EXPECT_EQ(Color4(11, 12, 13, 14), v2);

	swap(v1, v2);

	EXPECT_EQ(Color4(11, 12, 13, 14), v1);
	EXPECT_EQ(Color4(21, 22, 23, 24), v2);
}

TYPED_TEST(MathColor4Test, PlusMinusTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	{
		Color4 v1(-1, 2, -3, 4);
		Color4 v3 = +v1;
		Color4 v4 = -v1;

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
		BKSGE_CONSTEXPR_OR_CONST Color4 v2(3, -4, 5, -6);
		BKSGE_CONSTEXPR_OR_CONST Color4 v5 = +v2;
		BKSGE_CONSTEXPR_OR_CONST Color4 v6 = -v2;

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

TYPED_TEST(MathColor4Test, AddTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	// Color4 += Color4
	{
		Color4 v;
		Color4 t = (v += Color4(2, 3, -4, 5));
		EXPECT_EQ(Color4(2, 3, -4, 5), v);
		EXPECT_EQ(t, v);
	}

	// Color4 + Color4 -> Color4
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 t =
			Color4(-3, 4, 5, 6) + Color4(0, 2, -1, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(-3, 6, 4, 9), t);
	}
}

TYPED_TEST(MathColor4Test, SubTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	// Color4 -= Color4
	{
		Color4 v;
		Color4 t = (v -= Color4(2, 3, -4, 5));
		EXPECT_EQ(Color4(-2, -3, 4, -5), v);
		EXPECT_EQ(t, v);
	}

	// Color4 - Color4 -> Color4
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 t =
			Color4(-3, 4, 5, 6) - Color4(0, 2, -1, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(-3, 2, 6, 3), t);
	}
}

TYPED_TEST(MathColor4Test, MulScalarTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	// Color4 *= スカラー
	{
		Color4 v(2, 3, 4, 5);
		{
			Color4 t = (v *= 4);
			EXPECT_EQ(Color4(8, 12, 16, 20), v);
			EXPECT_EQ(t, v);
		}
		{
			Color4 t = (v *= 0.5);
			EXPECT_EQ(Color4(4, 6, 8, 10), v);
			EXPECT_EQ(t, v);
		}
	}

	// Color4 * スカラー -> Color4
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 t = Color4(-3, 42, 5, 4) * -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(12, -168, -20, -16), t);
	}
	{
		const Color4 t = Color4(4, 6, 2, -10) * 2.5;
		EXPECT_EQ(Color4(10, 15, 5, -25), t);
	}
	// スカラー * Color4 -> Color4
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 t = 5 * Color4(7, -8, 9, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(35, -40, 45, 10), t);
	}
	{
		const Color4 t = -1.5 * Color4(4, -6, -2, 8);
		EXPECT_EQ(Color4(-6, 9, 3, -12), t);
	}
}

TYPED_TEST(MathColor4Test, MulColor4Test)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	// Color4 *= Color4
	{
		Color4 v(2, 3, 4, 5);

		auto t = (v *= Color4(-1, 2, -3, 4));
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		EXPECT_EQ(Color4(-2, 6, -12, 20), v);
		EXPECT_EQ(t, v);
	}

	// Color4 * Color4 -> Color4
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Color4(-3, 4, 5, 6) * Color4(0, 2, -1, -2);
		static_assert(bksge::is_same<decltype(t), const Color4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(0, 8, -5, -12), t);
	}
}

TYPED_TEST(MathColor4Test, DivScalarTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	// Color4 /= スカラー
	{
		Color4 v(2, 4, 6, 8);
		{
			Color4 t = (v /= 2);
			EXPECT_EQ(Color4(1, 2, 3, 4), v);
			EXPECT_EQ(t, v);
		}
		{
			Color4 t = (v /= 0.5);
			EXPECT_EQ(Color4(2, 4, 6, 8), v);
			EXPECT_EQ(t, v);
		}
	}

	// Color4 / スカラー -> Color4
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 t = Color4(-4, 8, -12, 16) / -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(1, -2, 3, -4), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 t = Color4(-4, 8, -12, 16) / 0.25;
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(-16, 32, -48, 64), t);
	}
}

TYPED_TEST(MathColor4Test, DivColor4Test)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	// Color4 /= Color4
	{
		Color4 v(8, 12, 16, 15);

		auto t = (v /= Color4(-1, 2, -4, 5));
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		EXPECT_EQ(Color4(-8, 6, -4, 3), v);
		EXPECT_EQ(t, v);
	}

	// Color4 / Color4 -> Color4
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Color4(-3, 4, 5, 6) / Color4(1, 2, -1, 3);
		static_assert(bksge::is_same<decltype(t), const Color4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(-3, 2, -5, 2), t);
	}
}

TYPED_TEST(MathColor4Test, CompareTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	BKSGE_CONSTEXPR_OR_CONST Color4 v1(1, 2, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Color4 v2(1, 2, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Color4 v3(2, 2, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Color4 v4(1, 0, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Color4 v5(1, 2, 2, 4);
	BKSGE_CONSTEXPR_OR_CONST Color4 v6(1, 2, 3, 5);

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

TYPED_TEST(MathColor4Test, OutputStreamTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	{
		Color4 const v{1, -2, 3, 4};
		bksge::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2, 3, 4 }", ss.str());
	}
	{
		Color4 const v{-10, 9, 8, -7};
		bksge::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9, 8, -7 }", ss.str());
	}
}

TYPED_TEST(MathColor4Test, TupleElementTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	static_assert(bksge::is_same<typename std::tuple_element<0, Color4>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<1, Color4>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<2, Color4>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<3, Color4>::type, T>::value, "");
}

TYPED_TEST(MathColor4Test, TupleGetTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	{
		Color4 v{1, 2, 3, 4};

		EXPECT_EQ(1, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));
		EXPECT_EQ(4, bksge::get<3>(v));

		bksge::get<0>(v) = 5;
		bksge::get<3>(v) = 6;

		EXPECT_EQ(Color4(5, 2, 3, 6), v);
		EXPECT_EQ(5, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));
		EXPECT_EQ(6, bksge::get<3>(v));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v{1, 2, 3, 4};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::get<2>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::get<3>(v));
	}
}

TYPED_TEST(MathColor4Test, TupleSizeTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	static_assert(std::tuple_size<Color4>::value == 4, "");
}

TYPED_TEST(MathColor4Test, ZeroTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = Color4::Zero();
		static_assert(bksge::is_same<decltype(v), const Color4>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(0, 0, 0, 0), v);
	}
	{
		const auto v = Color4::Zero();
		static_assert(bksge::is_same<decltype(v), const Color4>::value, "");
		EXPECT_EQ(Color4(0, 0, 0, 0), v);
	}
}

TYPED_TEST(MathColor4FloatTest, LerpTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v1 {  0,  0,  0,  0 };
		BKSGE_CONSTEXPR_OR_CONST Color4 v2 { 10, 20, 30, 40 };

		BKSGE_CONSTEXPR_EXPECT_EQ(Color4( 0.0,  0.0,  0.0,  0.0), Lerp(v1, v2, 0.00f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4( 2.5,  5.0,  7.5, 10.0), Lerp(v1, v2, 0.25f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4( 5.0, 10.0, 15.0, 20.0), Lerp(v1, v2, 0.50f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4( 7.5, 15.0, 22.5, 30.0), Lerp(v1, v2, 0.75f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(10.0, 20.0, 30.0, 40.0), Lerp(v1, v2, 1.00f));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v1 { -10,  10,  20, -30 };
		BKSGE_CONSTEXPR_OR_CONST Color4 v2 {  10, -20, -30,  40 };

		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(-10.0,  10.0,  20.0, -30.0), Lerp(v1, v2, 0.00));
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4( -5.0,   2.5,   7.5, -12.5), Lerp(v1, v2, 0.25));
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(  0.0,  -5.0,  -5.0,   5.0), Lerp(v1, v2, 0.50));
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4(  5.0, -12.5, -17.5,  22.5), Lerp(v1, v2, 0.75));
		BKSGE_CONSTEXPR_EXPECT_EQ(Color4( 10.0, -20.0, -30.0,  40.0), Lerp(v1, v2, 1.00));
	}
}

TYPED_TEST(MathColor4Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::Color4<T> const v { 1, 2, -3, 4 };

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

TYPED_TEST(MathColor4Test, HashTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	std::hash<Color4> h;

	Color4 const c1(1, 2, 3, 4);
	Color4 const c2(2, 2, 3, 4);
	Color4 const c3(1, 0, 3, 4);
	Color4 const c4(1, 2, 2, 4);
	Color4 const c5(1, 2, 3, 0);

	std::vector<bksge::size_t> v;
	v.push_back(h(c1));
	v.push_back(h(c2));
	v.push_back(h(c3));
	v.push_back(h(c4));
	v.push_back(h(c5));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(c1));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace color4_test

}	// namespace bksge_math_test
