/**
 *	@file	unit_test_fnd_pair_copy_ctor.cpp
 *
 *	@brief	pairのコピーコンストラクタのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_pair_copy_ctor_test
{

struct NonCopyable
{
	NonCopyable(NonCopyable const&) = delete;
};

struct ImplicitCopy
{
	ImplicitCopy(ImplicitCopy const&) {}
};

struct ExplicitCopy
{
	explicit ExplicitCopy(ExplicitCopy const&) {}
};

struct NothrowCopy
{
	NothrowCopy(NothrowCopy const&) noexcept {}
};

GTEST_TEST(PairTest, CopyCtorTest)
{
	{
        static_assert( bksge::is_copy_constructible<bksge::pair<int, float>>::value, "");
        static_assert(!bksge::is_copy_constructible<bksge::pair<int, NonCopyable>>::value, "");
        static_assert(!bksge::is_copy_constructible<bksge::pair<NonCopyable, float>>::value, "");
        static_assert( bksge::is_copy_constructible<bksge::pair<int, ImplicitCopy>>::value, "");
        static_assert( bksge::is_copy_constructible<bksge::pair<ImplicitCopy, int>>::value, "");
        static_assert( bksge::is_copy_constructible<bksge::pair<int, ExplicitCopy>>::value, "");
        static_assert( bksge::is_copy_constructible<bksge::pair<ExplicitCopy, int>>::value, "");
        static_assert( bksge::is_copy_constructible<bksge::pair<int, NothrowCopy>>::value, "");
        static_assert( bksge::is_copy_constructible<bksge::pair<NothrowCopy, int>>::value, "");

        static_assert( bksge::is_implicitly_copy_constructible<bksge::pair<int, float>>::value, "");
        static_assert(!bksge::is_implicitly_copy_constructible<bksge::pair<int, NonCopyable>>::value, "");
        static_assert(!bksge::is_implicitly_copy_constructible<bksge::pair<NonCopyable, float>>::value, "");
        static_assert( bksge::is_implicitly_copy_constructible<bksge::pair<int, ImplicitCopy>>::value, "");
        static_assert( bksge::is_implicitly_copy_constructible<bksge::pair<ImplicitCopy, int>>::value, "");
        static_assert( bksge::is_implicitly_copy_constructible<bksge::pair<int, ExplicitCopy>>::value, "");	// TODO
        static_assert( bksge::is_implicitly_copy_constructible<bksge::pair<ExplicitCopy, int>>::value, "");	// TODO
        static_assert( bksge::is_implicitly_copy_constructible<bksge::pair<int, NothrowCopy>>::value, "");
        static_assert( bksge::is_implicitly_copy_constructible<bksge::pair<NothrowCopy, int>>::value, "");

        static_assert( bksge::is_nothrow_copy_constructible<bksge::pair<int, float>>::value, "");
        static_assert(!bksge::is_nothrow_copy_constructible<bksge::pair<int, NonCopyable>>::value, "");
        static_assert(!bksge::is_nothrow_copy_constructible<bksge::pair<NonCopyable, float>>::value, "");
        static_assert(!bksge::is_nothrow_copy_constructible<bksge::pair<int, ImplicitCopy>>::value, "");
        static_assert(!bksge::is_nothrow_copy_constructible<bksge::pair<ImplicitCopy, int>>::value, "");
        static_assert(!bksge::is_nothrow_copy_constructible<bksge::pair<int, ExplicitCopy>>::value, "");
        static_assert(!bksge::is_nothrow_copy_constructible<bksge::pair<ExplicitCopy, int>>::value, "");
        static_assert( bksge::is_nothrow_copy_constructible<bksge::pair<int, NothrowCopy>>::value, "");
        static_assert( bksge::is_nothrow_copy_constructible<bksge::pair<NothrowCopy, int>>::value, "");
	}
	{
		bksge::pair<int, float> p1 { 3, 4.5f };
		bksge::pair<int, float> p2 { p1 };
		EXPECT_EQ(3,    p2.first);
		EXPECT_EQ(4.5f, p2.second);
	}
	{
		BKSGE_CONSTEXPR bksge::pair<int, float> p1 { 3, 4.5f };
		BKSGE_CONSTEXPR bksge::pair<int, float> p2 { p1 };
		BKSGE_CONSTEXPR_EXPECT_EQ(3,    p2.first);
		BKSGE_CONSTEXPR_EXPECT_EQ(4.5f, p2.second);
	}
}

}	// namespace bksge_pair_copy_ctor_test
