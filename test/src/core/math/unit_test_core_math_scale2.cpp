/**
 *	@file	unit_test_core_math_scale2.cpp
 *
 *	@brief	Scale2 のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/scale2.hpp>
#include <bksge/core/math/scale3.hpp>
#include <bksge/core/math/vector4.hpp>
#include <bksge/core/math/vector3.hpp>
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

namespace scale2_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using Scale2f = bksge::math::Scale2<float>;
using Scale2i = bksge::math::Scale2<int>;


using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathScale2Test : public ::testing::Test {};

TYPED_TEST_SUITE(MathScale2Test, MathTestTypes);

TYPED_TEST(MathScale2Test, DefaultConstructTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	static_assert(sizeof(Scale2) == sizeof(T) * 2, "");
	static_assert(bksge::is_default_constructible<Scale2>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<Scale2>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Scale2>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v[1]);
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
	static_assert( bksge::is_constructible<Scale2, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Scale2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Scale2, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<Scale2, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Scale2, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<Scale2, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Scale2, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Scale2, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Scale2, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<Scale2, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Scale2, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 v(1, 2);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 v{5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 v = {9, 10};
		BKSGE_CONSTEXPR_EXPECT_EQ( 9, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(10, v[1]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Scale2 v{13};
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(13, v[1]);
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

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using Scale2 = bksge::math::Scale2<T>;

	Scale2 v{0, 1};
	VERIFY(v[0] == 0);
	VERIFY(v[1] == 1);

	v = Scale2(-2, 3);
	VERIFY(v[0] == -2);
	VERIFY(v[1] ==  3);

	v = Scale2i(3, -4);
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);

	// 自己代入
	v = v;
	VERIFY(v[0] ==  3);
	VERIFY(v[1] == -4);

	// 多重代入
	Scale2 v2;
	v2 = v = Scale2f(4, 5);
	VERIFY(v[0] == 4);
	VERIFY(v[1] == 5);
	VERIFY(v2[0] == 4);
	VERIFY(v2[1] == 5);

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathScale2Test, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	{
		Scale2 v{1, 2};
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);

		v[0] = -3;
		v[1] =  4;

		VERIFY(v[0] == -3);
		VERIFY(v[1] ==  4);
	}
	{
		Scale2 const v{5, 6};
		VERIFY(v[0] == 5);
		VERIFY(v[1] == 6);
	}
	return true;
}

TYPED_TEST(MathScale2Test, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	{
		Scale2 v{1, 2};
		VERIFY(v.at(0) == 1);
		VERIFY(v.at(1) == 2);

		v.at(0) = -3;
		v.at(1) =  4;

		VERIFY(v.at(0) == -3);
		VERIFY(v.at(1) ==  4);
	}
	{
		Scale2 const v{5, 6};
		VERIFY(v.at(0) == 5);
		VERIFY(v.at(1) == 6);
	}
	return true;
}

TYPED_TEST(MathScale2Test, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());

	using Scale2 = bksge::math::Scale2<TypeParam>;
	{
		Scale2 v{1, 2};
		EXPECT_THROW((void)v.at(2), bksge::out_of_range);
	}
	{
		Scale2 const v{5, 6};
		EXPECT_THROW((void)v.at(2), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	{
		Scale2 v{1, 2};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == 1);
		*p = 5;
		++p;
		VERIFY(*p == 2);

		VERIFY(v == Scale2(5, 2));
	}
	{
		Scale2 const v{1, 2};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(*p == 1);
		++p;
		VERIFY(*p == 2);
	}
	return true;
}

TYPED_TEST(MathScale2Test, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using Scale2 = bksge::math::Scale2<T>;

	// begin, end (non const)
	{
		Scale2 v{1, 2};
		auto it = v.begin();
		VERIFY(it != v.end());
		VERIFY(*it == 1);
		*it++ = 5;
		VERIFY(it != v.end());
		VERIFY(*it == 2);
		it++;
		VERIFY(it == v.end());

		VERIFY(Scale2(5, 2) == v);
	}
	// begin, end (const)
	{
		Scale2 const v{1, 2};
		auto it = v.begin();
		VERIFY(it != v.end());

		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);

		VERIFY(*it++ == 1);
		VERIFY(it != v.end());
		++it;
		VERIFY(it == v.end());
	}
	// cbegin, cend
	{
		Scale2 v{1, 2};
		auto it = v.cbegin();
		VERIFY(it != v.cend());

		VERIFY(it[0] == 1);
		VERIFY(it[1] == 2);

		VERIFY(*it++ == 1);
		VERIFY(it != v.cend());
		++it;
		VERIFY(it == v.cend());
	}
	return true;
}

TYPED_TEST(MathScale2Test, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using Scale2 = bksge::math::Scale2<T>;

	// rbegin, rend (non const)
	{
		Scale2 v{1, 2};
		auto it = v.rbegin();
		VERIFY(it != v.rend());
		VERIFY(*it == 2);
		*it++ = 5;
		VERIFY(it != v.rend());
		VERIFY(*it == 1);
		it++;
		VERIFY(it == v.rend());

		VERIFY(Scale2(1, 5) == v);
	}
	// rbegin, rend (const)
	{
		Scale2 const v{1, 2};
		auto it = v.rbegin();
		VERIFY(it != v.rend());

		VERIFY(it[0] == 2);
		VERIFY(it[1] == 1);

		VERIFY(*it++ == 2);
		VERIFY(it != v.rend());
		++it;
		VERIFY(it == v.rend());
	}
	// crbegin, crend
	{
		Scale2 v{1, 2};
		auto it = v.crbegin();
		VERIFY(it != v.crend());

		VERIFY(it[0] == 2);
		VERIFY(it[1] == 1);

		VERIFY(*it++ == 2);
		VERIFY(it != v.crend());
		++it;
		VERIFY(it == v.crend());
	}
	return true;
}

TYPED_TEST(MathScale2Test, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	Scale2 v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathScale2Test, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	Scale2 v1{};
	VERIFY(v1.size() == 2);
	return true;
}

TYPED_TEST(MathScale2Test, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	Scale2 v1{};
	VERIFY(v1.max_size() == 2);
	return true;
}

TYPED_TEST(MathScale2Test, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	{
		Scale2 v{1, 2};
		VERIFY(v.x() == 1);
		VERIFY(v.y() == 2);

		v.x() = -3;
		v.y() =  4;

		VERIFY(v.x() == -3);
		VERIFY(v.y() ==  4);
	}
	{
		Scale2 const v{5, 6};
		VERIFY(v.x() == 5);
		VERIFY(v.y() == 6);
	}
	return true;
}

TYPED_TEST(MathScale2Test, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwizzleTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	using Vector4 = bksge::math::Vector4<T>;
	using Vector3 = bksge::math::Vector3<T>;
	using Vector2 = bksge::math::Vector2<T>;

	Scale2 v(1, 2);

	VERIFY(Vector4(1, 1, 1, 1) == v.xxxx());
	VERIFY(Vector4(1, 1, 1, 2) == v.xxxy());
	VERIFY(Vector4(1, 1, 2, 1) == v.xxyx());
	VERIFY(Vector4(1, 1, 2, 2) == v.xxyy());
	VERIFY(Vector4(1, 2, 1, 1) == v.xyxx());
	VERIFY(Vector4(1, 2, 1, 2) == v.xyxy());
	VERIFY(Vector4(1, 2, 2, 1) == v.xyyx());
	VERIFY(Vector4(1, 2, 2, 2) == v.xyyy());
	VERIFY(Vector4(2, 1, 1, 1) == v.yxxx());
	VERIFY(Vector4(2, 1, 1, 2) == v.yxxy());
	VERIFY(Vector4(2, 1, 2, 1) == v.yxyx());
	VERIFY(Vector4(2, 1, 2, 2) == v.yxyy());
	VERIFY(Vector4(2, 2, 1, 1) == v.yyxx());
	VERIFY(Vector4(2, 2, 1, 2) == v.yyxy());
	VERIFY(Vector4(2, 2, 2, 1) == v.yyyx());
	VERIFY(Vector4(2, 2, 2, 2) == v.yyyy());

	VERIFY(Vector3(1, 1, 1) == v.xxx());
	VERIFY(Vector3(1, 1, 2) == v.xxy());
	VERIFY(Vector3(1, 2, 1) == v.xyx());
	VERIFY(Vector3(1, 2, 2) == v.xyy());
	VERIFY(Vector3(2, 1, 1) == v.yxx());
	VERIFY(Vector3(2, 1, 2) == v.yxy());
	VERIFY(Vector3(2, 2, 1) == v.yyx());
	VERIFY(Vector3(2, 2, 2) == v.yyy());

	VERIFY(Vector2(1, 1) == v.xx());
	VERIFY(Vector2(1, 2) == v.xy());
	VERIFY(Vector2(2, 1) == v.yx());
	VERIFY(Vector2(2, 2) == v.yy());

	return true;
}

TYPED_TEST(MathScale2Test, SwizzleTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwizzleTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using Scale2 = bksge::math::Scale2<T>;

	Scale2 v1{1, 2};
	Scale2 v2{5, 6};

	v1.swap(v2);

	VERIFY(v1 == Scale2(5, 6));
	VERIFY(v2 == Scale2(1, 2));

	bksge::ranges::swap(v1, v2);

	VERIFY(v1 == Scale2(1, 2));
	VERIFY(v2 == Scale2(5, 6));

	return true;
}

TYPED_TEST(MathScale2Test, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool PlusMinusTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	{
		Scale2 const v1(-1, 2);
		Scale2 const v2 = +v1;
		Scale2 const v3 = -v1;

		VERIFY(v2[0] == -1);
		VERIFY(v2[1] ==  2);
		VERIFY(v3[0] ==  1);
		VERIFY(v3[1] == -2);
	}
	return true;
}

TYPED_TEST(MathScale2Test, PlusMinusTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(PlusMinusTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AddTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	// Scale2 += Scale2
	{
		Scale2 v;
		VERIFY(v == Scale2(0, 0));

		auto t = (v += Scale2(2, 3));
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(v == Scale2(2, 3));
		VERIFY(v == t);
	}
	// Scale2 + Scale2 -> Scale2
	{
		auto t = Scale2(-3, 4) + Scale2(0, 2);
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(t == Scale2(-3, 6));
	}
	return true;
}

TYPED_TEST(MathScale2Test, AddTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SubTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	// Scale2 -= Scale2
	{
		Scale2 v;
		VERIFY(v == Scale2(0, 0));

		auto t = (v -= Scale2(2, 3));
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(v == Scale2(-2, -3));
		VERIFY(v == t);
	}
	// Scale2 - Scale2 -> Scale2
	{
		auto t = Scale2(-3, 4) - Scale2(0, 2);
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(t == Scale2(-3, 2));
	}
	return true;
}

TYPED_TEST(MathScale2Test, SubTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SubTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScalarTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	// Scale2 *= スカラー
	{
		Scale2 v(2, 3);
		{
			auto t = (v *= 4);
			static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
			VERIFY(v == Scale2(8, 12));
			VERIFY(t == v);
		}
		{
			auto t = (v *= 0.5);
			static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
			VERIFY(v == Scale2(4, 6));
			VERIFY(t == v);
		}
	}
	// Scale2 * スカラー -> Scale2
	{
		auto t = Scale2(-3, 42) * -4;
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(t == Scale2(12, -168));
	}
	{
		auto t = Scale2(4, 6) * 2.5;
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(t == Scale2(10, 15));
	}
	// スカラー * Scale2 -> Scale2
	{
		auto t = 5 * Scale2(7, -8);
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(t == Scale2(35, -40));
	}
	{
		auto t = -1.5 * Scale2(4, -6);
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(t == Scale2(-6, 9));
	}
	return true;
}

TYPED_TEST(MathScale2Test, MulScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulScale2Test()
{
	using Scale2 = bksge::math::Scale2<T>;

	// Scale2 *= Scale2
	{
		Scale2 v(2, 3);

		auto t = (v *= Scale2(-1, 2));
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(Scale2(-2, 6) == v);
		VERIFY(t == v);
	}

	// Scale2 * Scale2 -> Scale2
	{
		auto t = Scale2(-3, 4) * Scale2(0, 2);
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(Scale2(0, 8) == t);
	}

	return true;
}

TYPED_TEST(MathScale2Test, MulScale2Test)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulScale2Test<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MulVector2Test()
{
	using Scale2 = bksge::math::Scale2<T>;
	using Vector2 = bksge::math::Vector2<T>;

	// Vector2 *= Scale2
	{
		Vector2 v {1, 2};

		auto t = (v *= Scale2{2, -3});
		static_assert(bksge::is_same<decltype(t), Vector2>::value, "");
		VERIFY(Vector2(2, -6) == v);
		VERIFY(t == v);
	}

	// Vector2 * Scale2 -> Vector2
	{
		auto t = Vector2{-5, 6} * Scale2{2, -2};
		static_assert(bksge::is_same<decltype(t), Vector2>::value, "");
		VERIFY(Vector2(-10, -12) == t);
	}

	return true;
}

TYPED_TEST(MathScale2Test, MulVector2Test)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MulVector2Test<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScalarTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	// Scale2 /= スカラー
	{
		Scale2 v(2, 4);
		{
			auto t = (v /= 2);
			static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
			VERIFY(v == Scale2(1, 2));
			VERIFY(t == v);
		}
		{
			auto t = (v /= 0.5);
			static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
			VERIFY(v == Scale2(2, 4));
			VERIFY(t == v);
		}
	}
	// Scale2 / スカラー -> Scale2
	{
		auto t = Scale2(-4, 8) / -4;
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(t == Scale2(1, -2));
	}
	{
		auto t = Scale2(-4, 8) / 0.25;
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(t == Scale2(-16, 32));
	}
	return true;
}

TYPED_TEST(MathScale2Test, DivScalarTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScalarTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DivScale2Test()
{
	using Scale2 = bksge::math::Scale2<T>;

	// Scale2 /= Scale2
	{
		Scale2 v(8, 12);

		auto t = (v /= Scale2(-1, 2));
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(Scale2(-8, 6) == v);
		VERIFY(t == v);
	}

	// Scale2 / Scale2 -> Scale2
	{
		auto t = Scale2(-3, 4) / Scale2(1, 2);
		static_assert(bksge::is_same<decltype(t), Scale2>::value, "");
		VERIFY(Scale2(-3, 2) == t);
	}

	return true;
}

TYPED_TEST(MathScale2Test, DivScale2Test)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DivScale2Test<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using Scale2 = bksge::math::Scale2<T>;

	Scale2 const v1(1, 2);
	Scale2 const v2(1, 2);
	Scale2 const v3(2, 2);
	Scale2 const v4(1, 0);

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

TYPED_TEST(MathScale2Test, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathScale2Test, OutputStreamTest)
{
	using Scale2 = bksge::math::Scale2<TypeParam>;
	{
		Scale2 const v{1, -2};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2 }", ss.str());
	}
	{
		Scale2 const v{-10, 9};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9 }", ss.str());
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	{
		auto v = Scale2::Zero();
		static_assert(bksge::is_same<decltype(v), Scale2>::value, "");
		VERIFY(Scale2(0, 0) == v);
	}
	return true;
}

TYPED_TEST(MathScale2Test, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IdentityTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	{
		auto v = Scale2::Identity();
		static_assert(bksge::is_same<decltype(v), Scale2>::value, "");
		VERIFY(Scale2(1, 1) == v);
	}
	return true;
}

TYPED_TEST(MathScale2Test, IdentityTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IdentityTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool LerpTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	{
		Scale2 v1 {  0,  0 };
		Scale2 v2 { 10, 20 };

		VERIFY(Scale2( 0.0,  0.0) == Lerp(v1, v2, 0.00f));
		VERIFY(Scale2( 2.5,  5.0) == Lerp(v1, v2, 0.25f));
		VERIFY(Scale2( 5.0, 10.0) == Lerp(v1, v2, 0.50f));
		VERIFY(Scale2( 7.5, 15.0) == Lerp(v1, v2, 0.75f));
		VERIFY(Scale2(10.0, 20.0) == Lerp(v1, v2, 1.00f));
	}
	{
		Scale2 v1 { -10,  10 };
		Scale2 v2 {  10, -20 };

		VERIFY(Scale2(-10.0,  10.0) == Lerp(v1, v2, 0.00));
		VERIFY(Scale2( -5.0,   2.5) == Lerp(v1, v2, 0.25));
		VERIFY(Scale2(  0.0,  -5.0) == Lerp(v1, v2, 0.50));
		VERIFY(Scale2(  5.0, -12.5) == Lerp(v1, v2, 0.75));
		VERIFY(Scale2( 10.0, -20.0) == Lerp(v1, v2, 1.00));
	}
	return true;
}

TYPED_TEST(MathScale2Test, LerpTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(LerpTest<TypeParam>());
}

TYPED_TEST(MathScale2Test, SerializeTest)
{
	using namespace bksge::serialization;
	using Scale2 = bksge::math::Scale2<TypeParam>;

	Scale2 const v { 1, -2 };

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
	using Scale2 = bksge::math::Scale2<T>;

	Scale2 const v1(1, 2);
	Scale2 const v2(2, 2);
	Scale2 const v3(1, 0);
	Scale2 const v4(1, 2);

	std::hash<Scale2> h;

	VERIFY(h(v1) == h(v1));
	VERIFY(h(v1) != h(v2));
	VERIFY(h(v1) != h(v3));
	VERIFY(h(v1) == h(v4));

	VERIFY(h(v2) != h(v1));
	VERIFY(h(v2) == h(v2));
	VERIFY(h(v2) != h(v3));
	VERIFY(h(v2) != h(v4));

	VERIFY(h(v3) != h(v1));
	VERIFY(h(v3) != h(v2));
	VERIFY(h(v3) == h(v3));
	VERIFY(h(v3) != h(v4));

	VERIFY(h(v4) == h(v1));
	VERIFY(h(v4) != h(v2));
	VERIFY(h(v4) != h(v3));
	VERIFY(h(v4) == h(v4));

	return true;
}

TYPED_TEST(MathScale2Test, HashTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

TYPED_TEST(MathScale2Test, TupleElementTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	static_assert(bksge::is_same<typename std::tuple_element<0, Scale2>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<1, Scale2>::type, T>::value, "");
}

TYPED_TEST(MathScale2Test, TupleSizeTest)
{
	using T = TypeParam;
	using Scale2 = bksge::math::Scale2<T>;

	static_assert(std::tuple_size<Scale2>::value == 2, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using Scale2 = bksge::math::Scale2<T>;
	{
		Scale2 v{1, 2};

		VERIFY(1 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));

		bksge::get<0>(v) = 5;

		VERIFY(v == Scale2(5, 2));
		VERIFY(5 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
	}
	{
		Scale2 const v{1, 2};

		VERIFY(1 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
	}
	return true;
}

TYPED_TEST(MathScale2Test, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

#undef VERIFY

}	// namespace scale2_test

}	// namespace bksge_math_test
