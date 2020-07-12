/**
 *	@file	unit_test_fnd_concepts_move_constructible.cpp
 *
 *	@brief	move_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/move_constructible.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_MOVE_CONSTRUCTIBLE_TEST(B, T)	\
	static_assert(B == bksge::move_constructible<T>, " ");	\
	static_assert(B == bksge::move_constructible_t<T>::value, " ")
#else
#  define BKSGE_MOVE_CONSTRUCTIBLE_TEST(B, T)	\
	static_assert(B == bksge::move_constructible_t<T>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace move_constructible_test
{

BKSGE_MOVE_CONSTRUCTIBLE_TEST(false, void);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  void*);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  const void*);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  char);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  const float);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  int*);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  int&);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  int&&);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  const int&);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(false, int[]);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(false, int[2]);
BKSGE_MOVE_CONSTRUCTIBLE_TEST(false, int());
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  int(*)());
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)());
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)() noexcept);

enum E { };
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  E);
enum class CE { };
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  CE);
struct A { };
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  A);
union B { };
BKSGE_MOVE_CONSTRUCTIBLE_TEST(true,  B);

struct C
{
	C(void* = nullptr) { }
	~C() noexcept(false) { }
};
BKSGE_MOVE_CONSTRUCTIBLE_TEST(false, C);

class D
{
public:
	D() { }
	D(int) { }
private:
	~D() { }
};
BKSGE_MOVE_CONSTRUCTIBLE_TEST(false, D);

}	// namespace move_constructible_test

}	// namespace bksge_concepts_test

#undef BKSGE_MOVE_CONSTRUCTIBLE_TEST
