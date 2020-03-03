/**
 *	@file	unit_test_fnd_pair_default_ctor.cpp
 *
 *	@brief	pairのデフォルトコンストラクタのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
//#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_default_ctor_test
{

struct NoDefault
{
	NoDefault() = delete;
};

struct ImplicitDefault
{
	BKSGE_CONSTEXPR ImplicitDefault() : value(42) {}
	int value;
};

struct ExplicitDefault
{
	explicit BKSGE_CONSTEXPR ExplicitDefault() : value(42) {}
	int value;
};

struct NothrowDefault
{
	NothrowDefault() noexcept {}
};

GTEST_TEST(PairTest, DefaultCtorTest)
{
	{
        static_assert( bksge::is_default_constructible<bksge::pair<int, float>>::value, "");
        static_assert(!bksge::is_default_constructible<bksge::pair<int, NoDefault>>::value, "");
        static_assert( bksge::is_default_constructible<bksge::pair<int, ImplicitDefault>>::value, "");
        static_assert( bksge::is_default_constructible<bksge::pair<int, ExplicitDefault>>::value, "");
        static_assert( bksge::is_default_constructible<bksge::pair<int, NothrowDefault>>::value, "");
        static_assert(!bksge::is_default_constructible<bksge::pair<NoDefault, int>>::value, "");
        static_assert( bksge::is_default_constructible<bksge::pair<ImplicitDefault, int>>::value, "");
        static_assert( bksge::is_default_constructible<bksge::pair<ExplicitDefault, int>>::value, "");
        static_assert( bksge::is_default_constructible<bksge::pair<NothrowDefault, int>>::value, "");

        static_assert( bksge::is_implicitly_default_constructible<bksge::pair<int, float>>::value, "");
        static_assert(!bksge::is_implicitly_default_constructible<bksge::pair<int, NoDefault>>::value, "");
        static_assert( bksge::is_implicitly_default_constructible<bksge::pair<int, ImplicitDefault>>::value, "");
        static_assert(!bksge::is_implicitly_default_constructible<bksge::pair<int, ExplicitDefault>>::value, "");
        static_assert( bksge::is_implicitly_default_constructible<bksge::pair<int, NothrowDefault>>::value, "");
        static_assert(!bksge::is_implicitly_default_constructible<bksge::pair<NoDefault, int>>::value, "");
        static_assert( bksge::is_implicitly_default_constructible<bksge::pair<ImplicitDefault, int>>::value, "");
        static_assert(!bksge::is_implicitly_default_constructible<bksge::pair<ExplicitDefault, int>>::value, "");
        static_assert( bksge::is_implicitly_default_constructible<bksge::pair<NothrowDefault, int>>::value, "");

        //static_assert( bksge::is_nothrow_default_constructible<bksge::pair<int, float>>::value, "");
        //static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<int, NoDefault>>::value, "");
        //static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<int, ImplicitDefault>>::value, "");
        //static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<int, ExplicitDefault>>::value, "");
        //static_assert( bksge::is_nothrow_default_constructible<bksge::pair<int, NothrowDefault>>::value, "");
        //static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<NoDefault, int>>::value, "");
        //static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<ImplicitDefault, int>>::value, "");
        //static_assert(!bksge::is_nothrow_default_constructible<bksge::pair<ExplicitDefault, int>>::value, "");
        //static_assert( bksge::is_nothrow_default_constructible<bksge::pair<NothrowDefault, int>>::value, "");
	}
	{
		BKSGE_CONSTEXPR bksge::pair<int, double> p;
		BKSGE_CONSTEXPR_EXPECT_EQ(0,   p.first);
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0, p.second);
	}
	{
		BKSGE_CONSTEXPR bksge::pair<float, short*> p;
		BKSGE_CONSTEXPR_EXPECT_EQ(0.0f,    p.first);
		BKSGE_CONSTEXPR_EXPECT_EQ(nullptr, p.second);
	}
	{
		BKSGE_CONSTEXPR bksge::pair<ImplicitDefault, ImplicitDefault> p;
		BKSGE_CONSTEXPR_EXPECT_EQ(42, p.first.value);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, p.second.value);
	}
	{
		BKSGE_CONSTEXPR bksge::pair<ImplicitDefault, ImplicitDefault> p = {};
		BKSGE_CONSTEXPR_EXPECT_EQ(42, p.first.value);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, p.second.value);
	}
	{
		BKSGE_CONSTEXPR bksge::pair<ExplicitDefault, ExplicitDefault> p;
		BKSGE_CONSTEXPR_EXPECT_EQ(42, p.first.value);
		BKSGE_CONSTEXPR_EXPECT_EQ(42, p.second.value);
	}
	//{
	//	BKSGE_CONSTEXPR bksge::pair<ExplicitDefault, ExplicitDefault> p = {};
	//	BKSGE_CONSTEXPR_EXPECT_EQ(42, p.first.value);
	//	BKSGE_CONSTEXPR_EXPECT_EQ(42, p.second.value);
	//}
}

}	// namespace bksge_pair_default_ctor_test
