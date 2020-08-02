/**
 *	@file	unit_test_fnd_iterator_concepts_indirect_equivalence_relation.cpp
 *
 *	@brief	indirect_equivalence_relation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/concepts/indirect_equivalence_relation.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST(B, ...)	\
	static_assert(B == bksge::indirect_equivalence_relation<__VA_ARGS__>, "")
#else
#  define BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST(B, ...)	\
	static_assert(B == bksge::indirect_equivalence_relation<__VA_ARGS__>::value, "")
#endif

namespace bksge_iterator_test
{

namespace indirect_equivalence_relation_test
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

BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST(true,  bool(*)(int, int), int*, int*);
BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST(false, bool(*)(int, int), int, int);
BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST(false, void(*)(int, int), int*, int*);
BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST(false, void(*)(int, int), int, int);
BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST(true,  bool(*)(int, int), short*, char*);
BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST(true,  Pred1, int*, int*);
BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST(false, Pred2, int*, int*);
BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST(false, Pred3, int*, int*);

}	// namespace indirect_equivalence_relation_test

}	// namespace bksge_iterator_test

#undef BKSGE_INDIRECT_EQUIVALENCE_RELATION_TEST
