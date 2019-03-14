/**
 *	@file	unit_test_preprocessor_stringize.cpp
 *
 *	@brief	BKSGE_PP_STRINGIZEのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/preprocessor/stringize.hpp>
#include <bksge/preprocessor/cat.hpp>
#include <gtest/gtest.h>

namespace bksge_preprocessor_stringize_test
{

GTEST_TEST(PreprocessorTest, StringizeTest)
{
	EXPECT_STREQ("ab", BKSGE_PP_STRINGIZE(BKSGE_PP_CAT(a, b)));
}

}	// namespace bksge_preprocessor_stringize_test
