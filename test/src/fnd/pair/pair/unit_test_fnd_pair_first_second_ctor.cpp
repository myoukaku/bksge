/**
 *	@file	unit_test_fnd_pair_first_second_ctor.cpp
 *
 *	@brief	pairのfirst_typeとsecond_typeを取るコンストラクタのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
//#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_first_second_ctor_test
{

struct ImplicitT
{
	BKSGE_CONSTEXPR ImplicitT(int x) : value(x) {}
	BKSGE_CONSTEXPR ImplicitT(ImplicitT const& o) : value(o.value) {}
	int value;
};

struct ExplicitT
{
	BKSGE_CONSTEXPR explicit ExplicitT(int x) : value(x) {}
	BKSGE_CONSTEXPR explicit ExplicitT(ExplicitT const& o) : value(o.value) {}
	int value;
};

struct NothrowT
{
	BKSGE_CONSTEXPR NothrowT(int) noexcept {}
	BKSGE_CONSTEXPR NothrowT(NothrowT const&) noexcept {}
};

GTEST_TEST(PairTest, FirstSecondCtorTest)
{
	{
		static_assert( bksge::is_constructible<bksge::pair<int, float>, int       const&, float const&>::value, "");
		static_assert(!bksge::is_constructible<bksge::pair<int, float>, int       const&>::value, "");
		static_assert(!bksge::is_constructible<bksge::pair<int, float>, ImplicitT const&, float const&>::value, "");
		static_assert(!bksge::is_constructible<bksge::pair<int, float>, ExplicitT const&, float const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<ImplicitT, float>, int       const&, float const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<ImplicitT, float>, ImplicitT const&, float const&>::value, "");
		static_assert(!bksge::is_constructible<bksge::pair<ImplicitT, float>, ExplicitT const&, float const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<ExplicitT, float>, int       const&, float const&>::value, "");
		static_assert(!bksge::is_constructible<bksge::pair<ExplicitT, float>, ImplicitT const&, float const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<ExplicitT, float>, ExplicitT const&, float const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<NothrowT,  float>, int       const&, float const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<NothrowT,  float>, NothrowT  const&, float const&>::value, "");
		static_assert(!bksge::is_constructible<bksge::pair<NothrowT,  float>, ExplicitT const&, float const&>::value, "");

		static_assert( bksge::is_implicitly_constructible<bksge::pair<int, float>, int       const&, float const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<int, float>, int       const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<int, float>, ImplicitT const&, float const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<int, float>, ExplicitT const&, float const&>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<ImplicitT, float>, int       const&, float const&>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<ImplicitT, float>, ImplicitT const&, float const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<ImplicitT, float>, ExplicitT const&, float const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<ExplicitT, float>, int       const&, float const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<ExplicitT, float>, ImplicitT const&, float const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<ExplicitT, float>, ExplicitT const&, float const&>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<NothrowT,  float>, int       const&, float const&>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<NothrowT,  float>, NothrowT  const&, float const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<NothrowT,  float>, ExplicitT const&, float const&>::value, "");

		//static_assert( bksge::is_nothrow_constructible<bksge::pair<int, float>, int       const&, float const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<int, float>, int       const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<int, float>, ImplicitT const&, float const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<int, float>, ExplicitT const&, float const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<ImplicitT, float>, int       const&, float const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<ImplicitT, float>, ImplicitT const&, float const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<ImplicitT, float>, ExplicitT const&, float const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<ExplicitT, float>, int       const&, float const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<ExplicitT, float>, ImplicitT const&, float const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<ExplicitT, float>, ExplicitT const&, float const&>::value, "");
		//static_assert( bksge::is_nothrow_constructible<bksge::pair<NothrowT,  float>, int       const&, float const&>::value, "");
		//static_assert( bksge::is_nothrow_constructible<bksge::pair<NothrowT,  float>, NothrowT  const&, float const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<NothrowT,  float>, ExplicitT const&, float const&>::value, "");
	}
	{
		BKSGE_CXX14_CONSTEXPR int n = 2;
		BKSGE_CXX14_CONSTEXPR double d = 2.5;
		BKSGE_CXX14_CONSTEXPR bksge::pair<int, double> p(n, d);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(2,   p.first);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(2.5, p.second);
	}
	{
		BKSGE_CXX14_CONSTEXPR float f = 0.5f;
		BKSGE_CXX14_CONSTEXPR short* sp = nullptr;
		BKSGE_CXX14_CONSTEXPR bksge::pair<float, short*> p = { f, sp };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(0.5f,    p.first);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(nullptr, p.second);
	}
	{
		BKSGE_CXX14_CONSTEXPR ImplicitT e(42);
		BKSGE_CXX14_CONSTEXPR int x = 10;
		BKSGE_CXX14_CONSTEXPR bksge::pair<ImplicitT, int> p { e, x };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, p.first.value);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(10, p.second);
	}
	{
		BKSGE_CXX14_CONSTEXPR ImplicitT e(42);
		BKSGE_CXX14_CONSTEXPR int x = 10;
		BKSGE_CXX14_CONSTEXPR bksge::pair<ImplicitT, int> p = { e, x };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, p.first.value);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(10, p.second);
	}
	{
		BKSGE_CXX14_CONSTEXPR ExplicitT e(42);
		BKSGE_CXX14_CONSTEXPR int x = 10;
		BKSGE_CXX14_CONSTEXPR bksge::pair<ExplicitT, int> p { e, x };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, p.first.value);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(10, p.second);
	}
	//{
	//	BKSGE_CXX14_CONSTEXPR ExplicitT e(42);
	//	BKSGE_CXX14_CONSTEXPR int x = 10;
	//	BKSGE_CXX14_CONSTEXPR bksge::pair<ExplicitT, int> p = { e, x };
	//	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, p.first.value);
	//	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(10, p.second);
	//}
}

}	// namespace bksge_pair_first_second_ctor_test
