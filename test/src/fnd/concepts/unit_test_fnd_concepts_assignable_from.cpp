/**
 *	@file	unit_test_fnd_concepts_assignable_from.cpp
 *
 *	@brief	assignable_from のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/assignable_from.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_ASSIGNABLE_FROM_TEST(B, T1, T2)	\
	static_assert(B == bksge::assignable_from<T1, T2>, "")
#else
#  define BKSGE_ASSIGNABLE_FROM_TEST(B, T1, T2)	\
	static_assert(B == bksge::assignable_from<T1, T2>::value, "")
#endif

namespace bksge_concepts_test
{

namespace assignable_from_test
{

BKSGE_ASSIGNABLE_FROM_TEST(false, void, void);
BKSGE_ASSIGNABLE_FROM_TEST(false, void*, int*);
BKSGE_ASSIGNABLE_FROM_TEST(true,  void*&, int*);
BKSGE_ASSIGNABLE_FROM_TEST(false, void*&, const int*);
BKSGE_ASSIGNABLE_FROM_TEST(true,  const void*&, const int*);
BKSGE_ASSIGNABLE_FROM_TEST(false, char, char);
BKSGE_ASSIGNABLE_FROM_TEST(true,  char&, char);
BKSGE_ASSIGNABLE_FROM_TEST(false, float, float);
BKSGE_ASSIGNABLE_FROM_TEST(true,  float&, double);
BKSGE_ASSIGNABLE_FROM_TEST(true,  int*&, int*);
BKSGE_ASSIGNABLE_FROM_TEST(true,  int&, int&);
BKSGE_ASSIGNABLE_FROM_TEST(true,  int&, int&&);
BKSGE_ASSIGNABLE_FROM_TEST(false, int&&, int);
BKSGE_ASSIGNABLE_FROM_TEST(false, const int&, int);
BKSGE_ASSIGNABLE_FROM_TEST(false, const int&, int&);
BKSGE_ASSIGNABLE_FROM_TEST(false, const int&, const int);
BKSGE_ASSIGNABLE_FROM_TEST(false, const int&, const int&);
BKSGE_ASSIGNABLE_FROM_TEST(false, int(&)[], int(&)[]);
BKSGE_ASSIGNABLE_FROM_TEST(false, int(&)[], int);
BKSGE_ASSIGNABLE_FROM_TEST(false, int(&)[2], int(&)[2]);
BKSGE_ASSIGNABLE_FROM_TEST(false, int(), int());
BKSGE_ASSIGNABLE_FROM_TEST(false, int(*)(), int(*)());
BKSGE_ASSIGNABLE_FROM_TEST(true,  int(*&)(), int(*)());
BKSGE_ASSIGNABLE_FROM_TEST(true,  int(*&)(), std::nullptr_t);
BKSGE_ASSIGNABLE_FROM_TEST(true,  int(*&)(), int(*)() noexcept);
BKSGE_ASSIGNABLE_FROM_TEST(true,  int(*&)(), int(&)() noexcept);
BKSGE_ASSIGNABLE_FROM_TEST(false, int(&)(), std::nullptr_t);
BKSGE_ASSIGNABLE_FROM_TEST(false, int(&)(), int(&)() noexcept);

enum E { };
BKSGE_ASSIGNABLE_FROM_TEST(false, E, E);
BKSGE_ASSIGNABLE_FROM_TEST(true,  E&, E);
BKSGE_ASSIGNABLE_FROM_TEST(true,  E&, E&);
BKSGE_ASSIGNABLE_FROM_TEST(true,  E&, const E&);
BKSGE_ASSIGNABLE_FROM_TEST(false, const E&, const E&);
enum class CE { };
BKSGE_ASSIGNABLE_FROM_TEST(false, CE, CE);
BKSGE_ASSIGNABLE_FROM_TEST(true,  CE&, CE&);
BKSGE_ASSIGNABLE_FROM_TEST(true,  CE&, const CE&);
BKSGE_ASSIGNABLE_FROM_TEST(false, const CE&, const CE&);
struct A { };
BKSGE_ASSIGNABLE_FROM_TEST(false, A, A);
BKSGE_ASSIGNABLE_FROM_TEST(true,  A&, A);
BKSGE_ASSIGNABLE_FROM_TEST(false, A, A&);
BKSGE_ASSIGNABLE_FROM_TEST(true,  A&, const A&);
union B { };
BKSGE_ASSIGNABLE_FROM_TEST(false, B, B);
BKSGE_ASSIGNABLE_FROM_TEST(true,  B&, B);
BKSGE_ASSIGNABLE_FROM_TEST(false, B, B&);
BKSGE_ASSIGNABLE_FROM_TEST(true,  B&, const B&);

struct C
{
	C(int) { }
	C(const C&) { }
	C& operator=(const C&) { return *this; }
	C& operator=(int) { return *this; }
	void operator=(void*) { }
};
BKSGE_ASSIGNABLE_FROM_TEST(true,  C&, C);
BKSGE_ASSIGNABLE_FROM_TEST(true,  C&, const C&);
BKSGE_ASSIGNABLE_FROM_TEST(true,  C&, int);
BKSGE_ASSIGNABLE_FROM_TEST(false, C&, void*);
BKSGE_ASSIGNABLE_FROM_TEST(false, C&, std::nullptr_t);

}	// namespace assignable_from_test

}	// namespace bksge_concepts_test

#undef BKSGE_ASSIGNABLE_FROM_TEST
