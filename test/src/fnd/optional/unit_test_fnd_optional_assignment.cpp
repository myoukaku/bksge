/**
 *	@file	unit_test_fnd_optional_assignment.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/optional/nullopt.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace bksge_optional_test
{

namespace assignment_test
{

struct exception {};

int counter = 0;

struct mixin_counter
{
	mixin_counter() { ++counter; }
	mixin_counter(mixin_counter const&) { ++counter; }
	~mixin_counter() { --counter; }
};

struct value_type : private mixin_counter
{
	enum state_type
	{
		zero,
		moved_from,
		throwing_construction,
		throwing_copy,
		throwing_copy_assignment,
		throwing_move,
		throwing_move_assignment,
		threw,
	};

	value_type() = default;

	explicit value_type(state_type state_)
		: state(state_)
	{
		throw_if(throwing_construction);
	}

	value_type(value_type const& other)
		: mixin_counter(other)
		, state(other.state)
	{
		throw_if(throwing_copy);
	}

	value_type&
		operator=(value_type const& other)
	{
		state = other.state;
		throw_if(throwing_copy_assignment);
		return *this;
	}

	value_type(value_type&& other)
		: state(other.state)
	{
		other.state = moved_from;
		throw_if(throwing_move);
	}

	value_type&
		operator=(value_type&& other)
	{
		state = other.state;
		other.state = moved_from;
		throw_if(throwing_move_assignment);
		return *this;
	}

	void throw_if(state_type match)
	{
		if (state == match)
		{
			state = threw;
			throw exception{};
		}
	}

	state_type state = zero;
};

GTEST_TEST(OptionalTest, AssignmentForDisengagedOptionalTest)
{
	using O = bksge::optional<value_type>;
	using S = value_type::state_type;
	auto const make = [](S s) { return O{ bksge::in_place, s }; };

	// Check copy/move assignment for disengaged optional

	// From disengaged optional
	{
		O o;
		EXPECT_TRUE(!o);
		O p;
		o = p;
		EXPECT_TRUE(!o);
		EXPECT_TRUE(!p);
	}
	{
		O o;
		EXPECT_TRUE(!o);
		O p;
		o = std::move(p);
		EXPECT_TRUE(!o);
		EXPECT_TRUE(!p);
	}
	{
		O o;
		EXPECT_TRUE(!o);
		o = {};
		EXPECT_TRUE(!o);
	}

	// From engaged optional
	{
		O o;
		EXPECT_TRUE(!o);
		O p = make(S::throwing_copy_assignment);
		o = p;
		EXPECT_TRUE(o && o->state == S::throwing_copy_assignment);
		EXPECT_TRUE(p && p->state == S::throwing_copy_assignment);
	}
	{
		O o;
		EXPECT_TRUE(!o);
		O p = make(S::throwing_move_assignment);
		o = std::move(p);
		EXPECT_TRUE(o && o->state == S::throwing_move_assignment);
		EXPECT_TRUE(p && p->state == S::moved_from);
	}
	{
		O o;
		EXPECT_TRUE(!o);
		O p = make(S::throwing_copy);

		EXPECT_THROW(o = p, exception);
		EXPECT_TRUE(!o);
		EXPECT_TRUE(p && p->state == S::throwing_copy);
	}
	{
		O o;
		EXPECT_TRUE(!o);
		O p = make(S::throwing_move);

		EXPECT_THROW(o = std::move(p), exception);
		EXPECT_TRUE(!o);
		EXPECT_TRUE(p && p->state == S::moved_from);
	}

	EXPECT_TRUE(counter == 0);
}

GTEST_TEST(OptionalTest, AssignmentForEngagedOptionalTest)
{
	using O = bksge::optional<value_type>;
	using S = value_type::state_type;
	auto const make = [](S s) { return O{ bksge::in_place, s }; };

	// Check copy/move assignment for engaged optional

	// From disengaged optional
	{
		O o = make(S::zero);
		EXPECT_TRUE((bool)o);
		O p;
		o = p;
		EXPECT_TRUE(!o);
		EXPECT_TRUE(!p);
	}

	{
		O o = make(S::zero);
		EXPECT_TRUE((bool)o);
		O p;
		o = std::move(p);
		EXPECT_TRUE(!o);
		EXPECT_TRUE(!p);
	}

	{
		O o = make(S::zero);
		EXPECT_TRUE((bool)o);
		o = {};
		EXPECT_TRUE(!o);
	}

	// From engaged optional
	{
		O o = make(S::zero);
		EXPECT_TRUE((bool)o);
		O p = make(S::throwing_copy);
		o = p;
		EXPECT_TRUE(o && o->state == S::throwing_copy);
		EXPECT_TRUE(p && p->state == S::throwing_copy);
	}

	{
		O o = make(S::zero);
		EXPECT_TRUE((bool)o);
		O p = make(S::throwing_move);
		o = std::move(p);
		EXPECT_TRUE(o && o->state == S::throwing_move);
		EXPECT_TRUE(p && p->state == S::moved_from);
	}

	{
		O o = make(S::zero);
		EXPECT_TRUE((bool)o);
		O p = make(S::throwing_copy_assignment);

		EXPECT_THROW(o = p, exception);
		EXPECT_TRUE(o && o->state == S::threw);
		EXPECT_TRUE(p && p->state == S::throwing_copy_assignment);
	}

	{
		O o = make(S::zero);
		EXPECT_TRUE((bool)o);
		O p = make(S::throwing_move_assignment);

		EXPECT_THROW(o = std::move(p), exception);
		EXPECT_TRUE(o && o->state == S::threw);
		EXPECT_TRUE(p && p->state == S::moved_from);
	}

	EXPECT_TRUE(counter == 0);
}

GTEST_TEST(OptionalTest, ValueAssignmentForDisengagedOptionalTest)
{
	using O = bksge::optional<value_type>;
	using S = value_type::state_type;
	auto const make = [](S s) { return value_type{ s }; };

	// Check value assignment for disengaged optional

	{
		O o;
		value_type v = make(S::throwing_copy_assignment);
		o = v;
		EXPECT_TRUE(o && o->state == S::throwing_copy_assignment);
	}

	{
		O o;
		value_type v = make(S::throwing_move_assignment);
		o = std::move(v);
		EXPECT_TRUE(o && o->state == S::throwing_move_assignment);
	}

	{
		O o;
		value_type v = make(S::throwing_copy);

		EXPECT_THROW(o = v, exception);
		EXPECT_TRUE(!o);
	}

	{
		O o;
		value_type v = make(S::throwing_move);

		EXPECT_THROW(o = std::move(v), exception);
		EXPECT_TRUE(!o);
	}

	EXPECT_TRUE(counter == 0);
}

GTEST_TEST(OptionalTest, ValueAssignmentForEngagedOptionalTest)
{
	using O = bksge::optional<value_type>;
	using S = value_type::state_type;
	auto const make = [](S s) { return value_type{ s }; };

	// Check value assignment for engaged optional

	{
		O o = make(S::zero);
		value_type v = make(S::throwing_copy);
		o = v;
		EXPECT_TRUE(o && o->state == S::throwing_copy);
	}

	{
		O o = make(S::zero);
		value_type v = make(S::throwing_move);
		o = std::move(v);
		EXPECT_TRUE(o && o->state == S::throwing_move);
	}

	{
		O o = make(S::zero);
		value_type v = make(S::throwing_copy_assignment);

		EXPECT_THROW(o = v, exception);
		EXPECT_TRUE(o && o->state == S::threw);
	}

	{
		O o = make(S::zero);
		value_type v = make(S::throwing_move_assignment);

		EXPECT_THROW(o = std::move(v), exception);
		EXPECT_TRUE(o && o->state == S::threw);
	}

	EXPECT_TRUE(counter == 0);
}

GTEST_TEST(OptionalTest, NulloptAssignmentTest)
{
	using O = bksge::optional<value_type>;

	// Check bksge::nullopt_t and 'default' (= {}) assignment

	{
		O o;
		o = bksge::nullopt;
		EXPECT_TRUE(!o);
	}

	{
		O o{ bksge::in_place };
		o = bksge::nullopt;
		EXPECT_TRUE(!o);
	}

	{
		O o;
		o = {};
		EXPECT_TRUE(!o);
	}

	{
		O o{ bksge::in_place };
		o = {};
		EXPECT_TRUE(!o);
	}

	EXPECT_TRUE(counter == 0);
}

}	// namespace assignment_test

}	// namespace bksge_optional_test
