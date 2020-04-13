/**
 *	@file	unit_test_fnd_config_cxx20.cpp
 *
 *	@brief	
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <map>
#include <type_traits>

#if BKSGE_HAS_INCLUDE(<compare>) && (BKSGE_CXX_STANDARD >= 20)
#include <compare>
#endif

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

GTEST_TEST(ConfigTest, Cxx20DesignatedInitializersTest)
{
#if defined(BKSGE_HAS_CXX20_DESIGNATED_INITIALIZERS)
	struct A { int x; int y; int z; };

	A a{.x = 1, .y = 2, .z = 3};
	EXPECT_EQ(1, a.x);
	EXPECT_EQ(2, a.y);
	EXPECT_EQ(3, a.z);

	A b{.x = 1, .z = 2};
	EXPECT_EQ(1, b.x);
	EXPECT_EQ(0, b.y);
	EXPECT_EQ(2, b.z);

	A c{.y = 1};
	EXPECT_EQ(0, c.x);
	EXPECT_EQ(1, c.y);
	EXPECT_EQ(0, c.z);

	union U { int a; const char* b; };

	U d ={.a = 42};
	EXPECT_EQ(42, d.a);

	U e ={.b = "asdf"};
	EXPECT_STREQ("asdf", e.b);
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

GTEST_TEST(ConfigTest, Cxx20RangeBasedForInitializerTest)
{
#if defined(BKSGE_HAS_CXX20_RANGE_BASED_FOR_INITIALIZER)
	std::vector<int> v {10, 20, 30};
	for (int i = 0; auto& x : v)
	{
		x += i;
		i++;
	}

	EXPECT_EQ(10, v[0]);
	EXPECT_EQ(21, v[1]);
	EXPECT_EQ(32, v[2]);
#endif
}

GTEST_TEST(ConfigTest, Cxx20ThreeWayComparisonTest)
{
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON) && BKSGE_HAS_INCLUDE(<compare>)
	struct X
	{
		int x;
		int y;
		auto operator<=>(const X&) const = default;
	};

	X x1 = {10, 20};
	X x2 = {10, 20};
	X x3 = {11, 20};
	X x4 = {10, 19};

	EXPECT_TRUE ((x1 <=> x2) == 0);
	EXPECT_FALSE((x1 <=> x2) >  0);
	EXPECT_FALSE((x1 <=> x2) <  0);
	EXPECT_FALSE((x1 <=> x3) == 0);
	EXPECT_FALSE((x1 <=> x3) >  0);
	EXPECT_TRUE ((x1 <=> x3) <  0);
	EXPECT_FALSE((x1 <=> x4) == 0);
	EXPECT_TRUE ((x1 <=> x4) >  0);
	EXPECT_FALSE((x1 <=> x4) <  0);

	EXPECT_TRUE (x1 == x2);
	EXPECT_FALSE(x1 != x2);
	EXPECT_FALSE(x1 <  x2);
	EXPECT_FALSE(x1 >  x2);
	EXPECT_TRUE (x1 <= x2);
	EXPECT_TRUE (x1 >= x2);

	EXPECT_FALSE(x1 == x3);
	EXPECT_TRUE (x1 != x3);
	EXPECT_TRUE (x1 <  x3);
	EXPECT_FALSE(x1 >  x3);
	EXPECT_TRUE (x1 <= x3);
	EXPECT_FALSE(x1 >= x3);

	EXPECT_FALSE(x1 == x4);
	EXPECT_TRUE (x1 != x4);
	EXPECT_FALSE(x1 <  x4);
	EXPECT_TRUE (x1 >  x4);
	EXPECT_FALSE(x1 <= x4);
	EXPECT_TRUE (x1 >= x4);
#endif
}

GTEST_TEST(ConfigTest, Cxx20DefaultConstructibleAndAssignableStatelessLambdasTest)
{
#if defined(BKSGE_HAS_CXX20_DEFAULT_CONSTRUCTIBLE_AND_ASSIGNABLE_STATELESS_LAMBDAS)
	auto greater = [](auto x, auto y) { return x > y; };
	decltype(greater) f;
	f = greater;
#endif
}

namespace conditional_explicit_test
{

#if defined(BKSGE_HAS_CXX20_CONDITIONAL_EXPLICIT)
template <bool B>
struct S
{
	explicit(B) S() {}
	explicit(B) operator bool() const { return true; }
};
#endif

GTEST_TEST(ConfigTest, Cxx20ConditionalExplicitTest)
{
#if defined(BKSGE_HAS_CXX20_CONDITIONAL_EXPLICIT)
	static_assert( std::is_default_constructible<S<true>>::value, "");
	static_assert( std::is_default_constructible<S<false>>::value, "");

	static_assert(!bksge::is_implicitly_default_constructible<S<true>>::value, "");
	static_assert( bksge::is_implicitly_default_constructible<S<false>>::value, "");

	S<true> x1;
	S<false> x2;
//	bool b1 = x1;
	bool b2 = x2;
	bool b3 = static_cast<bool>(x1);
	bool b4 = static_cast<bool>(x2);

	(void)b2;
	(void)b3;
	(void)b4;
#endif
}

}	// namespace conditional_explicit_test

namespace char8_t_test
{

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
template <typename> struct S { static const bool value = false; };
template <> struct S<char8_t> { static const bool value = true; };
#endif

GTEST_TEST(ConfigTest, Cxx20Char8TTest)
{
#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	{
		const char8_t* s = u8"hoge";
		const char8_t c = u8'c';
		(void)s;
		(void)c;
	}
	{
		const auto* s = u8"hoge";
		const auto c = u8'c';
		static_assert(std::is_same<const char8_t*, decltype(s)>::value, "");
		static_assert(std::is_same<const char8_t, decltype(c)>::value, "");
	}

	static_assert(sizeof(char8_t) == sizeof(unsigned char), "");
	static_assert(!std::is_same<char8_t, char>::value, "");
	static_assert(!std::is_same<char8_t, unsigned char>::value, "");

	static_assert(S<char8_t>::value, "");
	static_assert(!S<char>::value, "");
	static_assert(!S<unsigned char>::value, "");
#endif
}

}	// namespace char8_t_test

}	// namespace bksge_config_cxx20_test
