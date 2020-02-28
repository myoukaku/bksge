/**
 *	@file	unit_test_fnd_functional_unwrap_reference.cpp
 *
 *	@brief	unwrap_reference のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/unwrap_reference.hpp>
#include <bksge/fnd/functional/reference_wrapper.hpp>
//#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/add_lvalue_reference.hpp>
#include <gtest/gtest.h>
#include <type_traits>

namespace bksge_functional_test
{

namespace unwrap_reference_test
{

struct S{};

template <typename> class T{};

GTEST_TEST(FunctionalTest, UnwrapReferenceTest)
{
#define BKSGE_UNWRAP_REFERENCE_TEST_1(T1, T2)										\
	static_assert(std::is_same<bksge::unwrap_reference<T1>::type, T2>::value, "");	\
	static_assert(std::is_same<bksge::unwrap_reference_t<T1>,     T2>::value, "")

#define BKSGE_UNWRAP_REFERENCE_TEST_2(T)	\
	BKSGE_UNWRAP_REFERENCE_TEST_1(T, T);	\
	BKSGE_UNWRAP_REFERENCE_TEST_1(bksge::reference_wrapper<T>, bksge::add_lvalue_reference_t<T>)

#define BKSGE_UNWRAP_REFERENCE_TEST_CV(T)				\
	BKSGE_UNWRAP_REFERENCE_TEST_2(               T);	\
	BKSGE_UNWRAP_REFERENCE_TEST_2(const          T);	\
	BKSGE_UNWRAP_REFERENCE_TEST_2(      volatile T);	\
	BKSGE_UNWRAP_REFERENCE_TEST_2(const volatile T)

#define BKSGE_UNWRAP_REFERENCE_TEST(T)	        \
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T);	        \
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T*);	        \
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T**);	    \
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T&);		    \
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T&&);	    \
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T*&);	    \
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T[]);	    \
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T[2]);	    \
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T[2][3]);	\
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T(*)[2]);	\
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T(&)[2]);	\
	BKSGE_UNWRAP_REFERENCE_TEST_CV(T(&&)[2])


	BKSGE_UNWRAP_REFERENCE_TEST(char);
	BKSGE_UNWRAP_REFERENCE_TEST(short);
	BKSGE_UNWRAP_REFERENCE_TEST(long);
	BKSGE_UNWRAP_REFERENCE_TEST(int);
	BKSGE_UNWRAP_REFERENCE_TEST(unsigned char);
	BKSGE_UNWRAP_REFERENCE_TEST(unsigned short);
	BKSGE_UNWRAP_REFERENCE_TEST(unsigned long);
	BKSGE_UNWRAP_REFERENCE_TEST(unsigned int);
	BKSGE_UNWRAP_REFERENCE_TEST(float);
	BKSGE_UNWRAP_REFERENCE_TEST(double);
	BKSGE_UNWRAP_REFERENCE_TEST(long double);
	BKSGE_UNWRAP_REFERENCE_TEST(S);
	BKSGE_UNWRAP_REFERENCE_TEST(T<int>);


#undef BKSGE_UNWRAP_REFERENCE_TEST
#undef BKSGE_UNWRAP_REFERENCE_TEST_CV
#undef BKSGE_UNWRAP_REFERENCE_TEST_2
#undef BKSGE_UNWRAP_REFERENCE_TEST_1
}

}	// namespace unwrap_reference_test

}	// namespace bksge_functional_test
