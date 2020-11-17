/**
 *	@file	unit_test_core_math_color3.cpp
 *
 *	@brief	Color3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/color3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/fnd/concepts/swap.hpp>
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

namespace color3_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Color3f = bksge::math::Color3<float>;
using Color3i = bksge::math::Color3<int>;

using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathColor3Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathColor3Test, MathTestTypes);

TYPED_TEST(MathColor3Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	static_assert(sizeof(Color3) == sizeof(T) * 3, "");
	static_assert(bksge::is_default_constructible<Color3>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Color3>::value, "");
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

	static_assert(!bksge::is_constructible<Color3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Color3, T, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Color3, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Color3, T, T>::value, "");
	static_assert( bksge::is_constructible<Color3, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color3, T, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Color3, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color3, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Color3, T>::value, "");
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
		BKSGE_CONSTEXPR_OR_CONST Color3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v = {9, 10, 11};
		BKSGE_CONSTEXPR_EXPECT_EQ( 9, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Color3 v{13};
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[2]);
	}
}
#if 0
TYPED_TEST(MathColor3Test, Vector2ConstructTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	static_assert(!bksge::is_constructible<Color3, Vector2, T, T>::value, "");
	static_assert( bksge::is_constructible<Color3, Vector2, T>::value, "");
	static_assert(!bksge::is_constructible<Color3, Vector2>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color3, Vector2, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Color3, Vector2, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Color3, Vector2>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color3, Vector2, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Color3, Vector2, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Color3, Vector2>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v1(1, 2);
		BKSGE_CONSTEXPR_OR_CONST Color3 v2(v1, 4);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v1(2, 3);
		BKSGE_CONSTEXPR_OR_CONST Color3 v2{v1, 5};
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v2[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v1(3, 4);
		BKSGE_CONSTEXPR_OR_CONST Color3 v2 = {v1, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v2[2]);
	}
}
#endif
TYPED_TEST(MathColor3Test, CopyConstructTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	static_assert(bksge::is_constructible<Color3, Color3 const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color3, Color3 const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color3, Color3 const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Color3  v1{1, 2, 3};
	BKSGE_CONSTEXPR_OR_CONST Color3  v2{v1};

	BKSGE_CONSTEXPR_EXPECT_EQ(1, v1[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v1[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v1[2]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[2]);
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ConvertConstructTest()
{
	using Color3 = bksge::math::Color3<T>;
	using Color3u8 = bksge::math::Color3<std::uint8_t>;

	static_assert(bksge::is_constructible<Color3,   Color3u8 const&>::value, "");
	static_assert(bksge::is_constructible<Color3u8, Color3   const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color3,   Color3u8 const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Color3u8, Color3   const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color3,   Color3u8 const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Color3u8, Color3   const&>::value, "");

	{
		Color3u8 const v1(0, 128, 255);
		Color3   const v2(v1);
		double error = 0.0000001;
		VERIFY(IsNear(0.00000000000000000, (double)v2[0], error));
		VERIFY(IsNear(0.50196078431372548, (double)v2[1], error));
		VERIFY(IsNear(1.00000000000000000, (double)v2[2], error));
	}
	{
		Color3u8 const v1(32, 64, 192);
		Color3   const v2(v1);
		double error = 0.0000001;
		VERIFY(IsNear(0.12549019607843137, (double)v2[0], error));
		VERIFY(IsNear(0.25098039215686274, (double)v2[1], error));
		VERIFY(IsNear(0.75294117647058822, (double)v2[2], error));
	}
	{
		Color3   const v1(0.5, 1.0, 0.0);
		Color3u8 const v2(v1);
		VERIFY(127 == v2[0]);
		VERIFY(255 == v2[1]);
		VERIFY(  0 == v2[2]);
	}
	{
		Color3   const v1(0.25, 0.75, 0.125);
		Color3u8 const v2(v1);
		VERIFY( 63 == v2[0]);
		VERIFY(191 == v2[1]);
		VERIFY( 31 == v2[2]);
	}

	return true;
}

TYPED_TEST(MathColor3Test, ConvertConstructTest)
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
	using Color3 = bksge::math::Color3<T>;

	const double error = 0.0000001;

	Color3 v1(0, 1, 2);
	Color3 v2(3, 4, 5);
	VERIFY(0 == v1[0]);
	VERIFY(1 == v1[1]);
	VERIFY(2 == v1[2]);
	VERIFY(3 == v2[0]);
	VERIFY(4 == v2[1]);
	VERIFY(5 == v2[2]);

	v1 = Color3(6, -7, 8);
	v2 = Color3i(128, 255, 64);
	VERIFY( 6 == v1[0]);
	VERIFY(-7 == v1[1]);
	VERIFY( 8 == v1[2]);
	VERIFY(IsNear(0.50196078431372548, (double)v2[0], error));
	VERIFY(IsNear(1.00000000000000000, (double)v2[1], error));
	VERIFY(IsNear(0.25098039215686274, (double)v2[2], error));

	// 自己代入
	v1 = v1;
	v2 = v2;
	VERIFY( 6 == v1[0]);
	VERIFY(-7 == v1[1]);
	VERIFY( 8 == v1[2]);
	VERIFY(IsNear(0.50196078431372548, (double)v2[0], error));
	VERIFY(IsNear(1.00000000000000000, (double)v2[1], error));
	VERIFY(IsNear(0.25098039215686274, (double)v2[2], error));

	// 多重代入
	v1 = v2 = Color3f(4, 5, 6);
	VERIFY(4 == v1[0]);
	VERIFY(5 == v1[1]);
	VERIFY(6 == v1[2]);
	VERIFY(4 == v2[0]);
	VERIFY(5 == v2[1]);
	VERIFY(6 == v2[2]);

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathColor3Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Color3 = bksge::math::Color3<T>;
	{
		Color3 v{1, 2, 3};
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);

		v[0] = -3;
		v[1] =  4;
		v[2] = -5;

		VERIFY(v[0] == -3);
		VERIFY(v[1] ==  4);
		VERIFY(v[2] == -5);
	}
	{
		Color3 const v{5, 6, 7};
		VERIFY(v[0] == 5);
		VERIFY(v[1] == 6);
		VERIFY(v[2] == 7);
	}
	return true;
}

TYPED_TEST(MathColor3Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Color3 = bksge::math::Color3<T>;
	{
		Color3 v{1, 2, 3};
		VERIFY(v.at(0) == 1);
		VERIFY(v.at(1) == 2);
		VERIFY(v.at(2) == 3);

		v.at(0) = -3;
		v.at(1) =  4;
		v.at(2) = -5;

		VERIFY(v.at(0) == -3);
		VERIFY(v.at(1) ==  4);
		VERIFY(v.at(2) == -5);
	}
	{
		Color3 const v{5, 6, 7};
		VERIFY(v.at(0) == 5);
		VERIFY(v.at(1) == 6);
		VERIFY(v.at(2) == 7);
	}
	return true;
}

TYPED_TEST(MathColor3Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Color3 = bksge::math::Color3<TypeParam>;
	{
		Color3 v{1, 2, 3};
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
	{
		Color3 const v{5, 6, 7};
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Color3 = bksge::math::Color3<T>;
	{
		Color3 v{1, 2, 3};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == 1);
		*p = 5;
		++p;
		VERIFY(*p == 2);
		p++;
		VERIFY(*p == 3);
		*p = 6;

		VERIFY(v == Color3(5, 2, 6));
	}
	{
		Color3 const v{1, 2, 3};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == 1);
		++p;
		VERIFY(*p == 2);
		p++;
		VERIFY(*p == 3);
	}
	return true;
}

TYPED_TEST(MathColor3Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Color3 = bksge::math::Color3<T>;

	// begin, end (non const)
	{
		Color3 v{1, 2, 3};
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
		VERIFY(it == v.end());

		VERIFY(Color3(5, 2, 6) == v);
	}
	// begin, end (const)
	{
		Color3 const v{1, 2, 3};
		auto it = v.begin();
		VERIFY(it != v.end());

		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 3);

		VERIFY(*it++ == 1);
		VERIFY(it != v.end());
		VERIFY(*++it == 3);
		VERIFY(it != v.end());
		VERIFY(*it++ == 3);
		VERIFY(it == v.end());
	}
	// cbegin, cend
	{
		Color3 v{1, 2, 3};
		auto it = v.cbegin();
		VERIFY(it != v.cend());

		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 3);

		VERIFY(*it++ == 1);
		VERIFY(it != v.cend());
		VERIFY(*++it == 3);
		VERIFY(it != v.cend());
		VERIFY(*it++ == 3);
		VERIFY(it == v.cend());
	}
	return true;
}

TYPED_TEST(MathColor3Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Color3 = bksge::math::Color3<T>;

	// rbegin, rend (non const)
	{
		Color3 v{1, 2, 3};
		auto it = v.rbegin();
		VERIFY(it != v.rend());
		VERIFY(*it == 3);
		*it++ = 5;
		VERIFY(it != v.rend());
		VERIFY(*it == 2);
		*++it = 6;
		VERIFY(it != v.rend());
		VERIFY(*it == 6);
		it++;
		VERIFY(it == v.rend());

		VERIFY(Color3(6, 2, 5) == v);
	}
	// rbegin, rend (const)
	{
		Color3 const v{1, 2, 3};
		auto it = v.rbegin();
		VERIFY(it != v.rend());

		VERIFY(it[0] == 3);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 1);

		VERIFY(*it++ == 3);
		VERIFY(it != v.rend());
		VERIFY(*++it == 1);
		VERIFY(it != v.rend());
		VERIFY(*it++ == 1);
		VERIFY(it == v.rend());
	}
	// crbegin, crend
	{
		Color3 v{1, 2, 3};
		auto it = v.crbegin();
		VERIFY(it != v.crend());

		VERIFY(it[0] == 3);
		VERIFY(it[1] == 2);
		VERIFY(it[2] == 1);

		VERIFY(*it++ == 3);
		VERIFY(it != v.crend());
		VERIFY(*++it == 1);
		VERIFY(it != v.crend());
		VERIFY(*it++ == 1);
		VERIFY(it == v.crend());
	}
	return true;
}

TYPED_TEST(MathColor3Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Color3 = bksge::math::Color3<T>;
	Color3 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathColor3Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Color3 = bksge::math::Color3<T>;
	Color3 v1{};
	VERIFY(v1.size() == 3);
	return true;
}

TYPED_TEST(MathColor3Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Color3 = bksge::math::Color3<T>;
	Color3 v1{};
	VERIFY(v1.max_size() == 3);
	return true;
}

TYPED_TEST(MathColor3Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Color3 = bksge::math::Color3<T>;
	{
		Color3 v{1, 2, 3};
		VERIFY(v.r() == 1);
		VERIFY(v.g() == 2);
		VERIFY(v.b() == 3);

		v.r() = -3;
		v.g() =  4;
		v.b() = -5;

		VERIFY(v.r() == -3);
		VERIFY(v.g() ==  4);
		VERIFY(v.b() == -5);
	}
	{
		Color3 const v{5, 6, 7};
		VERIFY(v.r() == 5);
		VERIFY(v.g() == 6);
		VERIFY(v.b() == 7);
	}
	return true;
}

TYPED_TEST(MathColor3Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Color3 = bksge::math::Color3<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	Color3 const v(1, 2, 3);

	VERIFY(Vector4(1, 1, 1, 1) == v.rrrr());
	VERIFY(Vector4(1, 1, 1, 2) == v.rrrg());
	VERIFY(Vector4(1, 1, 1, 3) == v.rrrb());
	VERIFY(Vector4(1, 1, 2, 1) == v.rrgr());
	VERIFY(Vector4(1, 1, 2, 2) == v.rrgg());
	VERIFY(Vector4(1, 1, 2, 3) == v.rrgb());
	VERIFY(Vector4(1, 1, 3, 1) == v.rrbr());
	VERIFY(Vector4(1, 1, 3, 2) == v.rrbg());
	VERIFY(Vector4(1, 1, 3, 3) == v.rrbb());
	VERIFY(Vector4(1, 2, 1, 1) == v.rgrr());
	VERIFY(Vector4(1, 2, 1, 2) == v.rgrg());
	VERIFY(Vector4(1, 2, 1, 3) == v.rgrb());
	VERIFY(Vector4(1, 2, 2, 1) == v.rggr());
	VERIFY(Vector4(1, 2, 2, 2) == v.rggg());
	VERIFY(Vector4(1, 2, 2, 3) == v.rggb());
	VERIFY(Vector4(1, 2, 3, 1) == v.rgbr());
	VERIFY(Vector4(1, 2, 3, 2) == v.rgbg());
	VERIFY(Vector4(1, 2, 3, 3) == v.rgbb());
	VERIFY(Vector4(1, 3, 1, 1) == v.rbrr());
	VERIFY(Vector4(1, 3, 1, 2) == v.rbrg());
	VERIFY(Vector4(1, 3, 1, 3) == v.rbrb());
	VERIFY(Vector4(1, 3, 2, 1) == v.rbgr());
	VERIFY(Vector4(1, 3, 2, 2) == v.rbgg());
	VERIFY(Vector4(1, 3, 2, 3) == v.rbgb());
	VERIFY(Vector4(1, 3, 3, 1) == v.rbbr());
	VERIFY(Vector4(1, 3, 3, 2) == v.rbbg());
	VERIFY(Vector4(1, 3, 3, 3) == v.rbbb());
	VERIFY(Vector4(2, 1, 1, 1) == v.grrr());
	VERIFY(Vector4(2, 1, 1, 2) == v.grrg());
	VERIFY(Vector4(2, 1, 1, 3) == v.grrb());
	VERIFY(Vector4(2, 1, 2, 1) == v.grgr());
	VERIFY(Vector4(2, 1, 2, 2) == v.grgg());
	VERIFY(Vector4(2, 1, 2, 3) == v.grgb());
	VERIFY(Vector4(2, 1, 3, 1) == v.grbr());
	VERIFY(Vector4(2, 1, 3, 2) == v.grbg());
	VERIFY(Vector4(2, 1, 3, 3) == v.grbb());
	VERIFY(Vector4(2, 2, 1, 1) == v.ggrr());
	VERIFY(Vector4(2, 2, 1, 2) == v.ggrg());
	VERIFY(Vector4(2, 2, 1, 3) == v.ggrb());
	VERIFY(Vector4(2, 2, 2, 1) == v.gggr());
	VERIFY(Vector4(2, 2, 2, 2) == v.gggg());
	VERIFY(Vector4(2, 2, 2, 3) == v.gggb());
	VERIFY(Vector4(2, 2, 3, 1) == v.ggbr());
	VERIFY(Vector4(2, 2, 3, 2) == v.ggbg());
	VERIFY(Vector4(2, 2, 3, 3) == v.ggbb());
	VERIFY(Vector4(2, 3, 1, 1) == v.gbrr());
	VERIFY(Vector4(2, 3, 1, 2) == v.gbrg());
	VERIFY(Vector4(2, 3, 1, 3) == v.gbrb());
	VERIFY(Vector4(2, 3, 2, 1) == v.gbgr());
	VERIFY(Vector4(2, 3, 2, 2) == v.gbgg());
	VERIFY(Vector4(2, 3, 2, 3) == v.gbgb());
	VERIFY(Vector4(2, 3, 3, 1) == v.gbbr());
	VERIFY(Vector4(2, 3, 3, 2) == v.gbbg());
	VERIFY(Vector4(2, 3, 3, 3) == v.gbbb());
	VERIFY(Vector4(3, 1, 1, 1) == v.brrr());
	VERIFY(Vector4(3, 1, 1, 2) == v.brrg());
	VERIFY(Vector4(3, 1, 1, 3) == v.brrb());
	VERIFY(Vector4(3, 1, 2, 1) == v.brgr());
	VERIFY(Vector4(3, 1, 2, 2) == v.brgg());
	VERIFY(Vector4(3, 1, 2, 3) == v.brgb());
	VERIFY(Vector4(3, 1, 3, 1) == v.brbr());
	VERIFY(Vector4(3, 1, 3, 2) == v.brbg());
	VERIFY(Vector4(3, 1, 3, 3) == v.brbb());
	VERIFY(Vector4(3, 2, 1, 1) == v.bgrr());
	VERIFY(Vector4(3, 2, 1, 2) == v.bgrg());
	VERIFY(Vector4(3, 2, 1, 3) == v.bgrb());
	VERIFY(Vector4(3, 2, 2, 1) == v.bggr());
	VERIFY(Vector4(3, 2, 2, 2) == v.bggg());
	VERIFY(Vector4(3, 2, 2, 3) == v.bggb());
	VERIFY(Vector4(3, 2, 3, 1) == v.bgbr());
	VERIFY(Vector4(3, 2, 3, 2) == v.bgbg());
	VERIFY(Vector4(3, 2, 3, 3) == v.bgbb());
	VERIFY(Vector4(3, 3, 1, 1) == v.bbrr());
	VERIFY(Vector4(3, 3, 1, 2) == v.bbrg());
	VERIFY(Vector4(3, 3, 1, 3) == v.bbrb());
	VERIFY(Vector4(3, 3, 2, 1) == v.bbgr());
	VERIFY(Vector4(3, 3, 2, 2) == v.bbgg());
	VERIFY(Vector4(3, 3, 2, 3) == v.bbgb());
	VERIFY(Vector4(3, 3, 3, 1) == v.bbbr());
	VERIFY(Vector4(3, 3, 3, 2) == v.bbbg());
	VERIFY(Vector4(3, 3, 3, 3) == v.bbbb());

	VERIFY(Vector3(1, 1, 1) == v.rrr());
	VERIFY(Vector3(1, 1, 2) == v.rrg());
	VERIFY(Vector3(1, 1, 3) == v.rrb());
	VERIFY(Vector3(1, 2, 1) == v.rgr());
	VERIFY(Vector3(1, 2, 2) == v.rgg());
	VERIFY(Vector3(1, 2, 3) == v.rgb());
	VERIFY(Vector3(1, 3, 1) == v.rbr());
	VERIFY(Vector3(1, 3, 2) == v.rbg());
	VERIFY(Vector3(1, 3, 3) == v.rbb());
	VERIFY(Vector3(2, 1, 1) == v.grr());
	VERIFY(Vector3(2, 1, 2) == v.grg());
	VERIFY(Vector3(2, 1, 3) == v.grb());
	VERIFY(Vector3(2, 2, 1) == v.ggr());
	VERIFY(Vector3(2, 2, 2) == v.ggg());
	VERIFY(Vector3(2, 2, 3) == v.ggb());
	VERIFY(Vector3(2, 3, 1) == v.gbr());
	VERIFY(Vector3(2, 3, 2) == v.gbg());
	VERIFY(Vector3(2, 3, 3) == v.gbb());
	VERIFY(Vector3(3, 1, 1) == v.brr());
	VERIFY(Vector3(3, 1, 2) == v.brg());
	VERIFY(Vector3(3, 1, 3) == v.brb());
	VERIFY(Vector3(3, 2, 1) == v.bgr());
	VERIFY(Vector3(3, 2, 2) == v.bgg());
	VERIFY(Vector3(3, 2, 3) == v.bgb());
	VERIFY(Vector3(3, 3, 1) == v.bbr());
	VERIFY(Vector3(3, 3, 2) == v.bbg());
	VERIFY(Vector3(3, 3, 3) == v.bbb());

	VERIFY(Vector2(1, 1) == v.rr());
	VERIFY(Vector2(1, 2) == v.rg());
	VERIFY(Vector2(1, 3) == v.rb());
	VERIFY(Vector2(2, 1) == v.gr());
	VERIFY(Vector2(2, 2) == v.gg());
	VERIFY(Vector2(2, 3) == v.gb());
	VERIFY(Vector2(3, 1) == v.br());
	VERIFY(Vector2(3, 2) == v.bg());
	VERIFY(Vector2(3, 3) == v.bb());

	return true;
}

TYPED_TEST(MathColor3Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Color3 = bksge::math::Color3<T>;

	Color3 v1{1, 2, 3};
	Color3 v2{5, 6, 7};

	v1.swap(v2);

	VERIFY(v1 == Color3(5, 6, 7));
	VERIFY(v2 == Color3(1, 2, 3));

	bksge::ranges::swap(v1, v2);

	VERIFY(v1 == Color3(1, 2, 3));
	VERIFY(v2 == Color3(5, 6, 7));

	return true;
}

TYPED_TEST(MathColor3Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Color3 = bksge::math::Color3<T>;
	{
		Color3 const v1(-1, 2, -3);
		Color3 const v2 = +v1;
		Color3 const v3 = -v1;

		VERIFY(v2[0] == -1);
		VERIFY(v2[1] ==  2);
		VERIFY(v2[2] == -3);
		VERIFY(v3[0] ==  1);
		VERIFY(v3[1] == -2);
		VERIFY(v3[2] ==  3);
	}
	return true;
}

TYPED_TEST(MathColor3Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Color3 = bksge::math::Color3<T>;
	// Color3 += Color3
	{
		Color3 v;
		VERIFY(v == Color3(0, 0, 0));

		auto t = (v += Color3(2, 3, -4));
		static_assert(bksge::is_same<decltype(t), Color3>::value, "");
		VERIFY(v == Color3(2, 3, -4));
		VERIFY(v == t);
	}
	// Color3 + Color3 -> Color3
	{
		auto t = Color3(-3, 4, 5) + Color3(0, 2, -1);
		static_assert(bksge::is_same<decltype(t), Color3>::value, "");
		VERIFY(t == Color3(-3, 6, 4));
	}
	return true;
}

TYPED_TEST(MathColor3Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Color3 = bksge::math::Color3<T>;
	// Color3 -= Color3
	{
		Color3 v;
		VERIFY(v == Color3(0, 0, 0));

		auto t = (v -= Color3(2, 3, -4));
		static_assert(bksge::is_same<decltype(t), Color3>::value, "");
		VERIFY(v == Color3(-2, -3, 4));
		VERIFY(v == t);
	}
	// Color3 - Color3 -> Color3
	{
		auto t = Color3(-3, 4, 5) - Color3(0, 2, -1);
		static_assert(bksge::is_same<decltype(t), Color3>::value, "");
		VERIFY(t == Color3(-3, 2, 6));
	}
	return true;
}

TYPED_TEST(MathColor3Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Color3 = bksge::math::Color3<T>;
	// Color3 *= スカラー
	{
		Color3 v(2, 3, 4);
		{
			auto t = (v *= 4);
			static_assert(bksge::is_same<decltype(t), Color3>::value, "");
			VERIFY(v == Color3(8, 12, 16));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(bksge::is_same<decltype(t), Color3>::value, "");
			VERIFY(v == Color3(4, 6, 8));
			VERIFY(t == v);
		}
	}
	// Color3 * スカラー -> Color3
	{
		auto t = Color3(-3, 42, 5) * -4;
		static_assert(bksge::is_same<decltype(t), Color3>::value, "");
		VERIFY(t == Color3(12, -168, -20));
	}
	{
		auto t = Color3(4, 6, 2) * 2.5;
		static_assert(bksge::is_same<decltype(t), Color3>::value, "");
		VERIFY(t == Color3(10, 15, 5));
	}
	// スカラー * Color3 -> Color3
	{
		auto t = 5 * Color3(7, -8, 9);
		static_assert(bksge::is_same<decltype(t), Color3>::value, "");
		VERIFY(t == Color3(35, -40, 45));
	}
	{
		auto t = -1.5 * Color3(4, -6, -2);
		static_assert(bksge::is_same<decltype(t), Color3>::value, "");
		VERIFY(t == Color3(-6, 9, 3));
	}
	return true;
}

TYPED_TEST(MathColor3Test, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Color3 = bksge::math::Color3<T>;
	// Color3 /= スカラー
	{
		Color3 v(2, 4, 6);
		{
			auto t = (v /= 2);
			static_assert(bksge::is_same<decltype(t), Color3>::value, "");
			VERIFY(v == Color3(1, 2, 3));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(bksge::is_same<decltype(t), Color3>::value, "");
			VERIFY(v == Color3(2, 4, 6));
			VERIFY(t == v);
		}
	}
	// Color3 / スカラー -> Color3
	{
		auto t = Color3(-4, 8, -12) / -4;
		static_assert(bksge::is_same<decltype(t), Color3>::value, "");
		VERIFY(t == Color3(1, -2, 3));
	}
	{
		auto t = Color3(-4, 8, -12) / 0.25;
		static_assert(bksge::is_same<decltype(t), Color3>::value, "");
		VERIFY(t == Color3(-16, 32, -48));
	}
	return true;
}

TYPED_TEST(MathColor3Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Color3 = bksge::math::Color3<T>;

	Color3 const v1(1, 2, 3);
	Color3 const v2(1, 2, 3);
	Color3 const v3(2, 2, 3);
	Color3 const v4(1, 0, 3);
	Color3 const v5(1, 2, 2);

	VERIFY( (v1 == v1));
	VERIFY( (v1 == v2));
	VERIFY(!(v1 == v3));
	VERIFY(!(v1 == v4));
	VERIFY(!(v1 == v5));

	VERIFY(!(v1 != v1));
	VERIFY(!(v1 != v2));
	VERIFY( (v1 != v3));
	VERIFY( (v1 != v4));
	VERIFY( (v1 != v5));

	return true;
}

TYPED_TEST(MathColor3Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathColor3Test, OutputStreamTest)
{
	using Color3 = bksge::math::Color3<TypeParam>;
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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Color3 = bksge::math::Color3<T>;

	{
		auto v = Color3::Zero();
		static_assert(bksge::is_same<decltype(v), Color3>::value, "");
		VERIFY(Color3(0, 0, 0) == v);
	}
	return true;
}

TYPED_TEST(MathColor3Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool LerpTest()
{
	using Color3 = bksge::math::Color3<T>;
	{
		Color3 v1 {  0,  0,  0 };
		Color3 v2 { 10, 20, 30 };

		VERIFY(Color3( 0.0,  0.0,  0.0) == Lerp(v1, v2, 0.00f));
		VERIFY(Color3( 2.5,  5.0,  7.5) == Lerp(v1, v2, 0.25f));
		VERIFY(Color3( 5.0, 10.0, 15.0) == Lerp(v1, v2, 0.50f));
		VERIFY(Color3( 7.5, 15.0, 22.5) == Lerp(v1, v2, 0.75f));
		VERIFY(Color3(10.0, 20.0, 30.0) == Lerp(v1, v2, 1.00f));
	}
	{
		Color3 v1 { -10,  10,  20 };
		Color3 v2 {  10, -20, -30 };

		VERIFY(Color3(-10.0,  10.0,  20.0) == Lerp(v1, v2, 0.00));
		VERIFY(Color3( -5.0,   2.5,   7.5) == Lerp(v1, v2, 0.25));
		VERIFY(Color3(  0.0,  -5.0,  -5.0) == Lerp(v1, v2, 0.50));
		VERIFY(Color3(  5.0, -12.5, -17.5) == Lerp(v1, v2, 0.75));
		VERIFY(Color3( 10.0, -20.0, -30.0) == Lerp(v1, v2, 1.00));
	}
	return true;
}

TYPED_TEST(MathColor3Test, LerpTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(LerpTest<TypeParam>());
}

TYPED_TEST(MathColor3Test, SerializeTest)
{
	using namespace bksge::serialization;
	using Color3 = bksge::math::Color3<TypeParam>;

	Color3 const v { 1, -2, 3 };

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
	using Color3 = bksge::math::Color3<T>;

	Color3 const v1(1, 2, 3);
	Color3 const v2(2, 2, 3);
	Color3 const v3(1, 0, 3);
	Color3 const v4(1, 2, 2);
	Color3 const v5(1, 2, 3);

	std::hash<Color3> h;

	VERIFY(h(v1) == h(v1));
	VERIFY(h(v1) != h(v2));
	VERIFY(h(v1) != h(v3));
	VERIFY(h(v1) != h(v4));
	VERIFY(h(v1) == h(v5));

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

	VERIFY(h(v5) == h(v1));
	VERIFY(h(v5) != h(v2));
	VERIFY(h(v5) != h(v3));
	VERIFY(h(v5) != h(v4));
	VERIFY(h(v5) == h(v5));

	return true;
}

TYPED_TEST(MathColor3Test, HashTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

TYPED_TEST(MathColor3Test, TupleElementTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	static_assert(bksge::is_same<typename std::tuple_element<0, Color3>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<1, Color3>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<2, Color3>::type, T>::value, "");
}

TYPED_TEST(MathColor3Test, TupleSizeTest)
{
	using T = TypeParam;
	using Color3 = bksge::math::Color3<T>;

	static_assert(std::tuple_size<Color3>::value == 3, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Color3 = bksge::math::Color3<T>;
	{
		Color3 v{1, 2, 3};

		VERIFY(1 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(3 == bksge::get<2>(v));

		bksge::get<0>(v) = 5;
		bksge::get<2>(v) = 6;

		VERIFY(v == Color3(5, 2, 6));
		VERIFY(5 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(6 == bksge::get<2>(v));
	}
	{
		Color3 const v{1, 2, 3};

		VERIFY(1 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(3 == bksge::get<2>(v));
	}
	return true;
}

TYPED_TEST(MathColor3Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

#undef VERIFY

}	// namespace color3_test

}	// namespace bksge_math_test
