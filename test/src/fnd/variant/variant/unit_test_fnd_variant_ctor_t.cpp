/**
 *	@file	unit_test_fnd_variant_ctor_t.cpp
 *
 *	@brief	variant::variant(T&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <string>
#include <memory>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"
#include "fnd/variant/variant_test_helpers.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

namespace bksge_variant_test
{

namespace ctor_t_test
{

struct Dummy
{
	Dummy() = default;
};

struct ThrowsT
{
	ThrowsT(int) noexcept(false) {}
};

struct NoThrowT
{
	NoThrowT(int) noexcept(true) {}
};

struct AnyConstructible { template <typename T> AnyConstructible(T&&) {} };
struct NoConstructible { NoConstructible() = delete; };
template <typename T>
struct RValueConvertibleFrom { RValueConvertibleFrom(T&&) {} };

void test_T_ctor_noexcept()
{
	{
		using V = bksge::variant<Dummy, NoThrowT>;
		static_assert(bksge::is_nothrow_constructible<V, int>::value, "");
	}
	{
		using V = bksge::variant<Dummy, ThrowsT>;
		static_assert(!bksge::is_nothrow_constructible<V, int>::value, "");
	}
}

void test_T_ctor_sfinae()
{
	{
		using V = bksge::variant<long, long long>;
		static_assert(!bksge::is_constructible<V, int>::value, "ambiguous");
	}
	{
		using V = bksge::variant<std::string, std::string>;
		static_assert(!bksge::is_constructible<V, const char*>::value, "ambiguous");
	}
	{
		using V = bksge::variant<std::string, void*>;
		static_assert(!bksge::is_constructible<V, int>::value, "no matching constructor");
	}
	{
		//using V = bksge::variant<std::string, float>;
		//static_assert(bksge::is_constructible<V, int>::value == VariantAllowsNarrowingConversions, "no matching constructor");
	}
	{
		using V = bksge::variant<std::unique_ptr<int>, bool>;
		static_assert(!bksge::is_constructible<V, std::unique_ptr<char>>::value, "no explicit bool in constructor");
		struct X
		{
			operator void* ();
		};
// TODO
//		static_assert(!bksge::is_constructible<V, X>::value, "no boolean conversion in constructor");
//		static_assert(!bksge::is_constructible<V, std::false_type>::value, "no converted to bool in constructor");
	}
	{
		struct X {};
		struct Y {
			operator X();
		};
		using V = bksge::variant<X>;
		static_assert(bksge::is_constructible<V, Y>::value, "regression on user-defined conversions in constructor");
	}
	{
		using V = bksge::variant<AnyConstructible, NoConstructible>;
		static_assert(!bksge::is_constructible<V, bksge::in_place_type_t<NoConstructible>>::value, "no matching constructor");
		static_assert(!bksge::is_constructible<V, bksge::in_place_index_t<1>>::value, "no matching constructor");
	}

#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int, int&&>;
		static_assert(!bksge::is_constructible<V, int>::value, "ambiguous");
	}
	{
		using V = bksge::variant<int, const int&>;
		static_assert(!bksge::is_constructible<V, int>::value, "ambiguous");
	}
#endif
}

void test_T_ctor_basic()
{
	{
		constexpr bksge::variant<int> v(42);
		static_assert(v.index() == 0, "");
		static_assert(bksge::get<0>(v) == 42, "");
	}
	{
		constexpr bksge::variant<int, long> v(42l);
		static_assert(v.index() == 1, "");
		static_assert(bksge::get<1>(v) == 42, "");
	}
#if 0//ndef TEST_VARIANT_ALLOWS_NARROWING_CONVERSIONS
	{
		constexpr bksge::variant<unsigned, long> v(42);
		static_assert(v.index() == 1, "");
		static_assert(bksge::get<1>(v) == 42, "");
	}
#endif
#if 0	// TODO
	{
		bksge::variant<std::string, bool const> v = "foo";
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(bksge::get<0>(v), "foo");
	}
#endif
#if 0	// TODO
	{
		bksge::variant<bool volatile, std::unique_ptr<int>> v = nullptr;
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(bksge::get<1>(v), nullptr);
	}
#endif
	{
		bksge::variant<bool volatile const, int> v = true;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_TRUE(bksge::get<0>(v));
	}
	{
		bksge::variant<RValueConvertibleFrom<int>> v1 = 42;
		EXPECT_EQ(v1.index(), 0u);

		int x = 42;
		bksge::variant<RValueConvertibleFrom<int>, AnyConstructible> v2 = x;
		EXPECT_EQ(v2.index(), 1u);
	}
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<const int&, int&&, long>;
		static_assert(bksge::is_convertible<int&, V>::value, "must be implicit");
		int x = 42;
		V v(x);
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(&bksge::get<0>(v), &x);
	}
	{
		using V = bksge::variant<const int&, int&&, long>;
		static_assert(bksge::is_convertible<int, V>::value, "must be implicit");
		int x = 42;
		V v(bksge::move(x));
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(&bksge::get<1>(v), &x);
	}
#endif
}

struct BoomOnAnything
{
	template <typename T>
	constexpr BoomOnAnything(T) { /*static_assert(!bksge::is_same<T, T>::value, "");*/ }
};

void test_no_narrowing_check_for_class_types()
{
	using V = bksge::variant<int, BoomOnAnything>;
	V v(42);
	EXPECT_EQ(v.index(), 0u);
	EXPECT_EQ(bksge::get<0>(v), 42);
}

struct Bar {};
struct Baz {};

void test_construction_with_repeated_types()
{
	using V = bksge::variant<int, Bar, Baz, int, Baz, int, int>;
	static_assert(!bksge::is_constructible<V, int>::value, "");
	static_assert(!bksge::is_constructible<V, Baz>::value, "");
	// OK, the selected type appears only once and so it shouldn't
	// be affected by the duplicate types.
	static_assert(bksge::is_constructible<V, Bar>::value, "");
}

GTEST_TEST(VariantTest, CtorTTest)
{
	test_T_ctor_basic();
	test_T_ctor_noexcept();
	test_T_ctor_sfinae();
	test_no_narrowing_check_for_class_types();
	test_construction_with_repeated_types();
}

}	// namespace ctor_t_test

}	// namespace bksge_variant_test

BKSGE_WARNING_POP();
