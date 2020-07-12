/**
 *	@file	unit_test_fnd_concepts_regular.cpp
 *
 *	@brief	regular のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/regular.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_REGULAR_TEST(B, T)	\
	static_assert(B == bksge::regular<T>, " ");	\
	static_assert(B == bksge::regular_t<T>::value, " ")
#else
#  define BKSGE_REGULAR_TEST(B, T)	\
	static_assert(B == bksge::regular_t<T>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace regular_test
{

BKSGE_REGULAR_TEST(true,  int);
BKSGE_REGULAR_TEST(true,  int*);
BKSGE_REGULAR_TEST(false, int&);
BKSGE_REGULAR_TEST(false, void);
BKSGE_REGULAR_TEST(false, void());
BKSGE_REGULAR_TEST(false, void() noexcept);
BKSGE_REGULAR_TEST(false, void() const);

struct Trivial { };
BKSGE_REGULAR_TEST(false, Trivial);

struct NotTrivial
{
	NotTrivial() { }
	~NotTrivial() { }
};
BKSGE_REGULAR_TEST(false, NotTrivial);

struct NotDefaultConstructible
{
	NotDefaultConstructible(int) { }
};
BKSGE_REGULAR_TEST(false, NotDefaultConstructible);

struct HasReference
{
	int& ref;
};
BKSGE_REGULAR_TEST(false, HasReference);

struct HasEq { };
bool operator==(HasEq, HasEq) { return true; }
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
BKSGE_REGULAR_TEST(true,  HasEq);
#else
BKSGE_REGULAR_TEST(false, HasEq);
#endif

struct HasEqNeq { };
bool operator==(HasEqNeq, HasEqNeq) { return true; }
bool operator!=(HasEqNeq, HasEqNeq) { return false; }
BKSGE_REGULAR_TEST(true,  HasEqNeq);

}	// namespace regular_test

}	// namespace bksge_concepts_test

#undef BKSGE_REGULAR_TEST
