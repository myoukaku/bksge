/**
 *	@file	unit_test_fnd_iterator_concepts_indirectly_swappable.cpp
 *
 *	@brief	indirectly_swappable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirectly_swappable.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <vector>
#include <memory>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECTLY_SWAPPABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_swappable<__VA_ARGS__>, "")
#else
#  define BKSGE_INDIRECTLY_SWAPPABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_swappable<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace indirectly_swappable_test
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

BKSGE_INDIRECTLY_SWAPPABLE_TEST(true,  int      *, int*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, int const*, int*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, int      *, int const*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, int const*, int const*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(true,  int*, float*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(true,  int*, char*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, int*, int);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, int*, int&);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, int*, int&&);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, int*, int[]);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, int*, int[2]);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, int*, void*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(true,  int*, std::unique_ptr<int>);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(true,  int*, std::shared_ptr<int>);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(true,  std::vector<int>::iterator,       int*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(true,  std::vector<int>::iterator,       std::vector<int>::iterator);
//BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, std::vector<int>::iterator,       std::vector<int>::const_iterator);
//BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, std::vector<int>::const_iterator, int*);
//BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, std::vector<int>::const_iterator, std::vector<int>::iterator);
//BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, std::vector<int>::const_iterator, std::vector<int>::const_iterator);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(true,  CopyableMovable<true,  true >*, CopyableMovable<true,  true >*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<true,  false>*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<false, true >*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  true >*, CopyableMovable<false, false>*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<true,  true >*);
//BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<true,  false>*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<false, true >*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<true,  false>*, CopyableMovable<false, false>*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<true,  true >*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<true,  false>*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(true,  CopyableMovable<false, true >*, CopyableMovable<false, true >*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, true >*, CopyableMovable<false, false>*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<true,  true >*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<true,  false>*);
BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<false, true >*);
//BKSGE_INDIRECTLY_SWAPPABLE_TEST(false, CopyableMovable<false, false>*, CopyableMovable<false, false>*);

}	// namespace indirectly_swappable_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECTLY_SWAPPABLE_TEST
