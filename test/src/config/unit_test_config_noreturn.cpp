/**
 *	@file	unit_test_config_noreturn.cpp
 *
 *	@brief	BKSGE_NORETURN のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/config.hpp>
#include <gtest/gtest.h>
#include <stdexcept>

namespace bksge_config_noreturn_test
{

BKSGE_NORETURN void report_error()
{
	throw std::runtime_error("");
}

int func(int x)
{
	if (x > 0)
	{
		return x;
	}

	report_error();
}

GTEST_TEST(ConfigTest, NoReturnTest)
{
	func(1);
}

}	// namespace bksge_config_noreturn_test
