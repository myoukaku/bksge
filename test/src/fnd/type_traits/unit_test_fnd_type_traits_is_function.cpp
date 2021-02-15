/**
 *	@file	unit_test_fnd_type_traits_is_function.cpp
 *
 *	@brief	is_function のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_function.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace bksge_type_traits_test
{

namespace is_function_test
{

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_FUNCTION_TEST(b, T)	\
	static_assert(bksge::is_function_v<T>      == b, #T);	\
	static_assert(bksge::is_function<T>::value == b, #T);	\
	static_assert(bksge::is_function<T>()      == b, #T)

#else

#define BKSGE_IS_FUNCTION_TEST(b, T)	\
	static_assert(bksge::is_function<T>::value == b, #T);	\
	static_assert(bksge::is_function<T>()      == b, #T)

#endif

typedef void  func1()                                       ;
typedef int   func2()                        const          ;
typedef int   func3(int)                           volatile ;
typedef void  func4(int, float)              const volatile ;
typedef int   func5(int, float, UDT)                        &;
typedef int   func6(int, float, int[], int&) const          &;
typedef float func7(UDT)                           volatile &;
typedef UDT   func8()                        const volatile &;
typedef int   func9(int, int, int, int, int)                &&;
typedef int   func10(int*)                   const          &&;
typedef int   func11(float)                        volatile &&;
typedef int   func12(double)                 const volatile &&;
typedef int   func13(...)                                   ;
typedef void  func14(int, ...)               const          ;
typedef float func15(float, ...)                   volatile ;
typedef int   func16(int, char, ...)         const volatile ;
typedef char  func17(int, int, int, ...)                    &;
typedef void  func18(float, ...)             const          &;
typedef int*  func19(int, ...)                     volatile &;
typedef int&  func20(...)                    const volatile &;
typedef int&& func21(int, ...)                              &&;
typedef int   func22(...)                    const          &&;
typedef int   func23(float, ...)                   volatile &&;
typedef int   func24(...)                    const volatile &&;

BKSGE_IS_FUNCTION_TEST(true,  func1);
BKSGE_IS_FUNCTION_TEST(false, func1*);
BKSGE_IS_FUNCTION_TEST(false, func1&);
BKSGE_IS_FUNCTION_TEST(false, func1&&);
BKSGE_IS_FUNCTION_TEST(true, func2);
BKSGE_IS_FUNCTION_TEST(true, func3);
BKSGE_IS_FUNCTION_TEST(true, func4);
BKSGE_IS_FUNCTION_TEST(true, func5);
BKSGE_IS_FUNCTION_TEST(true, func6);
BKSGE_IS_FUNCTION_TEST(true, func7);
BKSGE_IS_FUNCTION_TEST(true, func8);
BKSGE_IS_FUNCTION_TEST(true, func9);
BKSGE_IS_FUNCTION_TEST(true, func10);
BKSGE_IS_FUNCTION_TEST(true, func11);
BKSGE_IS_FUNCTION_TEST(true, func12);
BKSGE_IS_FUNCTION_TEST(true, func13);
BKSGE_IS_FUNCTION_TEST(true, func14);
BKSGE_IS_FUNCTION_TEST(true, func15);
BKSGE_IS_FUNCTION_TEST(true, func16);
BKSGE_IS_FUNCTION_TEST(true, func17);
BKSGE_IS_FUNCTION_TEST(true, func18);
BKSGE_IS_FUNCTION_TEST(true, func19);
BKSGE_IS_FUNCTION_TEST(true, func20);
BKSGE_IS_FUNCTION_TEST(true, func21);
BKSGE_IS_FUNCTION_TEST(true, func22);
BKSGE_IS_FUNCTION_TEST(true, func23);
BKSGE_IS_FUNCTION_TEST(true, func24);

BKSGE_IS_FUNCTION_TEST(true, int(int));
BKSGE_IS_FUNCTION_TEST(true, int(int, int));
BKSGE_IS_FUNCTION_TEST(true, int(int, int, int));
BKSGE_IS_FUNCTION_TEST(true, int(int, int, int, int));
BKSGE_IS_FUNCTION_TEST(true, int(int, ...));
BKSGE_IS_FUNCTION_TEST(true, int(int, int, ...));
BKSGE_IS_FUNCTION_TEST(true, int(int, int, int, ...));
BKSGE_IS_FUNCTION_TEST(true, int(int, int, int, int, ...));

BKSGE_IS_FUNCTION_TEST(false,                int);
BKSGE_IS_FUNCTION_TEST(false, const          int);
BKSGE_IS_FUNCTION_TEST(false,       volatile int);
BKSGE_IS_FUNCTION_TEST(false, const volatile int);
BKSGE_IS_FUNCTION_TEST(false, int*);
BKSGE_IS_FUNCTION_TEST(false, int&);
BKSGE_IS_FUNCTION_TEST(false, int&&);
BKSGE_IS_FUNCTION_TEST(false, int[2]);
BKSGE_IS_FUNCTION_TEST(false, int[]);
BKSGE_IS_FUNCTION_TEST(false, int(*)[2]);
BKSGE_IS_FUNCTION_TEST(false, int(*)[]);
BKSGE_IS_FUNCTION_TEST(false, int(&)[2]);
BKSGE_IS_FUNCTION_TEST(false, int(&)[]);
BKSGE_IS_FUNCTION_TEST(false, int(&&)[2]);
BKSGE_IS_FUNCTION_TEST(false, int(&&)[]);
BKSGE_IS_FUNCTION_TEST(false, int(*)());
BKSGE_IS_FUNCTION_TEST(false, int(*)(int));
BKSGE_IS_FUNCTION_TEST(false, int(&)());
BKSGE_IS_FUNCTION_TEST(false, int(&)(int));
BKSGE_IS_FUNCTION_TEST(false, int(&&)());
BKSGE_IS_FUNCTION_TEST(false, int(&&)(int));
BKSGE_IS_FUNCTION_TEST(false, int(*)(...));
BKSGE_IS_FUNCTION_TEST(false, int(&)(...));
BKSGE_IS_FUNCTION_TEST(false, int(&&)(...));

BKSGE_IS_FUNCTION_TEST(false,                void);
BKSGE_IS_FUNCTION_TEST(false, const          void);
BKSGE_IS_FUNCTION_TEST(false,       volatile void);
BKSGE_IS_FUNCTION_TEST(false, const volatile void);

BKSGE_IS_FUNCTION_TEST(false, bool);
BKSGE_IS_FUNCTION_TEST(false, char);
BKSGE_IS_FUNCTION_TEST(false, float);
BKSGE_IS_FUNCTION_TEST(false, void*);
BKSGE_IS_FUNCTION_TEST(false, bksge::nullptr_t);
BKSGE_IS_FUNCTION_TEST(false, decltype(nullptr));
BKSGE_IS_FUNCTION_TEST(false, enum_UDT);
BKSGE_IS_FUNCTION_TEST(false, enum_class_UDT);
BKSGE_IS_FUNCTION_TEST(false, UDT);
BKSGE_IS_FUNCTION_TEST(false, POD_UDT);
BKSGE_IS_FUNCTION_TEST(false, f1);
BKSGE_IS_FUNCTION_TEST(false, f2);
BKSGE_IS_FUNCTION_TEST(false, f3);
BKSGE_IS_FUNCTION_TEST(false, mf1);
BKSGE_IS_FUNCTION_TEST(false, mf2);
BKSGE_IS_FUNCTION_TEST(false, mf3);
BKSGE_IS_FUNCTION_TEST(false, mf4);
BKSGE_IS_FUNCTION_TEST(false, mp);
BKSGE_IS_FUNCTION_TEST(false, cmf);
BKSGE_IS_FUNCTION_TEST(true,  foo0_t);
BKSGE_IS_FUNCTION_TEST(false, foo0_t*);
BKSGE_IS_FUNCTION_TEST(false, foo0_t&);
BKSGE_IS_FUNCTION_TEST(false, foo0_t&&);
BKSGE_IS_FUNCTION_TEST(true,  foo1_t);
BKSGE_IS_FUNCTION_TEST(true,  foo2_t);
BKSGE_IS_FUNCTION_TEST(true,  foo3_t);
BKSGE_IS_FUNCTION_TEST(true,  foo4_t);

#undef BKSGE_IS_FUNCTION_TEST

}	// namespace is_function_test

}	// namespace bksge_type_traits_test
