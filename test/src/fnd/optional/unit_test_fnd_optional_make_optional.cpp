/**
 *	@file	unit_test_fnd_optional_make_optional.cpp
 *
 *	@brief	make_optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/make_optional.hpp>
#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_optional_test
{

namespace make_optional_test
{

struct combined
{
	std::vector<int> v;
	bksge::tuple<int, int> t;

	template<class... Args>
	combined(std::initializer_list<int> il, Args&&... args)
		: v(il), t(bksge::forward<Args>(args)...)
	{
	}
};

GTEST_TEST(OptionalTest, MakeOptionalTest)
{
	using std::get;
	{
		const int i = 42;
		auto o = bksge::make_optional(i);
		static_assert(bksge::is_same<decltype(o), bksge::optional<int>>(), "");
		EXPECT_TRUE(o && *o == 42);
		EXPECT_TRUE(&*o != &i);
		auto o2 = bksge::make_optional<bksge::tuple<int, int>>(1, 2);
		static_assert(bksge::is_same<decltype(o2), bksge::optional<bksge::tuple<int, int>>>(), "");
		EXPECT_TRUE(o2 && get<0>(*o2) == 1 && get<1>(*o2) == 2);
		auto o3 = bksge::make_optional<std::vector<int>>({42, 666});
		static_assert(bksge::is_same<decltype(o3), bksge::optional<std::vector<int>>>(), "");
		EXPECT_TRUE(o3 && (*o3)[0] == 42 && (*o3)[1] == 666);
		auto o4 = bksge::make_optional<combined>({42, 666});
		static_assert(bksge::is_same<decltype(o4), bksge::optional<combined>>(), "");
		EXPECT_TRUE(o4 && (o4->v)[0] == 42 && (o4->v)[1] == 666 &&
			get<0>(o4->t) == 0 && get<1>(o4->t) == 0);
		auto o5 = bksge::make_optional<combined>({1, 2}, 3, 4);
		static_assert(bksge::is_same<decltype(o5), bksge::optional<combined>>(), "");
		EXPECT_TRUE(o4 && (o5->v)[0] == 1 && (o5->v)[1] == 2 &&
			get<0>(o5->t) == 3 && get<1>(o5->t) == 4);
	}
	{
		BKSGE_CONSTEXPR int i = 42;
		BKSGE_CONSTEXPR auto o = bksge::make_optional(i);
		static_assert(bksge::is_same<decltype(o), const bksge::optional<int>>::value, "");
		BKSGE_CONSTEXPR_EXPECT_TRUE(o && *o == 42);
		BKSGE_CONSTEXPR_EXPECT_TRUE(&*o != &i);
	}
}

}	// namespace make_optional_test

}	// namespace bksge_optional_test
