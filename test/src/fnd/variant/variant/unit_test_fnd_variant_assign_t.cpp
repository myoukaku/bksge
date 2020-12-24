/**
 *	@file	unit_test_fnd_variant_assign_t.cpp
 *
 *	@brief	variant& operator=(T&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"
#include "fnd/variant/variant_test_helpers.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

namespace bksge_variant_test
{

namespace assign_t_test
{

namespace MetaHelpers
{

struct Dummy
{
	Dummy() = default;
};

struct ThrowsCtorT
{
	ThrowsCtorT(int) noexcept(false) {}
	ThrowsCtorT& operator=(int) noexcept { return *this; }
};

struct ThrowsAssignT
{
	ThrowsAssignT(int) noexcept {}
	ThrowsAssignT& operator=(int) noexcept(false) { return *this; }
};

struct NoThrowT
{
	NoThrowT(int) noexcept {}
	NoThrowT& operator=(int) noexcept { return *this; }
};

} // namespace MetaHelpers

namespace RuntimeHelpers
{
#if !defined(BKSGE_NO_EXCEPTIONS)

struct ThrowsCtorT
{
	int value;
	ThrowsCtorT() : value(0) {}
	ThrowsCtorT(int) noexcept(false) { throw 42; }
	ThrowsCtorT& operator=(int v) noexcept
	{
		value = v;
		return *this;
	}
};

struct MoveCrashes
{
	int value;
	MoveCrashes(int v = 0) noexcept : value{v} {}
	MoveCrashes(MoveCrashes&&) noexcept { assert(false); }
	MoveCrashes& operator=(MoveCrashes&&) noexcept { assert(false); return *this; }
	MoveCrashes& operator=(int v) noexcept
	{
		value = v;
		return *this;
	}
};

struct ThrowsCtorTandMove
{
	int value;
	ThrowsCtorTandMove() : value(0) {}
	ThrowsCtorTandMove(int) noexcept(false) { throw 42; }
	ThrowsCtorTandMove(ThrowsCtorTandMove&&) noexcept(false) { assert(false); }
	ThrowsCtorTandMove& operator=(int v) noexcept
	{
		value = v;
		return *this;
	}
};

struct ThrowsAssignT
{
	int value;
	ThrowsAssignT() : value(0) {}
	ThrowsAssignT(int v) noexcept : value(v) {}
	ThrowsAssignT& operator=(int) noexcept(false) { throw 42; }
};

struct NoThrowT
{
	int value;
	NoThrowT() : value(0) {}
	NoThrowT(int v) noexcept : value(v) {}
	NoThrowT& operator=(int v) noexcept
	{
		value = v;
		return *this;
	}
};

#endif

} // namespace RuntimeHelpers

void test_T_assignment_noexcept()
{
	using namespace MetaHelpers;
	{
		using V = bksge::variant<Dummy, NoThrowT>;
		static_assert(bksge::is_nothrow_assignable<V, int>::value, "");
	}
	{
		using V = bksge::variant<Dummy, ThrowsCtorT>;
		static_assert(!bksge::is_nothrow_assignable<V, int>::value, "");
	}
	{
		using V = bksge::variant<Dummy, ThrowsAssignT>;
		static_assert(!bksge::is_nothrow_assignable<V, int>::value, "");
	}
}

void test_T_assignment_sfinae()
{
	{
		using V = bksge::variant<long, long long>;
		static_assert(!bksge::is_assignable<V, int>::value, "ambiguous");
	}
	{
		using V = bksge::variant<bksge::string, bksge::string>;
		static_assert(!bksge::is_assignable<V, const char*>::value, "ambiguous");
	}
	{
		using V = bksge::variant<bksge::string, void*>;
		static_assert(!bksge::is_assignable<V, int>::value, "no matching operator=");
	}
	{
		//using V = bksge::variant<bksge::string, float>;
		//static_assert(bksge::is_assignable<V, int>::value == VariantAllowsNarrowingConversions, "no matching operator=");
	}
	{
		using V = bksge::variant<bksge::unique_ptr<int>, bool>;
		static_assert(!bksge::is_assignable<V, bksge::unique_ptr<char>>::value,"no explicit bool in operator=");
		struct X
		{
			operator void* ();
		};
// TODO
//		static_assert(!bksge::is_assignable<V, X>::value, "no boolean conversion in operator=");
// TODO
//		static_assert(!bksge::is_assignable<V, bksge::false_type>::value, "no converted to bool in operator=");
	}
	{
		struct X {};
		struct Y
		{
			operator X();
		};
		using V = bksge::variant<X>;
		static_assert(bksge::is_assignable<V, Y>::value, "regression on user-defined conversions in operator=");
	}
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int, int&&>;
		static_assert(!bksge::is_assignable<V, int>::value, "ambiguous");
	}
	{
		using V = bksge::variant<int, const int&>;
		static_assert(!bksge::is_assignable<V, int>::value, "ambiguous");
	}
#endif
}

void test_T_assignment_basic()
{
	using std::get;
	{
		bksge::variant<int> v(43);
		v = 42;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v), 42);
	}
	{
		bksge::variant<int, long> v(43l);
		v = 42;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v), 42);
		v = 43l;
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(get<1>(v), 43);
	}
#if 0//ndef TEST_VARIANT_ALLOWS_NARROWING_CONVERSIONS
	{
		bksge::variant<unsigned, long> v;
		v = 42;
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(get<1>(v), 42);
		v = 43u;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v), 43u);
	}
#endif
#if 0	// TODO
	{
		bksge::variant<bksge::string, bool> v = true;
		v = "bar";
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v), "bar");
	}
#endif
#if 0	// TODO
	{
		bksge::variant<bool, bksge::unique_ptr<int>> v;
		v = nullptr;
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(get<1>(v), nullptr);
	}
#endif
#if !defined(BKSGE_GCC)	// TODO
	{
		bksge::variant<bool volatile, int> v = 42;
		v = false;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_TRUE(!get<0>(v));
		bool lvt = true;
		v = lvt;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_TRUE(get<0>(v));
	}
#endif
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		using V = bksge::variant<int&, int&&, long>;
		int x = 42;
		V v(43l);
		v = x;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(&get<0>(v), &x);
		v = bksge::move(x);
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(&get<1>(v), &x);
		// 'long' is selected by FUN(const int &) since 'const int &' cannot bind
		// to 'int&'.
		const int& cx = x;
		v = cx;
		EXPECT_EQ(v.index(), 2u);
		EXPECT_EQ(get<2>(v), 42);
	}
#endif
}

void test_T_assignment_performs_construction()
{
	using std::get;
	using namespace RuntimeHelpers;
#if !defined(BKSGE_NO_EXCEPTIONS)
	{
		using V = bksge::variant<bksge::string, ThrowsCtorT>;
		V v(bksge::in_place_type_t<bksge::string>{}, "hello");
		try
		{
			v = 42;
			GTEST_FAIL();
		}
		catch (...)
		{
			/* ... */
		}
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v), "hello");
	}
	{
		using V = bksge::variant<ThrowsAssignT, bksge::string>;
		V v(bksge::in_place_type_t<bksge::string>{}, "hello");
		v = 42;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v).value, 42);
	}
#endif
}

void test_T_assignment_performs_assignment()
{
	using std::get;
	using namespace RuntimeHelpers;
#if !defined(BKSGE_NO_EXCEPTIONS)
	{
		using V = bksge::variant<ThrowsCtorT>;
		V v;
		v = 42;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v).value, 42);
	}
	{
		using V = bksge::variant<ThrowsCtorT, bksge::string>;
		V v;
		v = 42;
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v).value, 42);
	}
	{
		using V = bksge::variant<ThrowsAssignT>;
		V v(100);
		try
		{
			v = 42;
			GTEST_FAIL();
		}
		catch (...)
		{
			/* ... */
		}
		EXPECT_EQ(v.index(), 0u);
		EXPECT_EQ(get<0>(v).value, 100);
	}
	{
		using V = bksge::variant<bksge::string, ThrowsAssignT>;
		V v(100);
		try
		{
			v = 42;
			GTEST_FAIL();
		}
		catch (...)
		{
			/* ... */
		}
		EXPECT_EQ(v.index(), 1u);
		EXPECT_EQ(get<1>(v).value, 100);
	}
#endif
}

GTEST_TEST(VariantTest, AssignTTest)
{
	test_T_assignment_basic();
	test_T_assignment_performs_construction();
	test_T_assignment_performs_assignment();
	test_T_assignment_noexcept();
	test_T_assignment_sfinae();
}

}	// namespace assign_t_test

}	// namespace bksge_variant_test

BKSGE_WARNING_POP();
