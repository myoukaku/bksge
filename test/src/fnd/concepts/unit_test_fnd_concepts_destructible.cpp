/**
 *	@file	unit_test_fnd_concepts_destructible.cpp
 *
 *	@brief	destructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/destructible.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_DESTRUCTIBLE_TEST(B, T)	\
	static_assert(B == bksge::destructible<T>, " ");	\
	static_assert(B == bksge::destructible_t<T>::value, " ")
#else
#  define BKSGE_DESTRUCTIBLE_TEST(B, T) \
	static_assert(B == bksge::destructible_t<T>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace destructible_test
{

BKSGE_DESTRUCTIBLE_TEST(false, void);
BKSGE_DESTRUCTIBLE_TEST(true,  char);
BKSGE_DESTRUCTIBLE_TEST(true,  float);
BKSGE_DESTRUCTIBLE_TEST(true,  int*);
BKSGE_DESTRUCTIBLE_TEST(true,  int&);
BKSGE_DESTRUCTIBLE_TEST(true,  int&&);
BKSGE_DESTRUCTIBLE_TEST(true,  const int&);
BKSGE_DESTRUCTIBLE_TEST(false, int[]);
BKSGE_DESTRUCTIBLE_TEST(true,  int[2]);
BKSGE_DESTRUCTIBLE_TEST(false, int());
BKSGE_DESTRUCTIBLE_TEST(true,  int(*)());
BKSGE_DESTRUCTIBLE_TEST(true,  int(&)());

enum E { };
BKSGE_DESTRUCTIBLE_TEST(true,  E);
enum class CE { };
BKSGE_DESTRUCTIBLE_TEST(true,  CE);
struct A { };
BKSGE_DESTRUCTIBLE_TEST(true,  A);
union B { };
BKSGE_DESTRUCTIBLE_TEST(true,  B);

struct C
{
	~C() noexcept(false) { }
};
BKSGE_DESTRUCTIBLE_TEST(false, C);

class D
{
public:
	D() { }
private:
	~D() { }
};
BKSGE_DESTRUCTIBLE_TEST(false, D);

}	// namespace destructible_test

}	// namespace bksge_concepts_test

#undef BKSGE_DESTRUCTIBLE_TEST
