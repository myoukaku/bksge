/**
 *	@file	unit_test_fnd_functional_unwrap_ref_decay.cpp
 *
 *	@brief	unwrap_ref_decay のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/functional/unwrap_ref_decay.hpp>
#include <bksge/fnd/functional/reference_wrapper.hpp>
//#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <type_traits>

namespace bksge_functional_test
{

namespace unwrap_ref_decay_test
{

struct S{};

template <typename> class T{};

GTEST_TEST(FunctionalTest, DecayUnwrapTest)
{
#define BKSGE_UNWRAP_REF_DECAY_TEST_1(T1, T2)										\
	static_assert(std::is_same<bksge::unwrap_ref_decay<T1>::type, T2>::value, "");	\
	static_assert(std::is_same<bksge::unwrap_ref_decay_t<T1>,     T2>::value, "")

#define BKSGE_UNWRAP_REF_DECAY_TEST_2(T1, T2)	                                    \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1,        T2);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1&,       T2);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1&&,      T2);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1*,       T1*);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1*&,      T1*);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1*&&,     T1*);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1**,      T1**);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1**&,     T1**);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1**&&,    T1**);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1[2],     T1*);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1[],      T1*);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1(*)[2],  T1(*)[2]);	                            \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1(*)[],   T1(*)[]);	                            \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1(&)[2],  T1*);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1(&)[],   T1*);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1(&&)[2], T1*);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(T1(&&)[],  T1*);	                                \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1>,        T1&);	    \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1&>,       T1&);	    \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1&&>,      T1&);	    \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1*>,       T1*&);	    \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1*&>,      T1*&);	    \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1*&&>,     T1*&);	    \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1**>,      T1**&);	    \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1**&>,     T1**&);	    \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1**&&>,    T1**&);	    \
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1[2]>,     T1(&)[2]);	\
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1[]>,      T1(&)[]);	\
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1(*)[2]>,  T1(*&)[2]);	\
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1(*)[]>,   T1(*&)[]);	\
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1(&)[2]>,  T1(&)[2]);	\
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1(&)[]>,   T1(&)[]);	\
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1(&&)[2]>, T1(&)[2]);	\
	BKSGE_UNWRAP_REF_DECAY_TEST_1(bksge::reference_wrapper<T1(&&)[]>,  T1(&)[])

#define BKSGE_UNWRAP_REF_DECAY_TEST_CV(T)				\
	BKSGE_UNWRAP_REF_DECAY_TEST_2(               T, T);	\
	BKSGE_UNWRAP_REF_DECAY_TEST_2(const          T, T);	\
	BKSGE_UNWRAP_REF_DECAY_TEST_2(      volatile T, T);	\
	BKSGE_UNWRAP_REF_DECAY_TEST_2(const volatile T, T)


	BKSGE_UNWRAP_REF_DECAY_TEST_CV(char);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(short);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(long);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(int);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(unsigned char);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(unsigned short);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(unsigned long);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(unsigned int);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(float);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(double);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(long double);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(S);
	BKSGE_UNWRAP_REF_DECAY_TEST_CV(T<int>);


#undef BKSGE_UNWRAP_REF_DECAY_TEST_1
#undef BKSGE_UNWRAP_REF_DECAY_TEST_2
#undef BKSGE_UNWRAP_REF_DECAY_TEST_CV
}

}	// namespace unwrap_ref_decay_test

}	// namespace bksge_functional_test
