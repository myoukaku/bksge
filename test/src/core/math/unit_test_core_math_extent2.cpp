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
#include <bksge/fnd/config.hpp>
#include <sstream>
#include <functional>
#include <vector>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace extent2_test
{

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
	static_assert(!bksge::is_constructible<Extent2, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent2, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent2, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Extent2, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Extent2, T>::value, "");
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

TYPED_TEST(MathExtent2Test, CopyAssignTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 v1(0, 1);
	Extent2 v2(3, 4);
	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(3, v2[0]);
	EXPECT_EQ(4, v2[1]);

	v1 = Extent2(6, -7);
	v2 = Extent2i(-9, 10);
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
	v1 = v2 = Extent2f(4, 5);
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(5, v1[1]);
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
}

BKSGE_WARNING_POP()

TYPED_TEST(MathExtent2Test, IndexAccessTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 v{1, 2};
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);

		v[0] = -3;
		v[1] =  4;

		EXPECT_EQ(-3, v[0]);
		EXPECT_EQ( 4, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
	}
}

TYPED_TEST(MathExtent2Test, AtTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 v{1, 2};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_THROW((void)v.at(2), bksge::out_of_range);

		v.at(0) = -3;
		v.at(1) =  4;

		EXPECT_EQ(-3, v.at(0));
		EXPECT_EQ( 4, v.at(1));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		EXPECT_THROW((void)v.at(2), bksge::out_of_range);
	}
}

TYPED_TEST(MathExtent2Test, DataTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 v{1, 2};
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, *p);
		*p = 5;
		++p;
		EXPECT_EQ(2, *p);
		*p = 6;

		EXPECT_EQ(Extent2(5, 6), v);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Extent2 v{1, 2};
		BKSGE_STATIC_CONSTEXPR auto p = v.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
	}
#endif
}

TYPED_TEST(MathExtent2Test, IteratorTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	// begin, end (non const)
	{
		Extent2 v{1, 2};
		auto it = v.begin();
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(1, *it);
		*it++ = 5;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(2, *it);
		++it;
		EXPECT_TRUE(it == v.end());

		EXPECT_EQ(Extent2(5, 2), v);
	}
	// begin, end (const)
	{
		const Extent2 v{1, 2};
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
		const Extent2 v{1, 2};
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
		BKSGE_STATIC_CONSTEXPR Extent2 v{1, 2};
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

TYPED_TEST(MathExtent2Test, ReverseIteratorTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	// rbegin, rend (non const)
	{
		Extent2 v{1, 2};
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
		const Extent2 v{1, 2};
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
		const Extent2 v{1, 2};
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
		BKSGE_CXX17_STATIC_CONSTEXPR Extent2 v{1, 2};
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

TYPED_TEST(MathExtent2Test, EmptyTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 v1{};
	const Extent2 v2{};
	BKSGE_CONSTEXPR Extent2 v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathExtent2Test, SizeTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 v1{};
	const Extent2 v2{};
	BKSGE_CONSTEXPR Extent2 v3{};
	EXPECT_EQ(2u, v1.size());
	EXPECT_EQ(2u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(2u, v3.size());
}

TYPED_TEST(MathExtent2Test, MaxSizeTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 v1{};
	const Extent2 v2{};
	BKSGE_CONSTEXPR Extent2 v3{};
	EXPECT_EQ(2u, v1.max_size());
	EXPECT_EQ(2u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(2u, v3.max_size());
}

TYPED_TEST(MathExtent2Test, NameAccessTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 v{1, 2};
		EXPECT_EQ(1, v.w());
		EXPECT_EQ(2, v.h());

		v.w() = -3;
		v.h() =  4;

		EXPECT_EQ(-3, v.w());
		EXPECT_EQ( 4, v.h());
	}
	{
		Extent2 v{3, 4};
		EXPECT_EQ(3, v.width());
		EXPECT_EQ(4, v.height());

		v.width()  = 1;
		v.height() = 2;

		EXPECT_EQ(1, v.width());
		EXPECT_EQ(2, v.height());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.w());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.h());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v{7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.width());
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.height());
	}
}

TYPED_TEST(MathExtent2Test, SwizzleTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Extent2 v(1, 2);

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

TYPED_TEST(MathExtent2Test, SwapTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	Extent2 v1{11, 12};
	Extent2 v2{21, 22};

	EXPECT_EQ(Extent2(11, 12), v1);
	EXPECT_EQ(Extent2(21, 22), v2);

	v1.swap(v2);

	EXPECT_EQ(Extent2(21, 22), v1);
	EXPECT_EQ(Extent2(11, 12), v2);

	swap(v1, v2);

	EXPECT_EQ(Extent2(11, 12), v1);
	EXPECT_EQ(Extent2(21, 22), v2);
}

TYPED_TEST(MathExtent2Test, PlusMinusTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 v1(-1, 2);
		Extent2 v3 = +v1;
		Extent2 v4 = -v1;

		EXPECT_EQ(-1, v3[0]);
		EXPECT_EQ( 2, v3[1]);
		EXPECT_EQ( 1, v4[0]);
		EXPECT_EQ(-2, v4[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v2(3, -4);
		BKSGE_CONSTEXPR_OR_CONST Extent2 v5 = +v2;
		BKSGE_CONSTEXPR_OR_CONST Extent2 v6 = -v2;

		BKSGE_CONSTEXPR_EXPECT_EQ( 3, v5[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-4, v5[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-3, v6[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v6[1]);
	}
}

TYPED_TEST(MathExtent2Test, AddTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	// Extent2 += Extent2
	{
		Extent2 v;
		Extent2 t = (v += Extent2(2, 3));
		EXPECT_EQ(Extent2(2, 3), v);
		EXPECT_EQ(t, v);
	}

	// Extent2 + Extent2 -> Extent2
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 t =
			Extent2(-3, 4) + Extent2(0, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Extent2(-3, 6), t);
	}
}

TYPED_TEST(MathExtent2Test, SubTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	// Extent2 -= Extent2
	{
		Extent2 v;
		Extent2 t = (v -= Extent2(2, 3));
		EXPECT_EQ(Extent2(-2, -3), v);
		EXPECT_EQ(t, v);
	}

	// Extent2 - Extent2 -> Extent2
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 t =
			Extent2(-3, 4) - Extent2(0, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Extent2(-3, 2), t);
	}
}

TYPED_TEST(MathExtent2Test, MulScalarTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	// Extent2 *= スカラー
	{
		Extent2 v(2, 3);
		{
			Extent2 t = (v *= 4);
			EXPECT_EQ(Extent2(8, 12), v);
			EXPECT_EQ(t, v);
		}
		{
			Extent2 t = (v *= 0.5);
			EXPECT_EQ(Extent2(4, 6), v);
			EXPECT_EQ(t, v);
		}
	}

	// Extent2 * スカラー -> Extent2
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 t = Extent2(-3, 42) * -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Extent2(12, -168), t);
	}
	{
		const Extent2 t = Extent2(4, 6) * 2.5;
		EXPECT_EQ(Extent2(10, 15), t);
	}
	// スカラー * Extent2 -> Extent2
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 t = 5 * Extent2(7, -8);
		BKSGE_CONSTEXPR_EXPECT_EQ(Extent2(35, -40), t);
	}
	{
		const Extent2 t = -1.5 * Extent2(4, -6);
		EXPECT_EQ(Extent2(-6, 9), t);
	}
}

TYPED_TEST(MathExtent2Test, MulScaleTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;
	using Scale2 = bksge::math::Scale2<T>;

	// Extent2 *= Scale2
	{
		Extent2 v(2, 3);
		{
			Extent2 t = (v *= Scale2(4, 5));
			EXPECT_EQ(Extent2(8, 15), v);
			EXPECT_EQ(t, v);
		}
	}

	// Extent2 * Scale2 -> Extent2
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 t = Extent2(-3, 2) * Scale2(-4, -5);
		BKSGE_CONSTEXPR_EXPECT_EQ(Extent2(12, -10), t);
	}
}

TYPED_TEST(MathExtent2Test, DivScalarTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	// Extent2 /= スカラー
	{
		Extent2 v(2, 4);
		{
			Extent2 t = (v /= 2);
			EXPECT_EQ(Extent2(1, 2), v);
			EXPECT_EQ(t, v);
		}
		{
			Extent2 t = (v /= 0.5);
			EXPECT_EQ(Extent2(2, 4), v);
			EXPECT_EQ(t, v);
		}
	}

	// Extent2 / スカラー -> Extent2
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 t = Extent2(-4, 8) / -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Extent2(1, -2), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 t = Extent2(-4, 8) / 0.25;
		BKSGE_CONSTEXPR_EXPECT_EQ(Extent2(-16, 32), t);
	}
}

TYPED_TEST(MathExtent2Test, CompareTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	BKSGE_CONSTEXPR_OR_CONST Extent2 v1(1, 2);
	BKSGE_CONSTEXPR_OR_CONST Extent2 v2(1, 2);
	BKSGE_CONSTEXPR_OR_CONST Extent2 v3(2, 2);
	BKSGE_CONSTEXPR_OR_CONST Extent2 v4(1, 0);

	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v4);

	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v4);
}

TYPED_TEST(MathExtent2Test, OutputStreamTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 const v{1, -2};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2 }", ss.str());
	}
	{
		Extent2 const v{-10, 9};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9 }", ss.str());
	}
}

TYPED_TEST(MathExtent2Test, TupleElementTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	static_assert(bksge::is_same<typename bksge::tuple_element<0, Extent2>::type, T>::value, "");
	static_assert(bksge::is_same<typename bksge::tuple_element<1, Extent2>::type, T>::value, "");
}

TYPED_TEST(MathExtent2Test, TupleGetTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	{
		Extent2 v{1, 2};

		EXPECT_EQ(1, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));

		bksge::get<0>(v) = 5;

		EXPECT_EQ(Extent2(5, 2), v);
		EXPECT_EQ(5, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Extent2 v{1, 2};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(v));
	}
}

TYPED_TEST(MathExtent2Test, TupleSizeTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	static_assert(bksge::tuple_size<Extent2>::value == 2, "");
}

TYPED_TEST(MathExtent2Test, ZeroTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = Extent2::Zero();
		static_assert(bksge::is_same<decltype(v), const Extent2>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Extent2(0, 0), v);
	}
	{
		const auto v = Extent2::Zero();
		static_assert(bksge::is_same<decltype(v), const Extent2>::value, "");
		EXPECT_EQ(Extent2(0, 0), v);
	}
}

TYPED_TEST(MathExtent2Test, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::Extent2<T> const v { 7, 8 };

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

TYPED_TEST(MathExtent2Test, HashTest)
{
	using T = TypeParam;
	using Extent2 = bksge::math::Extent2<T>;

	std::hash<Extent2> h;

	Extent2 const c1( 1, 2);
	Extent2 const c2(-1, 2);
	Extent2 const c3( 1,-2);
	Extent2 const c4(-1,-2);
	Extent2 const c5( 2, 1);

	bksge::vector<bksge::size_t> v;
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

}	// namespace extent2_test

}	// namespace bksge_math_test
