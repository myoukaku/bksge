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
#include <bksge/fnd/concepts/swap.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace vector4_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Vector4f = bksge::math::Vector4<float>;
using Vector4i = bksge::math::Vector4<int>;


using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathVector4Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathVector4Test, MathTestTypes);

TYPED_TEST(MathVector4Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(sizeof(Vector4) == sizeof(T) * 4, "");
	static_assert(bksge::is_default_constructible<Vector4>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Vector4>::value, "");
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
		BKSGE_CONSTEXPR_OR_CONST Vector4 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3]);
	}
}

TYPED_TEST(MathVector4Test, ValueConstructTest)
{
	using T = TypeParam;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(!bksge::is_constructible<Vector4, T, T, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Vector4, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Vector4, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Vector4, T, T>::value, "");
	static_assert( bksge::is_constructible<Vector4, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector4, T, T, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Vector4, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector4, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector4, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Vector4, T>::value, "");
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
		BKSGE_CONSTEXPR_EXPECT_EQ( 9, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector4 v{13};
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[3]);
	}
}

TYPED_TEST(MathVector4Test, Vector3ConstructTest)
{
	using T = TypeParam;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(!bksge::is_constructible<Vector4, Vector3, T, T>::value, "");
	static_assert( bksge::is_constructible<Vector4, Vector3, T>::value, "");
	static_assert(!bksge::is_constructible<Vector4, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector4, Vector3, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Vector4, Vector3, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector4, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector4, Vector3, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Vector4, Vector3, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector4, Vector3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v1(1, 2, 3);
		BKSGE_CONSTEXPR_OR_CONST Vector4 v2(v1, 4);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v1(2, 3, 4);
		BKSGE_CONSTEXPR_OR_CONST Vector4 v2{v1, 5};
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v2[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v1(3, 4, 5);
		BKSGE_CONSTEXPR_OR_CONST Vector4 v2 = {v1, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v2[3]);
	}
}

TYPED_TEST(MathVector4Test, CopyConstructTest)
{
	using T = TypeParam;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(bksge::is_constructible<Vector4,  Vector4  const&>::value, "");
	static_assert(bksge::is_constructible<Vector4,  Vector4i const&>::value, "");
	static_assert(bksge::is_constructible<Vector4,  Vector4f const&>::value, "");
	static_assert(bksge::is_constructible<Vector4i, Vector4  const&>::value, "");
	static_assert(bksge::is_constructible<Vector4i, Vector4i const&>::value, "");
	static_assert(bksge::is_constructible<Vector4i, Vector4f const&>::value, "");
	static_assert(bksge::is_constructible<Vector4f, Vector4  const&>::value, "");
	static_assert(bksge::is_constructible<Vector4f, Vector4i const&>::value, "");
	static_assert(bksge::is_constructible<Vector4f, Vector4f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Vector4,  Vector4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector4,  Vector4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector4,  Vector4f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector4i, Vector4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector4i, Vector4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector4i, Vector4f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector4f, Vector4  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector4f, Vector4i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector4f, Vector4f const&>::value, "");

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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Vector4 = bksge::math::Vector4<T>;

	Vector4 v{0, 1, 2, 3};
	VERIFY(v[0] == 0);
	VERIFY(v[1] == 1);
	VERIFY(v[2] == 2);
	VERIFY(v[3] == 3);

	v = Vector4(-2, 3, -4, 5);
	VERIFY(v[0] == -2);
	VERIFY(v[1] ==  3);
	VERIFY(v[2] == -4);
	VERIFY(v[3] ==  5);

	v = Vector4i(3, -4, 5, -6);
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);
	VERIFY(v[2] ==  5);
	VERIFY(v[3] == -6);

	// 自己代入
	v = v;
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);
	VERIFY(v[2] ==  5);
	VERIFY(v[3] == -6);

	// 多重代入
	Vector4 v2;
	v2 = v = Vector4f(4, 5, 6, 7);
	VERIFY(v[0] == 4);
	VERIFY(v[1] == 5);
	VERIFY(v[2] == 6);
	VERIFY(v[3] == 7);
	VERIFY(v2[0] == 4);
	VERIFY(v2[1] == 5);
	VERIFY(v2[2] == 6);
	VERIFY(v2[3] == 7);

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathVector4Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	{
		Vector4 v{1, 2, 3, 4};
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
		Vector4 const v{5, 6, 7, 8};
		VERIFY(v[0] == 5);
		VERIFY(v[1] == 6);
		VERIFY(v[2] == 7);
		VERIFY(v[3] == 8);
	}
	return true;
}

TYPED_TEST(MathVector4Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	{
		Vector4 v{1, 2, 3, 4};
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
		Vector4 const v{5, 6, 7, 8};
		VERIFY(v.at(0) == 5);
		VERIFY(v.at(1) == 6);
		VERIFY(v.at(2) == 7);
		VERIFY(v.at(3) == 8);
	}
	return true;
}

TYPED_TEST(MathVector4Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Vector4 = bksge::math::Vector4<TypeParam>;
	{
		Vector4 v{1, 2, 3, 4};
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
	{
		Vector4 const v{5, 6, 7, 8};
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	{
		Vector4 v{1, 2, 3, 4};
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

		VERIFY(v == Vector4(5, 2, 6, 4));
	}
	{
		Vector4 const v{1, 2, 3, 4};
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

TYPED_TEST(MathVector4Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Vector4 = bksge::math::Vector4<T>;

	// begin, end (non const)
	{
		Vector4 v{1, 2, 3, 4};
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

		VERIFY(Vector4(5, 2, 6, 4) == v);
	}
	// begin, end (const)
	{
		Vector4 const v{1, 2, 3, 4};
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
		Vector4 v{1, 2, 3, 4};
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

TYPED_TEST(MathVector4Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Vector4 = bksge::math::Vector4<T>;

	// rbegin, rend (non const)
	{
		Vector4 v{1, 2, 3, 4};
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

		VERIFY(Vector4(1, 6, 3, 5) == v);
	}
	// rbegin, rend (const)
	{
		Vector4 const v{1, 2, 3, 4};
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
		Vector4 v{1, 2, 3, 4};
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

TYPED_TEST(MathVector4Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	Vector4 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathVector4Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	Vector4 v1{};
	VERIFY(v1.size() == 4);
	return true;
}

TYPED_TEST(MathVector4Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	Vector4 v1{};
	VERIFY(v1.max_size() == 4);
	return true;
}

TYPED_TEST(MathVector4Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	{
		Vector4 v{1, 2, 3, 4};
		VERIFY(v.x() == 1);
		VERIFY(v.y() == 2);
		VERIFY(v.z() == 3);
		VERIFY(v.w() == 4);

		v.x() = -3;
		v.y() =  4;
		v.z() = -5;
		v.w() =  6;

		VERIFY(v.x() == -3);
		VERIFY(v.y() ==  4);
		VERIFY(v.z() == -5);
		VERIFY(v.w() ==  6);
	}
	{
		Vector4 const v{5, 6, 7, 8};
		VERIFY(v.x() == 5);
		VERIFY(v.y() == 6);
		VERIFY(v.z() == 7);
		VERIFY(v.w() == 8);
	}
	return true;
}

TYPED_TEST(MathVector4Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	Vector4 v(1, 2, 3, 4);

	static_assert(bksge::is_same<decltype(v.xxxx()), Vector4>::value, "");
	static_assert(bksge::is_same<decltype(v.xxx()), Vector3>::value, "");
	static_assert(bksge::is_same<decltype(v.xx()), Vector2>::value, "");

	VERIFY(Vector4(1, 1, 1, 1) == v.xxxx());
	VERIFY(Vector4(1, 1, 1, 2) == v.xxxy());
	VERIFY(Vector4(1, 1, 1, 3) == v.xxxz());
	VERIFY(Vector4(1, 1, 1, 4) == v.xxxw());
	VERIFY(Vector4(1, 1, 2, 1) == v.xxyx());
	VERIFY(Vector4(1, 1, 2, 2) == v.xxyy());
	VERIFY(Vector4(1, 1, 2, 3) == v.xxyz());
	VERIFY(Vector4(1, 1, 2, 4) == v.xxyw());
	VERIFY(Vector4(1, 1, 3, 1) == v.xxzx());
	VERIFY(Vector4(1, 1, 3, 2) == v.xxzy());
	VERIFY(Vector4(1, 1, 3, 3) == v.xxzz());
	VERIFY(Vector4(1, 1, 3, 4) == v.xxzw());
	VERIFY(Vector4(1, 1, 4, 1) == v.xxwx());
	VERIFY(Vector4(1, 1, 4, 2) == v.xxwy());
	VERIFY(Vector4(1, 1, 4, 3) == v.xxwz());
	VERIFY(Vector4(1, 1, 4, 4) == v.xxww());
	VERIFY(Vector4(1, 2, 1, 1) == v.xyxx());
	VERIFY(Vector4(1, 2, 1, 2) == v.xyxy());
	VERIFY(Vector4(1, 2, 1, 3) == v.xyxz());
	VERIFY(Vector4(1, 2, 1, 4) == v.xyxw());
	VERIFY(Vector4(1, 2, 2, 1) == v.xyyx());
	VERIFY(Vector4(1, 2, 2, 2) == v.xyyy());
	VERIFY(Vector4(1, 2, 2, 3) == v.xyyz());
	VERIFY(Vector4(1, 2, 2, 4) == v.xyyw());
	VERIFY(Vector4(1, 2, 3, 1) == v.xyzx());
	VERIFY(Vector4(1, 2, 3, 2) == v.xyzy());
	VERIFY(Vector4(1, 2, 3, 3) == v.xyzz());
	VERIFY(Vector4(1, 2, 3, 4) == v.xyzw());
	VERIFY(Vector4(1, 2, 4, 1) == v.xywx());
	VERIFY(Vector4(1, 2, 4, 2) == v.xywy());
	VERIFY(Vector4(1, 2, 4, 3) == v.xywz());
	VERIFY(Vector4(1, 2, 4, 4) == v.xyww());
	VERIFY(Vector4(1, 3, 1, 1) == v.xzxx());
	VERIFY(Vector4(1, 3, 1, 2) == v.xzxy());
	VERIFY(Vector4(1, 3, 1, 3) == v.xzxz());
	VERIFY(Vector4(1, 3, 1, 4) == v.xzxw());
	VERIFY(Vector4(1, 3, 2, 1) == v.xzyx());
	VERIFY(Vector4(1, 3, 2, 2) == v.xzyy());
	VERIFY(Vector4(1, 3, 2, 3) == v.xzyz());
	VERIFY(Vector4(1, 3, 2, 4) == v.xzyw());
	VERIFY(Vector4(1, 3, 3, 1) == v.xzzx());
	VERIFY(Vector4(1, 3, 3, 2) == v.xzzy());
	VERIFY(Vector4(1, 3, 3, 3) == v.xzzz());
	VERIFY(Vector4(1, 3, 3, 4) == v.xzzw());
	VERIFY(Vector4(1, 3, 4, 1) == v.xzwx());
	VERIFY(Vector4(1, 3, 4, 2) == v.xzwy());
	VERIFY(Vector4(1, 3, 4, 3) == v.xzwz());
	VERIFY(Vector4(1, 3, 4, 4) == v.xzww());
	VERIFY(Vector4(1, 4, 1, 1) == v.xwxx());
	VERIFY(Vector4(1, 4, 1, 2) == v.xwxy());
	VERIFY(Vector4(1, 4, 1, 3) == v.xwxz());
	VERIFY(Vector4(1, 4, 1, 4) == v.xwxw());
	VERIFY(Vector4(1, 4, 2, 1) == v.xwyx());
	VERIFY(Vector4(1, 4, 2, 2) == v.xwyy());
	VERIFY(Vector4(1, 4, 2, 3) == v.xwyz());
	VERIFY(Vector4(1, 4, 2, 4) == v.xwyw());
	VERIFY(Vector4(1, 4, 3, 1) == v.xwzx());
	VERIFY(Vector4(1, 4, 3, 2) == v.xwzy());
	VERIFY(Vector4(1, 4, 3, 3) == v.xwzz());
	VERIFY(Vector4(1, 4, 3, 4) == v.xwzw());
	VERIFY(Vector4(1, 4, 4, 1) == v.xwwx());
	VERIFY(Vector4(1, 4, 4, 2) == v.xwwy());
	VERIFY(Vector4(1, 4, 4, 3) == v.xwwz());
	VERIFY(Vector4(1, 4, 4, 4) == v.xwww());
	VERIFY(Vector4(2, 1, 1, 1) == v.yxxx());
	VERIFY(Vector4(2, 1, 1, 2) == v.yxxy());
	VERIFY(Vector4(2, 1, 1, 3) == v.yxxz());
	VERIFY(Vector4(2, 1, 1, 4) == v.yxxw());
	VERIFY(Vector4(2, 1, 2, 1) == v.yxyx());
	VERIFY(Vector4(2, 1, 2, 2) == v.yxyy());
	VERIFY(Vector4(2, 1, 2, 3) == v.yxyz());
	VERIFY(Vector4(2, 1, 2, 4) == v.yxyw());
	VERIFY(Vector4(2, 1, 3, 1) == v.yxzx());
	VERIFY(Vector4(2, 1, 3, 2) == v.yxzy());
	VERIFY(Vector4(2, 1, 3, 3) == v.yxzz());
	VERIFY(Vector4(2, 1, 3, 4) == v.yxzw());
	VERIFY(Vector4(2, 1, 4, 1) == v.yxwx());
	VERIFY(Vector4(2, 1, 4, 2) == v.yxwy());
	VERIFY(Vector4(2, 1, 4, 3) == v.yxwz());
	VERIFY(Vector4(2, 1, 4, 4) == v.yxww());
	VERIFY(Vector4(2, 2, 1, 1) == v.yyxx());
	VERIFY(Vector4(2, 2, 1, 2) == v.yyxy());
	VERIFY(Vector4(2, 2, 1, 3) == v.yyxz());
	VERIFY(Vector4(2, 2, 1, 4) == v.yyxw());
	VERIFY(Vector4(2, 2, 2, 1) == v.yyyx());
	VERIFY(Vector4(2, 2, 2, 2) == v.yyyy());
	VERIFY(Vector4(2, 2, 2, 3) == v.yyyz());
	VERIFY(Vector4(2, 2, 2, 4) == v.yyyw());
	VERIFY(Vector4(2, 2, 3, 1) == v.yyzx());
	VERIFY(Vector4(2, 2, 3, 2) == v.yyzy());
	VERIFY(Vector4(2, 2, 3, 3) == v.yyzz());
	VERIFY(Vector4(2, 2, 3, 4) == v.yyzw());
	VERIFY(Vector4(2, 2, 4, 1) == v.yywx());
	VERIFY(Vector4(2, 2, 4, 2) == v.yywy());
	VERIFY(Vector4(2, 2, 4, 3) == v.yywz());
	VERIFY(Vector4(2, 2, 4, 4) == v.yyww());
	VERIFY(Vector4(2, 3, 1, 1) == v.yzxx());
	VERIFY(Vector4(2, 3, 1, 2) == v.yzxy());
	VERIFY(Vector4(2, 3, 1, 3) == v.yzxz());
	VERIFY(Vector4(2, 3, 1, 4) == v.yzxw());
	VERIFY(Vector4(2, 3, 2, 1) == v.yzyx());
	VERIFY(Vector4(2, 3, 2, 2) == v.yzyy());
	VERIFY(Vector4(2, 3, 2, 3) == v.yzyz());
	VERIFY(Vector4(2, 3, 2, 4) == v.yzyw());
	VERIFY(Vector4(2, 3, 3, 1) == v.yzzx());
	VERIFY(Vector4(2, 3, 3, 2) == v.yzzy());
	VERIFY(Vector4(2, 3, 3, 3) == v.yzzz());
	VERIFY(Vector4(2, 3, 3, 4) == v.yzzw());
	VERIFY(Vector4(2, 3, 4, 1) == v.yzwx());
	VERIFY(Vector4(2, 3, 4, 2) == v.yzwy());
	VERIFY(Vector4(2, 3, 4, 3) == v.yzwz());
	VERIFY(Vector4(2, 3, 4, 4) == v.yzww());
	VERIFY(Vector4(2, 4, 1, 1) == v.ywxx());
	VERIFY(Vector4(2, 4, 1, 2) == v.ywxy());
	VERIFY(Vector4(2, 4, 1, 3) == v.ywxz());
	VERIFY(Vector4(2, 4, 1, 4) == v.ywxw());
	VERIFY(Vector4(2, 4, 2, 1) == v.ywyx());
	VERIFY(Vector4(2, 4, 2, 2) == v.ywyy());
	VERIFY(Vector4(2, 4, 2, 3) == v.ywyz());
	VERIFY(Vector4(2, 4, 2, 4) == v.ywyw());
	VERIFY(Vector4(2, 4, 3, 1) == v.ywzx());
	VERIFY(Vector4(2, 4, 3, 2) == v.ywzy());
	VERIFY(Vector4(2, 4, 3, 3) == v.ywzz());
	VERIFY(Vector4(2, 4, 3, 4) == v.ywzw());
	VERIFY(Vector4(2, 4, 4, 1) == v.ywwx());
	VERIFY(Vector4(2, 4, 4, 2) == v.ywwy());
	VERIFY(Vector4(2, 4, 4, 3) == v.ywwz());
	VERIFY(Vector4(2, 4, 4, 4) == v.ywww());
	VERIFY(Vector4(3, 1, 1, 1) == v.zxxx());
	VERIFY(Vector4(3, 1, 1, 2) == v.zxxy());
	VERIFY(Vector4(3, 1, 1, 3) == v.zxxz());
	VERIFY(Vector4(3, 1, 1, 4) == v.zxxw());
	VERIFY(Vector4(3, 1, 2, 1) == v.zxyx());
	VERIFY(Vector4(3, 1, 2, 2) == v.zxyy());
	VERIFY(Vector4(3, 1, 2, 3) == v.zxyz());
	VERIFY(Vector4(3, 1, 2, 4) == v.zxyw());
	VERIFY(Vector4(3, 1, 3, 1) == v.zxzx());
	VERIFY(Vector4(3, 1, 3, 2) == v.zxzy());
	VERIFY(Vector4(3, 1, 3, 3) == v.zxzz());
	VERIFY(Vector4(3, 1, 3, 4) == v.zxzw());
	VERIFY(Vector4(3, 1, 4, 1) == v.zxwx());
	VERIFY(Vector4(3, 1, 4, 2) == v.zxwy());
	VERIFY(Vector4(3, 1, 4, 3) == v.zxwz());
	VERIFY(Vector4(3, 1, 4, 4) == v.zxww());
	VERIFY(Vector4(3, 2, 1, 1) == v.zyxx());
	VERIFY(Vector4(3, 2, 1, 2) == v.zyxy());
	VERIFY(Vector4(3, 2, 1, 3) == v.zyxz());
	VERIFY(Vector4(3, 2, 1, 4) == v.zyxw());
	VERIFY(Vector4(3, 2, 2, 1) == v.zyyx());
	VERIFY(Vector4(3, 2, 2, 2) == v.zyyy());
	VERIFY(Vector4(3, 2, 2, 3) == v.zyyz());
	VERIFY(Vector4(3, 2, 2, 4) == v.zyyw());
	VERIFY(Vector4(3, 2, 3, 1) == v.zyzx());
	VERIFY(Vector4(3, 2, 3, 2) == v.zyzy());
	VERIFY(Vector4(3, 2, 3, 3) == v.zyzz());
	VERIFY(Vector4(3, 2, 3, 4) == v.zyzw());
	VERIFY(Vector4(3, 2, 4, 1) == v.zywx());
	VERIFY(Vector4(3, 2, 4, 2) == v.zywy());
	VERIFY(Vector4(3, 2, 4, 3) == v.zywz());
	VERIFY(Vector4(3, 2, 4, 4) == v.zyww());
	VERIFY(Vector4(3, 3, 1, 1) == v.zzxx());
	VERIFY(Vector4(3, 3, 1, 2) == v.zzxy());
	VERIFY(Vector4(3, 3, 1, 3) == v.zzxz());
	VERIFY(Vector4(3, 3, 1, 4) == v.zzxw());
	VERIFY(Vector4(3, 3, 2, 1) == v.zzyx());
	VERIFY(Vector4(3, 3, 2, 2) == v.zzyy());
	VERIFY(Vector4(3, 3, 2, 3) == v.zzyz());
	VERIFY(Vector4(3, 3, 2, 4) == v.zzyw());
	VERIFY(Vector4(3, 3, 3, 1) == v.zzzx());
	VERIFY(Vector4(3, 3, 3, 2) == v.zzzy());
	VERIFY(Vector4(3, 3, 3, 3) == v.zzzz());
	VERIFY(Vector4(3, 3, 3, 4) == v.zzzw());
	VERIFY(Vector4(3, 3, 4, 1) == v.zzwx());
	VERIFY(Vector4(3, 3, 4, 2) == v.zzwy());
	VERIFY(Vector4(3, 3, 4, 3) == v.zzwz());
	VERIFY(Vector4(3, 3, 4, 4) == v.zzww());
	VERIFY(Vector4(3, 4, 1, 1) == v.zwxx());
	VERIFY(Vector4(3, 4, 1, 2) == v.zwxy());
	VERIFY(Vector4(3, 4, 1, 3) == v.zwxz());
	VERIFY(Vector4(3, 4, 1, 4) == v.zwxw());
	VERIFY(Vector4(3, 4, 2, 1) == v.zwyx());
	VERIFY(Vector4(3, 4, 2, 2) == v.zwyy());
	VERIFY(Vector4(3, 4, 2, 3) == v.zwyz());
	VERIFY(Vector4(3, 4, 2, 4) == v.zwyw());
	VERIFY(Vector4(3, 4, 3, 1) == v.zwzx());
	VERIFY(Vector4(3, 4, 3, 2) == v.zwzy());
	VERIFY(Vector4(3, 4, 3, 3) == v.zwzz());
	VERIFY(Vector4(3, 4, 3, 4) == v.zwzw());
	VERIFY(Vector4(3, 4, 4, 1) == v.zwwx());
	VERIFY(Vector4(3, 4, 4, 2) == v.zwwy());
	VERIFY(Vector4(3, 4, 4, 3) == v.zwwz());
	VERIFY(Vector4(3, 4, 4, 4) == v.zwww());
	VERIFY(Vector4(4, 1, 1, 1) == v.wxxx());
	VERIFY(Vector4(4, 1, 1, 2) == v.wxxy());
	VERIFY(Vector4(4, 1, 1, 3) == v.wxxz());
	VERIFY(Vector4(4, 1, 1, 4) == v.wxxw());
	VERIFY(Vector4(4, 1, 2, 1) == v.wxyx());
	VERIFY(Vector4(4, 1, 2, 2) == v.wxyy());
	VERIFY(Vector4(4, 1, 2, 3) == v.wxyz());
	VERIFY(Vector4(4, 1, 2, 4) == v.wxyw());
	VERIFY(Vector4(4, 1, 3, 1) == v.wxzx());
	VERIFY(Vector4(4, 1, 3, 2) == v.wxzy());
	VERIFY(Vector4(4, 1, 3, 3) == v.wxzz());
	VERIFY(Vector4(4, 1, 3, 4) == v.wxzw());
	VERIFY(Vector4(4, 1, 4, 1) == v.wxwx());
	VERIFY(Vector4(4, 1, 4, 2) == v.wxwy());
	VERIFY(Vector4(4, 1, 4, 3) == v.wxwz());
	VERIFY(Vector4(4, 1, 4, 4) == v.wxww());
	VERIFY(Vector4(4, 2, 1, 1) == v.wyxx());
	VERIFY(Vector4(4, 2, 1, 2) == v.wyxy());
	VERIFY(Vector4(4, 2, 1, 3) == v.wyxz());
	VERIFY(Vector4(4, 2, 1, 4) == v.wyxw());
	VERIFY(Vector4(4, 2, 2, 1) == v.wyyx());
	VERIFY(Vector4(4, 2, 2, 2) == v.wyyy());
	VERIFY(Vector4(4, 2, 2, 3) == v.wyyz());
	VERIFY(Vector4(4, 2, 2, 4) == v.wyyw());
	VERIFY(Vector4(4, 2, 3, 1) == v.wyzx());
	VERIFY(Vector4(4, 2, 3, 2) == v.wyzy());
	VERIFY(Vector4(4, 2, 3, 3) == v.wyzz());
	VERIFY(Vector4(4, 2, 3, 4) == v.wyzw());
	VERIFY(Vector4(4, 2, 4, 1) == v.wywx());
	VERIFY(Vector4(4, 2, 4, 2) == v.wywy());
	VERIFY(Vector4(4, 2, 4, 3) == v.wywz());
	VERIFY(Vector4(4, 2, 4, 4) == v.wyww());
	VERIFY(Vector4(4, 3, 1, 1) == v.wzxx());
	VERIFY(Vector4(4, 3, 1, 2) == v.wzxy());
	VERIFY(Vector4(4, 3, 1, 3) == v.wzxz());
	VERIFY(Vector4(4, 3, 1, 4) == v.wzxw());
	VERIFY(Vector4(4, 3, 2, 1) == v.wzyx());
	VERIFY(Vector4(4, 3, 2, 2) == v.wzyy());
	VERIFY(Vector4(4, 3, 2, 3) == v.wzyz());
	VERIFY(Vector4(4, 3, 2, 4) == v.wzyw());
	VERIFY(Vector4(4, 3, 3, 1) == v.wzzx());
	VERIFY(Vector4(4, 3, 3, 2) == v.wzzy());
	VERIFY(Vector4(4, 3, 3, 3) == v.wzzz());
	VERIFY(Vector4(4, 3, 3, 4) == v.wzzw());
	VERIFY(Vector4(4, 3, 4, 1) == v.wzwx());
	VERIFY(Vector4(4, 3, 4, 2) == v.wzwy());
	VERIFY(Vector4(4, 3, 4, 3) == v.wzwz());
	VERIFY(Vector4(4, 3, 4, 4) == v.wzww());
	VERIFY(Vector4(4, 4, 1, 1) == v.wwxx());
	VERIFY(Vector4(4, 4, 1, 2) == v.wwxy());
	VERIFY(Vector4(4, 4, 1, 3) == v.wwxz());
	VERIFY(Vector4(4, 4, 1, 4) == v.wwxw());
	VERIFY(Vector4(4, 4, 2, 1) == v.wwyx());
	VERIFY(Vector4(4, 4, 2, 2) == v.wwyy());
	VERIFY(Vector4(4, 4, 2, 3) == v.wwyz());
	VERIFY(Vector4(4, 4, 2, 4) == v.wwyw());
	VERIFY(Vector4(4, 4, 3, 1) == v.wwzx());
	VERIFY(Vector4(4, 4, 3, 2) == v.wwzy());
	VERIFY(Vector4(4, 4, 3, 3) == v.wwzz());
	VERIFY(Vector4(4, 4, 3, 4) == v.wwzw());
	VERIFY(Vector4(4, 4, 4, 1) == v.wwwx());
	VERIFY(Vector4(4, 4, 4, 2) == v.wwwy());
	VERIFY(Vector4(4, 4, 4, 3) == v.wwwz());
	VERIFY(Vector4(4, 4, 4, 4) == v.wwww());

	VERIFY(Vector3(1, 1, 1) == v.xxx());
	VERIFY(Vector3(1, 1, 2) == v.xxy());
	VERIFY(Vector3(1, 1, 3) == v.xxz());
	VERIFY(Vector3(1, 1, 4) == v.xxw());
	VERIFY(Vector3(1, 2, 1) == v.xyx());
	VERIFY(Vector3(1, 2, 2) == v.xyy());
	VERIFY(Vector3(1, 2, 3) == v.xyz());
	VERIFY(Vector3(1, 2, 4) == v.xyw());
	VERIFY(Vector3(1, 3, 1) == v.xzx());
	VERIFY(Vector3(1, 3, 2) == v.xzy());
	VERIFY(Vector3(1, 3, 3) == v.xzz());
	VERIFY(Vector3(1, 3, 4) == v.xzw());
	VERIFY(Vector3(1, 4, 1) == v.xwx());
	VERIFY(Vector3(1, 4, 2) == v.xwy());
	VERIFY(Vector3(1, 4, 3) == v.xwz());
	VERIFY(Vector3(1, 4, 4) == v.xww());
	VERIFY(Vector3(2, 1, 1) == v.yxx());
	VERIFY(Vector3(2, 1, 2) == v.yxy());
	VERIFY(Vector3(2, 1, 3) == v.yxz());
	VERIFY(Vector3(2, 1, 4) == v.yxw());
	VERIFY(Vector3(2, 2, 1) == v.yyx());
	VERIFY(Vector3(2, 2, 2) == v.yyy());
	VERIFY(Vector3(2, 2, 3) == v.yyz());
	VERIFY(Vector3(2, 2, 4) == v.yyw());
	VERIFY(Vector3(2, 3, 1) == v.yzx());
	VERIFY(Vector3(2, 3, 2) == v.yzy());
	VERIFY(Vector3(2, 3, 3) == v.yzz());
	VERIFY(Vector3(2, 3, 4) == v.yzw());
	VERIFY(Vector3(2, 4, 1) == v.ywx());
	VERIFY(Vector3(2, 4, 2) == v.ywy());
	VERIFY(Vector3(2, 4, 3) == v.ywz());
	VERIFY(Vector3(2, 4, 4) == v.yww());
	VERIFY(Vector3(3, 1, 1) == v.zxx());
	VERIFY(Vector3(3, 1, 2) == v.zxy());
	VERIFY(Vector3(3, 1, 3) == v.zxz());
	VERIFY(Vector3(3, 1, 4) == v.zxw());
	VERIFY(Vector3(3, 2, 1) == v.zyx());
	VERIFY(Vector3(3, 2, 2) == v.zyy());
	VERIFY(Vector3(3, 2, 3) == v.zyz());
	VERIFY(Vector3(3, 2, 4) == v.zyw());
	VERIFY(Vector3(3, 3, 1) == v.zzx());
	VERIFY(Vector3(3, 3, 2) == v.zzy());
	VERIFY(Vector3(3, 3, 3) == v.zzz());
	VERIFY(Vector3(3, 3, 4) == v.zzw());
	VERIFY(Vector3(3, 4, 1) == v.zwx());
	VERIFY(Vector3(3, 4, 2) == v.zwy());
	VERIFY(Vector3(3, 4, 3) == v.zwz());
	VERIFY(Vector3(3, 4, 4) == v.zww());
	VERIFY(Vector3(4, 1, 1) == v.wxx());
	VERIFY(Vector3(4, 1, 2) == v.wxy());
	VERIFY(Vector3(4, 1, 3) == v.wxz());
	VERIFY(Vector3(4, 1, 4) == v.wxw());
	VERIFY(Vector3(4, 2, 1) == v.wyx());
	VERIFY(Vector3(4, 2, 2) == v.wyy());
	VERIFY(Vector3(4, 2, 3) == v.wyz());
	VERIFY(Vector3(4, 2, 4) == v.wyw());
	VERIFY(Vector3(4, 3, 1) == v.wzx());
	VERIFY(Vector3(4, 3, 2) == v.wzy());
	VERIFY(Vector3(4, 3, 3) == v.wzz());
	VERIFY(Vector3(4, 3, 4) == v.wzw());
	VERIFY(Vector3(4, 4, 1) == v.wwx());
	VERIFY(Vector3(4, 4, 2) == v.wwy());
	VERIFY(Vector3(4, 4, 3) == v.wwz());
	VERIFY(Vector3(4, 4, 4) == v.www());

	VERIFY(Vector2(1, 1) == v.xx());
	VERIFY(Vector2(1, 2) == v.xy());
	VERIFY(Vector2(1, 3) == v.xz());
	VERIFY(Vector2(1, 4) == v.xw());
	VERIFY(Vector2(2, 1) == v.yx());
	VERIFY(Vector2(2, 2) == v.yy());
	VERIFY(Vector2(2, 3) == v.yz());
	VERIFY(Vector2(2, 4) == v.yw());
	VERIFY(Vector2(3, 1) == v.zx());
	VERIFY(Vector2(3, 2) == v.zy());
	VERIFY(Vector2(3, 3) == v.zz());
	VERIFY(Vector2(3, 4) == v.zw());
	VERIFY(Vector2(4, 1) == v.wx());
	VERIFY(Vector2(4, 2) == v.wy());
	VERIFY(Vector2(4, 3) == v.wz());
	VERIFY(Vector2(4, 4) == v.ww());

	return true;
}

TYPED_TEST(MathVector4Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Vector4 = bksge::math::Vector4<T>;

	Vector4 v1{1, 2, 3, 4};
	Vector4 v2{5, 6, 7, 8};

	v1.swap(v2);

	VERIFY(v1 == Vector4(5, 6, 7, 8));
	VERIFY(v2 == Vector4(1, 2, 3, 4));

	bksge::ranges::swap(v1, v2);

	VERIFY(v1 == Vector4(1, 2, 3, 4));
	VERIFY(v2 == Vector4(5, 6, 7, 8));

	return true;
}

TYPED_TEST(MathVector4Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	{
		Vector4 const v1(-1, 2, -3, 4);
		auto const v2 = +v1;
		auto const v3 = -v1;
		static_assert(bksge::is_same<decltype(v2), Vector4 const>::value, "");
		static_assert(bksge::is_same<decltype(v3), Vector4 const>::value, "");

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

TYPED_TEST(MathVector4Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	// Vector4 += Vector4
	{
		Vector4 v;
		VERIFY(v == Vector4(0, 0, 0, 0));

		auto t = (v += Vector4(2, 3, -4, 5));
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(v == Vector4(2, 3, -4, 5));
		VERIFY(v == t);
	}
	// Vector4 + Vector4 -> Vector4
	{
		auto t = Vector4(-3, 4, 5, 6) + Vector4(0, 2, -1, 3);
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(t == Vector4(-3, 6, 4, 9));
	}
	return true;
}

TYPED_TEST(MathVector4Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	// Vector4 -= Vector4
	{
		Vector4 v;
		VERIFY(v == Vector4(0, 0, 0, 0));

		auto t = (v -= Vector4(2, 3, -4, 5));
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(v == Vector4(-2, -3, 4, -5));
		VERIFY(v == t);
	}
	// Vector4 - Vector4 -> Vector4
	{
		auto t = Vector4(-3, 4, 5, 6) - Vector4(0, 2, -1, 3);
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(t == Vector4(-3, 2, 6, 3));
	}
	return true;
}

TYPED_TEST(MathVector4Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	// Vector4 *= スカラー
	{
		Vector4 v(2, 3, 4, 5);
		{
			auto t = (v *= 4);
			static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
			VERIFY(v == Vector4(8, 12, 16, 20));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
			VERIFY(v == Vector4(4, 6, 8, 10));
			VERIFY(t == v);
		}
	}
	// Vector4 * スカラー -> Vector4
	{
		auto t = Vector4(-3, 42, 5, 4) * -4;
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(t == Vector4(12, -168, -20, -16));
	}
	{
		auto t = Vector4(4, 6, 2, -10) * 2.5;
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(t == Vector4(10, 15, 5, -25));
	}
	// スカラー * Vector4 -> Vector4
	{
		auto t = 5 * Vector4(7, -8, 9, 2);
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(t == Vector4(35, -40, 45, 10));
	}
	{
		auto t = -1.5 * Vector4(4, -6, -2, 8);
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(t == Vector4(-6, 9, 3, -12));
	}
	return true;
}

TYPED_TEST(MathVector4Test, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	// Vector4 /= スカラー
	{
		Vector4 v(2, 4, 6, 8);
		{
			auto t = (v /= 2);
			static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
			VERIFY(v == Vector4(1, 2, 3, 4));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
			VERIFY(v == Vector4(2, 4, 6, 8));
			VERIFY(t == v);
		}
	}
	// Vector4 / スカラー -> Vector4
	{
		auto t = Vector4(-4, 8, -12, 16) / -4;
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(t == Vector4(1, -2, 3, -4));
	}
	{
		auto t = Vector4(-4, 8, -12, 16) / 0.25;
		static_assert(bksge::is_same<decltype(t), Vector4>::value, "");
		VERIFY(t == Vector4(-16, 32, -48, 64));
	}
	return true;
}

TYPED_TEST(MathVector4Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Vector4 = bksge::math::Vector4<T>;

	Vector4 const v1(1, 2, 3, 4);
	Vector4 const v2(1, 2, 3, 4);
	Vector4 const v3(2, 2, 3, 4);
	Vector4 const v4(1, 0, 3, 4);
	Vector4 const v5(1, 2, 2, 4);
	Vector4 const v6(1, 2, 3, 5);

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

TYPED_TEST(MathVector4Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathVector4Test, OutputStreamTest)
{
	using Vector4 = bksge::math::Vector4<TypeParam>;
	{
		Vector4 const v{1, -2, 3, 4};
		bksge::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2, 3, 4 }", ss.str());
	}
	{
		Vector4 const v{-10, 9, 8, -7};
		bksge::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9, 8, -7 }", ss.str());
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Vector4 = bksge::math::Vector4<T>;

	auto v = Vector4::Zero();
	static_assert(bksge::is_same<decltype(v), Vector4>::value, "");
	VERIFY(0 == v[0]);
	VERIFY(0 == v[1]);
	VERIFY(0 == v[2]);
	VERIFY(0 == v[3]);

	return true;
}

TYPED_TEST(MathVector4Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DotTest()
{
	using Vector4 = bksge::math::Vector4<T>;

	VERIFY( 0 == Dot(Vector4( 0, 0, 0, 0), Vector4( 0, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0, 0, 0), Vector4( 1, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0, 0, 0), Vector4(-1, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0, 0, 0), Vector4( 0, 1, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0, 0, 0), Vector4( 0,-1, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0, 0, 0), Vector4( 0, 0, 1, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0, 0, 0), Vector4( 0, 0,-1, 0)));

	VERIFY( 0 == Dot(Vector4( 1, 0, 0, 0), Vector4( 0, 0, 0, 0)));
	VERIFY( 1 == Dot(Vector4( 1, 0, 0, 0), Vector4( 1, 0, 0, 0)));
	VERIFY(-1 == Dot(Vector4( 1, 0, 0, 0), Vector4(-1, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 1, 0, 0, 0), Vector4( 0, 1, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 1, 0, 0, 0), Vector4( 0,-1, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 1, 0, 0, 0), Vector4( 0, 0, 1, 0)));
	VERIFY( 0 == Dot(Vector4( 1, 0, 0, 0), Vector4( 0, 0,-1, 0)));

	VERIFY( 0 == Dot(Vector4(-1, 0, 0, 0), Vector4( 0, 0, 0, 0)));
	VERIFY(-1 == Dot(Vector4(-1, 0, 0, 0), Vector4( 1, 0, 0, 0)));
	VERIFY( 1 == Dot(Vector4(-1, 0, 0, 0), Vector4(-1, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4(-1, 0, 0, 0), Vector4( 0, 1, 0, 0)));
	VERIFY( 0 == Dot(Vector4(-1, 0, 0, 0), Vector4( 0,-1, 0, 0)));
	VERIFY( 0 == Dot(Vector4(-1, 0, 0, 0), Vector4( 0, 0, 1, 0)));
	VERIFY( 0 == Dot(Vector4(-1, 0, 0, 0), Vector4( 0, 0,-1, 0)));

	VERIFY( 0 == Dot(Vector4( 0, 1, 0, 0), Vector4( 0, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 1, 0, 0), Vector4( 1, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 1, 0, 0), Vector4(-1, 0, 0, 0)));
	VERIFY( 1 == Dot(Vector4( 0, 1, 0, 0), Vector4( 0, 1, 0, 0)));
	VERIFY(-1 == Dot(Vector4( 0, 1, 0, 0), Vector4( 0,-1, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 1, 0, 0), Vector4( 0, 0, 1, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 1, 0, 0), Vector4( 0, 0,-1, 0)));

	VERIFY( 0 == Dot(Vector4( 0,-1, 0, 0), Vector4( 0, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0,-1, 0, 0), Vector4( 1, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0,-1, 0, 0), Vector4(-1, 0, 0, 0)));
	VERIFY(-1 == Dot(Vector4( 0,-1, 0, 0), Vector4( 0, 1, 0, 0)));
	VERIFY( 1 == Dot(Vector4( 0,-1, 0, 0), Vector4( 0,-1, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0,-1, 0, 0), Vector4( 0, 0, 1, 0)));
	VERIFY( 0 == Dot(Vector4( 0,-1, 0, 0), Vector4( 0, 0,-1, 0)));

	VERIFY( 0 == Dot(Vector4( 0, 0, 1, 0), Vector4( 0, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0, 1, 0), Vector4( 1, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0, 1, 0), Vector4(-1, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0, 1, 0), Vector4( 0, 1, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0, 1, 0), Vector4( 0,-1, 0, 0)));
	VERIFY( 1 == Dot(Vector4( 0, 0, 1, 0), Vector4( 0, 0, 1, 0)));
	VERIFY(-1 == Dot(Vector4( 0, 0, 1, 0), Vector4( 0, 0,-1, 0)));

	VERIFY( 0 == Dot(Vector4( 0, 0,-1, 0), Vector4( 0, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0,-1, 0), Vector4( 1, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0,-1, 0), Vector4(-1, 0, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0,-1, 0), Vector4( 0, 1, 0, 0)));
	VERIFY( 0 == Dot(Vector4( 0, 0,-1, 0), Vector4( 0,-1, 0, 0)));
	VERIFY(-1 == Dot(Vector4( 0, 0,-1, 0), Vector4( 0, 0, 1, 0)));
	VERIFY( 1 == Dot(Vector4( 0, 0,-1, 0), Vector4( 0, 0,-1, 0)));

	return true;
}

TYPED_TEST(MathVector4Test, DotTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DotTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SquaredLengthTest()
{
	using Vector4 = bksge::math::Vector4<T>;

	VERIFY(  0 == SquaredLength(Vector4(0, 0, 0, 0)));
	VERIFY(  9 == SquaredLength(Vector4(3, 0, 0, 0)));
	VERIFY( 16 == SquaredLength(Vector4(0, 4, 0, 0)));
	VERIFY( 25 == SquaredLength(Vector4(0, 0,-5, 0)));
	VERIFY( 36 == SquaredLength(Vector4(0, 0, 0, 6)));
	VERIFY( 30 == SquaredLength(Vector4(1, 2, 3, 4)));
	VERIFY( 30 == SquaredLength(Vector4(1,-2, 3, 4)));
	VERIFY( 30 == SquaredLength(Vector4(1, 2, 3,-4)));
	VERIFY(109 == SquaredLength(Vector4(4,-8, 5, 2)));

	return true;
}

TYPED_TEST(MathVector4Test, SquaredLengthTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SquaredLengthTest<TypeParam>());
}

TYPED_TEST(MathVector4Test, LengthTest)
{
	using Vector4 = bksge::math::Vector4<TypeParam>;

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

TYPED_TEST(MathVector4Test, NormalizedTest)
{
	using Vector4 = bksge::math::Vector4<TypeParam>;

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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool LerpTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	{
		Vector4 v1 {  0,  0,  0,  0 };
		Vector4 v2 { 10, 20, 30, 40 };

		VERIFY(Vector4( 0.0,  0.0,  0.0,  0.0) == Lerp(v1, v2, 0.00f));
		VERIFY(Vector4( 2.5,  5.0,  7.5, 10.0) == Lerp(v1, v2, 0.25f));
		VERIFY(Vector4( 5.0, 10.0, 15.0, 20.0) == Lerp(v1, v2, 0.50f));
		VERIFY(Vector4( 7.5, 15.0, 22.5, 30.0) == Lerp(v1, v2, 0.75f));
		VERIFY(Vector4(10.0, 20.0, 30.0, 40.0) == Lerp(v1, v2, 1.00f));
	}
	{
		Vector4 v1 { -10,  10,  20, -30 };
		Vector4 v2 {  10, -20, -30,  40 };

		VERIFY(Vector4(-10.0,  10.0,  20.0, -30.0) == Lerp(v1, v2, 0.00));
		VERIFY(Vector4( -5.0,   2.5,   7.5, -12.5) == Lerp(v1, v2, 0.25));
		VERIFY(Vector4(  0.0,  -5.0,  -5.0,   5.0) == Lerp(v1, v2, 0.50));
		VERIFY(Vector4(  5.0, -12.5, -17.5,  22.5) == Lerp(v1, v2, 0.75));
		VERIFY(Vector4( 10.0, -20.0, -30.0,  40.0) == Lerp(v1, v2, 1.00));
	}
	return true;
}

TYPED_TEST(MathVector4Test, LerpTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(LerpTest<TypeParam>());
}

TYPED_TEST(MathVector4Test, SerializeTest)
{
	using namespace bksge::serialization;
	using Vector4 = bksge::math::Vector4<TypeParam>;

	Vector4 const v { 1, -2, 3, -4 };

	SerializeTest<text_oarchive,   text_iarchive,   bksge::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   bksge::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    bksge::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, bksge::wstringstream>(v);
#endif
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool HashTest()
{
	using Vector4 = bksge::math::Vector4<T>;

	Vector4 const v1(1, 2, 3, 4);
	Vector4 const v2(2, 2, 3, 4);
	Vector4 const v3(1, 0, 3, 4);
	Vector4 const v4(1, 2, 2, 4);
	Vector4 const v5(1, 2, 3, 0);

	std::hash<Vector4> h;

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

TYPED_TEST(MathVector4Test, HashTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

TYPED_TEST(MathVector4Test, TupleElementTest)
{
	using T = TypeParam;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(bksge::is_same<typename bksge::tuple_element<0, Vector4>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<1, Vector4>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<2, Vector4>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<3, Vector4>::type, T>::value, "");
}

TYPED_TEST(MathVector4Test, TupleSizeTest)
{
	using T = TypeParam;
	using Vector4 = bksge::math::Vector4<T>;

	static_assert(bksge::tuple_size<Vector4>::value == 4, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Vector4 = bksge::math::Vector4<T>;
	using std::get;
	{
		Vector4 v{1, 2, 3, 4};

		VERIFY(1 == get<0>(v));
		VERIFY(2 == get<1>(v));
		VERIFY(3 == get<2>(v));
		VERIFY(4 == get<3>(v));

		get<0>(v) = 5;
		get<3>(v) = 6;

		VERIFY(v == Vector4(5, 2, 3, 6));
		VERIFY(5 == get<0>(v));
		VERIFY(2 == get<1>(v));
		VERIFY(3 == get<2>(v));
		VERIFY(6 == get<3>(v));
	}
	{
		Vector4 const v{1, 2, 3, 4};

		VERIFY(1 == get<0>(v));
		VERIFY(2 == get<1>(v));
		VERIFY(3 == get<2>(v));
		VERIFY(4 == get<3>(v));
	}
	return true;
}

TYPED_TEST(MathVector4Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

#undef VERIFY

}	// namespace vector4_test

}	// namespace bksge_math_test
