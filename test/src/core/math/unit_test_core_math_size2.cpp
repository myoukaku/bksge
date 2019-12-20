/**
 *	@file	unit_test_core_math_size2.cpp
 *
 *	@brief	Size2 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/size2.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/scale2.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace size2_test
{

using Size2f = bksge::math::Size2<float>;
using Size2i = bksge::math::Size2<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;

template <typename T>
class MathSize2Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathSize2Test, MathTestTypes);

TYPED_TEST(MathSize2Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	static_assert(sizeof(Size2) == sizeof(T) * 2, "");
	static_assert(std::is_default_constructible<Size2>::value, "");
	static_assert(std::is_nothrow_default_constructible<Size2>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Size2>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
}

TYPED_TEST(MathSize2Test, ValueConstructTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	static_assert(!std::is_constructible<Size2, T, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<Size2, T, T, T, T>::value, "");
	static_assert(!std::is_constructible<Size2, T, T, T>::value, "");
	static_assert( std::is_constructible<Size2, T, T>::value, "");
	static_assert(!std::is_constructible<Size2, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Size2, T, T, T, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Size2, T, T, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Size2, T, T, T>::value, "");
	static_assert( std::is_nothrow_constructible<Size2, T, T>::value, "");
	static_assert(!std::is_nothrow_constructible<Size2, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Size2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Size2, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Size2, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Size2, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Size2, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v(1, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v{4, 5};
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v = {7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[1]);
	}
}

TYPED_TEST(MathSize2Test, CopyConstructTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	static_assert(std::is_constructible<Size2,  Size2  const&>::value, "");
	static_assert(std::is_constructible<Size2,  Size2i const&>::value, "");
	static_assert(std::is_constructible<Size2,  Size2f const&>::value, "");
	static_assert(std::is_constructible<Size2i, Size2  const&>::value, "");
	static_assert(std::is_constructible<Size2i, Size2i const&>::value, "");
	static_assert(std::is_constructible<Size2i, Size2f const&>::value, "");
	static_assert(std::is_constructible<Size2f, Size2  const&>::value, "");
	static_assert(std::is_constructible<Size2f, Size2i const&>::value, "");
	static_assert(std::is_constructible<Size2f, Size2f const&>::value, "");

	static_assert(std::is_nothrow_constructible<Size2,  Size2  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size2,  Size2i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size2,  Size2f const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size2i, Size2  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size2i, Size2i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size2i, Size2f const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size2f, Size2  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size2f, Size2i const&>::value, "");
	static_assert(std::is_nothrow_constructible<Size2f, Size2f const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Size2,  Size2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size2,  Size2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size2,  Size2f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size2i, Size2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size2i, Size2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size2i, Size2f const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size2f, Size2  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size2f, Size2i const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Size2f, Size2f const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Size2  v1{1, 2};
	BKSGE_CONSTEXPR_OR_CONST Size2  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Size2i v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Size2f v4{v2};

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

TYPED_TEST(MathSize2Test, CopyAssignTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	Size2 v1(0, 1);
	Size2 v2(3, 4);
	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(3, v2[0]);
	EXPECT_EQ(4, v2[1]);

	v1 = Size2(6, -7);
	v2 = Size2i(-9, 10);
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
	v1 = v2 = Size2f(4, 5);
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(5, v1[1]);
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
}

BKSGE_WARNING_POP()

TYPED_TEST(MathSize2Test, IndexAccessTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	{
		Size2 v{1, 2};
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);

		v[0] = -3;
		v[1] =  4;

		EXPECT_EQ(-3, v[0]);
		EXPECT_EQ( 4, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
	}
}

TYPED_TEST(MathSize2Test, AtTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	{
		Size2 v{1, 2};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_THROW((void)v.at(2), std::out_of_range);

		v.at(0) = -3;
		v.at(1) =  4;

		EXPECT_EQ(-3, v.at(0));
		EXPECT_EQ( 4, v.at(1));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		EXPECT_THROW((void)v.at(2), std::out_of_range);
	}
}

TYPED_TEST(MathSize2Test, DataTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	{
		Size2 v{1, 2};
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, *p);
		*p = 5;
		++p;
		EXPECT_EQ(2, *p);
		*p = 6;

		EXPECT_EQ(Size2(5, 6), v);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Size2 v{1, 2};
		BKSGE_STATIC_CONSTEXPR auto p = v.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
	}
#endif
}

TYPED_TEST(MathSize2Test, IteratorTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	// begin, end (non const)
	{
		Size2 v{1, 2};
		auto it = v.begin();
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(1, *it);
		*it++ = 5;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(2, *it);
		++it;
		EXPECT_TRUE(it == v.end());

		EXPECT_EQ(Size2(5, 2), v);
	}
	// begin, end (const)
	{
		const Size2 v{1, 2};
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
		const Size2 v{1, 2};
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
		BKSGE_STATIC_CONSTEXPR Size2 v{1, 2};
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

TYPED_TEST(MathSize2Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	// rbegin, rend (non const)
	{
		Size2 v{1, 2};
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
		const Size2 v{1, 2};
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
		const Size2 v{1, 2};
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
		BKSGE_CXX17_STATIC_CONSTEXPR Size2 v{1, 2};
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

TYPED_TEST(MathSize2Test, EmptyTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	Size2 v1{};
	const Size2 v2{};
	BKSGE_CONSTEXPR Size2 v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathSize2Test, SizeTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	Size2 v1{};
	const Size2 v2{};
	BKSGE_CONSTEXPR Size2 v3{};
	EXPECT_EQ(2u, v1.size());
	EXPECT_EQ(2u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(2u, v3.size());
}

TYPED_TEST(MathSize2Test, MaxSizeTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	Size2 v1{};
	const Size2 v2{};
	BKSGE_CONSTEXPR Size2 v3{};
	EXPECT_EQ(2u, v1.max_size());
	EXPECT_EQ(2u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(2u, v3.max_size());
}

TYPED_TEST(MathSize2Test, NameAccessTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	{
		Size2 v{1, 2};
		EXPECT_EQ(1, v.w());
		EXPECT_EQ(2, v.h());

		v.w() = -3;
		v.h() =  4;

		EXPECT_EQ(-3, v.w());
		EXPECT_EQ( 4, v.h());
	}
	{
		Size2 v{3, 4};
		EXPECT_EQ(3, v.width());
		EXPECT_EQ(4, v.height());

		v.width()  = 1;
		v.height() = 2;

		EXPECT_EQ(1, v.width());
		EXPECT_EQ(2, v.height());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.w());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.h());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v{7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.width());
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.height());
	}
}

TYPED_TEST(MathSize2Test, SwizzleTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Size2 v(1, 2);

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 1), v.wwww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 2), v.wwwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 1), v.wwhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 2), v.wwhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 1), v.whww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 2), v.whwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 1), v.whhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 2), v.whhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 1), v.hwww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 2), v.hwwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 1), v.hwhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 2), v.hwhh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 1), v.hhww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 2), v.hhwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 1), v.hhhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 2), v.hhhh());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 1), v.www());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 2), v.wwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 1), v.whw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 2), v.whh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 1), v.hww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 2), v.hwh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 1), v.hhw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 2), v.hhh());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 1), v.ww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 2), v.wh());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 1), v.hw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 2), v.hh());
}

TYPED_TEST(MathSize2Test, SwapTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	Size2 v1{11, 12};
	Size2 v2{21, 22};

	EXPECT_EQ(Size2(11, 12), v1);
	EXPECT_EQ(Size2(21, 22), v2);

	v1.swap(v2);

	EXPECT_EQ(Size2(21, 22), v1);
	EXPECT_EQ(Size2(11, 12), v2);

	swap(v1, v2);

	EXPECT_EQ(Size2(11, 12), v1);
	EXPECT_EQ(Size2(21, 22), v2);
}

TYPED_TEST(MathSize2Test, PlusMinusTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	{
		Size2 v1(-1, 2);
		Size2 v3 = +v1;
		Size2 v4 = -v1;

		EXPECT_EQ(-1, v3[0]);
		EXPECT_EQ( 2, v3[1]);
		EXPECT_EQ( 1, v4[0]);
		EXPECT_EQ(-2, v4[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v2(3, -4);
		BKSGE_CONSTEXPR_OR_CONST Size2 v5 = +v2;
		BKSGE_CONSTEXPR_OR_CONST Size2 v6 = -v2;

		BKSGE_CONSTEXPR_EXPECT_EQ( 3, v5[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-4, v5[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-3, v6[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v6[1]);
	}
}

TYPED_TEST(MathSize2Test, AddTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	// Size2 += Size2
	{
		Size2 v;
		Size2 t = (v += Size2(2, 3));
		EXPECT_EQ(Size2(2, 3), v);
		EXPECT_EQ(t, v);
	}

	// Size2 + Size2 -> Size2
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 t =
			Size2(-3, 4) + Size2(0, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Size2(-3, 6), t);
	}
}

TYPED_TEST(MathSize2Test, SubTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	// Size2 -= Size2
	{
		Size2 v;
		Size2 t = (v -= Size2(2, 3));
		EXPECT_EQ(Size2(-2, -3), v);
		EXPECT_EQ(t, v);
	}

	// Size2 - Size2 -> Size2
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 t =
			Size2(-3, 4) - Size2(0, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Size2(-3, 2), t);
	}
}

TYPED_TEST(MathSize2Test, MulScalarTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	// Size2 *= スカラー
	{
		Size2 v(2, 3);
		{
			Size2 t = (v *= 4);
			EXPECT_EQ(Size2(8, 12), v);
			EXPECT_EQ(t, v);
		}
		{
			Size2 t = (v *= 0.5);
			EXPECT_EQ(Size2(4, 6), v);
			EXPECT_EQ(t, v);
		}
	}

	// Size2 * スカラー -> Size2
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 t = Size2(-3, 42) * -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Size2(12, -168), t);
	}
	{
		const Size2 t = Size2(4, 6) * 2.5;
		EXPECT_EQ(Size2(10, 15), t);
	}
	// スカラー * Size2 -> Size2
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 t = 5 * Size2(7, -8);
		BKSGE_CONSTEXPR_EXPECT_EQ(Size2(35, -40), t);
	}
	{
		const Size2 t = -1.5 * Size2(4, -6);
		EXPECT_EQ(Size2(-6, 9), t);
	}
}

TYPED_TEST(MathSize2Test, MulScaleTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;
	using Scale2 = bksge::math::Scale2<T>;

	// Size2 *= Scale2
	{
		Size2 v(2, 3);
		{
			Size2 t = (v *= Scale2(4, 5));
			EXPECT_EQ(Size2(8, 15), v);
			EXPECT_EQ(t, v);
		}
	}

	// Size2 * Scale2 -> Size2
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 t = Size2(-3, 2) * Scale2(-4, -5);
		BKSGE_CONSTEXPR_EXPECT_EQ(Size2(12, -10), t);
	}
}

TYPED_TEST(MathSize2Test, DivScalarTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	// Size2 /= スカラー
	{
		Size2 v(2, 4);
		{
			Size2 t = (v /= 2);
			EXPECT_EQ(Size2(1, 2), v);
			EXPECT_EQ(t, v);
		}
		{
			Size2 t = (v /= 0.5);
			EXPECT_EQ(Size2(2, 4), v);
			EXPECT_EQ(t, v);
		}
	}

	// Size2 / スカラー -> Size2
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 t = Size2(-4, 8) / -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Size2(1, -2), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 t = Size2(-4, 8) / 0.25;
		BKSGE_CONSTEXPR_EXPECT_EQ(Size2(-16, 32), t);
	}
}

TYPED_TEST(MathSize2Test, CompareTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	BKSGE_CONSTEXPR_OR_CONST Size2 v1(1, 2);
	BKSGE_CONSTEXPR_OR_CONST Size2 v2(1, 2);
	BKSGE_CONSTEXPR_OR_CONST Size2 v3(2, 2);
	BKSGE_CONSTEXPR_OR_CONST Size2 v4(1, 0);

	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v4);

	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v4);
}

TYPED_TEST(MathSize2Test, OutputStreamTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	{
		Size2 const v{1, -2};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2 }", ss.str());
	}
	{
		Size2 const v{-10, 9};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9 }", ss.str());
	}
}

TYPED_TEST(MathSize2Test, TupleElementTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	static_assert(std::is_same<typename std::tuple_element<0, Size2>::type, T>::value, "");
	static_assert(std::is_same<typename std::tuple_element<1, Size2>::type, T>::value, "");
}

TYPED_TEST(MathSize2Test, TupleGetTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	{
		Size2 v{1, 2};

		EXPECT_EQ(1, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));

		bksge::get<0>(v) = 5;

		EXPECT_EQ(Size2(5, 2), v);
		EXPECT_EQ(5, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Size2 v{1, 2};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(v));
	}
}

TYPED_TEST(MathSize2Test, TupleSizeTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	static_assert(std::tuple_size<Size2>::value == 2, "");
}

TYPED_TEST(MathSize2Test, ZeroTest)
{
	using T = TypeParam;
	using Size2 = bksge::math::Size2<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = Size2::Zero();
		static_assert(std::is_same<decltype(v), const Size2>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Size2(0, 0), v);
	}
	{
		const auto v = Size2::Zero();
		static_assert(std::is_same<decltype(v), const Size2>::value, "");
		EXPECT_EQ(Size2(0, 0), v);
	}
}

TYPED_TEST(MathSize2Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::Size2<T> const v { 7, 8 };

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

}	// namespace size2_test

}	// namespace bksge_math_test
