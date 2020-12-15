/**
 *	@file	unit_test_fnd_utility_pair_ctor_copy.cpp
 *
 *	@brief	pair::pair(pair&&) のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace ctor_copy_test
{

struct NoexceptCopy
{
	NoexceptCopy(NoexceptCopy const&) noexcept(true);
	NoexceptCopy& operator=(NoexceptCopy const&) = default;
};

struct ExceptCopy
{
	ExceptCopy(ExceptCopy const&) noexcept(false);
};

typedef bksge::pair<int, int>                   tt1;
typedef bksge::pair<int, double>                tt2;
typedef bksge::pair<NoexceptCopy, NoexceptCopy> tt3;
typedef bksge::pair<ExceptCopy, ExceptCopy>     tt4;
typedef bksge::pair<ExceptCopy, double>         tt5;
typedef bksge::pair<NoexceptCopy, ExceptCopy>   tt6;

static_assert( bksge::is_nothrow_copy_constructible<tt1>::value, "");
static_assert( bksge::is_nothrow_copy_constructible<tt2>::value, "");
static_assert( bksge::is_nothrow_copy_constructible<tt3>::value, "");
static_assert(!bksge::is_nothrow_copy_constructible<tt4>::value, "");
static_assert(!bksge::is_nothrow_copy_constructible<tt5>::value, "");
static_assert(!bksge::is_nothrow_copy_constructible<tt6>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test()
{
	{
		bksge::pair<int, double> const p1(1, 2);
		bksge::pair<int, double> const p2(p1);
		VERIFY(p2.first  == 1);
		VERIFY(p2.second == 2.0f);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, CtorCopyTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace ctor_copy_test

}	// namespace bksge_pair_test
