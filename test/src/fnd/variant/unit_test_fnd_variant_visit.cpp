/**
 *	@file	unit_test_fnd_variant_visit.cpp
 *
 *	@brief	visit のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/variant/visit.hpp>
#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/bad_variant_access.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "fnd/variant/test_macros.hpp"
#include "fnd/variant/type_id.hpp"
#include "fnd/variant/variant_test_helpers.hpp"

namespace bksge_variant_test
{

namespace visit_test
{

enum CallType : unsigned
{
	CT_None,
	CT_NonConst = 1,
	CT_Const = 2,
	CT_LValue = 4,
	CT_RValue = 8
};

inline constexpr CallType operator|(CallType LHS, CallType RHS)
{
	return static_cast<CallType>(
		static_cast<unsigned>(LHS) |
		static_cast<unsigned>(RHS));
}

struct ForwardingCallObject
{

	template <typename... Args> bool operator()(Args&&...)&
	{
		set_call<Args&&...>(CT_NonConst | CT_LValue);
		return true;
	}

	template <typename... Args> bool operator()(Args&&...) const&
	{
		set_call<Args&&...>(CT_Const | CT_LValue);
		return true;
	}

	// Don't allow the call operator to be invoked as an rvalue.
	template <typename... Args> bool operator()(Args&&...)&&
	{
		set_call<Args&&...>(CT_NonConst | CT_RValue);
		return true;
	}

	template <typename... Args> bool operator()(Args&&...) const&&
	{
		set_call<Args&&...>(CT_Const | CT_RValue);
		return true;
	}

	template <typename... Args> static void set_call(CallType type)
	{
		EXPECT_EQ(last_call_type, CT_None);
		EXPECT_EQ(last_call_args, nullptr);
		last_call_type = type;
		last_call_args = bksge::addressof(makeArgumentID<Args...>());
	}

	template <typename... Args> static bool check_call(CallType type)
	{
		bool result = last_call_type == type && last_call_args &&
			*last_call_args == makeArgumentID<Args...>();
		last_call_type = CT_None;
		last_call_args = nullptr;
		return result;
	}

	static CallType last_call_type;
	static const TypeID* last_call_args;
};

CallType ForwardingCallObject::last_call_type = CT_None;
const TypeID* ForwardingCallObject::last_call_args = nullptr;

void test_call_operator_forwarding()
{
	using Fn = ForwardingCallObject;
	Fn obj{};
	const Fn& cobj = obj;
	{
		// test call operator forwarding - no variant
		bksge::visit(obj);
		EXPECT_TRUE(Fn::check_call<>(CT_NonConst | CT_LValue));
		bksge::visit(cobj);
		EXPECT_TRUE(Fn::check_call<>(CT_Const | CT_LValue));
		bksge::visit(bksge::move(obj));
		EXPECT_TRUE(Fn::check_call<>(CT_NonConst | CT_RValue));
		bksge::visit(bksge::move(cobj));
		EXPECT_TRUE(Fn::check_call<>(CT_Const | CT_RValue));
	}
	{
		// test call operator forwarding - single variant, single arg
		using V = bksge::variant<int>;
		V v(42);
		bksge::visit(obj, v);
		EXPECT_TRUE(Fn::check_call<int&>(CT_NonConst | CT_LValue));
		bksge::visit(cobj, v);
		EXPECT_TRUE(Fn::check_call<int&>(CT_Const | CT_LValue));
		bksge::visit(bksge::move(obj), v);
		EXPECT_TRUE(Fn::check_call<int&>(CT_NonConst | CT_RValue));
		bksge::visit(bksge::move(cobj), v);
		EXPECT_TRUE(Fn::check_call<int&>(CT_Const | CT_RValue));
	}
	{
		// test call operator forwarding - single variant, multi arg
		using V = bksge::variant<int, long, double>;
		V v(42l);
		bksge::visit(obj, v);
		EXPECT_TRUE(Fn::check_call<long&>(CT_NonConst | CT_LValue));
		bksge::visit(cobj, v);
		EXPECT_TRUE(Fn::check_call<long&>(CT_Const | CT_LValue));
		bksge::visit(bksge::move(obj), v);
		EXPECT_TRUE(Fn::check_call<long&>(CT_NonConst | CT_RValue));
		bksge::visit(bksge::move(cobj), v);
		EXPECT_TRUE(Fn::check_call<long&>(CT_Const | CT_RValue));
	}
	{
		// test call operator forwarding - multi variant, multi arg
		using V = bksge::variant<int, long, double>;
		using V2 = bksge::variant<int*, bksge::string>;
		V v(42l);
		V2 v2("hello");
		bksge::visit(obj, v, v2);
		EXPECT_TRUE((Fn::check_call<long&, bksge::string&>(CT_NonConst | CT_LValue)));
		bksge::visit(cobj, v, v2);
		EXPECT_TRUE((Fn::check_call<long&, bksge::string&>(CT_Const | CT_LValue)));
		bksge::visit(bksge::move(obj), v, v2);
		EXPECT_TRUE((Fn::check_call<long&, bksge::string&>(CT_NonConst | CT_RValue)));
		bksge::visit(bksge::move(cobj), v, v2);
		EXPECT_TRUE((Fn::check_call<long&, bksge::string&>(CT_Const | CT_RValue)));
	}
}

void test_argument_forwarding()
{
	using Fn = ForwardingCallObject;
	Fn obj{};
	const auto Val = CT_LValue | CT_NonConst;
	{
		// single argument - value type
		using V = bksge::variant<int>;
		V v(42);
		const V& cv = v;
		bksge::visit(obj, v);
		EXPECT_TRUE(Fn::check_call<int&>(Val));
		bksge::visit(obj, cv);
		EXPECT_TRUE(Fn::check_call<const int&>(Val));
		bksge::visit(obj, bksge::move(v));
		EXPECT_TRUE(Fn::check_call<int&&>(Val));
		bksge::visit(obj, bksge::move(cv));
		EXPECT_TRUE(Fn::check_call<const int&&>(Val));
	}
#if !defined(TEST_VARIANT_HAS_NO_REFERENCES)
	{
		// single argument - lvalue reference
		using V = bksge::variant<int&>;
		int x = 42;
		V v(x);
		const V& cv = v;
		bksge::visit(obj, v);
		EXPECT_TRUE(Fn::check_call<int&>(Val));
		bksge::visit(obj, cv);
		EXPECT_TRUE(Fn::check_call<int&>(Val));
		bksge::visit(obj, bksge::move(v));
		EXPECT_TRUE(Fn::check_call<int&>(Val));
		bksge::visit(obj, bksge::move(cv));
		EXPECT_TRUE(Fn::check_call<int&>(Val));
	}
	{
		// single argument - rvalue reference
		using V = bksge::variant<int&&>;
		int x = 42;
		V v(bksge::move(x));
		const V& cv = v;
		bksge::visit(obj, v);
		EXPECT_TRUE(Fn::check_call<int&>(Val));
		bksge::visit(obj, cv);
		EXPECT_TRUE(Fn::check_call<int&>(Val));
		bksge::visit(obj, bksge::move(v));
		EXPECT_TRUE(Fn::check_call<int&&>(Val));
		bksge::visit(obj, bksge::move(cv));
		EXPECT_TRUE(Fn::check_call<int&&>(Val));
	}
	{
		// multi argument - multi variant
		using S = const bksge::string&;
		using V = bksge::variant<int, S, long&&>;
		const bksge::string str = "hello";
		long l = 43;
		V v1(42);
		const V& cv1 = v1;
		V v2(str);
		const V& cv2 = v2;
		V v3(bksge::move(l));
		const V& cv3 = v3;
		bksge::visit(obj, v1, v2, v3);
		EXPECT_TRUE((Fn::check_call<int&, S, long&>(Val)));
		bksge::visit(obj, cv1, cv2, bksge::move(v3));
		EXPECT_TRUE((Fn::check_call<const int&, S, long&&>(Val)));
	}
#endif
}

struct ReturnFirst
{
	template <typename... Args>
	constexpr int operator()(int f, Args&&...) const
	{
		return f;
	}
};

struct ReturnArity
{
	template <typename... Args>
	constexpr int operator()(Args&&...) const
	{
		return sizeof...(Args);
	}
};

void test_constexpr()
{
	constexpr ReturnFirst obj{};
	constexpr ReturnArity aobj{};
	{
		using V = bksge::variant<int>;
		constexpr V v(42);
		static_assert(bksge::visit(obj, v) == 42, "");
	}
	{
		using V = bksge::variant<short, long, char>;
		constexpr V v(42l);
		static_assert(bksge::visit(obj, v) == 42, "");
	}
	{
		using V1 = bksge::variant<int>;
		using V2 = bksge::variant<int, char*, long long>;
		using V3 = bksge::variant<bool, int, int>;
		constexpr V1 v1;
		constexpr V2 v2(nullptr);
		constexpr V3 v3;
		static_assert(bksge::visit(aobj, v1, v2, v3) == 3, "");
	}
	{
		using V1 = bksge::variant<int>;
		using V2 = bksge::variant<int, char*, long long>;
		using V3 = bksge::variant<void*, int, int>;
		constexpr V1 v1;
		constexpr V2 v2(nullptr);
		constexpr V3 v3;
		static_assert(bksge::visit(aobj, v1, v2, v3) == 3, "");
	}
}

#if !defined(BKSGE_NO_EXCEPTIONS)
struct Test
{
	ReturnArity& m_obj;
	template <typename... Args>
	bool operator()(Args&&... args) const
	{
		try
		{
			bksge::visit(m_obj, args...);
		}
		catch (const bksge::bad_variant_access&)
		{
			return true;
		}
		catch (...)
		{
		}
		return false;
	}
};
#endif

void test_exceptions()
{
#if !defined(BKSGE_NO_EXCEPTIONS)
	ReturnArity obj{};
	Test test{obj};
	{
		using V = bksge::variant<int, MakeEmptyT>;
		V v;
		makeEmpty(v);
		EXPECT_TRUE(test(v));
	}
	{
		using V = bksge::variant<int, MakeEmptyT>;
		using V2 = bksge::variant<long, bksge::string, void*>;
		V v;
		makeEmpty(v);
		V2 v2("hello");
		EXPECT_TRUE(test(v, v2));
	}
	{
		using V = bksge::variant<int, MakeEmptyT>;
		using V2 = bksge::variant<long, bksge::string, void*>;
		V v;
		makeEmpty(v);
		V2 v2("hello");
		EXPECT_TRUE(test(v2, v));
	}
	{
		using V = bksge::variant<int, MakeEmptyT>;
		using V2 = bksge::variant<long, bksge::string, void*, MakeEmptyT>;
		V v;
		makeEmpty(v);
		V2 v2;
		makeEmpty(v2);
		EXPECT_TRUE(test(v, v2));
	}
#endif
}

// See https://bugs.llvm.org/show_bug.cgi?id=31916
void test_caller_accepts_nonconst()
{
	struct A {};
	struct Visitor
	{
		void operator()(A&) {}
	};
	bksge::variant<A> v;
	bksge::visit(Visitor{}, v);
}

GTEST_TEST(VariantTest, VariantVisitTest)
{
	test_call_operator_forwarding();
	test_argument_forwarding();
	test_constexpr();
	test_exceptions();
	test_caller_accepts_nonconst();
}

}	// namespace visit_test

}	// namespace bksge_variant_test
