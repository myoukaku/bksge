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

namespace constexpr_try_catch_test
{

#if defined(BKSGE_HAS_CXX20_CONSTEXPR_TRY_CATCH)
constexpr int f(int x)
{
	try
	{
		return x + 1;
	}
	catch (...)
	{
		return 0;
	}
}
#endif

GTEST_TEST(ConfigTest, Cxx20ConstexprTryCatchTest)
{
#if defined(BKSGE_HAS_CXX20_CONSTEXPR_TRY_CATCH)
	static_assert(f(1) == 2, "");
	static_assert(f(2) == 3, "");
#endif
}

}	// namespace constexpr_try_catch_test

namespace concepts_test
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename From, typename To>
concept ConvertibleTo =
	std::is_convertible_v<From, To> &&
	requires(std::add_rvalue_reference_t<From> (&f)())
	{
		static_cast<To>(f());
	};

template <typename T>
concept Integral = std::is_integral_v<T>;

template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template <typename T, typename U>
concept EqualityComparable =
	requires (T a, U b)
	{
		{a == b} -> ConvertibleTo<bool>;
	};

template <typename T>
concept SequenceContainer =
	requires (T c)
	{
		typename T::size_type; // 型Tがメンバ型としてsize_typeを持っていること
		{c.size()} -> ConvertibleTo<typename T::size_type>;     // 型Tのオブジェクトに対して特定のメンバ関数が呼び出せることを要求
		{std::size(c)} -> ConvertibleTo<typename T::size_type>; // 非メンバ関数の呼び出しも要求できる

		typename T::value_type;
		c.push_back(std::declval<typename T::value_type>());
	};

static_assert( Integral<int>, "");
static_assert(!Integral<float>, "");
static_assert(!Integral<std::string>, "");
static_assert(!FloatingPoint<int>, "");
static_assert( FloatingPoint<float>, "");
static_assert(!FloatingPoint<std::string>, "");
static_assert( EqualityComparable<int, int>, "");
static_assert( EqualityComparable<int, float>, "");
static_assert(!EqualityComparable<int, std::string>, "");
static_assert( SequenceContainer<std::vector<int>>, "");
static_assert( SequenceContainer<std::string>, "");
static_assert(!SequenceContainer<int>, "");

template <Integral T>
constexpr int func(T)
{
  return 1;
}

template <FloatingPoint T>
constexpr int func(T)
{
  return 2;
}

static_assert(func(0) == 1, "");
static_assert(func(0.0f) == 2, "");

template <typename T>
requires Integral<T> || FloatingPoint<T>
constexpr bool func2(T)
{
	return true;
}

template <typename T>
requires (!Integral<T>) && (!FloatingPoint<T>)
constexpr bool func2(T)
{
	return false;
}

static_assert( func2(0), "");
static_assert( func2(0.0f), "");
static_assert(!func2("0"), "");

#endif

}	// namespace concepts_test

namespace va_opt_test
{

template <typename... Args>
constexpr int func(Args... args)
{
	return sizeof...(args);
}

GTEST_TEST(ConfigTest, Cxx20VaOptTest)
{
#if defined(BKSGE_HAS_CXX20_VA_OPT)

#define F(X, ...) func(X __VA_OPT__(,) __VA_ARGS__)
	static_assert(F(3) == 1, "");
	static_assert(F(3, "Hello") == 2, "");
	static_assert(F(3, "Hello", 'A') == 3, "");
#undef F

#define F(name, ...) std::vector<int> name __VA_OPT__(= { __VA_ARGS__ })
	F(v1);
	F(v2, 1, 2, 3);

	EXPECT_TRUE(v1.size() == 0);
	EXPECT_TRUE(v2.size() == 3);
#undef F

#endif
}

}	// namespace va_opt_test

namespace nodiscard_with_message_test
{

#if defined(BKSGE_HAS_CXX20_NODISCARD_WITH_MESSAGE)

struct [[nodiscard("with reason 1")]]  error_info {};

error_info f() { return error_info{}; }

[[nodiscard("with reason 2")]]  int g() { return 0; }

#endif

GTEST_TEST(ConfigTest, Cxx20NodiscardWithMessageTest)
{
#if defined(BKSGE_HAS_CXX20_NODISCARD_WITH_MESSAGE)

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4858)	// 戻り値 "..." を破棄しています 
BKSGE_WARNING_DISABLE_CLANG("-Wunused-result")
BKSGE_WARNING_DISABLE_GCC("-Wunused-result")

	f();
	g();

BKSGE_WARNING_POP()

#endif
}

}	// namespace nodiscard_with_message_test

namespace likely_unlikely_test
{

GTEST_TEST(ConfigTest, Cxx20LikelyUnlikelyTest)
{
#if defined(BKSGE_HAS_CXX20_LIKELY) && defined(BKSGE_HAS_CXX20_UNLIKELY)

#if !(defined(BKSGE_GCC_VERSION) && (BKSGE_GCC_VERSION < 100000))
	bool f1 = true;
	bool f2 = false;

	if (f1) [[likely]]
	{
		EXPECT_TRUE(f1);
	}
	if (f2) [[unlikely]]
	{
		EXPECT_TRUE(f1);
	}
#endif

	int n = 10;
	switch (n)
	{
	case 0:
		break;
	[[unlikely]] case 1:
		break;
	[[likely]] default:
		break;
	}

#endif
}

}	// namespace likely_unlikely_test

namespace nontype_template_parameter_class_test
{

#if defined(BKSGE_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_CLASS)

struct A
{
	friend bool operator==(const A&, const A&)
	{
		return true;
	}
};

template<A a> bool f()
{
	const A& ra = a, & rb = a;
	return &ra == &rb;
}

#endif

//GTEST_TEST(ConfigTest, Cxx20NontypeTemplateParameterClassTest)
//{
//	constexpr A a;
//	EXPECT_TRUE(f<a>());
//}

}	// namespace nontype_template_parameter_class_test

#if defined(BKSGE_HAS_CXX20_NONTYPE_TEMPLATE_PARAMETER_FLOAT)
namespace nontype_template_parameter_float_test
{

template <float f>
constexpr float func()
{
	return f * 2;
}

static_assert(func<1.0f>() == 2.0f, "");
static_assert(func<1.5f>() == 3.0f, "");

}	// namespace nontype_template_parameter_float_test
#endif

#if defined(BKSGE_HAS_CXX20_NO_UNIQUE_ADDRESS)
namespace no_unique_address_test
{

struct Empty{};
struct NotEmpty{int i;};

struct A
{
	Empty e;
	NotEmpty ne;
	char c;
};
struct B
{
	[[no_unique_address]] Empty e;
	[[no_unique_address]] NotEmpty ne;
	char c;
};

static_assert(sizeof(A) >= sizeof(B), "");

}	// namespace no_unique_address_test
#endif

}	// namespace bksge_config_cxx20_test
