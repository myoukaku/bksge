/**
 *	@file	unit_test_fnd_pair_const_pair_u_v_ctor.cpp
 *
 *	@brief	pairの pair<U,V> const& を取るコンストラクタのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
//#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_const_pair_u_v_ctor
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
};

GTEST_TEST(PairTest, ConstPairUVCtorTest)
{
	{
		static_assert( bksge::is_constructible<bksge::pair<int, float>, bksge::pair<int, float> const&>::value, "");
		static_assert(!bksge::is_constructible<bksge::pair<int, float>, bksge::pair<int, ImplicitT> const&>::value, "");
		static_assert(!bksge::is_constructible<bksge::pair<int, float>, bksge::pair<ExplicitT, float> const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<ImplicitT, float>, bksge::pair<int, float> const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<int, ImplicitT>, bksge::pair<int, float> const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<ExplicitT, float>, bksge::pair<int, float> const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<int, ExplicitT>, bksge::pair<int, float> const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<NothrowT, float>, bksge::pair<int, float> const&>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<int, NothrowT>, bksge::pair<int, float> const&>::value, "");

		static_assert( bksge::is_implicitly_constructible<bksge::pair<int, float>, bksge::pair<int, float> const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<int, float>, bksge::pair<int, ImplicitT> const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<int, float>, bksge::pair<ExplicitT, float> const&>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<ImplicitT, float>, bksge::pair<int, float> const&>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<int, ImplicitT>, bksge::pair<int, float> const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<ExplicitT, float>, bksge::pair<int, float> const&>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<int, ExplicitT>, bksge::pair<int, float> const&>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<NothrowT, float>, bksge::pair<int, float> const&>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<int, NothrowT>, bksge::pair<int, float> const&>::value, "");

		//static_assert( bksge::is_nothrow_constructible<bksge::pair<int, float>, bksge::pair<int, float> const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<int, float>, bksge::pair<int, ImplicitT> const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<int, float>, bksge::pair<ExplicitT, float> const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<ImplicitT, float>, bksge::pair<int, float> const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<int, ImplicitT>, bksge::pair<int, float> const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<ExplicitT, float>, bksge::pair<int, float> const&>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<int, ExplicitT>, bksge::pair<int, float> const&>::value, "");
		//static_assert( bksge::is_nothrow_constructible<bksge::pair<NothrowT, float>, bksge::pair<int, float> const&>::value, "");
		//static_assert( bksge::is_nothrow_constructible<bksge::pair<int, NothrowT>, bksge::pair<int, float> const&>::value, "");
	}
	{
		bksge::pair<int, int> p1 { 3, 4 };
		bksge::pair<ImplicitT, ImplicitT> p2 { p1 };
		EXPECT_EQ(3, p2.first.value);
		EXPECT_EQ(4, p2.second.value);
	}
	{
		bksge::pair<int, int> p1 { 3, 4 };
		bksge::pair<ImplicitT, ImplicitT> p2 = { p1 };
		EXPECT_EQ(3, p2.first.value);
		EXPECT_EQ(4, p2.second.value);
	}
	{
		bksge::pair<int, int> p1 { 3, 4 };
		bksge::pair<ExplicitT, ExplicitT> p2 { p1 };
		EXPECT_EQ(3, p2.first.value);
		EXPECT_EQ(4, p2.second.value);
	}
	//{
	//	bksge::pair<int, int> p1 { 3, 4 };
	//	bksge::pair<ExplicitT, ExplicitT> p2 = { p1 };
	//	EXPECT_EQ(3, p2.first.value);
	//	EXPECT_EQ(4, p2.second.value);
	//}
	{
		BKSGE_CXX14_CONSTEXPR bksge::pair<int, int> p1 { 3, 4 };
		BKSGE_CXX14_CONSTEXPR bksge::pair<ImplicitT, ImplicitT> p2 { p1 };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, p2.first.value);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, p2.second.value);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::pair<int, int> p1 { 3, 4 };
		BKSGE_CXX14_CONSTEXPR bksge::pair<ImplicitT, ImplicitT> p2 = { p1 };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, p2.first.value);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, p2.second.value);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::pair<int, int> p1 { 3, 4 };
		BKSGE_CXX14_CONSTEXPR bksge::pair<ExplicitT, ExplicitT> p2 { p1 };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, p2.first.value);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, p2.second.value);
	}
	//{
	//	BKSGE_CXX14_CONSTEXPR bksge::pair<int, int> p1 { 3, 4 };
	//	BKSGE_CXX14_CONSTEXPR bksge::pair<ExplicitT, ExplicitT> p2 = { p1 };
	//	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(3, p2.first.value);
	//	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(4, p2.second.value);
	//}
}

}	// namespace bksge_pair_const_pair_u_v_ctor
