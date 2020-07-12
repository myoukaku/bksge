/**
 *	@file	unit_test_fnd_concepts_semiregular.cpp
 *
 *	@brief	semiregular のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/semiregular.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_SEMIREGULAR_TEST(B, T)	\
	static_assert(B == bksge::semiregular<T>, " ");	\
	static_assert(B == bksge::semiregular_t<T>::value, " ")
#else
#  define BKSGE_SEMIREGULAR_TEST(B, T)	\
	static_assert(B == bksge::semiregular_t<T>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace semiregular_test
{

BKSGE_SEMIREGULAR_TEST(true,  int);
BKSGE_SEMIREGULAR_TEST(true,  int*);
BKSGE_SEMIREGULAR_TEST(false, int&);
BKSGE_SEMIREGULAR_TEST(false, void);
BKSGE_SEMIREGULAR_TEST(false, void());
BKSGE_SEMIREGULAR_TEST(false, void() noexcept);
BKSGE_SEMIREGULAR_TEST(false, void() const);

struct Trivial { };
BKSGE_SEMIREGULAR_TEST(true,  Trivial);

struct NotTrivial
{
	NotTrivial() { }
	~NotTrivial() { }
};
BKSGE_SEMIREGULAR_TEST(true,  NotTrivial);

struct NotDefaultConstructible
{
	NotDefaultConstructible(int) { }
};
BKSGE_SEMIREGULAR_TEST(false, NotDefaultConstructible);

struct HasReference
{
	int& ref;
};
BKSGE_SEMIREGULAR_TEST(false, HasReference);

}	// namespace semiregular_test

}	// namespace bksge_concepts_test

#undef BKSGE_SEMIREGULAR_TEST
