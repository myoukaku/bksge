/**
 *	@file	unit_test_preprocessor_cat.cpp
 *
 *	@brief	BKSGE_PP_CATのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/preprocessor/cat.hpp>
#include <gtest/gtest.h>

namespace bksge_preprocessor_cat_test
{

#define BKSGE_GEN_FUNC(name, i)	\
	int BKSGE_PP_CAT(name, BKSGE_PP_CAT(_, i))() \
	{	return i; }

BKSGE_GEN_FUNC(funcA, 0)
BKSGE_GEN_FUNC(funcA, 1)
BKSGE_GEN_FUNC(funcA, 2)
BKSGE_GEN_FUNC(funcB, 1)
BKSGE_GEN_FUNC(funcB, 2)
BKSGE_GEN_FUNC(funcB, 3)
BKSGE_GEN_FUNC(funcB, 4)
BKSGE_GEN_FUNC(funcB, 5)

#undef BKSGE_GEN_FUNC

GTEST_TEST(PreprocessorTest, CatTest)
{
	EXPECT_EQ(0, funcA_0());
	EXPECT_EQ(1, funcA_1());
	EXPECT_EQ(2, funcA_2());
	EXPECT_EQ(1, funcB_1());
	EXPECT_EQ(2, funcB_2());
	EXPECT_EQ(3, funcB_3());
	EXPECT_EQ(4, funcB_4());
	EXPECT_EQ(5, funcB_5());
}

}	// namespace bksge_preprocessor_cat_test
