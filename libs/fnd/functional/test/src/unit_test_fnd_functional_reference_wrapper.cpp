/**
 *	@file	unit_test_fnd_functional_reference_wrapper.cpp
 *
 *	@brief	reference_wrapper のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/reference_wrapper.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_trivially_copyable.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_functional_test
{

namespace reference_wrapper_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct NonTrivial
{
  ~NonTrivial() { }
};

using R = bksge::reference_wrapper<NonTrivial>;

static_assert(bksge::is_copy_constructible<R>::value, "copy constructible");
static_assert(bksge::is_copy_assignable<R>::value, "copy assignable");
static_assert(bksge::is_trivially_copyable<R>::value, "trivially copyable");

GTEST_TEST(ReferenceWrapperTest, DeductionTest)
{
#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)
	{
		int i = 0;
		bksge::reference_wrapper rw0(i);
		static_assert(bksge::is_same<decltype(rw0), bksge::reference_wrapper<int>>::value, "");

		bksge::reference_wrapper rw1(rw0);
		static_assert(bksge::is_same<decltype(rw1), bksge::reference_wrapper<int>>::value, "");
	}
	{
		int const i = 0;
		bksge::reference_wrapper rw0(i);
		static_assert(bksge::is_same<decltype(rw0), bksge::reference_wrapper<int const>>::value, "");

		bksge::reference_wrapper rw1(rw0);
		static_assert(bksge::is_same<decltype(rw1), bksge::reference_wrapper<int const>>::value, "");
	}
#endif
}

inline BKSGE_CXX14_CONSTEXPR bool test_get()
{
	int i = 0;
	bksge::reference_wrapper<int> rw(i);
	VERIFY(rw.get() == 0);
	rw.get() = 23;
	int& j = rw;
	VERIFY(j == 23);

	return true;
}

GTEST_TEST(ReferenceWrapperTest, GetTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_get());
}

struct Foo
{
	BKSGE_CONSTEXPR int operator()() const
	{
		return 1;
	}

	BKSGE_CONSTEXPR int operator()(int) const
	{
		return 2;
	}

	BKSGE_CONSTEXPR int operator()(float) const
	{
		return 3;
	}

	BKSGE_CONSTEXPR int operator()(int, int) const
	{
		return 4;
	}
};

inline BKSGE_CXX14_CONSTEXPR bool test_invoke()
{
	Foo f{};
	bksge::reference_wrapper<Foo> rw(f);
	VERIFY(rw() == 1);
	VERIFY(rw(0) == 2);
	VERIFY(rw(0.5f) == 3);
	VERIFY(rw(1, 1) == 4);
	return true;
}

GTEST_TEST(ReferenceWrapperTest, InvokeTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test_invoke());
}

#undef VERIFY

}	// namespace reference_wrapper_test

}	// namespace bksge_functional_test
