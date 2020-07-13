/**
 *	@file	unit_test_fnd_iterator_concepts_indirectly_writable.cpp
 *
 *	@brief	indirectly_writable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirectly_writable.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <memory>
#include <vector>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECTLY_WRITABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_writable<__VA_ARGS__>, " ");	\
	static_assert(B == bksge::indirectly_writable_t<__VA_ARGS__>::value, " ")
#else
#  define BKSGE_INDIRECTLY_WRITABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_writable_t<__VA_ARGS__>::value, " ")
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
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  std::unique_ptr<int>,             int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  std::shared_ptr<int>,             int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, std::vector<int>,                 int);
BKSGE_INDIRECTLY_WRITABLE_TEST(true,  std::vector<int>::iterator,       int);
BKSGE_INDIRECTLY_WRITABLE_TEST(false, std::vector<int>::const_iterator, int);
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

}	// namespace indirectly_writable_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECTLY_WRITABLE_TEST
