/**
 *	@file	unit_test_fnd_optional_in_place.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/memory/allocator.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_empty.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(OptionalTest, InPlaceTest)
{
	// [20.5.5] In-place construction

	{
		BKSGE_CONSTEXPR bksge::optional<int> o{ bksge::in_place };
		BKSGE_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_CONSTEXPR_EXPECT_TRUE(*o == int());

		static_assert(!bksge::is_convertible<bksge::in_place_t, bksge::optional<int>>::value, "");
	}

	{
		BKSGE_CONSTEXPR bksge::optional<int> o{ bksge::in_place, 42 };
		BKSGE_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_CONSTEXPR_EXPECT_TRUE(*o == 42);
	}

	{
		bksge::optional<bksge::vector<int>> o{ bksge::in_place, 18, 4 };
		EXPECT_TRUE((bool)o);
		EXPECT_TRUE(o->size() == 18);
		EXPECT_TRUE((*o)[ 0] == 4);
		EXPECT_TRUE((*o)[17] == 4);
	}

	{
		bksge::optional<bksge::vector<int>> o{ bksge::in_place, { 18, 4 } };
		EXPECT_TRUE((bool)o);
		EXPECT_TRUE(o->size() == 2);
		EXPECT_TRUE((*o)[0] == 18);
		EXPECT_TRUE((*o)[1] ==  4);
	}

	{
		bksge::optional<bksge::vector<int>> o{ bksge::in_place, { 18, 4 }, bksge::allocator<int> {} };
		EXPECT_TRUE((bool)o);
		EXPECT_TRUE(o->size() == 2);
		EXPECT_TRUE((*o)[0] == 18);
		EXPECT_TRUE((*o)[1] ==  4);
	}
}
