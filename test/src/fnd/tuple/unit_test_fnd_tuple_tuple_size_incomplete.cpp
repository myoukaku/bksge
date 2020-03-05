/**
 *	@file	unit_test_fnd_tuple_tuple_size_incomplete.cpp
 *
 *	@brief	tuple_size のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/type_traits/integral_constant.hpp>
#include <bksge/fnd/pair.hpp>
//#include <bksge/fnd/array.hpp>
#include <gtest/gtest.h>

namespace bksge_tuple_size_incomplete_test
{

template <typename T, size_t Size = sizeof(bksge::tuple_size<T>)>
constexpr bool is_complete(int) { static_assert(Size > 0, ""); return true; }
template <typename> constexpr bool is_complete(long) { return false; }
template <typename T> constexpr bool is_complete() { return is_complete<T>(0); }

struct Dummy1 {};
struct Dummy2 {};

}

namespace std
{

template <>
class tuple_size<bksge_tuple_size_incomplete_test::Dummy1>
	: public bksge::integral_constant<size_t, 0>
{};

}	// namespace std

namespace bksge_tuple_size_incomplete_test
{

template <typename T>
void test_complete()
{
	static_assert(is_complete<T>(), "");
	static_assert(is_complete<const T>(), "");
	static_assert(is_complete<volatile T>(), "");
	static_assert(is_complete<const volatile T>(), "");
}

template <typename T>
void test_incomplete()
{
	static_assert(!is_complete<T>(), "");
	//static_assert(!is_complete<const T>(), "");
	//static_assert(!is_complete<volatile T>(), "");
	//static_assert(!is_complete<const volatile T>(), "");
}

GTEST_TEST(TupleTest, TupleSizeIncompleteTest)
{
	test_complete<bksge::tuple<>>();
	test_complete<bksge::tuple<int&>>();
	test_complete<bksge::tuple<int&&, int&, void*>>();
	test_complete<bksge::pair<int, long>>();
	//test_complete<bksge::array<int, 5>>();
	test_complete<Dummy1>();

	test_incomplete<void>();
	test_incomplete<int>();
	test_incomplete<bksge::tuple<int>&>();
	test_incomplete<Dummy2>();
}

}	// namespace bksge_tuple_size_incomplete_test
