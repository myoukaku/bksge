/**
 *	@file	unit_test_fnd_tuple_apply_large_arity.cpp
 *
 *	@brief	apply のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/apply.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
//#include <bksge/fnd/array.hpp>
#include <bksge/fnd/utility/integer_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <gtest/gtest.h>

namespace bksge_tuple_test
{

namespace apply_large_arity_test
{

////////////////////////////////////////////////////////////////////////////////
template <typename T, bksge::size_t Dummy = 0>
struct always_imp
{
	typedef T type;
};

template <typename T, bksge::size_t Dummy = 0>
using always_t = typename always_imp<T, Dummy>::type;

////////////////////////////////////////////////////////////////////////////////
template <typename Tuple, typename Idx>
struct make_function;

template <typename Tp, bksge::size_t ...Idx>
struct make_function<Tp, bksge::integer_sequence<bksge::size_t, Idx...>>
{
	using type = bool (*)(always_t<Tp, Idx>...);
};

template <typename Tp, bksge::size_t Size>
using make_function_t = typename make_function<Tp, bksge::make_index_sequence<Size>>::type;

////////////////////////////////////////////////////////////////////////////////
template <typename Tp, typename Idx>
struct make_tuple_imp;

////////////////////////////////////////////////////////////////////////////////
template <typename Tp, bksge::size_t ...Idx>
struct make_tuple_imp<Tp, bksge::integer_sequence<bksge::size_t, Idx...>>
{
	using type = bksge::tuple<always_t<Tp, Idx>...>;
};

template <typename Tp, bksge::size_t Size>
using make_tuple_t = typename make_tuple_imp<Tp, bksge::make_index_sequence<Size>>::type;

template <typename ...Types>
bool test_apply_fn(Types...) { return true; }

template <bksge::size_t Size>
void test_all()
{
#if 0	// TODO
	using A = bksge::array<int, Size>;
	using ConstA = bksge::array<int const, Size>;
#endif

	using Tuple = make_tuple_t<int, Size>;
	using CTuple = make_tuple_t<const int, Size>;

	using ValFn  = make_function_t<int, Size>;
	ValFn val_fn = &test_apply_fn;

	using RefFn  = make_function_t<int &, Size>;
	RefFn ref_fn = &test_apply_fn;

	using CRefFn = make_function_t<int const &, Size>;
	CRefFn cref_fn = &test_apply_fn;

	using RRefFn = make_function_t<int &&, Size>;
	RRefFn rref_fn = &test_apply_fn;

#if 0	// TODO
	{
		A a{};
		EXPECT_TRUE(bksge::apply(val_fn, a));
		EXPECT_TRUE(bksge::apply(ref_fn, a));
		EXPECT_TRUE(bksge::apply(cref_fn, a));
		EXPECT_TRUE(bksge::apply(rref_fn, bksge::move(a)));
	}
	{
		ConstA a{{}};
		EXPECT_TRUE(bksge::apply(val_fn, a));
		EXPECT_TRUE(bksge::apply(cref_fn, a));
	}
#endif
	{
		Tuple a{};
		EXPECT_TRUE(bksge::apply(val_fn, a));
		EXPECT_TRUE(bksge::apply(ref_fn, a));
		EXPECT_TRUE(bksge::apply(cref_fn, a));
		EXPECT_TRUE(bksge::apply(rref_fn, bksge::move(a)));
	}
	{
		CTuple a{};
		EXPECT_TRUE(bksge::apply(val_fn, a));
		EXPECT_TRUE(bksge::apply(cref_fn, a));
	}
}

template <bksge::size_t Size>
void test_one()
{
//	using A = bksge::array<int, Size>;
	using Tuple = make_tuple_t<int, Size>;

	using ValFn  = make_function_t<int, Size>;
	ValFn val_fn = &test_apply_fn;

#if 0	// TODO
	{
		A a{};
		EXPECT_TRUE(bksge::apply(val_fn, a));
	}
#endif
	{
		Tuple a{};
		EXPECT_TRUE(bksge::apply(val_fn, a));
	}
}

GTEST_TEST(TupleTest, ApplyLargeArityTest)
{
	// Instantiate with 1-5 arguments.
	test_all<1>();
	test_all<2>();
	test_all<3>();
	test_all<4>();
	test_all<5>();

	// Stress test with 256
#if 0
	test_one<256>();
#else
	test_one<128>();
#endif
}

}	// namespace apply_large_arity_test

}	// namespace bksge_tuple_test
