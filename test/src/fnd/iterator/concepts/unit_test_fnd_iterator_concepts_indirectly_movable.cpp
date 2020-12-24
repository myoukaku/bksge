/**
 *	@file	unit_test_fnd_iterator_concepts_indirectly_movable.cpp
 *
 *	@brief	indirectly_movable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirectly_movable.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECTLY_MOVABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_movable<__VA_ARGS__>, "")
#else
#  define BKSGE_INDIRECTLY_MOVABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_movable<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace indirectly_movable_test
{

template <bool, bool>
struct CopyableMovable;

template <>
struct CopyableMovable<true, true>
{
	CopyableMovable(CopyableMovable const&);
	CopyableMovable& operator=(CopyableMovable const&);
	CopyableMovable(CopyableMovable&&);
	CopyableMovable& operator=(CopyableMovable&&);
};
template <>
struct CopyableMovable<true, false>
{
	CopyableMovable(CopyableMovable const&);
	CopyableMovable& operator=(CopyableMovable const&);
	CopyableMovable(CopyableMovable&&) = delete;
	CopyableMovable& operator=(CopyableMovable&&) = delete;
};
template <>
struct CopyableMovable<false, true>
{
	CopyableMovable(CopyableMovable const&) = delete;
	CopyableMovable& operator=(CopyableMovable const&) = delete;
	CopyableMovable(CopyableMovable&&);
	CopyableMovable& operator=(CopyableMovable&&);
};
template <>
struct CopyableMovable<false, false>
{
	CopyableMovable(CopyableMovable const&) = delete;
	CopyableMovable& operator=(CopyableMovable const&) = delete;
	CopyableMovable(CopyableMovable&&) = delete;
	CopyableMovable& operator=(CopyableMovable&&) = delete;
};

struct A1
{
	A1(A1&&);
	A1& operator=(A1&&);
};
struct A2
{
	A2(A2&&) = delete;
	A2& operator=(A2&&) = delete;
};
struct B1
{
	B1(A1 const&);
	B1(A2 const&);
};
struct B2
{
	B2& operator=(A1 const&);
	B2& operator=(A2 const&);
};
struct C1
{
	C1(A1&&);
	C1(A2&&);
};
struct C2
{
	C2& operator=(A1&&);
	C2& operator=(A2&&);
};

BKSGE_INDIRECTLY_MOVABLE_TEST(true,  int      *, int*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  int const*, int*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, int      *, int const*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, int const*, int const*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  int*, float*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  int*, char*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, int*, void*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  float*, int*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  char*, int*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, void*, int*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  int*, bksge::vector<int>::iterator);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, int*, bksge::vector<int>::const_iterator);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  bksge::vector<int>::iterator, int*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  bksge::vector<int>::iterator, bksge::vector<int>::iterator);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, bksge::vector<int>::iterator, bksge::vector<int>::const_iterator);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  bksge::vector<int>::const_iterator, int*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  bksge::vector<int>::const_iterator, bksge::vector<int>::iterator);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, bksge::vector<int>::const_iterator, bksge::vector<int>::const_iterator);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  CopyableMovable<true,  true >*, CopyableMovable<true,  true >*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<true,  false>*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<false, true >*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<false, false>*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<true,  true >*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<true,  false>*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<false, true >*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<false, false>*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<true,  true >*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<true,  false>*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  CopyableMovable<false, true >*, CopyableMovable<false, true >*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<false, false>*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<true,  true >*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<true,  false>*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<false, true >*);
BKSGE_INDIRECTLY_MOVABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<false, false>*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  A1*, B1*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  A2*, B1*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  A1*, B2*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  A2*, B2*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  A1*, C1*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  A2*, C1*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  A1*, C2*);
BKSGE_INDIRECTLY_MOVABLE_TEST(true,  A2*, C2*);

}	// namespace indirectly_movable_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECTLY_MOVABLE_TEST
