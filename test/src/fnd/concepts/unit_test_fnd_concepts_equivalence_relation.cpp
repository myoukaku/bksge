/**
 *	@file	unit_test_fnd_concepts_equivalence_relation.cpp
 *
 *	@brief	equivalence_relation のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/equivalence_relation.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_EQUIVALENCE_RELATION_TEST(B, ...)	\
	static_assert(B == bksge::equivalence_relation<__VA_ARGS__>, " ");	\
	static_assert(B == bksge::equivalence_relation_t<__VA_ARGS__>::value, " ")
#else
#  define BKSGE_EQUIVALENCE_RELATION_TEST(B, ...)	\
	static_assert(B == bksge::equivalence_relation_t<__VA_ARGS__>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace equivalence_relation_test
{

struct F
{
	void operator()(long, long) const;
	bool& operator()(int, const int&) const;
};

BKSGE_EQUIVALENCE_RELATION_TEST(true,  bool(*)(int, int), short, long);
BKSGE_EQUIVALENCE_RELATION_TEST(false, F, long, long);
BKSGE_EQUIVALENCE_RELATION_TEST(true,  const F&, const int, const int);

}	// namespace equivalence_relation_test

}	// namespace bksge_concepts_test

#undef BKSGE_EQUIVALENCE_RELATION_TEST
