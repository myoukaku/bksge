/**
 *	@file	unit_test_core_math_color_hsv.cpp
 *
 *	@brief	ColorHSV のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/math/color_hsv.hpp>
#include <bksge/core/math/color3.hpp>
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
#include <bksge/fnd/config.hpp>
#include <functional>
#include <tuple>
#include <vector>
#include <sstream>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "serialize_test.hpp"

namespace bksge_math_test
{

namespace color_hsv_test
{

using ColorHSVf = bksge::math::ColorHSV<float>;
using ColorHSVi = bksge::math::ColorHSV<int>;

using MathTestTypes = ::testing::Types</*int,*/ float, double, long double>;
using MathFloatTestTypes = ::testing::Types<float, double, long double>;

template <typename T>
class MathColorHSVTest : public ::testing::Test {};
template <typename T>
class MathColorHSVFloatTest : public ::testing::Test {};

TYPED_TEST_SUITE(MathColorHSVTest, MathTestTypes);
TYPED_TEST_SUITE(MathColorHSVFloatTest, MathFloatTestTypes);

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
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0.0 / 6.0, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(1.0 / 6.0, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(2.0 / 6.0, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(3.0 / 6.0, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(4.0 / 6.0, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(5.0 / 6.0, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(6.0 / 6.0, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(1.0, (double)rgb.r(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.g(), error);
		BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(0.0, (double)rgb.b(), error);
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0.25, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.5f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0.5, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.b());
	}
	{
		BKSGE_CXX14_CONSTEXPR ColorHSV hsv(0.75, 1, 1);
		BKSGE_CXX14_CONSTEXPR ColorRGB rgb(hsv);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.5f, rgb.r());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.0f, rgb.g());
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(1.0f, rgb.b());
	}
}

TYPED_TEST(MathColorHSVTest, NormalizedTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		BKSGE_CONSTEXPR auto hsv = Normalized(ColorHSV(0.0, 0.0, -1.0));
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f, hsv.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f, hsv.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f, hsv.v());
	}
	{
		BKSGE_CONSTEXPR auto hsv = Normalized(ColorHSV(0.5, 1.0, -0.5));
		BKSGE_CONSTEXPR_EXPECT_EQ(0.5f, hsv.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(1.0f, hsv.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f, hsv.v());
	}
	{
		BKSGE_CONSTEXPR auto hsv = Normalized(ColorHSV(1.0, 1.25, -0.25));
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f, hsv.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(1.0f, hsv.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f, hsv.v());
	}
	{
		BKSGE_CONSTEXPR auto hsv = Normalized(ColorHSV(1.25, 1.5, 2.0));
		BKSGE_CONSTEXPR_EXPECT_EQ(0.25f, hsv.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(1.0f,  hsv.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(1.0f,  hsv.v());
	}
	{
		BKSGE_CONSTEXPR auto hsv = Normalized(ColorHSV(1.5, 2.0, 1.5));
		BKSGE_CONSTEXPR_EXPECT_EQ(0.5f, hsv.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(1.0f, hsv.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(1.0f, hsv.v());
	}
	{
		BKSGE_CONSTEXPR auto hsv = Normalized(ColorHSV(2.0, -0.25, 1.0));
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f, hsv.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f, hsv.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(1.0f, hsv.v());
	}
	{
		BKSGE_CONSTEXPR auto hsv = Normalized(ColorHSV(-0.25, -0.5, 0.5));
		BKSGE_CONSTEXPR_EXPECT_EQ(0.75f, hsv.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f,  hsv.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.5f,  hsv.v());
	}
	{
		BKSGE_CONSTEXPR auto hsv = Normalized(ColorHSV(-0.5, -1.0, 0.25));
		BKSGE_CONSTEXPR_EXPECT_EQ(0.5f,  hsv.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f,  hsv.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.25f, hsv.v());
	}
	{
		BKSGE_CONSTEXPR auto hsv = Normalized(ColorHSV(-1.0, 0.5, 0.0));
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f, hsv.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.5f, hsv.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f, hsv.v());
	}
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

TYPED_TEST(MathColorHSVTest, CopyAssignTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV v1(0, 1, 2);
	ColorHSV v2(3, 4, 5);
	EXPECT_EQ(0, v1.h());
	EXPECT_EQ(1, v1.s());
	EXPECT_EQ(2, v1.v());
	EXPECT_EQ(3, v2.h());
	EXPECT_EQ(4, v2.s());
	EXPECT_EQ(5, v2.v());

	v1 = ColorHSV(6, -7, 8);
	v2 = ColorHSVi(-9, 10, 11);
	EXPECT_EQ( 6, v1.h());
	EXPECT_EQ(-7, v1.s());
	EXPECT_EQ( 8, v1.v());
	EXPECT_EQ(-9, v2.h());
	EXPECT_EQ(10, v2.s());
	EXPECT_EQ(11, v2.v());

	// 自己代入
	v1 = v1;
	v2 = v2;
	EXPECT_EQ( 6, v1.h());
	EXPECT_EQ(-7, v1.s());
	EXPECT_EQ( 8, v1.v());
	EXPECT_EQ(-9, v2.h());
	EXPECT_EQ(10, v2.s());
	EXPECT_EQ(11, v2.v());

	// 多重代入
	v1 = v2 = ColorHSVf(4, 5, 6);
	EXPECT_EQ(4, v1.h());
	EXPECT_EQ(5, v1.s());
	EXPECT_EQ(6, v1.v());
	EXPECT_EQ(4, v2.h());
	EXPECT_EQ(5, v2.s());
	EXPECT_EQ(6, v2.v());
}

BKSGE_WARNING_POP()

TYPED_TEST(MathColorHSVTest, IndexAccessTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV v{1, 2, 3};
		EXPECT_EQ(1, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(3, v[2]);

		v[0] = -3;
		v[1] =  4;
		v[2] = -5;

		EXPECT_EQ(-3, v[0]);
		EXPECT_EQ( 4, v[1]);
		EXPECT_EQ(-5, v[2]);
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ColorHSV v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v[2]);
	}
}

TYPED_TEST(MathColorHSVTest, AtTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV v{1, 2, 3};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);

		v.at(0) = -3;
		v.at(1) =  4;
		v.at(2) = -5;

		EXPECT_EQ(-3, v.at(0));
		EXPECT_EQ( 4, v.at(1));
		EXPECT_EQ(-5, v.at(2));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ColorHSV v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.at(0));
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.at(1));
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.at(2));
		EXPECT_THROW((void)v.at(3), bksge::out_of_range);
	}
}

TYPED_TEST(MathColorHSVTest, DataTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV v{1, 2, 3};
		auto p = v.data();
		EXPECT_TRUE(p != nullptr);
		EXPECT_EQ(1, *p);
		*p = 5;
		++p;
		EXPECT_EQ(2, *p);
		++p;
		EXPECT_EQ(3, *p);
		*p = 6;

		EXPECT_EQ(ColorHSV(5, 2, 6), v);
	}
#if !defined(BKSGE_GCC)
	{
		BKSGE_STATIC_CONSTEXPR ColorHSV v{1, 2, 3};
		BKSGE_STATIC_CONSTEXPR auto p = v.data();
		BKSGE_CONSTEXPR_EXPECT_TRUE(p != nullptr);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, p[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, p[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, p[2]);
	}
#endif
}

TYPED_TEST(MathColorHSVTest, IteratorTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	// begin, end (non const)
	{
		ColorHSV v{1, 2, 3};
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
		EXPECT_TRUE(it == v.end());

		EXPECT_EQ(ColorHSV(5, 2, 6), v);
	}
	// begin, end (const)
	{
		const ColorHSV v{1, 2, 3};
		auto it = v.begin();
		EXPECT_TRUE(it != v.end());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(3, it[2]);

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
		EXPECT_TRUE(it == v.end());
	}
	// cbegin, cend
	{
		const ColorHSV v{1, 2, 3};
		auto it = v.cbegin();
		EXPECT_TRUE(it != v.cend());

		EXPECT_EQ(1, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(3, it[2]);

		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(3, *++it);
		EXPECT_TRUE(it != v.cend());
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it == v.cend());
	}
#if !defined(BKSGE_GCC)
	// begin, end (constexpr)
	{
		BKSGE_STATIC_CONSTEXPR ColorHSV v{1, 2, 3};
		BKSGE_CONSTEXPR_OR_CONST auto it = v.begin();
		BKSGE_CONSTEXPR_EXPECT_TRUE(it != v.end());

		BKSGE_CONSTEXPR_EXPECT_EQ(1, it[0]);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, it[1]);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, it[2]);

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
		BKSGE_CONSTEXPR_EXPECT_TRUE(it5 == v.end());
	}
#endif
}

TYPED_TEST(MathColorHSVTest, ReverseIteratorTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	// rbegin, rend (non const)
	{
		ColorHSV v{1, 2, 3};
		auto it = v.rbegin();
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(3, *it);
		*it++ = 5;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *it);
		*++it = 6;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(6, *it);
		it++;
		EXPECT_TRUE(it == v.rend());

		EXPECT_EQ(6, v[0]);
		EXPECT_EQ(2, v[1]);
		EXPECT_EQ(5, v[2]);
	}
	// rbegin, rend (const)
	{
		const ColorHSV v{1, 2, 3};
		auto it = v.rbegin();
		EXPECT_TRUE(it != v.rend());

		EXPECT_EQ(3, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(1, it[2]);

		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(1, *++it);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *--it);
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(2, *it--);
		EXPECT_TRUE(it != v.rend());
		it += 2;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(1, *it);
		it -= 2;
		EXPECT_TRUE(it != v.rend());
		EXPECT_EQ(3, *it);
		it += 3;
		EXPECT_TRUE(it == v.rend());
	}
	// crbegin, crend
	{
		const ColorHSV v{1, 2, 3};
		auto it = v.crbegin();
		EXPECT_TRUE(it != v.crend());

		EXPECT_EQ(3, it[0]);
		EXPECT_EQ(2, it[1]);
		EXPECT_EQ(1, it[2]);

		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(1, *++it);
		EXPECT_TRUE(it != v.crend());
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == v.crend());
	}
#if defined(__cpp_lib_array_constexpr) && (__cpp_lib_array_constexpr >= 201603) && !defined(BKSGE_GCC)
	// rbegin, rend (constexpr)
	{
		BKSGE_CXX17_STATIC_CONSTEXPR ColorHSV v{1, 2, 3};
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it = v.rbegin();
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it != v.rend());

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, it[0]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, it[1]);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, it[2]);

		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(3, *it);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it2 = it + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it2 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it2);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it3 = it2 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it3 != v.rend());
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(1, *it3);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it4 = it3 - 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it4 == it2);
		BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(2, *it4);
		BKSGE_CXX17_CONSTEXPR_OR_CONST auto it5 = it3 + 1;
		BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(it5 == v.rend());
	}
#endif
}

TYPED_TEST(MathColorHSVTest, EmptyTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV v1{};
	const           ColorHSV v2{};
	BKSGE_CONSTEXPR ColorHSV v3{};
	EXPECT_FALSE(v1.empty());
	EXPECT_FALSE(v2.empty());
	BKSGE_CONSTEXPR_EXPECT_FALSE(v3.empty());
}

TYPED_TEST(MathColorHSVTest, SizeTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV v1{};
	const           ColorHSV v2{};
	BKSGE_CONSTEXPR ColorHSV v3{};
	EXPECT_EQ(3u, v1.size());
	EXPECT_EQ(3u, v2.size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, v3.size());
}

TYPED_TEST(MathColorHSVTest, MaxSizeTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV v1{};
	const           ColorHSV v2{};
	BKSGE_CONSTEXPR ColorHSV v3{};
	EXPECT_EQ(3u, v1.max_size());
	EXPECT_EQ(3u, v2.max_size());
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, v3.max_size());
}

TYPED_TEST(MathColorHSVTest, NameAccessTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV v{1, 2, 3};
		EXPECT_EQ(1, v.h());
		EXPECT_EQ(2, v.s());
		EXPECT_EQ(3, v.v());

		v.h() = -3;
		v.s() =  4;
		v.v() = -5;

		EXPECT_EQ(-3, v.h());
		EXPECT_EQ( 4, v.s());
		EXPECT_EQ(-5, v.v());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ColorHSV v{5, 6, 7};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, v.h());
		BKSGE_CONSTEXPR_EXPECT_EQ(6, v.s());
		BKSGE_CONSTEXPR_EXPECT_EQ(7, v.v());
	}
}

TYPED_TEST(MathColorHSVTest, SwapTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	ColorHSV v1{11, 12, 13};
	ColorHSV v2{21, 22, 23};

	EXPECT_EQ(ColorHSV(11, 12, 13), v1);
	EXPECT_EQ(ColorHSV(21, 22, 23), v2);

	v1.swap(v2);

	EXPECT_EQ(ColorHSV(21, 22, 23), v1);
	EXPECT_EQ(ColorHSV(11, 12, 13), v2);

	swap(v1, v2);

	EXPECT_EQ(ColorHSV(11, 12, 13), v1);
	EXPECT_EQ(ColorHSV(21, 22, 23), v2);
}

TYPED_TEST(MathColorHSVTest, CompareTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	BKSGE_CONSTEXPR_OR_CONST ColorHSV v1(1, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST ColorHSV v2(1, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST ColorHSV v3(2, 2, 3);
	BKSGE_CONSTEXPR_OR_CONST ColorHSV v4(1, 0, 3);
	BKSGE_CONSTEXPR_OR_CONST ColorHSV v5(1, 2, 2);

	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 == v2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v4);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 == v5);

	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(v1 != v2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v4);
	BKSGE_CONSTEXPR_EXPECT_TRUE (v1 != v5);
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

TYPED_TEST(MathColorHSVTest, TupleGetTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		ColorHSV v{1, 2, 3};

		EXPECT_EQ(1, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));

		bksge::get<0>(v) = 5;

		EXPECT_EQ(ColorHSV(5, 2, 3), v);
		EXPECT_EQ(5, bksge::get<0>(v));
		EXPECT_EQ(2, bksge::get<1>(v));
		EXPECT_EQ(3, bksge::get<2>(v));
	}
	{
		BKSGE_CONSTEXPR_OR_CONST ColorHSV v{1, 2, 3};

		BKSGE_CONSTEXPR_EXPECT_EQ(1, bksge::get<0>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(2, bksge::get<1>(v));
		BKSGE_CONSTEXPR_EXPECT_EQ(3, bksge::get<2>(v));
	}
}

TYPED_TEST(MathColorHSVTest, TupleSizeTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	static_assert(std::tuple_size<ColorHSV>::value == 3, "");
}

TYPED_TEST(MathColorHSVTest, ZeroTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	{
		BKSGE_CONSTEXPR_OR_CONST auto v = ColorHSV::Zero();
		static_assert(bksge::is_same<decltype(v), const ColorHSV>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(ColorHSV(0, 0, 0), v);
	}
	{
		const auto v = ColorHSV::Zero();
		static_assert(bksge::is_same<decltype(v), const ColorHSV>::value, "");
		EXPECT_EQ(ColorHSV(0, 0, 0), v);
	}
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

TYPED_TEST(MathColorHSVTest, HashTest)
{
	using T = TypeParam;
	using ColorHSV = bksge::math::ColorHSV<T>;

	std::hash<ColorHSV> h;

	ColorHSV const c1(1, 2, 3);
	ColorHSV const c2(2, 2, 3);
	ColorHSV const c3(1, 0, 3);
	ColorHSV const c4(1, 2, 2);

	std::vector<std::size_t> v;
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

}	// namespace color_hsv_test

}	// namespace bksge_math_test
