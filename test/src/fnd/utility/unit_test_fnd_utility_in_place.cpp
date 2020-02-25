/**
 *	@file	unit_test_fnd_utility_in_place.cpp
 *
 *	@brief	in_place のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace in_place_test
{

struct Foo
{
	BKSGE_CONSTEXPR Foo(int) : m_in_place_initialized(false) {}

	BKSGE_CONSTEXPR Foo(bksge::in_place_t, int) : m_in_place_initialized(true) {}

	bool m_in_place_initialized;
};

GTEST_TEST(UtilityTest, InPlaceTest)
{
	BKSGE_CONSTEXPR Foo f1(1);
	BKSGE_CONSTEXPR Foo f2(bksge::in_place, 1);

	BKSGE_CONSTEXPR_EXPECT_FALSE(f1.m_in_place_initialized);
	BKSGE_CONSTEXPR_EXPECT_TRUE (f2.m_in_place_initialized);
}

}	// namespace in_place_test

}	// namespace bksge_utility_test
