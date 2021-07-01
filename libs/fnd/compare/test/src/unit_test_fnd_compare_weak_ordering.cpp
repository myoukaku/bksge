/**
 *	@file	unit_test_fnd_compare_weak_ordering.cpp
 *
 *	@brief	weak_ordering のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/compare/weak_ordering.hpp>
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

namespace weak_ordering_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX17_CONSTEXPR bool test01()
{
	VERIFY(bksge::weak_ordering::less       == bksge::weak_ordering::less);
	VERIFY(bksge::weak_ordering::less       != bksge::weak_ordering::equivalent);
	VERIFY(bksge::weak_ordering::less       != bksge::weak_ordering::greater);
	VERIFY(bksge::weak_ordering::equivalent == bksge::weak_ordering::equivalent);
	VERIFY(bksge::weak_ordering::equivalent != bksge::weak_ordering::greater);
	VERIFY(bksge::weak_ordering::greater    == bksge::weak_ordering::greater);

	VERIFY(!(bksge::weak_ordering::less == 0));
	VERIFY( (bksge::weak_ordering::less <  0));
	VERIFY(!(bksge::weak_ordering::less >  0));
	VERIFY( (bksge::weak_ordering::less <= 0));
	VERIFY(!(bksge::weak_ordering::less >= 0));
	VERIFY(!(0 == bksge::weak_ordering::less));
	VERIFY(!(0 <  bksge::weak_ordering::less));
	VERIFY( (0 >  bksge::weak_ordering::less));
	VERIFY(!(0 <= bksge::weak_ordering::less));
	VERIFY( (0 >= bksge::weak_ordering::less));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::weak_ordering::less <=> 0) == bksge::weak_ordering::less);
	VERIFY((0 <=> bksge::weak_ordering::less) == bksge::weak_ordering::greater);
#endif

	VERIFY( (bksge::weak_ordering::equivalent == 0));
	VERIFY(!(bksge::weak_ordering::equivalent <  0));
	VERIFY(!(bksge::weak_ordering::equivalent >  0));
	VERIFY( (bksge::weak_ordering::equivalent <= 0));
	VERIFY( (bksge::weak_ordering::equivalent >= 0));
	VERIFY( (0 == bksge::weak_ordering::equivalent));
	VERIFY(!(0 <  bksge::weak_ordering::equivalent));
	VERIFY(!(0 >  bksge::weak_ordering::equivalent));
	VERIFY( (0 <= bksge::weak_ordering::equivalent));
	VERIFY( (0 >= bksge::weak_ordering::equivalent));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::weak_ordering::equivalent <=> 0) == bksge::weak_ordering::equivalent);
	VERIFY((0 <=> bksge::weak_ordering::equivalent) == bksge::weak_ordering::equivalent);
#endif

	VERIFY(!(bksge::weak_ordering::greater == 0));
	VERIFY(!(bksge::weak_ordering::greater <  0));
	VERIFY( (bksge::weak_ordering::greater >  0));
	VERIFY(!(bksge::weak_ordering::greater <= 0));
	VERIFY( (bksge::weak_ordering::greater >= 0));
	VERIFY(!(0 == bksge::weak_ordering::greater));
	VERIFY( (0 <  bksge::weak_ordering::greater));
	VERIFY(!(0 >  bksge::weak_ordering::greater));
	VERIFY( (0 <= bksge::weak_ordering::greater));
	VERIFY(!(0 >= bksge::weak_ordering::greater));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::weak_ordering::greater <=> 0) == bksge::weak_ordering::greater);
	VERIFY((0 <=> bksge::weak_ordering::greater) == bksge::weak_ordering::less);
#endif

	// Conversions
	VERIFY(bksge::partial_ordering(bksge::weak_ordering::less)       == bksge::partial_ordering::less);
	VERIFY(bksge::partial_ordering(bksge::weak_ordering::equivalent) == bksge::partial_ordering::equivalent);
	VERIFY(bksge::partial_ordering(bksge::weak_ordering::greater)    == bksge::partial_ordering::greater);

	static_assert(noexcept(bksge::weak_ordering::less == 0), "");
	static_assert(noexcept(bksge::weak_ordering::less != 0), "");
	static_assert(noexcept(bksge::weak_ordering::less <  0), "");
	static_assert(noexcept(bksge::weak_ordering::less >  0), "");
	static_assert(noexcept(bksge::weak_ordering::less <= 0), "");
	static_assert(noexcept(bksge::weak_ordering::less >= 0), "");
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(bksge::weak_ordering::less <=> 0), "");
#endif
	static_assert(noexcept(0 == bksge::weak_ordering::less), "");
	static_assert(noexcept(0 != bksge::weak_ordering::less), "");
	static_assert(noexcept(0 <  bksge::weak_ordering::less), "");
	static_assert(noexcept(0 >  bksge::weak_ordering::less), "");
	static_assert(noexcept(0 <= bksge::weak_ordering::less), "");
	static_assert(noexcept(0 >= bksge::weak_ordering::less), "");
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(0 <=> bksge::weak_ordering::less), "");
#endif

	VERIFY(bksge::is_eq  (bksge::weak_ordering::less)       == false);
	VERIFY(bksge::is_eq  (bksge::weak_ordering::equivalent) == true);
	VERIFY(bksge::is_eq  (bksge::weak_ordering::greater)    == false);
	VERIFY(bksge::is_neq (bksge::weak_ordering::less)       == true);
	VERIFY(bksge::is_neq (bksge::weak_ordering::equivalent) == false);
	VERIFY(bksge::is_neq (bksge::weak_ordering::greater)    == true);
	VERIFY(bksge::is_lt  (bksge::weak_ordering::less)       == true);
	VERIFY(bksge::is_lt  (bksge::weak_ordering::equivalent) == false);
	VERIFY(bksge::is_lt  (bksge::weak_ordering::greater)    == false);
	VERIFY(bksge::is_lteq(bksge::weak_ordering::less)       == true);
	VERIFY(bksge::is_lteq(bksge::weak_ordering::equivalent) == true);
	VERIFY(bksge::is_lteq(bksge::weak_ordering::greater)    == false);
	VERIFY(bksge::is_gt  (bksge::weak_ordering::less)       == false);
	VERIFY(bksge::is_gt  (bksge::weak_ordering::equivalent) == false);
	VERIFY(bksge::is_gt  (bksge::weak_ordering::greater)    == true);
	VERIFY(bksge::is_gteq(bksge::weak_ordering::less)       == false);
	VERIFY(bksge::is_gteq(bksge::weak_ordering::equivalent) == true);
	VERIFY(bksge::is_gteq(bksge::weak_ordering::greater)    == true);

	return true;
}

#undef VERIFY

GTEST_TEST(CompareTest, WeakOrderingTest)
{
#if defined(BKSGE_COMPARE_USE_INLINE_VARIABLES)
	BKSGE_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace weak_ordering_test

}	// namespace bksge_compare_test
