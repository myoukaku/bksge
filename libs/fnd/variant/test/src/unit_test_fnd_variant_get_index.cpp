/**
 *	@file	unit_test_fnd_variant_get_index.cpp
 *
 *	@brief	get のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/bad_variant_access.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <utility>
#include "test_macros.hpp"
#include "test_workarounds.hpp"
#include "variant_test_helpers.hpp"

namespace bksge_variant_test
{

namespace get_index_test
{

void test_const_lvalue_get()
{
	using std::get;
	{
		using V = bksge::variant<int, const long>;
		constexpr V v(42);
#if defined(TEST_WORKAROUND_CONSTEXPR_IMPLIES_NOEXCEPT)
		ASSERT_NOEXCEPT(get<0>(v));
#else
		ASSERT_NOT_NOEXCEPT(get<0>(v));
#endif
		ASSERT_SAME_TYPE(decltype(get<0>(v)), const int&);
		static_assert(get<0>(v) == 42, "");
	}
	{
		using V = bksge::variant<int, const long>;
		const V v(42);
		ASSERT_NOT_NOEXCEPT(get<0>(v));
		ASSERT_SAME_TYPE(decltype(get<0>(v)), const int&);
		EXPECT_EQ(get<0>(v), 42);
	}
	{
		using V = bksge::variant<int, const long>;
		constexpr V v(42l);
#if defined(TEST_WORKAROUND_CONSTEXPR_IMPLIES_NOEXCEPT)
		ASSERT_NOEXCEPT(get<1>(v));
#else
		ASSERT_NOT_NOEXCEPT(get<1>(v));
#endif
		ASSERT_SAME_TYPE(decltype(get<1>(v)), const long&);
		static_assert(get<1>(v) == 42, "");
	}
	{
		using V = bksge::variant<int, const long>;
		const V v(42l);
		ASSERT_NOT_NOEXCEPT(get<1>(v));
		ASSERT_SAME_TYPE(decltype(get<1>(v)), const long&);
		EXPECT_EQ(get<1>(v), 42);
	}
	// FIXME: Remove these once reference support is reinstated
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&>;
		int x = 42;
		const V v(x);
		ASSERT_SAME_TYPE(decltype(get<0>(v)), int&);
		EXPECT_EQ(&get<0>(v), &x);
	}
	{
		using V = bksge::variant<int&&>;
		int x = 42;
		const V v(std::move(x));
		ASSERT_SAME_TYPE(decltype(get<0>(v)), int&);
		EXPECT_EQ(&get<0>(v), &x);
	}
	{
		using V = bksge::variant<const int&&>;
		int x = 42;
		const V v(std::move(x));
		ASSERT_SAME_TYPE(decltype(get<0>(v)), const int&);
		EXPECT_EQ(&get<0>(v), &x);
	}
#endif
}

void test_lvalue_get()
{
	using std::get;
	{
		using V = bksge::variant<int, const long>;
		V v(42);
		ASSERT_NOT_NOEXCEPT(get<0>(v));
		ASSERT_SAME_TYPE(decltype(get<0>(v)), int&);
		EXPECT_EQ(get<0>(v), 42);
	}
	{
		using V = bksge::variant<int, const long>;
		V v(42l);
		ASSERT_SAME_TYPE(decltype(get<1>(v)), const long&);
		EXPECT_EQ(get<1>(v), 42);
	}
	// FIXME: Remove these once reference support is reinstated
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&>;
		int x = 42;
		V v(x);
		ASSERT_SAME_TYPE(decltype(get<0>(v)), int&);
		EXPECT_EQ(&get<0>(v), &x);
	}
	{
		using V = bksge::variant<const int&>;
		int x = 42;
		V v(x);
		ASSERT_SAME_TYPE(decltype(get<0>(v)), const int&);
		EXPECT_EQ(&get<0>(v), &x);
	}
	{
		using V = bksge::variant<int&&>;
		int x = 42;
		V v(std::move(x));
		ASSERT_SAME_TYPE(decltype(get<0>(v)), int&);
		EXPECT_EQ(&get<0>(v), &x);
	}
	{
		using V = bksge::variant<const int&&>;
		int x = 42;
		V v(std::move(x));
		ASSERT_SAME_TYPE(decltype(get<0>(v)), const int&);
		EXPECT_EQ(&get<0>(v), &x);
	}
#endif
}

void test_rvalue_get()
{
	using std::get;
	{
		using V = bksge::variant<int, const long>;
		V v(42);
		ASSERT_NOT_NOEXCEPT(get<0>(std::move(v)));
		ASSERT_SAME_TYPE(decltype(get<0>(std::move(v))), int&&);
		EXPECT_EQ(get<0>(std::move(v)), 42);
	}
	{
		using V = bksge::variant<int, const long>;
		V v(42l);
		ASSERT_SAME_TYPE(decltype(get<1>(std::move(v))), const long&&);
		EXPECT_EQ(get<1>(std::move(v)), 42);
	}
	// FIXME: Remove these once reference support is reinstated
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&>;
		int x = 42;
		V v(x);
		ASSERT_SAME_TYPE(decltype(get<0>(std::move(v))), int&);
		EXPECT_EQ(&get<0>(std::move(v)), &x);
	}
	{
		using V = bksge::variant<const int&>;
		int x = 42;
		V v(x);
		ASSERT_SAME_TYPE(decltype(get<0>(std::move(v))), const int&);
		EXPECT_EQ(&get<0>(std::move(v)), &x);
	}
	{
		using V = bksge::variant<int&&>;
		int x = 42;
		V v(std::move(x));
		ASSERT_SAME_TYPE(decltype(get<0>(std::move(v))), int&&);
		int&& xref = get<0>(std::move(v));
		EXPECT_EQ(&xref, &x);
	}
	{
		using V = bksge::variant<const int&&>;
		int x = 42;
		V v(std::move(x));
		ASSERT_SAME_TYPE(decltype(get<0>(std::move(v))), const int&&);
		const int&& xref = get<0>(std::move(v));
		EXPECT_EQ(&xref, &x);
	}
#endif
}

void test_const_rvalue_get()
{
	using std::get;
	{
		using V = bksge::variant<int, const long>;
		const V v(42);
		ASSERT_NOT_NOEXCEPT(get<0>(std::move(v)));
		ASSERT_SAME_TYPE(decltype(get<0>(std::move(v))), const int&&);
		EXPECT_EQ(get<0>(std::move(v)), 42);
	}
	{
		using V = bksge::variant<int, const long>;
		const V v(42l);
		ASSERT_SAME_TYPE(decltype(get<1>(std::move(v))), const long&&);
		EXPECT_EQ(get<1>(std::move(v)), 42);
	}
	// FIXME: Remove these once reference support is reinstated
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&>;
		int x = 42;
		const V v(x);
		ASSERT_SAME_TYPE(decltype(get<0>(std::move(v))), int&);
		EXPECT_EQ(&get<0>(std::move(v)), &x);
	}
	{
		using V = bksge::variant<const int&>;
		int x = 42;
		const V v(x);
		ASSERT_SAME_TYPE(decltype(get<0>(std::move(v))), const int&);
		EXPECT_EQ(&get<0>(std::move(v)), &x);
	}
	{
		using V = bksge::variant<int&&>;
		int x = 42;
		const V v(std::move(x));
		ASSERT_SAME_TYPE(decltype(get<0>(std::move(v))), int&&);
		int&& xref = get<0>(std::move(v));
		EXPECT_EQ(&xref, &x);
	}
	{
		using V = bksge::variant<const int&&>;
		int x = 42;
		const V v(std::move(x));
		ASSERT_SAME_TYPE(decltype(get<0>(std::move(v))), const int&&);
		const int&& xref = get<0>(std::move(v));
		EXPECT_EQ(&xref, &x);
	}
#endif
}

struct Test
{
	template <typename Idx, typename V>
	bool operator()(Idx, V&& v)
	{
		try
		{
			using std::get;
			TEST_IGNORE_NODISCARD get<Idx::value>(bksge::forward<V>(v));
		}
		catch (const bksge::bad_variant_access&)
		{
			return true;
		}
		catch (...)
		{
			/* ... */
		}
		return false;
	}
};

void test_throws_for_all_value_categories()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	using V = bksge::variant<int, long>;
	V v0(42);
	const V& cv0 = v0;
	EXPECT_EQ(v0.index(), 0u);
	V v1(42l);
	const V& cv1 = v1;
	EXPECT_EQ(v1.index(), 1u);
	bksge::integral_constant<std::size_t, 0> zero;
	bksge::integral_constant<std::size_t, 1> one;

	Test test;

	{
		// lvalue test cases
		EXPECT_TRUE(test(one, v0));
		EXPECT_TRUE(test(zero, v1));
	}
	{
		// const lvalue test cases
		EXPECT_TRUE(test(one, cv0));
		EXPECT_TRUE(test(zero, cv1));
	}
	{
		// rvalue test cases
		EXPECT_TRUE(test(one, std::move(v0)));
		EXPECT_TRUE(test(zero, std::move(v1)));
	}
	{
		// const rvalue test cases
		EXPECT_TRUE(test(one, std::move(cv0)));
		EXPECT_TRUE(test(zero, std::move(cv1)));
	}
#endif
}

GTEST_TEST(VariantTest, GetIndexTest)
{
	test_const_lvalue_get();
	test_lvalue_get();
	test_rvalue_get();
	test_const_rvalue_get();
	test_throws_for_all_value_categories();
}

}	// namespace get_index_test

}	// namespace bksge_variant_test
