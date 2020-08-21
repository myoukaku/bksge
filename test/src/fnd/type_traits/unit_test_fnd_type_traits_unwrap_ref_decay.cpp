/**
 *	@file	unit_test_fnd_type_traits_unwrap_ref_decay.cpp
 *
 *	@brief	unwrap_ref_decay のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/unwrap_ref_decay.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <functional>

#define BKSGE_UNWRAP_REF_DECAY_TEST(T1, T2)	\
	static_assert(bksge::is_same<bksge::unwrap_ref_decay_t<T1>, T2>::value, "");	\
	static_assert(bksge::is_same<bksge::unwrap_ref_decay<T1>::type, T2>::value, "")

BKSGE_UNWRAP_REF_DECAY_TEST(int               , int);
BKSGE_UNWRAP_REF_DECAY_TEST(int const         , int);
BKSGE_UNWRAP_REF_DECAY_TEST(int       volatile, int);
BKSGE_UNWRAP_REF_DECAY_TEST(int const volatile, int);
BKSGE_UNWRAP_REF_DECAY_TEST(int               &, int);
BKSGE_UNWRAP_REF_DECAY_TEST(int const         &, int);
BKSGE_UNWRAP_REF_DECAY_TEST(int       volatile&, int);
BKSGE_UNWRAP_REF_DECAY_TEST(int const volatile&, int);
BKSGE_UNWRAP_REF_DECAY_TEST(int               &&, int);
BKSGE_UNWRAP_REF_DECAY_TEST(int const         &&, int);
BKSGE_UNWRAP_REF_DECAY_TEST(int       volatile&&, int);
BKSGE_UNWRAP_REF_DECAY_TEST(int const volatile&&, int);
BKSGE_UNWRAP_REF_DECAY_TEST(int               *, int               *);
BKSGE_UNWRAP_REF_DECAY_TEST(int const         *, int const         *);
BKSGE_UNWRAP_REF_DECAY_TEST(int       volatile*, int       volatile*);
BKSGE_UNWRAP_REF_DECAY_TEST(int const volatile*, int const volatile*);
BKSGE_UNWRAP_REF_DECAY_TEST(int               *&, int               *);
BKSGE_UNWRAP_REF_DECAY_TEST(int const         *&, int const         *);
BKSGE_UNWRAP_REF_DECAY_TEST(int       volatile*&, int       volatile*);
BKSGE_UNWRAP_REF_DECAY_TEST(int const volatile*&, int const volatile*);

// reference_wrapper types (including cv and references) get unwrapped:
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int               >, int               &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const         >, int const         &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int       volatile>, int       volatile&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const volatile>, int const volatile&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int               *>, int               *&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const         *>, int const         *&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int       volatile*>, int       volatile*&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const volatile*>, int const volatile*&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int               &>, int               &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const         &>, int const         &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int       volatile&>, int       volatile&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const volatile&>, int const volatile&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int               &&>, int               &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const         &&>, int const         &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int       volatile&&>, int       volatile&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const volatile&&>, int const volatile&);

BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int               > const, int               &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const         > const, int const         &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int       volatile> const, int       volatile&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const volatile> const, int const volatile&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int               > volatile, int               &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const         > volatile, int const         &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int       volatile> volatile, int       volatile&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const volatile> volatile, int const volatile&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int               > const volatile, int               &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const         > const volatile, int const         &);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int       volatile> const volatile, int       volatile&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int const volatile> const volatile, int const volatile&);

BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int>               &, int&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int> const         &, int&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int>       volatile&, int&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int> const volatile&, int&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int>               &&, int&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int> const         &&, int&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int>       volatile&&, int&);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int> const volatile&&, int&);

// But not pointer to reference_wrapper types:
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int>               *, std::reference_wrapper<int>               *);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int> const         *, std::reference_wrapper<int> const         *);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int>       volatile*, std::reference_wrapper<int>       volatile*);
BKSGE_UNWRAP_REF_DECAY_TEST(std::reference_wrapper<int> const volatile*, std::reference_wrapper<int> const volatile*);

#undef BKSGE_UNWRAP_REF_DECAY_TEST
