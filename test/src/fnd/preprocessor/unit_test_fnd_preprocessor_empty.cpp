/**
 *	@file	unit_test_fnd_preprocessor_empty.cpp
 *
 *	@brief	BKSGE_PP_EMPTYのテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/preprocessor/empty.hpp>
#include <gtest/gtest.h>

namespace bksge_preprocessor_empty_test
{

struct foo
{
	foo(int v) : value(v) {}

#define GEN_FUNC(CV)	\
	int CV & get() CV { return value; }

GEN_FUNC(const)
GEN_FUNC(volatile)
GEN_FUNC(const volatile)
GEN_FUNC(BKSGE_PP_EMPTY())

#undef GEN_FUNC

private:
	int value;
};

GTEST_TEST(PreprocessorTest, EmptyTest)
{
	{
		foo f(1);
		EXPECT_EQ(1, f.get());
		f.get() = 2;
		EXPECT_EQ(2, f.get());
	}
	{
		const foo f(3);
		EXPECT_EQ(3, f.get());
	}
	{
		volatile foo f(4);
		EXPECT_EQ(4, f.get());
	}
	{
		const volatile foo f(5);
		EXPECT_EQ(5, f.get());
	}
}

}	// namespace bksge_preprocessor_empty_test
