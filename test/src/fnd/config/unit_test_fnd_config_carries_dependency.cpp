/**
 *	@file	unit_test_fnd_config_carries_dependency.cpp
 *
 *	@brief	BKSGE_CARRIES_DEPENDENCY のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_config_carries_dependency_test
{

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4648)	// 標準属性 'carries_dependency' は無視されます

BKSGE_CARRIES_DEPENDENCY void f()
{
}

void g(int* r BKSGE_CARRIES_DEPENDENCY)
{
	(void)r;
}

BKSGE_WARNING_POP()

GTEST_TEST(ConfigTest, CarriesDependencyTest)
{
	f();
	g(nullptr);
}

}	// namespace bksge_config_carries_dependency_test
