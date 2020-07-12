/**
 *	@file	unit_test_fnd_concepts_copy_constructible.cpp
 *
 *	@brief	copy_constructible のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/copy_constructible.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_COPY_CONSTRUCTIBLE_TEST(B, T)	\
	static_assert(B == bksge::copy_constructible<T>, " ");	\
	static_assert(B == bksge::copy_constructible_t<T>::value, " ")
#else
#  define BKSGE_COPY_CONSTRUCTIBLE_TEST(B, T)	\
	static_assert(B == bksge::copy_constructible_t<T>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace copy_constructible_test
{

BKSGE_COPY_CONSTRUCTIBLE_TEST(false, void);
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  void*);
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  const void*);
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  char);
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  const float);
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  int*);
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  int&);
BKSGE_COPY_CONSTRUCTIBLE_TEST(false, int&&);
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  const int&);
BKSGE_COPY_CONSTRUCTIBLE_TEST(false, int[]);
BKSGE_COPY_CONSTRUCTIBLE_TEST(false, int[2]);
BKSGE_COPY_CONSTRUCTIBLE_TEST(false, int());
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  int(*)());
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  int(&)());
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  int(&)() noexcept);

enum E { };
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  E);
enum class CE { };
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  CE);
struct A { };
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  A);
union B { };
BKSGE_COPY_CONSTRUCTIBLE_TEST(true,  B);

struct C
{
	C(void* = nullptr) { }
	~C() noexcept(false) { }
};
BKSGE_COPY_CONSTRUCTIBLE_TEST(false, C);

class D
{
public:
	D() { }
	D(int) { }
private:
	~D() { }
};
BKSGE_COPY_CONSTRUCTIBLE_TEST(false, D);

}	// namespace copy_constructible_test

}	// namespace bksge_concepts_test

#undef BKSGE_COPY_CONSTRUCTIBLE_TEST
