/**
 *	@file	unit_test_core_math_color_hsv.cpp
 *
 *	@brief	ColorHSV のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/color_hsv.hpp>
#include <bksge/core/math/color3.hpp>
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

namespace color_hsv_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

using ColorHSVf = bksge::math::ColorHSV<float>;
using ColorHSVi = bksge::math::ColorHSV<int>;

using MathTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathColorHSVTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathColorHSVTest, MathTestTypes);

TYPED_TEST(MathColorHSVTest, DefaultConstructTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	static_assert(sizeof(ColorHSV) == sizeof(T) * 3, "");
	static_assert(bksge::is_default_constructible<ColorHSV>::value, "");
	static_assert(bksge::is_nothrow_default_constructible<ColorHSV>::value, "");
	static_assert(bksge::is_implicitly_default_constructible<ColorHSV>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST ColorHSV v;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v.v());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ColorHSV v{};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v.v());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ColorHSV v = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(0, v.v());
	}
}

TYPED_TEST(MathColorHSVTest, ValueConstructTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	static_assert(!bksge::is_constructible<ColorHSV, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<ColorHSV, T, T, T, T>::value, "");
	static_assert( bksge::is_constructible<ColorHSV, T, T, T>::value, "");
	static_assert(!bksge::is_constructible<ColorHSV, T, T>::value, "");
	static_assert(!bksge::is_constructible<ColorHSV, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<ColorHSV, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<ColorHSV, T, T, T, T>::value, "");
	static_assert( bksge::is_nothrow_constructible<ColorHSV, T, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<ColorHSV, T, T>::value, "");
	static_assert(!bksge::is_nothrow_constructible<ColorHSV, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<ColorHSV, T, T, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<ColorHSV, T, T, T, T>::value, "");
	static_assert( bksge::is_implicitly_constructible<ColorHSV, T, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<ColorHSV, T, T>::value, "");
	static_assert(!bksge::is_implicitly_constructible<ColorHSV, T>::value, "");

	{
		BKSGE_CONSTEXPR_OR_CONST ColorHSV v(1, 2, 3);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, v.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(2, v.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(3, v.v());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ColorHSV v{4, 5, 6};
		BKSGE_CONSTEXPR_EXPECT_EQ(4, v.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.v());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ColorHSV v = {7, 8, 9};
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(8, v.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(9, v.v());
	}
}

TYPED_TEST(MathColorHSVTest, CopyConstructTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	static_assert(bksge::is_constructible<ColorHSV,  ColorHSV  const&>::value, "");
	static_assert(bksge::is_constructible<ColorHSV,  ColorHSVi const&>::value, "");
	static_assert(bksge::is_constructible<ColorHSV,  ColorHSVf const&>::value, "");
	static_assert(bksge::is_constructible<ColorHSVi, ColorHSV  const&>::value, "");
	static_assert(bksge::is_constructible<ColorHSVi, ColorHSVi const&>::value, "");
	static_assert(bksge::is_constructible<ColorHSVi, ColorHSVf const&>::value, "");
	static_assert(bksge::is_constructible<ColorHSVf, ColorHSV  const&>::value, "");
	static_assert(bksge::is_constructible<ColorHSVf, ColorHSVi const&>::value, "");
	static_assert(bksge::is_constructible<ColorHSVf, ColorHSVf const&>::value, "");

	static_assert(bksge::is_nothrow_constructible<ColorHSV,  ColorHSV  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<ColorHSV,  ColorHSVi const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<ColorHSV,  ColorHSVf const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<ColorHSVi, ColorHSV  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<ColorHSVi, ColorHSVi const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<ColorHSVi, ColorHSVf const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<ColorHSVf, ColorHSV  const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<ColorHSVf, ColorHSVi const&>::value, "");
	static_assert(bksge::is_nothrow_constructible<ColorHSVf, ColorHSVf const&>::value, "");

	static_assert(bksge::is_implicitly_constructible<ColorHSV,  ColorHSV  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<ColorHSV,  ColorHSVi const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<ColorHSV,  ColorHSVf const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<ColorHSVi, ColorHSV  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<ColorHSVi, ColorHSVi const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<ColorHSVi, ColorHSVf const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<ColorHSVf, ColorHSV  const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<ColorHSVf, ColorHSVi const&>::value, "");
	static_assert(bksge::is_implicitly_constructible<ColorHSVf, ColorHSVf const&>::value, "");

	BKSGE_CONSTEXPR_OR_CONST ColorHSV  v1{1, 2, 3};
	BKSGE_CONSTEXPR_OR_CONST ColorHSV  v2{v1};
	BKSGE_CONSTEXPR_OR_CONST ColorHSVi v3{v2};
	BKSGE_CONSTEXPR_OR_CONST ColorHSVf v4{v2};

	BKSGE_CONSTEXPR_EXPECT_EQ(1, v1.h());
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v1.s());
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v1.v());
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v2.h());
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v2.s());
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v2.v());
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v3.h());
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v3.s());
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v3.v());
	BKSGE_CONSTEXPR_EXPECT_EQ(1, v4.h());
	BKSGE_CONSTEXPR_EXPECT_EQ(2, v4.s());
	BKSGE_CONSTEXPR_EXPECT_EQ(3, v4.v());
}

TYPED_TEST(MathColorHSVTest, FromColor3Test)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;
	using ColorRGB = bksge::math::Color3<T>;

	BKSGE_CXX14_CONSTEXPR double error = 0.0000001;

	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0, 0, 0);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0, hsv.h());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0, hsv.s());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0, hsv.v());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(1, 0, 0);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0, hsv.h());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0, hsv.s());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0, hsv.v());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0, 1, 0);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(2.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0, 0, 1);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(4.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(1, 1, 0);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(1, 0, 1);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(5.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(3.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(1, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0.5, 0, 0);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0,       (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.5,       (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0, 0.25, 0);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(2.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.25,      (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0, 0, 0.125);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(4.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.125,     (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0.5, 0.5, 0);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.5,       (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0.5, 0, 0.5);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(5.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.5,       (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0, 0.5, 0.5);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(3.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.5,       (double)hsv.v(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(0.5, 0.5, 0.5);
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(rgb);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0 / 6.0, (double)hsv.h(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0,       (double)hsv.s(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.5,       (double)hsv.v(), error);
	}
}

TYPED_TEST(MathColorHSVTest, ToColor3Test)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;
	using ColorRGB = bksge::math::Color3<T>;

	BKSGE_CXX14_CONSTEXPR double error = 0.0000001;

	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0, 0, 0);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0, 1, 0);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0, 0, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0, 0.5, 0);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0, 0, 0.5);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.5f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.5f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.5f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0, 0.5, 0.5);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.5f,  rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.25f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.25f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(T(0.0 / 6.0), 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(T(1.0 / 6.0), 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(T(2.0 / 6.0), 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(T(3.0 / 6.0), 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(T(4.0 / 6.0), 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(T(5.0 / 6.0), 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(T(6.0 / 6.0), 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(T(0.25), 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.5f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(T(0.5), 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(T(0.75), 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.5f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.b());
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NormalizedTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		auto hsv = Normalized(ColorHSV(0.0, 0.0, -1.0));
		VERIFY(0.0 == hsv.h());
		VERIFY(0.0 == hsv.s());
		VERIFY(0.0 == hsv.v());
	}
	{
		auto hsv = Normalized(ColorHSV(0.5, 1.0, -0.5));
		VERIFY(0.5 == hsv.h());
		VERIFY(1.0 == hsv.s());
		VERIFY(0.0 == hsv.v());
	}
	{
		auto hsv = Normalized(ColorHSV(1.0, 1.25, -0.25));
		VERIFY(0.0 == hsv.h());
		VERIFY(1.0 == hsv.s());
		VERIFY(0.0 == hsv.v());
	}
	{
		auto hsv = Normalized(ColorHSV(1.25, 1.5, 2.0));
		VERIFY(0.25 == hsv.h());
		VERIFY(1.0  == hsv.s());
		VERIFY(1.0  == hsv.v());
	}
	{
		auto hsv = Normalized(ColorHSV(1.5, 2.0, 1.5));
		VERIFY(0.5 == hsv.h());
		VERIFY(1.0 == hsv.s());
		VERIFY(1.0 == hsv.v());
	}
	{
		auto hsv = Normalized(ColorHSV(2.0, -0.25, 1.0));
		VERIFY(0.0 == hsv.h());
		VERIFY(0.0 == hsv.s());
		VERIFY(1.0 == hsv.v());
	}
	{
		auto hsv = Normalized(ColorHSV(-0.25, -0.5, 0.5));
		VERIFY(0.75 == hsv.h());
		VERIFY(0.0  == hsv.s());
		VERIFY(0.5  == hsv.v());
	}
	{
		auto hsv = Normalized(ColorHSV(-0.5, -1.0, 0.25));
		VERIFY(0.5  == hsv.h());
		VERIFY(0.0  == hsv.s());
		VERIFY(0.25 == hsv.v());
	}
	{
		auto hsv = Normalized(ColorHSV(-1.0, 0.5, 0.0));
		VERIFY(0.0 == hsv.h());
		VERIFY(0.5 == hsv.s());
		VERIFY(0.0 == hsv.v());
	}
	return true;
}

TYPED_TEST(MathColorHSVTest, NormalizedTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NormalizedTest<TypeParam>());
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CopyAssignTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV v1(0, 1, 2);
	ColorHSV v2(3, 4, 5);
	VERIFY(0 == v1.h());
	VERIFY(1 == v1.s());
	VERIFY(2 == v1.v());
	VERIFY(3 == v2.h());
	VERIFY(4 == v2.s());
	VERIFY(5 == v2.v());

	v1 = ColorHSV(6, -7, 8);
	v2 = ColorHSVi(-9, 10, 11);
	VERIFY( 6 == v1.h());
	VERIFY(-7 == v1.s());
	VERIFY( 8 == v1.v());
	VERIFY(-9 == v2.h());
	VERIFY(10 == v2.s());
	VERIFY(11 == v2.v());

	// 自己代入
	v1 = v1;
	v2 = v2;
	VERIFY( 6 == v1.h());
	VERIFY(-7 == v1.s());
	VERIFY( 8 == v1.v());
	VERIFY(-9 == v2.h());
	VERIFY(10 == v2.s());
	VERIFY(11 == v2.v());

	// 多重代入
	v1 = v2 = ColorHSVf(4, 5, 6);
	VERIFY(4 == v1.h());
	VERIFY(5 == v1.s());
	VERIFY(6 == v1.v());
	VERIFY(4 == v2.h());
	VERIFY(5 == v2.s());
	VERIFY(6 == v2.v());

	return true;
}

BKSGE_WARNING_POP()

TYPED_TEST(MathColorHSVTest, CopyAssignTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CopyAssignTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IndexAccessTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV v{1, 2, 3};
		VERIFY(1 == v[0]);
		VERIFY(2 == v[1]);
		VERIFY(3 == v[2]);

		v[0] = -3;
		v[1] =  4;
		v[2] = -5;

		VERIFY(-3 == v[0]);
		VERIFY( 4 == v[1]);
		VERIFY(-5 == v[2]);
	}
	{
		ColorHSV const v{5, 6, 7};
		VERIFY(5 == v[0]);
		VERIFY(6 == v[1]);
		VERIFY(7 == v[2]);
	}

	return true;
}

TYPED_TEST(MathColorHSVTest, IndexAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IndexAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool AtTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV v{1, 2, 3};
		VERIFY(1 == v.at(0));
		VERIFY(2 == v.at(1));
		VERIFY(3 == v.at(2));

		v.at(0) = -3;
		v.at(1) =  4;
		v.at(2) = -5;

		VERIFY(-3 == v.at(0));
		VERIFY( 4 == v.at(1));
		VERIFY(-5 == v.at(2));
	}
	{
		ColorHSV const v{5, 6, 7};
		VERIFY(5 == v.at(0));
		VERIFY(6 == v.at(1));
		VERIFY(7 == v.at(2));
	}

	return true;
}

TYPED_TEST(MathColorHSVTest, AtTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(AtTest<TypeParam>());
	using ColorHSV = bksge::math::ColorHSV<TypeParam>;
	{
		ColorHSV v{1, 2, 3};
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
	{
		ColorHSV const v{1, 2, 3};
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool DataTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV v{1, 2, 3};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(1 == *p);
		*p = 5;
		++p;
		VERIFY(2 == *p);
		++p;
		VERIFY(3 == *p);
		*p = 6;

		VERIFY(ColorHSV(5, 2, 6) == v);
	}
	{
		ColorHSV const v{1, 2, 3};
		auto p = v.data();
		VERIFY(p != nullptr);
		VERIFY(1 == p[0]);
		VERIFY(2 == p[1]);
		VERIFY(3 == p[2]);
	}

	return true;
}

TYPED_TEST(MathColorHSVTest, DataTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(DataTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool IteratorTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	// begin, end (non const)
	{
		ColorHSV v{1, 2, 3};
		auto it = v.begin();
		VERIFY(it != v.end());
		VERIFY(1 == *it);
		*it++ = 5;
		VERIFY(it != v.end());
		VERIFY(2 == *it);
		*++it = 6;
		VERIFY(it != v.end());
		VERIFY(6 == *it);
		it++;
		VERIFY(it == v.end());

		VERIFY(ColorHSV(5, 2, 6) == v);
	}
	// begin, end (const)
	{
		const ColorHSV v{1, 2, 3};
		auto it = v.begin();
		VERIFY(it != v.end());

		VERIFY(1 == it[0]);
		VERIFY(2 == it[1]);
		VERIFY(3 == it[2]);

		VERIFY(1 == *it++);
		VERIFY(it != v.end());
		VERIFY(3 == *++it);
		VERIFY(it != v.end());
		VERIFY(2 == *--it);
		VERIFY(it != v.end());
		VERIFY(2 == *it--);
		VERIFY(it != v.end());
		it += 2;
		VERIFY(it != v.end());
		VERIFY(3 == *it);
		it -= 2;
		VERIFY(it != v.end());
		VERIFY(1 == *it);
		it += 3;
		VERIFY(it == v.end());
	}
	// cbegin, cend
	{
		const ColorHSV v{1, 2, 3};
		auto it = v.cbegin();
		VERIFY(it != v.cend());

		VERIFY(1 == it[0]);
		VERIFY(2 == it[1]);
		VERIFY(3 == it[2]);

		VERIFY(1 == *it++);
		VERIFY(it != v.cend());
		VERIFY(3 == *++it);
		VERIFY(it != v.cend());
		VERIFY(3 == *it++);
		VERIFY(it == v.cend());
	}

	return true;
}

TYPED_TEST(MathColorHSVTest, IteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(IteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ReverseIteratorTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	// rbegin, rend (non const)
	{
		ColorHSV v{1, 2, 3};
		auto it = v.rbegin();
		VERIFY(it != v.rend());
		VERIFY(3 == *it);
		*it++ = 5;
		VERIFY(it != v.rend());
		VERIFY(2 == *it);
		*++it = 6;
		VERIFY(it != v.rend());
		VERIFY(6 == *it);
		it++;
		VERIFY(it == v.rend());

		VERIFY(6 == v[0]);
		VERIFY(2 == v[1]);
		VERIFY(5 == v[2]);
	}
	// rbegin, rend (const)
	{
		const ColorHSV v{1, 2, 3};
		auto it = v.rbegin();
		VERIFY(it != v.rend());

		VERIFY(3 == it[0]);
		VERIFY(2 == it[1]);
		VERIFY(1 == it[2]);

		VERIFY(3 == *it++);
		VERIFY(it != v.rend());
		VERIFY(1 == *++it);
		VERIFY(it != v.rend());
		VERIFY(2 == *--it);
		VERIFY(it != v.rend());
		VERIFY(2 == *it--);
		VERIFY(it != v.rend());
		it += 2;
		VERIFY(it != v.rend());
		VERIFY(1 == *it);
		it -= 2;
		VERIFY(it != v.rend());
		VERIFY(3 == *it);
		it += 3;
		VERIFY(it == v.rend());
	}
	// crbegin, crend
	{
		const ColorHSV v{1, 2, 3};
		auto it = v.crbegin();
		VERIFY(it != v.crend());

		VERIFY(3 == it[0]);
		VERIFY(2 == it[1]);
		VERIFY(1 == it[2]);

		VERIFY(3 == *it++);
		VERIFY(it != v.crend());
		VERIFY(1 == *++it);
		VERIFY(it != v.crend());
		VERIFY(1 == *it++);
		VERIFY(it == v.crend());
	}

	return true;
}

TYPED_TEST(MathColorHSVTest, ReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ReverseIteratorTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool EmptyTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV v1{};
	VERIFY(!v1.empty());
	return true;
}

TYPED_TEST(MathColorHSVTest, EmptyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(EmptyTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SizeTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV v1{};
	VERIFY(3 == v1.size());
	return true;
}

TYPED_TEST(MathColorHSVTest, SizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool MaxSizeTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV v1{};
	VERIFY(3 == v1.max_size());
	return true;
}

TYPED_TEST(MathColorHSVTest, MaxSizeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(MaxSizeTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool NameAccessTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV v{1, 2, 3};
		VERIFY(1 == v.h());
		VERIFY(2 == v.s());
		VERIFY(3 == v.v());

		v.h() = -3;
		v.s() =  4;
		v.v() = -5;

		VERIFY(-3 == v.h());
		VERIFY( 4 == v.s());
		VERIFY(-5 == v.v());
	}
	{
		ColorHSV const v{5, 6, 7};
		VERIFY(5 == v.h());
		VERIFY(6 == v.s());
		VERIFY(7 == v.v());
	}
	return true;
}

TYPED_TEST(MathColorHSVTest, NameAccessTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(NameAccessTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool SwapTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV v1{11, 12, 13};
	ColorHSV v2{21, 22, 23};

	v1.swap(v2);

	VERIFY(ColorHSV(21, 22, 23) == v1);
	VERIFY(ColorHSV(11, 12, 13) == v2);

	swap(v1, v2);

	VERIFY(ColorHSV(11, 12, 13) == v1);
	VERIFY(ColorHSV(21, 22, 23) == v2);

	return true;
}

TYPED_TEST(MathColorHSVTest, SwapTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool CompareTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV const v1(1, 2, 3);
	ColorHSV const v2(1, 2, 3);
	ColorHSV const v3(2, 2, 3);
	ColorHSV const v4(1, 0, 3);
	ColorHSV const v5(1, 2, 2);

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

TYPED_TEST(MathColorHSVTest, CompareTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(CompareTest<TypeParam>());
}

TYPED_TEST(MathColorHSVTest, OutputStreamTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV const v{1, -2, 3};
		std::stringstream ss;
		ss << v;
		EXPECT_EQ("{ 1, -2, 3 }", ss.str());
	}
	{
		ColorHSV const v{-10, 9, 8};
		std::wstringstream ss;
		ss << v;
		EXPECT_EQ(L"{ -10, 9, 8 }", ss.str());
	}
}

TYPED_TEST(MathColorHSVTest, TupleElementTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	static_assert(bksge::is_same<typename std::tuple_element<0, ColorHSV>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<1, ColorHSV>::type, T>::value, "");
	static_assert(bksge::is_same<typename std::tuple_element<2, ColorHSV>::type, T>::value, "");
}

TYPED_TEST(MathColorHSVTest, TupleSizeTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	static_assert(std::tuple_size<ColorHSV>::value == 3, "");
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool TupleGetTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV v{1, 2, 3};

		VERIFY(1 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(3 == bksge::get<2>(v));

		bksge::get<0>(v) = 5;

		VERIFY(ColorHSV(5, 2, 3) == v);
		VERIFY(5 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(3 == bksge::get<2>(v));
	}
	{
		ColorHSV const v{1, 2, 3};

		VERIFY(1 == bksge::get<0>(v));
		VERIFY(2 == bksge::get<1>(v));
		VERIFY(3 == bksge::get<2>(v));
	}

	return true;
}

TYPED_TEST(MathColorHSVTest, TupleGetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(TupleGetTest<TypeParam>());
}

template <typename T>
inline BKSGE_CXX14_CONSTEXPR bool ZeroTest()
{
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		auto v = ColorHSV::Zero();
		static_assert(bksge::is_same<decltype(v), ColorHSV>::value, "");
		VERIFY(ColorHSV(0, 0, 0) == v);
	}

	return true;
}

TYPED_TEST(MathColorHSVTest, ZeroTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(ZeroTest<TypeParam>());
}

TYPED_TEST(MathColorHSVTest, SerializeTest)
{
	using namespace bksge::serialization;

	using T = TypeParam;
	bksge::ColorHSV<T> const v { 1, 2, 3 };

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
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV const v1(1, 2, 3);
	ColorHSV const v2(2, 2, 3);
	ColorHSV const v3(1, 0, 3);
	ColorHSV const v4(1, 2, 2);

	std::hash<ColorHSV> h;

	VERIFY(h(v1) == h(v1));
	VERIFY(h(v1) != h(v2));
	VERIFY(h(v1) != h(v3));
	VERIFY(h(v1) != h(v4));

	VERIFY(h(v2) != h(v1));
	VERIFY(h(v2) == h(v2));
	VERIFY(h(v2) != h(v3));
	VERIFY(h(v2) != h(v4));

	VERIFY(h(v3) != h(v1));
	VERIFY(h(v3) != h(v2));
	VERIFY(h(v3) == h(v3));
	VERIFY(h(v3) != h(v4));

	VERIFY(h(v4) != h(v1));
	VERIFY(h(v4) != h(v2));
	VERIFY(h(v4) != h(v3));
	VERIFY(h(v4) == h(v4));

	return true;
}

TYPED_TEST(MathColorHSVTest, HashTest)
{
	/*BKSGE_CXX14_CONSTEXPR_*/EXPECT_TRUE(HashTest<TypeParam>());
}

#undef VERIFY

}	// namespace color_hsv_test

}	// namespace bksge_math_test
