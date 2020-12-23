/**
 *	@file	unit_test_core_math_color4.cpp
 *
 *	@brief	Color4 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/color4.hpp>
#include <bksge/core/math/color3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/cstdint/uint8_t.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"
#include "math_test_utility.hpp"

namespace bksge_math_test
{

namespace color4_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Color4f = bksge::math::Color4<float>;
using Color4i = bksge::math::Color4<int>;


using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathColor4Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathColor4Test, MathTestTypes);

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
		BKSGE_CONSTEXPR_OR_CONST Color4 v = {};
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
	static_assert( bksge::is_constructible<Color4, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color4, T, T, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Color4, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color4, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color4, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Color4, T>::value, "");
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
		BKSGE_CONSTEXPR_EXPECT_EQ( 9, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color4 v{13};
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[3]);
	}
}

TYPED_TEST(MathColor4Test, Color3ConstructTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;
	using Color3 = bksge::math::Color3<T>;

	static_assert(!bksge::is_constructible<Color4, Color3, T, T>::value, "");
	static_assert( bksge::is_constructible<Color4, Color3, T>::value, "");
	static_assert(!bksge::is_constructible<Color4, Color3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color4, Color3, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Color4, Color3, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color4, Color3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color4, Color3, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Color4, Color3, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color4, Color3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v1(1, 2, 3);
		BKSGE_CONSTEXPR_OR_CONST Color4 v2(v1, 4);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v1(2, 3, 4);
		BKSGE_CONSTEXPR_OR_CONST Color4 v2{v1, 5};
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v2[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v1(3, 4, 5);
		BKSGE_CONSTEXPR_OR_CONST Color4 v2 = {v1, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v2[3]);
	}
}

TYPED_TEST(MathColor4Test, CopyConstructTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	static_assert(bksge::is_constructible<Color4,  Color4  const&>::value, "");
	static_assert(bksge::is_constructible<Color4,  Color4i const&>::value, "");
	static_assert(bksge::is_constructible<Color4,  Color4f const&>::value, "");
	static_assert(bksge::is_constructible<Color4i, Color4  const&>::value, "");
	static_assert(bksge::is_constructible<Color4i, Color4i const&>::value, "");
	static_assert(bksge::is_constructible<Color4i, Color4f const&>::value, "");
	static_assert(bksge::is_constructible<Color4f, Color4  const&>::value, "");
	static_assert(bksge::is_constructible<Color4f, Color4i const&>::value, "");
	static_assert(bksge::is_constructible<Color4f, Color4f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Color4,  Color4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4,  Color4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4,  Color4f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4i, Color4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4i, Color4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4i, Color4f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4f, Color4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4f, Color4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4f, Color4f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Color4,  Color4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4,  Color4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4,  Color4f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4i, Color4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4i, Color4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4i, Color4f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4f, Color4  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4f, Color4i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4f, Color4f const&>::value, "");

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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ConvertConstructTest()
{
	using Color4 = bksge::math::Color4<T>;
	using Color4u8 = bksge::math::Color4<bksge::uint8_t>;

	static_assert(bksge::is_constructible<Color4,   Color4u8 const&>::value, "");
	static_assert(bksge::is_constructible<Color4u8, Color4   const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4,   Color4u8 const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color4u8, Color4   const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4,   Color4u8 const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color4u8, Color4   const&>::value, "");

	{
		Color4u8 const v1(0, 128, 255, 160);
		Color4   const v2(v1);
		double error = 0.0000001;
		VERIFY(IsNear(0.00000000000000000, (double)v2[0], error));
		VERIFY(IsNear(0.50196078431372548, (double)v2[1], error));
		VERIFY(IsNear(1.00000000000000000, (double)v2[2], error));
		VERIFY(IsNear(0.62745100259780884, (double)v2[3], error));
	}
	{
		Color4u8 const v1(32, 64, 192, 225);
		Color4   const v2(v1);
		double error = 0.0000001;
		VERIFY(IsNear(0.12549019607843137, (double)v2[0], error));
		VERIFY(IsNear(0.25098039215686274, (double)v2[1], error));
		VERIFY(IsNear(0.75294117647058822, (double)v2[2], error));
		VERIFY(IsNear(0.88235294818878174, (double)v2[3], error));
	}
	{
		Color4   const v1(0.5, 1.0, 0.0, 0.25);
		Color4u8 const v2(v1);
		VERIFY(127 == v2[0]);
		VERIFY(255 == v2[1]);
		VERIFY(  0 == v2[2]);
		VERIFY( 63 == v2[3]);
	}
	{
		Color4   const v1(0.25, 0.75, 0.125, 0.375);
		Color4u8 const v2(v1);
		VERIFY( 63 == v2[0]);
		VERIFY(191 == v2[1]);
		VERIFY( 31 == v2[2]);
		VERIFY( 95 == v2[3]);
	}

	return true;
}

TYPED_TEST(MathColor4Test, ConvertConstructTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ConvertConstructTest<TypeParam>());
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Color4 = bksge::math::Color4<T>;

	const double error = 0.0000001;

	Color4 v1(0, 1, 2, -2);
	Color4 v2(3, 4, 5, 6);
	VERIFY( 0 == v1[0]);
	VERIFY( 1 == v1[1]);
	VERIFY( 2 == v1[2]);
	VERIFY(-2 == v1[3]);
	VERIFY( 3 == v2[0]);
	VERIFY( 4 == v2[1]);
	VERIFY( 5 == v2[2]);
	VERIFY( 6 == v2[3]);

	v1 = Color4(6, -7, 8, 9);
	v2 = Color4i(16, 32, 64, 128);
	VERIFY( 6 == v1[0]);
	VERIFY(-7 == v1[1]);
	VERIFY( 8 == v1[2]);
	VERIFY( 9 == v1[3]);
	VERIFY(IsNear(0.06274510174989700, (double)v2[0], error));
	VERIFY(IsNear(0.12549019607843137, (double)v2[1], error));
	VERIFY(IsNear(0.25098039215686274, (double)v2[2], error));
	VERIFY(IsNear(0.50196078431372548, (double)v2[3], error));

	// 自己代入
	v1 = v1;
	v2 = v2;
	VERIFY( 6 == v1[0]);
	VERIFY(-7 == v1[1]);
	VERIFY( 8 == v1[2]);
	VERIFY( 9 == v1[3]);
	VERIFY(IsNear(0.06274510174989700, (double)v2[0], error));
	VERIFY(IsNear(0.12549019607843137, (double)v2[1], error));
	VERIFY(IsNear(0.25098039215686274, (double)v2[2], error));
	VERIFY(IsNear(0.50196078431372548, (double)v2[3], error));

	// 多重代入
	v1 = v2 = Color4f(4, 5, 6, 7);
	VERIFY(4 == v1[0]);
	VERIFY(5 == v1[1]);
	VERIFY(6 == v1[2]);
	VERIFY(7 == v1[3]);
	VERIFY(4 == v2[0]);
	VERIFY(5 == v2[1]);
	VERIFY(6 == v2[2]);
	VERIFY(7 == v2[3]);

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathColor4Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Color4 = bksge::math::Color4<T>;
	{
		Color4 v{1, 2, 3, 4};
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
		VERIFY(v[3] == 4);

		v[0] = -3;
		v[1] =  4;
		v[2] = -5;
		v[3] =  6;

		VERIFY(v[0] == -3);
		VERIFY(v[1] ==  4);
		VERIFY(v[2] == -5);
		VERIFY(v[3] ==  6);
	}
	{
		Color4 const v{5, 6, 7, 8};
		VERIFY(v[0] == 5);
		VERIFY(v[1] == 6);
		VERIFY(v[2] == 7);
		VERIFY(v[3] == 8);
	}
	return true;
}

TYPED_TEST(MathColor4Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Color4 = bksge::math::Color4<T>;
	{
		Color4 v{1, 2, 3, 4};
		VERIFY(v.at(0) == 1);
		VERIFY(v.at(1) == 2);
		VERIFY(v.at(2) == 3);
		VERIFY(v.at(3) == 4);

		v.at(0) = -3;
		v.at(1) =  4;
		v.at(2) = -5;
		v.at(3) =  6;

		VERIFY(v.at(0) == -3);
		VERIFY(v.at(1) ==  4);
		VERIFY(v.at(2) == -5);
		VERIFY(v.at(3) ==  6);
	}
	{
		Color4 const v{5, 6, 7, 8};
		VERIFY(v.at(0) == 5);
		VERIFY(v.at(1) == 6);
		VERIFY(v.at(2) == 7);
		VERIFY(v.at(3) == 8);
	}
	return true;
}

TYPED_TEST(MathColor4Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Color4 = bksge::math::Color4<TypeParam>;
	{
		Color4 v{1, 2, 3, 4};
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
	{
		Color4 const v{5, 6, 7, 8};
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Color4 = bksge::math::Color4<T>;
	{
		Color4 v{1, 2, 3, 4};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == 1);
		*p = 5;
		++p;
		VERIFY(*p == 2);
		p++;
		VERIFY(*p == 3);
		*p = 6;
		++p;
		VERIFY(*p == 4);

		VERIFY(v == Color4(5, 2, 6, 4));
	}
	{
		Color4 const v{1, 2, 3, 4};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == 1);
		++p;
		VERIFY(*p == 2);
		p++;
		VERIFY(*p == 3);
		++p;
		VERIFY(*p == 4);
	}
	return true;
}

TYPED_TEST(MathColor4Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Color4 = bksge::math::Color4<T>;

	// begin, end (non const)
	{
		Color4 v{1, 2, 3, 4};
		auto it = v.begin();
		VERIFY(it != v.end());
		VERIFY(*it == 1);
		*it++ = 5;
		VERIFY(it != v.end());
		VERIFY(*it == 2);
		*++it = 6;
		VERIFY(it != v.end());
		VERIFY(*it == 6);
		it++;
		VERIFY(it != v.end());
		VERIFY(*it == 4);
		it++;
		VERIFY(it == v.end());

		VERIFY(Color4(5, 2, 6, 4) == v);
	}
	// begin, end (const)
	{
		Color4 const v{1, 2, 3, 4};
		auto it = v.begin();
		VERIFY(it != v.end());

		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 3);
		VERIFY(it[3] == 4);

		VERIFY(*it++ == 1);
		VERIFY(it != v.end());
		VERIFY(*++it == 3);
		VERIFY(it != v.end());
		VERIFY(*it++ == 3);
		VERIFY(it != v.end());
		VERIFY(*it++ == 4);
		VERIFY(it == v.end());
	}
	// cbegin, cend
	{
		Color4 v{1, 2, 3, 4};
		auto it = v.cbegin();
		VERIFY(it != v.cend());

		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 3);
		VERIFY(it[3] == 4);

		VERIFY(*it++ == 1);
		VERIFY(it != v.cend());
		VERIFY(*++it == 3);
		VERIFY(it != v.cend());
		VERIFY(*it++ == 3);
		VERIFY(it != v.cend());
		VERIFY(*it++ == 4);
		VERIFY(it == v.cend());
	}
	return true;
}

TYPED_TEST(MathColor4Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Color4 = bksge::math::Color4<T>;

	// rbegin, rend (non const)
	{
		Color4 v{1, 2, 3, 4};
		auto it = v.rbegin();
		VERIFY(it != v.rend());
		VERIFY(*it == 4);
		*it++ = 5;
		VERIFY(it != v.rend());
		VERIFY(*it == 3);
		*++it = 6;
		VERIFY(it != v.rend());
		VERIFY(*it == 6);
		it++;
		VERIFY(it != v.rend());
		VERIFY(*it == 1);
		it++;
		VERIFY(it == v.rend());

		VERIFY(Color4(1, 6, 3, 5) == v);
	}
	// rbegin, rend (const)
	{
		Color4 const v{1, 2, 3, 4};
		auto it = v.rbegin();
		VERIFY(it != v.rend());

		VERIFY(it[0] == 4);
		VERIFY(it[1] == 3);
		VERIFY(it[2] == 2);
		VERIFY(it[3] == 1);

		VERIFY(*it++ == 4);
		VERIFY(it != v.rend());
		VERIFY(*++it == 2);
		VERIFY(it != v.rend());
		VERIFY(*it++ == 2);
		VERIFY(it != v.rend());
		VERIFY(*it++ == 1);
		VERIFY(it == v.rend());
	}
	// crbegin, crend
	{
		Color4 v{1, 2, 3, 4};
		auto it = v.crbegin();
		VERIFY(it != v.crend());

		VERIFY(it[0] == 4);
		VERIFY(it[1] == 3);
		VERIFY(it[2] == 2);
		VERIFY(it[3] == 1);

		VERIFY(*it++ == 4);
		VERIFY(it != v.crend());
		VERIFY(*++it == 2);
		VERIFY(it != v.crend());
		VERIFY(*it++ == 2);
		VERIFY(it != v.crend());
		VERIFY(*it++ == 1);
		VERIFY(it == v.crend());
	}
	return true;
}

TYPED_TEST(MathColor4Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Color4 = bksge::math::Color4<T>;
	Color4 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathColor4Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Color4 = bksge::math::Color4<T>;
	Color4 v1{};
	VERIFY(v1.size() == 4);
	return true;
}

TYPED_TEST(MathColor4Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Color4 = bksge::math::Color4<T>;
	Color4 v1{};
	VERIFY(v1.max_size() == 4);
	return true;
}

TYPED_TEST(MathColor4Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Color4 = bksge::math::Color4<T>;
	{
		Color4 v{1, 2, 3, 4};
		VERIFY(v.r() == 1);
		VERIFY(v.g() == 2);
		VERIFY(v.b() == 3);
		VERIFY(v.a() == 4);

		v.r() = -3;
		v.g() =  4;
		v.b() = -5;
		v.a() =  6;

		VERIFY(v.r() == -3);
		VERIFY(v.g() ==  4);
		VERIFY(v.b() == -5);
		VERIFY(v.a() ==  6);
	}
	{
		Color4 const v{5, 6, 7, 8};
		VERIFY(v.r() == 5);
		VERIFY(v.g() == 6);
		VERIFY(v.b() == 7);
		VERIFY(v.a() == 8);
	}
	return true;
}

TYPED_TEST(MathColor4Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Color4 = bksge::math::Color4<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	Color4 v(1, 2, 3, 4);

	static_assert(bksge::is_same<decltype(v.rrrr()), Vector4>::value, "");
	static_assert(bksge::is_same<decltype(v.rrr()), Vector3>::value, "");
	static_assert(bksge::is_same<decltype(v.rr()), Vector2>::value, "");

	VERIFY(Vector4(1, 1, 1, 1) == v.rrrr());
	VERIFY(Vector4(1, 1, 1, 2) == v.rrrg());
	VERIFY(Vector4(1, 1, 1, 3) == v.rrrb());
	VERIFY(Vector4(1, 1, 1, 4) == v.rrra());
	VERIFY(Vector4(1, 1, 2, 1) == v.rrgr());
	VERIFY(Vector4(1, 1, 2, 2) == v.rrgg());
	VERIFY(Vector4(1, 1, 2, 3) == v.rrgb());
	VERIFY(Vector4(1, 1, 2, 4) == v.rrga());
	VERIFY(Vector4(1, 1, 3, 1) == v.rrbr());
	VERIFY(Vector4(1, 1, 3, 2) == v.rrbg());
	VERIFY(Vector4(1, 1, 3, 3) == v.rrbb());
	VERIFY(Vector4(1, 1, 3, 4) == v.rrba());
	VERIFY(Vector4(1, 1, 4, 1) == v.rrar());
	VERIFY(Vector4(1, 1, 4, 2) == v.rrag());
	VERIFY(Vector4(1, 1, 4, 3) == v.rrab());
	VERIFY(Vector4(1, 1, 4, 4) == v.rraa());
	VERIFY(Vector4(1, 2, 1, 1) == v.rgrr());
	VERIFY(Vector4(1, 2, 1, 2) == v.rgrg());
	VERIFY(Vector4(1, 2, 1, 3) == v.rgrb());
	VERIFY(Vector4(1, 2, 1, 4) == v.rgra());
	VERIFY(Vector4(1, 2, 2, 1) == v.rggr());
	VERIFY(Vector4(1, 2, 2, 2) == v.rggg());
	VERIFY(Vector4(1, 2, 2, 3) == v.rggb());
	VERIFY(Vector4(1, 2, 2, 4) == v.rgga());
	VERIFY(Vector4(1, 2, 3, 1) == v.rgbr());
	VERIFY(Vector4(1, 2, 3, 2) == v.rgbg());
	VERIFY(Vector4(1, 2, 3, 3) == v.rgbb());
	VERIFY(Vector4(1, 2, 3, 4) == v.rgba());
	VERIFY(Vector4(1, 2, 4, 1) == v.rgar());
	VERIFY(Vector4(1, 2, 4, 2) == v.rgag());
	VERIFY(Vector4(1, 2, 4, 3) == v.rgab());
	VERIFY(Vector4(1, 2, 4, 4) == v.rgaa());
	VERIFY(Vector4(1, 3, 1, 1) == v.rbrr());
	VERIFY(Vector4(1, 3, 1, 2) == v.rbrg());
	VERIFY(Vector4(1, 3, 1, 3) == v.rbrb());
	VERIFY(Vector4(1, 3, 1, 4) == v.rbra());
	VERIFY(Vector4(1, 3, 2, 1) == v.rbgr());
	VERIFY(Vector4(1, 3, 2, 2) == v.rbgg());
	VERIFY(Vector4(1, 3, 2, 3) == v.rbgb());
	VERIFY(Vector4(1, 3, 2, 4) == v.rbga());
	VERIFY(Vector4(1, 3, 3, 1) == v.rbbr());
	VERIFY(Vector4(1, 3, 3, 2) == v.rbbg());
	VERIFY(Vector4(1, 3, 3, 3) == v.rbbb());
	VERIFY(Vector4(1, 3, 3, 4) == v.rbba());
	VERIFY(Vector4(1, 3, 4, 1) == v.rbar());
	VERIFY(Vector4(1, 3, 4, 2) == v.rbag());
	VERIFY(Vector4(1, 3, 4, 3) == v.rbab());
	VERIFY(Vector4(1, 3, 4, 4) == v.rbaa());
	VERIFY(Vector4(1, 4, 1, 1) == v.rarr());
	VERIFY(Vector4(1, 4, 1, 2) == v.rarg());
	VERIFY(Vector4(1, 4, 1, 3) == v.rarb());
	VERIFY(Vector4(1, 4, 1, 4) == v.rara());
	VERIFY(Vector4(1, 4, 2, 1) == v.ragr());
	VERIFY(Vector4(1, 4, 2, 2) == v.ragg());
	VERIFY(Vector4(1, 4, 2, 3) == v.ragb());
	VERIFY(Vector4(1, 4, 2, 4) == v.raga());
	VERIFY(Vector4(1, 4, 3, 1) == v.rabr());
	VERIFY(Vector4(1, 4, 3, 2) == v.rabg());
	VERIFY(Vector4(1, 4, 3, 3) == v.rabb());
	VERIFY(Vector4(1, 4, 3, 4) == v.raba());
	VERIFY(Vector4(1, 4, 4, 1) == v.raar());
	VERIFY(Vector4(1, 4, 4, 2) == v.raag());
	VERIFY(Vector4(1, 4, 4, 3) == v.raab());
	VERIFY(Vector4(1, 4, 4, 4) == v.raaa());
	VERIFY(Vector4(2, 1, 1, 1) == v.grrr());
	VERIFY(Vector4(2, 1, 1, 2) == v.grrg());
	VERIFY(Vector4(2, 1, 1, 3) == v.grrb());
	VERIFY(Vector4(2, 1, 1, 4) == v.grra());
	VERIFY(Vector4(2, 1, 2, 1) == v.grgr());
	VERIFY(Vector4(2, 1, 2, 2) == v.grgg());
	VERIFY(Vector4(2, 1, 2, 3) == v.grgb());
	VERIFY(Vector4(2, 1, 2, 4) == v.grga());
	VERIFY(Vector4(2, 1, 3, 1) == v.grbr());
	VERIFY(Vector4(2, 1, 3, 2) == v.grbg());
	VERIFY(Vector4(2, 1, 3, 3) == v.grbb());
	VERIFY(Vector4(2, 1, 3, 4) == v.grba());
	VERIFY(Vector4(2, 1, 4, 1) == v.grar());
	VERIFY(Vector4(2, 1, 4, 2) == v.grag());
	VERIFY(Vector4(2, 1, 4, 3) == v.grab());
	VERIFY(Vector4(2, 1, 4, 4) == v.graa());
	VERIFY(Vector4(2, 2, 1, 1) == v.ggrr());
	VERIFY(Vector4(2, 2, 1, 2) == v.ggrg());
	VERIFY(Vector4(2, 2, 1, 3) == v.ggrb());
	VERIFY(Vector4(2, 2, 1, 4) == v.ggra());
	VERIFY(Vector4(2, 2, 2, 1) == v.gggr());
	VERIFY(Vector4(2, 2, 2, 2) == v.gggg());
	VERIFY(Vector4(2, 2, 2, 3) == v.gggb());
	VERIFY(Vector4(2, 2, 2, 4) == v.ggga());
	VERIFY(Vector4(2, 2, 3, 1) == v.ggbr());
	VERIFY(Vector4(2, 2, 3, 2) == v.ggbg());
	VERIFY(Vector4(2, 2, 3, 3) == v.ggbb());
	VERIFY(Vector4(2, 2, 3, 4) == v.ggba());
	VERIFY(Vector4(2, 2, 4, 1) == v.ggar());
	VERIFY(Vector4(2, 2, 4, 2) == v.ggag());
	VERIFY(Vector4(2, 2, 4, 3) == v.ggab());
	VERIFY(Vector4(2, 2, 4, 4) == v.ggaa());
	VERIFY(Vector4(2, 3, 1, 1) == v.gbrr());
	VERIFY(Vector4(2, 3, 1, 2) == v.gbrg());
	VERIFY(Vector4(2, 3, 1, 3) == v.gbrb());
	VERIFY(Vector4(2, 3, 1, 4) == v.gbra());
	VERIFY(Vector4(2, 3, 2, 1) == v.gbgr());
	VERIFY(Vector4(2, 3, 2, 2) == v.gbgg());
	VERIFY(Vector4(2, 3, 2, 3) == v.gbgb());
	VERIFY(Vector4(2, 3, 2, 4) == v.gbga());
	VERIFY(Vector4(2, 3, 3, 1) == v.gbbr());
	VERIFY(Vector4(2, 3, 3, 2) == v.gbbg());
	VERIFY(Vector4(2, 3, 3, 3) == v.gbbb());
	VERIFY(Vector4(2, 3, 3, 4) == v.gbba());
	VERIFY(Vector4(2, 3, 4, 1) == v.gbar());
	VERIFY(Vector4(2, 3, 4, 2) == v.gbag());
	VERIFY(Vector4(2, 3, 4, 3) == v.gbab());
	VERIFY(Vector4(2, 3, 4, 4) == v.gbaa());
	VERIFY(Vector4(2, 4, 1, 1) == v.garr());
	VERIFY(Vector4(2, 4, 1, 2) == v.garg());
	VERIFY(Vector4(2, 4, 1, 3) == v.garb());
	VERIFY(Vector4(2, 4, 1, 4) == v.gara());
	VERIFY(Vector4(2, 4, 2, 1) == v.gagr());
	VERIFY(Vector4(2, 4, 2, 2) == v.gagg());
	VERIFY(Vector4(2, 4, 2, 3) == v.gagb());
	VERIFY(Vector4(2, 4, 2, 4) == v.gaga());
	VERIFY(Vector4(2, 4, 3, 1) == v.gabr());
	VERIFY(Vector4(2, 4, 3, 2) == v.gabg());
	VERIFY(Vector4(2, 4, 3, 3) == v.gabb());
	VERIFY(Vector4(2, 4, 3, 4) == v.gaba());
	VERIFY(Vector4(2, 4, 4, 1) == v.gaar());
	VERIFY(Vector4(2, 4, 4, 2) == v.gaag());
	VERIFY(Vector4(2, 4, 4, 3) == v.gaab());
	VERIFY(Vector4(2, 4, 4, 4) == v.gaaa());
	VERIFY(Vector4(3, 1, 1, 1) == v.brrr());
	VERIFY(Vector4(3, 1, 1, 2) == v.brrg());
	VERIFY(Vector4(3, 1, 1, 3) == v.brrb());
	VERIFY(Vector4(3, 1, 1, 4) == v.brra());
	VERIFY(Vector4(3, 1, 2, 1) == v.brgr());
	VERIFY(Vector4(3, 1, 2, 2) == v.brgg());
	VERIFY(Vector4(3, 1, 2, 3) == v.brgb());
	VERIFY(Vector4(3, 1, 2, 4) == v.brga());
	VERIFY(Vector4(3, 1, 3, 1) == v.brbr());
	VERIFY(Vector4(3, 1, 3, 2) == v.brbg());
	VERIFY(Vector4(3, 1, 3, 3) == v.brbb());
	VERIFY(Vector4(3, 1, 3, 4) == v.brba());
	VERIFY(Vector4(3, 1, 4, 1) == v.brar());
	VERIFY(Vector4(3, 1, 4, 2) == v.brag());
	VERIFY(Vector4(3, 1, 4, 3) == v.brab());
	VERIFY(Vector4(3, 1, 4, 4) == v.braa());
	VERIFY(Vector4(3, 2, 1, 1) == v.bgrr());
	VERIFY(Vector4(3, 2, 1, 2) == v.bgrg());
	VERIFY(Vector4(3, 2, 1, 3) == v.bgrb());
	VERIFY(Vector4(3, 2, 1, 4) == v.bgra());
	VERIFY(Vector4(3, 2, 2, 1) == v.bggr());
	VERIFY(Vector4(3, 2, 2, 2) == v.bggg());
	VERIFY(Vector4(3, 2, 2, 3) == v.bggb());
	VERIFY(Vector4(3, 2, 2, 4) == v.bgga());
	VERIFY(Vector4(3, 2, 3, 1) == v.bgbr());
	VERIFY(Vector4(3, 2, 3, 2) == v.bgbg());
	VERIFY(Vector4(3, 2, 3, 3) == v.bgbb());
	VERIFY(Vector4(3, 2, 3, 4) == v.bgba());
	VERIFY(Vector4(3, 2, 4, 1) == v.bgar());
	VERIFY(Vector4(3, 2, 4, 2) == v.bgag());
	VERIFY(Vector4(3, 2, 4, 3) == v.bgab());
	VERIFY(Vector4(3, 2, 4, 4) == v.bgaa());
	VERIFY(Vector4(3, 3, 1, 1) == v.bbrr());
	VERIFY(Vector4(3, 3, 1, 2) == v.bbrg());
	VERIFY(Vector4(3, 3, 1, 3) == v.bbrb());
	VERIFY(Vector4(3, 3, 1, 4) == v.bbra());
	VERIFY(Vector4(3, 3, 2, 1) == v.bbgr());
	VERIFY(Vector4(3, 3, 2, 2) == v.bbgg());
	VERIFY(Vector4(3, 3, 2, 3) == v.bbgb());
	VERIFY(Vector4(3, 3, 2, 4) == v.bbga());
	VERIFY(Vector4(3, 3, 3, 1) == v.bbbr());
	VERIFY(Vector4(3, 3, 3, 2) == v.bbbg());
	VERIFY(Vector4(3, 3, 3, 3) == v.bbbb());
	VERIFY(Vector4(3, 3, 3, 4) == v.bbba());
	VERIFY(Vector4(3, 3, 4, 1) == v.bbar());
	VERIFY(Vector4(3, 3, 4, 2) == v.bbag());
	VERIFY(Vector4(3, 3, 4, 3) == v.bbab());
	VERIFY(Vector4(3, 3, 4, 4) == v.bbaa());
	VERIFY(Vector4(3, 4, 1, 1) == v.barr());
	VERIFY(Vector4(3, 4, 1, 2) == v.barg());
	VERIFY(Vector4(3, 4, 1, 3) == v.barb());
	VERIFY(Vector4(3, 4, 1, 4) == v.bara());
	VERIFY(Vector4(3, 4, 2, 1) == v.bagr());
	VERIFY(Vector4(3, 4, 2, 2) == v.bagg());
	VERIFY(Vector4(3, 4, 2, 3) == v.bagb());
	VERIFY(Vector4(3, 4, 2, 4) == v.baga());
	VERIFY(Vector4(3, 4, 3, 1) == v.babr());
	VERIFY(Vector4(3, 4, 3, 2) == v.babg());
	VERIFY(Vector4(3, 4, 3, 3) == v.babb());
	VERIFY(Vector4(3, 4, 3, 4) == v.baba());
	VERIFY(Vector4(3, 4, 4, 1) == v.baar());
	VERIFY(Vector4(3, 4, 4, 2) == v.baag());
	VERIFY(Vector4(3, 4, 4, 3) == v.baab());
	VERIFY(Vector4(3, 4, 4, 4) == v.baaa());
	VERIFY(Vector4(4, 1, 1, 1) == v.arrr());
	VERIFY(Vector4(4, 1, 1, 2) == v.arrg());
	VERIFY(Vector4(4, 1, 1, 3) == v.arrb());
	VERIFY(Vector4(4, 1, 1, 4) == v.arra());
	VERIFY(Vector4(4, 1, 2, 1) == v.argr());
	VERIFY(Vector4(4, 1, 2, 2) == v.argg());
	VERIFY(Vector4(4, 1, 2, 3) == v.argb());
	VERIFY(Vector4(4, 1, 2, 4) == v.arga());
	VERIFY(Vector4(4, 1, 3, 1) == v.arbr());
	VERIFY(Vector4(4, 1, 3, 2) == v.arbg());
	VERIFY(Vector4(4, 1, 3, 3) == v.arbb());
	VERIFY(Vector4(4, 1, 3, 4) == v.arba());
	VERIFY(Vector4(4, 1, 4, 1) == v.arar());
	VERIFY(Vector4(4, 1, 4, 2) == v.arag());
	VERIFY(Vector4(4, 1, 4, 3) == v.arab());
	VERIFY(Vector4(4, 1, 4, 4) == v.araa());
	VERIFY(Vector4(4, 2, 1, 1) == v.agrr());
	VERIFY(Vector4(4, 2, 1, 2) == v.agrg());
	VERIFY(Vector4(4, 2, 1, 3) == v.agrb());
	VERIFY(Vector4(4, 2, 1, 4) == v.agra());
	VERIFY(Vector4(4, 2, 2, 1) == v.aggr());
	VERIFY(Vector4(4, 2, 2, 2) == v.aggg());
	VERIFY(Vector4(4, 2, 2, 3) == v.aggb());
	VERIFY(Vector4(4, 2, 2, 4) == v.agga());
	VERIFY(Vector4(4, 2, 3, 1) == v.agbr());
	VERIFY(Vector4(4, 2, 3, 2) == v.agbg());
	VERIFY(Vector4(4, 2, 3, 3) == v.agbb());
	VERIFY(Vector4(4, 2, 3, 4) == v.agba());
	VERIFY(Vector4(4, 2, 4, 1) == v.agar());
	VERIFY(Vector4(4, 2, 4, 2) == v.agag());
	VERIFY(Vector4(4, 2, 4, 3) == v.agab());
	VERIFY(Vector4(4, 2, 4, 4) == v.agaa());
	VERIFY(Vector4(4, 3, 1, 1) == v.abrr());
	VERIFY(Vector4(4, 3, 1, 2) == v.abrg());
	VERIFY(Vector4(4, 3, 1, 3) == v.abrb());
	VERIFY(Vector4(4, 3, 1, 4) == v.abra());
	VERIFY(Vector4(4, 3, 2, 1) == v.abgr());
	VERIFY(Vector4(4, 3, 2, 2) == v.abgg());
	VERIFY(Vector4(4, 3, 2, 3) == v.abgb());
	VERIFY(Vector4(4, 3, 2, 4) == v.abga());
	VERIFY(Vector4(4, 3, 3, 1) == v.abbr());
	VERIFY(Vector4(4, 3, 3, 2) == v.abbg());
	VERIFY(Vector4(4, 3, 3, 3) == v.abbb());
	VERIFY(Vector4(4, 3, 3, 4) == v.abba());
	VERIFY(Vector4(4, 3, 4, 1) == v.abar());
	VERIFY(Vector4(4, 3, 4, 2) == v.abag());
	VERIFY(Vector4(4, 3, 4, 3) == v.abab());
	VERIFY(Vector4(4, 3, 4, 4) == v.abaa());
	VERIFY(Vector4(4, 4, 1, 1) == v.aarr());
	VERIFY(Vector4(4, 4, 1, 2) == v.aarg());
	VERIFY(Vector4(4, 4, 1, 3) == v.aarb());
	VERIFY(Vector4(4, 4, 1, 4) == v.aara());
	VERIFY(Vector4(4, 4, 2, 1) == v.aagr());
	VERIFY(Vector4(4, 4, 2, 2) == v.aagg());
	VERIFY(Vector4(4, 4, 2, 3) == v.aagb());
	VERIFY(Vector4(4, 4, 2, 4) == v.aaga());
	VERIFY(Vector4(4, 4, 3, 1) == v.aabr());
	VERIFY(Vector4(4, 4, 3, 2) == v.aabg());
	VERIFY(Vector4(4, 4, 3, 3) == v.aabb());
	VERIFY(Vector4(4, 4, 3, 4) == v.aaba());
	VERIFY(Vector4(4, 4, 4, 1) == v.aaar());
	VERIFY(Vector4(4, 4, 4, 2) == v.aaag());
	VERIFY(Vector4(4, 4, 4, 3) == v.aaab());
	VERIFY(Vector4(4, 4, 4, 4) == v.aaaa());

	VERIFY(Vector3(1, 1, 1) == v.rrr());
	VERIFY(Vector3(1, 1, 2) == v.rrg());
	VERIFY(Vector3(1, 1, 3) == v.rrb());
	VERIFY(Vector3(1, 1, 4) == v.rra());
	VERIFY(Vector3(1, 2, 1) == v.rgr());
	VERIFY(Vector3(1, 2, 2) == v.rgg());
	VERIFY(Vector3(1, 2, 3) == v.rgb());
	VERIFY(Vector3(1, 2, 4) == v.rga());
	VERIFY(Vector3(1, 3, 1) == v.rbr());
	VERIFY(Vector3(1, 3, 2) == v.rbg());
	VERIFY(Vector3(1, 3, 3) == v.rbb());
	VERIFY(Vector3(1, 3, 4) == v.rba());
	VERIFY(Vector3(1, 4, 1) == v.rar());
	VERIFY(Vector3(1, 4, 2) == v.rag());
	VERIFY(Vector3(1, 4, 3) == v.rab());
	VERIFY(Vector3(1, 4, 4) == v.raa());
	VERIFY(Vector3(2, 1, 1) == v.grr());
	VERIFY(Vector3(2, 1, 2) == v.grg());
	VERIFY(Vector3(2, 1, 3) == v.grb());
	VERIFY(Vector3(2, 1, 4) == v.gra());
	VERIFY(Vector3(2, 2, 1) == v.ggr());
	VERIFY(Vector3(2, 2, 2) == v.ggg());
	VERIFY(Vector3(2, 2, 3) == v.ggb());
	VERIFY(Vector3(2, 2, 4) == v.gga());
	VERIFY(Vector3(2, 3, 1) == v.gbr());
	VERIFY(Vector3(2, 3, 2) == v.gbg());
	VERIFY(Vector3(2, 3, 3) == v.gbb());
	VERIFY(Vector3(2, 3, 4) == v.gba());
	VERIFY(Vector3(2, 4, 1) == v.gar());
	VERIFY(Vector3(2, 4, 2) == v.gag());
	VERIFY(Vector3(2, 4, 3) == v.gab());
	VERIFY(Vector3(2, 4, 4) == v.gaa());
	VERIFY(Vector3(3, 1, 1) == v.brr());
	VERIFY(Vector3(3, 1, 2) == v.brg());
	VERIFY(Vector3(3, 1, 3) == v.brb());
	VERIFY(Vector3(3, 1, 4) == v.bra());
	VERIFY(Vector3(3, 2, 1) == v.bgr());
	VERIFY(Vector3(3, 2, 2) == v.bgg());
	VERIFY(Vector3(3, 2, 3) == v.bgb());
	VERIFY(Vector3(3, 2, 4) == v.bga());
	VERIFY(Vector3(3, 3, 1) == v.bbr());
	VERIFY(Vector3(3, 3, 2) == v.bbg());
	VERIFY(Vector3(3, 3, 3) == v.bbb());
	VERIFY(Vector3(3, 3, 4) == v.bba());
	VERIFY(Vector3(3, 4, 1) == v.bar());
	VERIFY(Vector3(3, 4, 2) == v.bag());
	VERIFY(Vector3(3, 4, 3) == v.bab());
	VERIFY(Vector3(3, 4, 4) == v.baa());
	VERIFY(Vector3(4, 1, 1) == v.arr());
	VERIFY(Vector3(4, 1, 2) == v.arg());
	VERIFY(Vector3(4, 1, 3) == v.arb());
	VERIFY(Vector3(4, 1, 4) == v.ara());
	VERIFY(Vector3(4, 2, 1) == v.agr());
	VERIFY(Vector3(4, 2, 2) == v.agg());
	VERIFY(Vector3(4, 2, 3) == v.agb());
	VERIFY(Vector3(4, 2, 4) == v.aga());
	VERIFY(Vector3(4, 3, 1) == v.abr());
	VERIFY(Vector3(4, 3, 2) == v.abg());
	VERIFY(Vector3(4, 3, 3) == v.abb());
	VERIFY(Vector3(4, 3, 4) == v.aba());
	VERIFY(Vector3(4, 4, 1) == v.aar());
	VERIFY(Vector3(4, 4, 2) == v.aag());
	VERIFY(Vector3(4, 4, 3) == v.aab());
	VERIFY(Vector3(4, 4, 4) == v.aaa());

	VERIFY(Vector2(1, 1) == v.rr());
	VERIFY(Vector2(1, 2) == v.rg());
	VERIFY(Vector2(1, 3) == v.rb());
	VERIFY(Vector2(1, 4) == v.ra());
	VERIFY(Vector2(2, 1) == v.gr());
	VERIFY(Vector2(2, 2) == v.gg());
	VERIFY(Vector2(2, 3) == v.gb());
	VERIFY(Vector2(2, 4) == v.ga());
	VERIFY(Vector2(3, 1) == v.br());
	VERIFY(Vector2(3, 2) == v.bg());
	VERIFY(Vector2(3, 3) == v.bb());
	VERIFY(Vector2(3, 4) == v.ba());
	VERIFY(Vector2(4, 1) == v.ar());
	VERIFY(Vector2(4, 2) == v.ag());
	VERIFY(Vector2(4, 3) == v.ab());
	VERIFY(Vector2(4, 4) == v.aa());

	return true;
}

TYPED_TEST(MathColor4Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Color4 = bksge::math::Color4<T>;

	Color4 v1{1, 2, 3, 4};
	Color4 v2{5, 6, 7, 8};

	v1.swap(v2);

	VERIFY(v1 == Color4(5, 6, 7, 8));
	VERIFY(v2 == Color4(1, 2, 3, 4));

	bksge::ranges::swap(v1, v2);

	VERIFY(v1 == Color4(1, 2, 3, 4));
	VERIFY(v2 == Color4(5, 6, 7, 8));

	return true;
}

TYPED_TEST(MathColor4Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Color4 = bksge::math::Color4<T>;
	{
		Color4 const v1(-1, 2, -3, 4);
		auto const v2 = +v1;
		auto const v3 = -v1;
		static_assert(bksge::is_same<decltype(v2), Color4 const>::value, "");
		static_assert(bksge::is_same<decltype(v3), Color4 const>::value, "");

		VERIFY(v2[0] == -1);
		VERIFY(v2[1] ==  2);
		VERIFY(v2[2] == -3);
		VERIFY(v2[3] ==  4);
		VERIFY(v3[0] ==  1);
		VERIFY(v3[1] == -2);
		VERIFY(v3[2] ==  3);
		VERIFY(v3[3] == -4);
	}
	return true;
}

TYPED_TEST(MathColor4Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Color4 = bksge::math::Color4<T>;

	// Color4 += Color4
	{
		Color4 v;
		VERIFY(v == Color4(0, 0, 0, 0));

		auto t = (v += Color4(2, 3, -4, 5));
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(v == Color4(2, 3, -4, 5));
		VERIFY(v == t);
	}
	// Color4 + Color4 -> Color4
	{
		auto t = Color4(-3, 4, 5, 6) + Color4(0, 2, -1, 3);
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(t == Color4(-3, 6, 4, 9));
	}

	return true;
}

TYPED_TEST(MathColor4Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Color4 = bksge::math::Color4<T>;

	// Color4 -= Color4
	{
		Color4 v;
		VERIFY(v == Color4(0, 0, 0, 0));

		auto t = (v -= Color4(2, 3, -4, 5));
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(v == Color4(-2, -3, 4, -5));
		VERIFY(v == t);
	}
	// Color4 - Color4 -> Color4
	{
		auto t = Color4(-3, 4, 5, 6) - Color4(0, 2, -1, 3);
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(t == Color4(-3, 2, 6, 3));
	}

	return true;
}

TYPED_TEST(MathColor4Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Color4 = bksge::math::Color4<T>;

	// Color4 *= スカラー
	{
		Color4 v(2, 3, 4, 5);
		{
			auto t = (v *= 4);
			static_assert(bksge::is_same<decltype(t), Color4>::value, "");
			VERIFY(v == Color4(8, 12, 16, 20));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(bksge::is_same<decltype(t), Color4>::value, "");
			VERIFY(v == Color4(4, 6, 8, 10));
			VERIFY(t == v);
		}
	}
	// Color4 * スカラー -> Color4
	{
		auto t = Color4(-3, 42, 5, 4) * -4;
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(t == Color4(12, -168, -20, -16));
	}
	{
		auto t = Color4(4, 6, 2, -10) * 2.5;
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(t == Color4(10, 15, 5, -25));
	}
	// スカラー * Color4 -> Color4
	{
		auto t = 5 * Color4(7, -8, 9, 2);
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(t == Color4(35, -40, 45, 10));
	}
	{
		auto t = -1.5 * Color4(4, -6, -2, 8);
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(t == Color4(-6, 9, 3, -12));
	}

	return true;
}

TYPED_TEST(MathColor4Test, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulColor4Test()
{
	using Color4 = bksge::math::Color4<T>;

	// Color4 *= Color4
	{
		Color4 v(2, 3, 4, 5);

		auto t = (v *= Color4(-1, 2, -3, 4));
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(Color4(-2, 6, -12, 20) == v);
		VERIFY(t == v);
	}

	// Color4 * Color4 -> Color4
	{
		auto t = Color4(-3, 4, 5, 6) * Color4(0, 2, -1, -2);
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(Color4(0, 8, -5, -12) == t);
	}

	return true;
}

TYPED_TEST(MathColor4Test, MulColor4Test)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulColor4Test<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Color4 = bksge::math::Color4<T>;

	// Color4 /= スカラー
	{
		Color4 v(2, 4, 6, 8);
		{
			auto t = (v /= 2);
			static_assert(bksge::is_same<decltype(t), Color4>::value, "");
			VERIFY(v == Color4(1, 2, 3, 4));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(bksge::is_same<decltype(t), Color4>::value, "");
			VERIFY(v == Color4(2, 4, 6, 8));
			VERIFY(t == v);
		}
	}
	// Color4 / スカラー -> Color4
	{
		auto t = Color4(-4, 8, -12, 16) / -4;
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(t == Color4(1, -2, 3, -4));
	}
	{
		auto t = Color4(-4, 8, -12, 16) / 0.25;
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(t == Color4(-16, 32, -48, 64));
	}

	return true;
}

TYPED_TEST(MathColor4Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivColor4Test()
{
	using Color4 = bksge::math::Color4<T>;

	// Color4 /= Color4
	{
		Color4 v(8, 12, 16, 15);

		auto t = (v /= Color4(-1, 2, -4, 5));
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(Color4(-8, 6, -4, 3) == v);
		VERIFY(t == v);
	}

	// Color4 / Color4 -> Color4
	{
		auto t = Color4(-3, 4, 5, 6) / Color4(1, 2, -1, 3);
		static_assert(bksge::is_same<decltype(t), Color4>::value, "");
		VERIFY(Color4(-3, 2, -5, 2) == t);
	}

	return true;
}

TYPED_TEST(MathColor4Test, DivColor4Test)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivColor4Test<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Color4 = bksge::math::Color4<T>;

	Color4 const v1(1, 2, 3, 4);
	Color4 const v2(1, 2, 3, 4);
	Color4 const v3(2, 2, 3, 4);
	Color4 const v4(1, 0, 3, 4);
	Color4 const v5(1, 2, 2, 4);
	Color4 const v6(1, 2, 3, 5);

	VERIFY( (v1 == v1));
	VERIFY( (v1 == v2));
	VERIFY(!(v1 == v3));
	VERIFY(!(v1 == v4));
	VERIFY(!(v1 == v5));
	VERIFY(!(v1 == v6));

	VERIFY(!(v1 != v1));
	VERIFY(!(v1 != v2));
	VERIFY( (v1 != v3));
	VERIFY( (v1 != v4));
	VERIFY( (v1 != v5));
	VERIFY( (v1 != v6));

	return true;
}

TYPED_TEST(MathColor4Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathColor4Test, OutputStreamTest)
{
	using Color4 = bksge::math::Color4<TypeParam>;
	{
		Color4 const v{1, -2, 3, 4};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2, 3, 4 }", ss.str());
	}
	{
		Color4 const v{-10, 9, 8, -7};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9, 8, -7 }", ss.str());
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Color4 = bksge::math::Color4<T>;

	{
		auto v = Color4::Zero();
		static_assert(bksge::is_same<decltype(v), Color4>::value, "");
		VERIFY(Color4(0, 0, 0, 0) == v);
	}
	return true;
}

TYPED_TEST(MathColor4Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool LerpTest()
{
	using Color4 = bksge::math::Color4<T>;
	{
		Color4 v1 {  0,  0,  0,  0 };
		Color4 v2 { 10, 20, 30, 40 };

		VERIFY(Color4( 0.0,  0.0,  0.0,  0.0) == Lerp(v1, v2, 0.00f));
		VERIFY(Color4( 2.5,  5.0,  7.5, 10.0) == Lerp(v1, v2, 0.25f));
		VERIFY(Color4( 5.0, 10.0, 15.0, 20.0) == Lerp(v1, v2, 0.50f));
		VERIFY(Color4( 7.5, 15.0, 22.5, 30.0) == Lerp(v1, v2, 0.75f));
		VERIFY(Color4(10.0, 20.0, 30.0, 40.0) == Lerp(v1, v2, 1.00f));
	}
	{
		Color4 v1 { -10,  10,  20, -30 };
		Color4 v2 {  10, -20, -30,  40 };

		VERIFY(Color4(-10.0,  10.0,  20.0, -30.0) == Lerp(v1, v2, 0.00));
		VERIFY(Color4( -5.0,   2.5,   7.5, -12.5) == Lerp(v1, v2, 0.25));
		VERIFY(Color4(  0.0,  -5.0,  -5.0,   5.0) == Lerp(v1, v2, 0.50));
		VERIFY(Color4(  5.0, -12.5, -17.5,  22.5) == Lerp(v1, v2, 0.75));
		VERIFY(Color4( 10.0, -20.0, -30.0,  40.0) == Lerp(v1, v2, 1.00));
	}
	return true;
}

TYPED_TEST(MathColor4Test, LerpTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(LerpTest<TypeParam>());
}

TYPED_TEST(MathColor4Test, SerializeTest)
{
	using namespace bksge::serialization;
	using Color4 = bksge::math::Color4<TypeParam>;

	Color4 const v { 1, -2, 3, -4 };

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
	using Color4 = bksge::math::Color4<T>;

	Color4 const v1(1, 2, 3, 4);
	Color4 const v2(2, 2, 3, 4);
	Color4 const v3(1, 0, 3, 4);
	Color4 const v4(1, 2, 2, 4);
	Color4 const v5(1, 2, 3, 0);

	std::hash<Color4> h;

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

TYPED_TEST(MathColor4Test, HashTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

TYPED_TEST(MathColor4Test, TupleElementTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	static_assert(bksge::is_same<typename bksge::tuple_element<0, Color4>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<1, Color4>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<2, Color4>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<3, Color4>::type, T>::value, "");
}

TYPED_TEST(MathColor4Test, TupleSizeTest)
{
	using T = TypeParam;
	using Color4 = bksge::math::Color4<T>;

	static_assert(bksge::tuple_size<Color4>::value == 4, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Color4 = bksge::math::Color4<T>;
	using std::get;
	{
		Color4 v{1, 2, 3, 4};

		VERIFY(1 == get<0>(v));
		VERIFY(2 == get<1>(v));
		VERIFY(3 == get<2>(v));
		VERIFY(4 == get<3>(v));

		get<0>(v) = 5;
		get<3>(v) = 6;

		VERIFY(v == Color4(5, 2, 3, 6));
		VERIFY(5 == get<0>(v));
		VERIFY(2 == get<1>(v));
		VERIFY(3 == get<2>(v));
		VERIFY(6 == get<3>(v));
	}
	{
		Color4 const v{1, 2, 3, 4};

		VERIFY(1 == get<0>(v));
		VERIFY(2 == get<1>(v));
		VERIFY(3 == get<2>(v));
		VERIFY(4 == get<3>(v));
	}
	return true;
}

TYPED_TEST(MathColor4Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

#undef VERIFY

}	// namespace color4_test

}	// namespace bksge_math_test
