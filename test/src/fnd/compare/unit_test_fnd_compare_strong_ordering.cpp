/**
 *	@file	unit_test_fnd_compare_strong_ordering.cpp
 *
 *	@brief	strong_ordering のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/compare/partial_ordering.hpp>
#include <bksge/fnd/compare/weak_ordering.hpp>
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

namespace strong_ordering_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline BKSGE_CXX14_CONSTEXPR bool test01()
{
	VERIFY(bksge::strong_ordering::less       == bksge::strong_ordering::less);
	VERIFY(bksge::strong_ordering::less       != bksge::strong_ordering::equal);
	VERIFY(bksge::strong_ordering::less       != bksge::strong_ordering::equivalent);
	VERIFY(bksge::strong_ordering::less       != bksge::strong_ordering::greater);
	VERIFY(bksge::strong_ordering::equivalent == bksge::strong_ordering::equivalent);
	VERIFY(bksge::strong_ordering::equivalent == bksge::strong_ordering::equal);
	VERIFY(bksge::strong_ordering::equivalent != bksge::strong_ordering::greater);
	VERIFY(bksge::strong_ordering::equal      == bksge::strong_ordering::equal);
	VERIFY(bksge::strong_ordering::equal      != bksge::strong_ordering::greater);
	VERIFY(bksge::strong_ordering::greater    == bksge::strong_ordering::greater);

	VERIFY(!(bksge::strong_ordering::less == 0));
	VERIFY( (bksge::strong_ordering::less <  0));
	VERIFY(!(bksge::strong_ordering::less >  0));
	VERIFY( (bksge::strong_ordering::less <= 0));
	VERIFY(!(bksge::strong_ordering::less >= 0));
	VERIFY(!(0 == bksge::strong_ordering::less));
	VERIFY(!(0 <  bksge::strong_ordering::less));
	VERIFY( (0 >  bksge::strong_ordering::less));
	VERIFY(!(0 <= bksge::strong_ordering::less));
	VERIFY( (0 >= bksge::strong_ordering::less));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::strong_ordering::less <=> 0) == bksge::strong_ordering::less);
	VERIFY((0 <=> bksge::strong_ordering::less) == bksge::strong_ordering::greater);
#endif

	VERIFY( (bksge::strong_ordering::equal == 0));
	VERIFY(!(bksge::strong_ordering::equal <  0));
	VERIFY(!(bksge::strong_ordering::equal >  0));
	VERIFY( (bksge::strong_ordering::equal <= 0));
	VERIFY( (bksge::strong_ordering::equal >= 0));
	VERIFY( (0 == bksge::strong_ordering::equal));
	VERIFY(!(0 <  bksge::strong_ordering::equal));
	VERIFY(!(0 >  bksge::strong_ordering::equal));
	VERIFY( (0 <= bksge::strong_ordering::equal));
	VERIFY( (0 >= bksge::strong_ordering::equal));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::strong_ordering::equal <=> 0) == bksge::strong_ordering::equal);
	VERIFY((0 <=> bksge::strong_ordering::equal) == bksge::strong_ordering::equal);
#endif

	VERIFY( (bksge::strong_ordering::equivalent == 0));
	VERIFY(!(bksge::strong_ordering::equivalent <  0));
	VERIFY(!(bksge::strong_ordering::equivalent >  0));
	VERIFY( (bksge::strong_ordering::equivalent <= 0));
	VERIFY( (bksge::strong_ordering::equivalent >= 0));
	VERIFY( (0 == bksge::strong_ordering::equivalent));
	VERIFY(!(0 <  bksge::strong_ordering::equivalent));
	VERIFY(!(0 >  bksge::strong_ordering::equivalent));
	VERIFY( (0 <= bksge::strong_ordering::equivalent));
	VERIFY( (0 >= bksge::strong_ordering::equivalent));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::strong_ordering::equivalent <=> 0) == bksge::strong_ordering::equivalent);
	VERIFY((0 <=> bksge::strong_ordering::equivalent) == bksge::strong_ordering::equivalent);
#endif

	VERIFY(!(bksge::strong_ordering::greater == 0));
	VERIFY(!(bksge::strong_ordering::greater <  0));
	VERIFY( (bksge::strong_ordering::greater >  0));
	VERIFY(!(bksge::strong_ordering::greater <= 0));
	VERIFY( (bksge::strong_ordering::greater >= 0));
	VERIFY(!(0 == bksge::strong_ordering::greater));
	VERIFY( (0 <  bksge::strong_ordering::greater));
	VERIFY(!(0 >  bksge::strong_ordering::greater));
	VERIFY( (0 <= bksge::strong_ordering::greater));
	VERIFY(!(0 >= bksge::strong_ordering::greater));
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	VERIFY((bksge::strong_ordering::greater <=> 0) == bksge::strong_ordering::greater);
	VERIFY((0 <=> bksge::strong_ordering::greater) == bksge::strong_ordering::less);
#endif

	// Conversions
	VERIFY(bksge::partial_ordering(bksge::strong_ordering::less)       == bksge::partial_ordering::less);
	VERIFY(bksge::partial_ordering(bksge::strong_ordering::equal)      == bksge::partial_ordering::equivalent);
	VERIFY(bksge::partial_ordering(bksge::strong_ordering::equivalent) == bksge::partial_ordering::equivalent);
	VERIFY(bksge::partial_ordering(bksge::strong_ordering::greater)    == bksge::partial_ordering::greater);

	VERIFY(bksge::weak_ordering(bksge::strong_ordering::less)          == bksge::weak_ordering::less);
	VERIFY(bksge::partial_ordering(bksge::strong_ordering::equal)      == bksge::weak_ordering::equivalent);
	VERIFY(bksge::partial_ordering(bksge::strong_ordering::equivalent) == bksge::weak_ordering::equivalent);
	VERIFY(bksge::weak_ordering(bksge::strong_ordering::greater)       == bksge::weak_ordering::greater);

	static_assert(noexcept(bksge::strong_ordering::less == 0), "");
	static_assert(noexcept(bksge::strong_ordering::less != 0), "");
	static_assert(noexcept(bksge::strong_ordering::less <  0), "");
	static_assert(noexcept(bksge::strong_ordering::less >  0), "");
	static_assert(noexcept(bksge::strong_ordering::less <= 0), "");
	static_assert(noexcept(bksge::strong_ordering::less >= 0), "");
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(bksge::strong_ordering::less <=> 0), "");
#endif
	static_assert(noexcept(0 == bksge::strong_ordering::less), "");
	static_assert(noexcept(0 != bksge::strong_ordering::less), "");
	static_assert(noexcept(0 <  bksge::strong_ordering::less), "");
	static_assert(noexcept(0 >  bksge::strong_ordering::less), "");
	static_assert(noexcept(0 <= bksge::strong_ordering::less), "");
	static_assert(noexcept(0 >= bksge::strong_ordering::less), "");
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(0 <=> bksge::strong_ordering::less), "");
#endif

	VERIFY(bksge::is_eq  (bksge::strong_ordering::less)       == false);
	VERIFY(bksge::is_eq  (bksge::strong_ordering::equal)      == true);
	VERIFY(bksge::is_eq  (bksge::strong_ordering::equivalent) == true);
	VERIFY(bksge::is_eq  (bksge::strong_ordering::greater)    == false);
	VERIFY(bksge::is_neq (bksge::strong_ordering::less)       == true);
	VERIFY(bksge::is_neq (bksge::strong_ordering::equal)      == false);
	VERIFY(bksge::is_neq (bksge::strong_ordering::equivalent) == false);
	VERIFY(bksge::is_neq (bksge::strong_ordering::greater)    == true);
	VERIFY(bksge::is_lt  (bksge::strong_ordering::less)       == true);
	VERIFY(bksge::is_lt  (bksge::strong_ordering::equal)      == false);
	VERIFY(bksge::is_lt  (bksge::strong_ordering::equivalent) == false);
	VERIFY(bksge::is_lt  (bksge::strong_ordering::greater)    == false);
	VERIFY(bksge::is_lteq(bksge::strong_ordering::less)       == true);
	VERIFY(bksge::is_lteq(bksge::strong_ordering::equal)      == true);
	VERIFY(bksge::is_lteq(bksge::strong_ordering::equivalent) == true);
	VERIFY(bksge::is_lteq(bksge::strong_ordering::greater)    == false);
	VERIFY(bksge::is_gt  (bksge::strong_ordering::less)       == false);
	VERIFY(bksge::is_gt  (bksge::strong_ordering::equal)      == false);
	VERIFY(bksge::is_gt  (bksge::strong_ordering::equivalent) == false);
	VERIFY(bksge::is_gt  (bksge::strong_ordering::greater)    == true);
	VERIFY(bksge::is_gteq(bksge::strong_ordering::less)       == false);
	VERIFY(bksge::is_gteq(bksge::strong_ordering::equal)      == true);
	VERIFY(bksge::is_gteq(bksge::strong_ordering::equivalent) == true);
	VERIFY(bksge::is_gteq(bksge::strong_ordering::greater)    == true);

	return true;
}

#undef VERIFY

GTEST_TEST(CompareTest, StrongOrderingTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace strong_ordering_test

}	// namespace bksge_compare_test
