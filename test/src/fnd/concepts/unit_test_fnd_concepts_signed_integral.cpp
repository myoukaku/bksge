/**
 *	@file	unit_test_fnd_concepts_signed_integral.cpp
 *
 *	@brief	signed_integral のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/concepts/signed_integral.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>	// WCHAR_MIN
#include <climits>	// CHAR_MIN

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
#  define BKSGE_SIGNED_INTEGRAL_TEST(B, T)	\
	static_assert(B == bksge::signed_integral<T>, "")
#else
#  define BKSGE_SIGNED_INTEGRAL_TEST(B, T)	\
	static_assert(B == bksge::signed_integral<T>::value, "")
#endif

namespace bksge_concepts_test
{

namespace signed_integral_test
{

// signed integer types
BKSGE_SIGNED_INTEGRAL_TEST(true,  signed char);
BKSGE_SIGNED_INTEGRAL_TEST(true,  signed short);
BKSGE_SIGNED_INTEGRAL_TEST(true,  signed int);
BKSGE_SIGNED_INTEGRAL_TEST(true,  signed long);
BKSGE_SIGNED_INTEGRAL_TEST(true,  signed long long);

// unsigned integer types
BKSGE_SIGNED_INTEGRAL_TEST(false, unsigned char);
BKSGE_SIGNED_INTEGRAL_TEST(false, unsigned short);
BKSGE_SIGNED_INTEGRAL_TEST(false, unsigned int);
BKSGE_SIGNED_INTEGRAL_TEST(false, unsigned long);
BKSGE_SIGNED_INTEGRAL_TEST(false, unsigned long long);

// other integral types
BKSGE_SIGNED_INTEGRAL_TEST(false, bool);
#if CHAR_MIN < 0
BKSGE_SIGNED_INTEGRAL_TEST(true,  char);
#else
BKSGE_SIGNED_INTEGRAL_TEST(false, char);
#endif
#if WCHAR_MIN < 0
BKSGE_SIGNED_INTEGRAL_TEST(true,  wchar_t);
#else
BKSGE_SIGNED_INTEGRAL_TEST(false, wchar_t);
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
BKSGE_SIGNED_INTEGRAL_TEST(false, char16_t);
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
BKSGE_SIGNED_INTEGRAL_TEST(false, char32_t);
#endif
#if 0//defined(BKSGE_HAS_CXX20_CHAR8_T)
BKSGE_SIGNED_INTEGRAL_TEST(false, char8_t);
#endif

BKSGE_SIGNED_INTEGRAL_TEST(false, void);
BKSGE_SIGNED_INTEGRAL_TEST(false, float);
BKSGE_SIGNED_INTEGRAL_TEST(false, int&);
BKSGE_SIGNED_INTEGRAL_TEST(false, int&);
BKSGE_SIGNED_INTEGRAL_TEST(false, int&&);
BKSGE_SIGNED_INTEGRAL_TEST(false, const int&);
BKSGE_SIGNED_INTEGRAL_TEST(false, int[]);
BKSGE_SIGNED_INTEGRAL_TEST(false, int[2]);
BKSGE_SIGNED_INTEGRAL_TEST(false, int());
BKSGE_SIGNED_INTEGRAL_TEST(false, int(*)());
BKSGE_SIGNED_INTEGRAL_TEST(false, int(&)());

enum E { };
BKSGE_SIGNED_INTEGRAL_TEST(false, E);
enum class CE { };
BKSGE_SIGNED_INTEGRAL_TEST(false, CE);
struct A { };
BKSGE_SIGNED_INTEGRAL_TEST(false, A);
union B { };
BKSGE_SIGNED_INTEGRAL_TEST(false, B);

}	// namespace signed_integral_test

}	// namespace bksge_concepts_test

#undef BKSGE_SIGNED_INTEGRAL_TEST
