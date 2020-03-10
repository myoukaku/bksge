/**
 *	@file	unit_test_core_math_quaternion.cpp
 *
 *	@brief	Quaternion のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/quaternion.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/fnd/cmath/degrees_to_radians.hpp>
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
#include <gtest/gtest.h>
#include <sstream>
#include <tuple>
#include <functional>
#include <vector>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace quaternion_test
{

using Quaternionf = bksge::math::Quaternion<float>;
using Quaternioni = bksge::math::Quaternion<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathQuaternionTest : public ::testing::Test {};
template <typename T>
class MathQuaternionFloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathQuaternionTest, MathTestTypes);
TYPED_TEST_SUITE(MathQuaternionFloatTest, MathFloatTestTypes);

TYPED_TEST(MathQuaternionTest, DefaultConstructTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	static_assert(sizeof(Quaternion) == sizeof(T) * 4, "");
	static_assert(bksge::is_default_constructible<Quaternion>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Quaternion>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Quaternion>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v={};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[3]);
	}
}

TYPED_TEST(MathQuaternionTest, ValueConstructTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	static_assert(!bksge::is_constructible<Quaternion, T, T, T, T, T>::value, "");
	static_assert( bksge::is_constructible<Quaternion, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Quaternion, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<Quaternion, T, T>::value, "");
	static_assert(!bksge::is_constructible<Quaternion, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Quaternion, T, T, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Quaternion, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Quaternion, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Quaternion, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Quaternion, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Quaternion, T, T, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Quaternion, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Quaternion, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Quaternion, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Quaternion, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v(1, 2, 3, 4);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v = {9, 10, 11, 12};
		BKSGE_CONSTEXPR_EXPECT_EQ(9, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3]);
	}
}

TYPED_TEST(MathQuaternionTest, CopyConstructTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	static_assert(bksge::is_constructible<Quaternion,  Quaternion  const&>::value, "");
	static_assert(bksge::is_constructible<Quaternion,  Quaternioni const&>::value, "");
	static_assert(bksge::is_constructible<Quaternion,  Quaternionf const&>::value, "");
	static_assert(bksge::is_constructible<Quaternioni, Quaternion  const&>::value, "");
	static_assert(bksge::is_constructible<Quaternioni, Quaternioni const&>::value, "");
	static_assert(bksge::is_constructible<Quaternioni, Quaternionf const&>::value, "");
	static_assert(bksge::is_constructible<Quaternionf, Quaternion  const&>::value, "");
	static_assert(bksge::is_constructible<Quaternionf, Quaternioni const&>::value, "");
	static_assert(bksge::is_constructible<Quaternionf, Quaternionf const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<Quaternion,  Quaternion  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Quaternion,  Quaternioni const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Quaternion,  Quaternionf const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Quaternioni, Quaternion  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Quaternioni, Quaternioni const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Quaternioni, Quaternionf const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Quaternionf, Quaternion  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Quaternionf, Quaternioni const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<Quaternionf, Quaternionf const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Quaternion,  Quaternion  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Quaternion,  Quaternioni const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Quaternion,  Quaternionf const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Quaternioni, Quaternion  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Quaternioni, Quaternioni const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Quaternioni, Quaternionf const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Quaternionf, Quaternion  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Quaternionf, Quaternioni const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Quaternionf, Quaternionf const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST Quaternion  v1{1, 2, 3, 4};
	BKSGE_CONSTEXPR_OR_CONST Quaternion  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST Quaternioni v3{v2};
	BKSGE_CONSTEXPR_OR_CONST Quaternionf v4{v2};

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

TYPED_TEST(MathQuaternionTest, FromMatrix3x3Test)
{
	using Quaternion = bksge::math::Quaternion<TypeParam>;
	using Matrix3x3 = bksge::math::Matrix3x3<TypeParam>;

	const double error = 0.0000001;

	{
		const auto m = Matrix3x3::Identity();
		const Quaternion q(m);
		EXPECT_EQ(Quaternion::Identity(), q);
	}
	{
		const auto angle = bksge::degrees_to_radians(30);
		const auto m = Matrix3x3::MakeRotationX(angle);
		const Quaternion q(m);
		const auto expected = Quaternion::MakeRotationX(angle);
		EXPECT_NEAR((double)expected[0], (double)q[0], error);
		EXPECT_NEAR((double)expected[1], (double)q[1], error);
		EXPECT_NEAR((double)expected[2], (double)q[2], error);
		EXPECT_NEAR((double)expected[3], (double)q[3], error);
	}
	{
		const auto angle = bksge::degrees_to_radians(45);
		const auto m = Matrix3x3::MakeRotationY(angle);
		const Quaternion q(m);
		const auto expected = Quaternion::MakeRotationY(angle);
		EXPECT_NEAR((double)expected[0], (double)q[0], error);
		EXPECT_NEAR((double)expected[1], (double)q[1], error);
		EXPECT_NEAR((double)expected[2], (double)q[2], error);
		EXPECT_NEAR((double)expected[3], (double)q[3], error);
	}
	{
		const auto angle = bksge::degrees_to_radians(90);
		const auto m = Matrix3x3::MakeRotationZ(angle);
		const Quaternion q(m);
		const auto expected = Quaternion::MakeRotationZ(angle);
		EXPECT_NEAR((double)expected[0], (double)q[0], error);
		EXPECT_NEAR((double)expected[1], (double)q[1], error);
		EXPECT_NEAR((double)expected[2], (double)q[2], error);
		EXPECT_NEAR((double)expected[3], (double)q[3], error);
	}
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

TYPED_TEST(MathQuaternionTest, CopyAssignTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	Quaternion v1(0, 1, 2, -2);
	Quaternion v2(3, 4, 5, 6);
	EXPECT_EQ(0, v1[0]);
	EXPECT_EQ(1, v1[1]);
	EXPECT_EQ(2, v1[2]);
	EXPECT_EQ(-2, v1[3]);
	EXPECT_EQ(3, v2[0]);
	EXPECT_EQ(4, v2[1]);
	EXPECT_EQ(5, v2[2]);
	EXPECT_EQ(6, v2[3]);

	v1 = Quaternion(6, -7, 8, 9);
	v2 = Quaternioni(-9, 10, 11, -12);
	EXPECT_EQ(6, v1[0]);
	EXPECT_EQ(-7, v1[1]);
	EXPECT_EQ(8, v1[2]);
	EXPECT_EQ(9, v1[3]);
	EXPECT_EQ(-9, v2[0]);
	EXPECT_EQ(10, v2[1]);
	EXPECT_EQ(11, v2[2]);
	EXPECT_EQ(-12, v2[3]);

	// 自己代入
	v1 = v1;
	v2 = v2;
	EXPECT_EQ(6, v1[0]);
	EXPECT_EQ(-7, v1[1]);
	EXPECT_EQ(8, v1[2]);
	EXPECT_EQ(9, v1[3]);
	EXPECT_EQ(-9, v2[0]);
	EXPECT_EQ(10, v2[1]);
	EXPECT_EQ(11, v2[2]);
	EXPECT_EQ(-12, v2[3]);

	// 多重代入
	v1 = v2 = Quaternionf(4, 5, 6, 7);
	EXPECT_EQ(4, v1[0]);
	EXPECT_EQ(5, v1[1]);
	EXPECT_EQ(6, v1[2]);
	EXPECT_EQ(7, v1[3]);
	EXPECT_EQ(4, v2[0]);
	EXPECT_EQ(5, v2[1]);
	EXPECT_EQ(6, v2[2]);
	EXPECT_EQ(7, v2[3]);
}

BKSGE_WARNING_POP()

TYPED_TEST(MathQuaternionTest, IndexAccessTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		Quaternion v{1, 2, 3, 4};
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_EQ(4, v[3]);

		v[0] = -3;
		v[1] =  4;
		v[2] = -5;
		v[3] =  6;

		EXPECT_EQ(-3, v[0]);
		EXPECT_EQ( 4, v[1]);
		EXPECT_EQ(-5, v[2]);
		EXPECT_EQ( 6, v[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v[3]);
	}
}

TYPED_TEST(MathQuaternionTest, AtTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		Quaternion v{1, 2, 3, 4};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
		EXPECT_EQ(4, v.at(3));
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);

		v.at(0) = -3;
		v.at(1) =  4;
		v.at(2) = -5;
		v.at(3) =  6;

		EXPECT_EQ(-3, v.at(0));
		EXPECT_EQ( 4, v.at(1));
		EXPECT_EQ(-5, v.at(2));
		EXPECT_EQ( 6, v.at(3));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.at(2));
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.at(3));
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
}

TYPED_TEST(MathQuaternionTest, DataTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		Quaternion v{1, 2, 3, 4};
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, *p);
		*p = 5;
		++p;
		EXPECT_EQ(2, *p);
		++p;
		EXPECT_EQ(3, *p);
		*p = 6;
		++p;
		EXPECT_EQ(4, *p);

		EXPECT_EQ(Quaternion(5, 2, 6, 4), v);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Quaternion v{1, 2, 3, 4};
		BKSGE_STATIC_CONSTEXPR auto p = v.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, p[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, p[3]);
	}
#endif
}

TYPED_TEST(MathQuaternionTest, IteratorTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	// begin, end (non const)
	{
		Quaternion v{1, 2, 3, 4};
		auto it = v.begin();
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(1, *it);
		*it++ = 5;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(2, *it);
		*++it = 6;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(6, *it);
		it++;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(4, *it);
		it++;
		EXPECT_TRUE(it == v.end());

		EXPECT_EQ(Quaternion(5, 2, 6, 4), v);
	}
	// begin, end (const)
	{
		const Quaternion v{1, 2, 3, 4};
		auto it = v.begin();
		EXPECT_TRUE(it != v.end());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(3, it[2]);
		EXPECT_EQ(4, it[3]);

		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(3, *++it);
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(2, *--it);
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(2, *it--);
		EXPECT_TRUE(it != v.end());
		it += 2;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(3, *it);
		it -= 2;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(1, *it);
		it += 3;
		EXPECT_TRUE(it != v.end());
		EXPECT_EQ(4, *it);
		++it;
		EXPECT_TRUE(it == v.end());
	}
	// cbegin, cend
	{
		const Quaternion v{1, 2, 3, 4};
		auto it = v.cbegin();
		EXPECT_TRUE(it != v.cend());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(3, it[2]);
		EXPECT_EQ(4, it[3]);

		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(3, *++it);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == v.cend());
	}
#if !defined(BKSGE_GCC)
	// begin, end (constexpr)
	{
		BKSGE_STATIC_CONSTEXPR Quaternion v{1, 2, 3, 4};
		BKSGE_CONSTEXPR_OR_CONST auto it = v.begin();
		BKSGE_CONSTEXPR_EXPECT_TRUE(it != v.end());

		BKSGE_CONSTEXPR_EXPECT_EQ(1, it[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, it[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, it[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, it[3]);

		BKSGE_CONSTEXPR_EXPECT_EQ(1, *it);
		BKSGE_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it2 != v.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(2, *it2);
		BKSGE_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it3 != v.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(3, *it3);
		BKSGE_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, *it4);
		BKSGE_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 != v.end());
		BKSGE_CONSTEXPR_EXPECT_EQ(4, *it5);
		BKSGE_CONSTEXPR_OR_CONST auto it6 = it5 + 1;
		BKSGE_CONSTEXPR_EXPECT_TRUE(it6 == v.end());
	}
#endif
}

TYPED_TEST(MathQuaternionTest, ReverseIteratorTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	// rbegin, rend (non const)
	{
		Quaternion v{1, 2, 3, 4};
		auto it = v.rbegin();
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(4, *it);
		*it++ = 5;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(3, *it);
		*++it = 6;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(6, *it);
		it++;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(1, *it);
		it++;
		EXPECT_TRUE(it == v.rend());

		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(6, v[1]);
		EXPECT_EQ(3, v[2]);
		EXPECT_EQ(5, v[3]);
	}
	// rbegin, rend (const)
	{
		const Quaternion v{1, 2, 3, 4};
		auto it = v.rbegin();
		EXPECT_TRUE(it != v.rend());

		EXPECT_EQ(4, it[0]);
		EXPECT_EQ(3, it[1]);
		EXPECT_EQ(2, it[2]);
		EXPECT_EQ(1, it[3]);

		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *++it);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(3, *--it);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(3, *it--);
		EXPECT_TRUE(it != v.rend());
		it += 2;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *it);
		it -= 2;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(4, *it);
		it += 3;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(1, *it);
		++it;
		EXPECT_TRUE(it == v.rend());
	}
	// crbegin, crend
	{
		const Quaternion v{1, 2, 3, 4};
		auto it = v.crbegin();
		EXPECT_TRUE(it != v.crend());

		EXPECT_EQ(4, it[0]);
		EXPECT_EQ(3, it[1]);
		EXPECT_EQ(2, it[2]);
		EXPECT_EQ(1, it[3]);

		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(2, *++it);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(2, *it++);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == v.crend());
	}
#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201603) && !defined(BKSGE_GCC)
	// rbegin, rend (constexpr)
	{
		BKSGE_CXX17_STATIC_CONSTEXPR Quaternion v{1, 2, 3, 4};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = v.rbegin();
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it != v.rend());

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, it[0]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, it[1]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, it[2]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, it[3]);

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(4, *it);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it2 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, *it2);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it3 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it3);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, *it4);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, *it5);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it6 = it5 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it6 == v.rend());
	}
#endif
}

TYPED_TEST(MathQuaternionTest, EmptyTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	Quaternion v1{};
	const           Quaternion v2{};
	BKSGE_CONSTEXPR Quaternion v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathQuaternionTest, SizeTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	Quaternion v1{};
	const           Quaternion v2{};
	BKSGE_CONSTEXPR Quaternion v3{};
	EXPECT_EQ(4u, v1.size());
	EXPECT_EQ(4u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, v3.size());
}

TYPED_TEST(MathQuaternionTest, MaxSizeTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	Quaternion v1{};
	const           Quaternion v2{};
	BKSGE_CONSTEXPR Quaternion v3{};
	EXPECT_EQ(4u, v1.max_size());
	EXPECT_EQ(4u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(4u, v3.max_size());
}

TYPED_TEST(MathQuaternionTest, NameAccessTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		Quaternion v{1, 2, 3, 4};
		EXPECT_EQ(1, v.x());
		EXPECT_EQ(2, v.y());
		EXPECT_EQ(3, v.z());
		EXPECT_EQ(4, v.w());

		v.x() = -3;
		v.y() =  4;
		v.z() = -5;
		v.w() =  6;

		EXPECT_EQ(-3, v.x());
		EXPECT_EQ( 4, v.y());
		EXPECT_EQ(-5, v.z());
		EXPECT_EQ( 6, v.w());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v{5, 6, 7, 8};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.x());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.y());
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.z());
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.w());
	}
}

TYPED_TEST(MathQuaternionTest, SwizzleTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CONSTEXPR_OR_CONST Quaternion q(1, 2, 3, 4);

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 1), q.xxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 2), q.xxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 3), q.xxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 1, 4), q.xxxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 1), q.xxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 2), q.xxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 3), q.xxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 2, 4), q.xxyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 1), q.xxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 2), q.xxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 3), q.xxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 3, 4), q.xxzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 1), q.xxwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 2), q.xxwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 3), q.xxwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 1, 4, 4), q.xxww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 1), q.xyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 2), q.xyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 3), q.xyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 1, 4), q.xyxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 1), q.xyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 2), q.xyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 3), q.xyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 2, 4), q.xyyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 1), q.xyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 2), q.xyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 3), q.xyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 3, 4), q.xyzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 1), q.xywx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 2), q.xywy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 3), q.xywz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 2, 4, 4), q.xyww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 1), q.xzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 2), q.xzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 3), q.xzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 1, 4), q.xzxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 1), q.xzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 2), q.xzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 3), q.xzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 2, 4), q.xzyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 1), q.xzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 2), q.xzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 3), q.xzzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 3, 4), q.xzzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 1), q.xzwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 2), q.xzwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 3), q.xzwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 3, 4, 4), q.xzww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 1), q.xwxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 2), q.xwxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 3), q.xwxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 1, 4), q.xwxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 1), q.xwyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 2), q.xwyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 3), q.xwyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 2, 4), q.xwyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 1), q.xwzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 2), q.xwzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 3), q.xwzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 3, 4), q.xwzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 1), q.xwwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 2), q.xwwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 3), q.xwwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(1, 4, 4, 4), q.xwww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 1), q.yxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 2), q.yxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 3), q.yxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 1, 4), q.yxxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 1), q.yxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 2), q.yxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 3), q.yxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 2, 4), q.yxyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 1), q.yxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 2), q.yxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 3), q.yxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 3, 4), q.yxzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 1), q.yxwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 2), q.yxwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 3), q.yxwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 1, 4, 4), q.yxww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 1), q.yyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 2), q.yyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 3), q.yyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 1, 4), q.yyxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 1), q.yyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 2), q.yyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 3), q.yyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 2, 4), q.yyyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 1), q.yyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 2), q.yyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 3), q.yyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 3, 4), q.yyzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 1), q.yywx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 2), q.yywy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 3), q.yywz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 2, 4, 4), q.yyww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 1), q.yzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 2), q.yzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 3), q.yzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 1, 4), q.yzxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 1), q.yzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 2), q.yzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 3), q.yzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 2, 4), q.yzyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 1), q.yzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 2), q.yzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 3), q.yzzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 3, 4), q.yzzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 1), q.yzwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 2), q.yzwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 3), q.yzwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 3, 4, 4), q.yzww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 1), q.ywxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 2), q.ywxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 3), q.ywxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 1, 4), q.ywxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 1), q.ywyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 2), q.ywyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 3), q.ywyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 2, 4), q.ywyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 1), q.ywzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 2), q.ywzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 3), q.ywzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 3, 4), q.ywzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 1), q.ywwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 2), q.ywwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 3), q.ywwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(2, 4, 4, 4), q.ywww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 1), q.zxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 2), q.zxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 3), q.zxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 1, 4), q.zxxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 1), q.zxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 2), q.zxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 3), q.zxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 2, 4), q.zxyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 1), q.zxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 2), q.zxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 3), q.zxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 3, 4), q.zxzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 1), q.zxwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 2), q.zxwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 3), q.zxwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 1, 4, 4), q.zxww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 1), q.zyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 2), q.zyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 3), q.zyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 1, 4), q.zyxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 1), q.zyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 2), q.zyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 3), q.zyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 2, 4), q.zyyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 1), q.zyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 2), q.zyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 3), q.zyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 3, 4), q.zyzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 1), q.zywx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 2), q.zywy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 3), q.zywz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 2, 4, 4), q.zyww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 1), q.zzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 2), q.zzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 3), q.zzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 1, 4), q.zzxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 1), q.zzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 2), q.zzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 3), q.zzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 2, 4), q.zzyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 1), q.zzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 2), q.zzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 3), q.zzzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 3, 4), q.zzzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 1), q.zzwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 2), q.zzwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 3), q.zzwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 3, 4, 4), q.zzww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 1), q.zwxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 2), q.zwxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 3), q.zwxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 1, 4), q.zwxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 1), q.zwyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 2), q.zwyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 3), q.zwyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 2, 4), q.zwyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 1), q.zwzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 2), q.zwzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 3), q.zwzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 3, 4), q.zwzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 1), q.zwwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 2), q.zwwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 3), q.zwwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(3, 4, 4, 4), q.zwww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 1), q.wxxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 2), q.wxxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 3), q.wxxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 1, 4), q.wxxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 1), q.wxyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 2), q.wxyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 3), q.wxyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 2, 4), q.wxyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 1), q.wxzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 2), q.wxzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 3), q.wxzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 3, 4), q.wxzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 1), q.wxwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 2), q.wxwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 3), q.wxwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 1, 4, 4), q.wxww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 1), q.wyxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 2), q.wyxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 3), q.wyxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 1, 4), q.wyxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 1), q.wyyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 2), q.wyyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 3), q.wyyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 2, 4), q.wyyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 1), q.wyzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 2), q.wyzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 3), q.wyzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 3, 4), q.wyzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 1), q.wywx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 2), q.wywy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 3), q.wywz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 2, 4, 4), q.wyww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 1), q.wzxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 2), q.wzxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 3), q.wzxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 1, 4), q.wzxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 1), q.wzyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 2), q.wzyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 3), q.wzyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 2, 4), q.wzyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 1), q.wzzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 2), q.wzzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 3), q.wzzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 3, 4), q.wzzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 1), q.wzwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 2), q.wzwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 3), q.wzwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 3, 4, 4), q.wzww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 1), q.wwxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 2), q.wwxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 3), q.wwxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 1, 4), q.wwxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 1), q.wwyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 2), q.wwyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 3), q.wwyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 2, 4), q.wwyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 1), q.wwzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 2), q.wwzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 3), q.wwzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 3, 4), q.wwzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 1), q.wwwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 2), q.wwwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 3), q.wwwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector4(4, 4, 4, 4), q.wwww());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 1), q.xxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 2), q.xxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 3), q.xxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 1, 4), q.xxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 1), q.xyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 2), q.xyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 3), q.xyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 2, 4), q.xyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 1), q.xzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 2), q.xzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 3), q.xzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 3, 4), q.xzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 1), q.xwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 2), q.xwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 3), q.xwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(1, 4, 4), q.xww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 1), q.yxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 2), q.yxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 3), q.yxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 1, 4), q.yxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 1), q.yyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 2), q.yyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 3), q.yyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 2, 4), q.yyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 1), q.yzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 2), q.yzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 3), q.yzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 3, 4), q.yzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 1), q.ywx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 2), q.ywy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 3), q.ywz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(2, 4, 4), q.yww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 1), q.zxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 2), q.zxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 3), q.zxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 1, 4), q.zxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 1), q.zyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 2), q.zyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 3), q.zyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 2, 4), q.zyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 1), q.zzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 2), q.zzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 3), q.zzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 3, 4), q.zzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 1), q.zwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 2), q.zwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 3), q.zwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(3, 4, 4), q.zww());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 1), q.wxx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 2), q.wxy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 3), q.wxz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 1, 4), q.wxw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 1), q.wyx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 2), q.wyy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 3), q.wyz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 2, 4), q.wyw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 1), q.wzx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 2), q.wzy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 3), q.wzz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 3, 4), q.wzw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 1), q.wwx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 2), q.wwy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 3), q.wwz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(4, 4, 4), q.www());

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 1), q.xx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 2), q.xy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 3), q.xz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(1, 4), q.xw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 1), q.yx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 2), q.yy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 3), q.yz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(2, 4), q.yw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 1), q.zx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 2), q.zy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 3), q.zz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(3, 4), q.zw());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 1), q.wx());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 2), q.wy());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 3), q.wz());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector2(4, 4), q.ww());
}

TYPED_TEST(MathQuaternionTest, SwapTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	Quaternion v1{11, 12, 13, 14};
	Quaternion v2{21, 22, 23, 24};

	EXPECT_EQ(Quaternion(11, 12, 13, 14), v1);
	EXPECT_EQ(Quaternion(21, 22, 23, 24), v2);

	v1.swap(v2);

	EXPECT_EQ(Quaternion(21, 22, 23, 24), v1);
	EXPECT_EQ(Quaternion(11, 12, 13, 14), v2);

	swap(v1, v2);

	EXPECT_EQ(Quaternion(11, 12, 13, 14), v1);
	EXPECT_EQ(Quaternion(21, 22, 23, 24), v2);
}

TYPED_TEST(MathQuaternionTest, PlusMinusTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		Quaternion v1(-1, 2, -3, 4);
		Quaternion v3 = +v1;
		Quaternion v4 = -v1;

		EXPECT_EQ(-1, v3[0]);
		EXPECT_EQ( 2, v3[1]);
		EXPECT_EQ(-3, v3[2]);
		EXPECT_EQ( 4, v3[3]);
		EXPECT_EQ( 1, v4[0]);
		EXPECT_EQ(-2, v4[1]);
		EXPECT_EQ( 3, v4[2]);
		EXPECT_EQ(-4, v4[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v2(3, -4, 5, -6);
		BKSGE_CONSTEXPR_OR_CONST Quaternion v5 = +v2;
		BKSGE_CONSTEXPR_OR_CONST Quaternion v6 = -v2;

		BKSGE_CONSTEXPR_EXPECT_EQ( 3, v5[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-4, v5[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 5, v5[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-6, v5[3]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-3, v6[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 4, v6[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(-5, v6[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ( 6, v6[3]);
	}
}

TYPED_TEST(MathQuaternionTest, AddTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	// Quaternion += Quaternion
	{
		Quaternion v;
		Quaternion t = (v += Quaternion(2, 3, -4, 5));
		EXPECT_EQ(Quaternion(2, 3, -4, 5), v);
		EXPECT_EQ(t, v);
	}

	// Quaternion + Quaternion -> Quaternion
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion t =
			Quaternion(-3, 4, 5, 6) + Quaternion(0, 2, -1, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(-3, 6, 4, 9), t);
	}
}

TYPED_TEST(MathQuaternionTest, SubTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	// Quaternion -= Quaternion
	{
		Quaternion v;
		Quaternion t = (v -= Quaternion(2, 3, -4, 5));
		EXPECT_EQ(Quaternion(-2, -3, 4, -5), v);
		EXPECT_EQ(t, v);
	}

	// Quaternion - Quaternion -> Quaternion
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion t =
			Quaternion(-3, 4, 5, 6) - Quaternion(0, 2, -1, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(-3, 2, 6, 3), t);
	}
}

TYPED_TEST(MathQuaternionTest, MulScalarTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	// Quaternion *= スカラー
	{
		Quaternion v(2, 3, 4, 5);
		{
			Quaternion t = (v *= 4);
			EXPECT_EQ(Quaternion(8, 12, 16, 20), v);
			EXPECT_EQ(t, v);
		}
		{
			Quaternion t = (v *= 0.5);
			EXPECT_EQ(Quaternion(4, 6, 8, 10), v);
			EXPECT_EQ(t, v);
		}
	}

	// Quaternion * スカラー -> Quaternion
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion t = Quaternion(-3, 42, 5, 4) * -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(12, -168, -20, -16), t);
	}
	{
		const Quaternion t = Quaternion(4, 6, 2, -10) * 2.5;
		EXPECT_EQ(Quaternion(10, 15, 5, -25), t);
	}
	// スカラー * Quaternion -> Quaternion
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion t = 5 * Quaternion(7, -8, 9, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(35, -40, 45, 10), t);
	}
	{
		const Quaternion t = -1.5 * Quaternion(4, -6, -2, 8);
		EXPECT_EQ(Quaternion(-6, 9, 3, -12), t);
	}
}

TYPED_TEST(MathQuaternionTest, MulQuaternionTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	// Quaternion *= Quaternion
	{
		Quaternion q(2, 3, 4, 5);
		auto t = (q *= Quaternion(3, 4, 5, 6));
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		EXPECT_EQ(Quaternion(26, 40, 48, -8), q);
		EXPECT_EQ(t, q);
	}

	// Quaternion * Quaternion -> Quaternion
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(1, 2, 3, 4) * Quaternion(5, -6, 7, 8);
		static_assert(bksge::is_same<decltype(t), const Quaternion>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(60, 0, 36, 18), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(1, 2, 3, 4) * Quaternion(5, 6, -7, 8) * Quaternion(9, 10, 11, -12);
		static_assert(bksge::is_same<decltype(t), const Quaternion>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(1134, -412, -106, -928), t);
	}

	// Identity * Identity = Identity
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion::Identity() * Quaternion::Identity();
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion::Identity(), t);
	}

	// ii = jj = kk = ijk = -1
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(1, 0, 0, 0) * Quaternion(1, 0, 0, 0);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(0, 0, 0, -1), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(0, 1, 0, 0) * Quaternion(0, 1, 0, 0);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(0, 0, 0, -1), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(0, 0, 1, 0) * Quaternion(0, 0, 1, 0);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(0, 0, 0, -1), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(1, 0, 0, 0) * Quaternion(0, 1, 0, 0) * Quaternion(0, 0, 1, 0);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(0, 0, 0, -1), t);
	}

	// ij = -ji = k
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(1, 0, 0, 0) * Quaternion(0, 1, 0, 0);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(0, 0, 1, 0), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(0, -1, 0, 0) * Quaternion(1, 0, 0, 0);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(0, 0, 1, 0), t);
	}

	// jk = -kj = i
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(0, 1, 0, 0) * Quaternion(0, 0, 1, 0);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(1, 0, 0, 0), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(0, 0, -1, 0) * Quaternion(0, 1, 0, 0);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(1, 0, 0, 0), t);
	}

	// ki = -ik = j
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(0, 0, 1, 0) * Quaternion(1, 0, 0, 0);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(0, 1, 0, 0), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Quaternion(-1, 0, 0, 0) * Quaternion(0, 0, 1, 0);
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(0, 1, 0, 0), t);
	}
}

TYPED_TEST(MathQuaternionFloatTest, MulVector3Test)
{
	using Quaternion = bksge::math::Quaternion<TypeParam>;
	using Vector3 = bksge::math::Vector3<TypeParam>;

	{
		const double error = 0.0000001;

		const auto q1 = Quaternion::MakeRotationX(bksge::degrees_to_radians(90));
		const auto q2 = Quaternion::MakeRotationY(bksge::degrees_to_radians(90));
		const auto q3 = Quaternion::MakeRotationZ(bksge::degrees_to_radians(90));

		const Vector3 xaxis(1, 0, 0);
		const Vector3 yaxis(0, 1, 0);
		const Vector3 zaxis(0, 0, 1);
		const Vector3 v1 = xaxis * q1;
		const Vector3 v2 = xaxis * q2;
		const Vector3 v3 = xaxis * q3;
		const Vector3 v4 = yaxis * q1;
		const Vector3 v5 = yaxis * q2;
		const Vector3 v6 = yaxis * q3;
		const Vector3 v7 = zaxis * q1;
		const Vector3 v8 = zaxis * q2;
		const Vector3 v9 = zaxis * q3;

		EXPECT_NEAR( 1.0, (double)v1[0], error);
		EXPECT_NEAR( 0.0, (double)v1[1], error);
		EXPECT_NEAR( 0.0, (double)v1[2], error);
		EXPECT_NEAR( 0.0, (double)v2[0], error);
		EXPECT_NEAR( 0.0, (double)v2[1], error);
		EXPECT_NEAR(-1.0, (double)v2[2], error);
		EXPECT_NEAR( 0.0, (double)v3[0], error);
		EXPECT_NEAR( 1.0, (double)v3[1], error);
		EXPECT_NEAR( 0.0, (double)v3[2], error);
		EXPECT_NEAR( 0.0, (double)v4[0], error);
		EXPECT_NEAR( 0.0, (double)v4[1], error);
		EXPECT_NEAR( 1.0, (double)v4[2], error);
		EXPECT_NEAR( 0.0, (double)v5[0], error);
		EXPECT_NEAR( 1.0, (double)v5[1], error);
		EXPECT_NEAR( 0.0, (double)v5[2], error);
		EXPECT_NEAR(-1.0, (double)v6[0], error);
		EXPECT_NEAR( 0.0, (double)v6[1], error);
		EXPECT_NEAR( 0.0, (double)v6[2], error);
		EXPECT_NEAR( 0.0, (double)v7[0], error);
		EXPECT_NEAR(-1.0, (double)v7[1], error);
		EXPECT_NEAR( 0.0, (double)v7[2], error);
		EXPECT_NEAR( 1.0, (double)v8[0], error);
		EXPECT_NEAR( 0.0, (double)v8[1], error);
		EXPECT_NEAR( 0.0, (double)v8[2], error);
		EXPECT_NEAR( 0.0, (double)v9[0], error);
		EXPECT_NEAR( 0.0, (double)v9[1], error);
		EXPECT_NEAR( 1.0, (double)v9[2], error);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v { 1, 2, 3 };
		BKSGE_CONSTEXPR_OR_CONST Quaternion q = Quaternion::Identity();
		BKSGE_CONSTEXPR_OR_CONST auto v2 = v * q;
		BKSGE_CONSTEXPR_EXPECT_EQ(v, v2);
	}
	{
		const double error = 0.000001;

		Vector3 v { 1, 2, 3 };

		{
			const auto t = v *= Quaternion::Identity();
			EXPECT_NEAR( 1.0, (double)v[0], error);
			EXPECT_NEAR( 2.0, (double)v[1], error);
			EXPECT_NEAR( 3.0, (double)v[2], error);
			EXPECT_EQ(t, v);
		}
		{
			const auto t = v *= Quaternion::MakeRotationX(bksge::degrees_to_radians(90));
			EXPECT_NEAR( 1.0, (double)v[0], error);
			EXPECT_NEAR(-3.0, (double)v[1], error);
			EXPECT_NEAR( 2.0, (double)v[2], error);
			EXPECT_EQ(t, v);
		}
		{
			const auto t = v *= Quaternion::MakeRotationY(bksge::degrees_to_radians(90));
			EXPECT_NEAR( 2.0, (double)v[0], error);
			EXPECT_NEAR(-3.0, (double)v[1], error);
			EXPECT_NEAR(-1.0, (double)v[2], error);
			EXPECT_EQ(t, v);
		}
		{
			const auto t = v *= Quaternion::MakeRotationZ(bksge::degrees_to_radians(90));
			EXPECT_NEAR( 3.0, (double)v[0], error);
			EXPECT_NEAR( 2.0, (double)v[1], error);
			EXPECT_NEAR(-1.0, (double)v[2], error);
			EXPECT_EQ(t, v);
		}
	}
}

TYPED_TEST(MathQuaternionTest, DivScalarTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	// Quaternion /= スカラー
	{
		Quaternion v(2, 4, 6, 8);
		{
			Quaternion t = (v /= 2);
			EXPECT_EQ(Quaternion(1, 2, 3, 4), v);
			EXPECT_EQ(t, v);
		}
		{
			Quaternion t = (v /= 0.5);
			EXPECT_EQ(Quaternion(2, 4, 6, 8), v);
			EXPECT_EQ(t, v);
		}
	}

	// Quaternion / スカラー -> Quaternion
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion t = Quaternion(-4, 8, -12, 16) / -4;
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(1, -2, 3, -4), t);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion t = Quaternion(-4, 8, -12, 16) / 0.25;
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(-16, 32, -48, 64), t);
	}
}

TYPED_TEST(MathQuaternionTest, CompareTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	BKSGE_CONSTEXPR_OR_CONST Quaternion v1(1, 2, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Quaternion v2(1, 2, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Quaternion v3(2, 2, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Quaternion v4(1, 0, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST Quaternion v5(1, 2, 2, 4);
	BKSGE_CONSTEXPR_OR_CONST Quaternion v6(1, 2, 3, 5);

	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v4);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v5);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v6);

	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v4);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v5);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v6);
}

TYPED_TEST(MathQuaternionTest, OutputStreamTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		Quaternion const v{1, -2, 3, 4};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2, 3, 4 }", ss.str());
	}
	{
		Quaternion const v{-10, 9, 8, -7};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9, 8, -7 }", ss.str());
	}
}

TYPED_TEST(MathQuaternionTest, TupleElementTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	static_assert(bksge::is_same<typename std::tuple_element<0, Quaternion>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<1, Quaternion>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<2, Quaternion>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<3, Quaternion>::type, T>::value, "");
}

TYPED_TEST(MathQuaternionTest, TupleGetTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		Quaternion v{1, 2, 3, 4};

		EXPECT_EQ(1, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));
		EXPECT_EQ(4, bksge::get<3>(v));

		bksge::get<0>(v) = 5;
		bksge::get<3>(v) = 6;

		EXPECT_EQ(Quaternion(5, 2, 3, 6), v);
		EXPECT_EQ(5, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));
		EXPECT_EQ(6, bksge::get<3>(v));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion v{1, 2, 3, 4};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::get<2>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(4, bksge::get<3>(v));
	}
}

TYPED_TEST(MathQuaternionTest, TupleSizeTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	static_assert(std::tuple_size<Quaternion>::value == 4, "");
}

TYPED_TEST(MathQuaternionTest, RealTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Quaternion( 0, 0, 0, 0).real());
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, Quaternion( 1, 2, 3, 4).real());
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, Quaternion(-1, 2, 3, 4).real());
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, Quaternion( 1,-2, 3, 4).real());
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, Quaternion( 1, 2,-3, 4).real());
	BKSGE_CONSTEXPR_EXPECT_EQ(-4, Quaternion( 1, 2, 3,-4).real());
	BKSGE_CONSTEXPR_EXPECT_EQ( 8, Quaternion( 5, 6, 7, 8).real());
}

TYPED_TEST(MathQuaternionTest, ImagTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;
	using Vector3 = bksge::math::Vector3<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 0, 0, 0), Quaternion( 0, 0, 0, 0).imag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 1, 2, 3), Quaternion( 1, 2, 3, 4).imag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3(-1, 2, 3), Quaternion(-1, 2, 3, 4).imag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 1,-2, 3), Quaternion( 1,-2, 3, 4).imag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 1, 2,-3), Quaternion( 1, 2,-3, 4).imag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 1, 2, 3), Quaternion( 1, 2, 3,-4).imag());
	BKSGE_CONSTEXPR_EXPECT_EQ(Vector3( 5, 6, 7), Quaternion( 5, 6, 7, 8).imag());
}

TYPED_TEST(MathQuaternionTest, ZeroTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = Quaternion::Zero();
		static_assert(bksge::is_same<decltype(v), const Quaternion>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(0, 0, 0, 0), v);
	}
	{
		const auto v = Quaternion::Zero();
		static_assert(bksge::is_same<decltype(v), const Quaternion>::value, "");
		EXPECT_EQ(Quaternion(0, 0, 0, 0), v);
	}
}

TYPED_TEST(MathQuaternionTest, IdentityTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto q = Quaternion::Identity();
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(0, 0, 0, 1), q);
	}
	{
		const auto q = Quaternion::Identity();
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_EQ(Quaternion(0, 0, 0, 1), q);
	}
}

TYPED_TEST(MathQuaternionTest, ConjugateTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	BKSGE_CONSTEXPR_OR_CONST Quaternion q1(1, 2, 3, 4);
	BKSGE_CONSTEXPR_OR_CONST auto q2 = Conjugate(q1);
	BKSGE_CONSTEXPR_OR_CONST auto q3 = Conjugate(q2);
	static_assert(bksge::is_same<decltype(q2), const Quaternion>::value, "");
	static_assert(bksge::is_same<decltype(q3), const Quaternion>::value, "");

	BKSGE_CONSTEXPR_EXPECT_EQ(q1, q3);
	BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion( 1,  2,  3, 4), q1);
	BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(-1, -2, -3, 4), q2);
	BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion( 1,  2,  3, 4), q3);

	{
		// 四元数 q = ix + jy + kz + w の共役をq'としたとき、
		// q * q' = q' * q = x^2 + y^2 + z^2 + w^2
		// となる。
		BKSGE_CONSTEXPR_OR_CONST Quaternion expected{ 0, 0, 0, 1*1 + 2*2 + 3*3 + 4*4 };
		BKSGE_CONSTEXPR_EXPECT_EQ(expected, q1 * q2);
		BKSGE_CONSTEXPR_EXPECT_EQ(expected, q2 * q1);
	}
}

TYPED_TEST(MathQuaternionFloatTest, InversedTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	BKSGE_CONSTEXPR_OR_CONST Quaternion q1(1, 2, 3, 4);
	                   const Quaternion q2(9, 41, -5, 6);

	BKSGE_CONSTEXPR_OR_CONST auto q1_inv = Inversed(q1);
	                   const auto q2_inv = Inversed(q2);
	static_assert(bksge::is_same<decltype(q1_inv), const Quaternion>::value, "");
	static_assert(bksge::is_same<decltype(q2_inv), const Quaternion>::value, "");

	BKSGE_CONSTEXPR_OR_CONST double error = 0.000001;
	BKSGE_CONSTEXPR_EXPECT_NEAR(-0.03333333333333333, (double)q1_inv.x(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-0.06666666666666666, (double)q1_inv.y(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(-0.10000000000000000, (double)q1_inv.z(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR( 0.13333333333333333, (double)q1_inv.w(), error);
	                EXPECT_NEAR(-0.00493691716950082, (double)q2_inv.x(), error);
	                EXPECT_NEAR(-0.02249040043883708, (double)q2_inv.y(), error);
	                EXPECT_NEAR( 0.00274273176083379, (double)q2_inv.z(), error);
	                EXPECT_NEAR( 0.00329127811300054, (double)q2_inv.w(), error);

	// あるクォータニオンとその逆クォータニオンをかけると単位クォータニオンになる
	BKSGE_CONSTEXPR_OR_CONST auto q3 = q1 * q1_inv;
	                   const auto q4 = q2 * q2_inv;
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.0, (double)q3.x(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.0, (double)q3.y(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(0.0, (double)q3.z(), error);
	BKSGE_CONSTEXPR_EXPECT_NEAR(1.0, (double)q3.w(), error);
	                EXPECT_NEAR(0.0, (double)q4.x(), error);
	                EXPECT_NEAR(0.0, (double)q4.y(), error);
	                EXPECT_NEAR(0.0, (double)q4.z(), error);
	                EXPECT_NEAR(1.0, (double)q4.w(), error);
}

TYPED_TEST(MathQuaternionFloatTest, NormalizedTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto t = Normalized(Quaternion(0,  0,  0, 0));
		static_assert(bksge::is_same<decltype(t), const Quaternion>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion( 0, 0, 0, 1), t);
	}
	EXPECT_EQ(Quaternion( 1, 0, 0, 0), Normalized(Quaternion(  1,  0,  0, 0)));
	EXPECT_EQ(Quaternion(-1, 0, 0, 0), Normalized(Quaternion( -1,  0,  0, 0)));
	EXPECT_EQ(Quaternion( 1, 0, 0, 0), Normalized(Quaternion( 10,  0,  0, 0)));
	EXPECT_EQ(Quaternion(-1, 0, 0, 0), Normalized(Quaternion(-10,  0,  0, 0)));
	EXPECT_EQ(Quaternion( 0, 1, 0, 0), Normalized(Quaternion(  0,  1,  0, 0)));
	EXPECT_EQ(Quaternion( 0,-1, 0, 0), Normalized(Quaternion(  0, -1,  0, 0)));
	EXPECT_EQ(Quaternion( 0, 1, 0, 0), Normalized(Quaternion(  0,  5,  0, 0)));
	EXPECT_EQ(Quaternion( 0,-1, 0, 0), Normalized(Quaternion(  0, -5,  0, 0)));
	EXPECT_EQ(Quaternion( 0, 0, 1, 0), Normalized(Quaternion(  0,  0,  1, 0)));
	EXPECT_EQ(Quaternion( 0, 0,-1, 0), Normalized(Quaternion(  0,  0, -1, 0)));
	EXPECT_EQ(Quaternion( 0, 0, 1, 0), Normalized(Quaternion(  0,  0, 42, 0)));
	EXPECT_EQ(Quaternion( 0, 0,-1, 0), Normalized(Quaternion(  0,  0,-42, 0)));
	EXPECT_EQ(Quaternion( 0, 0, 0, 1), Normalized(Quaternion(  0,  0,  0, 3)));
	EXPECT_EQ(Quaternion( 0, 0, 0,-1), Normalized(Quaternion(  0,  0,  0,-3)));
	{
		const double error = 0.000001;
		const auto t = Normalized(Quaternion(1, 2, 3, 4));
		EXPECT_NEAR(0.18257418583, (double)t.x(), error);
		EXPECT_NEAR(0.36514837167, (double)t.y(), error);
		EXPECT_NEAR(0.54772255750, (double)t.z(), error);
		EXPECT_NEAR(0.73029674334, (double)t.w(), error);
	}
}

TYPED_TEST(MathQuaternionTest, DotTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ( 0, Dot(Quaternion( 0, 0, 0, 0), Quaternion( 0, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 1, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 3, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0, 1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-4, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0, 0, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-1, Dot(Quaternion( 1,-2, 3,-4), Quaternion(-1, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0,-1, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-3, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0,-1, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 4, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0, 0,-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 2, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 2, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-4, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 2, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 6, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0, 2, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-8, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0, 0, 2)));
	BKSGE_CONSTEXPR_EXPECT_EQ(-2, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 1, 1, 1, 1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(10, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 1,-1, 1,-1)));
	BKSGE_CONSTEXPR_EXPECT_EQ(30, Dot(Quaternion( 1,-2, 3,-4), Quaternion( 1,-2, 3,-4)));
}

TYPED_TEST(MathQuaternionTest, SquaredLengthTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	BKSGE_CONSTEXPR_EXPECT_EQ(  0, SquaredLength(Quaternion(0, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ(  9, SquaredLength(Quaternion(3, 0, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 16, SquaredLength(Quaternion(0, 4, 0, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 25, SquaredLength(Quaternion(0, 0,-5, 0)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 36, SquaredLength(Quaternion(0, 0, 0, 6)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 30, SquaredLength(Quaternion(1, 2, 3, 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 30, SquaredLength(Quaternion(1,-2, 3, 4)));
	BKSGE_CONSTEXPR_EXPECT_EQ( 30, SquaredLength(Quaternion(1, 2, 3,-4)));
	BKSGE_CONSTEXPR_EXPECT_EQ(109, SquaredLength(Quaternion(4,-8, 5, 2)));
}

TYPED_TEST(MathQuaternionTest, LengthTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.000001;

	EXPECT_EQ(0, Length(Quaternion( 0, 0, 0, 0)));
	EXPECT_EQ(3, Length(Quaternion( 3, 0, 0, 0)));
	EXPECT_EQ(3, Length(Quaternion(-3, 0, 0, 0)));
	EXPECT_EQ(4, Length(Quaternion( 0, 4, 0, 0)));
	EXPECT_EQ(4, Length(Quaternion( 0,-4, 0, 0)));
	EXPECT_EQ(5, Length(Quaternion( 0, 0, 5, 0)));
	EXPECT_EQ(5, Length(Quaternion( 0, 0,-5, 0)));
	EXPECT_EQ(6, Length(Quaternion( 0, 0, 0, 6)));
	EXPECT_EQ(6, Length(Quaternion( 0, 0, 0,-6)));
	EXPECT_NEAR(5.47722557505, (double)Length(Quaternion(1, 2, 3, 4)), error);
	EXPECT_NEAR(5.47722557505, (double)Length(Quaternion(1,-2,-3, 4)), error);
	EXPECT_NEAR(10.4403065089, (double)Length(Quaternion(4,-8, 5, 2)), error);
}

TYPED_TEST(MathQuaternionTest, NormTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.000001;

	EXPECT_EQ(0, Norm(Quaternion(0, 0, 0, 0)));
	EXPECT_EQ(3, Norm(Quaternion(3, 0, 0, 0)));
	EXPECT_EQ(4, Norm(Quaternion(0, 4, 0, 0)));
	EXPECT_EQ(5, Norm(Quaternion(0, 0,-5, 0)));
	EXPECT_EQ(6, Norm(Quaternion(0, 0, 0,-6)));
	EXPECT_NEAR(5.47722557505, (double)Norm(Quaternion(1, 2, 3, 4)), error);
	EXPECT_NEAR(5.47722557505, (double)Norm(Quaternion(1,-2,-3, 4)), error);
	EXPECT_NEAR(10.4403065089, (double)Norm(Quaternion(4,-8, 5, 2)), error);
}

TYPED_TEST(MathQuaternionFloatTest, LerpTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion q1 {  0,  0,  0,  0 };
		BKSGE_CONSTEXPR_OR_CONST Quaternion q2 { 10, 20, 30, 40 };

		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion( 0.0,  0.0,  0.0,  0.0), Lerp(q1, q2, 0.00f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion( 2.5,  5.0,  7.5, 10.0), Lerp(q1, q2, 0.25f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion( 5.0, 10.0, 15.0, 20.0), Lerp(q1, q2, 0.50f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion( 7.5, 15.0, 22.5, 30.0), Lerp(q1, q2, 0.75f));
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(10.0, 20.0, 30.0, 40.0), Lerp(q1, q2, 1.00f));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Quaternion q1 { -10,  10,  20, -30 };
		BKSGE_CONSTEXPR_OR_CONST Quaternion q2 {  10, -20, -30,  40 };

		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(-10.0,  10.0,  20.0, -30.0), Lerp(q1, q2, 0.00));
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion( -5.0,   2.5,   7.5, -12.5), Lerp(q1, q2, 0.25));
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(  0.0,  -5.0,  -5.0,   5.0), Lerp(q1, q2, 0.50));
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion(  5.0, -12.5, -17.5,  22.5), Lerp(q1, q2, 0.75));
		BKSGE_CONSTEXPR_EXPECT_EQ(Quaternion( 10.0, -20.0, -30.0,  40.0), Lerp(q1, q2, 1.00));
	}
}

template <typename Quaternion, typename T>
void SlerpTest(Quaternion const& q1, Quaternion const& q2, T t, Quaternion const& expected, double error)
{
	EXPECT_EQ(q1, Slerp(q1, q2, T(-1.0)));
	EXPECT_EQ(q1, Slerp(q1, q2, T(-0.1)));
	EXPECT_EQ(q1, Slerp(q1, q2, T( 0.0)));
	EXPECT_EQ(q2, Slerp(q1, q2, T( 1.0)));
	EXPECT_EQ(q2, Slerp(q1, q2, T( 1.1)));
	EXPECT_EQ(q2, Slerp(q1, q2, T( 2.0)));

	const auto q = Slerp(q1, q2, t);
	static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
	EXPECT_NEAR((double)expected[0], (double)q[0], error);
	EXPECT_NEAR((double)expected[1], (double)q[1], error);
	EXPECT_NEAR((double)expected[2], (double)q[2], error);
	EXPECT_NEAR((double)expected[3], (double)q[3], error);
}

TYPED_TEST(MathQuaternionFloatTest, SlerpTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.000001;
	
	{
		const auto q1 = Quaternion::MakeRotationX(bksge::degrees_to_radians(  0));
		const auto q2 = Quaternion::MakeRotationX(bksge::degrees_to_radians(180));
		SlerpTest(q1, q2, TypeParam( 0.25), Quaternion::MakeRotationX(bksge::degrees_to_radians( 45)), error);
		SlerpTest(q1, q2, TypeParam( 0.50), Quaternion::MakeRotationX(bksge::degrees_to_radians( 90)), error);
		SlerpTest(q1, q2, TypeParam( 0.75), Quaternion::MakeRotationX(bksge::degrees_to_radians(135)), error);
	}
	{
		const auto q1 = Quaternion::MakeRotationY(bksge::degrees_to_radians(  0));
		const auto q2 = Quaternion::MakeRotationY(bksge::degrees_to_radians(  1));
		SlerpTest(q1, q2, TypeParam( 0.25), Quaternion::MakeRotationY(bksge::degrees_to_radians( 0.25)), error);
		SlerpTest(q1, q2, TypeParam( 0.50), Quaternion::MakeRotationY(bksge::degrees_to_radians( 0.50)), error);
		SlerpTest(q1, q2, TypeParam( 0.75), Quaternion::MakeRotationY(bksge::degrees_to_radians( 0.75)), error);
	}
	{
		const auto q1 = Quaternion::MakeRotationZ(bksge::degrees_to_radians( 30));
		const auto q2 = Quaternion::MakeRotationZ(bksge::degrees_to_radians(210));
		SlerpTest(q1, q2, TypeParam( 0.25), Quaternion::MakeRotationZ(bksge::degrees_to_radians( 75)), error);
		SlerpTest(q1, q2, TypeParam( 0.50), Quaternion::MakeRotationZ(bksge::degrees_to_radians(120)), error);
		SlerpTest(q1, q2, TypeParam( 0.75), Quaternion::MakeRotationZ(bksge::degrees_to_radians(165)), error);
	}
	{
		const auto q1 = Quaternion::MakeRotationX(bksge::degrees_to_radians(180));
		const auto q2 = Quaternion::MakeRotationX(bksge::degrees_to_radians( 90));
		SlerpTest(q1, q2, TypeParam( 0.25), Quaternion::MakeRotationX(bksge::degrees_to_radians(157.5)), error);
		SlerpTest(q1, q2, TypeParam( 0.50), Quaternion::MakeRotationX(bksge::degrees_to_radians(135.0)), error);
		SlerpTest(q1, q2, TypeParam( 0.75), Quaternion::MakeRotationX(bksge::degrees_to_radians(112.5)), error);
	}
}

TYPED_TEST(MathQuaternionFloatTest, MakeRotationXTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.0000001;

	{
		const auto q = Quaternion::MakeRotationX(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_EQ(Quaternion::Identity(), q);
	}
	{
		const auto q = Quaternion::MakeRotationX(bksge::degrees_to_radians(30));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.25881904510, (double)q[0], error);
		EXPECT_NEAR( 0.00000000000, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR( 0.96592582628, (double)q[3], error);
	}
	{
		const auto q = Quaternion::MakeRotationX(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.70710678118, (double)q[0], error);
		EXPECT_NEAR( 0.00000000000, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR( 0.70710678118, (double)q[3], error);
	}
	{
		const auto q = Quaternion::MakeRotationX(bksge::degrees_to_radians(180));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 1.00000000000, (double)q[0], error);
		EXPECT_NEAR( 0.00000000000, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR( 0.00000000000, (double)q[3], error);
	}
	{
		const auto q = Quaternion::MakeRotationX(bksge::degrees_to_radians(270));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.70710678118, (double)q[0], error);
		EXPECT_NEAR( 0.00000000000, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR(-0.70710678118, (double)q[3], error);
	}
}

TYPED_TEST(MathQuaternionFloatTest, MakeRotationYTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.0000001;

	{
		const auto q = Quaternion::MakeRotationY(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_EQ(Quaternion::Identity(), q);
	}
	{
		const auto q = Quaternion::MakeRotationY(bksge::degrees_to_radians(45));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		EXPECT_NEAR( 0.38268343236, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR( 0.92387953251, (double)q[3], error);
	}
	{
		const auto q = Quaternion::MakeRotationY(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		EXPECT_NEAR( 0.70710678118, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR( 0.70710678118, (double)q[3], error);
	}
}

TYPED_TEST(MathQuaternionFloatTest, MakeRotationZTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.0000001;

	{
		const auto q = Quaternion::MakeRotationZ(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_EQ(Quaternion::Identity(), q);
	}
	{
		const auto q = Quaternion::MakeRotationZ(bksge::degrees_to_radians(60));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		EXPECT_NEAR( 0.00000000000, (double)q[1], error);
		EXPECT_NEAR( 0.50000000000, (double)q[2], error);
		EXPECT_NEAR( 0.86602540378, (double)q[3], error);
	}
	{
		const auto q = Quaternion::MakeRotationZ(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		EXPECT_NEAR( 0.00000000000, (double)q[1], error);
		EXPECT_NEAR( 0.70710678118, (double)q[2], error);
		EXPECT_NEAR( 0.70710678118, (double)q[3], error);
	}
}

TYPED_TEST(MathQuaternionFloatTest, MakeRotationTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;
	using Vector3 = bksge::math::Vector3<T>;

	const double error = 0.0000001;

	{
		const auto q = Quaternion::MakeRotation(Vector3(1, 0, 0), bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_EQ(Quaternion::Identity(), q);
	}
	{
		const auto q = Quaternion::MakeRotation(Vector3(1, 0, 0), bksge::degrees_to_radians(60));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.50000000000, (double)q[0], error);
		EXPECT_NEAR( 0.00000000000, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR( 0.86602540378, (double)q[3], error);
	}
	{
		const auto q = Quaternion::MakeRotation(Vector3(0, 2, 0), bksge::degrees_to_radians(60));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		EXPECT_NEAR( 0.50000000000, (double)q[1], error);
		EXPECT_NEAR( 0.00000000000, (double)q[2], error);
		EXPECT_NEAR( 0.86602540378, (double)q[3], error);
	}
	{
		const auto q = Quaternion::MakeRotation(Vector3(0, 0, -3), bksge::degrees_to_radians(60));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.00000000000, (double)q[0], error);
		EXPECT_NEAR( 0.00000000000, (double)q[1], error);
		EXPECT_NEAR(-0.50000000000, (double)q[2], error);
		EXPECT_NEAR( 0.86602540378, (double)q[3], error);
	}
	{
		const auto q = Quaternion::MakeRotation(Vector3(3, -4, 5), bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.30000000000, (double)q[0], error);
		EXPECT_NEAR(-0.40000000000, (double)q[1], error);
		EXPECT_NEAR( 0.50000000000, (double)q[2], error);
		EXPECT_NEAR( 0.70710678118, (double)q[3], error);
	}
}

TYPED_TEST(MathQuaternionFloatTest, MakeLookAtTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;
	using Vector3 = bksge::math::Vector3<T>;

	const double error = 0.000001;

	{
		const auto q = Quaternion::MakeLookAt(
			Vector3{10, 10, 10},
			Vector3{30, 10, 10},
			Vector3{ 0,  1,  0});
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR( 0.000000, (double)q.x(), error);
		EXPECT_NEAR(-0.707107, (double)q.y(), error);
		EXPECT_NEAR( 0.000000, (double)q.z(), error);
		EXPECT_NEAR( 0.707107, (double)q.w(), error);
	}
	{
		const auto q = Quaternion::MakeLookAt(
			Vector3{10, 10, 10},
			Vector3{10,  0, 10},
			Vector3{ 0,  1,  0});
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR(-0.707107, (double)q.x(), error);
		EXPECT_NEAR( 0.000000, (double)q.y(), error);
		EXPECT_NEAR( 0.000000, (double)q.z(), error);
		EXPECT_NEAR( 0.707107, (double)q.w(), error);
	}
	{
		const auto q = Quaternion::MakeLookAt(
			Vector3{10, 10, 10},
			Vector3{ 0,  0,  0},
			Vector3{ 0,  1,  0});
		static_assert(bksge::is_same<decltype(q), const Quaternion>::value, "");
		EXPECT_NEAR(-0.279848, (double)q.x(), error);
		EXPECT_NEAR( 0.364705, (double)q.y(), error);
		EXPECT_NEAR( 0.115917, (double)q.z(), error);
		EXPECT_NEAR( 0.880476, (double)q.w(), error);
	}
}

TYPED_TEST(MathQuaternionTest, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::Quaternion<T> const v { 1, 2, 3, 4 };

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

TYPED_TEST(MathQuaternionTest, HashTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	std::hash<Quaternion> h;

	Quaternion const c1(1, 2, 3, 4);
	Quaternion const c2(2, 2, 3, 4);
	Quaternion const c3(1, 0, 3, 4);
	Quaternion const c4(1, 2, 2, 4);
	Quaternion const c5(1, 2, 3, 0);

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

}	// namespace quaternion_test

}	// namespace bksge_math_test
