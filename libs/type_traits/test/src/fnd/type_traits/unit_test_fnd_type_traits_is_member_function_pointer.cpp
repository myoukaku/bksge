/**
 *	@file	unit_test_fnd_type_traits_is_member_function_pointer.cpp
 *
 *	@brief	is_member_function_pointer のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_member_function_pointer.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(b, T)	\
	static_assert(bksge::is_member_function_pointer_v<T>      == b, #T);	\
	static_assert(bksge::is_member_function_pointer<T>::value == b, #T);	\
	static_assert(bksge::is_member_function_pointer<T>()      == b, #T)

#else

#define BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(b, T)	\
	static_assert(bksge::is_member_function_pointer<T>::value == b, #T);	\
	static_assert(bksge::is_member_function_pointer<T>()      == b, #T)

#endif

BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int*);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int* const);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int* volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int* const volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int**);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int&);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int&&);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int[2]);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int[]);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int(*)[2]);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int(*)[]);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int(&)[2]);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int(&)[]);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int(&&)[2]);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int(&&)[]);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int(UDT::*));
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, int*(UDT::*));
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  int    (UDT::*               )(             )               );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  char   (UDT::*               )(int          ) const         );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  short  (UDT::*               )(float        )       volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  long   (UDT::*               )(double       ) const volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  float  (UDT::* const         )(int, int     )               );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  double (UDT::* const         )(int, int, int) const         );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  void   (UDT::* const         )(char         )       volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  int*   (UDT::* const         )(char*        ) const volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  char*  (UDT::*       volatile)(int&         )               );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  short* (UDT::*       volatile)(int*         ) const         );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  long*  (UDT::*       volatile)(long         )       volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  float* (UDT::*       volatile)(short        ) const volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  double*(UDT::* const volatile)(const long&  )               );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  void*  (UDT::* const volatile)(const int&   ) const         );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  int    (UDT::* const volatile)(char const*  )       volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  int    (UDT::* const volatile)(char, char   ) const volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  int    (UDT::*               )(...)               );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  char   (UDT::*               )(int          , ...) const         );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  short  (UDT::*               )(float        , ...)       volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  long   (UDT::*               )(double       , ...) const volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  float  (UDT::* const         )(int, int     , ...)               );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  double (UDT::* const         )(int, int, int, ...) const         );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  void   (UDT::* const         )(char         , ...)       volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  int*   (UDT::* const         )(char*        , ...) const volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  char*  (UDT::*       volatile)(int&         , ...)               );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  short* (UDT::*       volatile)(int*         , ...) const         );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  long*  (UDT::*       volatile)(long         , ...)       volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  float* (UDT::*       volatile)(short        , ...) const volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  double*(UDT::* const volatile)(const long&  , ...)               );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  void*  (UDT::* const volatile)(const int&   , ...) const         );
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  int    (UDT::* const volatile)(char const*  , ...)       volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  int    (UDT::* const volatile)(char, char   , ...) const volatile);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, f1);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, f2);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, f3);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  mf1);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  mf2);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  mf3);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  mf4);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, mf1&);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, mf2&);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, mf3&);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, mf4&);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, mp);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(true,  cmf);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, foo0_t);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, foo1_t);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, foo2_t);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, foo3_t);
BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST(false, foo4_t);

#undef BKSGE_IS_MEMBER_FUNCTION_POINTER_TEST
