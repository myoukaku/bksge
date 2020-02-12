/**
 *	@file	unit_test_fnd_type_traits_remove_extent.cpp
 *
 *	@brief	remove_extent のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/remove_extent.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

GTEST_TEST(TypeTraitsTest, RemoveExtentTest)
{
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, /**/          , /**/);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const         , const);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile,       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile, const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,                &,                &);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const          &, const          &);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile &,       volatile &);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile &, const volatile &);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, *               , *               );
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, * const         , * const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, *       volatile, *       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, * const volatile, * const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const          *, const          *);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile *,       volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile *, const volatile *);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,                [2],               );
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const          [2], const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile [2],       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile [2], const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,                [2][3],                [3]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const          [2][3], const          [3]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile [2][3],       volatile [3]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile [2][3], const volatile [3]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,                [5][10][20],                [10][20]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const          [5][10][20], const          [10][20]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile [5][10][20],       volatile [10][20]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile [5][10][20], const volatile [10][20]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,                [],               );
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const          [], const         );
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile [],       volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile [], const volatile);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,                [][3],                [3]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const          [][3], const          [3]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile [][3],       volatile [3]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile [][3], const volatile [3]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,                (&)[2],                (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const          (&)[2], const          (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile (&)[2],       volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile (&)[2], const volatile (&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,                &&,                &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const          &&, const          &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile &&,       volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile &&, const volatile &&);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,                (&&)[2],                (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const          (&&)[2], const          (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent,       volatile (&&)[2],       volatile (&&)[2]);
	BKSGE_TRANSFORM_TEST(bksge::remove_extent, const volatile (&&)[2], const volatile (&&)[2]);
}
