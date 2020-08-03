/**
 *	@file	unit_test_fnd_concepts_unsigned_integral.cpp
 *
 *	@brief	unsigned_integral のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/unsigned_integral.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>	// WCHAR_MIN
#include <climits>	// CHAR_MIN

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_UNSIGNED_INTEGRAL_TEST(B, T)	\
	static_assert(B == bksge::unsigned_integral<T>, "")
#else
#  define BKSGE_UNSIGNED_INTEGRAL_TEST(B, T)	\
	static_assert(B == bksge::unsigned_integral<T>::value, "")
#endif

namespace bksge_concepts_test
{

namespace unsigned_integral_test
{

// unsigned integer types
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  unsigned char);
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  unsigned short);
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  unsigned int);
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  unsigned long);
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  unsigned long long);

// signed integer types
BKSGE_UNSIGNED_INTEGRAL_TEST(false, signed char);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, signed short);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, signed int);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, signed long);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, signed long long);

// other integral types
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  bool);
#if CHAR_MIN < 0
BKSGE_UNSIGNED_INTEGRAL_TEST(false, char);
#else
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  char);
#endif
#if WCHAR_MIN < 0
BKSGE_UNSIGNED_INTEGRAL_TEST(false, wchar_t);
#else
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  wchar_t);
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  char16_t);
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  char32_t);
#endif
#if 0//defined(BKSGE_HAS_CXX20_CHAR8_T)
BKSGE_UNSIGNED_INTEGRAL_TEST(true,  char8_t);
#endif

BKSGE_UNSIGNED_INTEGRAL_TEST(false, void);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, float);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, unsigned&);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, unsigned&);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, unsigned&&);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, const unsigned&);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, unsigned[]);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, unsigned[2]);
BKSGE_UNSIGNED_INTEGRAL_TEST(false, unsigned());
BKSGE_UNSIGNED_INTEGRAL_TEST(false, unsigned(*)());
BKSGE_UNSIGNED_INTEGRAL_TEST(false, unsigned(&)());

enum E { };
BKSGE_UNSIGNED_INTEGRAL_TEST(false, E);
enum class CE { };
BKSGE_UNSIGNED_INTEGRAL_TEST(false, CE);
struct A { };
BKSGE_UNSIGNED_INTEGRAL_TEST(false, A);
union B { };
BKSGE_UNSIGNED_INTEGRAL_TEST(false, B);

}	// namespace unsigned_integral_test

}	// namespace bksge_concepts_test

#undef BKSGE_UNSIGNED_INTEGRAL_TEST
