/**
 *	@file	unit_test_fnd_ranges_borrowed_range.cpp
 *
 *	@brief	ranges::borrowed_range のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/ranges/concepts/borrowed_range.hpp>
#include <bksge/fnd/ranges/concepts/enable_borrowed_range.hpp>
#include "ranges_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_RANGES_BORROWED_RANGE_TEST(B, ...)	\
	static_assert(B == bksge::ranges::borrowed_range<__VA_ARGS__>, "")
#else
#  define BKSGE_RANGES_BORROWED_RANGE_TEST(B, ...)	\
	static_assert(B == bksge::ranges::borrowed_range<__VA_ARGS__>::value, "")
#endif

namespace bksge_ranges_test
{

namespace borrowed_range_test
{

struct A {};
struct B {};

}	// namespace borrowed_range_test

}	// namespace bksge_ranges_test

BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, test_contiguous_range<bksge_ranges_test::borrowed_range_test::A>);
BKSGE_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, test_random_access_range<bksge_ranges_test::borrowed_range_test::B>);

BKSGE_RANGES_BORROWED_RANGE_TEST(false, int      [2]);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, int const[2]);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, int      []);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, int const[]);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  int      (&)[2]);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  int const(&)[2]);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, int      (&&)[2]);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, int const(&&)[2]);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, int      (*)[2]);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, int const(*)[2]);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, int      *);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, int const*);

BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_contiguous_range<bksge_ranges_test::borrowed_range_test::A>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_contiguous_range<bksge_ranges_test::borrowed_range_test::A>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_contiguous_range<bksge_ranges_test::borrowed_range_test::A>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_contiguous_range<bksge_ranges_test::borrowed_range_test::B>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_contiguous_range<bksge_ranges_test::borrowed_range_test::B>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_contiguous_range<bksge_ranges_test::borrowed_range_test::B>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_random_access_range<bksge_ranges_test::borrowed_range_test::A>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_random_access_range<bksge_ranges_test::borrowed_range_test::A>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_random_access_range<bksge_ranges_test::borrowed_range_test::A>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_random_access_range<bksge_ranges_test::borrowed_range_test::B>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_random_access_range<bksge_ranges_test::borrowed_range_test::B>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_random_access_range<bksge_ranges_test::borrowed_range_test::B>&&);

BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_contiguous_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_contiguous_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_contiguous_range<int>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_random_access_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_random_access_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_random_access_range<int>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_bidirectional_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_bidirectional_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_bidirectional_range<int>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_forward_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_forward_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_forward_range<int>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_input_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_input_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_input_range<int>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_output_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_output_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_output_range<int>&&);

BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_contiguous_sized_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_contiguous_sized_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_contiguous_sized_range<int>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_random_access_sized_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_random_access_sized_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_random_access_sized_range<int>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_bidirectional_sized_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_bidirectional_sized_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_bidirectional_sized_range<int>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_forward_sized_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_forward_sized_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_forward_sized_range<int>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_input_sized_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_input_sized_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_input_sized_range<int>&&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_output_sized_range<int>);
BKSGE_RANGES_BORROWED_RANGE_TEST(true,  test_output_sized_range<int>&);
BKSGE_RANGES_BORROWED_RANGE_TEST(false, test_output_sized_range<int>&&);

#undef BKSGE_RANGES_BORROWED_RANGE_TEST
