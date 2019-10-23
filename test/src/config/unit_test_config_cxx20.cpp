/**
 *	@file	unit_test_config_cxx20.cpp
 *
 *	@brief	
 *
 *	@author	myoukaku
 */

#include <bksge/config.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <string>

namespace bksge_config_cxx20_test
{

GTEST_TEST(ConfigTest, Cxx20BitfieldDefaultMemberInitializerTest)
{
#if defined(BKSGE_HAS_CXX20_BITFIELD_DEFAULT_MEMBER_INITIALIZER)
	struct X
	{
		int a : 6 = 8;
		int b : 2 {1};
	};

	X x;
	EXPECT_EQ(8, x.a);
	EXPECT_EQ(1, x.b);
#endif
}

GTEST_TEST(ConfigTest, Cxx20ConstQualifiedPointersToMembersTest)
{
	struct X { void foo() const& {} };

	X{}.foo();
#if defined(BKSGE_HAS_CXX20_CONST_QUALIFIED_POINTERS_TO_MEMBERS)
	(X{}.*&X::foo)();
#endif
}

GTEST_TEST(ConfigTest, Cxx20CaptureCopyThisTest)
{
#if defined(BKSGE_HAS_CXX20_CAPTURE_COPY_THIS)
	struct X
	{
		void f()
		{
			int value = 3;
			auto x = [=, this] { // [=]キャプチャと等価
				return value + g();
			};
			EXPECT_EQ(5, x());
		}

		int g() const
		{
			return 2;
		}
	};
	X().f();
#endif
}

GTEST_TEST(ConfigTest, Cxx20TemplateLambdaTest)
{
#if defined(BKSGE_HAS_CXX20_TEMPLATE_LAMBDA)
	auto f =[]<class T>(const std::vector<T>& v)
	{
		if (v.empty())
		{
			return T();
		}
		else
		{
			return v.front();
		}
	};

	std::vector<int> v = {1, 2, 3};
	std::vector<std::string> w;

	EXPECT_EQ(1,  f(v)); // Tの型はint
	EXPECT_EQ("", f(w)); // Tの型はstd::string
#endif
}

}	// namespace bksge_config_cxx20_test
