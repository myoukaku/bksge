/**
 *	@file	unit_test_fnd_compare_partial_ordering.cpp
 *
 *	@brief	partial_ordering のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/is_eq.hpp>
#include <bksge/fnd/compare/is_neq.hpp>
#include <bksge/fnd/compare/is_lt.hpp>
#include <bksge/fnd/compare/is_lteq.hpp>
#include <bksge/fnd/compare/is_gt.hpp>
#include <bksge/fnd/compare/is_gteq.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_compare_test
{

namespace partial_ordering_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	VERIFY(bksge::partial_ordering::less == bksge::partial_ordering::less);
	VERIFY(bksge::partial_ordering::less != bksge::partial_ordering::equivalent);
	VERIFY(bksge::partial_ordering::less != bksge::partial_ordering::greater);
	VERIFY(bksge::partial_ordering::less != bksge::partial_ordering::unordered);
	VERIFY(bksge::partial_ordering::equivalent == bksge::partial_ordering::equivalent);
	VERIFY(bksge::partial_ordering::equivalent != bksge::partial_ordering::greater);
	VERIFY(bksge::partial_ordering::equivalent != bksge::partial_ordering::unordered);
	VERIFY(bksge::partial_ordering::greater    == bksge::partial_ordering::greater);
	VERIFY(bksge::partial_ordering::greater    != bksge::partial_ordering::unordered);
	VERIFY(bksge::partial_ordering::unordered  == bksge::partial_ordering::unordered);

	VERIFY(!(bksge::partial_ordering::less == 0));
	VERIFY( (bksge::partial_ordering::less <  0));
	VERIFY(!(bksge::partial_ordering::less >  0));
	VERIFY( (bksge::partial_ordering::less <= 0));
	VERIFY(!(bksge::partial_ordering::less >= 0));
	VERIFY(!(0 == bksge::partial_ordering::less));
	VERIFY(!(0 <  bksge::partial_ordering::less));
	VERIFY( (0 >  bksge::partial_ordering::less));
	VERIFY(!(0 <= bksge::partial_ordering::less));
	VERIFY( (0 >= bksge::partial_ordering::less));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::partial_ordering::less <=> 0) == bksge::partial_ordering::less);
	VERIFY((0 <=> bksge::partial_ordering::less) == bksge::partial_ordering::greater);
#endif

	VERIFY( (bksge::partial_ordering::equivalent == 0));
	VERIFY(!(bksge::partial_ordering::equivalent <  0));
	VERIFY(!(bksge::partial_ordering::equivalent >  0));
	VERIFY( (bksge::partial_ordering::equivalent <= 0));
	VERIFY( (bksge::partial_ordering::equivalent >= 0));
	VERIFY( (0 == bksge::partial_ordering::equivalent));
	VERIFY(!(0 <  bksge::partial_ordering::equivalent));
	VERIFY(!(0 >  bksge::partial_ordering::equivalent));
	VERIFY( (0 <= bksge::partial_ordering::equivalent));
	VERIFY( (0 >= bksge::partial_ordering::equivalent));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::partial_ordering::equivalent <=> 0) == bksge::partial_ordering::equivalent);
	VERIFY((0 <=> bksge::partial_ordering::equivalent) == bksge::partial_ordering::equivalent);
#endif

	VERIFY(!(bksge::partial_ordering::greater == 0));
	VERIFY(!(bksge::partial_ordering::greater <  0));
	VERIFY( (bksge::partial_ordering::greater >  0));
	VERIFY(!(bksge::partial_ordering::greater <= 0));
	VERIFY( (bksge::partial_ordering::greater >= 0));
	VERIFY(!(0 == bksge::partial_ordering::greater));
	VERIFY( (0 <  bksge::partial_ordering::greater));
	VERIFY(!(0 >  bksge::partial_ordering::greater));
	VERIFY( (0 <= bksge::partial_ordering::greater));
	VERIFY(!(0 >= bksge::partial_ordering::greater));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::partial_ordering::greater <=> 0) == bksge::partial_ordering::greater);
	VERIFY((0 <=> bksge::partial_ordering::greater) == bksge::partial_ordering::less);
#endif

	VERIFY(!(bksge::partial_ordering::unordered == 0));
	VERIFY(!(bksge::partial_ordering::unordered <  0));
	VERIFY(!(bksge::partial_ordering::unordered >  0));
	VERIFY(!(bksge::partial_ordering::unordered <= 0));
	VERIFY(!(bksge::partial_ordering::unordered >= 0));
	VERIFY(!(0 == bksge::partial_ordering::unordered));
	VERIFY(!(0 <  bksge::partial_ordering::unordered));
	VERIFY(!(0 >  bksge::partial_ordering::unordered));
	VERIFY(!(0 <= bksge::partial_ordering::unordered));
	VERIFY(!(0 >= bksge::partial_ordering::unordered));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::partial_ordering::unordered <=> 0) == bksge::partial_ordering::unordered);
	VERIFY((0 <=> bksge::partial_ordering::unordered) == bksge::partial_ordering::unordered);
#endif

	static_assert(noexcept(bksge::partial_ordering::less == 0), "");
	static_assert(noexcept(bksge::partial_ordering::less != 0), "");
	static_assert(noexcept(bksge::partial_ordering::less <  0), "");
	static_assert(noexcept(bksge::partial_ordering::less >  0), "");
	static_assert(noexcept(bksge::partial_ordering::less <= 0), "");
	static_assert(noexcept(bksge::partial_ordering::less >= 0), "");
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(bksge::partial_ordering::less <=> 0), "");
#endif
	static_assert(noexcept(0 == bksge::partial_ordering::less), "");
	static_assert(noexcept(0 != bksge::partial_ordering::less), "");
	static_assert(noexcept(0 <  bksge::partial_ordering::less), "");
	static_assert(noexcept(0 >  bksge::partial_ordering::less), "");
	static_assert(noexcept(0 <= bksge::partial_ordering::less), "");
	static_assert(noexcept(0 >= bksge::partial_ordering::less), "");
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(0 <=> bksge::partial_ordering::less), "");
#endif

	VERIFY(bksge::is_eq  (bksge::partial_ordering::less)       == false);
	VERIFY(bksge::is_eq  (bksge::partial_ordering::equivalent) == true);
	VERIFY(bksge::is_eq  (bksge::partial_ordering::greater)    == false);
	VERIFY(bksge::is_eq  (bksge::partial_ordering::unordered)  == false);
	VERIFY(bksge::is_neq (bksge::partial_ordering::less)       == true);
	VERIFY(bksge::is_neq (bksge::partial_ordering::equivalent) == false);
	VERIFY(bksge::is_neq (bksge::partial_ordering::greater)    == true);
	VERIFY(bksge::is_neq (bksge::partial_ordering::unordered)  == true);
	VERIFY(bksge::is_lt  (bksge::partial_ordering::less)       == true);
	VERIFY(bksge::is_lt  (bksge::partial_ordering::equivalent) == false);
	VERIFY(bksge::is_lt  (bksge::partial_ordering::greater)    == false);
	VERIFY(bksge::is_lt  (bksge::partial_ordering::unordered)  == false);
	VERIFY(bksge::is_lteq(bksge::partial_ordering::less)       == true);
	VERIFY(bksge::is_lteq(bksge::partial_ordering::equivalent) == true);
	VERIFY(bksge::is_lteq(bksge::partial_ordering::greater)    == false);
	VERIFY(bksge::is_lteq(bksge::partial_ordering::unordered)  == false);
	VERIFY(bksge::is_gt  (bksge::partial_ordering::less)       == false);
	VERIFY(bksge::is_gt  (bksge::partial_ordering::equivalent) == false);
	VERIFY(bksge::is_gt  (bksge::partial_ordering::greater)    == true);
	VERIFY(bksge::is_gt  (bksge::partial_ordering::unordered)  == false);
	VERIFY(bksge::is_gteq(bksge::partial_ordering::less)       == false);
	VERIFY(bksge::is_gteq(bksge::partial_ordering::equivalent) == true);
	VERIFY(bksge::is_gteq(bksge::partial_ordering::greater)    == true);
	VERIFY(bksge::is_gteq(bksge::partial_ordering::unordered)  == false);

	return true;
}

#undef VERIFY

GTEST_TEST(CompareTest, PartialOrderingTest)
{
#if defined(BKSGE_HAS_CXX17_INLINE_VARIABLES)
	BKSGE_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace partial_ordering_test

}	// namespace bksge_compare_test
