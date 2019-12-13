/**
 *	@file	unit_test_fnd_preprocessor_variadic_size.cpp
 *
 *	@brief	BKSGE_PP_VARIADIC_SIZEのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/preprocessor/variadic/size.hpp>
#include <gtest/gtest.h>

GTEST_TEST(PreprocessorTest, VariadicSizeTest)
{
	static_assert(BKSGE_PP_VARIADIC_SIZE() == 1, "");
	static_assert(BKSGE_PP_VARIADIC_SIZE(1) == 1, "");
	static_assert(BKSGE_PP_VARIADIC_SIZE(1, 1) == 2, "");
	static_assert(BKSGE_PP_VARIADIC_SIZE(1, 1, 1) == 3, "");
	static_assert(BKSGE_PP_VARIADIC_SIZE(1, 1, 1, 1) == 4, "");
}
