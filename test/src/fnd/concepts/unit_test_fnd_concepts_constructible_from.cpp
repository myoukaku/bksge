/**
 *	@file	unit_test_fnd_concepts_constructible_from.cpp
 *
 *	@brief	constructible_from のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/constructible_from.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_CONSTRUCTIBLE_FROM_TEST(B, ...)	\
	static_assert(B == bksge::constructible_from<__VA_ARGS__>, " ");	\
	static_assert(B == bksge::constructible_from_t<__VA_ARGS__>::value, " ")
#else
#  define BKSGE_CONSTRUCTIBLE_FROM_TEST(B, ...)	\
	static_assert(B == bksge::constructible_from_t<__VA_ARGS__>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace constructible_from_test
{

BKSGE_CONSTRUCTIBLE_FROM_TEST(false, void);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, void, void);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  void*, int*);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, void*, const int*);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  const void*, const int*);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  char);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  float);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  float, float);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  float, double);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  int*);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  int*, int*);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, int&);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  int&, int&);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, int&&);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  int&&, int);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, const int&);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  const int&, int);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  const int&, int&);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  const int&, const int);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  const int&, const int&);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, const int&, int, int);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, int[]);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  int[2]);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, int());
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  int(*)());
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  int(*)(), std::nullptr_t);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  int(*)(), int(*)() noexcept);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  int(*)(), int(&)() noexcept);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, int(&)());
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  int(&)(), int(&)() noexcept);

enum E { };
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  E);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  E, E&);
enum class CE { };
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  CE);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  CE, CE&);
struct A { };
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  A);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  A, A);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  A, A&);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  A, const A&);
union B { };
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  B);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  B, B);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  B, B&);
BKSGE_CONSTRUCTIBLE_FROM_TEST(true,  B, const B&);

struct C
{
	C(void* = nullptr) { }
	~C() noexcept(false) { }
};
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, C);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, C, void*);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, C, std::nullptr_t);

class D
{
public:
	D() { }
	D(int) { }
private:
	~D() { }
};
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, D);
BKSGE_CONSTRUCTIBLE_FROM_TEST(false, D, int);

}	// namespace constructible_from_test

}	// namespace bksge_concepts_test

#undef BKSGE_CONSTRUCTIBLE_FROM_TEST
