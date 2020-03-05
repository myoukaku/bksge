/**
 *	@file	unit_test_fnd_tuple_get.cpp
 *
 *	@brief	get のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include <string>
#include <complex>
#include <memory>	// unique_ptr
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace get_test
{

struct Empty {};

struct S
{
	bksge::tuple<int, Empty> a;
	int k;
	Empty e;
	BKSGE_CXX14_CONSTEXPR S()
		: a{1, Empty{}}
		, k(bksge::get<0>(a))
		, e(bksge::get<1>(a))
	{}
};

BKSGE_CXX14_CONSTEXPR bksge::tuple<int, int> getP () { return{3, 4}; }

GTEST_TEST(TupleTest, GetConstTest)
{
	{
		typedef bksge::tuple<int> T;
		const T t(3);
		EXPECT_EQ(bksge::get<0>(t), 3);
	}
	{
		typedef bksge::tuple<std::string, int> T;
		const T t("high", 5);
		EXPECT_EQ(bksge::get<0>(t), "high");
		EXPECT_EQ(bksge::get<1>(t), 5);
	}
	{
		typedef bksge::tuple<double, int> T;
		BKSGE_CXX14_CONSTEXPR T t(2.718, 5);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t), 2.718);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<1>(t), 5);
	}
	{
		typedef bksge::tuple<Empty> T;
		BKSGE_CXX14_CONSTEXPR T t{Empty()};
		BKSGE_CXX14_CONSTEXPR Empty e = bksge::get<0>(t);
		((void)e); // Prevent unused warning
	}
	{
		typedef bksge::tuple<double&, std::string, int> T;
		double d = 1.5;
		const T t(d, "high", 5);
		EXPECT_EQ(bksge::get<0>(t), 1.5);
		EXPECT_EQ(bksge::get<1>(t), "high");
		EXPECT_EQ(bksge::get<2>(t), 5);
		bksge::get<0>(t) = 2.5;
		EXPECT_EQ(bksge::get<0>(t), 2.5);
		EXPECT_EQ(bksge::get<1>(t), "high");
		EXPECT_EQ(bksge::get<2>(t), 5);
		EXPECT_EQ(d, 2.5);
	}
}

GTEST_TEST(TupleTest, GetConstRVTest)
{
	{
		typedef bksge::tuple<int> T;
		const T t(3);
		static_assert(bksge::is_same<const int&&, decltype(bksge::get<0>(bksge::move(t)))>::value, "");
		static_assert(noexcept(bksge::get<0>(bksge::move(t))), "");
		const int&& i = bksge::get<0>(bksge::move(t));
		EXPECT_EQ(i, 3);
	}

	{
		typedef bksge::tuple<std::string, int> T;
		const T t("high", 5);
		static_assert(bksge::is_same<const std::string&&, decltype(bksge::get<0>(bksge::move(t)))>::value, "");
		static_assert(noexcept(bksge::get<0>(bksge::move(t))), "");
		static_assert(bksge::is_same<const int&&, decltype(bksge::get<1>(bksge::move(t)))>::value, "");
		static_assert(noexcept(bksge::get<1>(bksge::move(t))), "");
		const std::string&& s = bksge::get<0>(bksge::move(t));
		const int&& i = bksge::get<1>(bksge::move(t));
		EXPECT_EQ(s, "high");
		EXPECT_EQ(i, 5);
	}

	{
		int x = 42;
		int const y = 43;
		bksge::tuple<int&, int const&> const p(x, y);
		static_assert(bksge::is_same<int&, decltype(bksge::get<0>(bksge::move(p)))>::value, "");
		static_assert(noexcept(bksge::get<0>(bksge::move(p))), "");
		static_assert(bksge::is_same<int const&, decltype(bksge::get<1>(bksge::move(p)))>::value, "");
		static_assert(noexcept(bksge::get<1>(bksge::move(p))), "");
	}

	{
		int x = 42;
		int const y = 43;
		bksge::tuple<int&&, int const&&> const p(bksge::move(x), bksge::move(y));
		static_assert(bksge::is_same<int&&, decltype(bksge::get<0>(bksge::move(p)))>::value, "");
		static_assert(noexcept(bksge::get<0>(bksge::move(p))), "");
		static_assert(bksge::is_same<int const&&, decltype(bksge::get<1>(bksge::move(p)))>::value, "");
		static_assert(noexcept(bksge::get<1>(bksge::move(p))), "");
	}

	{
		typedef bksge::tuple<double, int> T;
		BKSGE_CXX14_CONSTEXPR const T t(2.718, 5);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(bksge::move(t)), 2.718);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<1>(bksge::move(t)), 5);
	}
}

GTEST_TEST(TupleTest, GetNonConstTest)
{
	{
		typedef bksge::tuple<int> T;
		T t(3);
		EXPECT_EQ(bksge::get<0>(t), 3);
		bksge::get<0>(t) = 2;
		EXPECT_EQ(bksge::get<0>(t), 2);
	}
	{
		typedef bksge::tuple<std::string, int> T;
		T t("high", 5);
		EXPECT_EQ(bksge::get<0>(t), "high");
		EXPECT_EQ(bksge::get<1>(t), 5);
		bksge::get<0>(t) = "four";
		bksge::get<1>(t) = 4;
		EXPECT_EQ(bksge::get<0>(t), "four");
		EXPECT_EQ(bksge::get<1>(t), 4);
	}
	{
		typedef bksge::tuple<double&, std::string, int> T;
		double d = 1.5;
		T t(d, "high", 5);
		EXPECT_EQ(bksge::get<0>(t), 1.5);
		EXPECT_EQ(bksge::get<1>(t), "high");
		EXPECT_EQ(bksge::get<2>(t), 5);
		bksge::get<0>(t) = 2.5;
		bksge::get<1>(t) = "four";
		bksge::get<2>(t) = 4;
		EXPECT_EQ(bksge::get<0>(t), 2.5);
		EXPECT_EQ(bksge::get<1>(t), "four");
		EXPECT_EQ(bksge::get<2>(t), 4);
		EXPECT_EQ(d, 2.5);
	}
	{ // get on an rvalue tuple
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(bksge::make_tuple(0.0f, 1, 2.0, 3L)), 0);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<1>(bksge::make_tuple(0.0f, 1, 2.0, 3L)), 1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<2>(bksge::make_tuple(0.0f, 1, 2.0, 3L)), 2);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<3>(bksge::make_tuple(0.0f, 1, 2.0, 3L)), 3);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(S().k, 1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<1>(getP()), 4);
	}
}

GTEST_TEST(TupleTest, GetRVTest)
{
	typedef bksge::tuple<std::unique_ptr<int> > T;
	T t(std::unique_ptr<int>(new int(3)));
	std::unique_ptr<int> p = bksge::get<0>(bksge::move(t));
	EXPECT_EQ(*p, 3);
}

GTEST_TEST(TupleTest, GetByTypeTest)
{
	typedef std::complex<float> cf;
	{
		auto t1 = bksge::tuple<int, std::string, cf>{42, "Hi", {1, 2}};
		EXPECT_EQ(bksge::get<int>(t1), 42); // find at the beginning
		EXPECT_EQ(bksge::get<std::string>(t1), "Hi"); // find in the middle
		EXPECT_EQ(bksge::get<cf>(t1).real(), 1); // find at the end
		EXPECT_EQ(bksge::get<cf>(t1).imag(), 2);
	}

	{
		auto t2 = bksge::tuple<int, std::string, int, cf>{42, "Hi", 23, {1, 2}};
		//  get<int> would fail!
		EXPECT_EQ(bksge::get<std::string>(t2), "Hi");
		EXPECT_TRUE((bksge::get<cf>(t2) == cf{1, 2}));
	}

	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int, const int, double, double> p5{1, 2, 3.4, 5.6};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<int>(p5), 1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<const int>(p5), 2);
	}

	{
		const bksge::tuple<int, const int, double, double> p5{1, 2, 3.4, 5.6};
		const int &i1 = bksge::get<int>(p5);
		const int &i2 = bksge::get<const int>(p5);
		EXPECT_EQ(i1, 1);
		EXPECT_EQ(i2, 2);
	}

	{
		typedef std::unique_ptr<int> upint;
		bksge::tuple<upint> t(upint(new int(4)));
		upint p = bksge::get<upint>(bksge::move(t)); // get rvalue
		EXPECT_EQ(*p, 4);
		EXPECT_TRUE(bksge::get<upint>(t) == nullptr); // has been moved from
	}

	{
		typedef std::unique_ptr<int> upint;
		const bksge::tuple<upint> t(upint(new int(4)));
		const upint&& p = bksge::get<upint>(bksge::move(t)); // get const rvalue
		EXPECT_EQ(*p, 4);
		EXPECT_TRUE(bksge::get<upint>(t) != nullptr);
	}

	{
		int x = 42;
		int y = 43;
		bksge::tuple<int&, int const&> const t(x, y);
		static_assert(bksge::is_same<int&, decltype(bksge::get<int&>(bksge::move(t)))>::value, "");
		static_assert(noexcept(bksge::get<int&>(bksge::move(t))), "");
		static_assert(bksge::is_same<int const&, decltype(bksge::get<int const&>(bksge::move(t)))>::value, "");
		static_assert(noexcept(bksge::get<int const&>(bksge::move(t))), "");
	}

	{
		int x = 42;
		int y = 43;
		bksge::tuple<int&&, int const&&> const t(bksge::move(x), bksge::move(y));
		static_assert(bksge::is_same<int&&, decltype(bksge::get<int&&>(bksge::move(t)))>::value, "");
		static_assert(noexcept(bksge::get<int&&>(bksge::move(t))), "");
		static_assert(bksge::is_same<int const&&, decltype(bksge::get<int const&&>(bksge::move(t)))>::value, "");
		static_assert(noexcept(bksge::get<int const&&>(bksge::move(t))), "");
	}

	{
		BKSGE_CXX14_CONSTEXPR const bksge::tuple<int, const int, double, double> t{1, 2, 3.4, 5.6};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<int>(bksge::move(t)), 1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<const int>(bksge::move(t)), 2);
	}
}

}	// namespace get_test

}	// namespace bksge_tuple_test
