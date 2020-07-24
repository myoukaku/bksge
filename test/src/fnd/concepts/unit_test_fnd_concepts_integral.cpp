/**
 *	@file	unit_test_fnd_concepts_integral.cpp
 *
 *	@brief	integral のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/integral.hpp>
#include <bksge/fnd/config.hpp>

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_INTEGRAL_TEST(B, T)	\
	static_assert(B == bksge::integral<T>, " ");	\
	static_assert(B == bksge::integral_t<T>::value, " ")
#else
#  define BKSGE_INTEGRAL_TEST(B, T) \
	static_assert(B == bksge::integral_t<T>::value, " ")
#endif

namespace bksge_concepts_test
{

namespace integral_test
{

// signed integer types
BKSGE_INTEGRAL_TEST(true,  signed char);
BKSGE_INTEGRAL_TEST(true,  signed short);
BKSGE_INTEGRAL_TEST(true,  signed int);
BKSGE_INTEGRAL_TEST(true,  signed long);
BKSGE_INTEGRAL_TEST(true,  signed long long);

// unsigned integer types
BKSGE_INTEGRAL_TEST(true,  unsigned char);
BKSGE_INTEGRAL_TEST(true,  unsigned short);
BKSGE_INTEGRAL_TEST(true,  unsigned int);
BKSGE_INTEGRAL_TEST(true,  unsigned long);
BKSGE_INTEGRAL_TEST(true,  unsigned long long);

// other integral types
BKSGE_INTEGRAL_TEST(true,  bool);
BKSGE_INTEGRAL_TEST(true,  char);
BKSGE_INTEGRAL_TEST(true,  wchar_t);
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
BKSGE_INTEGRAL_TEST(true,  char16_t);
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
BKSGE_INTEGRAL_TEST(true,  char32_t);
#endif
#if 0//defined(BKSGE_HAS_CXX20_CHAR8_T)
BKSGE_INTEGRAL_TEST(true,  char8_t);
#endif

BKSGE_INTEGRAL_TEST(false, void);
BKSGE_INTEGRAL_TEST(false, float);
BKSGE_INTEGRAL_TEST(false, int*);
BKSGE_INTEGRAL_TEST(false, int&);
BKSGE_INTEGRAL_TEST(false, int&&);
BKSGE_INTEGRAL_TEST(false, const int&);
BKSGE_INTEGRAL_TEST(false, int[]);
BKSGE_INTEGRAL_TEST(false, int[2]);
BKSGE_INTEGRAL_TEST(false, int());
BKSGE_INTEGRAL_TEST(false, int(*)());
BKSGE_INTEGRAL_TEST(false, int(&)());

enum E { };
BKSGE_INTEGRAL_TEST(false, E);
enum class CE { };
BKSGE_INTEGRAL_TEST(false, CE);
struct A { };
BKSGE_INTEGRAL_TEST(false, A);
union B { };
BKSGE_INTEGRAL_TEST(false, B);

}	// namespace integral_test

}	// namespace bksge_concepts_test

#undef BKSGE_INTEGRAL_TEST
