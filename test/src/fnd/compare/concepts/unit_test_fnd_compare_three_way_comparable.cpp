/**
 *	@file	unit_test_fnd_compare_three_way_comparable.cpp
 *
 *	@brief	three_way_comparable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/compare/concepts/three_way_comparable.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_STD_COMPARE) && defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

namespace bksge_compare_test
{

namespace three_way_comparable_test
{

static_assert(bksge::three_way_comparable<int>, "");
static_assert(bksge::three_way_comparable<char>, "");
static_assert(bksge::three_way_comparable<float>, "");

struct X1
{
	int n;
	friend bool operator==(const X1& a, const X1& b) { return a.n == b.n; }
};
static_assert(!bksge::three_way_comparable<X1>, "");

struct X2
{
	int n;
	friend bool operator==(const X2& a, const X2& b) { return a.n == b.n; }
	friend bool operator< (const X2& a, const X2& b) { return a.n <  b.n; }
};
static_assert(!bksge::three_way_comparable<X2>, "");

struct X3
{
	int n;
	friend auto operator<=>(const X3& a, const X3& b) = default;
};
static_assert(bksge::three_way_comparable<X3>, "");

}	// namespace three_way_comparable_test

}	// namespace bksge_compare_test

#endif
