/**
 *	@file	unit_test_fnd_iterator_incrementable_traits.cpp
 *
 *	@brief	incrementable_traits のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/incrementable_traits.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace incrementable_traits_test
{

template <typename T>
struct have_difference 
{
	using difference_type = T;
};

struct can_difference
{
	friend auto operator-(can_difference const&, can_difference const&) -> char
	{
		return 0;
	}
};

GTEST_TEST(IteratorTest, IncrementableTraitsTest)
{
	using T = int;

	using vec_iterator = std::vector<T>::iterator;
	using vec_const_iterator = std::vector<T>::const_iterator;

	static_assert(bksge::is_same<bksge::incrementable_traits<T      *                   >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<T const*                   >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<T      * const             >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<T const* const             >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<T[3]                       >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<T const[3]                 >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<T[]                        >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<T const[]                  >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<vec_iterator               >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<vec_iterator const         >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<vec_const_iterator         >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<vec_const_iterator const   >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<std::vector<T>             >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<std::vector<T> const       >::difference_type, std::ptrdiff_t>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<have_difference <T      >      >::difference_type, T>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<have_difference <T const>      >::difference_type, T const>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<have_difference <T      > const>::difference_type, T>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<have_difference <T const> const>::difference_type, T const>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<can_difference      >::difference_type, signed char>::value, "");
	static_assert(bksge::is_same<bksge::incrementable_traits<can_difference const>::difference_type, signed char>::value, "");
}

}	// namespace incrementable_traits_test

}	// namespace bksge_iterator_test
