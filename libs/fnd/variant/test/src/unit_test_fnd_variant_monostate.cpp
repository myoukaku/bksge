/**
 *	@file	unit_test_fnd_variant_monostate.cpp
 *
 *	@brief	monostate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/monostate.hpp>
#include <bksge/fnd/type_traits/is_trivially_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <gtest/gtest.h>
#include "test_macros.hpp"

GTEST_TEST(VariantTest, MonostateTest)
{
	using M = bksge::monostate;
	static_assert(bksge::is_trivially_default_constructible<M>::value, "");
	static_assert(bksge::is_trivially_copy_constructible<M>::value, "");
	static_assert(bksge::is_trivially_copy_assignable<M>::value, "");
	static_assert(bksge::is_trivially_destructible<M>::value, "");
	constexpr M m{};
	((void)m);
}

GTEST_TEST(VariantTest, MonostateCompareTest)
{
	using M = bksge::monostate;
	constexpr M m1{};
	constexpr M m2{};
	{
		static_assert((m1 < m2) == false, "");
		ASSERT_NOEXCEPT(m1 < m2);
	}
	{
		static_assert((m1 > m2) == false, "");
		ASSERT_NOEXCEPT(m1 > m2);
	}
	{
		static_assert((m1 <= m2) == true, "");
		ASSERT_NOEXCEPT(m1 <= m2);
	}
	{
		static_assert((m1 >= m2) == true, "");
		ASSERT_NOEXCEPT(m1 >= m2);
	}
	{
		static_assert((m1 == m2) == true, "");
		ASSERT_NOEXCEPT(m1 == m2);
	}
	{
		static_assert((m1 != m2) == false, "");
		ASSERT_NOEXCEPT(m1 != m2);
	}
}
