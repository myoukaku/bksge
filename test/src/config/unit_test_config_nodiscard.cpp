/**
 *	@file	unit_test_config_nodiscard.cpp
 *
 *	@brief	BKSGE_NODISCARD のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/config.hpp>
#include <gtest/gtest.h>

namespace bksge_config_nodiscard_test
{

BKSGE_NODISCARD int func()
{
	return 42;
}

GTEST_TEST(ConfigTest, NoDiscardTest)
{
	//func();
	int t = func();
	(void)t;
}

}	// namespace bksge_config_nodiscard_test
