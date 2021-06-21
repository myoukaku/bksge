/**
 *	@file	unit_test_fnd_optional_emplace.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace bksge_optional_test
{

namespace emplace_test
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
	value_type() = default;
	value_type(int) : state(1) {}
	value_type(std::initializer_list<char>, char const*) : state(2) {}
	int state = 0;
};

GTEST_TEST(OptionalTest, EmplaceTest)
{
	using O = bksge::optional<value_type>;

	counter = 0;

	// Check emplace

	{
		O o;
		o.emplace();
		EXPECT_TRUE(o && o->state == 0);
	}
	{
		O o{ bksge::in_place, 0 };
		o.emplace();
		EXPECT_TRUE(o && o->state == 0);
	}

	{
		O o;
		o.emplace(0);
		EXPECT_TRUE(o && o->state == 1);
	}
	{
		O o{ bksge::in_place };
		o.emplace(0);
		EXPECT_TRUE(o && o->state == 1);
	}

	{
		O o;
		o.emplace({ 'a' }, "");
		EXPECT_TRUE(o && o->state == 2);
	}
	{
		O o{ bksge::in_place };
		o.emplace({ 'a' }, "");
		EXPECT_TRUE(o && o->state == 2);
	}

	static_assert(!bksge::is_constructible<O, std::initializer_list<int>, int>::value, "");

	EXPECT_EQ(0, counter);
}

}	// namespace emplace_test

}	// namespace bksge_optional_test
