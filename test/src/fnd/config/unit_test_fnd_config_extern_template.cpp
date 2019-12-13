/**
 *	@file	unit_test_fnd_config_extern_template.cpp
 *
 *	@brief	BKSGE_EXTERN_TEMPLATE のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>

namespace bksge_config_extern_template_test
{

template <typename T>
class Class1 {};

template <typename T1, typename T2>
class Class2 {};

template <typename T>
void Function1() {}

template <typename T1, typename T2>
void Function2(T1, T2) {}

BKSGE_EXTERN_TEMPLATE(class Class1<int>);
BKSGE_EXTERN_TEMPLATE(class Class1<char>);
BKSGE_EXTERN_TEMPLATE(class Class2<int, float>);
BKSGE_EXTERN_TEMPLATE(void Function1<int>());
BKSGE_EXTERN_TEMPLATE(void Function1<float>());
BKSGE_EXTERN_TEMPLATE(void Function2<int, char>(int, char));

//template class Class1<int>;
template void Function1<int>();
template void Function2<int, char>(int, char);

GTEST_TEST(ConfigTest, ExternTemplateTest)
{
	{
		Class1<int> x;
		(void)x;
	}
	{
		Class2<int, float> x;
		(void)x;
	}
	{
		Function1<int>();
	}
	{
		int i = 0;
		char c = 0;
		Function2(i, c);
	}
}

}	// namespace bksge_config_extern_template_test
