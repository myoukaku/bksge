/**
 *	@file	unit_test_core_math_scale2.cpp
 *
 *	@brief	Scale2 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/scale2.hpp>
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
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <functional>
#include <vector>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace scale2_test
{

using Scale2f = bksge::math::Scale2<float>;
using Scale2i = bksge::math::Scale2<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathScale2Test : public ::testing::Test {};
template <typename T>
class MathScale2FloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathScale2Test, MathTestTypes);
TYPED_TEST_SUITE(MathScale2FloatTest, MathFloatTestTypes);

TYPED_TEST(MathScale2Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	static_assert(sizeof(Scale2) == sizeof(T) * 2, "");
	static_assert(bksge::is_default_constructible<Scale2>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Scale2>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Scale2>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 s;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, s[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, s[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 s{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, s[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, s[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 s = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, s[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, s[1]);
	}
}

TYPED_TEST(MathScale2Test, ValueConstructTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	static_assert(!bksge::is_constructible<Scale2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Scale2, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Scale2, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Scale2, T, T>::value, "");
	static_assert(!bksge::is_constructible<Scale2, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Scale2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Scale2, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Scale2, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Scale2, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Scale2, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Scale2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Scale2, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Scale2, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Scale2, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Scale2, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 s(1, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, s[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, s[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 s{3, 4};
		BKSGE_CONSTEXPR_EXPECT_EQ(3, s[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, s[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 s = {5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, s[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, s[1]);
	}
}

TYPED_TEST(MathScale2Test, CopyConstructTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	static_assert(bksge::is_constructible<Scale2,  Scale2  const&>::value, "");
	static_assert(bksge::is_constructible<Scale2,  Scale2i const&>::value, "");
	static_assert(bksge::is_constructible<Scale2,  Scale2f const&>::value, "");
	static_assert(bksge::is_constructible<Scale2i, Scale2  const&>::value, "");
	static_assert(bksge::is_constructible<Scale2i, Scale2i const&>::value, "");
	static_assert(bksge::is_constructible<Scale2i, Scale2f const&>::value, "");
	static_assert(bksge::is_constructible<Scale2f, Scale2  const&>::value, "");
	static_assert(bksge::is_constructible<Scale2f, Scale2i const&>::value, "");
	static_assert(bksge::is_constructible<Scale2f, Scale2f const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Scale2,  Scale2  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Scale2,  Scale2i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Scale2,  Scale2f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Scale2i, Scale2  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Scale2i, Scale2i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Scale2i, Scale2f const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Scale2f, Scale2  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Scale2f, Scale2i const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Scale2f, Scale2f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Scale2,  Scale2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Scale2,  Scale2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Scale2,  Scale2f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Scale2i, Scale2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Scale2i, Scale2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Scale2i, Scale2f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Scale2f, Scale2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Scale2f, Scale2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Scale2f, Scale2f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Scale2  v1{1, 2};
	BKSGE_CONSTEXPR_OR_CONST Scale2  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Scale2i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Scale2f v4{v2};

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

TYPED_TEST(MathScale2Test, CopyAssignTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	Scale2 v1(0, 1);
	Scale2 v2(3, 4);
	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(3, v2[0]);
	EXPECT_EQ(4, v2[1]);

	v1 = Scale2(6, -7);
	v2 = Scale2i(-9, 10);
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
	v1 = v2 = Scale2f(4, 5);
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(5, v1[1]);
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
}

BKSGE_WARNING_POP()

TYPED_TEST(MathScale2Test, IndexAccessTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	{
		Scale2 s{1, 2};
		EXPECT_EQ(1, s[0]);
		EXPECT_EQ(2, s[1]);

		s[0] = -3;
		s[1] =  4;

		EXPECT_EQ(-3, s[0]);
		EXPECT_EQ( 4, s[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 s{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, s[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, s[1]);
	}
}

TYPED_TEST(MathScale2Test, AtTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	{
		Scale2 s{1, 2};
		EXPECT_EQ(1, s.at(0));
		EXPECT_EQ(2, s.at(1));
		EXPECT_THROW((void)s.at(2), std::out_of_range);

		s.at(0) = -3;
		s.at(1) =  4;

		EXPECT_EQ(-3, s.at(0));
		EXPECT_EQ( 4, s.at(1));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 s{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, s.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, s.at(1));
		EXPECT_THROW((void)s.at(2), std::out_of_range);
	}
}

TYPED_TEST(MathScale2Test, DataTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	{
		Scale2 s{1, 2};
		auto p = s.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, *p);
		*p = 5;
		++p;
		EXPECT_EQ(2, *p);

		EXPECT_EQ(Scale2(5, 2), s);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Scale2 s{1, 2};
		BKSGE_STATIC_CONSTEXPR auto p = s.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
	}
#endif
}

TYPED_TEST(MathScale2Test, IteratorTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	// begin, end (non const)
	{
		Scale2 s{1, 2};
		auto it = s.begin();
		EXPECT_TRUE(it != s.end());
		EXPECT_EQ(1, *it);
		*it++ = 5;
		EXPECT_TRUE(it != s.end());
		EXPECT_EQ(2, *it);
		++it;
		EXPECT_TRUE(it == s.end());

		EXPECT_EQ(Scale2(5, 2), s);
	}
	// begin, end (const)
	{
		const Scale2 s{1, 2};
		auto it = s.begin();
		EXPECT_TRUE(it != s.end());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);

		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != s.end());
		EXPECT_EQ(2, *it);
		EXPECT_EQ(1, *--it);
		EXPECT_TRUE(it != s.end());
		it += 2;
		EXPECT_TRUE(it == s.end());
	}
	// cbegin, cend
	{
		const Scale2 s{1, 2};
		auto it = s.cbegin();
		EXPECT_TRUE(it != s.cend());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);

		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != s.cend());
		EXPECT_EQ(2, *it);
		EXPECT_TRUE(it != s.cend());
		++it;
		EXPECT_TRUE(it == s.cend());
	}
#if !defined(BKSGE_GCC)
	// begin, end (constexpr)
	{
		BKSGE_STATIC_CONSTEXPR Scale2 s{1, 2};
		BKSGE_CONSTEXPR_OR_CONST auto it = s.begin();
		BKSGE_CONSTEXPR_EXPECT_TRUE(it != s.end());

		BKSGE_CONSTEXPR_EXPECT_EQ(1, it[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, it[1]);

		BKSGE_CONSTEXPR_EXPECT_EQ(1, *it);
		BKSGE_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it2 != s.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(2, *it2);
		BKSGE_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it3 == s.end());
	}
#endif
}

TYPED_TEST(MathScale2Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	// rbegin, rend (non const)
	{
		Scale2 s{1, 2};
		auto it = s.rbegin();
		EXPECT_TRUE(it != s.rend());
		EXPECT_EQ(2, *it);
		*it++ = 5;
		EXPECT_TRUE(it != s.rend());
		EXPECT_EQ(1, *it);
		it++;
		EXPECT_TRUE(it == s.rend());

		EXPECT_EQ(1, s[0]);
		EXPECT_EQ(5, s[1]);
	}
	// rbegin, rend (const)
	{
		const Scale2 s{1, 2};
		auto it = s.rbegin();
		EXPECT_TRUE(it != s.rend());

		EXPECT_EQ(2, it[0]);
		EXPECT_EQ(1, it[1]);

		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it != s.rend());
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != s.rend());
		EXPECT_EQ(2, *--it);
		EXPECT_TRUE(it != s.rend());
		it += 2;
		EXPECT_TRUE(it == s.rend());
	}
	// crbegin, crend
	{
		const Scale2 s{1, 2};
		auto it = s.crbegin();
		EXPECT_TRUE(it != s.crend());

		EXPECT_EQ(2, it[0]);
		EXPECT_EQ(1, it[1]);

		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it != s.crend());
		EXPECT_EQ(1, *it);
		EXPECT_TRUE(it != s.crend());
		++it;
		EXPECT_TRUE(it == s.crend());
	}
#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201603) && !defined(BKSGE_GCC)
	// rbegin, rend (constexpr)
	{
		BKSGE_CXX17_STATIC_CONSTEXPR Scale2 s{1, 2};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = s.rbegin();
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it != s.rend());

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, it[0]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, it[1]);

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it2 != s.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, *it2);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it3 == s.rend());
	}
#endif
}

TYPED_TEST(MathScale2Test, EmptyTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	Scale2 v1{};
	const           Scale2 v2{};
	BKSGE_CONSTEXPR Scale2 v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathScale2Test, SizeTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	Scale2 v1{};
	const           Scale2 v2{};
	BKSGE_CONSTEXPR Scale2 v3{};
	EXPECT_EQ(2u, v1.size());
	EXPECT_EQ(2u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(2u, v3.size());
}

TYPED_TEST(MathScale2Test, MaxSizeTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	Scale2 v1{};
	const           Scale2 v2{};
	BKSGE_CONSTEXPR Scale2 v3{};
	EXPECT_EQ(2u, v1.max_size());
	EXPECT_EQ(2u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(2u, v3.max_size());
}

TYPED_TEST(MathScale2Test, NameAccessTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	{
		Scale2 s{1, 2};
		EXPECT_EQ(1, s.x());
		EXPECT_EQ(2, s.y());

		s.x() = -3;
		s.y() =  4;

		EXPECT_EQ(-3, s.x());
		EXPECT_EQ( 4, s.y());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 s{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, s.x());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, s.y());
	}
}

TYPED_TEST(MathScale2Test, SwizzleTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Scale2 s(1, 2);

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 1), s.xxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 2), s.xxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 1), s.xxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 2), s.xxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 1), s.xyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 2), s.xyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 1), s.xyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 2), s.xyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 1), s.yxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 2), s.yxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 1), s.yxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 2), s.yxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 1), s.yyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 2), s.yyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 1), s.yyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 2), s.yyyy());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 1), s.xxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 2), s.xxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 1), s.xyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 2), s.xyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 1), s.yxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 2), s.yxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 1), s.yyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 2), s.yyy());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 1), s.xx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 2), s.xy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 1), s.yx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 2), s.yy());
}

TYPED_TEST(MathScale2Test, SwapTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	Scale2 v1{11, 12};
	Scale2 v2{21, 22};

	EXPECT_EQ(Scale2(11, 12), v1);
	EXPECT_EQ(Scale2(21, 22), v2);

	v1.swap(v2);

	EXPECT_EQ(Scale2(21, 22), v1);
	EXPECT_EQ(Scale2(11, 12), v2);

	swap(v1, v2);

	EXPECT_EQ(Scale2(11, 12), v1);
	EXPECT_EQ(Scale2(21, 22), v2);
}

TYPED_TEST(MathScale2Test, PlusMinusTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	{
		Scale2 v1(-1, 2);
		Scale2 v3 = +v1;
		Scale2 v4 = -v1;

		EXPECT_EQ(-1, v3[0]);
		EXPECT_EQ( 2, v3[1]);
		EXPECT_EQ( 1, v4[0]);
		EXPECT_EQ(-2, v4[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 v2(3, -4);
		BKSGE_CONSTEXPR_OR_CONST Scale2 v5 = +v2;
		BKSGE_CONSTEXPR_OR_CONST Scale2 v6 = -v2;

		BKSGE_CONSTEXPR_EXPECT_EQ( 3, v5[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-4, v5[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-3, v6[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v6[1]);
	}
}

TYPED_TEST(MathScale2Test, AddTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	// Scale2 += Scale2
	{
		Scale2 s;
		Scale2 t = (s += Scale2(2, 3));
		EXPECT_EQ(Scale2(2, 3), s);
		EXPECT_EQ(t, s);
	}

	// Scale2 + Scale2 -> Scale2
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 t =
			Scale2(-3, 4) + Scale2(0, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(-3, 6), t);
	}
}

TYPED_TEST(MathScale2Test, SubTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	// Scale2 -= Scale2
	{
		Scale2 s;
		Scale2 t = (s -= Scale2(2, 3));
		EXPECT_EQ(Scale2(-2, -3), s);
		EXPECT_EQ(t, s);
	}

	// Scale2 - Scale2 -> Scale2
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 t =
			Scale2(-3, 4) - Scale2(0, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(-3, 2), t);
	}
}

TYPED_TEST(MathScale2Test, MulScalarTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	// Scale2 *= スカラー
	{
		Scale2 s(2, 3);
		{
			Scale2 t = (s *= 4);
			EXPECT_EQ(Scale2(8, 12), s);
			EXPECT_EQ(t, s);
		}
		{
			Scale2 t = (s *= 0.5);
			EXPECT_EQ(Scale2(4, 6), s);
			EXPECT_EQ(t, s);
		}
	}

	// Scale2 * スカラー -> Scale2
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 t = Scale2(-3, 42) * -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(12, -168), t);
	}
	{
		const Scale2 t = Scale2(4, 6) * 2.5;
		EXPECT_EQ(Scale2(10, 15), t);
	}
	// スカラー * Scale2 -> Scale2
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 t = 5 * Scale2(7, -8);
		BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(35, -40), t);
	}
	{
		const Scale2 t = -1.5 * Scale2(4, -6);
		EXPECT_EQ(Scale2(-6, 9), t);
	}
}

TYPED_TEST(MathScale2Test, MulScale2Test)
{
	using Scale2 = bksge::math::Scale2<TypeParam>;

	// Scale2 *= Scale2
	{
		Scale2 s(2, 3);

		auto t = (s *= Scale2(-1, 2));
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		EXPECT_EQ(Scale2(-2, 6), s);
		EXPECT_EQ(t, s);
	}

	// Scale2 * Scale2 -> Scale2
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Scale2(-3, 4) * Scale2(0, 2);
		static_assert(bksge::is_same<decltype(t), const Scale2>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(0, 8), t);
	}
}

TYPED_TEST(MathScale2Test, MulVector2Test)
{
	using Vector2 = bksge::math::Vector2<TypeParam>;
	using Scale2 = bksge::math::Scale2<TypeParam>;

	// Vector2 *= Scale2
	{
		Vector2 v {1, 2};

		auto t = (v *= Scale2{2, -3});
		static_assert(bksge::is_same<decltype(t), Vector2>::value, "");
		EXPECT_EQ(Vector2(2, -6), v);
		EXPECT_EQ(t, v);
	}

	// Vector2 * Scale2 -> Vector2
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Vector2{-5, 6} * Scale2{2, -2};
		static_assert(bksge::is_same<decltype(t), const Vector2>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(-10, -12), t);
	}
}

TYPED_TEST(MathScale2Test, DivScalarTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	// Scale2 /= スカラー
	{
		Scale2 s(2, 4);
		{
			Scale2 t = (s /= 2);
			EXPECT_EQ(Scale2(1, 2), s);
			EXPECT_EQ(t, s);
		}
		{
			Scale2 t = (s /= 0.5);
			EXPECT_EQ(Scale2(2, 4), s);
			EXPECT_EQ(t, s);
		}
	}

	// Scale2 / スカラー -> Scale2
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 t = Scale2(-4, 8) / -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(1, -2), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 t = Scale2(-4, 8) / 0.25;
		BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(-16, 32), t);
	}
}

TYPED_TEST(MathScale2Test, DivScale2Test)
{
	using Scale2 = bksge::math::Scale2<TypeParam>;

	// Scale2 /= Scale2
	{
		Scale2 s(8, 12);

		auto t = (s /= Scale2(-1, 2));
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		EXPECT_EQ(Scale2(-8, 6), s);
		EXPECT_EQ(t, s);
	}

	// Scale2 / Scale2 -> Scale2
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Scale2(-3, 4) / Scale2(1, 2);
		static_assert(bksge::is_same<decltype(t), const Scale2>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(-3, 2), t);
	}
}

TYPED_TEST(MathScale2Test, CompareTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	BKSGE_CONSTEXPR_OR_CONST Scale2 v1(1, 2);
	BKSGE_CONSTEXPR_OR_CONST Scale2 v2(1, 2);
	BKSGE_CONSTEXPR_OR_CONST Scale2 v3(2, 2);
	BKSGE_CONSTEXPR_OR_CONST Scale2 v4(1, 0);

	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v4);

	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v4);
}

TYPED_TEST(MathScale2Test, OutputStreamTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	{
		Scale2 const s{1, -2};
		std::stringstream ss;
		ss << s;
		EXPECT_EQ("{ 1, -2 }", ss.str());
	}
	{
		Scale2 const s{-10, 9};
		std::wstringstream ss;
		ss << s;
		EXPECT_EQ(L"{ -10, 9 }", ss.str());
	}
}

TYPED_TEST(MathScale2Test, TupleElementTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	static_assert(bksge::is_same<typename std::tuple_element<0, Scale2>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<1, Scale2>::type, T>::value, "");
}

TYPED_TEST(MathScale2Test, TupleGetTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	{
		Scale2 s{1, 2};

		EXPECT_EQ(1, bksge::get<0>(s));
		EXPECT_EQ(2, bksge::get<1>(s));

		bksge::get<0>(s) = 5;

		EXPECT_EQ(Scale2(5, 2), s);
		EXPECT_EQ(5, bksge::get<0>(s));
		EXPECT_EQ(2, bksge::get<1>(s));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 s{1, 2};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(s));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(s));
	}
}

TYPED_TEST(MathScale2Test, TupleSizeTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	static_assert(std::tuple_size<Scale2>::value == 2, "");
}

TYPED_TEST(MathScale2Test, ZeroTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto s = Scale2::Zero();
		static_assert(bksge::is_same<decltype(s), const Scale2>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(0, 0), s);
	}
	{
		const auto s = Scale2::Zero();
		static_assert(bksge::is_same<decltype(s), const Scale2>::value, "");
		EXPECT_EQ(Scale2(0, 0), s);
	}
}

TYPED_TEST(MathScale2Test, IdentityTest)
{
	using Scale2 = bksge::math::Scale2<TypeParam>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto s = Scale2::Identity();
		static_assert(bksge::is_same<decltype(s), const Scale2>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(1, 1), s);
	}
	{
		const auto s = Scale2::Identity();
		static_assert(bksge::is_same<decltype(s), const Scale2>::value, "");
		EXPECT_EQ(Scale2(1, 1), s);
	}
}

TYPED_TEST(MathScale2FloatTest, LerpTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ(Scale2( 0.0,  0.0), Lerp(Scale2(0, 0), Scale2(10, 20), TypeParam(0.00)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Scale2( 2.5,  5.0), Lerp(Scale2(0, 0), Scale2(10, 20), TypeParam(0.25)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Scale2( 5.0, 10.0), Lerp(Scale2(0, 0), Scale2(10, 20), TypeParam(0.50)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Scale2( 7.5, 15.0), Lerp(Scale2(0, 0), Scale2(10, 20), TypeParam(0.75)));
	BKSGE_CONSTEXPR_EXPECT_EQ(Scale2(10.0, 20.0), Lerp(Scale2(0, 0), Scale2(10, 20), TypeParam(1.00)));
}

TYPED_TEST(MathScale2Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::Scale2<T> const v { -6, 7 };

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

TYPED_TEST(MathScale2Test, HashTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	std::hash<Scale2> h;

	Scale2 const c1( 1, 2);
	Scale2 const c2(-1, 2);
	Scale2 const c3( 1,-2);
	Scale2 const c4( 2, 1);

	std::vector<bksge::size_t> v;
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

}	// namespace scale2_test

}	// namespace bksge_math_test
