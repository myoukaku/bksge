/**
 *	@file	unit_test_fnd_memory_pointer_traits.cpp
 *
 *	@brief	pointer_traits のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/memory/pointer_traits.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_memory_test
{

namespace pointer_traits_test
{

struct X {};

inline BKSGE_CXX14_CONSTEXPR bool pointer_to_test01()
{
	bool b = true;
	int i = 0;
	X x;

	return
		bksge::pointer_traits<bool*>::pointer_to(b) == &b &&
		bksge::pointer_traits<int*>::pointer_to(i) == &i &&
		bksge::pointer_traits<X*>::pointer_to(x) == &x;
}

struct Ptr
{
	typedef bool element_type;
	bool* value;

	template <typename> using rebind = Ptr;

	static BKSGE_CXX14_CONSTEXPR Ptr
	pointer_to(bool& b) { return Ptr{&b}; }
};

inline BKSGE_CXX14_CONSTEXPR bool
operator==(const Ptr& l, const Ptr& r)
{
	return l.value == r.value;
}

inline bool pointer_to_test02()
{
	bool test = true;
	Ptr p{&test};

	return bksge::pointer_traits<Ptr>::pointer_to(test) == p;
}

GTEST_TEST(MemoryTest, PointerTraitsTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(pointer_to_test01());
	EXPECT_TRUE(pointer_to_test02());
}

template <typename T, typename U>
using Rebind = typename bksge::pointer_traits<T>::template rebind<U>;

template <typename T>
struct HasRebind
{
	template <typename U> using rebind = U*;
};

static_assert(bksge::is_same<Rebind<HasRebind<int>, long>, long*>::value, "nested alias template is used");

template <typename T> struct NoRebind0 {};

static_assert(bksge::is_same<Rebind<NoRebind0<int>, long>, NoRebind0<long>>::value, "first template argument is replaced");

template <typename T, typename> struct NoRebind1 {};

static_assert(bksge::is_same<Rebind<NoRebind1<int, void>, long>, NoRebind1<long, void>>::value, "first template argument is replaced");

template <typename T, typename, typename> struct NoRebind2 {};

static_assert(bksge::is_same<Rebind<NoRebind2<int, void, void>, long>, NoRebind2<long, void, void>>::value, "first template argument is replaced");

template <typename T, typename...> struct NoRebindN {};

static_assert(bksge::is_same<Rebind<NoRebindN<int>, long>, NoRebindN<long>>::value, "first template argument is replaced");
static_assert(bksge::is_same<Rebind<NoRebindN<int, void>, long>, NoRebindN<long, void>>::value, "first template argument is replaced");

template <typename T, int = 0>
struct CannotRebind
{
	using element_type = T;
};

bksge::pointer_traits<CannotRebind<int>>::element_type e;

}	// namespace pointer_traits_test

}	// namespace bksge_memory_test
