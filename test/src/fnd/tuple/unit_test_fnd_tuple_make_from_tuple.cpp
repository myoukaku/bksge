/**
 *	@file	unit_test_fnd_tuple_make_from_tuple.cpp
 *
 *	@brief	make_from_tuple のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/make_from_tuple.hpp>
#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/pair/get.hpp>
//#include <bksge/fnd/array.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <tuple>
#include <gtest/gtest.h>
#include "tuple_test_utility.hpp"
#include "constexpr_test.hpp"

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_CLANG("-Wmissing-braces")

namespace bksge_tuple_test
{

namespace make_from_tuple_test
{

template <typename Tuple>
struct ConstexprConstructibleFromTuple
{
	template <typename ...Args>
	explicit constexpr ConstexprConstructibleFromTuple(Args&&... xargs)
		: args{bksge::forward<Args>(xargs)...}
	{}
	
	Tuple args;
};

template <typename TupleLike>
struct ConstructibleFromTuple;

template <template <typename ...> class Tuple, typename ...Types>
struct ConstructibleFromTuple<Tuple<Types...>>
{
	template <typename ...Args>
	explicit ConstructibleFromTuple(Args&&... xargs)
		: args(xargs...)
		, arg_types(&makeArgumentID<Args&&...>())
	{}

	Tuple<bksge::decay_t<Types>...> args;
	TypeID const* arg_types;
};

#if 0	// TODO
template <typename Tp, size_t N>
struct ConstructibleFromTuple<bksge::array<Tp, N>>
{
	template <typename ...Args>
	explicit ConstructibleFromTuple(Args&&... xargs)
		: args{xargs...}
		, arg_types(&makeArgumentID<Args&&...>())
	{}

	bksge::array<Tp, N> args;
	TypeID const* arg_types;
};
#endif

template <typename Tuple>
constexpr bool do_constexpr_test(Tuple&& tup)
{
	using RawTuple = bksge::decay_t<Tuple>;
	using Tp = ConstexprConstructibleFromTuple<RawTuple>;
	return bksge::make_from_tuple<Tp>(bksge::forward<Tuple>(tup)).args == tup;
}

// Needed by do_forwarding_test() since it compares pairs of different types.
template <typename T1, typename T2, typename U1, typename U2>
inline bool operator==(const bksge::pair<T1, T2>& lhs, const bksge::pair<U1, U2>& rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <typename ...ExpectTypes, typename Tuple>
bool do_forwarding_test(Tuple&& tup)
{
	using RawTuple = bksge::decay_t<Tuple>;
	using Tp = ConstructibleFromTuple<RawTuple>;
	const Tp value = bksge::make_from_tuple<Tp>(bksge::forward<Tuple>(tup));
	return value.args == tup &&
		value.arg_types == &makeArgumentID<ExpectTypes...>();
}

void test_constexpr_construction()
{
	{
		BKSGE_CXX14_CONSTEXPR std::tuple<> tup{};
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_constexpr_test(tup));
	}
	{
		BKSGE_CXX14_CONSTEXPR std::tuple<int> tup(42);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_constexpr_test(tup));
	}
	{
		BKSGE_CXX14_CONSTEXPR std::tuple<int, long, void*> tup(42, 101, nullptr);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_constexpr_test(tup));
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::pair<int, const char*> p(42, "hello world");
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(do_constexpr_test(p));
	}
#if 0	// TODO
	{
		using Tuple = bksge::array<int, 3>;
		using ValueTp = ConstexprConstructibleFromTuple<Tuple>;
		BKSGE_CXX14_CONSTEXPR Tuple arr ={{42, 101, -1}};
		BKSGE_CXX14_CONSTEXPR ValueTp value = bksge::make_from_tuple<ValueTp>(arr);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(
			value.args[0] == arr[0] &&
			value.args[1] == arr[1] &&
			value.args[2] == arr[2]);
	}
#endif
}

void test_perfect_forwarding()
{
	{
		using Tup = std::tuple<>;
		Tup tup;
		Tup const& ctup = tup;
		EXPECT_TRUE(do_forwarding_test<>(tup));
		EXPECT_TRUE(do_forwarding_test<>(ctup));
	}
	{
		using Tup = std::tuple<int>;
		Tup tup(42);
		Tup const& ctup = tup;
		EXPECT_TRUE(do_forwarding_test<int&>(tup));
		EXPECT_TRUE(do_forwarding_test<int const&>(ctup));
		EXPECT_TRUE(do_forwarding_test<int&&>(bksge::move(tup)));
		EXPECT_TRUE(do_forwarding_test<int const&&>(bksge::move(ctup)));
	}
	{
		using Tup = std::tuple<int&, const char*, unsigned&&>;
		int x = 42;
		unsigned y = 101;
		Tup tup(x, "hello world", bksge::move(y));
		Tup const& ctup = tup;
		EXPECT_TRUE((do_forwarding_test<int&, const char*&, unsigned&>(tup)));
		EXPECT_TRUE((do_forwarding_test<int&, const char* const&, unsigned &>(ctup)));
		EXPECT_TRUE((do_forwarding_test<int&, const char*&&, unsigned&&>(bksge::move(tup))));
		EXPECT_TRUE((do_forwarding_test<int&, const char* const&&, unsigned &&>(bksge::move(ctup))));
	}
	// test with pair<T, U>
	{
		using Tup = bksge::pair<int&, const char*>;
		int x = 42;
		Tup tup(x, "hello world");
		Tup const& ctup = tup;
		EXPECT_TRUE((do_forwarding_test<int&, const char*&>(tup)));
		EXPECT_TRUE((do_forwarding_test<int&, const char* const&>(ctup)));
		EXPECT_TRUE((do_forwarding_test<int&, const char*&&>(bksge::move(tup))));
		EXPECT_TRUE((do_forwarding_test<int&, const char* const&&>(bksge::move(ctup))));
	}
#if 0	// TODO
	// test with array<T, I>
	{
		using Tup = bksge::array<int, 3>;
		Tup tup ={{42, 101, -1}};
		Tup const& ctup = tup;
		EXPECT_TRUE((do_forwarding_test<int&, int&, int&>(tup)));
		EXPECT_TRUE((do_forwarding_test<int const&, int const&, int const&>(ctup)));
		EXPECT_TRUE((do_forwarding_test<int&&, int&&, int&&>(bksge::move(tup))));
		EXPECT_TRUE((do_forwarding_test<int const&&, int const&&, int const&&>(bksge::move(ctup))));
	}
#endif
}

void test_noexcept()
{
#if 0	// TODO
	struct NothrowMoveable
	{
		NothrowMoveable() = default;
		NothrowMoveable(NothrowMoveable const&) {}
		NothrowMoveable(NothrowMoveable&&) noexcept {}
	};

	struct TestType
	{
		TestType(int, NothrowMoveable) noexcept {}
		TestType(int, int, int) noexcept(false) {}
		TestType(long, long, long) noexcept {}
	};

	{
		using Tuple = std::tuple<int, NothrowMoveable>;
		Tuple tup; ((void)tup);
		Tuple const& ctup = tup; ((void)ctup);
		ASSERT_NOT_NOEXCEPT(bksge::make_from_tuple<TestType>(ctup));
		ASSERT_NOEXCEPT(bksge::make_from_tuple<TestType>(bksge::move(tup)));
	}
	{
		using Tuple = bksge::pair<int, NothrowMoveable>;
		Tuple tup; ((void)tup);
		Tuple const& ctup = tup; ((void)ctup);
		ASSERT_NOT_NOEXCEPT(bksge::make_from_tuple<TestType>(ctup));
		ASSERT_NOEXCEPT(bksge::make_from_tuple<TestType>(bksge::move(tup)));
	}
	{
		using Tuple = std::tuple<int, int, int>;
		Tuple tup; ((void)tup);
		ASSERT_NOT_NOEXCEPT(bksge::make_from_tuple<TestType>(tup));
	}
	{
		using Tuple = std::tuple<long, long, long>;
		Tuple tup; ((void)tup);
		ASSERT_NOEXCEPT(bksge::make_from_tuple<TestType>(tup));
	}
#endif
#if 0	// TODO
	{
		using Tuple = bksge::array<int, 3>;
		Tuple tup; ((void)tup);
		ASSERT_NOT_NOEXCEPT(bksge::make_from_tuple<TestType>(tup));
	}
	{
		using Tuple = bksge::array<long, 3>;
		Tuple tup; ((void)tup);
		ASSERT_NOEXCEPT(bksge::make_from_tuple<TestType>(tup));
	}
#endif
}

GTEST_TEST(TupleTest, MakeFromTupleTest)
{
	test_constexpr_construction();
	test_perfect_forwarding();
	test_noexcept();
}

}	// namespace make_from_tuple_test

}	// namespace bksge_tuple_test

BKSGE_WARNING_POP()
