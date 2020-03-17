/**
 *	@file	unit_test_fnd_variant_ctor_default.cpp
 *
 *	@brief	variant::variant() のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/variant/monostate.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"
#include "fnd/variant/variant_test_helpers.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4702);	// 制御が渡らないコードです

namespace bksge_variant_test
{

namespace ctor_default_test
{

struct NonDefaultConstructible
{
	constexpr NonDefaultConstructible(int) {}
};

struct NotNoexcept
{
	NotNoexcept() noexcept(false) {}
};

#if !defined(BKSGE_NO_EXCEPTIONS)
struct DefaultCtorThrows
{
	DefaultCtorThrows() { throw 42; }
};
#endif

void test_default_ctor_sfinae()
{
	{
		using V = bksge::variant<bksge::monostate, int>;
		static_assert(bksge::is_default_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<NonDefaultConstructible, int>;
		static_assert(!bksge::is_default_constructible<V>::value, "");
	}
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&, int>;
		static_assert(!bksge::is_default_constructible<V>::value, "");
	}
#endif
}

void test_default_ctor_noexcept()
{
	{
		using V = bksge::variant<int>;
		static_assert(bksge::is_nothrow_default_constructible<V>::value, "");
	}
	{
		using V = bksge::variant<NotNoexcept>;
		static_assert(!bksge::is_nothrow_default_constructible<V>::value, "");
	}
}

void test_default_ctor_throws()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using V = bksge::variant<DefaultCtorThrows, int>;
	try
	{
		V v;
		GTEST_FAIL();
	}
	catch (const int& ex)
	{
		EXPECT_EQ(ex, 42);
	}
	catch (...)
	{
		GTEST_FAIL();
	}
#endif
}

void test_default_ctor_basic()
{
	{
		bksge::variant<int> v;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(bksge::get<0>(v), 0);
	}
	{
		bksge::variant<int, long> v;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(bksge::get<0>(v), 0);
	}
	{
		bksge::variant<int, NonDefaultConstructible> v;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(bksge::get<0>(v), 0);
	}
	{
		using V = bksge::variant<int, long>;
		constexpr V v;
		static_assert(v.index() == 0, "");
		static_assert(bksge::get<0>(v) == 0, "");
	}
	{
		using V = bksge::variant<int, long>;
		constexpr V v;
		static_assert(v.index() == 0, "");
		static_assert(bksge::get<0>(v) == 0, "");
	}
	{
		using V = bksge::variant<int, NonDefaultConstructible>;
		constexpr V v;
		static_assert(v.index() == 0, "");
		static_assert(bksge::get<0>(v) == 0, "");
	}
}

GTEST_TEST(VariantTest, CtorDefaultTest)
{
	test_default_ctor_basic();
	test_default_ctor_sfinae();
	test_default_ctor_noexcept();
	test_default_ctor_throws();
}

}	// namespace ctor_default_test

}	// namespace bksge_variant_test

BKSGE_WARNING_POP();
