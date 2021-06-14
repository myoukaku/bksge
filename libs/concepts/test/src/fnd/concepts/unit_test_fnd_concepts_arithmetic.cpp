/**
 *	@file	unit_test_fnd_concepts_arithmetic.cpp
 *
 *	@brief	arithmetic のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_ARITHMETIC_TEST(B, T)	\
	static_assert(B == bksge::arithmetic<T>, "")
#else
#  define BKSGE_ARITHMETIC_TEST(B, T) \
	static_assert(B == bksge::arithmetic<T>::value, "")
#endif

#define BKSGE_ARITHMETIC_TEST_CV(B, T)			\
	BKSGE_ARITHMETIC_TEST(B,                T);	\
	BKSGE_ARITHMETIC_TEST(B, const          T);	\
	BKSGE_ARITHMETIC_TEST(B,       volatile T);	\
	BKSGE_ARITHMETIC_TEST(B, const volatile T)

namespace bksge_concepts_test
{

namespace arithmetic_test
{

// signed integer types
BKSGE_ARITHMETIC_TEST_CV(true,  signed char);
BKSGE_ARITHMETIC_TEST_CV(true,  signed short);
BKSGE_ARITHMETIC_TEST_CV(true,  signed int);
BKSGE_ARITHMETIC_TEST_CV(true,  signed long);
BKSGE_ARITHMETIC_TEST_CV(true,  signed long long);

// unsigned integer types
BKSGE_ARITHMETIC_TEST_CV(true,  unsigned char);
BKSGE_ARITHMETIC_TEST_CV(true,  unsigned short);
BKSGE_ARITHMETIC_TEST_CV(true,  unsigned int);
BKSGE_ARITHMETIC_TEST_CV(true,  unsigned long);
BKSGE_ARITHMETIC_TEST_CV(true,  unsigned long long);

// floating point types
BKSGE_ARITHMETIC_TEST_CV(true,  float);
BKSGE_ARITHMETIC_TEST_CV(true,  double);
BKSGE_ARITHMETIC_TEST_CV(true,  long double);

// other arithmetic types
BKSGE_ARITHMETIC_TEST_CV(true,  bool);
BKSGE_ARITHMETIC_TEST_CV(true,  char);
BKSGE_ARITHMETIC_TEST_CV(true,  wchar_t);
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
BKSGE_ARITHMETIC_TEST_CV(true,  char16_t);
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
BKSGE_ARITHMETIC_TEST_CV(true,  char32_t);
#endif
#if 0//defined(BKSGE_HAS_CXX20_CHAR8_T)
BKSGE_ARITHMETIC_TEST_CV(true,  char8_t);
#endif

// not arithmetic types
BKSGE_ARITHMETIC_TEST_CV(false, void);
BKSGE_ARITHMETIC_TEST_CV(false, int*);
BKSGE_ARITHMETIC_TEST_CV(false, int&);
BKSGE_ARITHMETIC_TEST_CV(false, int&&);
BKSGE_ARITHMETIC_TEST_CV(false, int[]);
BKSGE_ARITHMETIC_TEST_CV(false, int[2]);
BKSGE_ARITHMETIC_TEST(false, int());
BKSGE_ARITHMETIC_TEST(false, int(*)());
BKSGE_ARITHMETIC_TEST(false, int(&)());

enum E { };
BKSGE_ARITHMETIC_TEST_CV(false, E);
enum class CE { };
BKSGE_ARITHMETIC_TEST_CV(false, CE);
struct A { };
BKSGE_ARITHMETIC_TEST_CV(false, A);
union B { };
BKSGE_ARITHMETIC_TEST_CV(false, B);

}	// namespace arithmetic_test

}	// namespace bksge_concepts_test

#undef BKSGE_ARITHMETIC_TEST
#undef BKSGE_ARITHMETIC_TEST_CV
