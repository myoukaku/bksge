/**
 *	@file	unit_test_core_math_quaternion.cpp
 *
 *	@brief	Quaternion のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/quaternion.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/vector3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/matrix3x3.hpp>
#include <bksge/fnd/cmath/degrees_to_radians.hpp>
#include <bksge/fnd/concepts/floating_point.hpp>
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

namespace quaternion_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Quaternionf = bksge::math::Quaternion<float>;
using Quaternioni = bksge::math::Quaternion<int>;


using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathQuaternionTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathQuaternionTest, MathTestTypes);

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
		BKSGE_CONSTEXPR_OR_CONST Quaternion v = {};
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
		BKSGE_CONSTEXPR_EXPECT_EQ( 9, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(11, v[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(12, v[3]);
	}
}

TYPED_TEST(MathQuaternionTest, Vector3ConstructTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;
	using Vector3 = bksge::math::Vector3<T>;

	static_assert(!bksge::is_constructible<Quaternion, Vector3, T, T>::value, "");
	static_assert( bksge::is_constructible<Quaternion, Vector3, T>::value, "");
	static_assert(!bksge::is_constructible<Quaternion, Vector3>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Quaternion, Vector3, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Quaternion, Vector3, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Quaternion, Vector3>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Quaternion, Vector3, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Quaternion, Vector3, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Quaternion, Vector3>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v1(1, 2, 3);
		BKSGE_CONSTEXPR_OR_CONST Quaternion v2(v1, 4);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v1(2, 3, 4);
		BKSGE_CONSTEXPR_OR_CONST Quaternion v2{v1, 5};
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v2[3]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Vector3 v1(3, 4, 5);
		BKSGE_CONSTEXPR_OR_CONST Quaternion v2 = {v1, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v2[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v2[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v2[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v2[3]);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool Matrix3x3ConstructTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	using Matrix3x3 = bksge::math::Matrix3x3<T>;

	const double error = 0.0000001;

	{
		const auto m = Matrix3x3::Identity();
		const Quaternion q(m);
		VERIFY(Quaternion::Identity() == q);
	}
	{
		const auto angle = bksge::degrees_to_radians(30);
		const auto m = Matrix3x3::MakeRotationX(angle);
		const Quaternion q(m);
		const auto expected = Quaternion::MakeRotationX(angle);
		VERIFY(IsNear(expected, q, error));
	}
	{
		const auto angle = bksge::degrees_to_radians(45);
		const auto m = Matrix3x3::MakeRotationY(angle);
		const Quaternion q(m);
		const auto expected = Quaternion::MakeRotationY(angle);
		VERIFY(IsNear(expected, q, error));
	}
	{
		const auto angle = bksge::degrees_to_radians(90);
		const auto m = Matrix3x3::MakeRotationZ(angle);
		const Quaternion q(m);
		const auto expected = Quaternion::MakeRotationZ(angle);
		VERIFY(IsNear(expected, q, error));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, Matrix3x3ConstructTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(Matrix3x3ConstructTest<TypeParam>());
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

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	Quaternion v{0, 1, 2, 3};
	VERIFY(v[0] == 0);
	VERIFY(v[1] == 1);
	VERIFY(v[2] == 2);
	VERIFY(v[3] == 3);

	v = Quaternion(-2, 3, -4, 5);
	VERIFY(v[0] == -2);
	VERIFY(v[1] ==  3);
	VERIFY(v[2] == -4);
	VERIFY(v[3] ==  5);

	v = Quaternioni(3, -4, 5, -6);
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
	Quaternion v2;
	v2 = v = Quaternionf(4, 5, 6, 7);
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

TYPED_TEST(MathQuaternionTest, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	{
		Quaternion v{1, 2, 3, 4};
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
		Quaternion const v{5, 6, 7, 8};
		VERIFY(v[0] == 5);
		VERIFY(v[1] == 6);
		VERIFY(v[2] == 7);
		VERIFY(v[3] == 8);
	}
	return true;
}

TYPED_TEST(MathQuaternionTest, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	{
		Quaternion v{1, 2, 3, 4};
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
		Quaternion const v{5, 6, 7, 8};
		VERIFY(v.at(0) == 5);
		VERIFY(v.at(1) == 6);
		VERIFY(v.at(2) == 7);
		VERIFY(v.at(3) == 8);
	}
	return true;
}

TYPED_TEST(MathQuaternionTest, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Quaternion = bksge::math::Quaternion<TypeParam>;
	{
		Quaternion v{1, 2, 3, 4};
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
	{
		Quaternion const v{5, 6, 7, 8};
		EXPECT_THROW((void)v.at(4), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	{
		Quaternion v{1, 2, 3, 4};
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

		VERIFY(v == Quaternion(5, 2, 6, 4));
	}
	{
		Quaternion const v{1, 2, 3, 4};
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

TYPED_TEST(MathQuaternionTest, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	// begin, end (non const)
	{
		Quaternion v{1, 2, 3, 4};
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

		VERIFY(Quaternion(5, 2, 6, 4) == v);
	}
	// begin, end (const)
	{
		Quaternion const v{1, 2, 3, 4};
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
		Quaternion v{1, 2, 3, 4};
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

TYPED_TEST(MathQuaternionTest, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	// rbegin, rend (non const)
	{
		Quaternion v{1, 2, 3, 4};
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

		VERIFY(Quaternion(1, 6, 3, 5) == v);
	}
	// rbegin, rend (const)
	{
		Quaternion const v{1, 2, 3, 4};
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
		Quaternion v{1, 2, 3, 4};
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

TYPED_TEST(MathQuaternionTest, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	Quaternion v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathQuaternionTest, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	Quaternion v1{};
	VERIFY(v1.size() == 4);
	return true;
}

TYPED_TEST(MathQuaternionTest, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	Quaternion v1{};
	VERIFY(v1.max_size() == 4);
	return true;
}

TYPED_TEST(MathQuaternionTest, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	{
		Quaternion v{1, 2, 3, 4};
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
		Quaternion const v{5, 6, 7, 8};
		VERIFY(v.x() == 5);
		VERIFY(v.y() == 6);
		VERIFY(v.z() == 7);
		VERIFY(v.w() == 8);
	}
	return true;
}

TYPED_TEST(MathQuaternionTest, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	Quaternion v(1, 2, 3, 4);

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

TYPED_TEST(MathQuaternionTest, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	Quaternion v1{1, 2, 3, 4};
	Quaternion v2{5, 6, 7, 8};

	v1.swap(v2);

	VERIFY(v1 == Quaternion(5, 6, 7, 8));
	VERIFY(v2 == Quaternion(1, 2, 3, 4));

	bksge::ranges::swap(v1, v2);

	VERIFY(v1 == Quaternion(1, 2, 3, 4));
	VERIFY(v2 == Quaternion(5, 6, 7, 8));

	return true;
}

TYPED_TEST(MathQuaternionTest, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	{
		Quaternion const v1(-1, 2, -3, 4);
		auto const v2 = +v1;
		auto const v3 = -v1;
		static_assert(bksge::is_same<decltype(v2), Quaternion const>::value, "");
		static_assert(bksge::is_same<decltype(v3), Quaternion const>::value, "");

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

TYPED_TEST(MathQuaternionTest, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	// Quaternion += Quaternion
	{
		Quaternion v;
		VERIFY(v == Quaternion(0, 0, 0, 0));

		auto t = (v += Quaternion(2, 3, -4, 5));
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(v == Quaternion(2, 3, -4, 5));
		VERIFY(v == t);
	}
	// Quaternion + Quaternion -> Quaternion
	{
		auto t = Quaternion(-3, 4, 5, 6) + Quaternion(0, 2, -1, 3);
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(t == Quaternion(-3, 6, 4, 9));
	}
	return true;
}

TYPED_TEST(MathQuaternionTest, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	// Quaternion -= Quaternion
	{
		Quaternion v;
		VERIFY(v == Quaternion(0, 0, 0, 0));

		auto t = (v -= Quaternion(2, 3, -4, 5));
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(v == Quaternion(-2, -3, 4, -5));
		VERIFY(v == t);
	}
	// Quaternion - Quaternion -> Quaternion
	{
		auto t = Quaternion(-3, 4, 5, 6) - Quaternion(0, 2, -1, 3);
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(t == Quaternion(-3, 2, 6, 3));
	}
	return true;
}

TYPED_TEST(MathQuaternionTest, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	// Quaternion *= スカラー
	{
		Quaternion v(2, 3, 4, 5);
		{
			auto t = (v *= 4);
			static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
			VERIFY(v == Quaternion(8, 12, 16, 20));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
			VERIFY(v == Quaternion(4, 6, 8, 10));
			VERIFY(t == v);
		}
	}
	// Quaternion * スカラー -> Quaternion
	{
		auto t = Quaternion(-3, 42, 5, 4) * -4;
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(t == Quaternion(12, -168, -20, -16));
	}
	{
		auto t = Quaternion(4, 6, 2, -10) * 2.5;
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(t == Quaternion(10, 15, 5, -25));
	}
	// スカラー * Quaternion -> Quaternion
	{
		auto t = 5 * Quaternion(7, -8, 9, 2);
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(t == Quaternion(35, -40, 45, 10));
	}
	{
		auto t = -1.5 * Quaternion(4, -6, -2, 8);
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(t == Quaternion(-6, 9, 3, -12));
	}
	return true;
}

TYPED_TEST(MathQuaternionTest, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulQuaternionTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	// Quaternion *= Quaternion
	{
		Quaternion q(2, 3, 4, 5);
		auto t = (q *= Quaternion(3, 4, 5, 6));
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(Quaternion(26, 40, 48, -8) == q);
		VERIFY(t == q);
	}

	// Quaternion * Quaternion -> Quaternion
	{
		auto t = Quaternion(1, 2, 3, 4) * Quaternion(5, -6, 7, 8);
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(Quaternion(60, 0, 36, 18) == t);
	}
	{
		auto t = Quaternion(1, 2, 3, 4) * Quaternion(5, 6, -7, 8) * Quaternion(9, 10, 11, -12);
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(Quaternion(1134, -412, -106, -928) == t);
	}

	// Identity * Identity = Identity
	{
		auto t = Quaternion::Identity() * Quaternion::Identity();
		VERIFY(Quaternion::Identity() == t);
	}

	// ii = jj = kk = ijk = -1
	{
		auto t = Quaternion(1, 0, 0, 0) * Quaternion(1, 0, 0, 0);
		VERIFY(Quaternion(0, 0, 0, -1) == t);
	}
	{
		auto t = Quaternion(0, 1, 0, 0) * Quaternion(0, 1, 0, 0);
		VERIFY(Quaternion(0, 0, 0, -1) == t);
	}
	{
		auto t = Quaternion(0, 0, 1, 0) * Quaternion(0, 0, 1, 0);
		VERIFY(Quaternion(0, 0, 0, -1) == t);
	}
	{
		auto t = Quaternion(1, 0, 0, 0) * Quaternion(0, 1, 0, 0) * Quaternion(0, 0, 1, 0);
		VERIFY(Quaternion(0, 0, 0, -1) == t);
	}

	// ij = -ji = k
	{
		auto t = Quaternion(1, 0, 0, 0) * Quaternion(0, 1, 0, 0);
		VERIFY(Quaternion(0, 0, 1, 0) == t);
	}
	{
		auto t = Quaternion(0, -1, 0, 0) * Quaternion(1, 0, 0, 0);
		VERIFY(Quaternion(0, 0, 1, 0) == t);
	}

	// jk = -kj = i
	{
		auto t = Quaternion(0, 1, 0, 0) * Quaternion(0, 0, 1, 0);
		VERIFY(Quaternion(1, 0, 0, 0) == t);
	}
	{
		auto t = Quaternion(0, 0, -1, 0) * Quaternion(0, 1, 0, 0);
		VERIFY(Quaternion(1, 0, 0, 0) == t);
	}

	// ki = -ik = j
	{
		auto t = Quaternion(0, 0, 1, 0) * Quaternion(1, 0, 0, 0);
		VERIFY(Quaternion(0, 1, 0, 0) == t);
	}
	{
		auto t = Quaternion(-1, 0, 0, 0) * Quaternion(0, 0, 1, 0);
		VERIFY(Quaternion(0, 1, 0, 0) == t);
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, MulQuaternionTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulQuaternionTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulVector3Test1()
{
	using Quaternion = bksge::math::Quaternion<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Vector3 *= Quaternion
	{
		Vector3 v1 { 1, 2, 3 };
		auto t = (v1 *= Quaternion::Identity());
		static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
		VERIFY(v1 == Vector3{ 1, 2, 3 });
		VERIFY(v1 == t);
	}

	// Vector3 * Quaternion -> Vector3
	{
		Vector3 const v1 { 1, 2, 3 };
		auto v2 = v1 * Quaternion::Identity();
		static_assert(bksge::is_same<decltype(v2), Vector3>::value, "");
		VERIFY(v1 == v2);
	}

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulVector3Test2()
{
	using Quaternion = bksge::math::Quaternion<T>;
	using Vector3 = bksge::math::Vector3<T>;

	// Vector3 *= Quaternion
	{
		Vector3 v { 1, 2, 3 };
		{
			auto t = (v *= Quaternion::MakeRotationX(bksge::degrees_to_radians(90)));
			static_assert(bksge::is_same<decltype(t), Vector3>::value, "");
			double error = 0.000001;
			VERIFY(IsNear(Vector3{ 1,-3, 2}, v, error));
			VERIFY(t == v);
		}
		{
			auto t = (v *= Quaternion::MakeRotationY(bksge::degrees_to_radians(90)));
			double error = 0.000001;
			VERIFY(IsNear(Vector3{ 2,-3,-1}, v, error));
			VERIFY(t == v);
		}
		{
			auto t = (v *= Quaternion::MakeRotationZ(bksge::degrees_to_radians(90)));
			double error = 0.000001;
			VERIFY(IsNear(Vector3{ 3, 2,-1}, v, error));
			VERIFY(t == v);
		}
	}

	// Vector3 * Quaternion -> Vector3
	{
		auto q1 = Quaternion::MakeRotationX(bksge::degrees_to_radians(90));
		auto q2 = Quaternion::MakeRotationY(bksge::degrees_to_radians(90));
		auto q3 = Quaternion::MakeRotationZ(bksge::degrees_to_radians(90));

		Vector3 xaxis(1, 0, 0);
		Vector3 yaxis(0, 1, 0);
		Vector3 zaxis(0, 0, 1);
		auto v1 = xaxis * q1;
		auto v2 = xaxis * q2;
		auto v3 = xaxis * q3;
		auto v4 = yaxis * q1;
		auto v5 = yaxis * q2;
		auto v6 = yaxis * q3;
		auto v7 = zaxis * q1;
		auto v8 = zaxis * q2;
		auto v9 = zaxis * q3;

		double error = 0.0000001;
		VERIFY(IsNear(Vector3{ 1, 0, 0}, v1, error));
		VERIFY(IsNear(Vector3{ 0, 0,-1}, v2, error));
		VERIFY(IsNear(Vector3{ 0, 1, 0}, v3, error));
		VERIFY(IsNear(Vector3{ 0, 0, 1}, v4, error));
		VERIFY(IsNear(Vector3{ 0, 1, 0}, v5, error));
		VERIFY(IsNear(Vector3{-1, 0, 0}, v6, error));
		VERIFY(IsNear(Vector3{ 0,-1, 0}, v7, error));
		VERIFY(IsNear(Vector3{ 1, 0, 0}, v8, error));
		VERIFY(IsNear(Vector3{ 0, 0, 1}, v9, error));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, MulVector3Test)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulVector3Test1<TypeParam>());
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulVector3Test2<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	// Quaternion /= スカラー
	{
		Quaternion v(2, 4, 6, 8);
		{
			auto t = (v /= 2);
			static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
			VERIFY(v == Quaternion(1, 2, 3, 4));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
			VERIFY(v == Quaternion(2, 4, 6, 8));
			VERIFY(t == v);
		}
	}
	// Quaternion / スカラー -> Quaternion
	{
		auto t = Quaternion(-4, 8, -12, 16) / -4;
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(t == Quaternion(1, -2, 3, -4));
	}
	{
		auto t = Quaternion(-4, 8, -12, 16) / 0.25;
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(t == Quaternion(-16, 32, -48, 64));
	}
	return true;
}

TYPED_TEST(MathQuaternionTest, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	Quaternion const v1(1, 2, 3, 4);
	Quaternion const v2(1, 2, 3, 4);
	Quaternion const v3(2, 2, 3, 4);
	Quaternion const v4(1, 0, 3, 4);
	Quaternion const v5(1, 2, 2, 4);
	Quaternion const v6(1, 2, 3, 5);

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

TYPED_TEST(MathQuaternionTest, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool RealTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	VERIFY( 0 == Quaternion( 0, 0, 0, 0).real());
	VERIFY( 4 == Quaternion( 1, 2, 3, 4).real());
	VERIFY( 4 == Quaternion(-1, 2, 3, 4).real());
	VERIFY( 4 == Quaternion( 1,-2, 3, 4).real());
	VERIFY( 4 == Quaternion( 1, 2,-3, 4).real());
	VERIFY(-4 == Quaternion( 1, 2, 3,-4).real());
	VERIFY( 8 == Quaternion( 5, 6, 7, 8).real());

	return true;
}

TYPED_TEST(MathQuaternionTest, RealTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(RealTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ImagTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	using Vector3 = bksge::math::Vector3<T>;

	VERIFY(Vector3( 0, 0, 0) == Quaternion( 0, 0, 0, 0).imag());
	VERIFY(Vector3( 1, 2, 3) == Quaternion( 1, 2, 3, 4).imag());
	VERIFY(Vector3(-1, 2, 3) == Quaternion(-1, 2, 3, 4).imag());
	VERIFY(Vector3( 1,-2, 3) == Quaternion( 1,-2, 3, 4).imag());
	VERIFY(Vector3( 1, 2,-3) == Quaternion( 1, 2,-3, 4).imag());
	VERIFY(Vector3( 1, 2, 3) == Quaternion( 1, 2, 3,-4).imag());
	VERIFY(Vector3( 5, 6, 7) == Quaternion( 5, 6, 7, 8).imag());

	return true;
}

TYPED_TEST(MathQuaternionTest, ImagTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ImagTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	{
		auto q = Quaternion::Zero();
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(Quaternion(0, 0, 0, 0) == q);
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IdentityTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	{
		auto q = Quaternion::Identity();
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(Quaternion(0, 0, 0, 1) == q);
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, IdentityTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IdentityTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ConjugateTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	Quaternion q1(1, 2, 3, 4);
	auto q2 = Conjugate(q1);
	auto q3 = Conjugate(q2);
	static_assert(bksge::is_same<decltype(q2), Quaternion>::value, "");
	static_assert(bksge::is_same<decltype(q3), Quaternion>::value, "");

	VERIFY(q1 == q3);
	VERIFY(Quaternion( 1,  2,  3, 4) == q1);
	VERIFY(Quaternion(-1, -2, -3, 4) == q2);
	VERIFY(Quaternion( 1,  2,  3, 4) == q3);

	{
		// 四元数 q = ix + jy + kz + w の共役をq'としたとき、
		// q * q' = q' * q = x^2 + y^2 + z^2 + w^2
		// となる。
		Quaternion expected{ 0, 0, 0, 1*1 + 2*2 + 3*3 + 4*4 };
		VERIFY(expected == q1 * q2);
		VERIFY(expected == q2 * q1);
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, ConjugateTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ConjugateTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool InversedTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	{
		Quaternion q1(1, 2, 3, 4);
		auto q1_inv = Inversed(q1);
		static_assert(bksge::is_same<decltype(q1_inv), Quaternion>::value, "");

		Quaternion expected{
			T(-0.03333333333333333),
			T(-0.06666666666666666),
			T(-0.10000000000000000),
			T( 0.13333333333333333),
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, q1_inv, error));

		// あるクォータニオンとその逆クォータニオンをかけると単位クォータニオンになる
		auto q2 = q1 * q1_inv;
		VERIFY(IsNear(Quaternion::Identity(), q2, error));
	}
	{
		Quaternion q1(9, 41, -5, 6);
		auto q1_inv = Inversed(q1);
		static_assert(bksge::is_same<decltype(q1_inv), Quaternion>::value, "");

		Quaternion expected{
			T(-0.00493691716950082),
			T(-0.02249040043883708),
			T( 0.00274273176083379),
			T( 0.00329127811300054),
		};
		double error = 0.000001;
		VERIFY(IsNear(expected, q1_inv, error));

		// あるクォータニオンとその逆クォータニオンをかけると単位クォータニオンになる
		const auto q2 = q1 * q1_inv;
		VERIFY(IsNear(Quaternion::Identity(), q2, error));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, InversedTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(InversedTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NormalizedTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	{
		auto t = Normalized(Quaternion(0,  0,  0, 0));
		static_assert(bksge::is_same<decltype(t), Quaternion>::value, "");
		VERIFY(Quaternion( 0, 0, 0, 1) == t);
	}
	VERIFY(Quaternion( 1, 0, 0, 0) == Normalized(Quaternion(  1,  0,  0, 0)));
	VERIFY(Quaternion(-1, 0, 0, 0) == Normalized(Quaternion( -1,  0,  0, 0)));
	VERIFY(Quaternion( 1, 0, 0, 0) == Normalized(Quaternion( 10,  0,  0, 0)));
	VERIFY(Quaternion(-1, 0, 0, 0) == Normalized(Quaternion(-10,  0,  0, 0)));
	VERIFY(Quaternion( 0, 1, 0, 0) == Normalized(Quaternion(  0,  1,  0, 0)));
	VERIFY(Quaternion( 0,-1, 0, 0) == Normalized(Quaternion(  0, -1,  0, 0)));
	VERIFY(Quaternion( 0, 1, 0, 0) == Normalized(Quaternion(  0,  5,  0, 0)));
	VERIFY(Quaternion( 0,-1, 0, 0) == Normalized(Quaternion(  0, -5,  0, 0)));
	VERIFY(Quaternion( 0, 0, 1, 0) == Normalized(Quaternion(  0,  0,  1, 0)));
	VERIFY(Quaternion( 0, 0,-1, 0) == Normalized(Quaternion(  0,  0, -1, 0)));
	VERIFY(Quaternion( 0, 0, 1, 0) == Normalized(Quaternion(  0,  0, 42, 0)));
	VERIFY(Quaternion( 0, 0,-1, 0) == Normalized(Quaternion(  0,  0,-42, 0)));
	VERIFY(Quaternion( 0, 0, 0, 1) == Normalized(Quaternion(  0,  0,  0, 3)));
	VERIFY(Quaternion( 0, 0, 0,-1) == Normalized(Quaternion(  0,  0,  0,-3)));
	{
		auto t = Normalized(Quaternion(1, 2, 3, 4));
		double error = 0.000001;
		Quaternion expected{
			T(0.18257418583),
			T(0.36514837167),
			T(0.54772255750),
			T(0.73029674334),
		};
		VERIFY(IsNear(expected, t, error));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, NormalizedTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(NormalizedTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DotTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	VERIFY( 0 == Dot(Quaternion( 0, 0, 0, 0), Quaternion( 0, 0, 0, 0)));
	VERIFY( 1 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 1, 0, 0, 0)));
	VERIFY(-2 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 1, 0, 0)));
	VERIFY( 3 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0, 1, 0)));
	VERIFY(-4 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0, 0, 1)));
	VERIFY(-1 == Dot(Quaternion( 1,-2, 3,-4), Quaternion(-1, 0, 0, 0)));
	VERIFY( 2 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0,-1, 0, 0)));
	VERIFY(-3 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0,-1, 0)));
	VERIFY( 4 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0, 0,-1)));
	VERIFY( 2 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 2, 0, 0, 0)));
	VERIFY(-4 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 2, 0, 0)));
	VERIFY( 6 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0, 2, 0)));
	VERIFY(-8 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 0, 0, 0, 2)));
	VERIFY(-2 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 1, 1, 1, 1)));
	VERIFY(10 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 1,-1, 1,-1)));
	VERIFY(30 == Dot(Quaternion( 1,-2, 3,-4), Quaternion( 1,-2, 3,-4)));

	return true;
}

TYPED_TEST(MathQuaternionTest, DotTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DotTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SquaredLengthTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	VERIFY(  0 == SquaredLength(Quaternion(0, 0, 0, 0)));
	VERIFY(  9 == SquaredLength(Quaternion(3, 0, 0, 0)));
	VERIFY( 16 == SquaredLength(Quaternion(0, 4, 0, 0)));
	VERIFY( 25 == SquaredLength(Quaternion(0, 0,-5, 0)));
	VERIFY( 36 == SquaredLength(Quaternion(0, 0, 0, 6)));
	VERIFY( 30 == SquaredLength(Quaternion(1, 2, 3, 4)));
	VERIFY( 30 == SquaredLength(Quaternion(1,-2, 3, 4)));
	VERIFY( 30 == SquaredLength(Quaternion(1, 2, 3,-4)));
	VERIFY(109 == SquaredLength(Quaternion(4,-8, 5, 2)));

	return true;
}

TYPED_TEST(MathQuaternionTest, SquaredLengthTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SquaredLengthTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool LengthTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	VERIFY(0 == Length(Quaternion( 0, 0, 0, 0)));
	VERIFY(3 == Length(Quaternion( 3, 0, 0, 0)));
	VERIFY(3 == Length(Quaternion(-3, 0, 0, 0)));
	VERIFY(4 == Length(Quaternion( 0, 4, 0, 0)));
	VERIFY(4 == Length(Quaternion( 0,-4, 0, 0)));
	VERIFY(5 == Length(Quaternion( 0, 0, 5, 0)));
	VERIFY(5 == Length(Quaternion( 0, 0,-5, 0)));
	VERIFY(6 == Length(Quaternion( 0, 0, 0, 6)));
	VERIFY(6 == Length(Quaternion( 0, 0, 0,-6)));

	const double error = 0.000001;
	VERIFY(IsNear(5.47722557505, (double)Length(Quaternion(1, 2, 3, 4)), error));
	VERIFY(IsNear(5.47722557505, (double)Length(Quaternion(1,-2,-3, 4)), error));
	VERIFY(IsNear(10.4403065089, (double)Length(Quaternion(4,-8, 5, 2)), error));

	return true;
}

TYPED_TEST(MathQuaternionTest, LengthTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(LengthTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NormTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	VERIFY(0 == Norm(Quaternion( 0, 0, 0, 0)));
	VERIFY(3 == Norm(Quaternion( 3, 0, 0, 0)));
	VERIFY(3 == Norm(Quaternion(-3, 0, 0, 0)));
	VERIFY(4 == Norm(Quaternion( 0, 4, 0, 0)));
	VERIFY(4 == Norm(Quaternion( 0,-4, 0, 0)));
	VERIFY(5 == Norm(Quaternion( 0, 0, 5, 0)));
	VERIFY(5 == Norm(Quaternion( 0, 0,-5, 0)));
	VERIFY(6 == Norm(Quaternion( 0, 0, 0, 6)));
	VERIFY(6 == Norm(Quaternion( 0, 0, 0,-6)));

	const double error = 0.000001;
	VERIFY(IsNear(5.47722557505, (double)Norm(Quaternion(1, 2, 3, 4)), error));
	VERIFY(IsNear(5.47722557505, (double)Norm(Quaternion(1,-2,-3, 4)), error));
	VERIFY(IsNear(10.4403065089, (double)Norm(Quaternion(4,-8, 5, 2)), error));

	return true;
}

TYPED_TEST(MathQuaternionTest, NormTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(NormTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool LerpTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	{
		Quaternion q1 {  0,  0,  0,  0 };
		Quaternion q2 { 10, 20, 30, 40 };

		VERIFY(Quaternion( 0.0,  0.0,  0.0,  0.0) == Lerp(q1, q2, 0.00f));
		VERIFY(Quaternion( 2.5,  5.0,  7.5, 10.0) == Lerp(q1, q2, 0.25f));
		VERIFY(Quaternion( 5.0, 10.0, 15.0, 20.0) == Lerp(q1, q2, 0.50f));
		VERIFY(Quaternion( 7.5, 15.0, 22.5, 30.0) == Lerp(q1, q2, 0.75f));
		VERIFY(Quaternion(10.0, 20.0, 30.0, 40.0) == Lerp(q1, q2, 1.00f));
	}
	{
		Quaternion q1 { -10,  10,  20, -30 };
		Quaternion q2 {  10, -20, -30,  40 };

		VERIFY(Quaternion(-10.0,  10.0,  20.0, -30.0) == Lerp(q1, q2, 0.00));
		VERIFY(Quaternion( -5.0,   2.5,   7.5, -12.5) == Lerp(q1, q2, 0.25));
		VERIFY(Quaternion(  0.0,  -5.0,  -5.0,   5.0) == Lerp(q1, q2, 0.50));
		VERIFY(Quaternion(  5.0, -12.5, -17.5,  22.5) == Lerp(q1, q2, 0.75));
		VERIFY(Quaternion( 10.0, -20.0, -30.0,  40.0) == Lerp(q1, q2, 1.00));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, LerpTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(LerpTest<TypeParam>());
}

template <typename Quaternion, typename T>
inline BKSGE_CXX14_CONSTEXPR bool
SlerpTest2(Quaternion const& q1, Quaternion const& q2, T t, Quaternion const& expected, double error)
{
	VERIFY(q1 == Slerp(q1, q2, T(-1.0)));
	VERIFY(q1 == Slerp(q1, q2, T(-0.1)));
	VERIFY(q1 == Slerp(q1, q2, T( 0.0)));
	VERIFY(q2 == Slerp(q1, q2, T( 1.0)));
	VERIFY(q2 == Slerp(q1, q2, T( 1.1)));
	VERIFY(q2 == Slerp(q1, q2, T( 2.0)));

	auto q = Slerp(q1, q2, t);
	static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
	VERIFY(IsNear(expected, q, error));

	return true;
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SlerpTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.000001;
	
	{
		const auto q1 = Quaternion::MakeRotationX(bksge::degrees_to_radians(  0));
		const auto q2 = Quaternion::MakeRotationX(bksge::degrees_to_radians(180));
		VERIFY(SlerpTest2(q1, q2, T( 0.25), Quaternion::MakeRotationX(bksge::degrees_to_radians( 45)), error));
		VERIFY(SlerpTest2(q1, q2, T( 0.50), Quaternion::MakeRotationX(bksge::degrees_to_radians( 90)), error));
		VERIFY(SlerpTest2(q1, q2, T( 0.75), Quaternion::MakeRotationX(bksge::degrees_to_radians(135)), error));
	}
	{
		const auto q1 = Quaternion::MakeRotationY(bksge::degrees_to_radians(  0));
		const auto q2 = Quaternion::MakeRotationY(bksge::degrees_to_radians(  1));
		VERIFY(SlerpTest2(q1, q2, T( 0.25), Quaternion::MakeRotationY(bksge::degrees_to_radians( 0.25)), error));
		VERIFY(SlerpTest2(q1, q2, T( 0.50), Quaternion::MakeRotationY(bksge::degrees_to_radians( 0.50)), error));
		VERIFY(SlerpTest2(q1, q2, T( 0.75), Quaternion::MakeRotationY(bksge::degrees_to_radians( 0.75)), error));
	}
	{
		const auto q1 = Quaternion::MakeRotationZ(bksge::degrees_to_radians( 30));
		const auto q2 = Quaternion::MakeRotationZ(bksge::degrees_to_radians(210));
		VERIFY(SlerpTest2(q1, q2, T( 0.25), Quaternion::MakeRotationZ(bksge::degrees_to_radians( 75)), error));
		VERIFY(SlerpTest2(q1, q2, T( 0.50), Quaternion::MakeRotationZ(bksge::degrees_to_radians(120)), error));
		VERIFY(SlerpTest2(q1, q2, T( 0.75), Quaternion::MakeRotationZ(bksge::degrees_to_radians(165)), error));
	}
	{
		const auto q1 = Quaternion::MakeRotationX(bksge::degrees_to_radians(180));
		const auto q2 = Quaternion::MakeRotationX(bksge::degrees_to_radians( 90));
		VERIFY(SlerpTest2(q1, q2, T( 0.25), Quaternion::MakeRotationX(bksge::degrees_to_radians(157.5)), error));
		VERIFY(SlerpTest2(q1, q2, T( 0.50), Quaternion::MakeRotationX(bksge::degrees_to_radians(135.0)), error));
		VERIFY(SlerpTest2(q1, q2, T( 0.75), Quaternion::MakeRotationX(bksge::degrees_to_radians(112.5)), error));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, SlerpTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(SlerpTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationXTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.0000001;

	{
		auto q = Quaternion::MakeRotationX(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(Quaternion::Identity() == q);
	}
	{
		auto q = Quaternion::MakeRotationX(bksge::degrees_to_radians(30));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{T(0.25881904510), 0, 0, T(0.96592582628)}, q, error));
	}
	{
		auto q = Quaternion::MakeRotationX(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{T(0.70710678118), 0, 0, T(0.70710678118)}, q, error));
	}
	{
		auto q = Quaternion::MakeRotationX(bksge::degrees_to_radians(180));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{1, 0, 0, 0}, q, error));
	}
	{
		auto q = Quaternion::MakeRotationX(bksge::degrees_to_radians(270));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{T(0.70710678118), 0, 0, T(-0.70710678118)}, q, error));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, MakeRotationXTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationXTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationYTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.0000001;

	{
		auto q = Quaternion::MakeRotationY(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(Quaternion::Identity() == q);
	}
	{
		auto q = Quaternion::MakeRotationY(bksge::degrees_to_radians(45));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{0, T(0.38268343236), 0, T(0.92387953251)}, q, error));
	}
	{
		auto q = Quaternion::MakeRotationY(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{0, T(0.70710678118), 0, T(0.70710678118)}, q, error));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, MakeRotationYTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationYTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationZTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.0000001;

	{
		auto q = Quaternion::MakeRotationZ(bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(Quaternion::Identity() == q);
	}
	{
		auto q = Quaternion::MakeRotationZ(bksge::degrees_to_radians(60));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{0, 0, T(0.5), T(0.86602540378)}, q, error));
	}
	{
		auto q = Quaternion::MakeRotationZ(bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{0, 0, T(0.70710678118), T(0.70710678118)}, q, error));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, MakeRotationZTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationZTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeRotationTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.0000001;

	{
		auto q = Quaternion::MakeRotation({1, 0, 0}, bksge::degrees_to_radians(0));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(Quaternion::Identity() == q);
	}
	{
		auto q = Quaternion::MakeRotation({1, 0, 0}, bksge::degrees_to_radians(60));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{T(0.5), 0, 0, T(0.86602540378)}, q, error));
	}
	{
		auto q = Quaternion::MakeRotation({0, 2, 0}, bksge::degrees_to_radians(60));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{0, T(0.5), 0, T(0.86602540378)}, q, error));
	}
	{
		auto q = Quaternion::MakeRotation({0, 0, -3}, bksge::degrees_to_radians(60));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{0, 0, T(-0.5), T(0.86602540378)}, q, error));
	}
	{
		auto q = Quaternion::MakeRotation({3, -4, 5}, bksge::degrees_to_radians(90));
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{T(0.3), T(-0.4), T(0.5), T(0.70710678118)}, q, error));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, MakeRotationTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeRotationTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MakeLookAtTest()
{
	using Quaternion = bksge::math::Quaternion<T>;

	const double error = 0.000001;

	{
		auto q = Quaternion::MakeLookAt(
			{10, 10, 10},
			{30, 10, 10},
			{ 0,  1,  0});
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{T(0), T(-0.707107), T(0), T(0.707107)}, q, error));
	}
	{
		auto q = Quaternion::MakeLookAt(
			{10, 10, 10},
			{10,  0, 10},
			{ 0,  1,  0});
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{T(-0.707107), T(0), T(0), T(0.707107)}, q, error));
	}
	{
		auto q = Quaternion::MakeLookAt(
			{10, 10, 10},
			{ 0,  0,  0},
			{ 0,  1,  0});
		static_assert(bksge::is_same<decltype(q), Quaternion>::value, "");
		VERIFY(IsNear(Quaternion{T(-0.279848), T(0.364705), T(0.115917), T(0.880476)}, q, error));
	}

	return true;
}

TYPED_TEST(MathQuaternionTest, MakeLookAtTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(MakeLookAtTest<TypeParam>());
}

TYPED_TEST(MathQuaternionTest, OutputStreamTest)
{
	using Quaternion = bksge::math::Quaternion<TypeParam>;
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

TYPED_TEST(MathQuaternionTest, SerializeTest)
{
	using namespace bksge::serialization;
	using Quaternion = bksge::math::Quaternion<TypeParam>;

	Quaternion const v { 1, -2, 3, -4 };

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
	using Quaternion = bksge::math::Quaternion<T>;

	Quaternion const v1(1, 2, 3, 4);
	Quaternion const v2(2, 2, 3, 4);
	Quaternion const v3(1, 0, 3, 4);
	Quaternion const v4(1, 2, 2, 4);
	Quaternion const v5(1, 2, 3, 0);

	std::hash<Quaternion> h;

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

TYPED_TEST(MathQuaternionTest, HashTest)
{
	// TODO constexpr化
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
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

TYPED_TEST(MathQuaternionTest, TupleSizeTest)
{
	using T = TypeParam;
	using Quaternion = bksge::math::Quaternion<T>;

	static_assert(std::tuple_size<Quaternion>::value == 4, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Quaternion = bksge::math::Quaternion<T>;
	{
		Quaternion v{1, 2, 3, 4};

		VERIFY(1 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(3 == bksge::get<2>(v));
		VERIFY(4 == bksge::get<3>(v));

		bksge::get<0>(v) = 5;
		bksge::get<3>(v) = 6;

		VERIFY(v == Quaternion(5, 2, 3, 6));
		VERIFY(5 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(3 == bksge::get<2>(v));
		VERIFY(6 == bksge::get<3>(v));
	}
	{
		Quaternion const v{1, 2, 3, 4};

		VERIFY(1 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(3 == bksge::get<2>(v));
		VERIFY(4 == bksge::get<3>(v));
	}
	return true;
}

TYPED_TEST(MathQuaternionTest, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

#undef VERIFY

}	// namespace quaternion_test

}	// namespace bksge_math_test
