/**
 *	@file	unit_test_fnd_tuple_apply.cpp
 *
 *	@brief	apply のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/apply.hpp>
//#include <bksge/fnd/array.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <tuple>
#include <utility>
#include <gtest/gtest.h>
#include "tuple_test_utility.hpp"
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace apply_test
{

constexpr int constexpr_sum_fn() { return 0; }

template <typename ...Ints>
constexpr int constexpr_sum_fn(int x1, Ints... rest)
{
	return x1 + constexpr_sum_fn(rest...);
}

struct ConstexprSumT
{
	constexpr ConstexprSumT() = default;

	template <typename ...Ints>
	constexpr int operator()(Ints... values) const
	{
		return constexpr_sum_fn(values...);
	}
};

void test_constexpr_evaluation()
{
	constexpr ConstexprSumT sum_obj{};
	{
		using Tup = std::tuple<>;
		using Fn = int(&)();
		BKSGE_CXX14_CONSTEXPR Tup t{};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(static_cast<Fn>(constexpr_sum_fn), t), 0);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(sum_obj, t), 0);
	}
	{
		using Tup = std::tuple<int>;
		using Fn = int(&)(int);
		BKSGE_CXX14_CONSTEXPR Tup t(42);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(static_cast<Fn>(constexpr_sum_fn), t), 42);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(sum_obj, t), 42);
	}
	{
		using Tup = std::tuple<int, long>;
		using Fn = int(&)(int, int);
		BKSGE_CXX14_CONSTEXPR Tup t(42, 101);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(static_cast<Fn>(constexpr_sum_fn), t), 143);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(sum_obj, t), 143);
	}
	{
		using Tup = std::pair<int, long>;
		using Fn = int(&)(int, int);
		BKSGE_CXX14_CONSTEXPR Tup t(42, 101);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(static_cast<Fn>(constexpr_sum_fn), t), 143);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(sum_obj, t), 143);
	}
	{
		using Tup = std::tuple<int, long, int>;
		using Fn = int(&)(int, int, int);
		BKSGE_CXX14_CONSTEXPR Tup t(42, 101, -1);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(static_cast<Fn>(constexpr_sum_fn), t), 142);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(sum_obj, t), 142);
	}
#if 0	// TODO
	{
		using Tup = bksge::array<int, 3>;
		using Fn = int(&)(int, int, int);
		BKSGE_CXX14_CONSTEXPR Tup t ={{42, 101, -1}};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(static_cast<Fn>(constexpr_sum_fn), t), 142);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::apply(sum_obj, t), 142);
	}
#endif
}


enum CallQuals
{
	CQ_None,
	CQ_LValue,
	CQ_ConstLValue,
	CQ_RValue,
	CQ_ConstRValue
};

template <typename Tuple>
struct CallInfo
{
	CallQuals quals;
	TypeID const* arg_types;
	Tuple args;

	template <typename ...Args>
	CallInfo(CallQuals q, Args&&... xargs)
		: quals(q), arg_types(&makeArgumentID<Args&&...>()), args(bksge::forward<Args>(xargs)...)
	{}
};

template <typename ...Args>
inline CallInfo<decltype(std::forward_as_tuple(std::declval<Args>()...))>
makeCallInfo(CallQuals quals, Args&&... args)
{
	return{quals, bksge::forward<Args>(args)...};
}

struct TrackedCallable
{
	TrackedCallable() = default;

	template <typename ...Args> auto operator()(Args&&... xargs) &
	->decltype(makeCallInfo(CQ_LValue, bksge::forward<Args>(xargs)...))
	{
		return makeCallInfo(CQ_LValue, bksge::forward<Args>(xargs)...);
	}

	template <typename ...Args> auto operator()(Args&&... xargs) const&
	->decltype(makeCallInfo(CQ_ConstLValue, bksge::forward<Args>(xargs)...))
	{
		return makeCallInfo(CQ_ConstLValue, bksge::forward<Args>(xargs)...);
	}

	template <typename ...Args> auto operator()(Args&&... xargs) &&
	->decltype(makeCallInfo(CQ_RValue, bksge::forward<Args>(xargs)...))
	{
		return makeCallInfo(CQ_RValue, bksge::forward<Args>(xargs)...);
	}

	template <typename ...Args> auto operator()(Args&&... xargs) const&&
	->decltype(makeCallInfo(CQ_ConstRValue, bksge::forward<Args>(xargs)...))
	{
		return makeCallInfo(CQ_ConstRValue, bksge::forward<Args>(xargs)...);
	}
};

template <typename ...ExpectArgs, typename Tuple>
void check_apply_quals_and_types(Tuple&& t)
{
	TypeID const* const expect_args = &makeArgumentID<ExpectArgs...>();
	TrackedCallable obj;
	TrackedCallable const& cobj = obj;
	{
		auto ret = bksge::apply(obj, bksge::forward<Tuple>(t));
		EXPECT_EQ(ret.quals, CQ_LValue);
		EXPECT_EQ(ret.arg_types, expect_args);
		EXPECT_EQ(ret.args, t);
	}
	{
		auto ret = bksge::apply(cobj, bksge::forward<Tuple>(t));
		EXPECT_EQ(ret.quals, CQ_ConstLValue);
		EXPECT_EQ(ret.arg_types, expect_args);
		EXPECT_EQ(ret.args, t);
	}
	{
		auto ret = bksge::apply(bksge::move(obj), bksge::forward<Tuple>(t));
		EXPECT_EQ(ret.quals, CQ_RValue);
		EXPECT_EQ(ret.arg_types, expect_args);
		EXPECT_EQ(ret.args, t);
	}
	{
		auto ret = bksge::apply(bksge::move(cobj), bksge::forward<Tuple>(t));
		EXPECT_EQ(ret.quals, CQ_ConstRValue);
		EXPECT_EQ(ret.arg_types, expect_args);
		EXPECT_EQ(ret.args, t);
	}
}

void test_call_quals_and_arg_types()
{
	using Tup = std::tuple<int, int const&, unsigned&&>;
	const int x = 42;
	unsigned y = 101;
	Tup t(-1, x, bksge::move(y));
	Tup const& ct = t;
	check_apply_quals_and_types<int&, int const&, unsigned&>(t);
	check_apply_quals_and_types<int const&, int const&, unsigned&>(ct);
	check_apply_quals_and_types<int&&, int const&, unsigned&&>(bksge::move(t));
	check_apply_quals_and_types<int const&&, int const&, unsigned&&>(bksge::move(ct));
}

struct NothrowMoveable
{
	NothrowMoveable() noexcept = default;
	NothrowMoveable(NothrowMoveable const&) noexcept(false) {}
	NothrowMoveable(NothrowMoveable&&) noexcept {}
};

template <bool IsNoexcept>
struct TestNoexceptCallable
{
	template <typename ...Args>
	NothrowMoveable operator()(Args...) const noexcept(IsNoexcept) { return{}; }
};

void test_noexcept()
{
#if 0	// TODO
	TestNoexceptCallable<true> nec;
	TestNoexceptCallable<false> tc;
	(void)nec;
	(void)tc;
	{
		// test that the functions noexcept-ness is propagated
		using Tup = std::tuple<int, const char*, long>;
		Tup t;
		ASSERT_NOEXCEPT(bksge::apply(nec, t));
		ASSERT_NOT_NOEXCEPT(bksge::apply(tc, t));
	}
	{
		// test that the noexcept-ness of the argument conversions is checked.
		using Tup = std::tuple<NothrowMoveable, int>;
		Tup t;
		ASSERT_NOT_NOEXCEPT(bksge::apply(nec, t));
		ASSERT_NOEXCEPT(bksge::apply(nec, bksge::move(t)));
	}
#endif
}

namespace ReturnTypeTest
{

static int my_int = 42;

template <int N> struct index {};

void f(index<0>) {}

int f(index<1>) { return 0; }

int & f(index<2>) { return static_cast<int &>(my_int); }
int const & f(index<3>) { return static_cast<int const &>(my_int); }
int volatile & f(index<4>) { return static_cast<int volatile &>(my_int); }
int const volatile & f(index<5>) { return static_cast<int const volatile &>(my_int); }

int && f(index<6>) { return static_cast<int &&>(my_int); }
int const && f(index<7>) { return static_cast<int const &&>(my_int); }
int volatile && f(index<8>) { return static_cast<int volatile &&>(my_int); }
int const volatile && f(index<9>) { return static_cast<int const volatile &&>(my_int); }

int * f(index<10>) { return static_cast<int *>(&my_int); }
int const * f(index<11>) { return static_cast<int const *>(&my_int); }
int volatile * f(index<12>) { return static_cast<int volatile *>(&my_int); }
int const volatile * f(index<13>) { return static_cast<int const volatile *>(&my_int); }

template <int Func, typename Expect>
void test()
{
	using RawInvokeResult = decltype(f(index<Func>{}));
	static_assert(bksge::is_same<RawInvokeResult, Expect>::value, "");
	using FnType = RawInvokeResult (*) (index<Func>);
	FnType fn = f;
	std::tuple<index<Func>> t; ((void)t);
	using InvokeResult = decltype(bksge::apply(fn, t));
	static_assert(bksge::is_same<InvokeResult, Expect>::value, "");
	(void)fn;
}

} // end namespace ReturnTypeTest

void test_return_type()
{
	using ReturnTypeTest::test;
	test<0, void>();
	test<1, int>();
	test<2, int &>();
	test<3, int const &>();
	test<4, int volatile &>();
	test<5, int const volatile &>();
	test<6, int &&>();
	test<7, int const &&>();
	test<8, int volatile &&>();
	test<9, int const volatile &&>();
	test<10, int *>();
	test<11, int const *>();
	test<12, int volatile *>();
	test<13, int const volatile *>();
}

GTEST_TEST(TupleTest, ApplyTest)
{
	test_constexpr_evaluation();
	test_call_quals_and_arg_types();
	test_return_type();
	test_noexcept();
}

}	// namespace apply_test

}	// namespace bksge_tuple_test
