/**
 *	@file	unit_test_fnd_variant_get_type.cpp
 *
 *	@brief	get のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/bad_variant_access.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"
#include "fnd/variant/test_workarounds.hpp"
#include "fnd/variant/variant_test_helpers.hpp"

namespace bksge_variant_test
{

namespace get_type_test
{

void test_const_lvalue_get()
{
	using std::get;
	{
		using V = bksge::variant<int, const long>;
		constexpr V v(42);
#if defined(TEST_WORKAROUND_CONSTEXPR_IMPLIES_NOEXCEPT)
		ASSERT_NOEXCEPT(get<int>(v));
#else
		ASSERT_NOT_NOEXCEPT(get<int>(v));
#endif
		ASSERT_SAME_TYPE(decltype(get<int>(v)), const int&);
		static_assert(get<int>(v) == 42, "");
	}
	{
		using V = bksge::variant<int, const long>;
		const V v(42);
		ASSERT_NOT_NOEXCEPT(get<int>(v));
		ASSERT_SAME_TYPE(decltype(get<int>(v)), const int&);
		EXPECT_EQ(get<int>(v), 42);
	}
	{
		using V = bksge::variant<int, const long>;
		constexpr V v(42l);
#if defined(TEST_WORKAROUND_CONSTEXPR_IMPLIES_NOEXCEPT)
		ASSERT_NOEXCEPT(get<const long>(v));
#else
		ASSERT_NOT_NOEXCEPT(get<const long>(v));
#endif
		ASSERT_SAME_TYPE(decltype(get<const long>(v)), const long&);
		static_assert(get<const long>(v) == 42, "");
	}
	{
		using V = bksge::variant<int, const long>;
		const V v(42l);
		ASSERT_NOT_NOEXCEPT(get<const long>(v));
		ASSERT_SAME_TYPE(decltype(get<const long>(v)), const long&);
		EXPECT_EQ(get<const long>(v), 42);
	}
	// FIXME: Remove these once reference support is reinstated
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&>;
		int x = 42;
		const V v(x);
		ASSERT_SAME_TYPE(decltype(get<int&>(v)), int&);
		EXPECT_EQ(&get<int&>(v), &x);
	}
	{
		using V = bksge::variant<int&&>;
		int x = 42;
		const V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(get<int&&>(v)), int&);
		EXPECT_EQ(&get<int&&>(v), &x);
	}
	{
		using V = bksge::variant<const int&&>;
		int x = 42;
		const V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(get<const int&&>(v)), const int&);
		EXPECT_EQ(&get<const int&&>(v), &x);
	}
#endif
}

void test_lvalue_get()
{
	using std::get;
	{
		using V = bksge::variant<int, const long>;
		V v(42);
		ASSERT_NOT_NOEXCEPT(get<int>(v));
		ASSERT_SAME_TYPE(decltype(get<int>(v)), int&);
		EXPECT_EQ(get<int>(v), 42);
	}
	{
		using V = bksge::variant<int, const long>;
		V v(42l);
		ASSERT_SAME_TYPE(decltype(get<const long>(v)), const long&);
		EXPECT_EQ(get<const long>(v), 42);
	}
	// FIXME: Remove these once reference support is reinstated
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&>;
		int x = 42;
		V v(x);
		ASSERT_SAME_TYPE(decltype(get<int&>(v)), int&);
		EXPECT_EQ(&get<int&>(v), &x);
	}
	{
		using V = bksge::variant<const int&>;
		int x = 42;
		V v(x);
		ASSERT_SAME_TYPE(decltype(get<const int&>(v)), const int&);
		EXPECT_EQ(&get<const int&>(v), &x);
	}
	{
		using V = bksge::variant<int&&>;
		int x = 42;
		V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(get<int&&>(v)), int&);
		EXPECT_EQ(&get<int&&>(v), &x);
	}
	{
		using V = bksge::variant<const int&&>;
		int x = 42;
		V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(get<const int&&>(v)), const int&);
		EXPECT_EQ(&get<const int&&>(v), &x);
	}
#endif
}

void test_rvalue_get()
{
	using std::get;
	{
		using V = bksge::variant<int, const long>;
		V v(42);
		ASSERT_NOT_NOEXCEPT(get<int>(bksge::move(v)));
		ASSERT_SAME_TYPE(decltype(get<int>(bksge::move(v))), int&&);
		EXPECT_EQ(get<int>(bksge::move(v)), 42);
	}
	{
		using V = bksge::variant<int, const long>;
		V v(42l);
		ASSERT_SAME_TYPE(decltype(get<const long>(bksge::move(v))), const long&&);
		EXPECT_EQ(get<const long>(bksge::move(v)), 42);
	}
	// FIXME: Remove these once reference support is reinstated
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&>;
		int x = 42;
		V v(x);
		ASSERT_SAME_TYPE(decltype(get<int&>(bksge::move(v))), int&);
		EXPECT_EQ(&get<int&>(bksge::move(v)), &x);
	}
	{
		using V = bksge::variant<const int&>;
		int x = 42;
		V v(x);
		ASSERT_SAME_TYPE(decltype(get<const int&>(bksge::move(v))), const int&);
		EXPECT_EQ(&get<const int&>(bksge::move(v)), &x);
	}
	{
		using V = bksge::variant<int&&>;
		int x = 42;
		V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(get<int&&>(bksge::move(v))), int&&);
		int&& xref = get<int&&>(bksge::move(v));
		EXPECT_EQ(&xref, &x);
	}
	{
		using V = bksge::variant<const int&&>;
		int x = 42;
		V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(get<const int&&>(bksge::move(v))), const int&&);
		const int&& xref = get<const int&&>(bksge::move(v));
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
		ASSERT_NOT_NOEXCEPT(get<int>(bksge::move(v)));
		ASSERT_SAME_TYPE(decltype(get<int>(bksge::move(v))), const int&&);
		EXPECT_EQ(get<int>(bksge::move(v)), 42);
	}
	{
		using V = bksge::variant<int, const long>;
		const V v(42l);
		ASSERT_SAME_TYPE(decltype(get<const long>(bksge::move(v))), const long&&);
		EXPECT_EQ(get<const long>(bksge::move(v)), 42);
	}
	// FIXME: Remove these once reference support is reinstated
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&>;
		int x = 42;
		const V v(x);
		ASSERT_SAME_TYPE(decltype(get<int&>(bksge::move(v))), int&);
		EXPECT_EQ(&get<int&>(bksge::move(v)), &x);
	}
	{
		using V = bksge::variant<const int&>;
		int x = 42;
		const V v(x);
		ASSERT_SAME_TYPE(decltype(get<const int&>(bksge::move(v))), const int&);
		EXPECT_EQ(&get<const int&>(bksge::move(v)), &x);
	}
	{
		using V = bksge::variant<int&&>;
		int x = 42;
		const V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(get<int&&>(bksge::move(v))), int&&);
		int&& xref = get<int&&>(bksge::move(v));
		EXPECT_EQ(&xref, &x);
	}
	{
		using V = bksge::variant<const int&&>;
		int x = 42;
		const V v(bksge::move(x));
		ASSERT_SAME_TYPE(decltype(get<const int&&>(bksge::move(v))), const int&&);
		const int&& xref = get<const int&&>(bksge::move(v));
		EXPECT_EQ(&xref, &x);
	}
#endif
}

template <class Tp> struct identity { using type = Tp; };

struct Test
{
	template <typename Idx, typename V>
	bool operator()(Idx, V&& v) const
	{
		using std::get;
		try
		{
			TEST_IGNORE_NODISCARD get<typename Idx::type>(bksge::forward<V>(v));
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
	};
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
	identity<int> zero;
	identity<long> one;

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
		EXPECT_TRUE(test(one, bksge::move(v0)));
		EXPECT_TRUE(test(zero, bksge::move(v1)));
	}
	{
		// const rvalue test cases
		EXPECT_TRUE(test(one, bksge::move(cv0)));
		EXPECT_TRUE(test(zero, bksge::move(cv1)));
	}
#endif
}

GTEST_TEST(VariantTest, GetTypeTest)
{
	test_const_lvalue_get();
	test_lvalue_get();
	test_rvalue_get();
	test_const_rvalue_get();
	test_throws_for_all_value_categories();
}

}	// namespace get_type_test

}	// namespace bksge_variant_test
