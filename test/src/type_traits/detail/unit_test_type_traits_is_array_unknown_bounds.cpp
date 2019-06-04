/**
 *	@file	unit_test_type_traits_is_array_unknown_bounds.cpp
 *
 *	@brief	is_array_unknown_bounds のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/type_traits/detail/is_array_unknown_bounds.hpp>
#include <gtest/gtest.h>

namespace bksge_type_traits_test
{

namespace is_array_unknown_bounds_test
{

#define BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(b, T)	\
	static_assert(bksge::detail::is_array_unknown_bounds<T>::value == b, #T)

GTEST_TEST(TypeTraitsTest, IsArrayUnknownBoundsTest)
{
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false,                int);
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, const          int);
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false,       volatile int);
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, const volatile int);
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, int*);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, int* const);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, int* volatile);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, int* const volatile);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, int**);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(true,                 int[]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(true,  const          int[]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(true,        volatile int[]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(true,  const volatile int[]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false,                int[2]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, const          int[2]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false,       volatile int[2]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, const volatile int[2]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false,                int[2][3]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, const          int[2][3]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false,       volatile int[2][3]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, const volatile int[2][3]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, int(*)[2]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, int(&)[2]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, int(&&)[2]);	
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, int&);		
	BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST(false, int&&);
}

#undef BKSGE_IS_ARRAY_UNKNOWN_BOUNDS_TEST

}	// namespace is_array_unknown_bounds_test

}	// namespace bksge_type_traits_test
