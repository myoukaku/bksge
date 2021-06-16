/**
 *	@file	unit_test_fnd_variant_get_if_type.cpp
 *
 *	@brief	get_if のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/get_if.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <gtest/gtest.h>
#include "test_macros.hpp"
#include "variant_test_helpers.hpp"

namespace bksge_variant_test
{

namespace get_if_type_test
{

void test_const_get_if()
{
	{
		using V = bksge::variant<int>;
		constexpr const V* v = nullptr;
		static_assert(bksge::get_if<int>(v) == nullptr, "");
	}
	{
		using V = bksge::variant<int, const long>;
		constexpr V v(42);
		ASSERT_NOEXCEPT(bksge::get_if<int>(&v));
		ASSERT_SAME_TYPE(decltype(bksge::get_if<int>(&v)), const int*);
		static_assert(*bksge::get_if<int>(&v) == 42, "");
		static_assert(bksge::get_if<const long>(&v) == nullptr, "");
	}
	{
		using V = bksge::variant<int, const long>;
		constexpr V v(42l);
		ASSERT_SAME_TYPE(decltype(bksge::get_if<const long>(&v)), const long*);
		static_assert(*bksge::get_if<const long>(&v) == 42, "");
		static_assert(bksge::get_if<int>(&v) == nullptr, "");
	}
	// FIXME: Remove these once reference support is reinstated
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&>;
		int x = 42;
		const V v(x);
		ASSERT_SAME_TYPE(decltype(bksge::get_if<int&>(&v)), int*);
		EXPECT_EQ(bksge::get_if<int&>(&v), &x);
	}
	{
		using V = bksge::variant<int&&>;
		int x = 42;
		const V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(bksge::get_if<int&&>(&v)), int*);
		EXPECT_EQ(bksge::get_if<int&&>(&v), &x);
	}
	{
		using V = bksge::variant<const int&&>;
		int x = 42;
		const V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(bksge::get_if<const int&&>(&v)), const int*);
		EXPECT_EQ(bksge::get_if<const int&&>(&v), &x);
	}
#endif
}

void test_get_if()
{
	{
		using V = bksge::variant<int>;
		V* v = nullptr;
		EXPECT_TRUE(bksge::get_if<int>(v) == nullptr);
	}
	{
		using V = bksge::variant<int, const long>;
		V v(42);
		ASSERT_NOEXCEPT(bksge::get_if<int>(&v));
		ASSERT_SAME_TYPE(decltype(bksge::get_if<int>(&v)), int*);
		EXPECT_EQ(*bksge::get_if<int>(&v), 42);
		EXPECT_TRUE(bksge::get_if<const long>(&v) == nullptr);
	}
	{
		using V = bksge::variant<int, const long>;
		V v(42l);
		ASSERT_SAME_TYPE(decltype(bksge::get_if<const long>(&v)), const long*);
		EXPECT_EQ(*bksge::get_if<const long>(&v), 42);
		EXPECT_TRUE(bksge::get_if<int>(&v) == nullptr);
	}
	// FIXME: Remove these once reference support is reinstated
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&>;
		int x = 42;
		V v(x);
		ASSERT_SAME_TYPE(decltype(bksge::get_if<int&>(&v)), int*);
		EXPECT_EQ(bksge::get_if<int&>(&v), &x);
	}
	{
		using V = bksge::variant<const int&>;
		int x = 42;
		V v(x);
		ASSERT_SAME_TYPE(decltype(bksge::get_if<const int&>(&v)), const int*);
		EXPECT_EQ(bksge::get_if<const int&>(&v), &x);
	}
	{
		using V = bksge::variant<int&&>;
		int x = 42;
		V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(bksge::get_if<int&&>(&v)), int*);
		EXPECT_EQ(bksge::get_if<int&&>(&v), &x);
	}
	{
		using V = bksge::variant<const int&&>;
		int x = 42;
		V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(bksge::get_if<const int&&>(&v)), const int*);
		EXPECT_EQ(bksge::get_if<const int&&>(&v), &x);
	}
#endif
}

GTEST_TEST(VariantTest, GetIfTypeTest)
{
	test_const_get_if();
	test_get_if();
}

}	// namespace get_if_type_test

}	// namespace bksge_variant_test
