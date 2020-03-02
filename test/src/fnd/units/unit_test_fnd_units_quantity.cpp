/**
 *	@file	unit_test_fnd_units_quantity.cpp
 *
 *	@brief	quantity のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/units/detail/quantity.hpp>
#include <bksge/fnd/units/base_dimensions/length.hpp>
#include <bksge/fnd/units/base_dimensions/mass.hpp>
#include <bksge/fnd/units/base_dimensions/time.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <sstream>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace units_quantity_test
{

template <typename T>
class QuantityTest : public ::testing::Test {};

using QuantityTestTypes = ::testing::Types<float, double, long double>;

TYPED_TEST_SUITE(QuantityTest, QuantityTestTypes);

TYPED_TEST(QuantityTest, DefaultConstructTest)
{
	using T = TypeParam;
	{
		using D = bksge::units::length_dimension;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D> q;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, q.value());
	}
	{
		using D = bksge::units::mass_dimension;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D> q;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, q.value());
	}
	{
		using D = bksge::units::length_dimension;
		using S = std::ratio<1000, 1>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S> q;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, q.value());
	}
	{
		using D = bksge::units::mass_dimension;
		using S = std::ratio<1, 1000>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S> q;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, q.value());
	}
	{
		using D = bksge::units::length_dimension;
		using S = std::ratio<1000, 1>;
		using O = std::ratio<100, 3>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S, O> q;
		BKSGE_CONSTEXPR_EXPECT_EQ(0, q.value());
	}
}

TYPED_TEST(QuantityTest, ValueConstructTest)
{
	using T = TypeParam;
	{
		using D = bksge::units::length_dimension;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D> q(1);
		BKSGE_CONSTEXPR_EXPECT_EQ(1, q.value());
	}
	{
		using D = bksge::units::mass_dimension;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D> q{2};
		BKSGE_CONSTEXPR_EXPECT_EQ(2, q.value());
	}
	{
		using D = bksge::units::length_dimension;
		using S = std::ratio<1000, 1>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S> q{3};
		BKSGE_CONSTEXPR_EXPECT_EQ(3, q.value());
	}
	{
		using D = bksge::units::mass_dimension;
		using S = std::ratio<1, 1000>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S> q(4);
		BKSGE_CONSTEXPR_EXPECT_EQ(4, q.value());
	}
	{
		using D = bksge::units::length_dimension;
		using S = std::ratio<1000, 1>;
		using O = std::ratio<100, 3>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S, O> q{5};
		BKSGE_CONSTEXPR_EXPECT_EQ(5, q.value());
	}
}

TYPED_TEST(QuantityTest, CopyConstructTest)
{
	using T = TypeParam;
	{
		using D = bksge::units::length_dimension;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D> q1(1);
		BKSGE_CONSTEXPR bksge::units::quantity<T, D> q2{q1};
		BKSGE_CONSTEXPR_EXPECT_EQ(1, q2.value());
	}
	{
		using D = bksge::units::mass_dimension;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D> q1{2};
		BKSGE_CONSTEXPR bksge::units::quantity<T, D> q2(q1);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, q2.value());
	}
	{
		using D = bksge::units::length_dimension;
		using S = std::ratio<1000, 1>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S> q1(3);
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S> q2(q1);
		BKSGE_CONSTEXPR_EXPECT_EQ(3, q2.value());
	}
	{
		using D = bksge::units::mass_dimension;
		using S = std::ratio<1, 1000>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S> q1{4};
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S> q2{q1};
		BKSGE_CONSTEXPR_EXPECT_EQ(4, q2.value());
	}
	{
		using D = bksge::units::length_dimension;
		using S = std::ratio<1000, 1>;
		using O = std::ratio<100, 3>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S, O> q1(5);
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S, O> q2(q1);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, q2.value());
	}
}

TYPED_TEST(QuantityTest, ConvertConstructTest)
{
	using T = TypeParam;
	{
		using D = bksge::units::length_dimension;
		using S1 = std::ratio<   1, 1>;
		using S2 = std::ratio<1000, 1>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S1> q1(1);
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S2> q2(q1);
		BKSGE_CONSTEXPR_EXPECT_EQ(T(1) / T(1000), q2.value());
	}
	{
		using D = bksge::units::mass_dimension;
		using S1 = std::ratio<100, 1>;
		using S2 = std::ratio<1, 1>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S1> q1(2);
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S2> q2{q1};
		BKSGE_CONSTEXPR_EXPECT_EQ(T(2) * T(100), q2.value());
	}
	{
		using D = bksge::units::time_dimension;
		using S1 = std::ratio<2, 3>;
		using S2 = std::ratio<5, 7>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S1> q1{3};
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S2> q2{q1};
		BKSGE_CONSTEXPR_EXPECT_NEAR(3.0 * (2.0 / 3.0) / (5.0 / 7.0), (double)q2.value(), 0.0000001);
	}
	{
		using D = bksge::units::length_dimension;
		using S = std::ratio<1, 1>;
		using O1 = std::ratio<100, 1>;
		using O2 = std::ratio<0, 1>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S, O1> q1(4);
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S, O2> q2(q1);
		BKSGE_CONSTEXPR_EXPECT_EQ(104, q2.value());
	}
	{
		using D = bksge::units::mass_dimension;
		using S1 = std::ratio<314, 100>;
		using S2 = std::ratio<11, 1000>;
		using O1 = std::ratio<25, 13>;
		using O2 = std::ratio<10, 17>;
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S1, O1> q1{5};
		BKSGE_CONSTEXPR bksge::units::quantity<T, D, S2, O2> q2{q1};
		BKSGE_CONSTEXPR_EXPECT_NEAR((5.0 + (25.0 / 13.0)) * (314.0 / 100.0) / (11.0 / 1000.0) - (10.0 / 17.0), (double)q2.value(), 0.0001);
	}
}

BKSGE_WARNING_PUSH()
#if defined(__clang_major__) && (__clang_major__ >= 7) && !defined(__APPLE__)
BKSGE_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
#endif

TYPED_TEST(QuantityTest, AssignTest)
{
	using T = TypeParam;
	using D = bksge::units::length_dimension;

	bksge::units::quantity<T, D> x;
	EXPECT_EQ(0, x.value());

	// コピー代入
	x = bksge::units::quantity<T, D>(3);
	EXPECT_EQ(3, x.value());

	// 変換代入
	x = bksge::units::quantity<T, D, std::ratio<100>>(4);
	EXPECT_EQ(400, x.value());

	x = bksge::units::quantity<T, D, std::ratio<100>, std::ratio<30>>(4);
	EXPECT_EQ(3400, x.value());

	// 自己代入
	x = x;
	EXPECT_EQ(3400, x.value());

	// 多重代入
	bksge::units::quantity<T, D, std::ratio<1, 1000>> y;
	x = y = bksge::units::quantity<T, D>(5);
	EXPECT_EQ(5, x.value());
	EXPECT_EQ(5000, y.value());
}

BKSGE_WARNING_POP()

TYPED_TEST(QuantityTest, SwapTest)
{
	using T = TypeParam;
	using D = bksge::units::length_dimension;
	using Q = bksge::units::quantity<T, D>;

	Q x1(12);
	Q x2(34);

	x1.swap(x2);

	EXPECT_EQ(34, x1.value());
	EXPECT_EQ(12, x2.value());

	swap(x1, x2);

	EXPECT_EQ(12, x1.value());
	EXPECT_EQ(34, x2.value());
}

TYPED_TEST(QuantityTest, PlusMinusTest)
{
	using T = TypeParam;
	using D = bksge::units::length_dimension;
	using Q1 = bksge::units::quantity<T, D>;
	using Q2 = bksge::units::quantity<T, D, std::ratio<1, 10>>;

	BKSGE_CONSTEXPR Q1 x(5);

	BKSGE_CONSTEXPR Q1 x1 = +x;
	BKSGE_CONSTEXPR Q1 x2 = -x;
	BKSGE_CONSTEXPR_EXPECT_EQ( 5, x1.value());
	BKSGE_CONSTEXPR_EXPECT_EQ(-5, x2.value());

	BKSGE_CONSTEXPR Q2 y1 = +x;
	BKSGE_CONSTEXPR Q2 y2 = -x;
	BKSGE_CONSTEXPR_EXPECT_EQ( 50, y1.value());
	BKSGE_CONSTEXPR_EXPECT_EQ(-50, y2.value());
}

TYPED_TEST(QuantityTest, AddTest)
{
	using T = TypeParam;
	using D = bksge::units::length_dimension;
	using Q1 = bksge::units::quantity<T, D>;
	using Q2 = bksge::units::quantity<T, D, std::ratio<1000>>;

	// quantity += quantity
	{
		Q1 x;

		x += Q1(3);
		EXPECT_EQ(3, x.value());

		x += Q2(4);
		EXPECT_EQ(4003, x.value());
	}
	// quantity + quantity
	{
		BKSGE_CONSTEXPR Q1 x = Q1(2) + Q1(3);
		BKSGE_CONSTEXPR_EXPECT_EQ(5, x.value());
	}
	{
		BKSGE_CONSTEXPR Q1 x = Q1(4) + Q2(5);
		BKSGE_CONSTEXPR_EXPECT_EQ(5004, x.value());
	}
	{
		BKSGE_CONSTEXPR Q1 x = Q2(6) + Q1(7);
		BKSGE_CONSTEXPR_EXPECT_EQ(6007, x.value());
	}
	{
		BKSGE_CONSTEXPR Q1 x = Q2(4) + Q2(5);
		BKSGE_CONSTEXPR_EXPECT_EQ(9000, x.value());
	}
}

TYPED_TEST(QuantityTest, SubTest)
{
	using T = TypeParam;
	using D = bksge::units::length_dimension;
	using Q1 = bksge::units::quantity<T, D>;
	using Q2 = bksge::units::quantity<T, D, std::ratio<1000>>;

	// quantity -= quantity
	{
		Q1 x(20);

		x -= Q1(3);
		EXPECT_EQ(17, x.value());

		x -= Q2(4);
		EXPECT_EQ(-3983, x.value());
	}
	// quantity - quantity
	{
		BKSGE_CONSTEXPR Q1 x = Q1(5) - Q1(3);
		BKSGE_CONSTEXPR_EXPECT_EQ(2, x.value());
	}
	{
		BKSGE_CONSTEXPR Q1 x = Q1(4) - Q2(5);
		BKSGE_CONSTEXPR_EXPECT_EQ(-4996, x.value());
	}
	{
		BKSGE_CONSTEXPR Q1 x = Q2(6) - Q1(7);
		BKSGE_CONSTEXPR_EXPECT_EQ(5993, x.value());
	}
	{
		BKSGE_CONSTEXPR Q1 x = Q2(4) - Q2(5);
		BKSGE_CONSTEXPR_EXPECT_EQ(-1000, x.value());
	}
}

TYPED_TEST(QuantityTest, MulScalarTest)
{
	using T = TypeParam;
	using D = bksge::units::length_dimension;
	using Q = bksge::units::quantity<T, D>;

	// quantity *= Scalar
	{
		Q x(2);
		EXPECT_EQ(2, x.value());

		x *= 3;
		EXPECT_EQ(6, x.value());

		x *= 1.5f;
		EXPECT_EQ(9.0, x.value());
	}
	// quantity * Scalar
	{
		BKSGE_CONSTEXPR Q x = Q(21) * 2;
		BKSGE_CONSTEXPR_EXPECT_EQ(42, x.value());
	}
	{
		BKSGE_CONSTEXPR Q x = Q(22) * 0.5f;
		BKSGE_CONSTEXPR_EXPECT_EQ(11, x.value());
	}
	// Scalar * quantity
	{
		BKSGE_CONSTEXPR Q x = 3 * Q(11);
		BKSGE_CONSTEXPR_EXPECT_EQ(33, x.value());
	}
	{
		BKSGE_CONSTEXPR Q x = 1.5 * Q(12);
		BKSGE_CONSTEXPR_EXPECT_EQ(18, x.value());
	}
}

TYPED_TEST(QuantityTest, MulRatioTest)
{
	using T = TypeParam;
	using D = bksge::units::length_dimension;

	// quantity * ratio
	{
		BKSGE_CONSTEXPR_OR_CONST auto x =
			bksge::units::quantity<T, D>(2) * std::ratio<100>();
		static_assert(bksge::is_same<
			const bksge::units::quantity<T, D, std::ratio<100>>,
			decltype(x)>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(2, x.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto x =
			bksge::units::quantity<T, D, std::ratio<2, 5>>(3) * std::ratio<7, 3>();
		static_assert(bksge::is_same<
			const bksge::units::quantity<T, D, std::ratio<14, 15>>,
			decltype(x)>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(3, x.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST auto x =
			bksge::units::quantity<T, D, std::ratio<3, 100>>(4) * std::ratio<5>();
		static_assert(bksge::is_same<
			const bksge::units::quantity<T, D, std::ratio<3, 20>>,
			decltype(x)>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(4, x.value());
	}
}

TYPED_TEST(QuantityTest, MulQuantityTest)
{
	using T = TypeParam;

	// quantity * quantity
	{
		using D1 = bksge::units::length_dimension;
		using D2 = bksge::units::derived_dimension<
			bksge::units::dimension_holder<
				bksge::units::length_base_dimension, 2
			>
		>;

		BKSGE_CONSTEXPR_OR_CONST auto x =
			bksge::units::quantity<T, D1>(2) *
			bksge::units::quantity<T, D1>(3);
		static_assert(bksge::is_same<
			const bksge::units::quantity<T, D2>,
			decltype(x)>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(6, x.value());
	}
	{
		using D1 = bksge::units::length_dimension;
		using D2 = bksge::units::mass_dimension;
		using D3 = bksge::units::derived_dimension<
			bksge::units::dimension_holder<
				bksge::units::length_base_dimension
			>,
			bksge::units::dimension_holder<
				bksge::units::mass_base_dimension
			>
		>;

		BKSGE_CONSTEXPR_OR_CONST auto x =
			bksge::units::quantity<T, D1>(2) *
			bksge::units::quantity<T, D2>(3);
		static_assert(bksge::is_same<
			const bksge::units::quantity<T, D3>,
			decltype(x)>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(6, x.value());
	}
	{
		using D1 = bksge::units::length_dimension;
		using D2 = bksge::units::derived_dimension<
			bksge::units::dimension_holder<
				bksge::units::length_base_dimension, 2
			>
		>;
		using Q1 = bksge::units::quantity<T, D1>;
		using Q2 = bksge::units::quantity<T, D1, std::ratio<1000>>;
		using Q3 = bksge::units::quantity<T, D2, std::ratio<1000>>;
		BKSGE_CONSTEXPR_OR_CONST auto x = Q1(4) * Q2(5);
		static_assert(bksge::is_same<const Q3, decltype(x)>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(20, x.value());
	}
}

TYPED_TEST(QuantityTest, DivScalarTest)
{
	using T = TypeParam;
	using D = bksge::units::length_dimension;
	using Q = bksge::units::quantity<T, D>;

	// quantity /= Scalar
	{
		Q x(10);
		EXPECT_EQ(10, x.value());

		x /= 2;
		EXPECT_EQ(5, x.value());

		x /= 0.5f;
		EXPECT_EQ(10, x.value());
	}
	// quantity / Scalar
	{
		BKSGE_CONSTEXPR_OR_CONST Q x = Q(8) / 2;
		BKSGE_CONSTEXPR_EXPECT_EQ(4, x.value());
	}
	{
		BKSGE_CONSTEXPR_OR_CONST Q x = Q(10) / 0.5;
		BKSGE_CONSTEXPR_EXPECT_EQ(20, x.value());
	}
	// Scalar / quantity
	{
		BKSGE_CONSTEXPR_OR_CONST auto x = T(10) / Q(2);
		using D2 = bksge::units::derived_dimension<
			bksge::units::dimension_holder<
				bksge::units::length_base_dimension, -1
			>
		>;
		using Q2 = bksge::units::quantity<T, D2>;
		static_assert(bksge::is_same<const Q2, decltype(x)>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, x.value());
	}
}

TYPED_TEST(QuantityTest, DivQuantityTest)
{
	using T = TypeParam;

	// quantity / quantity
	{
		using D1 = bksge::units::length_dimension;

		BKSGE_CONSTEXPR_OR_CONST auto x =
			bksge::units::quantity<T, D1>(9) /
			bksge::units::quantity<T, D1>(3);
		static_assert(bksge::is_same<
			const bksge::units::dimensionless<T>,
			decltype(x)>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(3, x.value());
	}
	{
		using D1 = bksge::units::length_dimension;
		using D2 = bksge::units::mass_dimension;
		using D3 = bksge::units::derived_dimension<
			bksge::units::dimension_holder<
				bksge::units::length_base_dimension
			>,
			bksge::units::dimension_holder<
				bksge::units::mass_base_dimension, -1
			>
		>;

		BKSGE_CONSTEXPR_OR_CONST auto x =
			bksge::units::quantity<T, D1>(10) /
			bksge::units::quantity<T, D2>(2);
		static_assert(bksge::is_same<
			const bksge::units::quantity<T, D3>,
			decltype(x)>::value, "");
		BKSGE_CONSTEXPR_EXPECT_EQ(5, x.value());
	}
	{
		using D1 = bksge::units::length_dimension;
		using Q1 = bksge::units::quantity<T, D1>;
		using Q2 = bksge::units::quantity<T, D1, std::ratio<1000>>;
		using Q3 = bksge::units::dimensionless<T, std::ratio<1, 1000>>;
		BKSGE_CONSTEXPR_OR_CONST auto x = Q1(12) / Q2(3);
		static_assert(bksge::is_same<const Q3, decltype(x)>::value, "");
		BKSGE_CONSTEXPR_EXPECT_NEAR(4, (double)x.value(), 0.0000000001);
	}
}

TYPED_TEST(QuantityTest, CompareTest)
{
	using T = TypeParam;
	using D = bksge::units::length_dimension;
	using Q1 = bksge::units::quantity<T, D>;
	using Q2 = bksge::units::quantity<T, D, std::ratio<1, 1000>>;

	BKSGE_CONSTEXPR Q1 x1(4);
	BKSGE_CONSTEXPR Q1 x2(4);
	BKSGE_CONSTEXPR Q1 x3(-4);
	BKSGE_CONSTEXPR Q1 x4(5);
	BKSGE_CONSTEXPR Q2 x5(4);
	BKSGE_CONSTEXPR Q2 x6(4000);

	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 == x1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 == x2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 == x3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 == x4);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 == x5);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 == x6);

	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 != x1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 != x2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 != x3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 != x4);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 != x5);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 != x6);

	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 < x1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 < x2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 < x3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 < x4);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 < x5);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 < x6);

	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 > x1);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 > x2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 > x3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 > x4);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 > x5);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 > x6);

	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 <= x1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 <= x2);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 <= x3);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 <= x4);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 <= x5);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 <= x6);

	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 >= x1);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 >= x2);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 >= x3);
	BKSGE_CONSTEXPR_EXPECT_FALSE(x1 >= x4);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 >= x5);
	BKSGE_CONSTEXPR_EXPECT_TRUE (x1 >= x6);
}

TYPED_TEST(QuantityTest, OutputStreamTest)
{
	using T = TypeParam;
	using D = bksge::units::length_dimension;
	using Q1 = bksge::units::quantity<T, D>;
	using Q2 = bksge::units::quantity<T, D, std::ratio<1, 1000>>;

	{
		const Q1 x(321);
		std::stringstream ss;
		ss << x;
		EXPECT_EQ("321", ss.str());
	}
	{
		const Q2 x(54321);
		std::wstringstream ss;
		ss << x;
		EXPECT_EQ(L"54321", ss.str());
	}
}

}	// namespace units_quantity_test
