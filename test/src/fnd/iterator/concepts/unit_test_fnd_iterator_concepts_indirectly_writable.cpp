/**
 *	@file	unit_test_fnd_iterator_concepts_indirectly_writable.cpp
 *
 *	@brief	indirectly_writable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>	// istream_iterator, ostream_iterator
#include "iterator_test.hpp"

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECTLY_WRITABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_writable<__VA_ARGS__>, "")
#else
#  define BKSGE_INDIRECTLY_WRITABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_writable<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace indirectly_writable_test
{

BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int      *,                       int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, int const*,                       int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int      * const,                 int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, int const* const,                 int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, void*,                            int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  bksge::unique_ptr<int>,           int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  bksge::shared_ptr<int>,           int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, bksge::vector<int>,                 int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  bksge::vector<int>::iterator,       int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, bksge::vector<int>::const_iterator, int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, std::istream_iterator<int>,       int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  std::ostream_iterator<int>,       int);

BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int*, int const);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int*, float);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int*, bool);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, int*, void);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, int*, int*);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, int*, int[]);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, int*, int[2]);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int*, int&);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int*, int const&);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int*, int&&);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int*, int const&&);

BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int[],  int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  int[2], int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, int&,   int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, int&&,  int);

struct X
{
	int& operator*();
};
struct Y
{
	int operator*();
};

BKSGE_INDIRECTLY_WRITABLE_TEST(true,  X,        int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  X&,       int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, X const,  int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, X const&, int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, Y,        int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, Y&,       int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, Y const,  int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, Y const&, int);

BKSGE_INDIRECTLY_WRITABLE_TEST(false, weakly_incrementable_wrapper<int>,     int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, incrementable_wrapper<int>,            int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, indirectly_readable_wrapper<int>,      int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  indirectly_writable_wrapper<int>,      int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, input_or_output_iterator_wrapper<int>, int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  input_iterator_wrapper<int>,           int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  output_iterator_wrapper<int>,          int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  forward_iterator_wrapper<int>,         int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  bidirectional_iterator_wrapper<int>,   int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  random_access_iterator_wrapper<int>,   int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  contiguous_iterator_wrapper<int>,      int);

}	// namespace indirectly_writable_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECTLY_WRITABLE_TEST
