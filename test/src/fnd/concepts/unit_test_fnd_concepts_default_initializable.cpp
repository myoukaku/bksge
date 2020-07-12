/**
 *	@file	unit_test_fnd_concepts_default_initializable.cpp
 *
 *	@brief	default_initializable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/default_initializable.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_DEFAULT_INITIALIZABLE_TEST(B, T)	\
	static_assert(B == bksge::default_initializable<T>, "default_initializable");	\
	static_assert(B == bksge::default_initializable_t<T>::value, "default_initializable_t")
#else
#  define BKSGE_DEFAULT_INITIALIZABLE_TEST(B, T)	\
	static_assert(B == bksge::default_initializable_t<T>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace default_initializable_test
{

BKSGE_DEFAULT_INITIALIZABLE_TEST(false, void);
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  void*);
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  const void*);
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  char);
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  float);
//BKSGE_DEFAULT_INITIALIZABLE_TEST(false, const int);	// TODO
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  int*);
BKSGE_DEFAULT_INITIALIZABLE_TEST(false, int&);
BKSGE_DEFAULT_INITIALIZABLE_TEST(false, int&&);
BKSGE_DEFAULT_INITIALIZABLE_TEST(false, const int&);
BKSGE_DEFAULT_INITIALIZABLE_TEST(false, int[]);
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  int[2]);
BKSGE_DEFAULT_INITIALIZABLE_TEST(false, int());
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  int(*)());
BKSGE_DEFAULT_INITIALIZABLE_TEST(false, int(&)());

enum E { };
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  E);
enum class CE { };
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  CE);
struct A { };
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  A);
union B { };
BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  B);

struct C
{
	C(void* = nullptr) { }
	~C() noexcept(false) { }
};
BKSGE_DEFAULT_INITIALIZABLE_TEST(false, C);

class D
{
public:
	D() { }
	D(int) { }
private:
	~D() { }
};
BKSGE_DEFAULT_INITIALIZABLE_TEST(false, D);

#if 0	// TODO

struct S0 { explicit S0() = default; };
struct S1 { S0 x; };

BKSGE_DEFAULT_INITIALIZABLE_TEST(true,  S0);
BKSGE_DEFAULT_INITIALIZABLE_TEST(false, S1);

#endif

}	// namespace default_initializable_test

}	// namespace bksge_concepts_test

#undef BKSGE_DEFAULT_INITIALIZABLE_TEST
