/**
 *	@file	unit_test_fnd_optional_observers.cpp
 *
 *	@brief	optional のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/optional/nullopt.hpp>
#include <bksge/fnd/optional/bad_optional_access.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_optional_test
{

namespace observers_test
{

struct value_type
{
	int i;
};

inline void* operator&(value_type const&)
{
	return nullptr;
}

GTEST_TEST(OptionalTest, ObserversTest)
{
	{
		BKSGE_CONSTEXPR bksge::optional<value_type> o{ value_type{ 51 } };
		BKSGE_CONSTEXPR_EXPECT_TRUE((*o).i == 51);
		EXPECT_TRUE(o->i == 51);
		EXPECT_TRUE(o->i == (*o).i);
		EXPECT_TRUE(&o->i == &(*o).i);
		BKSGE_CONSTEXPR_EXPECT_TRUE(o.value().i == 51);
		BKSGE_CONSTEXPR_EXPECT_TRUE(o.value().i == (*o).i);
		BKSGE_CONSTEXPR_EXPECT_TRUE(&o.value().i == &(*o).i);
		BKSGE_CONSTEXPR value_type fallback{ 3 };
		BKSGE_CONSTEXPR_EXPECT_TRUE(o.value_or(fallback).i == 51);
		BKSGE_CONSTEXPR_EXPECT_TRUE(o.value_or(fallback).i == (*o).i);
	}
	{
		BKSGE_CONSTEXPR bksge::optional<value_type> o { bksge::nullopt };
		BKSGE_CONSTEXPR_EXPECT_TRUE(!o);

		bool called = false;
		auto const eat = [&called](int) { called = true; };
		EXPECT_THROW(eat(o.value().i), bksge::bad_optional_access);
		EXPECT_TRUE(!called);

		BKSGE_CONSTEXPR value_type fallback{ 3 };
		BKSGE_CONSTEXPR_EXPECT_TRUE(o.value_or(fallback).i == 3);
	}
}

}	// namespace observers_test

}	// namespace bksge_optional_test
