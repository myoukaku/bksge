/**
 *	@file	unit_test_fnd_iterator_concepts_indirect_unary_predicate.cpp
 *
 *	@brief	indirect_unary_predicate のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirect_unary_predicate.hpp>
#include <bksge/fnd/config.hpp>
#include <iterator>
#include <vector>
#include <memory>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECT_UNARY_PREDICATE_TEST(B, ...)	\
	static_assert(B == bksge::indirect_unary_predicate<__VA_ARGS__>, " ")
#else
#  define BKSGE_INDIRECT_UNARY_PREDICATE_TEST(B, ...)	\
	static_assert(B == bksge::indirect_unary_predicate<__VA_ARGS__>::value, " ")
#endif

namespace bksge_iterator_test
{

namespace indirect_unary_predicate_test
{

struct Pred1
{
	bool operator()(int) const;
};
struct Pred2
{
	bool operator()(int, int) const;
	void operator()(int) const;
};
struct Pred3
{
	Pred3(Pred3 const&) = delete;
	bool operator()(int) const;
};

BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), int      *      );
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), int const*      );
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), int      * const);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), int const* const);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), float*);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), char*);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), void*);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int**);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int const);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int&);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int&&);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int const&);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int const&&);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int[]);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int), int[3]);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), std::unique_ptr<int>);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), std::shared_ptr<int>);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), std::vector<int>::iterator);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  bool(*)(int), std::vector<int>::const_iterator);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, void(*)(int), int*);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(), int*);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, bool(*)(int, int), int*);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(true,  Pred1, int*);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, Pred2, int*);
BKSGE_INDIRECT_UNARY_PREDICATE_TEST(false, Pred3, int*);

}	// namespace indirect_unary_predicate_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECT_UNARY_PREDICATE_TEST
