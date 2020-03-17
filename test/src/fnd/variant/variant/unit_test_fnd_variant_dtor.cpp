/**
 *	@file	unit_test_fnd_variant_dtor.cpp
 *
 *	@brief	~variant() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"

namespace bksge_variant_test
{

namespace dtor_test
{

struct NonTDtor
{
	static int count;
	NonTDtor() = default;
	~NonTDtor() { ++count; }
};

int NonTDtor::count = 0;
static_assert(!bksge::is_trivially_destructible<NonTDtor>::value, "");

struct NonTDtor1
{
	static int count;
	NonTDtor1() = default;
	~NonTDtor1() { ++count; }
};

int NonTDtor1::count = 0;
static_assert(!bksge::is_trivially_destructible<NonTDtor1>::value, "");

struct TDtor
{
	TDtor(const TDtor&) {} // non-trivial copy
	~TDtor() = default;
};

static_assert(!bksge::is_trivially_copy_constructible<TDtor>::value, "");
static_assert(bksge::is_trivially_destructible<TDtor>::value, "");

GTEST_TEST(VariantTest, DtorTest)
{
	{
		using V = bksge::variant<int, long, TDtor>;
		static_assert(bksge::is_trivially_destructible<V>::value, "");
	}
	{
		using V = bksge::variant<NonTDtor, int, NonTDtor1>;
		static_assert(!bksge::is_trivially_destructible<V>::value, "");
		{
			V v(bksge::in_place_index_t<0>{});
			EXPECT_EQ(NonTDtor::count, 0);
			EXPECT_EQ(NonTDtor1::count, 0);
		}
		EXPECT_EQ(NonTDtor::count, 1);
		EXPECT_EQ(NonTDtor1::count, 0);
		NonTDtor::count = 0;
		{
			V v(bksge::in_place_index_t<1>{});
		}
		EXPECT_EQ(NonTDtor::count, 0);
		EXPECT_EQ(NonTDtor1::count, 0);
		{
			V v(bksge::in_place_index_t<2>{});
			EXPECT_EQ(NonTDtor::count, 0);
			EXPECT_EQ(NonTDtor1::count, 0);
		}
		EXPECT_EQ(NonTDtor::count, 0);
		EXPECT_EQ(NonTDtor1::count, 1);
	}
}

}	// namespace dtor_test

}	// namespace bksge_variant_test
