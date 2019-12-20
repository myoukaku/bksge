/**
 *	@file	unit_test_core_math_rect.cpp
 *
 *	@brief	Rect のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/rect.hpp>
#include <bksge/core/math/vector2.hpp>
#include <bksge/core/math/size2.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <sstream>
#include <type_traits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace rect_test
{

using Rectf = bksge::math::Rect<float>;
using Recti = bksge::math::Rect<int>;
using Vector2f = bksge::math::Vector2<float>;
using Vector2i = bksge::math::Vector2<int>;

using MathTestTypes = ::testing::Types<int, float, double, long double>;

template <typename T>
class MathRectTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathRectTest, MathTestTypes);

TYPED_TEST(MathRectTest, DefaultConstructTest)
{
	using T = TypeParam;
	using Rect = bksge::math::Rect<T>;

	static_assert(sizeof(Rect) == sizeof(T) * 4, "");
	static_assert(std::is_default_constructible<Rect>::value, "");
	static_assert(std::is_nothrow_default_constructible<Rect>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<Rect>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST Rect r;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.left());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.top());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.right());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.bottom());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.width());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.height());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Rect r{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.left());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.top());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.right());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.bottom());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.width());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.height());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Rect r = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.left());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.top());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.right());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.bottom());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.width());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, r.height());
	}
}

TYPED_TEST(MathRectTest, Vector2Vector2ConstructTest)
{
	using T = TypeParam;
	using Rect = bksge::math::Rect<T>;
	using Vector2 = bksge::math::Vector2<T>;

	static_assert(!std::is_constructible<Rect, Vector2, Vector2, Vector2>::value, "");
	static_assert( std::is_constructible<Rect, Vector2, Vector2>::value, "");
	static_assert(!std::is_constructible<Rect, Vector2>::value, "");
	static_assert(!std::is_nothrow_constructible<Rect, Vector2, Vector2, Vector2>::value, "");
	static_assert( std::is_nothrow_constructible<Rect, Vector2, Vector2>::value, "");
	static_assert(!std::is_nothrow_constructible<Rect, Vector2>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Rect, Vector2, Vector2, Vector2>::value, "");
	static_assert( bksge::is_implicitly_constructible<Rect, Vector2, Vector2>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Rect, Vector2>::value, "");

	{
		BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r(Vector2{1, 2}, Vector2{-3, -4});
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(-3, r.left());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(-4, r.top());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 1, r.right());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 2, r.bottom());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4, r.width());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 6, r.height());
	}
	{
		BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r{Vector2{4, 5}, Vector2{0, 7}};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 0, r.left());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 5, r.top());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4, r.right());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 7, r.bottom());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4, r.width());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 2, r.height());
	}
	{
		BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r = {Vector2{7, 8}, Vector2{9, 10}};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 7, r.left());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 8, r.top());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 9, r.right());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(10, r.bottom());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 2, r.width());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 2, r.height());
	}
}

TYPED_TEST(MathRectTest, Vector2Size2ConstructTest)
{
	using T = TypeParam;
	using Rect = bksge::math::Rect<T>;
	using Vector2 = bksge::math::Vector2<T>;
	using Size2 = bksge::math::Size2<T>;

	static_assert(!std::is_constructible<Rect, Vector2, Size2, Vector2>::value, "");
	static_assert( std::is_constructible<Rect, Vector2, Size2>::value, "");
	static_assert(!std::is_constructible<Rect, Vector2>::value, "");
	static_assert(!std::is_nothrow_constructible<Rect, Vector2, Size2, Vector2>::value, "");
	static_assert( std::is_nothrow_constructible<Rect, Vector2, Size2>::value, "");
	static_assert(!std::is_nothrow_constructible<Rect, Vector2>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Rect, Vector2, Size2, Vector2>::value, "");
	static_assert( bksge::is_implicitly_constructible<Rect, Vector2, Size2>::value, "");
	static_assert(!bksge::is_implicitly_constructible<Rect, Vector2>::value, "");

	{
		BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r(Vector2{1, 2}, Size2{3, 4});
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 1, r.left());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 2, r.top());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4, r.right());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 6, r.bottom());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 3, r.width());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4, r.height());
	}
	{
		BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r{Vector2{4, 5}, Size2{6, 7}};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 4, r.left());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 5, r.top());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(10, r.right());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(12, r.bottom());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 6, r.width());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 7, r.height());
	}
	{
		BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r = {Vector2{7, 8}, Size2{9, 10}};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 7, r.left());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 8, r.top());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(16, r.right());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(18, r.bottom());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ( 9, r.width());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(10, r.height());
	}
}

TYPED_TEST(MathRectTest, CopyConstructTest)
{
	using T = TypeParam;
	using Rect = bksge::math::Rect<T>;
	using Vector2 = bksge::math::Vector2<T>;

	static_assert(std::is_constructible<Rect,  Rect  const&>::value, "");
	static_assert(std::is_constructible<Rect,  Recti const&>::value, "");
	static_assert(std::is_constructible<Rect,  Rectf const&>::value, "");
	static_assert(std::is_constructible<Recti, Rect  const&>::value, "");
	static_assert(std::is_constructible<Recti, Recti const&>::value, "");
	static_assert(std::is_constructible<Recti, Rectf const&>::value, "");
	static_assert(std::is_constructible<Rectf, Rect  const&>::value, "");
	static_assert(std::is_constructible<Rectf, Recti const&>::value, "");
	static_assert(std::is_constructible<Rectf, Rectf const&>::value, "");

	static_assert(std::is_nothrow_constructible<Rect,  Rect  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Rect,  Recti const&>::value, "");
	static_assert(std::is_nothrow_constructible<Rect,  Rectf const&>::value, "");
	static_assert(std::is_nothrow_constructible<Recti, Rect  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Recti, Recti const&>::value, "");
	static_assert(std::is_nothrow_constructible<Recti, Rectf const&>::value, "");
	static_assert(std::is_nothrow_constructible<Rectf, Rect  const&>::value, "");
	static_assert(std::is_nothrow_constructible<Rectf, Recti const&>::value, "");
	static_assert(std::is_nothrow_constructible<Rectf, Rectf const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<Rect,  Rect  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Rect,  Recti const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Rect,  Rectf const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Recti, Rect  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Recti, Recti const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Recti, Rectf const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Rectf, Rect  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Rectf, Recti const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<Rectf, Rectf const&>::value, "");

	BKSGE_CXX14_CONSTEXPR_OR_CONST Rect  r1{Vector2{1, 2}, Vector2{3, 4}};
	BKSGE_CXX14_CONSTEXPR_OR_CONST Rect  r2{r1};
	BKSGE_CXX14_CONSTEXPR_OR_CONST Recti r3{r2};
	BKSGE_CXX14_CONSTEXPR_OR_CONST Rectf r4{r2};

	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1, r1.left());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(2, r1.top());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, r1.right());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, r1.bottom());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1, r2.left());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(2, r2.top());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, r2.right());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, r2.bottom());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1, r3.left());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(2, r3.top());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, r3.right());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, r3.bottom());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1, r4.left());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(2, r4.top());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, r4.right());
	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, r4.bottom());
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

TYPED_TEST(MathRectTest, CopyAssignTest)
{
	using T = TypeParam;
	using Rect = bksge::math::Rect<T>;
	using Vector2 = bksge::math::Vector2<T>;

	Rect r1(Vector2{0, 1}, Vector2{2, 3});
	Rect r2(Vector2{3, 4}, Vector2{5, 6});
	EXPECT_EQ(0, r1.left());
	EXPECT_EQ(1, r1.top());
	EXPECT_EQ(2, r1.right());
	EXPECT_EQ(3, r1.bottom());
	EXPECT_EQ(3, r2.left());
	EXPECT_EQ(4, r2.top());
	EXPECT_EQ(5, r2.right());
	EXPECT_EQ(6, r2.bottom());

	r1 = Rect(Vector2(6, -7), Vector2(8, 9));
	r2 = Recti(Vector2i(-9, 10), Vector2i(11, -12));
	EXPECT_EQ(  6, r1.left());
	EXPECT_EQ( -7, r1.top());
	EXPECT_EQ(  8, r1.right());
	EXPECT_EQ(  9, r1.bottom());
	EXPECT_EQ( -9, r2.left());
	EXPECT_EQ(-12, r2.top());
	EXPECT_EQ( 11, r2.right());
	EXPECT_EQ( 10, r2.bottom());

	// 自己代入
	r1 = r1;
	r2 = r2;
	EXPECT_EQ(  6, r1.left());
	EXPECT_EQ( -7, r1.top());
	EXPECT_EQ(  8, r1.right());
	EXPECT_EQ(  9, r1.bottom());
	EXPECT_EQ( -9, r2.left());
	EXPECT_EQ(-12, r2.top());
	EXPECT_EQ( 11, r2.right());
	EXPECT_EQ( 10, r2.bottom());

	// 多重代入
	r1 = r2 = Rectf(Vector2f(4, 5), Vector2f(-4, -9));
	EXPECT_EQ(-4, r1.left());
	EXPECT_EQ(-9, r1.top());
	EXPECT_EQ( 4, r1.right());
	EXPECT_EQ( 5, r1.bottom());
	EXPECT_EQ(-4, r2.left());
	EXPECT_EQ(-9, r2.top());
	EXPECT_EQ( 4, r2.right());
	EXPECT_EQ( 5, r2.bottom());
}

BKSGE_WARNING_POP()

TYPED_TEST(MathRectTest, DataTest)
{
	using T = TypeParam;
	using Rect = bksge::math::Rect<T>;
	using Vector2 = bksge::math::Vector2<T>;

	{
		Rect r{Vector2(1, 2), Vector2(3, 4)};
		auto p = r.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, p[0]);
		EXPECT_EQ(2, p[1]);
		EXPECT_EQ(3, p[2]);
		EXPECT_EQ(4, p[3]);
	}
#if 0//!defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR Rect r{Vector2{1, 2}, Vector2{3, 4}};
		BKSGE_STATIC_CONSTEXPR auto p = r.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, p[2]);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, p[3]);
	}
#endif
}

TYPED_TEST(MathRectTest, SwapTest)
{
	using T = TypeParam;
	using Rect = bksge::math::Rect<T>;
	using Vector2 = bksge::math::Vector2<T>;

	Rect r1{Vector2{11, 12}, Vector2{21, 22}};
	Rect r2{Vector2{31, 32}, Vector2{41, 42}};

	r1.swap(r2);

	EXPECT_EQ(Rect(Vector2(31, 32), Vector2(41, 42)), r1);
	EXPECT_EQ(Rect(Vector2(11, 12), Vector2(21, 22)), r2);

	swap(r1, r2);

	EXPECT_EQ(Rect(Vector2(11, 12), Vector2(21, 22)), r1);
	EXPECT_EQ(Rect(Vector2(31, 32), Vector2(41, 42)), r2);
}

TYPED_TEST(MathRectTest, CompareTest)
{
	using T = TypeParam;
	using Rect = bksge::math::Rect<T>;
	using Vector2 = bksge::math::Vector2<T>;

	BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r1(Vector2{1, 2}, Vector2{ 3, 4});
	BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r2(Vector2{1, 2}, Vector2{ 3, 4});
	BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r3(Vector2{2, 2}, Vector2{ 3, 4});
	BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r4(Vector2{1, 0}, Vector2{ 3, 4});
	BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r5(Vector2{1, 2}, Vector2{-3, 4});
	BKSGE_CXX14_CONSTEXPR_OR_CONST Rect r6(Vector2{1, 2}, Vector2{ 3, 5});

	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r1 == r1);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r1 == r2);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r1 == r3);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r1 == r4);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r1 == r5);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r1 == r6);

	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r1 != r1);
	BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(r1 != r2);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r1 != r3);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r1 != r4);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r1 != r5);
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE (r1 != r6);
}

TYPED_TEST(MathRectTest, OutputStreamTest)
{
	using T = TypeParam;
	using Rect = bksge::math::Rect<T>;
	using Vector2 = bksge::math::Vector2<T>;
	using Size2 = bksge::math::Size2<T>;

	{
		Rect const r{Vector2{1, -2}, Vector2{3, 4}};
		std::stringstream ss;
		ss << r;
		EXPECT_EQ("{ 1, -2, 3, 4 }", ss.str());
	}
	{
		Rect const r{Vector2{-10, 9}, Size2{10, 15}};
		std::wstringstream ss;
		ss << r;
		EXPECT_EQ(L"{ -10, 9, 0, 24 }", ss.str());
	}
}

TYPED_TEST(MathRectTest, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	using Rect = bksge::math::Rect<T>;
	using Vector2 = bksge::math::Vector2<T>;

	Rect const v{Vector2{1, -2}, Vector2{3, 4}};

	SerializeTest<text_oarchive,   text_iarchive,   std::stringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::stringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::stringstream>(v);

#if !defined(BKSGE_NO_STD_WSTREAMBUF)
	SerializeTest<text_oarchive,   text_iarchive,   std::wstringstream>(v);
//	SerializeTest<xml_oarchive,    xml_iarchive,    std::wstringstream>(v);
//	SerializeTest<binary_oarchive, binary_iarchive, std::wstringstream>(v);
#endif
}

}	// namespace rect_test

}	// namespace bksge_math_test
