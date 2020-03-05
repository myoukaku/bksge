/**
 *	@file	unit_test_fnd_tuple_uses_allocator.cpp
 *
 *	@brief	uses_allocator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <gtest/gtest.h>

namespace bksge_tuple_test
{

namespace uses_allocator_test
{

struct A {};

GTEST_TEST(TupleTest, UsesAllocatorTest)
{
	{
		typedef bksge::tuple<> T;
//		static_assert((bksge::is_base_of<bksge::true_type, std::uses_allocator<T, A>>::value), "");
		static_assert(std::uses_allocator<T, A>::value == true, "");
	}
	{
		typedef bksge::tuple<int> T;
//		static_assert((bksge::is_base_of<bksge::true_type, std::uses_allocator<T, A>>::value), "");
		static_assert(std::uses_allocator<T, A>::value == true, "");
	}
	{
		typedef bksge::tuple<char, int> T;
//		static_assert((bksge::is_base_of<bksge::true_type, std::uses_allocator<T, A>>::value), "");
		static_assert(std::uses_allocator<T, A>::value == true, "");
	}
	{
		typedef bksge::tuple<double&, char, int> T;
//		static_assert((bksge::is_base_of<bksge::true_type, std::uses_allocator<T, A>>::value), "");
		static_assert(std::uses_allocator<T, A>::value == true, "");
	}
}

}	// namespace uses_allocator_test

}	// namespace bksge_tuple_test
