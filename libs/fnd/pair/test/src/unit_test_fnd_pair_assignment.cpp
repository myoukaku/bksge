/**
 *	@file	unit_test_fnd_utility_pair_assignment.cpp
 *
 *	@brief	operator= のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_test
{

namespace assignment_test
{

struct NoexceptMoveAssignClass
{
	NoexceptMoveAssignClass(NoexceptMoveAssignClass&&) = default;
	NoexceptMoveAssignClass& operator=(NoexceptMoveAssignClass&&) noexcept(true);
};

struct ExceptMoveAssignClass
{
	ExceptMoveAssignClass& operator=(ExceptMoveAssignClass&&) noexcept(false);
};

typedef bksge::pair<int, int>                                         tt1;
typedef bksge::pair<int, double>                                      tt2;
typedef bksge::pair<NoexceptMoveAssignClass, NoexceptMoveAssignClass> tt3;
typedef bksge::pair<ExceptMoveAssignClass, ExceptMoveAssignClass>     tt4;
typedef bksge::pair<ExceptMoveAssignClass, double>                    tt5;
typedef bksge::pair<NoexceptMoveAssignClass, ExceptMoveAssignClass>   tt6;

static_assert( bksge::is_nothrow_move_assignable<tt1>::value, "");
static_assert( bksge::is_nothrow_move_assignable<tt2>::value, "");
static_assert( bksge::is_nothrow_move_assignable<tt3>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<tt4>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<tt5>::value, "");
static_assert(!bksge::is_nothrow_move_assignable<tt6>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	typedef bksge::pair<int&, int> pair_type;
	int i = 1;
	int j = 2;
	pair_type p(i, 3);
	const pair_type q(j, 4);
	p = q;
	VERIFY(p.first == q.first);
	VERIFY(p.second == q.second);
	VERIFY(i == j);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test02()
{
	typedef bksge::pair<int, int&> pair_type;
	int i = 1;
	int j = 2;
	pair_type p(3, i);
	const pair_type q(4, j);
	p = q;
	VERIFY(p.first == q.first);
	VERIFY(p.second == q.second);
	VERIFY(i == j);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test03()
{
	typedef bksge::pair<int&, int&> pair_type;
	int i = 1;
	int j = 2;
	int k = 3;
	int l = 4;
	pair_type p(i, j);
	const pair_type q(k, l);
	p = q;
	VERIFY(p.first == q.first);
	VERIFY(p.second == q.second);
	VERIFY(i == k);
	VERIFY(j == l);

	return true;
}

inline BKSGE_CXX14_CONSTEXPR bool test04()
{
	int i = 100;
	int j = 3;

	using T = bksge::tuple<int>;
	bksge::pair<int, int> p0, p1, p2, p3;
	bksge::pair<int, int> pij(bksge::piecewise_construct, T(i), T(j));
	p0 = pij;
	p1 = bksge::move(pij);
	bksge::pair<long, long> pijl(i, j);
	p2 = pijl;
	p3 = bksge::move(pijl);

	VERIFY(p0.first  == i);
	VERIFY(p0.second == j);

	return true;
}

#undef VERIFY

GTEST_TEST(PairTest, AssignmentTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test01()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test02()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test03()));
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE((test04()));
}

}	// namespace assignment_test

}	// namespace bksge_pair_test
