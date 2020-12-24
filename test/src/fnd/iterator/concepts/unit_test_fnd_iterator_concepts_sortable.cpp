/**
 *	@file	unit_test_fnd_iterator_concepts_sortable.cpp
 *
 *	@brief	sortable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/sortable.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/string_view.hpp>
#include <bksge/fnd/deque.hpp>
#include <bksge/fnd/forward_list.hpp>
#include <bksge/fnd/list.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <array>
#include <streambuf>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_SORTABLE_TEST(B, ...)	\
	static_assert(B == bksge::sortable<__VA_ARGS__>, "")
#else
#  define BKSGE_SORTABLE_TEST(B, ...)	\
	static_assert(B == bksge::sortable<__VA_ARGS__>::value, "")
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
BKSGE_SORTABLE_TEST(true,  bksge::deque<int>::iterator);
BKSGE_SORTABLE_TEST(false, bksge::deque<int>::const_iterator);
BKSGE_SORTABLE_TEST(true,  bksge::forward_list<int>::iterator);
BKSGE_SORTABLE_TEST(false, bksge::forward_list<int>::const_iterator);
BKSGE_SORTABLE_TEST(true,  bksge::list<int>::iterator);
BKSGE_SORTABLE_TEST(false, bksge::list<int>::const_iterator);
BKSGE_SORTABLE_TEST(true,  bksge::string::iterator);
BKSGE_SORTABLE_TEST(false, bksge::string::const_iterator);
BKSGE_SORTABLE_TEST(false, bksge::string_view::iterator);
BKSGE_SORTABLE_TEST(false, bksge::string_view::const_iterator);
BKSGE_SORTABLE_TEST(true,  bksge::vector<int>::iterator);
BKSGE_SORTABLE_TEST(false, bksge::vector<int>::const_iterator);
BKSGE_SORTABLE_TEST(false, std::istreambuf_iterator<char>);
BKSGE_SORTABLE_TEST(false, std::ostreambuf_iterator<char>);
BKSGE_SORTABLE_TEST(false, bksge::shared_ptr<int>);
BKSGE_SORTABLE_TEST(false, bksge::unique_ptr<int>);

}	// namespace sortable_test

}	// namespace bksge_iterator_test

#undef BKSGE_SORTABLE_TEST
