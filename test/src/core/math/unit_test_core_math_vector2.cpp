/**
 *	@file	unit_test_core_math_vector2.cpp
 *
 *	@brief	Vector2 のテスト
 *
 *	@author	myoukaku
 */

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
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <functional>
#include <vector>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace vector2_test
{

using Vector2f = bksge::math::Vector2<float>;
using Vector2i = bksge::math::Vector2<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathVector2Test : public ::testing::Test {};
template <typename T>
class MathVector2FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathVector2Test, MathTestTypes);
TYPED_TEST_SUITE(MathVector2FloatTest, MathFloatTestTypes);

TYPED_TEST(MathVector2Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	static_assert(sizeof(Vector2) == sizeof(T) * 2, "");
	static_assert(bksge::is_default_constructible<Vector2>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Vector2>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Vector2>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
}

TYPED_TEST(MathVector2Test, ValueConstructTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	static_assert(!bksge::is_constructible<Vector2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Vector2, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Vector2, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Vector2, T, T>::value, "");
	static_assert(!bksge::is_constructible<Vector2, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector2, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector2, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Vector2, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Vector2, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector2, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector2, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Vector2, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Vector2, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v(1, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v{3, 4};
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v = {5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
	}
}

TYPED_TEST(MathVector2Test, CopyConstructTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	static_assert(bksge::is_constructible<Vector2,  Vector2  const&>::value, "");
	static_assert(bksge::is_constructible<Vector2,  Vector2i const&>::value, "");
	static_assert(bksge::is_constructible<Vector2,  Vector2f const&>::value, "");
	static_assert(bksge::is_constructible<Vector2i, Vector2  const&>::value, "");
	static_assert(bksge::is_constructible<Vector2i, Vector2i const&>::value, "");
	static_assert(bksge::is_constructible<Vector2i, Vector2f const&>::value, "");
	static_assert(bksge::is_constructible<Vector2f, Vector2  const&>::value, "");
	static_assert(bksge::is_constructible<Vector2f, Vector2i const&>::value, "");
	static_assert(bksge::is_constructible<Vector2f, Vector2f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Vector2,  Vector2  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector2,  Vector2i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector2,  Vector2f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector2i, Vector2  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector2i, Vector2i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector2i, Vector2f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector2f, Vector2  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector2f, Vector2i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Vector2f, Vector2f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Vector2,  Vector2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector2,  Vector2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector2,  Vector2f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector2i, Vector2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector2i, Vector2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector2i, Vector2f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector2f, Vector2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector2f, Vector2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Vector2f, Vector2f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Vector2  v1{1, 2};
	BKSGE_CONSTEXPR_OR_CONST Vector2  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Vector2i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Vector2f v4{v2};

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

TYPED_TEST(MathVector2Test, CopyAssignTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	Vector2 v1(0, 1);
	Vector2 v2(3, 4);
	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(3, v2[0]);
	EXPECT_EQ(4, v2[1]);

	v1 = Vector2(6, -7);
	v2 = Vector2i(-9, 10);
	EXPECT_EQ( 6, v1[0]);
	EXPECT_EQ(-7, v1[1]);
	EXPECT_EQ(-9, v2[0]);
	EXPECT_EQ(10, v2[1]);

	// 自己代入
	v1 = v1;
	v2 = v2;
	EXPECT_EQ( 6, v1[0]);
	EXPECT_EQ(-7, v1[1]);
	EXPECT_EQ(-9, v2[0]);
	EXPECT_EQ(10, v2[1]);

	// 多重代入
	v1 = v2 = Vector2f(4, 5);
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(5, v1[1]);
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
}

BKSGE_WARNING_POP()

TYPED_TEST(MathVector2Test, IndexAccessTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	{
		Vector2 v{1, 2};
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);

		v[0] = -3;
		v[1] =  4;

		EXPECT_EQ(-3, v[0]);
		EXPECT_EQ( 4, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
	}
}

TYPED_TEST(MathVector2Test, AtTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	{
		Vector2 v{1, 2};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_THROW((void)v.at(2), bksge::out_of_range);

		v.at(0) = -3;
		v.at(1) =  4;

		EXPECT_EQ(-3, v.at(0));
		EXPECT_EQ( 4, v.at(1));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		EXPECT_THROW((void)v.at(2), bksge::out_of_range);
	}
}

TYPED_TEST(MathVector2Test, DataTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	{
		Vector2 v{1, 2};
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, *p);
		*p = 5;
		++p;
		EXPECT_EQ(2, *p);

		EXPECT_EQ(Vector2(5, 2), v);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Vector2 v{1, 2};
		BKSGE_STATIC_CONSTEXPR auto p = v.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
	}
#endif
}

TYPED_TEST(MathVector2Test, IteratorTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	// begin, end (non const)
	{
		Vector2 v{1, 2};
		auto it = v.begin();
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(1, *it);
		*it++ = 5;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(2, *it);
		++it;
		EXPECT_TRUE(it == v.end());

		EXPECT_EQ(Vector2(5, 2), v);
	}
	// begin, end (const)
	{
		const Vector2 v{1, 2};
		auto it = v.begin();
		EXPECT_TRUE(it != v.end());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);

		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(2, *it);
		EXPECT_EQ(1, *--it);
		EXPECT_TRUE(it != v.end());
		it += 2;
		EXPECT_TRUE(it == v.end());
	}
	// cbegin, cend
	{
		const Vector2 v{1, 2};
		auto it = v.cbegin();
		EXPECT_TRUE(it != v.cend());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);

		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it != v.cend());
		++it;
		EXPECT_TRUE(it == v.cend());
	}
#if !defined(BKSGE_GCC)
	// begin, end (constexpr)
	{
		BKSGE_STATIC_CONSTEXPR Vector2 v{1, 2};
		BKSGE_CONSTEXPR_OR_CONST auto it = v.begin();
		BKSGE_CONSTEXPR_EXPECT_TRUE(it != v.end());

		BKSGE_CONSTEXPR_EXPECT_EQ(1, it[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, it[1]);

		BKSGE_CONSTEXPR_EXPECT_EQ(1, *it);
		BKSGE_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it2 != v.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(2, *it2);
		BKSGE_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it3 == v.end());
	}
#endif
}

TYPED_TEST(MathVector2Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	// rbegin, rend (non const)
	{
		Vector2 v{1, 2};
		auto it = v.rbegin();
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *it);
		*it++ = 5;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(1, *it);
		it++;
		EXPECT_TRUE(it == v.rend());

		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(5, v[1]);
	}
	// rbegin, rend (const)
	{
		const Vector2 v{1, 2};
		auto it = v.rbegin();
		EXPECT_TRUE(it != v.rend());

		EXPECT_EQ(2, it[0]);
		EXPECT_EQ(1, it[1]);

		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *--it);
		EXPECT_TRUE(it != v.rend());
		it += 2;
		EXPECT_TRUE(it == v.rend());
	}
	// crbegin, crend
	{
		const Vector2 v{1, 2};
		auto it = v.crbegin();
		EXPECT_TRUE(it != v.crend());

		EXPECT_EQ(2, it[0]);
		EXPECT_EQ(1, it[1]);

		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != v.crend());
		++it;
		EXPECT_TRUE(it == v.crend());
	}
#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201603) && !defined(BKSGE_GCC)
	// rbegin, rend (constexpr)
	{
		BKSGE_CXX17_STATIC_CONSTEXPR Vector2 v{1, 2};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = v.rbegin();
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it != v.rend());

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, it[0]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, it[1]);

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it2 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, *it2);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it3 == v.rend());
	}
#endif
}

TYPED_TEST(MathVector2Test, EmptyTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	Vector2 v1{};
	const           Vector2 v2{};
	BKSGE_CONSTEXPR Vector2 v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathVector2Test, SizeTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	Vector2 v1{};
	const           Vector2 v2{};
	BKSGE_CONSTEXPR Vector2 v3{};
	EXPECT_EQ(2u, v1.size());
	EXPECT_EQ(2u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(2u, v3.size());
}

TYPED_TEST(MathVector2Test, MaxSizeTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	Vector2 v1{};
	const           Vector2 v2{};
	BKSGE_CONSTEXPR Vector2 v3{};
	EXPECT_EQ(2u, v1.max_size());
	EXPECT_EQ(2u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(2u, v3.max_size());
}

TYPED_TEST(MathVector2Test, NameAccessTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	{
		Vector2 v{1, 2};
		EXPECT_EQ(1, v.x());
		EXPECT_EQ(2, v.y());

		v.x() = -3;
		v.y() =  4;

		EXPECT_EQ(-3, v.x());
		EXPECT_EQ( 4, v.y());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.x());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.y());
	}
}

TYPED_TEST(MathVector2Test, SwizzleTest)
{
	using T = TypeParam;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Vector2 v(1, 2);

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 1), v.xxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 2), v.xxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 1), v.xxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 2), v.xxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 1), v.xyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 2), v.xyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 1), v.xyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 2), v.xyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 1), v.yxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 2), v.yxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 1), v.yxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 2), v.yxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 1), v.yyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 2), v.yyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 1), v.yyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 2), v.yyyy());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 1), v.xxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 2), v.xxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 1), v.xyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 2), v.xyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 1), v.yxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 2), v.yxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 1), v.yyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 2), v.yyy());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 1), v.xx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 2), v.xy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 1), v.yx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 2), v.yy());
}

TYPED_TEST(MathVector2Test, ZeroTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = Vector2::Zero();
		static_assert(bksge::is_same<decltype(v), const Vector2>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(0, 0), v);
	}
	{
		const auto v = Vector2::Zero();
		static_assert(bksge::is_same<decltype(v), const Vector2>::value, "");
		EXPECT_EQ(Vector2(0, 0), v);
	}
}

TYPED_TEST(MathVector2Test, SwapTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	Vector2 v1{11, 12};
	Vector2 v2{21, 22};

	EXPECT_EQ(Vector2(11, 12), v1);
	EXPECT_EQ(Vector2(21, 22), v2);

	v1.swap(v2);

	EXPECT_EQ(Vector2(21, 22), v1);
	EXPECT_EQ(Vector2(11, 12), v2);

	swap(v1, v2);

	EXPECT_EQ(Vector2(11, 12), v1);
	EXPECT_EQ(Vector2(21, 22), v2);
}

TYPED_TEST(MathVector2Test, PlusMinusTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	{
		Vector2 v1(-1, 2);
		Vector2 v3 = +v1;
		Vector2 v4 = -v1;

		EXPECT_EQ(-1, v3[0]);
		EXPECT_EQ( 2, v3[1]);
		EXPECT_EQ( 1, v4[0]);
		EXPECT_EQ(-2, v4[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v2(3, -4);
		BKSGE_CONSTEXPR_OR_CONST Vector2 v5 = +v2;
		BKSGE_CONSTEXPR_OR_CONST Vector2 v6 = -v2;

		BKSGE_CONSTEXPR_EXPECT_EQ( 3, v5[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-4, v5[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-3, v6[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v6[1]);
	}
}

TYPED_TEST(MathVector2Test, AddTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	// Vector2 += Vector2
	{
		Vector2 v;
		Vector2 t = (v += Vector2(2, 3));
		EXPECT_EQ(Vector2(2, 3), v);
		EXPECT_EQ(t, v);
	}

	// Vector2 + Vector2 -> Vector2
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 t =
			Vector2(-3, 4) + Vector2(0, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(-3, 6), t);
	}
}

TYPED_TEST(MathVector2Test, SubTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	// Vector2 -= Vector2
	{
		Vector2 v;
		Vector2 t = (v -= Vector2(2, 3));
		EXPECT_EQ(Vector2(-2, -3), v);
		EXPECT_EQ(t, v);
	}

	// Vector2 - Vector2 -> Vector2
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 t =
			Vector2(-3, 4) - Vector2(0, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(-3, 2), t);
	}
}

TYPED_TEST(MathVector2Test, MulScalarTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	// Vector2 *= スカラー
	{
		Vector2 v(2, 3);
		{
			Vector2 t = (v *= 4);
			EXPECT_EQ(Vector2(8, 12), v);
			EXPECT_EQ(t, v);
		}
		{
			Vector2 t = (v *= 0.5);
			EXPECT_EQ(Vector2(4, 6), v);
			EXPECT_EQ(t, v);
		}
	}

	// Vector2 * スカラー -> Vector2
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 t = Vector2(-3, 42) * -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(12, -168), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 t = Vector2(4, 6) * 2.5;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(10, 15), t);
	}
	// スカラー * Vector2 -> Vector2
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 t = 5 * Vector2(7, -8);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(35, -40), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 t = -1.5 * Vector2(4, -6);
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(-6, 9), t);
	}
}

TYPED_TEST(MathVector2Test, DivScalarTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	// Vector2 /= スカラー
	{
		Vector2 v(2, 4);
		{
			Vector2 t = (v /= 2);
			EXPECT_EQ(Vector2(1, 2), v);
			EXPECT_EQ(t, v);
		}
		{
			Vector2 t = (v /= 0.5);
			EXPECT_EQ(Vector2(2, 4), v);
			EXPECT_EQ(t, v);
		}
	}

	// Vector2 / スカラー -> Vector2
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 t = Vector2(-4, 8) / -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, -2), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 t = Vector2(-4, 8) / 0.25;
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(-16, 32), t);
	}
}

TYPED_TEST(MathVector2Test, CompareTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Vector2 v1(1, 2);
	BKSGE_CONSTEXPR_OR_CONST Vector2 v2(1, 2);
	BKSGE_CONSTEXPR_OR_CONST Vector2 v3(2, 2);
	BKSGE_CONSTEXPR_OR_CONST Vector2 v4(1, 0);

	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v4);

	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v4);
}

TYPED_TEST(MathVector2Test, OutputStreamTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	{
		Vector2 const v{1, -2};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2 }", ss.str());
	}
	{
		Vector2 const v{-10, 9};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9 }", ss.str());
	}
}

TYPED_TEST(MathVector2Test, TupleElementTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	static_assert(bksge::is_same<typename bksge::tuple_element<0, Vector2>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<1, Vector2>::type, T>::value, "");
}

TYPED_TEST(MathVector2Test, TupleGetTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	{
		Vector2 v{1, 2};

		EXPECT_EQ(1, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));

		bksge::get<0>(v) = 5;

		EXPECT_EQ(Vector2(5, 2), v);
		EXPECT_EQ(5, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector2 v{1, 2};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(v));
	}
}

TYPED_TEST(MathVector2Test, TupleSizeTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	static_assert(bksge::tuple_size<Vector2>::value == 2, "");
}

TYPED_TEST(MathVector2Test, DotTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ(0, Dot(Vector2(0, 0), Vector2(0, 0)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector2(1, 0), Vector2( 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector2(1, 0), Vector2(-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector2(1, 0), Vector2( 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector2(1, 0), Vector2( 0,-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector2(1, 0), Vector2( 1, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector2(1, 0), Vector2(-1,-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, Dot(Vector2(1, 0), Vector2( 2, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2, Dot(Vector2(1, 0), Vector2(-2, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector2(1, 0), Vector2( 0, 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector2(1, 0), Vector2( 0,-2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, Dot(Vector2(1, 0), Vector2( 2, 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2, Dot(Vector2(1, 0), Vector2(-2,-2)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector2(0, 1), Vector2( 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector2(0, 1), Vector2(-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector2(0, 1), Vector2( 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector2(0, 1), Vector2( 0,-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector2(0, 1), Vector2( 1, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector2(0, 1), Vector2(-1,-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector2(0, 1), Vector2( 2, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Vector2(0, 1), Vector2(-2, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, Dot(Vector2(0, 1), Vector2( 0, 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2, Dot(Vector2(0, 1), Vector2( 0,-2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, Dot(Vector2(0, 1), Vector2( 2, 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2, Dot(Vector2(0, 1), Vector2(-2,-2)));

	BKSGE_CONSTEXPR_EXPECT_EQ( 2, Dot(Vector2(2,-3), Vector2( 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2, Dot(Vector2(2,-3), Vector2(-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-3, Dot(Vector2(2,-3), Vector2( 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, Dot(Vector2(2,-3), Vector2( 0,-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Vector2(2,-3), Vector2( 1, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Vector2(2,-3), Vector2(-1,-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, Dot(Vector2(2,-3), Vector2( 2, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-4, Dot(Vector2(2,-3), Vector2(-2, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-6, Dot(Vector2(2,-3), Vector2( 0, 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, Dot(Vector2(2,-3), Vector2( 0,-2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2, Dot(Vector2(2,-3), Vector2( 2, 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, Dot(Vector2(2,-3), Vector2(-2,-2)));
}

TYPED_TEST(MathVector2Test, SquaredLengthTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, SquaredLength(Vector2(0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 9, SquaredLength(Vector2(3, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(16, SquaredLength(Vector2(0, 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(61, SquaredLength(Vector2(5, 6)));
	BKSGE_CONSTEXPR_EXPECT_EQ(80, SquaredLength(Vector2(4,-8)));
}

TYPED_TEST(MathVector2Test, LengthTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	const double error = 0.000001;

	EXPECT_EQ(0, Length(Vector2( 0, 0)));
	EXPECT_EQ(3, Length(Vector2( 3, 0)));
	EXPECT_EQ(4, Length(Vector2( 0, 4)));
	EXPECT_EQ(5, Length(Vector2( 3, 4)));
	EXPECT_EQ(5, Length(Vector2(-3, 4)));
	EXPECT_EQ(5, Length(Vector2( 3,-4)));
	EXPECT_EQ(5, Length(Vector2(-3,-4)));
	EXPECT_NEAR(2.2360679774997896964091736687313, (double)Length(Vector2( 1, 2)), error);
	EXPECT_NEAR(2.2360679774997896964091736687313, (double)Length(Vector2(-1, 2)), error);
	EXPECT_NEAR(6.4031242374328486864882176746218, (double)Length(Vector2( 5, 4)), error);
}

TYPED_TEST(MathVector2FloatTest, NormalizedTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	EXPECT_EQ(Vector2( 0, 0), Normalized(Vector2(  0,  0)));
	EXPECT_EQ(Vector2( 1, 0), Normalized(Vector2(  1,  0)));
	EXPECT_EQ(Vector2(-1, 0), Normalized(Vector2( -1,  0)));
	EXPECT_EQ(Vector2( 1, 0), Normalized(Vector2( 10,  0)));
	EXPECT_EQ(Vector2(-1, 0), Normalized(Vector2(-10,  0)));
	EXPECT_EQ(Vector2( 0, 1), Normalized(Vector2(  0,  1)));
	EXPECT_EQ(Vector2( 0,-1), Normalized(Vector2(  0, -1)));
	EXPECT_EQ(Vector2( 0, 1), Normalized(Vector2(  0,  5)));
	EXPECT_EQ(Vector2( 0,-1), Normalized(Vector2(  0, -5)));

	const double error = 0.000001;
	{
		auto const t = Normalized(Vector2(2, 3));
		EXPECT_NEAR( 0.55470019622522915, (double)t.x(), error);
		EXPECT_NEAR( 0.83205029433784372, (double)t.y(), error);
	}
	{
		auto const t = Normalized(Vector2(-4, 5));
		EXPECT_NEAR(-0.62469504755442429, (double)t.x(), error);
		EXPECT_NEAR( 0.78086880944303039, (double)t.y(), error);
	}
}

TYPED_TEST(MathVector2FloatTest, LerpTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2( 0.0,  0.0), Lerp(Vector2(0, 0), Vector2(10, 20), TypeParam(0.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2( 2.5,  5.0), Lerp(Vector2(0, 0), Vector2(10, 20), TypeParam(0.25)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2( 5.0, 10.0), Lerp(Vector2(0, 0), Vector2(10, 20), TypeParam(0.50)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2( 7.5, 15.0), Lerp(Vector2(0, 0), Vector2(10, 20), TypeParam(0.75)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(10.0, 20.0), Lerp(Vector2(0, 0), Vector2(10, 20), TypeParam(1.00)));
}

TYPED_TEST(MathVector2Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::Vector2<T> const v { 4, 5 };

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

TYPED_TEST(MathVector2Test, HashTest)
{
	using T = TypeParam;
	using Vector2 = bksge::math::Vector2<T>;

	std::hash<Vector2> h;

	Vector2 const c1( 1, 2);
	Vector2 const c2(-1, 2);
	Vector2 const c3( 1,-2);
	Vector2 const c4( 2, 1);

	bksge::vector<bksge::size_t> v;
	v.push_back(h(c1));
	v.push_back(h(c2));
	v.push_back(h(c3));
	v.push_back(h(c4));
	bksge::sort(v.begin(), v.end());
	EXPECT_TRUE(bksge::is_unique(v.begin(), v.end()));

	v.push_back(h(c1));
	bksge::sort(v.begin(), v.end());
	EXPECT_FALSE(bksge::is_unique(v.begin(), v.end()));
}

}	// namespace vector2_test

}	// namespace bksge_math_test
