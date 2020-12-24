/**
 *	@file	unit_test_core_math_extent3.cpp
 *
 *	@brief	Extent3 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/extent3.hpp>
#include <bksge/core/math/extent2.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/scale3.hpp>
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
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace extent3_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Extent3f = bksge::math::Extent3<float>;
using Extent3i = bksge::math::Extent3<int>;


using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathExtent3Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathExtent3Test, MathTestTypes);

TYPED_TEST(MathExtent3Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Extent3 = bksge::math::Extent3<T>;

	static_assert(sizeof(Extent3) == sizeof(T) * 3, "");
	static_assert(bksge::is_default_constructible<Extent3>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Extent3>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Extent3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Extent3 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent3 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent3 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
	}
}

TYPED_TEST(MathExtent3Test, ValueConstructTest)
{
	using T = TypeParam;
	using Extent3 = bksge::math::Extent3<T>;

	static_assert(!bksge::is_constructible<Extent3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Extent3, T, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Extent3, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Extent3, T, T>::value, "");
	static_assert( bksge::is_constructible<Extent3, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent3, T, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Extent3, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent3, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Extent3, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Extent3, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Extent3, T, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Extent3, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Extent3, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Extent3, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Extent3 v(1, 2, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent3 v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent3 v = {9, 10, 11};
		BKSGE_CONSTEXPR_EXPECT_EQ( 9, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent3 v{13};
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[2]);
	}
}

TYPED_TEST(MathExtent3Test, Extent2ConstructTest)
{
	using T = TypeParam;
	using Extent3 = bksge::math::Extent3<T>;
	using Extent2 = bksge::math::Extent2<T>;

	static_assert(!bksge::is_constructible<Extent3, Extent2, T, T>::value, "");
	static_assert( bksge::is_constructible<Extent3, Extent2, T>::value, "");
	static_assert(!bksge::is_constructible<Extent3, Extent2>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent3, Extent2, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Extent3, Extent2, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent3, Extent2>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Extent3, Extent2, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Extent3, Extent2, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Extent3, Extent2>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v1(1, 2);
		BKSGE_CONSTEXPR_OR_CONST Extent3 v2(v1, 4);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v1(2, 3);
		BKSGE_CONSTEXPR_OR_CONST Extent3 v2{v1, 5};
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v2[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v1(3, 4);
		BKSGE_CONSTEXPR_OR_CONST Extent3 v2 = {v1, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v2[2]);
	}
}

TYPED_TEST(MathExtent3Test, CopyConstructTest)
{
	using T = TypeParam;
	using Extent3 = bksge::math::Extent3<T>;

	static_assert(bksge::is_constructible<Extent3,  Extent3  const&>::value, "");
	static_assert(bksge::is_constructible<Extent3,  Extent3i const&>::value, "");
	static_assert(bksge::is_constructible<Extent3,  Extent3f const&>::value, "");
	static_assert(bksge::is_constructible<Extent3i, Extent3  const&>::value, "");
	static_assert(bksge::is_constructible<Extent3i, Extent3i const&>::value, "");
	static_assert(bksge::is_constructible<Extent3i, Extent3f const&>::value, "");
	static_assert(bksge::is_constructible<Extent3f, Extent3  const&>::value, "");
	static_assert(bksge::is_constructible<Extent3f, Extent3i const&>::value, "");
	static_assert(bksge::is_constructible<Extent3f, Extent3f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Extent3,  Extent3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent3,  Extent3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent3,  Extent3f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent3i, Extent3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent3i, Extent3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent3i, Extent3f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent3f, Extent3  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent3f, Extent3i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent3f, Extent3f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Extent3,  Extent3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent3,  Extent3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent3,  Extent3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent3i, Extent3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent3i, Extent3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent3i, Extent3f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent3f, Extent3  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent3f, Extent3i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent3f, Extent3f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Extent3  v1{1, 2, 3};
	BKSGE_CONSTEXPR_OR_CONST Extent3  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Extent3i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Extent3f v4{v2};

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
	using Extent3 = bksge::math::Extent3<T>;

	Extent3 v{0, 1, 2};
	VERIFY(v[0] == 0);
	VERIFY(v[1] == 1);
	VERIFY(v[2] == 2);

	v = Extent3(-2, 3, -4);
	VERIFY(v[0] == -2);
	VERIFY(v[1] ==  3);
	VERIFY(v[2] == -4);

	v = Extent3i(3, -4, 5);
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);
	VERIFY(v[2] ==  5);

	// 自己代入
	v = v;
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);
	VERIFY(v[2] ==  5);

	// 多重代入
	Extent3 v2;
	v2 = v = Extent3f(4, 5, 6);
	VERIFY(v[0] == 4);
	VERIFY(v[1] == 5);
	VERIFY(v[2] == 6);
	VERIFY(v2[0] == 4);
	VERIFY(v2[1] == 5);
	VERIFY(v2[2] == 6);

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathExtent3Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	{
		Extent3 v{1, 2, 3};
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
		Extent3 const v{5, 6, 7};
		VERIFY(v[0] == 5);
		VERIFY(v[1] == 6);
		VERIFY(v[2] == 7);
	}
	return true;
}

TYPED_TEST(MathExtent3Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	{
		Extent3 v{1, 2, 3};
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
		Extent3 const v{5, 6, 7};
		VERIFY(v.at(0) == 5);
		VERIFY(v.at(1) == 6);
		VERIFY(v.at(2) == 7);
	}
	return true;
}

TYPED_TEST(MathExtent3Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Extent3 = bksge::math::Extent3<TypeParam>;
	{
		Extent3 v{1, 2, 3};
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
	{
		Extent3 const v{5, 6, 7};
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	{
		Extent3 v{1, 2, 3};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == 1);
		*p = 5;
		++p;
		VERIFY(*p == 2);
		p++;
		VERIFY(*p == 3);
		*p = 6;

		VERIFY(v == Extent3(5, 2, 6));
	}
	{
		Extent3 const v{1, 2, 3};
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

TYPED_TEST(MathExtent3Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Extent3 = bksge::math::Extent3<T>;

	// begin, end (non const)
	{
		Extent3 v{1, 2, 3};
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

		VERIFY(Extent3(5, 2, 6) == v);
	}
	// begin, end (const)
	{
		Extent3 const v{1, 2, 3};
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
		Extent3 v{1, 2, 3};
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

TYPED_TEST(MathExtent3Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Extent3 = bksge::math::Extent3<T>;

	// rbegin, rend (non const)
	{
		Extent3 v{1, 2, 3};
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

		VERIFY(Extent3(6, 2, 5) == v);
	}
	// rbegin, rend (const)
	{
		Extent3 const v{1, 2, 3};
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
		Extent3 v{1, 2, 3};
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

TYPED_TEST(MathExtent3Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	Extent3 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathExtent3Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	Extent3 v1{};
	VERIFY(v1.size() == 3);
	return true;
}

TYPED_TEST(MathExtent3Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	Extent3 v1{};
	VERIFY(v1.max_size() == 3);
	return true;
}

TYPED_TEST(MathExtent3Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	{
		Extent3 v{1, 2, 3};
		VERIFY(v.w() == 1);
		VERIFY(v.h() == 2);
		VERIFY(v.d() == 3);

		v.w() = -3;
		v.h() =  4;
		v.d() = -5;

		VERIFY(v.w() == -3);
		VERIFY(v.h() ==  4);
		VERIFY(v.d() == -5);
	}
	{
		Extent3 v{1, 2, 3};
		VERIFY(v.width()  == 1);
		VERIFY(v.height() == 2);
		VERIFY(v.depth()  == 3);

		v.width()  = -3;
		v.height() =  4;
		v.depth()  = -5;

		VERIFY(v.width()  == -3);
		VERIFY(v.height() ==  4);
		VERIFY(v.depth()  == -5);
	}
	{
		Extent3 const v{5, 6, 7};
		VERIFY(v.w() == 5);
		VERIFY(v.h() == 6);
		VERIFY(v.d() == 7);
	}
	{
		Extent3 const v{5, 6, 7};
		VERIFY(v.width()  == 5);
		VERIFY(v.height() == 6);
		VERIFY(v.depth()  == 7);
	}
	return true;
}

TYPED_TEST(MathExtent3Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Extent2 = bksge::math::Extent2<T>;

	Extent3 v(1, 2, 3);

	VERIFY(Vector4(1, 1, 1, 1) == v.wwww());
	VERIFY(Vector4(1, 1, 1, 2) == v.wwwh());
	VERIFY(Vector4(1, 1, 1, 3) == v.wwwd());
	VERIFY(Vector4(1, 1, 2, 1) == v.wwhw());
	VERIFY(Vector4(1, 1, 2, 2) == v.wwhh());
	VERIFY(Vector4(1, 1, 2, 3) == v.wwhd());
	VERIFY(Vector4(1, 1, 3, 1) == v.wwdw());
	VERIFY(Vector4(1, 1, 3, 2) == v.wwdh());
	VERIFY(Vector4(1, 1, 3, 3) == v.wwdd());
	VERIFY(Vector4(1, 2, 1, 1) == v.whww());
	VERIFY(Vector4(1, 2, 1, 2) == v.whwh());
	VERIFY(Vector4(1, 2, 1, 3) == v.whwd());
	VERIFY(Vector4(1, 2, 2, 1) == v.whhw());
	VERIFY(Vector4(1, 2, 2, 2) == v.whhh());
	VERIFY(Vector4(1, 2, 2, 3) == v.whhd());
	VERIFY(Vector4(1, 2, 3, 1) == v.whdw());
	VERIFY(Vector4(1, 2, 3, 2) == v.whdh());
	VERIFY(Vector4(1, 2, 3, 3) == v.whdd());
	VERIFY(Vector4(1, 3, 1, 1) == v.wdww());
	VERIFY(Vector4(1, 3, 1, 2) == v.wdwh());
	VERIFY(Vector4(1, 3, 1, 3) == v.wdwd());
	VERIFY(Vector4(1, 3, 2, 1) == v.wdhw());
	VERIFY(Vector4(1, 3, 2, 2) == v.wdhh());
	VERIFY(Vector4(1, 3, 2, 3) == v.wdhd());
	VERIFY(Vector4(1, 3, 3, 1) == v.wddw());
	VERIFY(Vector4(1, 3, 3, 2) == v.wddh());
	VERIFY(Vector4(1, 3, 3, 3) == v.wddd());
	VERIFY(Vector4(2, 1, 1, 1) == v.hwww());
	VERIFY(Vector4(2, 1, 1, 2) == v.hwwh());
	VERIFY(Vector4(2, 1, 1, 3) == v.hwwd());
	VERIFY(Vector4(2, 1, 2, 1) == v.hwhw());
	VERIFY(Vector4(2, 1, 2, 2) == v.hwhh());
	VERIFY(Vector4(2, 1, 2, 3) == v.hwhd());
	VERIFY(Vector4(2, 1, 3, 1) == v.hwdw());
	VERIFY(Vector4(2, 1, 3, 2) == v.hwdh());
	VERIFY(Vector4(2, 1, 3, 3) == v.hwdd());
	VERIFY(Vector4(2, 2, 1, 1) == v.hhww());
	VERIFY(Vector4(2, 2, 1, 2) == v.hhwh());
	VERIFY(Vector4(2, 2, 1, 3) == v.hhwd());
	VERIFY(Vector4(2, 2, 2, 1) == v.hhhw());
	VERIFY(Vector4(2, 2, 2, 2) == v.hhhh());
	VERIFY(Vector4(2, 2, 2, 3) == v.hhhd());
	VERIFY(Vector4(2, 2, 3, 1) == v.hhdw());
	VERIFY(Vector4(2, 2, 3, 2) == v.hhdh());
	VERIFY(Vector4(2, 2, 3, 3) == v.hhdd());
	VERIFY(Vector4(2, 3, 1, 1) == v.hdww());
	VERIFY(Vector4(2, 3, 1, 2) == v.hdwh());
	VERIFY(Vector4(2, 3, 1, 3) == v.hdwd());
	VERIFY(Vector4(2, 3, 2, 1) == v.hdhw());
	VERIFY(Vector4(2, 3, 2, 2) == v.hdhh());
	VERIFY(Vector4(2, 3, 2, 3) == v.hdhd());
	VERIFY(Vector4(2, 3, 3, 1) == v.hddw());
	VERIFY(Vector4(2, 3, 3, 2) == v.hddh());
	VERIFY(Vector4(2, 3, 3, 3) == v.hddd());
	VERIFY(Vector4(3, 1, 1, 1) == v.dwww());
	VERIFY(Vector4(3, 1, 1, 2) == v.dwwh());
	VERIFY(Vector4(3, 1, 1, 3) == v.dwwd());
	VERIFY(Vector4(3, 1, 2, 1) == v.dwhw());
	VERIFY(Vector4(3, 1, 2, 2) == v.dwhh());
	VERIFY(Vector4(3, 1, 2, 3) == v.dwhd());
	VERIFY(Vector4(3, 1, 3, 1) == v.dwdw());
	VERIFY(Vector4(3, 1, 3, 2) == v.dwdh());
	VERIFY(Vector4(3, 1, 3, 3) == v.dwdd());
	VERIFY(Vector4(3, 2, 1, 1) == v.dhww());
	VERIFY(Vector4(3, 2, 1, 2) == v.dhwh());
	VERIFY(Vector4(3, 2, 1, 3) == v.dhwd());
	VERIFY(Vector4(3, 2, 2, 1) == v.dhhw());
	VERIFY(Vector4(3, 2, 2, 2) == v.dhhh());
	VERIFY(Vector4(3, 2, 2, 3) == v.dhhd());
	VERIFY(Vector4(3, 2, 3, 1) == v.dhdw());
	VERIFY(Vector4(3, 2, 3, 2) == v.dhdh());
	VERIFY(Vector4(3, 2, 3, 3) == v.dhdd());
	VERIFY(Vector4(3, 3, 1, 1) == v.ddww());
	VERIFY(Vector4(3, 3, 1, 2) == v.ddwh());
	VERIFY(Vector4(3, 3, 1, 3) == v.ddwd());
	VERIFY(Vector4(3, 3, 2, 1) == v.ddhw());
	VERIFY(Vector4(3, 3, 2, 2) == v.ddhh());
	VERIFY(Vector4(3, 3, 2, 3) == v.ddhd());
	VERIFY(Vector4(3, 3, 3, 1) == v.dddw());
	VERIFY(Vector4(3, 3, 3, 2) == v.dddh());
	VERIFY(Vector4(3, 3, 3, 3) == v.dddd());

	VERIFY(Vector3(1, 1, 1) == v.www());
	VERIFY(Vector3(1, 1, 2) == v.wwh());
	VERIFY(Vector3(1, 1, 3) == v.wwd());
	VERIFY(Vector3(1, 2, 1) == v.whw());
	VERIFY(Vector3(1, 2, 2) == v.whh());
	VERIFY(Vector3(1, 2, 3) == v.whd());
	VERIFY(Vector3(1, 3, 1) == v.wdw());
	VERIFY(Vector3(1, 3, 2) == v.wdh());
	VERIFY(Vector3(1, 3, 3) == v.wdd());
	VERIFY(Vector3(2, 1, 1) == v.hww());
	VERIFY(Vector3(2, 1, 2) == v.hwh());
	VERIFY(Vector3(2, 1, 3) == v.hwd());
	VERIFY(Vector3(2, 2, 1) == v.hhw());
	VERIFY(Vector3(2, 2, 2) == v.hhh());
	VERIFY(Vector3(2, 2, 3) == v.hhd());
	VERIFY(Vector3(2, 3, 1) == v.hdw());
	VERIFY(Vector3(2, 3, 2) == v.hdh());
	VERIFY(Vector3(2, 3, 3) == v.hdd());
	VERIFY(Vector3(3, 1, 1) == v.dww());
	VERIFY(Vector3(3, 1, 2) == v.dwh());
	VERIFY(Vector3(3, 1, 3) == v.dwd());
	VERIFY(Vector3(3, 2, 1) == v.dhw());
	VERIFY(Vector3(3, 2, 2) == v.dhh());
	VERIFY(Vector3(3, 2, 3) == v.dhd());
	VERIFY(Vector3(3, 3, 1) == v.ddw());
	VERIFY(Vector3(3, 3, 2) == v.ddh());
	VERIFY(Vector3(3, 3, 3) == v.ddd());

	VERIFY(Extent2(1, 1) == v.ww());
	VERIFY(Extent2(1, 2) == v.wh());
	VERIFY(Extent2(1, 3) == v.wd());
	VERIFY(Extent2(2, 1) == v.hw());
	VERIFY(Extent2(2, 2) == v.hh());
	VERIFY(Extent2(2, 3) == v.hd());
	VERIFY(Extent2(3, 1) == v.dw());
	VERIFY(Extent2(3, 2) == v.dh());
	VERIFY(Extent2(3, 3) == v.dd());

	return true;
}

TYPED_TEST(MathExtent3Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Extent3 = bksge::math::Extent3<T>;

	Extent3 v1{1, 2, 3};
	Extent3 v2{5, 6, 7};

	v1.swap(v2);

	VERIFY(v1 == Extent3(5, 6, 7));
	VERIFY(v2 == Extent3(1, 2, 3));

	bksge::ranges::swap(v1, v2);

	VERIFY(v1 == Extent3(1, 2, 3));
	VERIFY(v2 == Extent3(5, 6, 7));

	return true;
}

TYPED_TEST(MathExtent3Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	{
		Extent3 const v1(-1, 2, -3);
		Extent3 const v2 = +v1;
		Extent3 const v3 = -v1;

		VERIFY(v2[0] == -1);
		VERIFY(v2[1] ==  2);
		VERIFY(v2[2] == -3);
		VERIFY(v3[0] ==  1);
		VERIFY(v3[1] == -2);
		VERIFY(v3[2] ==  3);
	}
	return true;
}

TYPED_TEST(MathExtent3Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	// Extent3 += Extent3
	{
		Extent3 v;
		VERIFY(v == Extent3(0, 0, 0));

		auto t = (v += Extent3(2, 3, -4));
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(v == Extent3(2, 3, -4));
		VERIFY(v == t);
	}
	// Extent3 + Extent3 -> Extent3
	{
		auto t = Extent3(-3, 4, 5) + Extent3(0, 2, -1);
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(t == Extent3(-3, 6, 4));
	}
	return true;
}

TYPED_TEST(MathExtent3Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	// Extent3 -= Extent3
	{
		Extent3 v;
		VERIFY(v == Extent3(0, 0, 0));

		auto t = (v -= Extent3(2, 3, -4));
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(v == Extent3(-2, -3, 4));
		VERIFY(v == t);
	}
	// Extent3 - Extent3 -> Extent3
	{
		auto t = Extent3(-3, 4, 5) - Extent3(0, 2, -1);
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(t == Extent3(-3, 2, 6));
	}
	return true;
}

TYPED_TEST(MathExtent3Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Extent3 = bksge::math::Extent3<T>;

	// Extent3 *= スカラー
	{
		Extent3 v(2, 3, 4);
		{
			auto t = (v *= 4);
			static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
			VERIFY(v == Extent3(8, 12, 16));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
			VERIFY(v == Extent3(4, 6, 8));
			VERIFY(t == v);
		}
	}
	// Extent3 * スカラー -> Extent3
	{
		auto t = Extent3(-3, 42, 5) * -4;
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(t == Extent3(12, -168, -20));
	}
	{
		auto t = Extent3(4, 6, 2) * 2.5;
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(t == Extent3(10, 15, 5));
	}
	// スカラー * Extent3 -> Extent3
	{
		auto t = 5 * Extent3(7, -8, 9);
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(t == Extent3(35, -40, 45));
	}
	{
		auto t = -1.5 * Extent3(4, -6, -2);
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(t == Extent3(-6, 9, 3));
	}

	return true;
}

TYPED_TEST(MathExtent3Test, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScaleTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	using Scale3 = bksge::math::Scale3<T>;

	// Extent3 *= Scale3
	{
		Extent3 v(2, 3, 4);
		{
			auto t = (v *= Scale3(4, 5, 6));
			static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
			VERIFY(Extent3(8, 15, 24) == v);
			VERIFY(t == v);
		}
	}

	// Extent3 * Scale3 -> Extent3
	{
		auto t = Extent3(-3, 2, 5) * Scale3(-4, -5, 8);
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(Extent3(12, -10, 40) == t);
	}

	return true;
}

TYPED_TEST(MathExtent3Test, MulScaleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScaleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Extent3 = bksge::math::Extent3<T>;

	// Extent3 /= スカラー
	{
		Extent3 v(2, 4, 6);
		{
			auto t = (v /= 2);
			static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
			VERIFY(v == Extent3(1, 2, 3));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
			VERIFY(v == Extent3(2, 4, 6));
			VERIFY(t == v);
		}
	}
	// Extent3 / スカラー -> Extent3
	{
		auto t = Extent3(-4, 8, -12) / -4;
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(t == Extent3(1, -2, 3));
	}
	{
		auto t = Extent3(-4, 8, -12) / 0.25;
		static_assert(bksge::is_same<decltype(t), Extent3>::value, "");
		VERIFY(t == Extent3(-16, 32, -48));
	}

	return true;
}

TYPED_TEST(MathExtent3Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Extent3 = bksge::math::Extent3<T>;

	Extent3 const v1(1, 2, 3);
	Extent3 const v2(1, 2, 3);
	Extent3 const v3(2, 2, 3);
	Extent3 const v4(1, 0, 3);
	Extent3 const v5(1, 2, 2);

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

TYPED_TEST(MathExtent3Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathExtent3Test, OutputStreamTest)
{
	using Extent3 = bksge::math::Extent3<TypeParam>;
	{
		Extent3 const v{1, -2, 3};
		bksge::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2, 3 }", ss.str());
	}
	{
		Extent3 const v{-10, 9, 8};
		bksge::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9, 8 }", ss.str());
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Extent3 = bksge::math::Extent3<T>;

	{
		auto v = Extent3::Zero();
		static_assert(bksge::is_same<decltype(v), Extent3>::value, "");
		VERIFY(Extent3(0, 0, 0) == v);
	}
	return true;
}

TYPED_TEST(MathExtent3Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

TYPED_TEST(MathExtent3Test, SerializeTest)
{
	using namespace bksge::serialization;
	using Extent3 = bksge::math::Extent3<TypeParam>;

	Extent3 const v { 1, -2, 3 };

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
	using Extent3 = bksge::math::Extent3<T>;

	Extent3 const v1(1, 2, 3);
	Extent3 const v2(2, 2, 3);
	Extent3 const v3(1, 0, 3);
	Extent3 const v4(1, 2, 2);
	Extent3 const v5(1, 2, 3);

	std::hash<Extent3> h;

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

TYPED_TEST(MathExtent3Test, HashTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

TYPED_TEST(MathExtent3Test, TupleElementTest)
{
	using T = TypeParam;
	using Extent3 = bksge::math::Extent3<T>;

	static_assert(bksge::is_same<typename bksge::tuple_element<0, Extent3>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<1, Extent3>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<2, Extent3>::type, T>::value, "");
}

TYPED_TEST(MathExtent3Test, TupleSizeTest)
{
	using T = TypeParam;
	using Extent3 = bksge::math::Extent3<T>;

	static_assert(bksge::tuple_size<Extent3>::value == 3, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Extent3 = bksge::math::Extent3<T>;
	using std::get;
	{
		Extent3 v{1, 2, 3};

		VERIFY(1 == get<0>(v));
		VERIFY(2 == get<1>(v));
		VERIFY(3 == get<2>(v));

		get<0>(v) = 5;
		get<2>(v) = 6;

		VERIFY(v == Extent3(5, 2, 6));
		VERIFY(5 == get<0>(v));
		VERIFY(2 == get<1>(v));
		VERIFY(6 == get<2>(v));
	}
	{
		Extent3 const v{1, 2, 3};

		VERIFY(1 == get<0>(v));
		VERIFY(2 == get<1>(v));
		VERIFY(3 == get<2>(v));
	}
	return true;
}

TYPED_TEST(MathExtent3Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

#undef VERIFY

}	// namespace extent3_test

}	// namespace bksge_math_test
