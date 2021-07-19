/**
 *	@file	unit_test_fnd_optional_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_optional_test
{

namespace swap_test
{

int counter = 0;

struct mixin_counter
{
	mixin_counter() { ++counter; }
	mixin_counter(mixin_counter const&) { ++counter; }
	~mixin_counter() { --counter; }
};

struct value_type : private mixin_counter
{
	explicit value_type(int state) : state(state) {}
	int state;
};

int swaps = 0;

inline void swap(value_type& lhs, value_type& rhs)
{
	++swaps;
	using std::swap;
	swap(lhs.state, rhs.state);
}

GTEST_TEST(OptionalTest, SwapTest)
{
	using O = bksge::optional<value_type>;

	EXPECT_TRUE(swaps == 0);

	{
		O o;
		O p;
		swap(o, p);
		EXPECT_TRUE(!o);
		EXPECT_TRUE(!p);
	}

	{
		O o{ bksge::in_place, 45 };
		O p;
		swap(o, p);
		EXPECT_TRUE(!o);
		EXPECT_TRUE(p && p->state == 45);
	}

	{
		O o;
		O p{ bksge::in_place, 45 };
		swap(o, p);
		EXPECT_TRUE(o && o->state == 45);
		EXPECT_TRUE(!p);
	}

	{
		O o{ bksge::in_place, 167 };
		O p{ bksge::in_place, 999 };
		EXPECT_TRUE(swaps == 0);

		swap(o, p);

		EXPECT_TRUE(o && o->state == 999);
		EXPECT_TRUE(p && p->state == 167);
		EXPECT_TRUE(swaps == 1);
	}

	EXPECT_TRUE(counter == 0);
}

}	// namespace swap_test

}	// namespace bksge_optional_test
