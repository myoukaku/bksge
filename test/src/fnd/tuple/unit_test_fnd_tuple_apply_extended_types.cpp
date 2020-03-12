/**
 *	@file	unit_test_fnd_tuple_apply_extended_types.cpp
 *
 *	@brief	apply のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/apply.hpp>
//#include <bksge/fnd/array.hpp>
#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/pair/get.hpp>
#include <tuple>
#include <gtest/gtest.h>

namespace bksge_tuple_test
{

namespace apply_extended_types_test
{

int count = 0;

struct A_int_0
{
	A_int_0() : obj1(0){}
	A_int_0(int x) : obj1(x) {}
	int mem1() { return ++count; }
	int mem2() const { return ++count; }
	int const obj1;
};

struct A_int_1
{
	A_int_1() {}
	A_int_1(int) {}
	int mem1(int x) { return count += x; }
	int mem2(int x) const { return count += x; }
};

struct A_int_2
{
	A_int_2() {}
	A_int_2(int) {}
	int mem1(int x, int y) { return count += (x + y); }
	int mem2(int x, int y) const { return count += (x + y); }
};

template <typename A>
struct A_wrap
{
	A_wrap() {}
	A_wrap(int x) : m_a(x) {}
	A & operator*() { return m_a; }
	A const & operator*() const { return m_a; }
	A m_a;
};

typedef A_wrap<A_int_0> A_wrap_0;
typedef A_wrap<A_int_1> A_wrap_1;
typedef A_wrap<A_int_2> A_wrap_2;


template <typename A>
struct A_base : public A
{
	A_base() : A() {}
	A_base(int x) : A(x) {}
};

typedef A_base<A_int_0> A_base_0;
typedef A_base<A_int_1> A_base_1;
typedef A_base<A_int_2> A_base_2;


template <
	typename Tuple,     typename ConstTuple,
	typename TuplePtr,  typename ConstTuplePtr,
	typename TupleWrap, typename ConstTupleWrap,
	typename TupleBase, typename ConstTupleBase
>
void test_ext_int_0()
{
	count = 0;
	typedef A_int_0 T;
	typedef A_wrap_0 Wrap;
	typedef A_base_0 Base;

	typedef int(T::*mem1_t)();
	mem1_t mem1 = &T::mem1;

	typedef int(T::*mem2_t)() const;
	mem2_t mem2 = &T::mem2;

	typedef int const T::*obj1_t;
	obj1_t obj1 = &T::obj1;

	// member function w/ref
	{
		T a;
		Tuple t{{a}};
		EXPECT_EQ(1, bksge::apply(mem1, t));
		EXPECT_EQ(1, count);
	}
	count = 0;
	// member function w/pointer
	{
		T a;
		TuplePtr t{{&a}};
		EXPECT_EQ(1, bksge::apply(mem1, t));
		EXPECT_EQ(1, count);
	}
	count = 0;
	// member function w/base
	{
		Base a;
		TupleBase t{{a}};
		EXPECT_EQ(1, bksge::apply(mem1, t));
		EXPECT_EQ(1, count);
	}
	count = 0;
	// member function w/wrap
	{
		Wrap a;
		TupleWrap t{{a}};
		EXPECT_EQ(1, bksge::apply(mem1, t));
		EXPECT_EQ(1, count);
	}
	count = 0;
	// const member function w/ref
	{
		T const a;
		ConstTuple t{{a}};
		EXPECT_EQ(1, bksge::apply(mem2, t));
		EXPECT_EQ(1, count);
	}
	count = 0;
	// const member function w/pointer
	{
		T const a;
		ConstTuplePtr t{{&a}};
		EXPECT_EQ(1, bksge::apply(mem2, t));
		EXPECT_EQ(1, count);
	}
	count = 0;
	// const member function w/base
	{
		Base const a;
		ConstTupleBase t{{a}};
		EXPECT_EQ(1, bksge::apply(mem2, t));
		EXPECT_EQ(1, count);
	}
	count = 0;
	// const member function w/wrapper
	{
		Wrap const a;
		ConstTupleWrap t{{a}};
		EXPECT_EQ(1, bksge::apply(mem2, t));
		EXPECT_EQ(1, count);
	}
	// member object w/ref
	{
		T a{42};
		Tuple t{{a}};
		EXPECT_EQ(42, bksge::apply(obj1, t));
	}
	// member object w/pointer
	{
		T a{42};
		TuplePtr t{{&a}};
		EXPECT_EQ(42, bksge::apply(obj1, t));
	}
	// member object w/base
	{
		Base a{42};
		TupleBase t{{a}};
		EXPECT_EQ(42, bksge::apply(obj1, t));
	}
	// member object w/wrapper
	{
		Wrap a{42};
		TupleWrap t{{a}};
		EXPECT_EQ(42, bksge::apply(obj1, t));
	}
}


template <
	typename Tuple,     typename ConstTuple,
	typename TuplePtr,  typename ConstTuplePtr,
	typename TupleWrap, typename ConstTupleWrap,
	typename TupleBase, typename ConstTupleBase
>
void test_ext_int_1()
{
	count = 0;
	typedef A_int_1 T;
	typedef A_wrap_1 Wrap;
	typedef A_base_1 Base;

	typedef int(T::*mem1_t)(int);
	mem1_t mem1 = &T::mem1;

	typedef int(T::*mem2_t)(int) const;
	mem2_t mem2 = &T::mem2;

	// member function w/ref
	{
		T a;
		Tuple t{a, 2};
		EXPECT_EQ(2, bksge::apply(mem1, t));
		EXPECT_EQ(2, count);
	}
	count = 0;
	// member function w/pointer
	{
		T a;
		TuplePtr t{&a, 3};
		EXPECT_EQ(3, bksge::apply(mem1, t));
		EXPECT_EQ(3, count);
	}
	count = 0;
	// member function w/base
	{
		Base a;
		TupleBase t{a, 4};
		EXPECT_EQ(4, bksge::apply(mem1, t));
		EXPECT_EQ(4, count);
	}
	count = 0;
	// member function w/wrap
	{
		Wrap a;
		TupleWrap t{a, 5};
		EXPECT_EQ(5, bksge::apply(mem1, t));
		EXPECT_EQ(5, count);
	}
	count = 0;
	// const member function w/ref
	{
		T const a;
		ConstTuple t{a, 6};
		EXPECT_EQ(6, bksge::apply(mem2, t));
		EXPECT_EQ(6, count);
	}
	count = 0;
	// const member function w/pointer
	{
		T const a;
		ConstTuplePtr t{&a, 7};
		EXPECT_EQ(7, bksge::apply(mem2, t));
		EXPECT_EQ(7, count);
	}
	count = 0;
	// const member function w/base
	{
		Base const a;
		ConstTupleBase t{a, 8};
		EXPECT_EQ(8, bksge::apply(mem2, t));
		EXPECT_EQ(8, count);
	}
	count = 0;
	// const member function w/wrapper
	{
		Wrap const a;
		ConstTupleWrap t{a, 9};
		EXPECT_EQ(9, bksge::apply(mem2, t));
		EXPECT_EQ(9, count);
	}
}


template <
	typename Tuple,     typename ConstTuple,
	typename TuplePtr,  typename ConstTuplePtr,
	typename TupleWrap, typename ConstTupleWrap,
	typename TupleBase, typename ConstTupleBase
>
void test_ext_int_2()
{
	count = 0;
	typedef A_int_2 T;
	typedef A_wrap_2 Wrap;
	typedef A_base_2 Base;

	typedef int(T::*mem1_t)(int, int);
	mem1_t mem1 = &T::mem1;

	typedef int(T::*mem2_t)(int, int) const;
	mem2_t mem2 = &T::mem2;

	// member function w/ref
	{
		T a;
		Tuple t{a, 1, 1};
		EXPECT_EQ(2, bksge::apply(mem1, t));
		EXPECT_EQ(2, count);
	}
	count = 0;
	// member function w/pointer
	{
		T a;
		TuplePtr t{&a, 1, 2};
		EXPECT_EQ(3, bksge::apply(mem1, t));
		EXPECT_EQ(3, count);
	}
	count = 0;
	// member function w/base
	{
		Base a;
		TupleBase t{a, 2, 2};
		EXPECT_EQ(4, bksge::apply(mem1, t));
		EXPECT_EQ(4, count);
	}
	count = 0;
	// member function w/wrap
	{
		Wrap a;
		TupleWrap t{a, 2, 3};
		EXPECT_EQ(5, bksge::apply(mem1, t));
		EXPECT_EQ(5, count);
	}
	count = 0;
	// const member function w/ref
	{
		T const a;
		ConstTuple t{a, 3, 3};
		EXPECT_EQ(6, bksge::apply(mem2, t));
		EXPECT_EQ(6, count);
	}
	count = 0;
	// const member function w/pointer
	{
		T const a;
		ConstTuplePtr t{&a, 3, 4};
		EXPECT_EQ(7, bksge::apply(mem2, t));
		EXPECT_EQ(7, count);
	}
	count = 0;
	// const member function w/base
	{
		Base const a;
		ConstTupleBase t{a, 4, 4};
		EXPECT_EQ(8, bksge::apply(mem2, t));
		EXPECT_EQ(8, count);
	}
	count = 0;
	// const member function w/wrapper
	{
		Wrap const a;
		ConstTupleWrap t{a, 4, 5};
		EXPECT_EQ(9, bksge::apply(mem2, t));
		EXPECT_EQ(9, count);
	}
}

GTEST_TEST(TupleTest, ApplyExtendedTypesTest)
{
	{
		test_ext_int_0<
			std::tuple<A_int_0 &>,  std::tuple<A_int_0 const &>,
			std::tuple<A_int_0 *>,  std::tuple<A_int_0 const *>,
			std::tuple<A_wrap_0 &>, std::tuple<A_wrap_0 const &>,
			std::tuple<A_base_0 &>, std::tuple<A_base_0 const &>
		>();
		test_ext_int_0<
			std::tuple<A_int_0>,   std::tuple<A_int_0 const>,
			std::tuple<A_int_0 *>, std::tuple<A_int_0 const *>,
			std::tuple<A_wrap_0>,  std::tuple<A_wrap_0 const>,
			std::tuple<A_base_0>,  std::tuple<A_base_0 const>
		>();
#if 0	// TODO
		test_ext_int_0<
			bksge::array<A_int_0, 1>,  bksge::array<A_int_0 const, 1>,
			bksge::array<A_int_0*, 1>, bksge::array<A_int_0 const*, 1>,
			bksge::array<A_wrap_0, 1>, bksge::array<A_wrap_0 const, 1>,
			bksge::array<A_base_0, 1>, bksge::array<A_base_0 const, 1>
		>();
#endif
	}
	{
		test_ext_int_1<
			std::tuple<A_int_1 &, int>,  std::tuple<A_int_1 const &, int>,
			std::tuple<A_int_1 *, int>,  std::tuple<A_int_1 const *, int>,
			std::tuple<A_wrap_1 &, int>, std::tuple<A_wrap_1 const &, int>,
			std::tuple<A_base_1 &, int>, std::tuple<A_base_1 const &, int>
		>();
		test_ext_int_1<
			std::tuple<A_int_1, int>,   std::tuple<A_int_1 const, int>,
			std::tuple<A_int_1 *, int>, std::tuple<A_int_1 const *, int>,
			std::tuple<A_wrap_1, int>,  std::tuple<A_wrap_1 const, int>,
			std::tuple<A_base_1, int>,  std::tuple<A_base_1 const, int>
		>();
		test_ext_int_1<
			bksge::pair<A_int_1 &, int>,  bksge::pair<A_int_1 const &, int>,
			bksge::pair<A_int_1 *, int>,  bksge::pair<A_int_1 const *, int>,
			bksge::pair<A_wrap_1 &, int>, bksge::pair<A_wrap_1 const &, int>,
			bksge::pair<A_base_1 &, int>, bksge::pair<A_base_1 const &, int>
		>();
		test_ext_int_1<
			bksge::pair<A_int_1, int>,   bksge::pair<A_int_1 const, int>,
			bksge::pair<A_int_1 *, int>, bksge::pair<A_int_1 const *, int>,
			bksge::pair<A_wrap_1, int>,  bksge::pair<A_wrap_1 const, int>,
			bksge::pair<A_base_1, int>,  bksge::pair<A_base_1 const, int>
		>();
	}
	{
		test_ext_int_2<
			std::tuple<A_int_2 &, int, int>,  std::tuple<A_int_2 const &, int, int>,
			std::tuple<A_int_2 *, int, int>,  std::tuple<A_int_2 const *, int, int>,
			std::tuple<A_wrap_2 &, int, int>, std::tuple<A_wrap_2 const &, int, int>,
			std::tuple<A_base_2 &, int, int>, std::tuple<A_base_2 const &, int, int>
		>();
		test_ext_int_2<
			std::tuple<A_int_2, int, int>,   std::tuple<A_int_2 const, int, int>,
			std::tuple<A_int_2 *, int, int>, std::tuple<A_int_2 const *, int, int>,
			std::tuple<A_wrap_2, int, int>,  std::tuple<A_wrap_2 const, int, int>,
			std::tuple<A_base_2, int, int>,  std::tuple<A_base_2 const, int, int>
		>();
	}
}

}	// namespace apply_extended_types_test

}	// namespace bksge_tuple_test
