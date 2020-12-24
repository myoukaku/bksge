/**
 *	@file	unit_test_core_math_extent2.cpp
 *
 *	@brief	Extent2 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/extent2.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/scale2.hpp>
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

namespace extent2_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Extent2f = bksge::math::Extent2<float>;
using Extent2i = bksge::math::Extent2<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;

template <typename T>
class MathExtent2Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathExtent2Test, MathTestTypes);

TYPED_TEST(MathExtent2Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	static_assert(sizeof(Extent2) == sizeof(T) * 2, "");
	static_assert(bksge::is_default_constructible<Extent2>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Extent2>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Extent2>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
}

TYPED_TEST(MathExtent2Test, ValueConstructTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	static_assert(!bksge::is_constructible<Extent2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Extent2, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Extent2, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Extent2, T, T>::value, "");
	static_assert( bksge::is_constructible<Extent2, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent2, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent2, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Extent2, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Extent2, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Extent2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Extent2, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Extent2, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Extent2, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Extent2, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v(1, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v{4, 5};
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v = {7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v{42};
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, v[1]);
	}
}

TYPED_TEST(MathExtent2Test, CopyConstructTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	static_assert(bksge::is_constructible<Extent2,  Extent2  const&>::value, "");
	static_assert(bksge::is_constructible<Extent2,  Extent2i const&>::value, "");
	static_assert(bksge::is_constructible<Extent2,  Extent2f const&>::value, "");
	static_assert(bksge::is_constructible<Extent2i, Extent2  const&>::value, "");
	static_assert(bksge::is_constructible<Extent2i, Extent2i const&>::value, "");
	static_assert(bksge::is_constructible<Extent2i, Extent2f const&>::value, "");
	static_assert(bksge::is_constructible<Extent2f, Extent2  const&>::value, "");
	static_assert(bksge::is_constructible<Extent2f, Extent2i const&>::value, "");
	static_assert(bksge::is_constructible<Extent2f, Extent2f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Extent2,  Extent2  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent2,  Extent2i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent2,  Extent2f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent2i, Extent2  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent2i, Extent2i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent2i, Extent2f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent2f, Extent2  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent2f, Extent2i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Extent2f, Extent2f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Extent2,  Extent2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent2,  Extent2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent2,  Extent2f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent2i, Extent2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent2i, Extent2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent2i, Extent2f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent2f, Extent2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent2f, Extent2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Extent2f, Extent2f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Extent2  v1{1, 2};
	BKSGE_CONSTEXPR_OR_CONST Extent2  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Extent2i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Extent2f v4{v2};

	BKSGE_CONSTEXPR_EXPECT_EQ(1, v1[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v1[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v3[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v3[1]);
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v4[0]);
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v4[1]);
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 v1(0, 1);
	Extent2 v2(3, 4);
	VERIFY(0 == v1[0]);
	VERIFY(1 == v1[1]);
	VERIFY(3 == v2[0]);
	VERIFY(4 == v2[1]);

	v1 = Extent2(6, -7);
	v2 = Extent2i(-9, 10);
	VERIFY( 6 == v1[0]);
	VERIFY(-7 == v1[1]);
	VERIFY(-9 == v2[0]);
	VERIFY(10 == v2[1]);

	// 自己代入
	v1 = v1;
	v2 = v2;
	VERIFY( 6 == v1[0]);
	VERIFY(-7 == v1[1]);
	VERIFY(-9 == v2[0]);
	VERIFY(10 == v2[1]);

	// 多重代入
	v1 = v2 = Extent2f(4, 5);
	VERIFY(4 == v1[0]);
	VERIFY(5 == v1[1]);
	VERIFY(4 == v2[0]);
	VERIFY(5 == v2[1]);

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathExtent2Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 v{1, 2};
		VERIFY(1 == v[0]);
		VERIFY(2 == v[1]);

		v[0] = -3;
		v[1] =  4;

		VERIFY(-3 == v[0]);
		VERIFY( 4 == v[1]);
	}
	{
		Extent2 const v{5, 6};
		VERIFY(5 == v[0]);
		VERIFY(6 == v[1]);
	}

	return true;
}

TYPED_TEST(MathExtent2Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 v{1, 2};
		VERIFY(1 == v.at(0));
		VERIFY(2 == v.at(1));

		v.at(0) = -3;
		v.at(1) =  4;

		VERIFY(-3 == v.at(0));
		VERIFY( 4 == v.at(1));
	}
	{
		Extent2 const v{5, 6};
		VERIFY(5 == v.at(0));
		VERIFY(6 == v.at(1));
	}

	return true;
}

TYPED_TEST(MathExtent2Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Extent2 = bksge::math::Extent2<TypeParam>;
	{
		Extent2 v{1, 2};
		EXPECT_THROW((void)v.at(2), bksge::out_of_range);
	}
	{
		Extent2 const v{5, 6};
		EXPECT_THROW((void)v.at(2), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 v{1, 2};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(1 == *p);
		*p = 5;
		++p;
		VERIFY(2 == *p);
		*p = 6;

		VERIFY(Extent2(5, 6) == v);
	}
	{
		Extent2 const v{1, 2};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(1 == p[0]);
		VERIFY(2 == p[1]);
	}

	return true;
}

TYPED_TEST(MathExtent2Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	// begin, end (non const)
	{
		Extent2 v{1, 2};
		auto it = v.begin();
		VERIFY(it != v.end());
		VERIFY(1 == *it);
		*it++ = 5;
		VERIFY(it != v.end());
		VERIFY(2 == *it);
		++it;
		VERIFY(it == v.end());

		VERIFY(Extent2(5, 2) == v);
	}
	// begin, end (const)
	{
		Extent2 const v{1, 2};
		auto it = v.begin();
		VERIFY(it != v.end());

		VERIFY(1 == it[0]);
		VERIFY(2 == it[1]);

		VERIFY(1 == *it++);
		VERIFY(it != v.end());
		VERIFY(2 == *it);
		VERIFY(1 == *--it);
		VERIFY(it != v.end());
		it += 2;
		VERIFY(it == v.end());
	}
	// cbegin, cend
	{
		Extent2 v{1, 2};
		auto it = v.cbegin();
		VERIFY(it != v.cend());

		VERIFY(1 == it[0]);
		VERIFY(2 == it[1]);

		VERIFY(1 == *it++);
		VERIFY(it != v.cend());
		VERIFY(2 == *it);
		VERIFY(it != v.cend());
		++it;
		VERIFY(it == v.cend());
	}

	return true;
}

TYPED_TEST(MathExtent2Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	// rbegin, rend (non const)
	{
		Extent2 v{1, 2};
		auto it = v.rbegin();
		VERIFY(it != v.rend());
		VERIFY(2 == *it);
		*it++ = 5;
		VERIFY(it != v.rend());
		VERIFY(1 == *it);
		it++;
		VERIFY(it == v.rend());

		VERIFY(1 == v[0]);
		VERIFY(5 == v[1]);
	}
	// rbegin, rend (const)
	{
		Extent2 const v{1, 2};
		auto it = v.rbegin();
		VERIFY(it != v.rend());

		VERIFY(2 == it[0]);
		VERIFY(1 == it[1]);

		VERIFY(2 == *it++);
		VERIFY(it != v.rend());
		VERIFY(1 == *it);
		VERIFY(it != v.rend());
		VERIFY(2 == *--it);
		VERIFY(it != v.rend());
		it += 2;
		VERIFY(it == v.rend());
	}
	// crbegin, crend
	{
		Extent2 v{1, 2};
		auto it = v.crbegin();
		VERIFY(it != v.crend());

		VERIFY(2 == it[0]);
		VERIFY(1 == it[1]);

		VERIFY(2 == *it++);
		VERIFY(it != v.crend());
		VERIFY(1 == *it);
		VERIFY(it != v.crend());
		++it;
		VERIFY(it == v.crend());
	}

	return true;
}

TYPED_TEST(MathExtent2Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathExtent2Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 v1{};
	VERIFY(2 == v1.size());
	return true;
}

TYPED_TEST(MathExtent2Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 v1{};
	VERIFY(2 == v1.max_size());
	return true;
}

TYPED_TEST(MathExtent2Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 v{1, 2};
		VERIFY(1 == v.w());
		VERIFY(2 == v.h());

		v.w() = -3;
		v.h() =  4;

		VERIFY(-3 == v.w());
		VERIFY( 4 == v.h());
	}
	{
		Extent2 v{3, 4};
		VERIFY(3 == v.width());
		VERIFY(4 == v.height());

		v.width()  = 1;
		v.height() = 2;

		VERIFY(1 == v.width());
		VERIFY(2 == v.height());
	}
	{
		Extent2 const v{5, 6};
		VERIFY(5 == v.w());
		VERIFY(6 == v.h());
	}
	{
		Extent2 const v{7, 8};
		VERIFY(7 == v.width());
		VERIFY(8 == v.height());
	}

	return true;
}

TYPED_TEST(MathExtent2Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Extent2 = bksge::math::Extent2<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	Extent2 v(1, 2);

	VERIFY(Vector4(1, 1, 1, 1) == v.wwww());
	VERIFY(Vector4(1, 1, 1, 2) == v.wwwh());
	VERIFY(Vector4(1, 1, 2, 1) == v.wwhw());
	VERIFY(Vector4(1, 1, 2, 2) == v.wwhh());
	VERIFY(Vector4(1, 2, 1, 1) == v.whww());
	VERIFY(Vector4(1, 2, 1, 2) == v.whwh());
	VERIFY(Vector4(1, 2, 2, 1) == v.whhw());
	VERIFY(Vector4(1, 2, 2, 2) == v.whhh());
	VERIFY(Vector4(2, 1, 1, 1) == v.hwww());
	VERIFY(Vector4(2, 1, 1, 2) == v.hwwh());
	VERIFY(Vector4(2, 1, 2, 1) == v.hwhw());
	VERIFY(Vector4(2, 1, 2, 2) == v.hwhh());
	VERIFY(Vector4(2, 2, 1, 1) == v.hhww());
	VERIFY(Vector4(2, 2, 1, 2) == v.hhwh());
	VERIFY(Vector4(2, 2, 2, 1) == v.hhhw());
	VERIFY(Vector4(2, 2, 2, 2) == v.hhhh());

	VERIFY(Vector3(1, 1, 1) == v.www());
	VERIFY(Vector3(1, 1, 2) == v.wwh());
	VERIFY(Vector3(1, 2, 1) == v.whw());
	VERIFY(Vector3(1, 2, 2) == v.whh());
	VERIFY(Vector3(2, 1, 1) == v.hww());
	VERIFY(Vector3(2, 1, 2) == v.hwh());
	VERIFY(Vector3(2, 2, 1) == v.hhw());
	VERIFY(Vector3(2, 2, 2) == v.hhh());

	VERIFY(Vector2(1, 1) == v.ww());
	VERIFY(Vector2(1, 2) == v.wh());
	VERIFY(Vector2(2, 1) == v.hw());
	VERIFY(Vector2(2, 2) == v.hh());

	return true;
}

TYPED_TEST(MathExtent2Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 v1{11, 12};
	Extent2 v2{21, 22};

	v1.swap(v2);

	VERIFY(Extent2(21, 22) == v1);
	VERIFY(Extent2(11, 12) == v2);

	bksge::ranges::swap(v1, v2);

	VERIFY(Extent2(11, 12) == v1);
	VERIFY(Extent2(21, 22) == v2);

	return true;
}

TYPED_TEST(MathExtent2Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 const v1(-1, 2);
		auto v2 = +v1;
		auto v3 = -v1;
		static_assert(bksge::is_same<decltype(v2), Extent2>::value, "");
		static_assert(bksge::is_same<decltype(v3), Extent2>::value, "");

		VERIFY(-1 == v2[0]);
		VERIFY( 2 == v2[1]);
		VERIFY( 1 == v3[0]);
		VERIFY(-2 == v3[1]);
	}

	return true;
}

TYPED_TEST(MathExtent2Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	// Extent2 += Extent2
	{
		Extent2 v;
		auto t = (v += Extent2(2, 3));
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(2, 3) == v);
		VERIFY(t == v);
	}

	// Extent2 + Extent2 -> Extent2
	{
		auto t = Extent2(-3, 4) + Extent2(0, 2);
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(-3, 6) == t);
	}

	return true;
}

TYPED_TEST(MathExtent2Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	// Extent2 -= Extent2
	{
		Extent2 v;
		auto t = (v -= Extent2(2, 3));
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(-2, -3) == v);
		VERIFY(t == v);
	}

	// Extent2 - Extent2 -> Extent2
	{
		auto t = Extent2(-3, 4) - Extent2(0, 2);
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(-3, 2) == t);
	}

	return true;
}

TYPED_TEST(MathExtent2Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	// Extent2 *= スカラー
	{
		Extent2 v(2, 3);
		{
			auto t = (v *= 4);
			static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
			VERIFY(Extent2(8, 12) == v);
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
			VERIFY(Extent2(4, 6) == v);
			VERIFY(t == v);
		}
	}

	// Extent2 * スカラー -> Extent2
	{
		auto t = Extent2(-3, 42) * -4;
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(12, -168) == t);
	}
	{
		auto t = Extent2(4, 6) * 2.5;
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(10, 15) == t);
	}
	// スカラー * Extent2 -> Extent2
	{
		auto t = 5 * Extent2(7, -8);
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(35, -40) == t);
	}
	{
		auto t = -1.5 * Extent2(4, -6);
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(-6, 9) == t);
	}

	return true;
}

TYPED_TEST(MathExtent2Test, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScale2Test()
{
	using Extent2 = bksge::math::Extent2<T>;
	using Scale2 = bksge::math::Scale2<T>;

	// Extent2 *= Scale2
	{
		Extent2 v(2, 3);
		auto t = (v *= Scale2(4, 5));
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(8, 15) == v);
		VERIFY(t == v);
	}

	// Extent2 * Scale2 -> Extent2
	{
		auto t = Extent2(-3, 2) * Scale2(-4, -5);
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(12, -10) == t);
	}

	return true;
}

TYPED_TEST(MathExtent2Test, MulScale2Test)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScale2Test<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	// Extent2 /= スカラー
	{
		Extent2 v(2, 4);
		{
			auto t = (v /= 2);
			static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
			VERIFY(Extent2(1, 2) == v);
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
			VERIFY(Extent2(2, 4) == v);
			VERIFY(t == v);
		}
	}

	// Extent2 / スカラー -> Extent2
	{
		auto t = Extent2(-4, 8) / -4;
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(1, -2) == t);
	}
	{
		auto t = Extent2(-4, 8) / 0.25;
		static_assert(bksge::is_same<decltype(t), Extent2>::value, "");
		VERIFY(Extent2(-16, 32) == t);
	}

	return true;
}

TYPED_TEST(MathExtent2Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 const v1(1, 2);
	Extent2 const v2(1, 2);
	Extent2 const v3(2, 2);
	Extent2 const v4(1, 0);

	VERIFY( (v1 == v1));
	VERIFY( (v1 == v2));
	VERIFY(!(v1 == v3));
	VERIFY(!(v1 == v4));

	VERIFY(!(v1 != v1));
	VERIFY(!(v1 != v2));
	VERIFY( (v1 != v3));
	VERIFY( (v1 != v4));

	return true;
}

TYPED_TEST(MathExtent2Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathExtent2Test, OutputStreamTest)
{
	using Extent2 = bksge::math::Extent2<TypeParam>;

	{
		Extent2 const v{1, -2};
		bksge::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2 }", ss.str());
	}
	{
		Extent2 const v{-10, 9};
		bksge::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9 }", ss.str());
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Extent2 = bksge::math::Extent2<T>;

	{
		auto v = Extent2::Zero();
		static_assert(bksge::is_same<decltype(v), Extent2>::value, "");
		VERIFY(Extent2(0, 0) == v);
	}
	return true;
}

TYPED_TEST(MathExtent2Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

TYPED_TEST(MathExtent2Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::Extent2<T> const v { 7, 8 };

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
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 const v1( 1, 2);
	Extent2 const v2(-1, 2);
	Extent2 const v3( 1,-2);
	Extent2 const v4(-1,-2);
	Extent2 const v5( 2, 1);

	std::hash<Extent2> h;

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

TYPED_TEST(MathExtent2Test, HashTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

TYPED_TEST(MathExtent2Test, TupleElementTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	static_assert(bksge::is_same<typename bksge::tuple_element<0, Extent2>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<1, Extent2>::type, T>::value, "");
}

TYPED_TEST(MathExtent2Test, TupleSizeTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	static_assert(bksge::tuple_size<Extent2>::value == 2, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Extent2 = bksge::math::Extent2<T>;
	using std::get;

	{
		Extent2 v{1, 2};

		VERIFY(1 == get<0>(v));
		VERIFY(2 == get<1>(v));

		get<0>(v) = 5;

		VERIFY(Extent2(5, 2) == v);
		VERIFY(5 == get<0>(v));
		VERIFY(2 == get<1>(v));
	}
	{
		Extent2 const v{1, 2};

		VERIFY(1 == get<0>(v));
		VERIFY(2 == get<1>(v));
	}

	return true;
}

TYPED_TEST(MathExtent2Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

#undef VERIFY

}	// namespace extent2_test

}	// namespace bksge_math_test
