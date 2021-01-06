/**
 *	@file	unit_test_fnd_tuple_tuple_ctor_allocator.cpp
 *
 *	@brief	uses-allocator construction のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/tuple/make_tuple.hpp>
#include <bksge/fnd/memory/allocator_arg.hpp>
#include <bksge/fnd/memory/uses_allocator.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

namespace bksge_tuple_test
{

namespace ctor_allocator_test
{

struct MyAlloc {};

// type that can't be constructed with an allocator
struct CannotUse
{
	BKSGE_CONSTEXPR CannotUse(int = 0, int = 0) : ok(true) { }

	bool ok;
};

// type that can be constructed with an allocator
// but which has uses_allocator == false
struct DoesNotUse
{
	typedef MyAlloc allocator_type;

	BKSGE_CONSTEXPR DoesNotUse(int = 0) : ok(true) { }
	BKSGE_CONSTEXPR DoesNotUse(bksge::allocator_arg_t, MyAlloc, int = 0) : ok(false) { }
	BKSGE_CONSTEXPR DoesNotUse(MyAlloc) : ok(false) { }
	BKSGE_CONSTEXPR DoesNotUse(int, MyAlloc) : ok(false) { }

	BKSGE_CONSTEXPR DoesNotUse(const DoesNotUse&) : ok(true) { }
	BKSGE_CONSTEXPR DoesNotUse(bksge::allocator_arg_t, MyAlloc, const DoesNotUse&) : ok(false) { }
	BKSGE_CONSTEXPR DoesNotUse(const DoesNotUse&, MyAlloc) : ok(false) { }

	BKSGE_CONSTEXPR DoesNotUse(DoesNotUse&&) : ok(true) { }
	BKSGE_CONSTEXPR DoesNotUse(bksge::allocator_arg_t, MyAlloc, DoesNotUse&&) : ok(false) { }
	BKSGE_CONSTEXPR DoesNotUse(DoesNotUse&&, MyAlloc) : ok(false) { }

	bool ok;
};

}	// namespace ctor_allocator_test

}	// namespace bksge_tuple_test

namespace BKSGE_USES_ALLOCATOR_NAMESPACE
{

template<typename A>
struct uses_allocator<bksge_tuple_test::ctor_allocator_test::DoesNotUse, A> : bksge::false_type {};

}	// namespace BKSGE_USES_ALLOCATOR_NAMESPACE

namespace bksge_tuple_test
{

namespace ctor_allocator_test
{

// type that can be constructed with an allocator as second argument
struct UsesWithTag
{
	typedef MyAlloc allocator_type;

	BKSGE_CONSTEXPR UsesWithTag(int = 0) : ok(false) { }
	BKSGE_CONSTEXPR UsesWithTag(bksge::allocator_arg_t, MyAlloc, int = 0) : ok(true) { }
	BKSGE_CONSTEXPR UsesWithTag(MyAlloc) : ok(false) {  }
	BKSGE_CONSTEXPR UsesWithTag(int, MyAlloc) : ok(false) {  }

	BKSGE_CONSTEXPR UsesWithTag(const UsesWithTag&) : ok(false) { }
	BKSGE_CONSTEXPR UsesWithTag(bksge::allocator_arg_t, MyAlloc, const UsesWithTag&) : ok(true) { }
	BKSGE_CONSTEXPR UsesWithTag(const UsesWithTag&, MyAlloc) : ok(false) {  }

	BKSGE_CONSTEXPR UsesWithTag(UsesWithTag&&) : ok(false) { }
	BKSGE_CONSTEXPR UsesWithTag(bksge::allocator_arg_t, MyAlloc, UsesWithTag&&) : ok(true) { }
	BKSGE_CONSTEXPR UsesWithTag(UsesWithTag&&, MyAlloc) : ok(false) {  }

	bool ok;
};

// type that can be constructed with an allocator as last argument
struct UsesWithoutTag
{
	typedef MyAlloc allocator_type;

	BKSGE_CONSTEXPR UsesWithoutTag(int = 0) : ok(false) { }
	BKSGE_CONSTEXPR UsesWithoutTag(MyAlloc) : ok(true) { }
	BKSGE_CONSTEXPR UsesWithoutTag(int, MyAlloc) : ok(true) { }

	BKSGE_CONSTEXPR UsesWithoutTag(const UsesWithoutTag&) : ok(false) { }
	BKSGE_CONSTEXPR UsesWithoutTag(const UsesWithoutTag&, MyAlloc) : ok(true) { }

	BKSGE_CONSTEXPR UsesWithoutTag(UsesWithoutTag&&) : ok(false) { }
	BKSGE_CONSTEXPR UsesWithoutTag(UsesWithoutTag&&, MyAlloc) : ok(true) { }

	bool ok;
};

struct Explicit
{
	explicit BKSGE_CONSTEXPR Explicit() noexcept : n(0) {}
	explicit BKSGE_CONSTEXPR Explicit(int x) noexcept : n(x) {}
	explicit BKSGE_CONSTEXPR Explicit(MyAlloc) noexcept : n(0) {}
	explicit BKSGE_CONSTEXPR Explicit(int x, MyAlloc) noexcept : n(x) {}
	explicit BKSGE_CONSTEXPR Explicit(Explicit const& rhs) : n(rhs.n) {}
	explicit BKSGE_CONSTEXPR Explicit(Explicit const& rhs, MyAlloc) : n(rhs.n) {}
	explicit BKSGE_CONSTEXPR Explicit(Explicit&& rhs) : n(rhs.n) {}
	explicit BKSGE_CONSTEXPR Explicit(Explicit&& rhs, MyAlloc) : n(rhs.n) {}
	int n;
};

struct Implicit
{
	BKSGE_CONSTEXPR Implicit() : n(0) {}
	BKSGE_CONSTEXPR Implicit(int x) : n(x) {}
	BKSGE_CONSTEXPR Implicit(MyAlloc) : n(0) {}
	BKSGE_CONSTEXPR Implicit(int x, MyAlloc) : n(x) {}
	BKSGE_CONSTEXPR Implicit(Implicit const& rhs) : n(rhs.n) {}
	BKSGE_CONSTEXPR Implicit(Implicit const& rhs, MyAlloc) : n(rhs.n) {}
	BKSGE_CONSTEXPR Implicit(Implicit&& rhs) : n(rhs.n) {}
	BKSGE_CONSTEXPR Implicit(Implicit&& rhs, MyAlloc) : n(rhs.n) {}
	int n;
};

struct Empty
{
	BKSGE_CONSTEXPR Empty() {}
	BKSGE_CONSTEXPR Empty(int) {}
	BKSGE_CONSTEXPR Empty(MyAlloc) {}
	BKSGE_CONSTEXPR Empty(int, MyAlloc) {}
	BKSGE_CONSTEXPR Empty(Empty const&) {}
	BKSGE_CONSTEXPR Empty(Empty const&, MyAlloc) {}
	BKSGE_CONSTEXPR Empty(Empty&&) {}
	BKSGE_CONSTEXPR Empty(Empty&&, MyAlloc) {}
};

static_assert( bksge::is_constructible<bksge::tuple<>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<>, bksge::allocator_arg_t, MyAlloc, int const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<>, bksge::allocator_arg_t, MyAlloc, int&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");

static_assert( bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, int const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, int const&, int const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, int const&, int const&, int const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, int&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, int&&, int&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, int&&, int&&, int&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");

static_assert( bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, int const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, int const&, int const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, int const&, int const&, int const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, int&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, int&&, int&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, int&&, int&&, int&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<int, int>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");

// (10)
static_assert( bksge::is_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc>::value, "");

// (11)
static_assert( bksge::is_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, Explicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, Explicit const&, Explicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Explicit const&, Implicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Implicit const&, Implicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Explicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Implicit const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Implicit const&, Implicit const&, Implicit const&>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, Explicit const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, Explicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Explicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Explicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Explicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Implicit const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Implicit const&, Implicit const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, Implicit const&, Implicit const&, Implicit const&, Implicit const&>::value, "");

// (12)
static_assert( bksge::is_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int, int, int>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int, int>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, int, int, int, int>::value, "");

// (13)
static_assert( bksge::is_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int, int> const&>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int, int> const&>::value, "");

// (14)
static_assert( bksge::is_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int, int>&&>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<int, int, int, int>&&>::value, "");

// (15)
static_assert(!bksge::is_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Explicit> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Implicit> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Explicit> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Implicit> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Explicit> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Implicit> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Explicit> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Implicit> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Explicit> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Implicit> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Explicit> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Implicit> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int> const&>::value, "");

// (16)
static_assert(!bksge::is_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Explicit>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Implicit>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Explicit>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Implicit>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Explicit>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Implicit>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");

static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Explicit>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Implicit>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Explicit>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Explicit, Implicit>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Explicit>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<Implicit, Implicit>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");
static_assert(!bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::pair<int, int>&&>::value, "");

// (17)
static_assert( bksge::is_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit, Explicit> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit, Implicit> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit, Explicit> const&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit, Implicit> const&>::value, "");

static_assert( bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit, Explicit> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit, Implicit> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit, Explicit> const&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit, Implicit> const&>::value, "");

// (18)
static_assert( bksge::is_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit, Explicit>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit, Implicit>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit, Explicit>&&>::value, "");
static_assert( bksge::is_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit, Implicit>&&>::value, "");

static_assert( bksge::is_implicitly_constructible<bksge::tuple<Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Explicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit, Explicit>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Explicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Explicit, Implicit>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Explicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit, Explicit>&&>::value, "");
static_assert( bksge::is_implicitly_constructible<bksge::tuple<Implicit, Implicit>, bksge::allocator_arg_t, MyAlloc, bksge::tuple<Implicit, Implicit>&&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test00()
{
	using std::get;

	typedef CannotUse T1;
	typedef DoesNotUse T2;
	typedef UsesWithTag T3;
	typedef UsesWithoutTag T4;
	typedef bksge::tuple<T1, T2, T3, T4> test_type;

	MyAlloc a;

	// default construction
	test_type t1(bksge::allocator_arg, a);
	VERIFY(get<0>(t1).ok);
	VERIFY(get<1>(t1).ok);
	VERIFY(get<2>(t1).ok);
	VERIFY(get<3>(t1).ok);

	// copy construction
	test_type t2(bksge::allocator_arg, a, t1);
	VERIFY(get<0>(t2).ok);
	VERIFY(get<1>(t2).ok);
	VERIFY(get<2>(t2).ok);
	VERIFY(get<3>(t2).ok);

	// move construction
	test_type t3(bksge::allocator_arg, a, bksge::move(t1));
	VERIFY(get<0>(t3).ok);
	VERIFY(get<1>(t3).ok);
	VERIFY(get<2>(t3).ok);
	VERIFY(get<3>(t3).ok);

	// construction from int
	test_type t4(bksge::allocator_arg, a, 1, 2, 3, 4);
	VERIFY(get<0>(t4).ok);
	VERIFY(get<1>(t4).ok);
	VERIFY(get<2>(t4).ok);
	VERIFY(get<3>(t4).ok);

	auto ints = bksge::make_tuple(1, 2, 3, 4);

	// construction from lvalue tuple of ints
	test_type t5(bksge::allocator_arg, a, ints);
	VERIFY(get<0>(t5).ok);
	VERIFY(get<1>(t5).ok);
	VERIFY(get<2>(t5).ok);
	VERIFY(get<3>(t2).ok);

	// construction from rvalue tuple of ints
	test_type t6(bksge::allocator_arg, a, bksge::move(ints));
	VERIFY(get<0>(t6).ok);
	VERIFY(get<1>(t6).ok);
	VERIFY(get<2>(t6).ok);
	VERIFY(get<3>(t6).ok);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	MyAlloc a;

	// default construction
	bksge::tuple<> t1(bksge::allocator_arg, a);
	// copy construction
	bksge::tuple<> t2(bksge::allocator_arg, a, t1);
	// move construction
	bksge::tuple<> t3(bksge::allocator_arg, a, bksge::move(t1));

	(void)t2;
	(void)t3;

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	using std::get;

	MyAlloc a;

	// default ctor
	{
		bksge::tuple<Empty> t(bksge::allocator_arg, a);
		(void)t;
	}
	{
		bksge::tuple<Empty, Empty> t(bksge::allocator_arg, a);
		(void)t;
	}
	{
		bksge::tuple<Empty, Empty, Empty> t(bksge::allocator_arg, a);
		(void)t;
	}
	{
		bksge::tuple<int> t(bksge::allocator_arg, a);
		VERIFY(get<0>(t) == 0);
	}
	{
		bksge::tuple<int, int> t(bksge::allocator_arg, a);
		VERIFY(get<0>(t) == 0);
		VERIFY(get<1>(t) == 0);
	}
	{
		bksge::tuple<int, int, int> t(bksge::allocator_arg, a);
		VERIFY(get<0>(t) == 0);
		VERIFY(get<1>(t) == 0);
		VERIFY(get<2>(t) == 0);
	}
	{
		bksge::tuple<Explicit> const t {bksge::allocator_arg, a};
		VERIFY(get<0>(t).n == 0);
	}
	{
		bksge::tuple<Implicit> const t = {bksge::allocator_arg, a};
		VERIFY(get<0>(t).n == 0);
	}
	{
		bksge::tuple<Explicit, Implicit> const t {bksge::allocator_arg, a};
		VERIFY(get<0>(t).n == 0);
		VERIFY(get<1>(t).n == 0);
	}
	{
		bksge::tuple<Implicit, Implicit> const t = {bksge::allocator_arg, a};
		VERIFY(get<0>(t).n == 0);
		VERIFY(get<1>(t).n == 0);
	}
	{
		bksge::tuple<Explicit, Implicit, Implicit> const t {bksge::allocator_arg, a};
		VERIFY(get<0>(t).n == 0);
		VERIFY(get<1>(t).n == 0);
		VERIFY(get<2>(t).n == 0);
	}
	{
		bksge::tuple<Implicit, Implicit, Implicit> const t = {bksge::allocator_arg, a};
		VERIFY(get<0>(t).n == 0);
		VERIFY(get<1>(t).n == 0);
		VERIFY(get<2>(t).n == 0);
	}
	// direct ctor
	{
		Empty const x1;
		bksge::tuple<Empty> t(bksge::allocator_arg, a, x1);
		(void)t;
	}
	{
		Empty const x1;
		Empty const x2;
		bksge::tuple<Empty, Empty> t(bksge::allocator_arg, a, x1, x2);
		(void)t;
	}
	{
		Empty const x1;
		Empty const x2;
		Empty const x3;
		bksge::tuple<Empty, Empty, Empty> t(bksge::allocator_arg, a, x1, x2, x3);
		(void)t;
	}
	{
		int const x1 = 1;
		bksge::tuple<int> t(bksge::allocator_arg, a, x1);
		VERIFY(get<0>(t) == 1);
	}
	{
		int const x1 = 1;
		int const x2 = 2;
		bksge::tuple<int, int> t(bksge::allocator_arg, a, x1, x2);
		VERIFY(get<0>(t) == 1);
		VERIFY(get<1>(t) == 2);
	}
	{
		int const x1 = 1;
		int const x2 = 2;
		int const x3 = 3;
		bksge::tuple<int, int, int> t(bksge::allocator_arg, a, x1, x2, x3);
		VERIFY(get<0>(t) == 1);
		VERIFY(get<1>(t) == 2);
		VERIFY(get<2>(t) == 3);
	}
	{
		Explicit const x{2};
		bksge::tuple<Explicit> const t {bksge::allocator_arg, a, x};
		VERIFY(get<0>(t).n == 2);
	}
	{
		Implicit const x{2};
		bksge::tuple<Implicit> const t = {bksge::allocator_arg, a, x};
		VERIFY(get<0>(t).n == 2);
	}
	// converting ctor
	{
		bksge::tuple<Empty> t(bksge::allocator_arg, a, 1);
		(void)t;
	}
	{
		bksge::tuple<Empty, Empty> t(bksge::allocator_arg, a, 1, 2);
		(void)t;
	}
	{
		bksge::tuple<Empty, Empty, Empty> t(bksge::allocator_arg, a, 1, 2, 3);
		(void)t;
	}
	{
		bksge::tuple<int> t(bksge::allocator_arg, a, 2);
		VERIFY(get<0>(t) == 2);
	}
	{
		bksge::tuple<long, short> t(bksge::allocator_arg, a, 3, 4);
		VERIFY(get<0>(t) == 3);
		VERIFY(get<1>(t) == 4);
	}
	{
		bksge::tuple<int, short, long> t(bksge::allocator_arg, a, 2, 3, 4);
		VERIFY(get<0>(t) == 2);
		VERIFY(get<1>(t) == 3);
		VERIFY(get<2>(t) == 4);
	}
	{
		bksge::tuple<Explicit> const t {bksge::allocator_arg, a, 11};
		VERIFY(get<0>(t).n == 11);
	}
	{
		bksge::tuple<Implicit> const t = {bksge::allocator_arg, a, 12};
		VERIFY(get<0>(t).n == 12);
	}
	{
		bksge::tuple<Explicit, Implicit> const t {bksge::allocator_arg, a, 13, 14};
		VERIFY(get<0>(t).n == 13);
		VERIFY(get<1>(t).n == 14);
	}
	{
		bksge::tuple<Implicit, Implicit> const t = {bksge::allocator_arg, a, 13, 14};
		VERIFY(get<0>(t).n == 13);
		VERIFY(get<1>(t).n == 14);
	}
	{
		bksge::tuple<Implicit, Explicit, Implicit> const t {bksge::allocator_arg, a, 13, 14, 15};
		VERIFY(get<0>(t).n == 13);
		VERIFY(get<1>(t).n == 14);
		VERIFY(get<2>(t).n == 15);
	}
	{
		bksge::tuple<Implicit, Implicit, Implicit> const t = {bksge::allocator_arg, a, 13, 14, 15};
		VERIFY(get<0>(t).n == 13);
		VERIFY(get<1>(t).n == 14);
		VERIFY(get<2>(t).n == 15);
	}
	// copy ctor
	{
		bksge::tuple<Empty> const t1;
		bksge::tuple<Empty> const t2(bksge::allocator_arg, a, t1);
		(void)t2;
	}
	{
		bksge::tuple<Empty, Empty> const t1;
		bksge::tuple<Empty, Empty> const t2(bksge::allocator_arg, a, t1);
		(void)t2;
	}
	{
		bksge::tuple<Empty, Empty, Empty> const t1;
		bksge::tuple<Empty, Empty, Empty> const t2(bksge::allocator_arg, a, t1);
		(void)t2;
	}
	{
		bksge::tuple<int> const t1(5);
		bksge::tuple<int> const t2(bksge::allocator_arg, a, t1);
		VERIFY(get<0>(t2) == 5);
	}
	{
		bksge::tuple<int, int> const t1(5, 6);
		bksge::tuple<int, int> const t2(bksge::allocator_arg, a, t1);
		VERIFY(get<0>(t2) == 5);
		VERIFY(get<1>(t2) == 6);
	}
	{
		bksge::tuple<int, int, int> const t1(5, 6, 7);
		bksge::tuple<int, int, int> const t2(bksge::allocator_arg, a, t1);
		VERIFY(get<0>(t2) == 5);
		VERIFY(get<1>(t2) == 6);
		VERIFY(get<2>(t2) == 7);
	}
	// move ctor
	{
		bksge::tuple<Empty> t1;
		bksge::tuple<Empty> t2(bksge::allocator_arg, a, bksge::move(t1));
		(void)t2;
	}
	{
		bksge::tuple<Empty, Empty> t1;
		bksge::tuple<Empty, Empty> t2(bksge::allocator_arg, a, bksge::move(t1));
		(void)t2;
	}
	{
		bksge::tuple<Empty, Empty, Empty> t1;
		bksge::tuple<Empty, Empty, Empty> t2(bksge::allocator_arg, a, bksge::move(t1));
		(void)t2;
	}
	{
		bksge::tuple<int> t1(6);
		bksge::tuple<int> t2(bksge::allocator_arg, a, bksge::move(t1));
		VERIFY(get<0>(t2) == 6);
	}
	{
		bksge::tuple<int, int> t1(6, 7);
		bksge::tuple<int, int> t2(bksge::allocator_arg, a, bksge::move(t1));
		VERIFY(get<0>(t2) == 6);
		VERIFY(get<1>(t2) == 7);
	}
	{
		bksge::tuple<int, int, int> t1(6, 7, 8);
		bksge::tuple<int, int, int> t2(bksge::allocator_arg, a, bksge::move(t1));
		VERIFY(get<0>(t2) == 6);
		VERIFY(get<1>(t2) == 7);
		VERIFY(get<2>(t2) == 8);
	}
	// convert copy ctor
	{
		bksge::tuple<int> const t1;
		bksge::tuple<Empty> t2(bksge::allocator_arg, a, t1);
		(void)t2;
	}
	{
		bksge::tuple<int, int> const t1;
		bksge::tuple<Empty, Empty> t2(bksge::allocator_arg, a, t1);
		(void)t2;
	}
	{
		bksge::tuple<int, int, int> const t1;
		bksge::tuple<Empty, Empty, Empty> t2(bksge::allocator_arg, a, t1);
		(void)t2;
	}
	{
		bksge::tuple<int, int> const t1(5, 6);
		bksge::tuple<Explicit, Explicit> const t2 {bksge::allocator_arg, a, t1};
		VERIFY(get<0>(t2).n == 5);
		VERIFY(get<1>(t2).n == 6);
	}
	{
		bksge::tuple<int, int> const t1(5, 6);
		bksge::tuple<Implicit, Implicit> const t2 = {bksge::allocator_arg, a, t1};
		VERIFY(get<0>(t2).n == 5);
		VERIFY(get<1>(t2).n == 6);
	}
	{
		bksge::tuple<int, int, int> const t1(4, 5, 6);
		bksge::tuple<Implicit, Explicit, Explicit> const t2 {bksge::allocator_arg, a, t1};
		VERIFY(get<0>(t2).n == 4);
		VERIFY(get<1>(t2).n == 5);
		VERIFY(get<2>(t2).n == 6);
	}
	{
		bksge::tuple<int, int, int> const t1(4, 5, 6);
		bksge::tuple<Implicit, Implicit, Implicit> const t2 = {bksge::allocator_arg, a, t1};
		VERIFY(get<0>(t2).n == 4);
		VERIFY(get<1>(t2).n == 5);
		VERIFY(get<2>(t2).n == 6);
	}
	// convert move ctor
	{
		bksge::tuple<int> t1;
		bksge::tuple<Empty> t2(bksge::allocator_arg, a, bksge::move(t1));
		(void)t2;
	}
	{
		bksge::tuple<int, int> t1;
		bksge::tuple<Empty, Empty> t2(bksge::allocator_arg, a, bksge::move(t1));
		(void)t2;
	}
	{
		bksge::tuple<int, int, int> t1;
		bksge::tuple<Empty, Empty, Empty> t2(bksge::allocator_arg, a, bksge::move(t1));
		(void)t2;
	}
	{
		bksge::tuple<int, int> t1(5, 6);
		bksge::tuple<Explicit, Explicit> const t2 {bksge::allocator_arg, a, bksge::move(t1)};
		VERIFY(get<0>(t2).n == 5);
		VERIFY(get<1>(t2).n == 6);
	}
	{
		bksge::tuple<int, int> t1(5, 6);
		bksge::tuple<Implicit, Implicit> const t2 = {bksge::allocator_arg, a, bksge::move(t1)};
		VERIFY(get<0>(t2).n == 5);
		VERIFY(get<1>(t2).n == 6);
	}
	{
		bksge::tuple<int, int, int> t1(4, 5, 6);
		bksge::tuple<Implicit, Explicit, Explicit> const t2 {bksge::allocator_arg, a, bksge::move(t1)};
		VERIFY(get<0>(t2).n == 4);
		VERIFY(get<1>(t2).n == 5);
		VERIFY(get<2>(t2).n == 6);
	}
	{
		bksge::tuple<int, int, int> t1(4, 5, 6);
		bksge::tuple<Implicit, Implicit, Implicit> const t2 = {bksge::allocator_arg, a, bksge::move(t1)};
		VERIFY(get<0>(t2).n == 4);
		VERIFY(get<1>(t2).n == 5);
		VERIFY(get<2>(t2).n == 6);
	}
	// pair copy ctor
	{
		bksge::pair<int, int> const t1;
		bksge::tuple<Empty, Empty> t2(bksge::allocator_arg, a, t1);
		(void)t2;
	}
	{
		bksge::pair<int, int> const t1(5, 6);
		bksge::tuple<int, int> const t2 {bksge::allocator_arg, a, t1};
		VERIFY(get<0>(t2) == 5);
		VERIFY(get<1>(t2) == 6);
	}
	{
		bksge::pair<int, int> const t1(5, 6);
		bksge::tuple<Explicit, Explicit> const t2 {bksge::allocator_arg, a, t1};
		VERIFY(get<0>(t2).n == 5);
		VERIFY(get<1>(t2).n == 6);
	}
	{
		bksge::pair<int, int> const t1(5, 6);
		bksge::tuple<Implicit, Implicit> const t2 = {bksge::allocator_arg, a, t1};
		VERIFY(get<0>(t2).n == 5);
		VERIFY(get<1>(t2).n == 6);
	}
	// pair move ctor
	{
		bksge::pair<int, int> t1;
		bksge::tuple<Empty, Empty> t2(bksge::allocator_arg, a, bksge::move(t1));
		(void)t2;
	}
	{
		bksge::pair<int, int> t1(5, 6);
		bksge::tuple<int, int> const t2 {bksge::allocator_arg, a, bksge::move(t1)};
		VERIFY(get<0>(t2) == 5);
		VERIFY(get<1>(t2) == 6);
	}
	{
		bksge::pair<int, int> t1(5, 6);
		bksge::tuple<Explicit, Explicit> const t2 {bksge::allocator_arg, a, bksge::move(t1)};
		VERIFY(get<0>(t2).n == 5);
		VERIFY(get<1>(t2).n == 6);
	}
	{
		bksge::pair<int, int> t1(5, 6);
		bksge::tuple<Implicit, Implicit> const t2 = {bksge::allocator_arg, a, bksge::move(t1)};
		VERIFY(get<0>(t2).n == 5);
		VERIFY(get<1>(t2).n == 6);
	}
	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	using std::get;

	MyAlloc a;

	{
		bksge::tuple t(bksge::allocator_arg, a);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<>>::value, "");
	}
	{
		int const x1 = 1;
		bksge::tuple t(bksge::allocator_arg, a, x1);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int>>::value, "");
		VERIFY(get<0>(t) == 1);
	}
	{
		int   const x1 = 2;
		float const x2 = 3;
		bksge::tuple t(bksge::allocator_arg, a, x1, x2);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int, float>>::value, "");
		VERIFY(get<0>(t) == 2);
		VERIFY(get<1>(t) == 3);
	}
	{
		bksge::tuple t(bksge::allocator_arg, a, 1);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int>>::value, "");
		VERIFY(get<0>(t) == 1);
	}
	{
		bksge::tuple t(bksge::allocator_arg, a, 2, 0.5);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<int, double>>::value, "");
		VERIFY(get<0>(t) == 2);
		VERIFY(get<1>(t) == 0.5);
	}
	{
		bksge::tuple t(bksge::allocator_arg, a, 'a', 2, 0.5);
		static_assert(bksge::is_same<decltype(t), bksge::tuple<char, int, double>>::value, "");
		VERIFY(get<0>(t) == 'a');
		VERIFY(get<1>(t) == 2);
		VERIFY(get<2>(t) == 0.5);
	}
	{
		bksge::tuple<int> const t1(5);
		bksge::tuple t2(bksge::allocator_arg, a, t1);
		static_assert(bksge::is_same<decltype(t2), bksge::tuple<int>>::value, "");
		VERIFY(get<0>(t2) == 5);
	}
	{
		bksge::tuple<float, int> t1(0.5f, 6);
		bksge::tuple t2(bksge::allocator_arg, a, bksge::move(t1));
		static_assert(bksge::is_same<decltype(t2), bksge::tuple<float, int>>::value, "");
		VERIFY(get<0>(t2) == 0.5f);
		VERIFY(get<1>(t2) == 6);
	}
	{
		bksge::pair<int, int> const t1(2, 3);
		bksge::tuple t2(bksge::allocator_arg, a, t1);
		static_assert(bksge::is_same<decltype(t2), bksge::tuple<int, int>>::value, "");
		VERIFY(get<0>(t2) == 2);
		VERIFY(get<1>(t2) == 3);
	}
	{
		bksge::pair<long, int> t1(3, 4);
		bksge::tuple t2(bksge::allocator_arg, a, bksge::move(t1));
		static_assert(bksge::is_same<decltype(t2), bksge::tuple<long, int>>::value, "");
		VERIFY(get<0>(t2) == 3);
		VERIFY(get<1>(t2) == 4);
	}
#endif
	return true;
}

#undef VERIFY

GTEST_TEST(TupleTest, CtorAllocatorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test00()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test01()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test02()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test03()));
}

}	// namespace ctor_allocator_test

}	// namespace bksge_tuple_test

BKSGE_WARNING_POP();
