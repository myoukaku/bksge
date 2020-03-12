/**
 *	@file	unit_test_fnd_tuple_tuple.cpp
 *
 *	@brief	tuple のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>
#include <bksge/fnd/pair/pair.hpp>
#include <bksge/fnd/pair/get.hpp>
//#include <bksge/fnd/memory/allocator_arg.hpp>
//#include <bksge/fnd/memory/allocator.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_trivially_destructible.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <string>
#include <array>
#include "tuple_test_utility.hpp"
#include "constexpr_test.hpp"

namespace bksge_tuple_test
{

namespace default_ctor_test
{

struct NoDefault
{
	NoDefault() = delete;
	explicit NoDefault(int) { }
};

struct ExplicitDefault
{
	explicit ExplicitDefault() {}
};

struct NoExceptDefault
{
	NoExceptDefault() noexcept = default;
};

struct ThrowingDefault
{
	ThrowingDefault() { }
};

struct IllFormedDefault
{
	IllFormedDefault(int x) : value(x) {}

	template <bool Pred = false>
	constexpr IllFormedDefault()
	{
		static_assert(Pred,
			"The default constructor should not be instantiated");
	}

	int value;
};

GTEST_TEST(TupleTest, DefaultCtorTest)
{
	{
		bksge::tuple<> t;
		(void)t;
	}
	{
		bksge::tuple<int> t;
		EXPECT_EQ(bksge::get<0>(t), 0);
	}
	{
		bksge::tuple<int, char*> t;
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_TRUE(bksge::get<1>(t) == nullptr);
	}
	{
		bksge::tuple<int, char*, std::string> t;
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_TRUE(bksge::get<1>(t) == nullptr);
		EXPECT_TRUE(bksge::get<2>(t) == "");
	}
	{
		bksge::tuple<int, char*, std::string, DefaultOnly> t;
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_TRUE(bksge::get<1>(t) == nullptr);
		EXPECT_TRUE(bksge::get<2>(t) == "");
		EXPECT_TRUE(bksge::get<3>(t) == DefaultOnly());
	}
	{
		static_assert( bksge::is_default_constructible<bksge::tuple<>>(), "");
		static_assert( bksge::is_default_constructible<bksge::tuple<int>>(), "");
		static_assert( bksge::is_default_constructible<bksge::tuple<int, char*>>(), "");
		static_assert( bksge::is_default_constructible<bksge::tuple<DefaultOnly>>(), "");
		static_assert( bksge::is_default_constructible<bksge::tuple<NoExceptDefault>>(), "");
		static_assert( bksge::is_default_constructible<bksge::tuple<ExplicitDefault>>(), "");
		static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault>>(), "");
		static_assert(!bksge::is_default_constructible<bksge::tuple<DefaultOnly, NoDefault>>(), "");
		static_assert(!bksge::is_default_constructible<bksge::tuple<NoDefault, DefaultOnly, NoDefault>>(), "");

		static_assert( bksge::is_implicitly_default_constructible<bksge::tuple<>>(), "");
		static_assert( bksge::is_implicitly_default_constructible<bksge::tuple<int>>(), "");
		static_assert( bksge::is_implicitly_default_constructible<bksge::tuple<int, char*>>(), "");
		static_assert( bksge::is_implicitly_default_constructible<bksge::tuple<DefaultOnly>>(), "");
		static_assert( bksge::is_implicitly_default_constructible<bksge::tuple<NoExceptDefault>>(), "");
		static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<ExplicitDefault>>(), "");
		static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault>>(), "");
		static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<DefaultOnly, NoDefault>>(), "");
		static_assert(!bksge::is_implicitly_default_constructible<bksge::tuple<NoDefault, DefaultOnly, NoDefault>>(), "");

#if (BKSGE_CXX_STANDARD >= 20)
		static_assert( bksge::is_nothrow_default_constructible<bksge::tuple<>>(), "");
		static_assert( bksge::is_nothrow_default_constructible<bksge::tuple<int>>(), "");
		static_assert( bksge::is_nothrow_default_constructible<bksge::tuple<int, char*>>(), "");
		static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<DefaultOnly>>(), "");
		static_assert( bksge::is_nothrow_default_constructible<bksge::tuple<NoExceptDefault>>(), "");
		static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<ExplicitDefault>>(), "");
		static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault>>(), "");
		static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<DefaultOnly, NoDefault>>(), "");
		static_assert(!bksge::is_nothrow_default_constructible<bksge::tuple<NoDefault, DefaultOnly, NoDefault>>(), "");
#endif
	}
	{
#if (BKSGE_CXX_STANDARD >= 20)
		static_assert(noexcept(bksge::tuple<NoExceptDefault>()), "");
		static_assert(noexcept(bksge::tuple<NoExceptDefault, NoExceptDefault>()), "");
#endif

		static_assert(!noexcept(bksge::tuple<ThrowingDefault, NoExceptDefault>()), "");
		static_assert(!noexcept(bksge::tuple<NoExceptDefault, ThrowingDefault>()), "");
		static_assert(!noexcept(bksge::tuple<ThrowingDefault, ThrowingDefault>()), "");
	}
	{
		constexpr bksge::tuple<> t;
		(void)t;
	}
	{
		constexpr bksge::tuple<int> t;
		EXPECT_EQ(bksge::get<0>(t), 0);
	}
	{
		constexpr bksge::tuple<int, char*> t;
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_TRUE(bksge::get<1>(t) == nullptr);
	}
	{
		// Check that the SFINAE on the default constructor is not evaluated when
		// it isn't needed. If the default constructor is evaluated then this test
		// should fail to compile.
		IllFormedDefault v(0);
		bksge::tuple<IllFormedDefault> t(v);
	}
}

}	// namespace default_ctor_test

namespace const_types_ctor_test
{

template <typename ...>
struct never
{
	enum { value = 0 };
};

struct NoValueCtor
{
	NoValueCtor() : id(++count) {}
	NoValueCtor(NoValueCtor const & other) : id(other.id) { ++count; }

	// The constexpr is required to make is_constructible instantiate this template.
	// The explicit is needed to test-around a similar bug with is_convertible.
	template <typename T>
	constexpr explicit NoValueCtor(T)
	{
		static_assert(never<T>::value, "This should not be instantiated");
	}

	static int count;
	int id;
};

int NoValueCtor::count = 0;

struct NoValueCtorEmpty
{
	NoValueCtorEmpty() {}
	NoValueCtorEmpty(NoValueCtorEmpty const &) {}

	template <typename T>
	constexpr explicit NoValueCtorEmpty(T)
	{
		static_assert(never<T>::value, "This should not be instantiated");
	}
};

struct ImplicitCopy
{
	explicit ImplicitCopy(int) {}
	ImplicitCopy(ImplicitCopy const&) {}
};

struct ExplicitCopy
{
	explicit ExplicitCopy(int) {}
	explicit ExplicitCopy(ExplicitCopy const&) {}
};

// Test that tuple(std::allocator_arg, Alloc, Types const&...) allows implicit
// copy conversions in return value expressions.
bksge::tuple<ImplicitCopy> testImplicitCopy1()
{
	ImplicitCopy i(42);
	return{i};
}

bksge::tuple<ImplicitCopy> testImplicitCopy2()
{
	const ImplicitCopy i(42);
	return{i};
}

bksge::tuple<ImplicitCopy> testImplicitCopy3()
{
	const ImplicitCopy i(42);
	return i;
}

GTEST_TEST(TupleTest, ConstTypesCtorTest)
{
	{
		static_assert( bksge::is_constructible<bksge::tuple<>>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<>, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int>, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int>, char>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int>, float>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<int, float>, int>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<int, float>, float>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int, float>, int, float>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int, float>, float, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int, float>, int, int>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<int, float, int*>, int>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<int, float, int*>, int, float>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int, float, int*>, int, float, int*>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<int, float, int*>, int, float, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<ImplicitCopy>, ImplicitCopy>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<ExplicitCopy>, ExplicitCopy>(), "");

		static_assert( bksge::is_implicitly_constructible<bksge::tuple<>>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<>, int>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int>, int>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int>, char>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int>, float>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<int, float>, int>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<int, float>, float>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int, float>, int, float>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int, float>, float, int>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int, float>, int, int>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<int, float, int*>, int>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<int, float, int*>, int, float>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int, float, int*>, int, float, int*>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<int, float, int*>, int, float, int>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<ImplicitCopy>, ImplicitCopy>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<ExplicitCopy>, ExplicitCopy>(), "");

#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<>, int>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int>, int>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int>, char>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int>, float>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int, float>, int>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int, float>, float>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int, float>, int, float>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int, float>, float, int>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int, float>, int, int>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int, float, int*>, int>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int, float, int*>, int, float>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int, float, int*>, int, float, int*>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int, float, int*>, int, float, int>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<ImplicitCopy>, ImplicitCopy>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<ExplicitCopy>, ExplicitCopy>(), "");
#endif
	}

	{
		// check that the literal '0' can implicitly initialize a stored pointer.
		bksge::tuple<int*> t = 0;
		EXPECT_TRUE(bksge::get<0>(t) == nullptr);
	}
	{
		bksge::tuple<int> t(2);
		EXPECT_EQ(bksge::get<0>(t), 2);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int> t(2);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t), 2);
	}
	{
		constexpr bksge::tuple<int> t;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t), 0);
	}
	{
		bksge::tuple<int, char*> t(2, 0);
		EXPECT_EQ(bksge::get<0>(t), 2);
		EXPECT_TRUE(bksge::get<1>(t) == nullptr);
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<int, char*> t(2, nullptr);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t), 2);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<1>(t), nullptr);
	}
	{
		bksge::tuple<int, char*> t(2, nullptr);
		EXPECT_EQ(bksge::get<0>(t), 2);
		EXPECT_TRUE(bksge::get<1>(t) == nullptr);
	}
	{
		bksge::tuple<int, char*, std::string> t(2, nullptr, "text");
		EXPECT_EQ(bksge::get<0>(t), 2);
		EXPECT_TRUE(bksge::get<1>(t) == nullptr);
		EXPECT_TRUE(bksge::get<2>(t) == "text");
	}
	// __tuple_leaf<T> uses is_constructible<T, U> to disable its explicit converting
	// constructor overload __tuple_leaf(U &&). Evaluating is_constructible can cause a compile error.
	// This overload is evaluated when __tuple_leafs copy or move ctor is called.
	// This checks that is_constructible is not evaluated when U == __tuple_leaf.
	{
		bksge::tuple<int, NoValueCtor, int, int> t(1, NoValueCtor(), 2, 3);
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_EQ(bksge::get<1>(t).id, 1);
		EXPECT_EQ(bksge::get<2>(t), 2);
		EXPECT_EQ(bksge::get<3>(t), 3);
	}
	{
		bksge::tuple<int, NoValueCtorEmpty, int, int> t(1, NoValueCtorEmpty(), 2, 3);
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_EQ(bksge::get<2>(t), 2);
		EXPECT_EQ(bksge::get<3>(t), 3);
	}
}

}	// namespace const_types_ctor_test

namespace alloc_ctor_test
{

#if 0	// TODO
template <typename T = void>
struct NonDefaultConstructible
{
	constexpr NonDefaultConstructible()
	{
		static_assert(!bksge::is_same<T, T>::value, "Default Ctor instantiated");
	}

	explicit constexpr NonDefaultConstructible(int) {}
};
#endif

struct NoDefault
{
	NoDefault() = delete;
	explicit NoDefault(int) { }
};

struct ExplicitDefault
{
	explicit ExplicitDefault() noexcept {}
};

struct DerivedFromAllocArgT : std::allocator_arg_t {};

GTEST_TEST(TupleTest, AllocCtorTest)
{
	{
		static_assert( bksge::is_constructible<bksge::tuple<>, std::allocator_arg_t, A1<int>>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<>, DerivedFromAllocArgT, A1<int>>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<>, std::allocator_arg_t>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<>, A1<int>>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<DefaultOnly>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<DefaultOnly>, std::allocator_arg_t>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<DefaultOnly>, A1<int>>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<DefaultOnly, alloc_first>, std::allocator_arg_t, A1<int>>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<ExplicitDefault>, std::allocator_arg_t, A1<int>>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<DefaultOnly, DefaultOnly, DefaultOnly>, std::allocator_arg_t, A1<int>>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<DefaultOnly, ExplicitDefault, DefaultOnly>, std::allocator_arg_t, A1<int>>(), "");
#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert(!bksge::is_constructible<bksge::tuple<NoDefault>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<DefaultOnly, DefaultOnly, NoDefault>, std::allocator_arg_t, A1<int>>(), "");
#endif

		static_assert( bksge::is_implicitly_constructible<bksge::tuple<>, std::allocator_arg_t, A1<int>>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<>, DerivedFromAllocArgT, A1<int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<>, std::allocator_arg_t>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<>, A1<int>>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<DefaultOnly>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<DefaultOnly>, std::allocator_arg_t>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<DefaultOnly>, A1<int>>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<DefaultOnly, alloc_first>, std::allocator_arg_t, A1<int>>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<DefaultOnly, DefaultOnly, DefaultOnly>, std::allocator_arg_t, A1<int>>(), "");
#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<NoDefault>, std::allocator_arg_t, A1<int>>(), "");
//		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<ExplicitDefault>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<DefaultOnly, DefaultOnly, NoDefault>, std::allocator_arg_t, A1<int>>(), "");
//		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<DefaultOnly, ExplicitDefault, DefaultOnly>, std::allocator_arg_t, A1<int>>(), "");
#endif

#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<>, std::allocator_arg_t, A1<int>>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<>, DerivedFromAllocArgT, A1<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<>, std::allocator_arg_t>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<>, A1<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<DefaultOnly>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<DefaultOnly>, std::allocator_arg_t>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<DefaultOnly>, A1<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<DefaultOnly, alloc_first>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<NoDefault>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<ExplicitDefault>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<DefaultOnly, DefaultOnly, DefaultOnly>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<DefaultOnly, DefaultOnly, NoDefault>, std::allocator_arg_t, A1<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<DefaultOnly, ExplicitDefault, DefaultOnly>, std::allocator_arg_t, A1<int>>(), "");
#endif
	}
	{
		bksge::tuple<> t(std::allocator_arg, A1<int>());
	}
	{
		bksge::tuple<int> t(std::allocator_arg, A1<int>());
		EXPECT_EQ(bksge::get<0>(t), 0);
	}
	{
		bksge::tuple<DefaultOnly> t(std::allocator_arg, A1<int>());
		EXPECT_TRUE(bksge::get<0>(t) == DefaultOnly());
	}
	{
		EXPECT_FALSE(alloc_first::allocator_constructed);
		bksge::tuple<alloc_first> t(std::allocator_arg, A1<int>(5));
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(bksge::get<0>(t) == alloc_first());
	}
	{
		EXPECT_FALSE(alloc_last::allocator_constructed);
		bksge::tuple<alloc_last> t(std::allocator_arg, A1<int>(5));
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_TRUE(bksge::get<0>(t) == alloc_last());
	}
	{
		alloc_first::allocator_constructed = false;
		bksge::tuple<DefaultOnly, alloc_first> t(std::allocator_arg, A1<int>(5));
		EXPECT_TRUE(bksge::get<0>(t) == DefaultOnly());
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(bksge::get<1>(t) == alloc_first());
	}
	{
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		bksge::tuple<DefaultOnly, alloc_first, alloc_last> t(std::allocator_arg, A1<int>(5));
		EXPECT_TRUE(bksge::get<0>(t) == DefaultOnly());
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(bksge::get<1>(t) == alloc_first());
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_TRUE(bksge::get<2>(t) == alloc_last());
	}
	{
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		bksge::tuple<DefaultOnly, alloc_first, alloc_last> t(std::allocator_arg, A2<int>(5));
		EXPECT_TRUE(bksge::get<0>(t) == DefaultOnly());
		EXPECT_FALSE(alloc_first::allocator_constructed);
		EXPECT_TRUE(bksge::get<1>(t) == alloc_first());
		EXPECT_FALSE(alloc_last::allocator_constructed);
		EXPECT_TRUE(bksge::get<2>(t) == alloc_last());
	}
#if 0	// TODO
	{
		// Test that the uses-allocator default constructor does not evaluate
		// its SFINAE when it otherwise shouldn't be selected. Do this by
		// using 'NonDefaultConstructible' which will cause a compile error
		// if bksge::is_default_constructible is evaluated on it.
		using T = NonDefaultConstructible<>;
		T v(42);
		bksge::tuple<T, T> t(v, v);
		(void)t;
		bksge::tuple<T, T> t2(42, 42);
		(void)t2;
	}
#endif
}

}	// namespace alloc_ctor_test

namespace alloc_const_pair_ctor_test
{

struct ExplicitCtor
{
	explicit ExplicitCtor(int) noexcept {}
};
struct ImplicitCtor
{
	ImplicitCtor(int) noexcept {}
};

GTEST_TEST(TupleTest, AllocConstPairCtorTest)
{
	{
		static_assert(!bksge::is_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<long, int>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<int, long>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<alloc_first, double>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<alloc_first, alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<ExplicitCtor, ExplicitCtor>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<ImplicitCtor, ImplicitCtor>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<ExplicitCtor, ImplicitCtor>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");

		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long, int>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<int, long>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<alloc_first, double>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<alloc_first, alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<ExplicitCtor, ExplicitCtor>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<ImplicitCtor, ImplicitCtor>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<ExplicitCtor, ImplicitCtor>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");

		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long, int>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<int, long>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<alloc_first, double>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<alloc_first, alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<ExplicitCtor, ExplicitCtor>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<ImplicitCtor, ImplicitCtor>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<ExplicitCtor, ImplicitCtor>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>>(), "");
	}
	{
		typedef bksge::pair<long, int> T0;
		typedef bksge::tuple<long long, double> T1;
		T0 t0(2, 3);
		T1 t1(std::allocator_arg, A1<int>(5), t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), 3);
	}
	{
		typedef bksge::pair<int, int> T0;
		typedef bksge::tuple<alloc_first, double> T1;
		T0 t0(2, 3);
		alloc_first::allocator_constructed = false;
		T1 t1(std::allocator_arg, A1<int>(5), t0);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), 3);
	}
	{
		typedef bksge::pair<int, int> T0;
		typedef bksge::tuple<alloc_first, alloc_last> T1;
		T0 t0(2, 3);
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		T1 t1(std::allocator_arg, A1<int>(5), t0);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), 3);
	}
}

}	// namespace alloc_const_pair_ctor_test

namespace alloc_const_types_ctor_test
{

struct ImplicitCopy
{
	explicit ImplicitCopy(int) {}
	ImplicitCopy(ImplicitCopy const&) {}
};

struct ExplicitCopy
{
	ExplicitCopy(int) {}
	explicit ExplicitCopy(ExplicitCopy const&) {}
};

// Test that tuple(std::allocator_arg, Alloc, Types const&...) allows implicit
// copy conversions in return value expressions.
bksge::tuple<ImplicitCopy> testImplicitCopy1()
{
	ImplicitCopy i(42);
	return{std::allocator_arg, std::allocator<void>{}, i};
}

bksge::tuple<ImplicitCopy> testImplicitCopy2()
{
	const ImplicitCopy i(42);
	return{std::allocator_arg, std::allocator<void>{}, i};
}

GTEST_TEST(TupleTest, AllocConstTypesCtorTest)
{
	{
		static_assert(!bksge::is_constructible<bksge::tuple<>,     std::allocator_arg_t, A1<int>, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int>,  std::allocator_arg_t, A1<int>, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int>,  std::allocator_arg_t, A1<int>, char>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int>,  std::allocator_arg_t, A1<int>, double>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<int*>, std::allocator_arg_t, A1<int>, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int*>, std::allocator_arg_t, A1<int>, bksge::nullptr_t>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<ImplicitCopy>, std::allocator_arg_t, A1<int>, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<ImplicitCopy>, std::allocator_arg_t, A1<int>, ImplicitCopy const&>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<ExplicitCopy>, std::allocator_arg_t, A1<int>, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<ExplicitCopy>, std::allocator_arg_t, A1<int>, ExplicitCopy const&>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int, alloc_first>, std::allocator_arg_t, A1<int>, int, alloc_first>(), "");

		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<>,     std::allocator_arg_t, A1<int>, int>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int>,  std::allocator_arg_t, A1<int>, int>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int>,  std::allocator_arg_t, A1<int>, char>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int>,  std::allocator_arg_t, A1<int>, double>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<int*>, std::allocator_arg_t, A1<int>, int>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int*>, std::allocator_arg_t, A1<int>, bksge::nullptr_t>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<ImplicitCopy>, std::allocator_arg_t, A1<int>, int>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<ImplicitCopy>, std::allocator_arg_t, A1<int>, ImplicitCopy const&>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<ExplicitCopy>, std::allocator_arg_t, A1<int>, int>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<ExplicitCopy>, std::allocator_arg_t, A1<int>, ExplicitCopy const&>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int, alloc_first>, std::allocator_arg_t, A1<int>, int, alloc_first>(), "");

		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<>,     std::allocator_arg_t, A1<int>, int>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int>,  std::allocator_arg_t, A1<int>, int>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int>,  std::allocator_arg_t, A1<int>, char>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int>,  std::allocator_arg_t, A1<int>, double>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int*>, std::allocator_arg_t, A1<int>, int>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int*>, std::allocator_arg_t, A1<int>, bksge::nullptr_t>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<ImplicitCopy>, std::allocator_arg_t, A1<int>, int>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<ImplicitCopy>, std::allocator_arg_t, A1<int>, ImplicitCopy const&>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<ExplicitCopy>, std::allocator_arg_t, A1<int>, int>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<ExplicitCopy>, std::allocator_arg_t, A1<int>, ExplicitCopy const&>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int, alloc_first>, std::allocator_arg_t, A1<int>, int, alloc_first>(), "");
	}
	{
		// check that the literal '0' can implicitly initialize a stored pointer.
		bksge::tuple<int*> t ={std::allocator_arg, std::allocator<void>{}, 0};
		(void)t;
	}
	{
		bksge::tuple<int> t(std::allocator_arg, A1<int>(), 3);
		EXPECT_EQ(bksge::get<0>(t), 3);
	}
	{
		alloc_first::allocator_constructed = false;
		bksge::tuple<alloc_first> t(std::allocator_arg, A1<int>(5), alloc_first(3));
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(bksge::get<0>(t) == alloc_first(3));
	}
	{
		alloc_last::allocator_constructed = false;
		bksge::tuple<alloc_last> t(std::allocator_arg, A1<int>(5), alloc_last(3));
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_TRUE(bksge::get<0>(t) == alloc_last(3));
	}
	{
		alloc_first::allocator_constructed = false;
		bksge::tuple<int, alloc_first> t(std::allocator_arg, A1<int>(5), 10, alloc_first(15));
		EXPECT_EQ(bksge::get<0>(t), 10);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(bksge::get<1>(t) == alloc_first(15));
	}
	{
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		bksge::tuple<int, alloc_first, alloc_last> t(std::allocator_arg,
			A1<int>(5), 1, alloc_first(2),
			alloc_last(3));
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(bksge::get<1>(t) == alloc_first(2));
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_TRUE(bksge::get<2>(t) == alloc_last(3));
	}
	{
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		bksge::tuple<int, alloc_first, alloc_last> t(std::allocator_arg,
			A2<int>(5), 1, alloc_first(2),
			alloc_last(3));
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_FALSE(alloc_first::allocator_constructed);
		EXPECT_TRUE(bksge::get<1>(t) == alloc_first(2));
		EXPECT_FALSE(alloc_last::allocator_constructed);
		EXPECT_TRUE(bksge::get<2>(t) == alloc_last(3));
	}
}

}	// namespace alloc_const_types_ctor_test

namespace alloc_convert_copy_ctor_test
{

struct Explicit
{
	int value;
	explicit Explicit(int x) : value(x) {}
};

struct Implicit
{
	int value;
	Implicit(int x) : value(x) {}
};

GTEST_TEST(TupleTest, AllocConvertCopyCtorTest)
{
	{
		static_assert( bksge::is_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long long>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<long long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<long long, alloc_first, alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long, int, int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>>(), "");
	}
	{
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long long>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long long, alloc_first, alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long, int, int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>>(), "");
	}
	{
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long long>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long long, alloc_first, alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long, int, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>>(), "");
	}
	{
		typedef bksge::tuple<long> T0;
		typedef bksge::tuple<long long> T1;
		T0 t0(2);
		T1 t1(std::allocator_arg, A1<int>(), t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
	}
	{
		typedef bksge::tuple<int> T0;
		typedef bksge::tuple<alloc_first> T1;
		T0 t0(2);
		alloc_first::allocator_constructed = false;
		T1 t1(std::allocator_arg, A1<int>(5), t0);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t1), 2);
	}
	{
		typedef bksge::tuple<int, int> T0;
		typedef bksge::tuple<alloc_first, alloc_last> T1;
		T0 t0(2, 3);
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		T1 t1(std::allocator_arg, A1<int>(5), t0);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), 3);
	}
	{
		typedef bksge::tuple<long, int, int> T0;
		typedef bksge::tuple<long long, alloc_first, alloc_last> T1;
		T0 t0(1, 2, 3);
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		T1 t1(std::allocator_arg, A1<int>(5), t0);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t1), 1);
		EXPECT_EQ(bksge::get<1>(t1), 2);
		EXPECT_EQ(bksge::get<2>(t1), 3);
	}
	{
		const bksge::tuple<int> t1(42);
		bksge::tuple<Explicit> t2{std::allocator_arg, std::allocator<void>{}, t1};
		EXPECT_EQ(bksge::get<0>(t2).value, 42);
	}
	{
		const bksge::tuple<int> t1(42);
		bksge::tuple<Implicit> t2 ={std::allocator_arg, std::allocator<void>{}, t1};
		EXPECT_EQ(bksge::get<0>(t2).value, 42);
	}
}

}	// namespace alloc_convert_copy_ctor_test

namespace alloc_convert_move_ctor_test
{

struct B
{
	int id_;

	explicit B(int i) : id_(i) {}

	virtual ~B() {}
};

struct D
	: B
{
	explicit D(int i) : B(i) {}
};

struct Explicit
{
	int value;
	explicit Explicit(int x) : value(x) {}
};

struct Implicit
{
	int value;
	Implicit(int x) : value(x) {}
};

GTEST_TEST(TupleTest, AllocConvertMoveCtorTest)
{
	{
		static_assert( bksge::is_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long long>&&>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>&&>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<long long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<long long, alloc_first, alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long, int, int>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>&&>(), "");
	}
	{
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long long>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long long, alloc_first, alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long, int, int>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>&&>(), "");
	}
	{
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long long>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long long>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long long, alloc_first, alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<long, int, int>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Explicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Implicit>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int, int>&&>(), "");
	}
	{
		typedef bksge::tuple<int> T0;
		typedef bksge::tuple<alloc_first> T1;
		T0 t0(2);
		alloc_first::allocator_constructed = false;
		T1 t1(std::allocator_arg, A1<int>(5), bksge::move(t0));
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t1), 2);
	}
	{
		typedef bksge::tuple<bksge::unique_ptr<D>> T0;
		typedef bksge::tuple<bksge::unique_ptr<B>> T1;
		T0 t0(bksge::unique_ptr<D>(new D(3)));
		T1 t1(std::allocator_arg, A1<int>(5), bksge::move(t0));
		EXPECT_EQ(bksge::get<0>(t1)->id_, 3);
	}
	{
		typedef bksge::tuple<int, bksge::unique_ptr<D>> T0;
		typedef bksge::tuple<alloc_first, bksge::unique_ptr<B>> T1;
		T0 t0(2, bksge::unique_ptr<D>(new D(3)));
		alloc_first::allocator_constructed = false;
		T1 t1(std::allocator_arg, A1<int>(5), bksge::move(t0));
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1)->id_, 3);
	}
	{
		typedef bksge::tuple<int, int, bksge::unique_ptr<D>> T0;
		typedef bksge::tuple<alloc_last, alloc_first, bksge::unique_ptr<B>> T1;
		T0 t0(1, 2, bksge::unique_ptr<D>(new D(3)));
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		T1 t1(std::allocator_arg, A1<int>(5), bksge::move(t0));
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t1), 1);
		EXPECT_EQ(bksge::get<1>(t1), 2);
		EXPECT_EQ(bksge::get<2>(t1)->id_, 3);
	}
	{
		bksge::tuple<int> t1(42);
		bksge::tuple<Explicit> t2{std::allocator_arg, std::allocator<void>{}, bksge::move(t1)};
		EXPECT_EQ(bksge::get<0>(t2).value, 42);
	}
	{
		bksge::tuple<int> t1(42);
		bksge::tuple<Implicit> t2 ={std::allocator_arg, std::allocator<void>{}, bksge::move(t1)};
		EXPECT_EQ(bksge::get<0>(t2).value, 42);
	}
}

}	// namespace alloc_convert_move_ctor_test

GTEST_TEST(TupleTest, AllocCopyCtorTest)
{
	{
		static_assert( bksge::is_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::tuple<> const&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int> const&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first> const&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_last> const&>(), "");
	}
	{
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::tuple<> const&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int> const&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first> const&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_last> const&>(), "");
	}
	{
#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert( bksge::is_nothrow_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::tuple<> const&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int> const&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first> const&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_last> const&>(), "");
#endif
	}
	{
		typedef bksge::tuple<> T;
		T t0;
		T t(std::allocator_arg, A1<int>(), t0);
	}
	{
		typedef bksge::tuple<int> T;
		T t0(2);
		T t(std::allocator_arg, A1<int>(), t0);
		EXPECT_EQ(bksge::get<0>(t), 2);
	}
	{
		typedef bksge::tuple<alloc_first> T;
		T t0(2);
		alloc_first::allocator_constructed = false;
		T t(std::allocator_arg, A1<int>(5), t0);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t), 2);
	}
	{
		typedef bksge::tuple<alloc_last> T;
		T t0(2);
		alloc_last::allocator_constructed = false;
		T t(std::allocator_arg, A1<int>(5), t0);
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t), 2);
	}
	// testing extensions
#if 1
	{
		typedef bksge::tuple<alloc_first, alloc_last> T;
		T t0(2, 3);
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		T t(std::allocator_arg, A1<int>(5), t0);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t), 2);
		EXPECT_EQ(bksge::get<1>(t), 3);
	}
	{
		typedef bksge::tuple<int, alloc_first, alloc_last> T;
		T t0(1, 2, 3);
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		T t(std::allocator_arg, A1<int>(5), t0);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_EQ(bksge::get<1>(t), 2);
		EXPECT_EQ(bksge::get<2>(t), 3);
	}
#endif
}

GTEST_TEST(TupleTest, AllocMoveCtorTest)
{
	{
		static_assert( bksge::is_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::tuple<>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_last>&&>(), "");
	}
	{
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::tuple<>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_last>&&>(), "");
	}
	{
#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert( bksge::is_nothrow_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::tuple<>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<int>, std::allocator_arg_t, A1<int>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<alloc_first>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_first>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<alloc_last>, std::allocator_arg_t, A1<int>,
			bksge::tuple<alloc_last>&&>(), "");
#endif
	}
	{
		typedef bksge::tuple<> T;
		T t0;
		T t(std::allocator_arg, A1<int>(), bksge::move(t0));
	}
	{
		typedef bksge::tuple<MoveOnly> T;
		T t0(MoveOnly(0));
		T t(std::allocator_arg, A1<int>(), bksge::move(t0));
		EXPECT_EQ(bksge::get<0>(t), 0);
	}
	{
		typedef bksge::tuple<alloc_first> T;
		T t0(1);
		alloc_first::allocator_constructed = false;
		T t(std::allocator_arg, A1<int>(5), bksge::move(t0));
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t), 1);
	}
	{
		typedef bksge::tuple<alloc_last> T;
		T t0(1);
		alloc_last::allocator_constructed = false;
		T t(std::allocator_arg, A1<int>(5), bksge::move(t0));
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t), 1);
	}
	// testing extensions
#if 1
	{
		typedef bksge::tuple<MoveOnly, alloc_first> T;
		T t0(0, 1);
		alloc_first::allocator_constructed = false;
		T t(std::allocator_arg, A1<int>(5), bksge::move(t0));
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 1);
	}
	{
		typedef bksge::tuple<MoveOnly, alloc_first, alloc_last> T;
		T t0(1, 2, 3);
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		T t(std::allocator_arg, A1<int>(5), bksge::move(t0));
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_EQ(bksge::get<1>(t), 2);
		EXPECT_EQ(bksge::get<2>(t), 3);
	}
#endif
}

namespace alloc_move_pair_ctor_test
{

struct B
{
	int id_;

	explicit B(int i) : id_(i) {}

	virtual ~B() {}
};

struct D : B
{
	explicit D(int i) : B(i) {}
};

GTEST_TEST(TupleTest, AllocMovePairCtorTest)
{
	{
		static_assert(!bksge::is_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<long, int>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, char>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<D, int>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>&&>(), "");
	}
	{
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long, int>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, char>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<D, int>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>&&>(), "");
	}
	{
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<>, std::allocator_arg_t, A1<int>,
			bksge::pair<long, int>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long, int>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, char>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<D, int>, std::allocator_arg_t, A1<int>,
			bksge::pair<int, int>&&>(), "");
	}
	{
		typedef bksge::pair<int, bksge::unique_ptr<D>> T0;
		typedef bksge::tuple<alloc_first, bksge::unique_ptr<B>> T1;
		T0 t0(2, bksge::unique_ptr<D>(new D(3)));
		alloc_first::allocator_constructed = false;
		T1 t1(std::allocator_arg, A1<int>(5), bksge::move(t0));
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1)->id_, 3);
	}
}

}	// namespace alloc_move_pair_ctor_test

namespace alloc_utypes_ctor_test
{

template <typename T = void>
struct DefaultCtorBlowsUp
{
	constexpr DefaultCtorBlowsUp()
	{
		static_assert(!bksge::is_same<T, T>::value, "Default Ctor instantiated");
	}

	explicit constexpr DefaultCtorBlowsUp(int x) : value(x) {}

	int value;
};

struct DerivedFromAllocArgT : std::allocator_arg_t {};

// Make sure the _Up... constructor SFINAEs out when the number of initializers
// is less that the number of elements in the tuple. Previously libc++ would
// offer these constructers as an extension but they broke conforming code.
void test_uses_allocator_sfinae_evaluation()
{
	using BadDefault = DefaultCtorBlowsUp<>;
	{
		typedef bksge::tuple<MoveOnly, MoveOnly, BadDefault> Tuple;

		static_assert(!bksge::is_constructible<
			Tuple,
			std::allocator_arg_t, A1<int>, MoveOnly
		>::value, "");

		static_assert(bksge::is_constructible<
			Tuple,
			std::allocator_arg_t, A1<int>, MoveOnly, MoveOnly, BadDefault
		>::value, "");
	}
	{
		typedef bksge::tuple<MoveOnly, MoveOnly, BadDefault, BadDefault> Tuple;

		static_assert(!bksge::is_constructible<
			Tuple,
			std::allocator_arg_t, A1<int>, MoveOnly, MoveOnly
		>::value, "");

		static_assert(bksge::is_constructible<
			Tuple,
			std::allocator_arg_t, A1<int>, MoveOnly, MoveOnly, BadDefault, BadDefault
		>::value, "");
	}
}

struct Explicit
{
	int value;
	explicit Explicit(int x) : value(x) {}
};

GTEST_TEST(TupleTest, AllocUTypesCtorTest)
{
	{
		bksge::tuple<Explicit> t{std::allocator_arg, std::allocator<void>{}, 42};
		EXPECT_EQ(bksge::get<0>(t).value, 42);
	}
	{
		bksge::tuple<MoveOnly> t(std::allocator_arg, A1<int>(), MoveOnly(0));
		EXPECT_EQ(bksge::get<0>(t), 0);
	}
	{
		using T = DefaultCtorBlowsUp<>;
		bksge::tuple<T> t(std::allocator_arg, A1<int>(), T(42));
		EXPECT_EQ(bksge::get<0>(t).value, 42);
	}
	{
		bksge::tuple<MoveOnly, MoveOnly> t(std::allocator_arg, A1<int>(),
			MoveOnly(0), MoveOnly(1));
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 1);
	}
	{
		using T = DefaultCtorBlowsUp<>;
		bksge::tuple<T, T> t(std::allocator_arg, A1<int>(), T(42), T(43));
		EXPECT_EQ(bksge::get<0>(t).value, 42);
		EXPECT_EQ(bksge::get<1>(t).value, 43);
	}
	{
		bksge::tuple<MoveOnly, MoveOnly, MoveOnly> t(std::allocator_arg, A1<int>(),
			MoveOnly(0),
			1, 2);
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 1);
		EXPECT_EQ(bksge::get<2>(t), 2);
	}
	{
		using T = DefaultCtorBlowsUp<>;
		bksge::tuple<T, T, T> t(std::allocator_arg, A1<int>(), T(1), T(2), T(3));
		EXPECT_EQ(bksge::get<0>(t).value, 1);
		EXPECT_EQ(bksge::get<1>(t).value, 2);
		EXPECT_EQ(bksge::get<2>(t).value, 3);
	}
	{
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		bksge::tuple<int, alloc_first, alloc_last> t(std::allocator_arg, A1<int>(5), 1, 2, 3);
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(bksge::get<1>(t) == alloc_first(2));
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_TRUE(bksge::get<2>(t) == alloc_last(3));
	}
	{
		// Check that uses-allocator construction is still selected when
		// given a tag type that derives from allocator_arg_t.
		DerivedFromAllocArgT tag;
		alloc_first::allocator_constructed = false;
		alloc_last::allocator_constructed = false;
		bksge::tuple<int, alloc_first, alloc_last> t(tag, A1<int>(5), 1, 2, 3);
		EXPECT_EQ(bksge::get<0>(t), 1);
		EXPECT_TRUE(alloc_first::allocator_constructed);
		EXPECT_TRUE(bksge::get<1>(t) == alloc_first(2));
		EXPECT_TRUE(alloc_last::allocator_constructed);
		EXPECT_TRUE(bksge::get<2>(t) == alloc_last(3));
	}
	// Stress test the SFINAE on the uses-allocator constructors and
	// ensure that the "reduced-arity-initialization" extension is not offered
	// for these constructors.
	test_uses_allocator_sfinae_evaluation();
}

}	// namespace alloc_utypes_ctor_test

namespace const_pair_ctor_test
{

struct Explicit
{
	int value;
	explicit Explicit(int x) noexcept : value(x) {}
};

struct Implicit
{
	int value;
	Implicit(int x) : value(x) {}
};

GTEST_TEST(TupleTest, ConstPairCtorTest)
{
	{
		static_assert( bksge::is_constructible<
			bksge::tuple<long long, short>,
			bksge::pair<long, char>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<>,
			bksge::pair<long, char>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<long>,
			bksge::pair<long, char>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<Explicit, Explicit>,
			bksge::pair<long, char>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<Implicit, Implicit>,
			bksge::pair<long, char>>(), "");
	}
	{
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long long, short>,
			bksge::pair<long, char>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<>,
			bksge::pair<long, char>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<long>,
			bksge::pair<long, char>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<Explicit, Explicit>,
			bksge::pair<long, char>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<Implicit, Implicit>,
			bksge::pair<long, char>>(), "");
	}
	{
#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert( bksge::is_nothrow_constructible<
			bksge::tuple<long long, short>,
			bksge::pair<long, char>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<>,
			bksge::pair<long, char>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long>,
			bksge::pair<long, char>>(), "");
		static_assert( bksge::is_nothrow_constructible<
			bksge::tuple<Explicit, Explicit>,
			bksge::pair<long, char>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Implicit, Implicit>,
			bksge::pair<long, char>>(), "");
#endif
	}
	{
		typedef bksge::pair<long, char> T0;
		typedef bksge::tuple<long long, short> T1;
		T0 t0(2, 'a');
		T1 t1 = t0;
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), short('a'));
	}
	{
		typedef bksge::pair<long, char> P0;
		typedef bksge::tuple<long long, short> T1;
		BKSGE_CXX14_CONSTEXPR P0 p0(2, 'a');
		BKSGE_CXX14_CONSTEXPR T1 t1 = p0;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t1), bksge::get<0>(p0));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<1>(t1), bksge::get<1>(p0));
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t1), 2);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<1>(t1), short('a'));
	}
}

}	// namespace const_pair_ctor_test

namespace convert_copy_ctor_test
{

struct Explicit
{
	int value;
	explicit Explicit(int x) : value(x) {}
};

struct Implicit
{
	int value;
	Implicit(int x) : value(x) {}
};

struct B
{
	int id_;

	explicit B(int i) : id_(i) {}
};

struct D
	: B
{
	explicit D(int i) : B(i) {}
};

struct A
{
	int id_;

	constexpr A(int i) noexcept : id_(i) {}
	friend constexpr bool operator==(const A& x, const A& y) { return x.id_ == y.id_; }
};

struct C
{
	int id_;

	constexpr explicit C(int i) : id_(i) {}
	friend constexpr bool operator==(const C& x, const C& y) { return x.id_ == y.id_; }
};

GTEST_TEST(TupleTest, ConvertCopyCtorTest)
{
	{
		static_assert( bksge::is_constructible<
			bksge::tuple<long long>,
			bksge::tuple<long>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<long long>,
			bksge::tuple<>>(), "");
#if !(defined(_MSC_VER) && (_MSC_VER < 1920))
		static_assert(!bksge::is_constructible<
			bksge::tuple<>,
			bksge::tuple<int>>(), "");
#endif
		static_assert(!bksge::is_constructible<
			bksge::tuple<int>,
			bksge::tuple<int, float>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<Explicit>,
			bksge::tuple<int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<Implicit>,
			bksge::tuple<int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<A>,
			bksge::tuple<int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<C>,
			bksge::tuple<int>>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<B>,
			bksge::tuple<D>>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<D>,
			bksge::tuple<B>>(), "");
	}
	{
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long long>,
			bksge::tuple<long>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<long long>,
			bksge::tuple<>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<int>,
			bksge::tuple<int, float>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<Explicit>,
			bksge::tuple<int>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<Implicit>,
			bksge::tuple<int>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<A>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<C>,
			bksge::tuple<int>>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<B>,
			bksge::tuple<D>>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<D>,
			bksge::tuple<B>>(), "");
	}
	{
#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert( bksge::is_nothrow_constructible<
			bksge::tuple<long long>,
			bksge::tuple<long>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long long>,
			bksge::tuple<>>(), "");
#if !(defined(_MSC_VER) && (_MSC_VER < 1920))
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<>,
			bksge::tuple<int>>(), "");
#endif
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<int>,
			bksge::tuple<int, float>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Explicit>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Implicit>,
			bksge::tuple<int>>(), "");
		static_assert( bksge::is_nothrow_constructible<
			bksge::tuple<A>,
			bksge::tuple<int>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<C>,
			bksge::tuple<int>>(), "");
		static_assert( bksge::is_nothrow_constructible<
			bksge::tuple<B>,
			bksge::tuple<D>>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<D>,
			bksge::tuple<B>>(), "");
#endif
	}
	{
		typedef bksge::tuple<long> T0;
		typedef bksge::tuple<long long> T1;
		T0 t0(2);
		T1 t1 = t0;
		EXPECT_EQ(bksge::get<0>(t1), 2);
	}
	{
		typedef bksge::tuple<int> T0;
		typedef bksge::tuple<A> T1;
		BKSGE_CXX14_CONSTEXPR T0 t0(2);
		BKSGE_CXX14_CONSTEXPR T1 t1 = t0;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t1), 2);
	}
	{
		typedef bksge::tuple<int> T0;
		typedef bksge::tuple<C> T1;
		BKSGE_CXX14_CONSTEXPR T0 t0(2);
		BKSGE_CXX14_CONSTEXPR T1 t1{t0};
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t1), C(2));
	}
	{
		typedef bksge::tuple<long, char> T0;
		typedef bksge::tuple<long long, int> T1;
		T0 t0(2, 'a');
		T1 t1 = t0;
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
	}
	{
		typedef bksge::tuple<long, char, D> T0;
		typedef bksge::tuple<long long, int, B> T1;
		T0 t0(2, 'a', D(3));
		T1 t1 = t0;
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
		EXPECT_EQ(bksge::get<2>(t1).id_, 3);
	}
	// TODO
	//{
	//    D d(3);
	//    typedef bksge::tuple<long, char, D&> T0;
	//    typedef bksge::tuple<long long, int, B&> T1;
	//    T0 t0(2, 'a', d);
	//    T1 t1 = t0;
	//    d.id_ = 2;
	//    EXPECT_EQ(bksge::get<0>(t1), 2);
	//    EXPECT_EQ(bksge::get<1>(t1), int('a'));
	//    EXPECT_EQ(bksge::get<2>(t1).id_, 2);
	//}
	{
		typedef bksge::tuple<long, char, int> T0;
		typedef bksge::tuple<long long, int, B> T1;
		T0 t0(2, 'a', 3);
		T1 t1(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
		EXPECT_EQ(bksge::get<2>(t1).id_, 3);
	}
	{
		const bksge::tuple<int> t1(42);
		bksge::tuple<Explicit> t2(t1);
		EXPECT_EQ(bksge::get<0>(t2).value, 42);
	}
	{
		const bksge::tuple<int> t1(42);
		bksge::tuple<Implicit> t2 = t1;
		EXPECT_EQ(bksge::get<0>(t2).value, 42);
	}
}

}	// namespace convert_copy_ctor_test

namespace convert_move_ctor_test
{

struct Explicit
{
	int value;
	explicit Explicit(int x) : value(x) {}
};

struct Implicit
{
	int value;
	Implicit(int x) noexcept : value(x) {}
};

struct B
{
	int id_;

	explicit B(int i) : id_(i) {}

	virtual ~B() {}
};

struct D : B
{
	explicit D(int i) : B(i) {}
};

GTEST_TEST(TupleTest, ConvertMoveCtorTest)
{
	{
		static_assert( bksge::is_constructible<
			bksge::tuple<long long>,
			bksge::tuple<long>&&>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<long long>,
			bksge::tuple<>&&>(), "");
#if !(defined(_MSC_VER) && (_MSC_VER < 1920))
		static_assert(!bksge::is_constructible<
			bksge::tuple<>,
			bksge::tuple<int>&&>(), "");
#endif
		static_assert(!bksge::is_constructible<
			bksge::tuple<int>,
			bksge::tuple<int, float>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<Explicit>,
			bksge::tuple<int>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<Implicit>,
			bksge::tuple<int>&&>(), "");
		static_assert( bksge::is_constructible<
			bksge::tuple<B>,
			bksge::tuple<D>&&>(), "");
		static_assert(!bksge::is_constructible<
			bksge::tuple<D>,
			bksge::tuple<B>&&>(), "");
	}
	{
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<long long>,
			bksge::tuple<long>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<long long>,
			bksge::tuple<>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<>,
			bksge::tuple<int>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<int>,
			bksge::tuple<int, float>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<Explicit>,
			bksge::tuple<int>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<Implicit>,
			bksge::tuple<int>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<
			bksge::tuple<B>,
			bksge::tuple<D>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<
			bksge::tuple<D>,
			bksge::tuple<B>&&>(), "");
	}
	{
#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert( bksge::is_nothrow_constructible<
			bksge::tuple<long long>,
			bksge::tuple<long>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<long long>,
			bksge::tuple<>&&>(), "");
#if !(defined(_MSC_VER) && (_MSC_VER < 1920))
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<>,
			bksge::tuple<int>&&>(), "");
#endif
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<int>,
			bksge::tuple<int, float>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<Explicit>,
			bksge::tuple<int>&&>(), "");
		static_assert( bksge::is_nothrow_constructible<
			bksge::tuple<Implicit>,
			bksge::tuple<int>&&>(), "");
		static_assert( bksge::is_nothrow_constructible<
			bksge::tuple<B>,
			bksge::tuple<D>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<
			bksge::tuple<D>,
			bksge::tuple<B>&&>(), "");
#endif
	}
	{
		typedef bksge::tuple<long> T0;
		typedef bksge::tuple<long long> T1;
		T0 t0(2);
		T1 t1 = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
	}
	{
		typedef bksge::tuple<long, char> T0;
		typedef bksge::tuple<long long, int> T1;
		T0 t0(2, 'a');
		T1 t1 = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
	}
	{
		typedef bksge::tuple<long, char, D> T0;
		typedef bksge::tuple<long long, int, B> T1;
		T0 t0(2, 'a', D(3));
		T1 t1 = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
		EXPECT_EQ(bksge::get<2>(t1).id_, 3);
	}
	// TODO
	//{
	//    D d(3);
	//    typedef bksge::tuple<long, char, D&> T0;
	//    typedef bksge::tuple<long long, int, B&> T1;
	//    T0 t0(2, 'a', d);
	//    T1 t1 = bksge::move(t0);
	//    d.id_ = 2;
	//    EXPECT_EQ(bksge::get<0>(t1), 2);
	//    EXPECT_EQ(bksge::get<1>(t1), int('a'));
	//    EXPECT_EQ(bksge::get<2>(t1).id_, 2);
	//}
	{
		typedef bksge::tuple<long, char, bksge::unique_ptr<D>> T0;
		typedef bksge::tuple<long long, int, bksge::unique_ptr<B>> T1;
		T0 t0(2, 'a', bksge::unique_ptr<D>(new D(3)));
		T1 t1 = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
		EXPECT_EQ(bksge::get<2>(t1)->id_, 3);
	}
	{
		bksge::tuple<int> t1(42);
		bksge::tuple<Explicit> t2(bksge::move(t1));
		EXPECT_EQ(bksge::get<0>(t2).value, 42);
	}
	{
		bksge::tuple<int> t1(42);
		bksge::tuple<Implicit> t2 = bksge::move(t1);
		EXPECT_EQ(bksge::get<0>(t2).value, 42);
	}
}

}	// namespace convert_move_ctor_test

namespace copy_ctor_test
{

struct Empty {};

GTEST_TEST(TupleTest, CopyCtorTest)
{
	{
		static_assert( bksge::is_copy_constructible<bksge::tuple<>>(), "");
		static_assert( bksge::is_copy_constructible<bksge::tuple<int>>(), "");
		static_assert( bksge::is_copy_constructible<bksge::tuple<int, char>>(), "");
		static_assert( bksge::is_copy_constructible<bksge::tuple<int, char, std::string>>(), "");
		static_assert( bksge::is_copy_constructible<bksge::tuple<Empty>>(), "");
	}
	{
		static_assert( bksge::is_implicitly_copy_constructible<bksge::tuple<>>(), "");
		static_assert( bksge::is_implicitly_copy_constructible<bksge::tuple<int>>(), "");
		static_assert( bksge::is_implicitly_copy_constructible<bksge::tuple<int, char>>(), "");
		static_assert( bksge::is_implicitly_copy_constructible<bksge::tuple<int, char, std::string>>(), "");
		static_assert( bksge::is_implicitly_copy_constructible<bksge::tuple<Empty>>(), "");
	}
	{
		static_assert( bksge::is_nothrow_copy_constructible<bksge::tuple<>>(), "");
		static_assert( bksge::is_nothrow_copy_constructible<bksge::tuple<int>>(), "");
		static_assert( bksge::is_nothrow_copy_constructible<bksge::tuple<int, char>>(), "");
		static_assert(!bksge::is_nothrow_copy_constructible<bksge::tuple<int, char, std::string>>(), "");
		static_assert( bksge::is_nothrow_copy_constructible<bksge::tuple<Empty>>(), "");
	}
	{
		typedef bksge::tuple<> T;
		T t0;
		T t = t0;
		((void)t); // Prevent unused warning
	}
	{
		typedef bksge::tuple<int> T;
		T t0(2);
		T t = t0;
		EXPECT_EQ(bksge::get<0>(t), 2);
	}
	{
		typedef bksge::tuple<int, char> T;
		T t0(2, 'a');
		T t = t0;
		EXPECT_EQ(bksge::get<0>(t), 2);
		EXPECT_EQ(bksge::get<1>(t), 'a');
	}
	{
		typedef bksge::tuple<int, char, std::string> T;
		const T t0(2, 'a', "some text");
		T t = t0;
		EXPECT_EQ(bksge::get<0>(t), 2);
		EXPECT_EQ(bksge::get<1>(t), 'a');
		EXPECT_TRUE(bksge::get<2>(t) == "some text");
	}
	{
		typedef bksge::tuple<int> T;
		BKSGE_CXX14_CONSTEXPR T t0(2);
		BKSGE_CXX14_CONSTEXPR T t = t0;
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t), 2);
	}
	{
		typedef bksge::tuple<Empty> T;
		BKSGE_CXX14_CONSTEXPR T t0;
		BKSGE_CXX14_CONSTEXPR T t = t0;
		BKSGE_CXX14_CONSTEXPR Empty e = bksge::get<0>(t);
		((void)e); // Prevent unused warning
	}
}

}	// namespace copy_ctor_test

GTEST_TEST(TupleTest, DtorTest)
{
	static_assert(bksge::is_trivially_destructible<bksge::tuple<> >::value, "");
	static_assert(bksge::is_trivially_destructible<bksge::tuple<void*> >::value, "");
	static_assert(bksge::is_trivially_destructible<bksge::tuple<int, float> >::value, "");
	static_assert(!bksge::is_trivially_destructible<bksge::tuple<std::string> >::value, "");
	static_assert(!bksge::is_trivially_destructible<bksge::tuple<int, std::string> >::value, "");
}

namespace move_ctor_test
{

struct ConstructsWithTupleLeaf
{
	ConstructsWithTupleLeaf() {}

	ConstructsWithTupleLeaf(ConstructsWithTupleLeaf const &) { assert(false); }
	ConstructsWithTupleLeaf(ConstructsWithTupleLeaf &&) {}

	template <typename T>
	ConstructsWithTupleLeaf(T)
	{
		static_assert(!bksge::is_same<T, T>::value,
			"Constructor instantiated for type other than int");
	}
};

// move_only type which triggers the empty base optimization
struct move_only_ebo
{
	move_only_ebo() = default;
	move_only_ebo(move_only_ebo&&) = default;
};

// a move_only type which does not trigger the empty base optimization
struct move_only_large final
{
	move_only_large() : value(42) {}
	move_only_large(move_only_large&&) = default;
	int value;
};

struct ImplicitMovable
{
	ImplicitMovable(ImplicitMovable&&) {}
};

struct ExplicitMovable
{
	explicit ExplicitMovable(ExplicitMovable&&) {}
};

template <typename Elem>
void test_sfinae()
{
	using Tup = bksge::tuple<Elem>;
	using Alloc = std::allocator<int>;
	using Tag = std::allocator_arg_t;
	// special members
	{
		static_assert(bksge::is_default_constructible<Tup>::value, "");
		static_assert(bksge::is_move_constructible<Tup>::value, "");
		static_assert(!bksge::is_copy_constructible<Tup>::value, "");
		static_assert(!bksge::is_constructible<Tup, Tup&>::value, "");
	}
	// args constructors
	{
		static_assert(bksge::is_constructible<Tup, Elem&&>::value, "");
		static_assert(!bksge::is_constructible<Tup, Elem const&>::value, "");
		static_assert(!bksge::is_constructible<Tup, Elem&>::value, "");
	}
	// uses-allocator special member constructors
	{
#if (BKSGE_CXX_STANDARD >= 20)
		static_assert(bksge::is_constructible<Tup, Tag, Alloc>::value, "");
		static_assert(bksge::is_constructible<Tup, Tag, Alloc, Tup&&>::value, "");
		static_assert(!bksge::is_constructible<Tup, Tag, Alloc, Tup const&>::value, "");
		static_assert(!bksge::is_constructible<Tup, Tag, Alloc, Tup &>::value, "");
#endif
	}
	// uses-allocator args constructors
	{
		static_assert(bksge::is_constructible<Tup, Tag, Alloc, Elem&&>::value, "");
		static_assert(!bksge::is_constructible<Tup, Tag, Alloc, Elem const&>::value, "");
		static_assert(!bksge::is_constructible<Tup, Tag, Alloc, Elem &>::value, "");
	}
}

GTEST_TEST(TupleTest, MoveCtorTest)
{
	{
		static_assert( bksge::is_move_constructible<bksge::tuple<>>(), "");
		static_assert( bksge::is_move_constructible<bksge::tuple<int>>(), "");
		static_assert( bksge::is_move_constructible<bksge::tuple<int, char>>(), "");
		static_assert( bksge::is_move_constructible<bksge::tuple<int, char, std::string>>(), "");
		static_assert( bksge::is_move_constructible<bksge::tuple<move_only_ebo>>(), "");
		static_assert( bksge::is_move_constructible<bksge::tuple<move_only_large>>(), "");
		static_assert( bksge::is_move_constructible<bksge::tuple<ImplicitMovable>>(), "");
		static_assert( bksge::is_move_constructible<bksge::tuple<ExplicitMovable>>(), "");
	}
	{
		static_assert( bksge::is_implicitly_move_constructible<bksge::tuple<>>(), "");
		static_assert( bksge::is_implicitly_move_constructible<bksge::tuple<int>>(), "");
		static_assert( bksge::is_implicitly_move_constructible<bksge::tuple<int, char>>(), "");
		static_assert( bksge::is_implicitly_move_constructible<bksge::tuple<int, char, std::string>>(), "");
		static_assert( bksge::is_implicitly_move_constructible<bksge::tuple<move_only_ebo>>(), "");
		static_assert( bksge::is_implicitly_move_constructible<bksge::tuple<move_only_large>>(), "");
		static_assert( bksge::is_implicitly_move_constructible<bksge::tuple<ImplicitMovable>>(), "");
		static_assert( bksge::is_implicitly_move_constructible<bksge::tuple<ExplicitMovable>>(), "");
	}
	{
		static_assert( bksge::is_nothrow_move_constructible<bksge::tuple<>>(), "");
		static_assert( bksge::is_nothrow_move_constructible<bksge::tuple<int>>(), "");
		static_assert( bksge::is_nothrow_move_constructible<bksge::tuple<int, char>>(), "");
		static_assert( bksge::is_nothrow_move_constructible<bksge::tuple<int, char, std::string>>(), "");
		static_assert( bksge::is_nothrow_move_constructible<bksge::tuple<move_only_ebo>>(), "");
		static_assert( bksge::is_nothrow_move_constructible<bksge::tuple<move_only_large>>(), "");
		static_assert(!bksge::is_nothrow_move_constructible<bksge::tuple<ImplicitMovable>>(), "");
		static_assert(!bksge::is_nothrow_move_constructible<bksge::tuple<ExplicitMovable>>(), "");
	}
	{
		typedef bksge::tuple<> T;
		T t0;
		T t = bksge::move(t0);
		((void)t); // Prevent unused warning
	}
	{
		typedef bksge::tuple<MoveOnly> T;
		T t0(MoveOnly(0));
		T t = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t), 0);
	}
	{
		typedef bksge::tuple<MoveOnly, MoveOnly> T;
		T t0(MoveOnly(0), MoveOnly(1));
		T t = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 1);
	}
	{
		typedef bksge::tuple<MoveOnly, MoveOnly, MoveOnly> T;
		T t0(MoveOnly(0), MoveOnly(1), MoveOnly(2));
		T t = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 1);
		EXPECT_EQ(bksge::get<2>(t), 2);
	}
#if 0
	// A bug in tuple caused __tuple_leaf to use its explicit converting constructor
	//  as its move constructor. This tests that ConstructsWithTupleLeaf is not called
	// (w/ __tuple_leaf)
	{
		typedef bksge::tuple<ConstructsWithTupleLeaf> d_t;
		d_t d((ConstructsWithTupleLeaf()));
		d_t d2(static_cast<d_t &&>(d));
	}
#endif
	{
		test_sfinae<move_only_ebo>();
#if (BKSGE_CXX_STANDARD >= 20)
		test_sfinae<move_only_large>();
#endif
	}
}

}	// namespace move_ctor_test

namespace move_pair_ctor_test
{

struct B
{
	int id_;

	explicit B(int i) : id_(i) {}

	virtual ~B() {}
};

struct D : B
{
	explicit D(int i) : B(i) {}
};

GTEST_TEST(TupleTest, MovePairCtorTest)
{
	{
		static_assert(!bksge::is_constructible<bksge::tuple<>,            bksge::pair<int, double>&&>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<int>,         bksge::pair<int, double>&&>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<double>,      bksge::pair<int, double>&&>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int, double>, bksge::pair<int, double>&&>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int, double>, bksge::pair<float, int>&&>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<B, D>,        bksge::pair<B, B>&&>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<B, D>,        bksge::pair<B, D>&&>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<B, D>,        bksge::pair<D, B>&&>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<B, D>,        bksge::pair<D, D>&&>(), "");
	}
	{
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<>,            bksge::pair<int, double>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<int>,         bksge::pair<int, double>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<double>,      bksge::pair<int, double>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int, double>, bksge::pair<int, double>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int, double>, bksge::pair<float, int>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<B, D>,        bksge::pair<B, B>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<B, D>,        bksge::pair<B, D>&&>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<B, D>,        bksge::pair<D, B>&&>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<B, D>,        bksge::pair<D, D>&&>(), "");
	}
	{
#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<>,            bksge::pair<int, double>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int>,         bksge::pair<int, double>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<double>,      bksge::pair<int, double>&&>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int, double>, bksge::pair<int, double>&&>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int, double>, bksge::pair<float, int>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<B, D>,        bksge::pair<B, B>&&>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<B, D>,        bksge::pair<B, D>&&>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<B, D>,        bksge::pair<D, B>&&>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<B, D>,        bksge::pair<D, D>&&>(), "");
#endif
	}
	{
		typedef bksge::pair<long, bksge::unique_ptr<D>> T0;
		typedef bksge::tuple<long long, bksge::unique_ptr<B>> T1;
		T0 t0(2, bksge::unique_ptr<D>(new D(3)));
		T1 t1 = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1)->id_, 3);
	}
}

}	// namespace move_pair_ctor_test

namespace lazy_sfinae_ctor_test
{

template <typename ConstructFrom>
struct ConstructibleFromT
{
	ConstructibleFromT() = default;
	ConstructibleFromT(ConstructFrom v) : value(v) {}
	ConstructFrom value;
};

template <typename AssertOn>
struct CtorAssertsT
{
	bool defaulted;
	CtorAssertsT() : defaulted(true) {}
	template <typename T>
	constexpr CtorAssertsT(T) : defaulted(false)
	{
		static_assert(!bksge::is_same<T, AssertOn>::value, "");
	}
};

template <typename AllowT, typename AssertT>
struct AllowAssertT
{
	AllowAssertT() = default;
	AllowAssertT(AllowT) {}
	template <typename U>
	constexpr AllowAssertT(U)
	{
		static_assert(!bksge::is_same<U, AssertT>::value, "");
	}
};

// Construct a tuple<T1, T2> from pair<int, int> where T1 and T2
// are not constructible from ints but T1 is constructible from bksge::pair.
// This considers the following constructors:
// (1) tuple(TupleLike) -> checks is_constructible<Tn, int>
// (2) tuple(UTypes...) -> checks is_constructible<T1, pair<int, int>>
//                            and is_default_constructible<T2>
// The point of this test is to ensure that the consideration of (1)
// short circuits before evaluating is_constructible<T2, int>, which
// will cause a static assertion.
void test_tuple_like_lazy_sfinae()
{
#if 0//defined(_LIBCPP_VERSION)
	// This test requires libc++'s reduced arity initialization.
	using T1 = ConstructibleFromT<bksge::pair<int, int>>;
	using T2 = CtorAssertsT<int>;
	bksge::pair<int, int> p(42, 100);
	bksge::tuple<T1, T2> t(p);
	EXPECT_TRUE(bksge::get<0>(t).value == p);
	EXPECT_TRUE(bksge::get<1>(t).defaulted);
#endif
}

#if !defined(_MSC_VER)
struct NonConstCopyable
{
	NonConstCopyable() = default;
	explicit NonConstCopyable(int v) : value(v) {}
	NonConstCopyable(NonConstCopyable&) = default;
	NonConstCopyable(NonConstCopyable const&) = delete;
	int value;
};

template <typename T>
struct BlowsUpOnConstCopy
{
	BlowsUpOnConstCopy() = default;
	constexpr BlowsUpOnConstCopy(BlowsUpOnConstCopy const&)
	{
		static_assert(!bksge::is_same<T, T>::value, "");
	}
	BlowsUpOnConstCopy(BlowsUpOnConstCopy&) = default;
};
#endif

// Test the following constructors:
// (1) tuple(Types const&...)
// (2) tuple(UTypes&&...)
// Test that (1) short circuits before evaluating the copy constructor of the
// second argument. Constructor (2) should be selected.
void test_const_Types_lazy_sfinae()
{
#if !defined(_MSC_VER)
	NonConstCopyable v(42);
	BlowsUpOnConstCopy<int> b;
	bksge::tuple<NonConstCopyable, BlowsUpOnConstCopy<int>> t(v, b);
	EXPECT_EQ(bksge::get<0>(t).value, 42);
#endif
}

GTEST_TEST(TupleTest, LazySFINAECtorTest)
{
	test_tuple_like_lazy_sfinae();
	test_const_Types_lazy_sfinae();
}

}	// namespace lazy_sfinae_ctor_test

GTEST_TEST(TupleTest, ArrayTemplateDepthCtorTest)
{
	typedef std::array<char, 1256> array_t;
	typedef bksge::tuple<array_t> tuple_t;

	array_t arr;
	tuple_t tup(arr);
}

namespace utypes_ctor_test
{

struct Empty {};
struct A
{
	int id_;
	explicit constexpr A(int i) : id_(i) {}
};

struct NoDefault { NoDefault() = delete; };

// Make sure the _Up... constructor SFINAEs out when the types that
// are not explicitly initialized are not all default constructible.
// Otherwise, bksge::is_constructible would return true but instantiating
// the constructor would fail.
void test_default_constructible_extension_sfinae()
{
	{
		typedef bksge::tuple<MoveOnly, NoDefault> Tuple;

		static_assert(!bksge::is_constructible<
			Tuple,
			MoveOnly
		>::value, "");

		static_assert(bksge::is_constructible<
			Tuple,
			MoveOnly, NoDefault
		>::value, "");
	}
	{
		typedef bksge::tuple<MoveOnly, MoveOnly, NoDefault> Tuple;

		static_assert(!bksge::is_constructible<
			Tuple,
			MoveOnly, MoveOnly
		>::value, "");

		static_assert(bksge::is_constructible<
			Tuple,
			MoveOnly, MoveOnly, NoDefault
		>::value, "");
	}
	{
		// Same idea as above but with a nested tuple type.
		typedef bksge::tuple<MoveOnly, NoDefault> Tuple;
		typedef bksge::tuple<MoveOnly, Tuple, MoveOnly, MoveOnly> NestedTuple;

		static_assert(!bksge::is_constructible<
			NestedTuple,
			MoveOnly, MoveOnly, MoveOnly, MoveOnly
		>::value, "");

		static_assert(bksge::is_constructible<
			NestedTuple,
			MoveOnly, Tuple, MoveOnly, MoveOnly
		>::value, "");
	}
	// testing extensions
#if 0
	{
		typedef bksge::tuple<MoveOnly, int> Tuple;
		typedef bksge::tuple<MoveOnly, Tuple, MoveOnly, MoveOnly> NestedTuple;

		static_assert(bksge::is_constructible<
			NestedTuple,
			MoveOnly, MoveOnly, MoveOnly, MoveOnly
		>::value, "");

		static_assert(bksge::is_constructible<
			NestedTuple,
			MoveOnly, Tuple, MoveOnly, MoveOnly
		>::value, "");
	}
#endif
}

GTEST_TEST(TupleTest, UTypesCtorTest)
{
	{
		static_assert(!bksge::is_constructible<bksge::tuple<>, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int>, int>(), "");
		static_assert(!bksge::is_constructible<bksge::tuple<int>, int, float>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<int, float>, int, float>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<A>, int>(), "");
		static_assert( bksge::is_constructible<bksge::tuple<A>, A const&>(), "");
	}
	{
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<>, int>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int>, int>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<int>, int, float>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<int, float>, int, float>(), "");
		static_assert(!bksge::is_implicitly_constructible<bksge::tuple<A>, int>(), "");
		static_assert( bksge::is_implicitly_constructible<bksge::tuple<A>, A const&>(), "");
	}
	{
#if 0//(BKSGE_CXX_STANDARD >= 20)
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<>, int>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int>, int>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<int>, int, float>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<int, float>, int, float>(), "");
		static_assert(!bksge::is_nothrow_constructible<bksge::tuple<A>, int>(), "");
		static_assert( bksge::is_nothrow_constructible<bksge::tuple<A>, A const&>(), "");
#endif
	}
	{
		bksge::tuple<MoveOnly> t(MoveOnly(0));
		EXPECT_EQ(bksge::get<0>(t), 0);
	}
	{
		bksge::tuple<MoveOnly, MoveOnly> t(MoveOnly(0), MoveOnly(1));
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 1);
	}
	{
		bksge::tuple<MoveOnly, MoveOnly, MoveOnly> t(MoveOnly(0),
			MoveOnly(1),
			MoveOnly(2));
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 1);
		EXPECT_EQ(bksge::get<2>(t), 2);
	}
	// extensions
#if 0
	{
		using E = MoveOnly;
		using Tup = bksge::tuple<E, E, E>;
		// Test that the reduced arity initialization extension is only
		// allowed on the explicit constructor.
		static_assert(test_convertible<Tup, E, E, E>(), "");

		Tup t(E(0), E(1));
		static_assert(!test_convertible<Tup, E, E>(), "");
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 1);
		EXPECT_TRUE(bksge::get<2>(t) == MoveOnly());

		Tup t2(E(0));
		static_assert(!test_convertible<Tup, E>(), "");
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_TRUE(bksge::get<1>(t) == E());
		EXPECT_TRUE(bksge::get<2>(t) == E());
	}
#endif
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<Empty> t0{Empty()};
		(void)t0;
	}
	{
		BKSGE_CXX14_CONSTEXPR bksge::tuple<A, A> t(3, 2);
		BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(bksge::get<0>(t).id_, 3);
	}
	// Check that SFINAE is properly applied with the default reduced arity
	// constructor extensions.
	test_default_constructible_extension_sfinae();
}

}	// namespace utypes_ctor_test

GTEST_TEST(TupleTest, ConstPairAssignTest)
{
	typedef bksge::pair<long, char> T0;
	typedef bksge::tuple<long long, short> T1;
	T0 t0(2, 'a');
	T1 t1;
	t1 = t0;
	EXPECT_EQ(bksge::get<0>(t1), 2);
	EXPECT_EQ(bksge::get<1>(t1), short('a'));
}

namespace convert_copy_assign_test
{

struct B
{
	int id_;

	explicit B(int i = 0) : id_(i) {}
};

struct D : B
{
	explicit D(int i = 0) : B(i) {}
};

GTEST_TEST(TupleTest, ConvertCopyAssignTest)
{
	{
		typedef bksge::tuple<long> T0;
		typedef bksge::tuple<long long> T1;
		T0 t0(2);
		T1 t1;
		t1 = t0;
		EXPECT_EQ(bksge::get<0>(t1), 2);
	}
	{
		typedef bksge::tuple<long, char> T0;
		typedef bksge::tuple<long long, int> T1;
		T0 t0(2, 'a');
		T1 t1;
		t1 = t0;
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
	}
	{
		typedef bksge::tuple<long, char, D> T0;
		typedef bksge::tuple<long long, int, B> T1;
		T0 t0(2, 'a', D(3));
		T1 t1;
		t1 = t0;
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
		EXPECT_EQ(bksge::get<2>(t1).id_, 3);
	}
	// TODO
	//{
	//	D d(3);
	//	D d2(2);
	//	typedef bksge::tuple<long, char, D&> T0;
	//	typedef bksge::tuple<long long, int, B&> T1;
	//	T0 t0(2, 'a', d2);
	//	T1 t1(1, 'b', d);
	//	t1 = t0;
	//	EXPECT_EQ(bksge::get<0>(t1), 2);
	//	EXPECT_EQ(bksge::get<1>(t1), int('a'));
	//	EXPECT_EQ(bksge::get<2>(t1).id_, 2);
	//}
	{
		// Test that tuple evaluates correctly applies an lvalue reference
		// before evaluating is_assignable (ie 'is_assignable<int&, int&>')
		// instead of evaluating 'is_assignable<int&&, int&>' which is false.
		int x = 42;
		int y = 43;
		bksge::tuple<int&&> t(bksge::move(x));
		bksge::tuple<int&> t2(y);
		t = t2;
		EXPECT_EQ(bksge::get<0>(t), 43);
		EXPECT_TRUE(&bksge::get<0>(t) == &x);
	}
}

}	// namespace convert_copy_assign_test

namespace convert_move_assign_test
{

struct B
{
	int id_;

	explicit B(int i= 0) : id_(i) {}

	virtual ~B() {}
};

struct D : B
{
	explicit D(int i) : B(i) {}
};

struct E
{
	E() = default;
	E& operator=(int)
	{
		return *this;
	}
};

GTEST_TEST(TupleTest, ConvertMoveAssignTest)
{
	{
		typedef bksge::tuple<long> T0;
		typedef bksge::tuple<long long> T1;
		T0 t0(2);
		T1 t1;
		t1 = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
	}
	{
		typedef bksge::tuple<long, char> T0;
		typedef bksge::tuple<long long, int> T1;
		T0 t0(2, 'a');
		T1 t1;
		t1 = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
	}
	{
		typedef bksge::tuple<long, char, D> T0;
		typedef bksge::tuple<long long, int, B> T1;
		T0 t0(2, 'a', D(3));
		T1 t1;
		t1 = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
		EXPECT_EQ(bksge::get<2>(t1).id_, 3);
	}
	// TODO
	//{
	//	D d(3);
	//	D d2(2);
	//	typedef bksge::tuple<long, char, D&> T0;
	//	typedef bksge::tuple<long long, int, B&> T1;
	//	T0 t0(2, 'a', d2);
	//	T1 t1(1, 'b', d);
	//	t1 = bksge::move(t0);
	//	EXPECT_EQ(bksge::get<0>(t1), 2);
	//	EXPECT_EQ(bksge::get<1>(t1), int('a'));
	//	EXPECT_EQ(bksge::get<2>(t1).id_, 2);
	//}
	{
		typedef bksge::tuple<long, char, bksge::unique_ptr<D>> T0;
		typedef bksge::tuple<long long, int, bksge::unique_ptr<B>> T1;
		T0 t0(2, 'a', bksge::unique_ptr<D>(new D(3)));
		T1 t1;
		t1 = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1), int('a'));
		EXPECT_EQ(bksge::get<2>(t1)->id_, 3);
	}
	{
		// Test that tuple evaluates correctly applies an lvalue reference
		// before evaluating is_assignable (ie 'is_assignable<int&, int&&>')
		// instead of evaluating 'is_assignable<int&&, int&&>' which is false.
		int x = 42;
		int y = 43;
		bksge::tuple<int&&, E> t(bksge::move(x), E{});
		bksge::tuple<int&&, int> t2(bksge::move(y), 44);
		t = bksge::move(t2);
		EXPECT_EQ(bksge::get<0>(t), 43);
		EXPECT_TRUE(&bksge::get<0>(t) == &x);
	}
}

}	// namespace convert_move_assign_test

namespace copy_assign_test
{

struct NonAssignable
{
	NonAssignable& operator=(NonAssignable const&) = delete;
	NonAssignable& operator=(NonAssignable&&) = delete;
};

struct CopyAssignable
{
	CopyAssignable& operator=(CopyAssignable const&) = default;
	CopyAssignable& operator=(CopyAssignable &&) = delete;
};

static_assert(bksge::is_copy_assignable<CopyAssignable>::value, "");

struct MoveAssignable
{
	MoveAssignable& operator=(MoveAssignable const&) = delete;
	MoveAssignable& operator=(MoveAssignable&&) = default;
};

GTEST_TEST(TupleTest, CopyAssignTest)
{
	{
		typedef bksge::tuple<> T;
		T t0;
		T t;
		t = t0;
	}
	{
		typedef bksge::tuple<int> T;
		T t0(2);
		T t;
		t = t0;
		EXPECT_EQ(bksge::get<0>(t), 2);
	}
	{
		typedef bksge::tuple<int, char> T;
		T t0(2, 'a');
		T t;
		t = t0;
		EXPECT_EQ(bksge::get<0>(t), 2);
		EXPECT_EQ(bksge::get<1>(t), 'a');
	}
	{
		typedef bksge::tuple<int, char, std::string> T;
		const T t0(2, 'a', "some text");
		T t;
		t = t0;
		EXPECT_EQ(bksge::get<0>(t), 2);
		EXPECT_EQ(bksge::get<1>(t), 'a');
		EXPECT_TRUE(bksge::get<2>(t) == "some text");
	}
	{
		// test reference assignment.
		using T = bksge::tuple<int&, int&&>;
		int x = 42;
		int y = 100;
		int x2 = -1;
		int y2 = 500;
		T t(x, bksge::move(y));
		T t2(x2, bksge::move(y2));
		t = t2;
		EXPECT_EQ(bksge::get<0>(t), x2);
		EXPECT_TRUE(&bksge::get<0>(t) == &x);
		EXPECT_EQ(bksge::get<1>(t), y2);
		EXPECT_TRUE(&bksge::get<1>(t) == &y);
	}
#if 0
	{
		// test that the implicitly generated copy assignment operator
		// is properly deleted
		using T = bksge::tuple<bksge::unique_ptr<int>>;
		static_assert(!bksge::is_copy_assignable<T>::value, "");
	}
	{
		using T = bksge::tuple<int, NonAssignable>;
		static_assert(!bksge::is_copy_assignable<T>::value, "");
	}
	{
		using T = bksge::tuple<int, CopyAssignable>;
		static_assert(bksge::is_copy_assignable<T>::value, "");
	}
	{
		using T = bksge::tuple<int, MoveAssignable>;
		static_assert(!bksge::is_copy_assignable<T>::value, "");
	}
#endif
}

}	// namespace copy_assign_test

namespace move_assign_test
{

struct NonAssignable
{
	NonAssignable& operator=(NonAssignable const&) = delete;
	NonAssignable& operator=(NonAssignable&&) = delete;
};

struct CopyAssignable
{
	CopyAssignable& operator=(CopyAssignable const&) = default;
	CopyAssignable& operator=(CopyAssignable&&) = delete;
};

static_assert(bksge::is_copy_assignable<CopyAssignable>::value, "");

struct MoveAssignable
{
	MoveAssignable& operator=(MoveAssignable const&) = delete;
	MoveAssignable& operator=(MoveAssignable&&) = default;
};


struct CountAssign
{
	static int copied;
	static int moved;
	static void reset() { copied = moved = 0; }
	CountAssign() = default;
	CountAssign& operator=(CountAssign const&) { ++copied; return *this; }
	CountAssign& operator=(CountAssign&&) { ++moved; return *this; }
};

int CountAssign::copied = 0;
int CountAssign::moved = 0;

GTEST_TEST(TupleTest, MoveAssignTest)
{
	{
		typedef bksge::tuple<> T;
		T t0;
		T t;
		t = bksge::move(t0);
	}
	{
		typedef bksge::tuple<MoveOnly> T;
		T t0(MoveOnly(0));
		T t;
		t = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t), 0);
	}
	{
		typedef bksge::tuple<MoveOnly, MoveOnly> T;
		T t0(MoveOnly(0), MoveOnly(1));
		T t;
		t = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 1);
	}
	{
		typedef bksge::tuple<MoveOnly, MoveOnly, MoveOnly> T;
		T t0(MoveOnly(0), MoveOnly(1), MoveOnly(2));
		T t;
		t = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t), 0);
		EXPECT_EQ(bksge::get<1>(t), 1);
		EXPECT_EQ(bksge::get<2>(t), 2);
	}
	{
		// test reference assignment.
		using T = bksge::tuple<int&, int&&>;
		int x = 42;
		int y = 100;
		int x2 = -1;
		int y2 = 500;
		T t(x, bksge::move(y));
		T t2(x2, bksge::move(y2));
		t = bksge::move(t2);
		EXPECT_EQ(bksge::get<0>(t), x2);
		EXPECT_TRUE(&bksge::get<0>(t) == &x);
		EXPECT_EQ(bksge::get<1>(t), y2);
		EXPECT_TRUE(&bksge::get<1>(t) == &y);
	}
#if 0
	{
		// test that the implicitly generated move assignment operator
		// is properly deleted
		using T = bksge::tuple<bksge::unique_ptr<int>>;
		static_assert(bksge::is_move_assignable<T>::value, "");
		static_assert(!bksge::is_copy_assignable<T>::value, "");

	}
	{
		using T = bksge::tuple<int, NonAssignable>;
		static_assert(!bksge::is_move_assignable<T>::value, "");
	}
	{
		using T = bksge::tuple<int, MoveAssignable>;
		static_assert(bksge::is_move_assignable<T>::value, "");
	}
	{
		// The move should decay to a copy.
		CountAssign::reset();
		using T = bksge::tuple<CountAssign, CopyAssignable>;
		static_assert(bksge::is_move_assignable<T>::value, "");
		T t1;
		T t2;
		t1 = bksge::move(t2);
		EXPECT_EQ(CountAssign::copied, 1);
		EXPECT_EQ(CountAssign::moved, 0);
	}
#endif
}

}	// namespace move_assign_test

namespace move_pair_assign_test
{

struct B
{
	int id_;

	explicit B(int i = 0) : id_(i) {}

	virtual ~B() {}
};

struct D : B
{
	explicit D(int i) : B(i) {}
};

GTEST_TEST(TupleTest, MovePairAssignTest)
{
	{
		typedef bksge::pair<long, bksge::unique_ptr<D>> T0;
		typedef bksge::tuple<long long, bksge::unique_ptr<B>> T1;
		T0 t0(2, bksge::unique_ptr<D>(new D(3)));
		T1 t1;
		t1 = bksge::move(t0);
		EXPECT_EQ(bksge::get<0>(t1), 2);
		EXPECT_EQ(bksge::get<1>(t1)->id_, 3);
	}
}

}	// namespace move_pair_assign_test

GTEST_TEST(TupleTest, ArrayTemplateDepthAssignTest)
{
	typedef std::array<char, 1256> array_t;
	typedef bksge::tuple<array_t> tuple_t;
	array_t arr;
	tuple_t tup;
	tup = arr;
}

GTEST_TEST(TupleTest, EqTest)
{
	{
		typedef bksge::tuple<> T1;
		typedef bksge::tuple<> T2;
		const T1 t1;
		const T2 t2;
		EXPECT_TRUE( (t1 == t2));
		EXPECT_TRUE(!(t1 != t2));
	}
	{
		typedef bksge::tuple<int> T1;
		typedef bksge::tuple<double> T2;
		const T1 t1(1);
		const T2 t2(1.1);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE( (t1 != t2));
	}
	{
		typedef bksge::tuple<int> T1;
		typedef bksge::tuple<double> T2;
		const T1 t1(1);
		const T2 t2(1);
		EXPECT_TRUE( (t1 == t2));
		EXPECT_TRUE(!(t1 != t2));
	}
	{
		typedef bksge::tuple<int, double> T1;
		typedef bksge::tuple<double, long> T2;
		const T1 t1(1, 2);
		const T2 t2(1, 2);
		EXPECT_TRUE( (t1 == t2));
		EXPECT_TRUE(!(t1 != t2));
	}
	{
		typedef bksge::tuple<int, double> T1;
		typedef bksge::tuple<double, long> T2;
		const T1 t1(1, 2);
		const T2 t2(1, 3);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE( (t1 != t2));
	}
	{
		typedef bksge::tuple<int, double> T1;
		typedef bksge::tuple<double, long> T2;
		const T1 t1(1, 2);
		const T2 t2(1.1, 2);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE( (t1 != t2));
	}
	{
		typedef bksge::tuple<int, double> T1;
		typedef bksge::tuple<double, long> T2;
		const T1 t1(1, 2);
		const T2 t2(1.1, 3);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE( (t1 != t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1, 2, 3);
		EXPECT_TRUE( (t1 == t2));
		EXPECT_TRUE(!(t1 != t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1.1, 2, 3);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE( (t1 != t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1, 3, 3);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE(  t1 != t2);
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1, 2, 4);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE(  t1 != t2);
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1, 3, 2);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE( (t1 != t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1.1, 2, 2);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE( (t1 != t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1.1, 3, 3);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE( (t1 != t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1.1, 3, 2);
		EXPECT_TRUE(!(t1 == t2));
		EXPECT_TRUE( (t1 != t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		BKSGE_CXX14_CONSTEXPR T1 t1(1, 2, 3);
		BKSGE_CXX14_CONSTEXPR T2 t2(1.1, 3, 2);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!(t1 == t2));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE( (t1 != t2));
	}
}

GTEST_TEST(TupleTest, LtTest)
{
	{
		typedef bksge::tuple<> T1;
		typedef bksge::tuple<> T2;
		const T1 t1;
		const T2 t2;
		EXPECT_TRUE(!(t1 <  t2));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE(!(t1 >  t2));
		EXPECT_TRUE( (t1 >= t2));
	}
	{
		typedef bksge::tuple<long> T1;
		typedef bksge::tuple<double> T2;
		const T1 t1(1);
		const T2 t2(1);
		EXPECT_TRUE(!(t1 <  t2));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE(!(t1 >  t2));
		EXPECT_TRUE( (t1 >= t2));
	}
	{
		typedef bksge::tuple<long> T1;
		typedef bksge::tuple<double> T2;
		const T1 t1(1);
		const T2 t2(0.9);
		EXPECT_TRUE(!(t1 <  t2));
		EXPECT_TRUE(!(t1 <= t2));
		EXPECT_TRUE( (t1 >  t2));
		EXPECT_TRUE( (t1 >= t2));
	}
	{
		typedef bksge::tuple<long> T1;
		typedef bksge::tuple<double> T2;
		const T1 t1(1);
		const T2 t2(1.1);
		EXPECT_TRUE( (t1 <  t2));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE(!(t1 >  t2));
		EXPECT_TRUE(!(t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int> T1;
		typedef bksge::tuple<double, long> T2;
		const T1 t1(1, 2);
		const T2 t2(1, 2);
		EXPECT_TRUE(!(t1 <  t2));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE(!(t1 >  t2));
		EXPECT_TRUE( (t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int> T1;
		typedef bksge::tuple<double, long> T2;
		const T1 t1(1, 2);
		const T2 t2(0.9, 2);
		EXPECT_TRUE(!(t1 <  t2));
		EXPECT_TRUE(!(t1 <= t2));
		EXPECT_TRUE( (t1 >  t2));
		EXPECT_TRUE( (t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int> T1;
		typedef bksge::tuple<double, long> T2;
		const T1 t1(1, 2);
		const T2 t2(1.1, 2);
		EXPECT_TRUE( (t1 <  t2));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE(!(t1 >  t2));
		EXPECT_TRUE(!(t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int> T1;
		typedef bksge::tuple<double, long> T2;
		const T1 t1(1, 2);
		const T2 t2(1, 1);
		EXPECT_TRUE(!(t1 <  t2));
		EXPECT_TRUE(!(t1 <= t2));
		EXPECT_TRUE( (t1 >  t2));
		EXPECT_TRUE( (t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int> T1;
		typedef bksge::tuple<double, long> T2;
		const T1 t1(1, 2);
		const T2 t2(1, 3);
		EXPECT_TRUE( (t1 <  t2));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE(!(t1 >  t2));
		EXPECT_TRUE(!(t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1, 2, 3);
		EXPECT_TRUE(!(t1 <  t2));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE(!(t1 >  t2));
		EXPECT_TRUE( (t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(0.9, 2, 3);
		EXPECT_TRUE(!(t1 <  t2));
		EXPECT_TRUE(!(t1 <= t2));
		EXPECT_TRUE( (t1 >  t2));
		EXPECT_TRUE( (t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1.1, 2, 3);
		EXPECT_TRUE( (t1 <  t2));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE(!(t1 >  t2));
		EXPECT_TRUE(!(t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1, 1, 3);
		EXPECT_TRUE(!(t1 <  t2));
		EXPECT_TRUE(!(t1 <= t2));
		EXPECT_TRUE( (t1 >  t2));
		EXPECT_TRUE( (t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1, 3, 3);
		EXPECT_TRUE( (t1 <  t2));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE(!(t1 >  t2));
		EXPECT_TRUE(!(t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1, 2, 2);
		EXPECT_TRUE(!(t1 <  t2));
		EXPECT_TRUE(!(t1 <= t2));
		EXPECT_TRUE( (t1 >  t2));
		EXPECT_TRUE( (t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		const T1 t1(1, 2, 3);
		const T2 t2(1, 2, 4);
		EXPECT_TRUE( (t1 <  t2));
		EXPECT_TRUE( (t1 <= t2));
		EXPECT_TRUE(!(t1 >  t2));
		EXPECT_TRUE(!(t1 >= t2));
	}
	{
		typedef bksge::tuple<long, int, double> T1;
		typedef bksge::tuple<double, long, int> T2;
		BKSGE_CXX14_CONSTEXPR T1 t1(1, 2, 3);
		BKSGE_CXX14_CONSTEXPR T2 t2(1, 2, 4);
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE( (t1 <  t2));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE( (t1 <= t2));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!(t1 >  t2));
		BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(!(t1 >= t2));
	}
}

GTEST_TEST(TupleTest, SwapTest)
{
	{
		typedef bksge::tuple<> T;
		T t0;
		T t1;
		t0.swap(t1);
	}
	{
		typedef bksge::tuple<MoveOnly> T;
		T t0(MoveOnly(0));
		T t1(MoveOnly(1));
		t0.swap(t1);
		EXPECT_EQ(bksge::get<0>(t0), 1);
		EXPECT_EQ(bksge::get<0>(t1), 0);
	}
	{
		typedef bksge::tuple<MoveOnly, MoveOnly> T;
		T t0(MoveOnly(0), MoveOnly(1));
		T t1(MoveOnly(2), MoveOnly(3));
		t0.swap(t1);
		EXPECT_EQ(bksge::get<0>(t0), 2);
		EXPECT_EQ(bksge::get<1>(t0), 3);
		EXPECT_EQ(bksge::get<0>(t1), 0);
		EXPECT_EQ(bksge::get<1>(t1), 1);
	}
	{
		typedef bksge::tuple<MoveOnly, MoveOnly, MoveOnly> T;
		T t0(MoveOnly(0), MoveOnly(1), MoveOnly(2));
		T t1(MoveOnly(3), MoveOnly(4), MoveOnly(5));
		t0.swap(t1);
		EXPECT_EQ(bksge::get<0>(t0), 3);
		EXPECT_EQ(bksge::get<1>(t0), 4);
		EXPECT_EQ(bksge::get<2>(t0), 5);
		EXPECT_EQ(bksge::get<0>(t1), 0);
		EXPECT_EQ(bksge::get<1>(t1), 1);
		EXPECT_EQ(bksge::get<2>(t1), 2);
	}
	{
		typedef bksge::tuple<> T;
		T t0;
		T t1;
		swap(t0, t1);
	}
	{
		typedef bksge::tuple<MoveOnly> T;
		T t0(MoveOnly(0));
		T t1(MoveOnly(1));
		swap(t0, t1);
		EXPECT_EQ(bksge::get<0>(t0), 1);
		EXPECT_EQ(bksge::get<0>(t1), 0);
	}
	{
		typedef bksge::tuple<MoveOnly, MoveOnly> T;
		T t0(MoveOnly(0), MoveOnly(1));
		T t1(MoveOnly(2), MoveOnly(3));
		swap(t0, t1);
		EXPECT_EQ(bksge::get<0>(t0), 2);
		EXPECT_EQ(bksge::get<1>(t0), 3);
		EXPECT_EQ(bksge::get<0>(t1), 0);
		EXPECT_EQ(bksge::get<1>(t1), 1);
	}
	{
		typedef bksge::tuple<MoveOnly, MoveOnly, MoveOnly> T;
		T t0(MoveOnly(0), MoveOnly(1), MoveOnly(2));
		T t1(MoveOnly(3), MoveOnly(4), MoveOnly(5));
		swap(t0, t1);
		EXPECT_EQ(bksge::get<0>(t0), 3);
		EXPECT_EQ(bksge::get<1>(t0), 4);
		EXPECT_EQ(bksge::get<2>(t0), 5);
		EXPECT_EQ(bksge::get<0>(t1), 0);
		EXPECT_EQ(bksge::get<1>(t1), 1);
		EXPECT_EQ(bksge::get<2>(t1), 2);
	}
}

}	// namespace bksge_tuple_test
