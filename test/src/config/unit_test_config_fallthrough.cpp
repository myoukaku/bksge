/**
 *	@file	unit_test_config_fallthrough.cpp
 *
 *	@brief	BKSGE_FALLTHROUGH のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/config.hpp>
#include <gtest/gtest.h>

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_CLANG("-Wmissing-declarations")

namespace bksge_config_fallthrough_test
{

void f() {}

void fallthrough_test(int n)
{
	switch (n)
	{
	case 1:
	case 2:
		f();
		BKSGE_FALLTHROUGH();
	case 3:
		if (n < 2)
		{
			f();
		}
		else
		{
			return;
		}
		BKSGE_FALLTHROUGH();
	case 4:
		f();
	}
}

GTEST_TEST(ConfigTest, FallthroughTest)
{
	fallthrough_test(1);
	fallthrough_test(2);
	fallthrough_test(3);
	fallthrough_test(4);
}

}	// namespace bksge_config_fallthrough_test

BKSGE_WARNING_POP()
