/**
 *	@file	unit_test_fnd_type_traits_remove_all_extents.cpp
 *
 *	@brief	remove_all_extents のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/remove_all_extents.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, RemoveAllExtentsTest)
{
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, /**/          , /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const         , const);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile,       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile, const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,                &,                &);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const          &, const          &);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile &,       volatile &);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile &, const volatile &);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, *               , *               );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, * const         , * const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, *       volatile, *       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, * const volatile, * const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const          *, const          *);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile *,       volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile *, const volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,                [2],               );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const          [2], const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile [2],       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile [2], const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,                [2][3],               );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const          [2][3], const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile [2][3],       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile [2][3], const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,                [5][10][20],               );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const          [5][10][20], const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile [5][10][20],       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile [5][10][20], const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,                [],               );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const          [], const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile [],       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile [], const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,                [][3],               );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const          [][3], const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile [][3],       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile [][3], const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,                (&)[2],                (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const          (&)[2], const          (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile (&)[2],       volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile (&)[2], const volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,                &&,                &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const          &&, const          &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile &&,       volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile &&, const volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,                (&&)[2],                (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const          (&&)[2], const          (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents,       volatile (&&)[2],       volatile (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_all_extents, const volatile (&&)[2], const volatile (&&)[2]);
}
