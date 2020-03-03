/**
 *	@file	unit_test_fnd_optional_ctor.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <vector>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4702)
BKSGE_WARNING_DISABLE_GCC("-Wunused-but-set-variable")

namespace bksge_optional_test
{

namespace ctor_test
{

struct tracker
{
	tracker(int value) : value(value) { ++count; }
	~tracker() { --count; }

	tracker(tracker const& other) : value(other.value) { ++count; }
	tracker(tracker&& other) : value(other.value)
	{
		other.value = -1;
		++count;
	}

	tracker& operator=(tracker const&) = default;
	tracker& operator=(tracker&& rhs)
	{
		value = rhs.value;
		return *this;
	}

	int value;

	static int count;
};

int tracker::count = 0;

struct exception {};

struct throwing_copy
{
	throwing_copy() = default;
	throwing_copy(throwing_copy const&) { throw exception{}; }
};

struct throwing_move
{
	throwing_move() = default;
	throwing_move(throwing_move&&) { throw exception{}; }
};

struct throwing_construction
{
	explicit throwing_construction(bool propagate) : propagate(propagate) {}

	throwing_construction(throwing_construction const& other)
		: propagate(other.propagate)
	{
		if (propagate)
		{
			throw exception{};
		}
	}

	bool propagate;
};

// [20.5.4.1] Constructors

GTEST_TEST(OptionalTest, DefaultCtorTest)
{
	{
		bksge::optional<tracker> o;
		EXPECT_TRUE(!o);
	}

	{
		bksge::optional<tracker> o{};
		EXPECT_TRUE(!o);
	}

	{
		bksge::optional<tracker> o = {};
		EXPECT_TRUE(!o);
	}

	{
		BKSGE_CONSTEXPR bksge::optional<int> o;
		BKSGE_CONSTEXPR_EXPECT_TRUE(!o);
	}

	{
		BKSGE_CONSTEXPR bksge::optional<int> o{};
		BKSGE_CONSTEXPR_EXPECT_TRUE(!o);
	}

	{
		BKSGE_CONSTEXPR bksge::optional<int> o = {};
		BKSGE_CONSTEXPR_EXPECT_TRUE(!o);
	}

	EXPECT_TRUE(tracker::count == 0);
}

GTEST_TEST(OptionalTest, CopyCtorTest)
{
	{
		bksge::optional<long> o;
		auto copy = o;
		EXPECT_TRUE(!copy);
		EXPECT_TRUE(!o);
	}

	{
		const long val = 0x1234ABCD;
		bksge::optional<long> o{ bksge::in_place, val };
		auto copy = o;
		EXPECT_TRUE((bool)copy);
		EXPECT_TRUE(*copy == val);
		EXPECT_TRUE(o && o == val);
	}

	{
		bksge::optional<tracker> o;
		auto copy = o;
		EXPECT_TRUE(!copy);
		EXPECT_TRUE(tracker::count == 0);
		EXPECT_TRUE(!o);
	}

	{
		bksge::optional<tracker> o{ bksge::in_place, 333 };
		auto copy = o;
		EXPECT_TRUE((bool)copy);
		EXPECT_TRUE(copy->value == 333);
		EXPECT_TRUE(tracker::count == 2);
		EXPECT_TRUE(o && o->value == 333);
	}

	{
		bksge::optional<throwing_copy> o;
		EXPECT_NO_THROW(auto copy = o);
	}
	{
		bksge::optional<throwing_copy> o{ bksge::in_place };
		EXPECT_THROW(auto copy = o, exception);
	}

	EXPECT_TRUE(tracker::count == 0);
}

GTEST_TEST(OptionalTest, MoveCtorTest)
{
	{
		bksge::optional<long> o;
		auto moved_to = bksge::move(o);
		EXPECT_TRUE(!moved_to);
		EXPECT_TRUE(!o);
	}

	{
		const long val = 0x1234ABCD;
		bksge::optional<long> o{ bksge::in_place, val };
		auto moved_to = bksge::move(o);
		EXPECT_TRUE((bool)moved_to);
		EXPECT_TRUE(*moved_to == val);
		EXPECT_TRUE(o && *o == val);
	}

	{
		bksge::optional<tracker> o;
		auto moved_to = bksge::move(o);
		EXPECT_TRUE(!moved_to);
		EXPECT_TRUE(tracker::count == 0);
		EXPECT_TRUE(!o);
	}

	{
		bksge::optional<tracker> o{ bksge::in_place, 333 };
		auto moved_to = bksge::move(o);
		EXPECT_TRUE((bool)moved_to);
		EXPECT_TRUE(moved_to->value == 333);
		EXPECT_TRUE(tracker::count == 2);
		EXPECT_TRUE(o && o->value == -1);
	}

	{
		bksge::optional<throwing_move> o;
		EXPECT_NO_THROW(auto moved_to = bksge::move(o));
	}
	{
		bksge::optional<throwing_move> o{ bksge::in_place };
		EXPECT_THROW(auto moved_to = bksge::move(o), exception);
	}

	EXPECT_TRUE(tracker::count == 0);
}

GTEST_TEST(OptionalTest, ValueCtorTest)
{
	{
		BKSGE_CONSTEXPR auto i = 0x1234ABCD;
		BKSGE_CONSTEXPR bksge::optional<long> o{ i };
		BKSGE_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_CONSTEXPR_EXPECT_TRUE(*o == 0x1234ABCD);
		BKSGE_CONSTEXPR_EXPECT_TRUE(i == 0x1234ABCD);
	}

	{
		BKSGE_CONSTEXPR auto i = 0x1234ABCD;
		BKSGE_CONSTEXPR bksge::optional<long> o( i );
		BKSGE_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_CONSTEXPR_EXPECT_TRUE(*o == 0x1234ABCD);
		BKSGE_CONSTEXPR_EXPECT_TRUE(i == 0x1234ABCD);
	}

	{
		BKSGE_CONSTEXPR auto i = 0x1234ABCD;
		bksge::optional<long> o = i;	// TODO 何故かconstexprにできない
		EXPECT_TRUE((bool)o);
		EXPECT_TRUE(*o == 0x1234ABCD);
		EXPECT_TRUE(i == 0x1234ABCD);
	}

	{
		BKSGE_CONSTEXPR auto i = 0x1234ABCD;
		BKSGE_CONSTEXPR bksge::optional<long> o = { i };
		BKSGE_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_CONSTEXPR_EXPECT_TRUE(*o == 0x1234ABCD);
		BKSGE_CONSTEXPR_EXPECT_TRUE(i == 0x1234ABCD);
	}

	{
		BKSGE_CONSTEXPR auto i = 0x1234ABCD;
		BKSGE_CONSTEXPR bksge::optional<long> o{ bksge::move(i) };
		BKSGE_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_CONSTEXPR_EXPECT_TRUE(*o == 0x1234ABCD);
		BKSGE_CONSTEXPR_EXPECT_TRUE(i == 0x1234ABCD);
	}

	{
		BKSGE_CONSTEXPR auto i = 0x1234ABCD;
		BKSGE_CONSTEXPR bksge::optional<long> o( bksge::move(i) );
		BKSGE_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_CONSTEXPR_EXPECT_TRUE(*o == 0x1234ABCD);
		BKSGE_CONSTEXPR_EXPECT_TRUE(i == 0x1234ABCD);
	}

	{
		BKSGE_CONSTEXPR auto i = 0x1234ABCD;
		bksge::optional<long> o = bksge::move(i);	// TODO 何故かconstexprにできない
		EXPECT_TRUE((bool)o);
		EXPECT_TRUE(*o == 0x1234ABCD);
		EXPECT_TRUE(i == 0x1234ABCD);
	}

	{
		BKSGE_CONSTEXPR auto i = 0x1234ABCD;
		BKSGE_CONSTEXPR bksge::optional<long> o = { bksge::move(i) };
		BKSGE_CONSTEXPR_EXPECT_TRUE((bool)o);
		BKSGE_CONSTEXPR_EXPECT_TRUE(*o == 0x1234ABCD);
		BKSGE_CONSTEXPR_EXPECT_TRUE(i == 0x1234ABCD);
	}

	{
		std::vector<int> v = { 0, 1, 2, 3, 4, 5 };
		bksge::optional<std::vector<int>> o{ v };
		EXPECT_TRUE(!v.empty());
		EXPECT_TRUE(o->size() == 6);
	}

	{
		std::vector<int> v = { 0, 1, 2, 3, 4, 5 };
		bksge::optional<std::vector<int>> o = v;
		EXPECT_TRUE(!v.empty());
		EXPECT_TRUE(o->size() == 6);
	}

	{
		std::vector<int> v = { 0, 1, 2, 3, 4, 5 };
		bksge::optional<std::vector<int>> o{ v };
		EXPECT_TRUE(!v.empty());
		EXPECT_TRUE(o->size() == 6);
	}

	{
		std::vector<int> v = { 0, 1, 2, 3, 4, 5 };
		bksge::optional<std::vector<int>> o{ bksge::move(v) };
		EXPECT_TRUE(v.empty());
		EXPECT_TRUE(o->size() == 6);
	}

	{
		std::vector<int> v = { 0, 1, 2, 3, 4, 5 };
		bksge::optional<std::vector<int>> o = bksge::move(v);
		EXPECT_TRUE(v.empty());
		EXPECT_TRUE(o->size() == 6);
	}

	{
		std::vector<int> v = { 0, 1, 2, 3, 4, 5 };
		bksge::optional<std::vector<int>> o{ bksge::move(v) };
		EXPECT_TRUE(v.empty());
		EXPECT_TRUE(o->size() == 6);
	}

	{
		tracker t{ 333 };
		bksge::optional<tracker> o = t;
		EXPECT_TRUE(o->value == 333);
		EXPECT_TRUE(tracker::count == 2);
		EXPECT_TRUE(t.value == 333);
	}

	{
		tracker t{ 333 };
		bksge::optional<tracker> o = bksge::move(t);
		EXPECT_TRUE(o->value == 333);
		EXPECT_TRUE(tracker::count == 2);
		EXPECT_TRUE(t.value == -1);
	}

	{
		throwing_construction t{ false };
		EXPECT_NO_THROW(bksge::optional<throwing_construction> o{ t });
	}
	{
		throwing_construction t{ true };
		EXPECT_THROW(bksge::optional<throwing_construction> o{ t }, exception);
	}
	{
		throwing_construction t{ false };
		EXPECT_NO_THROW(bksge::optional<throwing_construction> o{ bksge::move(t) });
	}
	{
		throwing_construction t{ true };
		EXPECT_THROW(bksge::optional<throwing_construction> o{ bksge::move(t) }, exception);
	}
}

}	// namespace ctor_test

}	// namespace bksge_optional_test

BKSGE_WARNING_POP()
