/**
 *	@file	unit_test_fnd_pair_u_v_ctor.cpp
 *
 *	@brief	pairのU型とV型を取るコンストラクタのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
//#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_u_v_ctor_test
{

struct ImplicitT
{
	BKSGE_CONSTEXPR ImplicitT(int x) : value(x) {}
	int value;
};

struct ExplicitT
{
	BKSGE_CONSTEXPR explicit ExplicitT(int x) : value(x) {}
	int value;
};

struct NothrowT
{
	BKSGE_CONSTEXPR NothrowT(int) noexcept {}
};

GTEST_TEST(PairTest, UVCtorTest)
{
	{
		static_assert( bksge::is_constructible<bksge::pair<int, float>, int, float>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<int, float>, char, int>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<int, ImplicitT>, float, int>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<ExplicitT, float>, int, float>::value, "");
		static_assert( bksge::is_constructible<bksge::pair<char, NothrowT>, char, int>::value, "");

		static_assert( bksge::is_implicitly_constructible<bksge::pair<int, float>, int, float>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<int, float>, char, int>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<int, ImplicitT>, float, int>::value, "");
		static_assert(!bksge::is_implicitly_constructible<bksge::pair<ExplicitT, float>, int, float>::value, "");
		static_assert( bksge::is_implicitly_constructible<bksge::pair<char, NothrowT>, char, int>::value, "");

		//static_assert( bksge::is_nothrow_constructible<bksge::pair<int, float>, int, float>::value, "");
		//static_assert( bksge::is_nothrow_constructible<bksge::pair<int, float>, char, int>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<int, ImplicitT>, float, int>::value, "");
		//static_assert(!bksge::is_nothrow_constructible<bksge::pair<ExplicitT, float>, int, float>::value, "");
		//static_assert( bksge::is_nothrow_constructible<bksge::pair<char, NothrowT>, char, int>::value, "");
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::pair<ImplicitT, int> p { 42, 43 };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, p.first.value);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(43, p.second);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::pair<ImplicitT, int> p = { 42, 43 };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, p.first.value);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(43, p.second);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::pair<ExplicitT, int> p { 42, 43 };
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, p.first.value);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(43, p.second);
	}
	//{
	//	BKSGE_CXX14_CONSTEXPR bksge::pair<ExplicitT, int> p = { 42, 43 };
	//	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(42, p.first.value);
	//	BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(43, p.second);
	//}
}

}	// namespace bksge_pair_u_v_ctor_test
