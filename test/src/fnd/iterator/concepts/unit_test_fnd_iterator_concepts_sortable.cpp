/**
 *	@file	unit_test_fnd_iterator_concepts_sortable.cpp
 *
 *	@brief	sortable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/sortable.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <string>
#include <vector>
#include <streambuf>
#include <memory>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_SORTABLE_TEST(B, ...)	\
	static_assert(B == bksge::sortable<__VA_ARGS__>, " ");	\
	static_assert(B == bksge::sortable_t<__VA_ARGS__>::value, " ")
#else
#  define BKSGE_SORTABLE_TEST(B, ...)	\
	static_assert(B == bksge::sortable_t<__VA_ARGS__>::value, " ")
#endif

namespace bksge_iterator_test
{

namespace sortable_test
{

BKSGE_SORTABLE_TEST(true,  int               *);
BKSGE_SORTABLE_TEST(false, int const         *);
BKSGE_SORTABLE_TEST(true,  int       volatile*);
BKSGE_SORTABLE_TEST(false, int const volatile*);
BKSGE_SORTABLE_TEST(false, int               * const);
BKSGE_SORTABLE_TEST(false, int const         * const);
BKSGE_SORTABLE_TEST(false, int       volatile* const);
BKSGE_SORTABLE_TEST(false, int const volatile* const);

BKSGE_SORTABLE_TEST(true,  int               **);
BKSGE_SORTABLE_TEST(true,  int const         **);
BKSGE_SORTABLE_TEST(true,  int       volatile**);
BKSGE_SORTABLE_TEST(true,  int const volatile**);
BKSGE_SORTABLE_TEST(false, int               ** const);
BKSGE_SORTABLE_TEST(false, int const         ** const);
BKSGE_SORTABLE_TEST(false, int       volatile** const);
BKSGE_SORTABLE_TEST(false, int const volatile** const);

BKSGE_SORTABLE_TEST(false, void               *);
BKSGE_SORTABLE_TEST(false, void const         *);
BKSGE_SORTABLE_TEST(false, void       volatile*);
BKSGE_SORTABLE_TEST(false, void const volatile*);
BKSGE_SORTABLE_TEST(false, void               * const);
BKSGE_SORTABLE_TEST(false, void const         * const);
BKSGE_SORTABLE_TEST(false, void       volatile* const);
BKSGE_SORTABLE_TEST(false, void const volatile* const);

BKSGE_SORTABLE_TEST(true,  void               **);
BKSGE_SORTABLE_TEST(true,  void const         **);
BKSGE_SORTABLE_TEST(true,  void       volatile**);
BKSGE_SORTABLE_TEST(true,  void const volatile**);
BKSGE_SORTABLE_TEST(false, void               ** const);
BKSGE_SORTABLE_TEST(false, void const         ** const);
BKSGE_SORTABLE_TEST(false, void       volatile** const);
BKSGE_SORTABLE_TEST(false, void const volatile** const);

BKSGE_SORTABLE_TEST(true,  std::array<int, 1>::iterator);
BKSGE_SORTABLE_TEST(false, std::array<int, 1>::const_iterator);
BKSGE_SORTABLE_TEST(true,  std::deque<int>::iterator);
BKSGE_SORTABLE_TEST(false, std::deque<int>::const_iterator);
BKSGE_SORTABLE_TEST(true,  std::forward_list<int>::iterator);
BKSGE_SORTABLE_TEST(false, std::forward_list<int>::const_iterator);
BKSGE_SORTABLE_TEST(true,  std::list<int>::iterator);
BKSGE_SORTABLE_TEST(false, std::list<int>::const_iterator);
BKSGE_SORTABLE_TEST(true,  std::string::iterator);
BKSGE_SORTABLE_TEST(false, std::string::const_iterator);
BKSGE_SORTABLE_TEST(false, bksge::string_view::iterator);
BKSGE_SORTABLE_TEST(false, bksge::string_view::const_iterator);
BKSGE_SORTABLE_TEST(true,  std::vector<int>::iterator);
BKSGE_SORTABLE_TEST(false, std::vector<int>::const_iterator);
BKSGE_SORTABLE_TEST(false, std::istreambuf_iterator<char>);
BKSGE_SORTABLE_TEST(false, std::ostreambuf_iterator<char>);
BKSGE_SORTABLE_TEST(false, std::shared_ptr<int>);
BKSGE_SORTABLE_TEST(false, std::unique_ptr<int>);

}	// namespace sortable_test

}	// namespace bksge_iterator_test

#undef BKSGE_SORTABLE_TEST
