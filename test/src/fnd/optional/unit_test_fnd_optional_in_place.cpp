/**
 *	@file	unit_test_fnd_optional_in_place.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_empty.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

#if defined(_MSC_VER)
#define BKSGE_OPTIONAL_CONSTEXPR
#define BKSGE_OPTIONAL_CONSTEXPR_EXPECT_TRUE    EXPECT_TRUE
#define BKSGE_OPTIONAL_CONSTEXPR_EXPECT_FALSE   EXPECT_FALSE
#else
#define BKSGE_OPTIONAL_CONSTEXPR                BKSGE_CONSTEXPR
#define BKSGE_OPTIONAL_CONSTEXPR_EXPECT_TRUE    BKSGE_CONSTEXPR_EXPECT_TRUE
#define BKSGE_OPTIONAL_CONSTEXPR_EXPECT_FALSE   BKSGE_CONSTEXPR_EXPECT_FALSE
#endif

GTEST_TEST(OptionalTest, InPlaceTest)
{
	// [20.5.5] In-place construction
	static_assert(bksge::is_same<decltype(bksge::in_place), const bksge::in_place_t>::value, "");
	static_assert(bksge::is_empty<bksge::in_place_t>::value, "");

	{
		BKSGE_OPTIONAL_CONSTEXPR bksge::optional<int> o{ bksge::in_place };
		BKSGE_OPTIONAL_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_OPTIONAL_CONSTEXPR_EXPECT_TRUE(*o == int());

		static_assert(!bksge::is_convertible<bksge::in_place_t, bksge::optional<int>>::value, "");
	}

	{
		BKSGE_CONSTEXPR bksge::optional<int> o{ bksge::in_place, 42 };
		BKSGE_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_CONSTEXPR_EXPECT_TRUE(*o == 42);
	}

	{
		bksge::optional<std::vector<int>> o{ bksge::in_place, 18, 4 };
		EXPECT_TRUE((bool)o);
		EXPECT_TRUE(o->size() == 18);
		EXPECT_TRUE((*o)[17] == 4);
	}

	{
		bksge::optional<std::vector<int>> o{ bksge::in_place, { 18, 4 } };
		EXPECT_TRUE((bool)o);
		EXPECT_TRUE(o->size() == 2);
		EXPECT_TRUE((*o)[0] == 18);
	}

	{
		bksge::optional<std::vector<int>> o{ bksge::in_place, { 18, 4 }, std::allocator<int> {} };
		EXPECT_TRUE((bool)o);
		EXPECT_TRUE(o->size() == 2);
		EXPECT_TRUE((*o)[0] == 18);
	}
}

#undef BKSGE_OPTIONAL_CONSTEXPR
#undef BKSGE_OPTIONAL_CONSTEXPR_EXPECT_TRUE
#undef BKSGE_OPTIONAL_CONSTEXPR_EXPECT_FALSE
