/**
 *	@file	unit_test_core_math_vector3.cpp
 *
 *	@brief	Vector3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector2.hpp>
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

namespace bksge_math_test
{

namespace vector3_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Vector3f = bksge::math::Vector3<float>;
using Vector3i = bksge::math::Vector3<int>;


using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathVector3Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathVector3Test, MathTestTypes);

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
	static_assert( bksge::is_constructible<Vector3, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector3, T, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Vector3, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector3, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Vector3, T>::value, "");
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
		BKSGE_CONSTEXPR_OR_CONST Vector3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v = {9, 10, 11};
		BKSGE_CONSTEXPR_EXPECT_EQ( 9, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v{13};
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[2]);
	}
}

TYPED_TEST(MathVector3Test, Vector2ConstructTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	static_assert(!bksge::is_constructible<Vector3, Vector2, T, T>::value, "");
	static_assert( bksge::is_constructible<Vector3, Vector2, T>::value, "");
	static_assert(!bksge::is_constructible<Vector3, Vector2>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector3, Vector2, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Vector3, Vector2, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector3, Vector2>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector3, Vector2, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Vector3, Vector2, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector3, Vector2>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v1(1, 2);
		BKSGE_CONSTEXPR_OR_CONST Vector3 v2(v1, 4);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v1(2, 3);
		BKSGE_CONSTEXPR_OR_CONST Vector3 v2{v1, 5};
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v2[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v1(3, 4);
		BKSGE_CONSTEXPR_OR_CONST Vector3 v2 = {v1, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v2[2]);
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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Vector3 = bksge::math::Vector3<T>;

	Vector3 v{0, 1, 2};
	VERIFY(v[0] == 0);
	VERIFY(v[1] == 1);
	VERIFY(v[2] == 2);

	v = Vector3(-2, 3, -4);
	VERIFY(v[0] == -2);
	VERIFY(v[1] ==  3);
	VERIFY(v[2] == -4);

	v = Vector3i(3, -4, 5);
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);
	VERIFY(v[2] ==  5);

	// 自己代入
	v = v;
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);
	VERIFY(v[2] ==  5);

	// 多重代入
	Vector3 v2;
	v2 = v = Vector3f(4, 5, 6);
	VERIFY(v[0] == 4);
	VERIFY(v[1] == 5);
	VERIFY(v[2] == 6);
	VERIFY(v2[0] == 4);
	VERIFY(v2[1] == 5);
	VERIFY(v2[2] == 6);

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathVector3Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	{
		Vector3 v{1, 2, 3};
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
		Vector3 const v{5, 6, 7};
		VERIFY(v[0] == 5);
		VERIFY(v[1] == 6);
		VERIFY(v[2] == 7);
	}
	return true;
}

TYPED_TEST(MathVector3Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	{
		Vector3 v{1, 2, 3};
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
		Vector3 const v{5, 6, 7};
		VERIFY(v.at(0) == 5);
		VERIFY(v.at(1) == 6);
		VERIFY(v.at(2) == 7);
	}
	return true;
}

TYPED_TEST(MathVector3Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Vector3 = bksge::math::Vector3<TypeParam>;
	{
		Vector3 v{1, 2, 3};
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
	{
		Vector3 const v{5, 6, 7};
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	{
		Vector3 v{1, 2, 3};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == 1);
		*p = 5;
		++p;
		VERIFY(*p == 2);
		p++;
		VERIFY(*p == 3);
		*p = 6;

		VERIFY(v == Vector3(5, 2, 6));
	}
	{
		Vector3 const v{1, 2, 3};
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

TYPED_TEST(MathVector3Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Vector3 = bksge::math::Vector3<T>;

	// begin, end (non const)
	{
		Vector3 v{1, 2, 3};
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

		VERIFY(Vector3(5, 2, 6) == v);
	}
	// begin, end (const)
	{
		Vector3 const v{1, 2, 3};
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
		Vector3 v{1, 2, 3};
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

TYPED_TEST(MathVector3Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Vector3 = bksge::math::Vector3<T>;

	// rbegin, rend (non const)
	{
		Vector3 v{1, 2, 3};
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

		VERIFY(Vector3(6, 2, 5) == v);
	}
	// rbegin, rend (const)
	{
		Vector3 const v{1, 2, 3};
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
		Vector3 v{1, 2, 3};
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

TYPED_TEST(MathVector3Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	Vector3 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathVector3Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	Vector3 v1{};
	VERIFY(v1.size() == 3);
	return true;
}

TYPED_TEST(MathVector3Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	Vector3 v1{};
	VERIFY(v1.max_size() == 3);
	return true;
}

TYPED_TEST(MathVector3Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	{
		Vector3 v{1, 2, 3};
		VERIFY(v.x() == 1);
		VERIFY(v.y() == 2);
		VERIFY(v.z() == 3);

		v.x() = -3;
		v.y() =  4;
		v.z() = -5;

		VERIFY(v.x() == -3);
		VERIFY(v.y() ==  4);
		VERIFY(v.z() == -5);
	}
	{
		Vector3 const v{5, 6, 7};
		VERIFY(v.x() == 5);
		VERIFY(v.y() == 6);
		VERIFY(v.z() == 7);
	}
	return true;
}

TYPED_TEST(MathVector3Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	Vector3 v(1, 2, 3);

	VERIFY(Vector4(1, 1, 1, 1) == v.xxxx());
	VERIFY(Vector4(1, 1, 1, 2) == v.xxxy());
	VERIFY(Vector4(1, 1, 1, 3) == v.xxxz());
	VERIFY(Vector4(1, 1, 2, 1) == v.xxyx());
	VERIFY(Vector4(1, 1, 2, 2) == v.xxyy());
	VERIFY(Vector4(1, 1, 2, 3) == v.xxyz());
	VERIFY(Vector4(1, 1, 3, 1) == v.xxzx());
	VERIFY(Vector4(1, 1, 3, 2) == v.xxzy());
	VERIFY(Vector4(1, 1, 3, 3) == v.xxzz());
	VERIFY(Vector4(1, 2, 1, 1) == v.xyxx());
	VERIFY(Vector4(1, 2, 1, 2) == v.xyxy());
	VERIFY(Vector4(1, 2, 1, 3) == v.xyxz());
	VERIFY(Vector4(1, 2, 2, 1) == v.xyyx());
	VERIFY(Vector4(1, 2, 2, 2) == v.xyyy());
	VERIFY(Vector4(1, 2, 2, 3) == v.xyyz());
	VERIFY(Vector4(1, 2, 3, 1) == v.xyzx());
	VERIFY(Vector4(1, 2, 3, 2) == v.xyzy());
	VERIFY(Vector4(1, 2, 3, 3) == v.xyzz());
	VERIFY(Vector4(1, 3, 1, 1) == v.xzxx());
	VERIFY(Vector4(1, 3, 1, 2) == v.xzxy());
	VERIFY(Vector4(1, 3, 1, 3) == v.xzxz());
	VERIFY(Vector4(1, 3, 2, 1) == v.xzyx());
	VERIFY(Vector4(1, 3, 2, 2) == v.xzyy());
	VERIFY(Vector4(1, 3, 2, 3) == v.xzyz());
	VERIFY(Vector4(1, 3, 3, 1) == v.xzzx());
	VERIFY(Vector4(1, 3, 3, 2) == v.xzzy());
	VERIFY(Vector4(1, 3, 3, 3) == v.xzzz());
	VERIFY(Vector4(2, 1, 1, 1) == v.yxxx());
	VERIFY(Vector4(2, 1, 1, 2) == v.yxxy());
	VERIFY(Vector4(2, 1, 1, 3) == v.yxxz());
	VERIFY(Vector4(2, 1, 2, 1) == v.yxyx());
	VERIFY(Vector4(2, 1, 2, 2) == v.yxyy());
	VERIFY(Vector4(2, 1, 2, 3) == v.yxyz());
	VERIFY(Vector4(2, 1, 3, 1) == v.yxzx());
	VERIFY(Vector4(2, 1, 3, 2) == v.yxzy());
	VERIFY(Vector4(2, 1, 3, 3) == v.yxzz());
	VERIFY(Vector4(2, 2, 1, 1) == v.yyxx());
	VERIFY(Vector4(2, 2, 1, 2) == v.yyxy());
	VERIFY(Vector4(2, 2, 1, 3) == v.yyxz());
	VERIFY(Vector4(2, 2, 2, 1) == v.yyyx());
	VERIFY(Vector4(2, 2, 2, 2) == v.yyyy());
	VERIFY(Vector4(2, 2, 2, 3) == v.yyyz());
	VERIFY(Vector4(2, 2, 3, 1) == v.yyzx());
	VERIFY(Vector4(2, 2, 3, 2) == v.yyzy());
	VERIFY(Vector4(2, 2, 3, 3) == v.yyzz());
	VERIFY(Vector4(2, 3, 1, 1) == v.yzxx());
	VERIFY(Vector4(2, 3, 1, 2) == v.yzxy());
	VERIFY(Vector4(2, 3, 1, 3) == v.yzxz());
	VERIFY(Vector4(2, 3, 2, 1) == v.yzyx());
	VERIFY(Vector4(2, 3, 2, 2) == v.yzyy());
	VERIFY(Vector4(2, 3, 2, 3) == v.yzyz());
	VERIFY(Vector4(2, 3, 3, 1) == v.yzzx());
	VERIFY(Vector4(2, 3, 3, 2) == v.yzzy());
	VERIFY(Vector4(2, 3, 3, 3) == v.yzzz());
	VERIFY(Vector4(3, 1, 1, 1) == v.zxxx());
	VERIFY(Vector4(3, 1, 1, 2) == v.zxxy());
	VERIFY(Vector4(3, 1, 1, 3) == v.zxxz());
	VERIFY(Vector4(3, 1, 2, 1) == v.zxyx());
	VERIFY(Vector4(3, 1, 2, 2) == v.zxyy());
	VERIFY(Vector4(3, 1, 2, 3) == v.zxyz());
	VERIFY(Vector4(3, 1, 3, 1) == v.zxzx());
	VERIFY(Vector4(3, 1, 3, 2) == v.zxzy());
	VERIFY(Vector4(3, 1, 3, 3) == v.zxzz());
	VERIFY(Vector4(3, 2, 1, 1) == v.zyxx());
	VERIFY(Vector4(3, 2, 1, 2) == v.zyxy());
	VERIFY(Vector4(3, 2, 1, 3) == v.zyxz());
	VERIFY(Vector4(3, 2, 2, 1) == v.zyyx());
	VERIFY(Vector4(3, 2, 2, 2) == v.zyyy());
	VERIFY(Vector4(3, 2, 2, 3) == v.zyyz());
	VERIFY(Vector4(3, 2, 3, 1) == v.zyzx());
	VERIFY(Vector4(3, 2, 3, 2) == v.zyzy());
	VERIFY(Vector4(3, 2, 3, 3) == v.zyzz());
	VERIFY(Vector4(3, 3, 1, 1) == v.zzxx());
	VERIFY(Vector4(3, 3, 1, 2) == v.zzxy());
	VERIFY(Vector4(3, 3, 1, 3) == v.zzxz());
	VERIFY(Vector4(3, 3, 2, 1) == v.zzyx());
	VERIFY(Vector4(3, 3, 2, 2) == v.zzyy());
	VERIFY(Vector4(3, 3, 2, 3) == v.zzyz());
	VERIFY(Vector4(3, 3, 3, 1) == v.zzzx());
	VERIFY(Vector4(3, 3, 3, 2) == v.zzzy());
	VERIFY(Vector4(3, 3, 3, 3) == v.zzzz());

	VERIFY(Vector3(1, 1, 1) == v.xxx());
	VERIFY(Vector3(1, 1, 2) == v.xxy());
	VERIFY(Vector3(1, 1, 3) == v.xxz());
	VERIFY(Vector3(1, 2, 1) == v.xyx());
	VERIFY(Vector3(1, 2, 2) == v.xyy());
	VERIFY(Vector3(1, 2, 3) == v.xyz());
	VERIFY(Vector3(1, 3, 1) == v.xzx());
	VERIFY(Vector3(1, 3, 2) == v.xzy());
	VERIFY(Vector3(1, 3, 3) == v.xzz());
	VERIFY(Vector3(2, 1, 1) == v.yxx());
	VERIFY(Vector3(2, 1, 2) == v.yxy());
	VERIFY(Vector3(2, 1, 3) == v.yxz());
	VERIFY(Vector3(2, 2, 1) == v.yyx());
	VERIFY(Vector3(2, 2, 2) == v.yyy());
	VERIFY(Vector3(2, 2, 3) == v.yyz());
	VERIFY(Vector3(2, 3, 1) == v.yzx());
	VERIFY(Vector3(2, 3, 2) == v.yzy());
	VERIFY(Vector3(2, 3, 3) == v.yzz());
	VERIFY(Vector3(3, 1, 1) == v.zxx());
	VERIFY(Vector3(3, 1, 2) == v.zxy());
	VERIFY(Vector3(3, 1, 3) == v.zxz());
	VERIFY(Vector3(3, 2, 1) == v.zyx());
	VERIFY(Vector3(3, 2, 2) == v.zyy());
	VERIFY(Vector3(3, 2, 3) == v.zyz());
	VERIFY(Vector3(3, 3, 1) == v.zzx());
	VERIFY(Vector3(3, 3, 2) == v.zzy());
	VERIFY(Vector3(3, 3, 3) == v.zzz());

	VERIFY(Vector2(1, 1) == v.xx());
	VERIFY(Vector2(1, 2) == v.xy());
	VERIFY(Vector2(1, 3) == v.xz());
	VERIFY(Vector2(2, 1) == v.yx());
	VERIFY(Vector2(2, 2) == v.yy());
	VERIFY(Vector2(2, 3) == v.yz());
	VERIFY(Vector2(3, 1) == v.zx());
	VERIFY(Vector2(3, 2) == v.zy());
	VERIFY(Vector2(3, 3) == v.zz());

	return true;
}

TYPED_TEST(MathVector3Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Vector3 = bksge::math::Vector3<T>;

	Vector3 v1{1, 2, 3};
	Vector3 v2{5, 6, 7};

	v1.swap(v2);

	VERIFY(v1 == Vector3(5, 6, 7));
	VERIFY(v2 == Vector3(1, 2, 3));

	bksge::ranges::swap(v1, v2);

	VERIFY(v1 == Vector3(1, 2, 3));
	VERIFY(v2 == Vector3(5, 6, 7));

	return true;
}

TYPED_TEST(MathVector3Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	{
		Vector3 const v1(-1, 2, -3);
		Vector3 const v2 = +v1;
		Vector3 const v3 = -v1;

		VERIFY(v2[0] == -1);
		VERIFY(v2[1] ==  2);
		VERIFY(v2[2] == -3);
		VERIFY(v3[0] ==  1);
		VERIFY(v3[1] == -2);
		VERIFY(v3[2] ==  3);
	}
	return true;
}

TYPED_TEST(MathVector3Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	// Vector3 += Vector3
	{
		Vector3 v;
		VERIFY(v == Vector3(0, 0, 0));

		auto t = (v += Vector3(2, 3, -4));
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(v == Vector3(2, 3, -4));
		VERIFY(v == t);
	}
	// Vector3 + Vector3 -> Vector3
	{
		auto t = Vector3(-3, 4, 5) + Vector3(0, 2, -1);
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(t == Vector3(-3, 6, 4));
	}
	return true;
}

TYPED_TEST(MathVector3Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	// Vector3 -= Vector3
	{
		Vector3 v;
		VERIFY(v == Vector3(0, 0, 0));

		auto t = (v -= Vector3(2, 3, -4));
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(v == Vector3(-2, -3, 4));
		VERIFY(v == t);
	}
	// Vector3 - Vector3 -> Vector3
	{
		auto t = Vector3(-3, 4, 5) - Vector3(0, 2, -1);
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(t == Vector3(-3, 2, 6));
	}
	return true;
}

TYPED_TEST(MathVector3Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	// Vector3 *= スカラー
	{
		Vector3 v(2, 3, 4);
		{
			auto t = (v *= 4);
			static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
			VERIFY(v == Vector3(8, 12, 16));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
			VERIFY(v == Vector3(4, 6, 8));
			VERIFY(t == v);
		}
	}
	// Vector3 * スカラー -> Vector3
	{
		auto t = Vector3(-3, 42, 5) * -4;
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(t == Vector3(12, -168, -20));
	}
	{
		auto t = Vector3(4, 6, 2) * 2.5;
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(t == Vector3(10, 15, 5));
	}
	// スカラー * Vector3 -> Vector3
	{
		auto t = 5 * Vector3(7, -8, 9);
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(t == Vector3(35, -40, 45));
	}
	{
		auto t = -1.5 * Vector3(4, -6, -2);
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(t == Vector3(-6, 9, 3));
	}
	return true;
}

TYPED_TEST(MathVector3Test, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	// Vector3 /= スカラー
	{
		Vector3 v(2, 4, 6);
		{
			auto t = (v /= 2);
			static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
			VERIFY(v == Vector3(1, 2, 3));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
			VERIFY(v == Vector3(2, 4, 6));
			VERIFY(t == v);
		}
	}
	// Vector3 / スカラー -> Vector3
	{
		auto t = Vector3(-4, 8, -12) / -4;
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(t == Vector3(1, -2, 3));
	}
	{
		auto t = Vector3(-4, 8, -12) / 0.25;
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(t == Vector3(-16, 32, -48));
	}
	return true;
}

TYPED_TEST(MathVector3Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Vector3 = bksge::math::Vector3<T>;

	Vector3 const v1(1, 2, 3);
	Vector3 const v2(1, 2, 3);
	Vector3 const v3(2, 2, 3);
	Vector3 const v4(1, 0, 3);
	Vector3 const v5(1, 2, 2);

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

TYPED_TEST(MathVector3Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathVector3Test, OutputStreamTest)
{
	using Vector3 = bksge::math::Vector3<TypeParam>;
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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Vector3 = bksge::math::Vector3<T>;

	auto v = Vector3::Zero();
	static_assert(bksge::is_same<decltype(v), Vector3>::value, "");
	VERIFY(0 == v[0]);
	VERIFY(0 == v[1]);
	VERIFY(0 == v[2]);

	return true;
}

TYPED_TEST(MathVector3Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DotTest()
{
	using Vector3 = bksge::math::Vector3<T>;

	VERIFY( 0 == Dot(Vector3( 0, 0, 0), Vector3( 0, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0, 0), Vector3( 1, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0, 0), Vector3(-1, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0, 0), Vector3( 0, 1, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0, 0), Vector3( 0,-1, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0, 0), Vector3( 0, 0, 1)));
	VERIFY( 0 == Dot(Vector3( 0, 0, 0), Vector3( 0, 0,-1)));

	VERIFY( 0 == Dot(Vector3( 1, 0, 0), Vector3( 0, 0, 0)));
	VERIFY( 1 == Dot(Vector3( 1, 0, 0), Vector3( 1, 0, 0)));
	VERIFY(-1 == Dot(Vector3( 1, 0, 0), Vector3(-1, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 1, 0, 0), Vector3( 0, 1, 0)));
	VERIFY( 0 == Dot(Vector3( 1, 0, 0), Vector3( 0,-1, 0)));
	VERIFY( 0 == Dot(Vector3( 1, 0, 0), Vector3( 0, 0, 1)));
	VERIFY( 0 == Dot(Vector3( 1, 0, 0), Vector3( 0, 0,-1)));

	VERIFY( 0 == Dot(Vector3(-1, 0, 0), Vector3( 0, 0, 0)));
	VERIFY(-1 == Dot(Vector3(-1, 0, 0), Vector3( 1, 0, 0)));
	VERIFY( 1 == Dot(Vector3(-1, 0, 0), Vector3(-1, 0, 0)));
	VERIFY( 0 == Dot(Vector3(-1, 0, 0), Vector3( 0, 1, 0)));
	VERIFY( 0 == Dot(Vector3(-1, 0, 0), Vector3( 0,-1, 0)));
	VERIFY( 0 == Dot(Vector3(-1, 0, 0), Vector3( 0, 0, 1)));
	VERIFY( 0 == Dot(Vector3(-1, 0, 0), Vector3( 0, 0,-1)));

	VERIFY( 0 == Dot(Vector3( 0, 1, 0), Vector3( 0, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 1, 0), Vector3( 1, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 1, 0), Vector3(-1, 0, 0)));
	VERIFY( 1 == Dot(Vector3( 0, 1, 0), Vector3( 0, 1, 0)));
	VERIFY(-1 == Dot(Vector3( 0, 1, 0), Vector3( 0,-1, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 1, 0), Vector3( 0, 0, 1)));
	VERIFY( 0 == Dot(Vector3( 0, 1, 0), Vector3( 0, 0,-1)));

	VERIFY( 0 == Dot(Vector3( 0,-1, 0), Vector3( 0, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0,-1, 0), Vector3( 1, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0,-1, 0), Vector3(-1, 0, 0)));
	VERIFY(-1 == Dot(Vector3( 0,-1, 0), Vector3( 0, 1, 0)));
	VERIFY( 1 == Dot(Vector3( 0,-1, 0), Vector3( 0,-1, 0)));
	VERIFY( 0 == Dot(Vector3( 0,-1, 0), Vector3( 0, 0, 1)));
	VERIFY( 0 == Dot(Vector3( 0,-1, 0), Vector3( 0, 0,-1)));

	VERIFY( 0 == Dot(Vector3( 0, 0, 1), Vector3( 0, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0, 1), Vector3( 1, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0, 1), Vector3(-1, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0, 1), Vector3( 0, 1, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0, 1), Vector3( 0,-1, 0)));
	VERIFY( 1 == Dot(Vector3( 0, 0, 1), Vector3( 0, 0, 1)));
	VERIFY(-1 == Dot(Vector3( 0, 0, 1), Vector3( 0, 0,-1)));

	VERIFY( 0 == Dot(Vector3( 0, 0,-1), Vector3( 0, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0,-1), Vector3( 1, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0,-1), Vector3(-1, 0, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0,-1), Vector3( 0, 1, 0)));
	VERIFY( 0 == Dot(Vector3( 0, 0,-1), Vector3( 0,-1, 0)));
	VERIFY(-1 == Dot(Vector3( 0, 0,-1), Vector3( 0, 0, 1)));
	VERIFY( 1 == Dot(Vector3( 0, 0,-1), Vector3( 0, 0,-1)));

	return true;
}

TYPED_TEST(MathVector3Test, DotTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DotTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CrossTest()
{
	using Vector3 = bksge::math::Vector3<T>;

	auto t = Cross(Vector3(0, 0, 0), Vector3(0, 0, 0));
	static_assert(bksge::is_same<decltype(t), Vector3>::value, "");

	VERIFY(Vector3( 0, 0, 0) == t);
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0, 0), Vector3( 1, 0, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0, 0), Vector3(-1, 0, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0, 0), Vector3( 0, 1, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0, 0), Vector3( 0,-1, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0, 0), Vector3( 0, 0, 1)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0, 0), Vector3( 0, 0,-1)));

	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 1, 0, 0), Vector3( 0, 0, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 1, 0, 0), Vector3( 1, 0, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 1, 0, 0), Vector3(-1, 0, 0)));
	VERIFY(Vector3( 0, 0, 1) == Cross(Vector3( 1, 0, 0), Vector3( 0, 1, 0)));
	VERIFY(Vector3( 0, 0,-1) == Cross(Vector3( 1, 0, 0), Vector3( 0,-1, 0)));
	VERIFY(Vector3( 0,-1, 0) == Cross(Vector3( 1, 0, 0), Vector3( 0, 0, 1)));
	VERIFY(Vector3( 0, 1, 0) == Cross(Vector3( 1, 0, 0), Vector3( 0, 0,-1)));

	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3(-1, 0, 0), Vector3( 0, 0, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3(-1, 0, 0), Vector3( 1, 0, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3(-1, 0, 0), Vector3(-1, 0, 0)));
	VERIFY(Vector3( 0, 0,-1) == Cross(Vector3(-1, 0, 0), Vector3( 0, 1, 0)));
	VERIFY(Vector3( 0, 0, 1) == Cross(Vector3(-1, 0, 0), Vector3( 0,-1, 0)));
	VERIFY(Vector3( 0, 1, 0) == Cross(Vector3(-1, 0, 0), Vector3( 0, 0, 1)));
	VERIFY(Vector3( 0,-1, 0) == Cross(Vector3(-1, 0, 0), Vector3( 0, 0,-1)));

	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 1, 0), Vector3( 0, 0, 0)));
	VERIFY(Vector3( 0, 0,-1) == Cross(Vector3( 0, 1, 0), Vector3( 1, 0, 0)));
	VERIFY(Vector3( 0, 0, 1) == Cross(Vector3( 0, 1, 0), Vector3(-1, 0, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 1, 0), Vector3( 0, 1, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 1, 0), Vector3( 0,-1, 0)));
	VERIFY(Vector3( 1, 0, 0) == Cross(Vector3( 0, 1, 0), Vector3( 0, 0, 1)));
	VERIFY(Vector3(-1, 0, 0) == Cross(Vector3( 0, 1, 0), Vector3( 0, 0,-1)));

	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0,-1, 0), Vector3( 0, 0, 0)));
	VERIFY(Vector3( 0, 0, 1) == Cross(Vector3( 0,-1, 0), Vector3( 1, 0, 0)));
	VERIFY(Vector3( 0, 0,-1) == Cross(Vector3( 0,-1, 0), Vector3(-1, 0, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0,-1, 0), Vector3( 0, 1, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0,-1, 0), Vector3( 0,-1, 0)));
	VERIFY(Vector3(-1, 0, 0) == Cross(Vector3( 0,-1, 0), Vector3( 0, 0, 1)));
	VERIFY(Vector3( 1, 0, 0) == Cross(Vector3( 0,-1, 0), Vector3( 0, 0,-1)));

	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0, 1), Vector3( 0, 0, 0)));
	VERIFY(Vector3( 0, 1, 0) == Cross(Vector3( 0, 0, 1), Vector3( 1, 0, 0)));
	VERIFY(Vector3( 0,-1, 0) == Cross(Vector3( 0, 0, 1), Vector3(-1, 0, 0)));
	VERIFY(Vector3(-1, 0, 0) == Cross(Vector3( 0, 0, 1), Vector3( 0, 1, 0)));
	VERIFY(Vector3( 1, 0, 0) == Cross(Vector3( 0, 0, 1), Vector3( 0,-1, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0, 1), Vector3( 0, 0, 1)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0, 1), Vector3( 0, 0,-1)));

	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0,-1), Vector3( 0, 0, 0)));
	VERIFY(Vector3( 0,-1, 0) == Cross(Vector3( 0, 0,-1), Vector3( 1, 0, 0)));
	VERIFY(Vector3( 0, 1, 0) == Cross(Vector3( 0, 0,-1), Vector3(-1, 0, 0)));
	VERIFY(Vector3( 1, 0, 0) == Cross(Vector3( 0, 0,-1), Vector3( 0, 1, 0)));
	VERIFY(Vector3(-1, 0, 0) == Cross(Vector3( 0, 0,-1), Vector3( 0,-1, 0)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0,-1), Vector3( 0, 0, 1)));
	VERIFY(Vector3( 0, 0, 0) == Cross(Vector3( 0, 0,-1), Vector3( 0, 0,-1)));

	return true;
}

TYPED_TEST(MathVector3Test, CrossTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CrossTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SquaredLengthTest()
{
	using Vector3 = bksge::math::Vector3<T>;

	VERIFY(  0 == SquaredLength(Vector3(0, 0, 0)));
	VERIFY(  9 == SquaredLength(Vector3(3, 0, 0)));
	VERIFY( 16 == SquaredLength(Vector3(0, 4, 0)));
	VERIFY( 25 == SquaredLength(Vector3(0, 0,-5)));
	VERIFY( 14 == SquaredLength(Vector3(1, 2, 3)));
	VERIFY( 14 == SquaredLength(Vector3(1,-2, 3)));
	VERIFY(105 == SquaredLength(Vector3(4,-8, 5)));

	return true;
}

TYPED_TEST(MathVector3Test, SquaredLengthTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SquaredLengthTest<TypeParam>());
}

TYPED_TEST(MathVector3Test, LengthTest)
{
	using Vector3 = bksge::math::Vector3<TypeParam>;

	const double error = 0.000001;

	EXPECT_EQ(0, Length(Vector3( 0, 0, 0)));
	EXPECT_EQ(3, Length(Vector3( 3, 0, 0)));
	EXPECT_EQ(3, Length(Vector3(-3, 0, 0)));
	EXPECT_EQ(4, Length(Vector3( 0, 4, 0)));
	EXPECT_EQ(4, Length(Vector3( 0,-4, 0)));
	EXPECT_EQ(5, Length(Vector3( 0, 0, 5)));
	EXPECT_EQ(5, Length(Vector3( 0, 0,-5)));
	EXPECT_NEAR(3.7416573867739413, (double)Length(Vector3( 1, 2, 3)), error);
	EXPECT_NEAR(3.7416573867739413, (double)Length(Vector3( 1,-2,-3)), error);
	EXPECT_NEAR(10.246950765959598, (double)Length(Vector3( 4,-8, 5)), error);
}

TYPED_TEST(MathVector3Test, NormalizedTest)
{
	using Vector3 = bksge::math::Vector3<TypeParam>;

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
		EXPECT_NEAR(0.2672612419124244,  (double)t.x(), error);
		EXPECT_NEAR(0.53452248382484879, (double)t.y(), error);
		EXPECT_NEAR(0.80178372573727319, (double)t.z(), error);
	}
	{
		auto const t = Normalized(Vector3(-5, 6, 7));
		EXPECT_NEAR(-0.47673129462279618, (double)t.x(), error);
		EXPECT_NEAR( 0.57207755354735534, (double)t.y(), error);
		EXPECT_NEAR( 0.66742381247191462, (double)t.z(), error);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool LerpTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	{
		Vector3 v1 {  0,  0,  0 };
		Vector3 v2 { 10, 20, 30 };

		VERIFY(Vector3( 0.0,  0.0,  0.0) == Lerp(v1, v2, 0.00f));
		VERIFY(Vector3( 2.5,  5.0,  7.5) == Lerp(v1, v2, 0.25f));
		VERIFY(Vector3( 5.0, 10.0, 15.0) == Lerp(v1, v2, 0.50f));
		VERIFY(Vector3( 7.5, 15.0, 22.5) == Lerp(v1, v2, 0.75f));
		VERIFY(Vector3(10.0, 20.0, 30.0) == Lerp(v1, v2, 1.00f));
	}
	{
		Vector3 v1 { -10,  10,  20 };
		Vector3 v2 {  10, -20, -30 };

		VERIFY(Vector3(-10.0,  10.0,  20.0) == Lerp(v1, v2, 0.00));
		VERIFY(Vector3( -5.0,   2.5,   7.5) == Lerp(v1, v2, 0.25));
		VERIFY(Vector3(  0.0,  -5.0,  -5.0) == Lerp(v1, v2, 0.50));
		VERIFY(Vector3(  5.0, -12.5, -17.5) == Lerp(v1, v2, 0.75));
		VERIFY(Vector3( 10.0, -20.0, -30.0) == Lerp(v1, v2, 1.00));
	}
	return true;
}

TYPED_TEST(MathVector3Test, LerpTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(LerpTest<TypeParam>());
}

TYPED_TEST(MathVector3Test, SerializeTest)
{
	using namespace bksge::serialization;
	using Vector3 = bksge::math::Vector3<TypeParam>;

	Vector3 const v { 1, -2, 3 };

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
	using Vector3 = bksge::math::Vector3<T>;

	Vector3 const v1(1, 2, 3);
	Vector3 const v2(2, 2, 3);
	Vector3 const v3(1, 0, 3);
	Vector3 const v4(1, 2, 2);
	Vector3 const v5(1, 2, 3);

	std::hash<Vector3> h;

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

TYPED_TEST(MathVector3Test, HashTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

TYPED_TEST(MathVector3Test, TupleElementTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(bksge::is_same<typename std::tuple_element<0, Vector3>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<1, Vector3>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<2, Vector3>::type, T>::value, "");
}

TYPED_TEST(MathVector3Test, TupleSizeTest)
{
	using T = TypeParam;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(std::tuple_size<Vector3>::value == 3, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Vector3 = bksge::math::Vector3<T>;
	{
		Vector3 v{1, 2, 3};

		VERIFY(1 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(3 == bksge::get<2>(v));

		bksge::get<0>(v) = 5;
		bksge::get<2>(v) = 6;

		VERIFY(v == Vector3(5, 2, 6));
		VERIFY(5 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(6 == bksge::get<2>(v));
	}
	{
		Vector3 const v{1, 2, 3};

		VERIFY(1 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(3 == bksge::get<2>(v));
	}
	return true;
}

TYPED_TEST(MathVector3Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

#undef VERIFY

}	// namespace vector3_test

}	// namespace bksge_math_test
