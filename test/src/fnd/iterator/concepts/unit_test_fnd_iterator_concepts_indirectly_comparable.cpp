/**
 *	@file	unit_test_fnd_iterator_concepts_indirectly_comparable.cpp
 *
 *	@brief	indirectly_comparable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirectly_comparable.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <vector>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECTLY_COMPARABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_comparable<__VA_ARGS__>, "")
#else
#  define BKSGE_INDIRECTLY_COMPARABLE_TEST(B, ...)	\
	static_assert(B == bksge::indirectly_comparable<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace indirectly_comparable_test
{

struct Pred1
{
	bool operator()(int, int) const;
};
struct Pred2
{
	bool operator()(int) const;
	void operator()(int, int) const;
};
struct Pred3
{
	Pred3(Pred3 const&) = delete;
	bool operator()(int, int) const;
};

BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int      *, int      *,                 bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int const*, int      *,                 bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int      *, int const*,                 bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int const*, int const*,                 bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int*, float*,                           bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int*, char*,                            bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(false, int*, void*,                            bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(false, int*, int**,                            bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(false, int*, int,                              bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(false, int*, int&,                             bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(false, int*, int&&,                            bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(false, int*, int[],                            bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(false, int*, int[2],                           bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int*, bksge::unique_ptr<int>,           bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int*, bksge::shared_ptr<int>,           bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int*, std::vector<int>::iterator,       bool(*)(int, int));
BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int*, std::vector<int>::const_iterator, bool(*)(int, int));

BKSGE_INDIRECTLY_COMPARABLE_TEST(true,  int*, int*, Pred1);
BKSGE_INDIRECTLY_COMPARABLE_TEST(false, int*, int*, Pred2);
BKSGE_INDIRECTLY_COMPARABLE_TEST(false, int*, int*, Pred3);

}	// namespace indirectly_comparable_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECTLY_COMPARABLE_TEST
