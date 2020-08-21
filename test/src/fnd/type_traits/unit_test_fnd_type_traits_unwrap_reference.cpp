/**
 *	@file	unit_test_fnd_type_traits_unwrap_reference.cpp
 *
 *	@brief	unwrap_reference のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/unwrap_reference.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <functional>

#define BKSGE_UNWRAP_REFERENCE_TEST(T1, T2)	\
	static_assert(bksge::is_same<bksge::unwrap_reference_t<T1>, T2>::value, "");	\
	static_assert(bksge::is_same<bksge::unwrap_reference<T1>::type, T2>::value, "")

BKSGE_UNWRAP_REFERENCE_TEST(int               , int               );
BKSGE_UNWRAP_REFERENCE_TEST(int const         , int const         );
BKSGE_UNWRAP_REFERENCE_TEST(int       volatile, int       volatile);
BKSGE_UNWRAP_REFERENCE_TEST(int const volatile, int const volatile);
BKSGE_UNWRAP_REFERENCE_TEST(int               &, int               &);
BKSGE_UNWRAP_REFERENCE_TEST(int const         &, int const         &);
BKSGE_UNWRAP_REFERENCE_TEST(int       volatile&, int       volatile&);
BKSGE_UNWRAP_REFERENCE_TEST(int const volatile&, int const volatile&);
BKSGE_UNWRAP_REFERENCE_TEST(int               &&, int               &&);
BKSGE_UNWRAP_REFERENCE_TEST(int const         &&, int const         &&);
BKSGE_UNWRAP_REFERENCE_TEST(int       volatile&&, int       volatile&&);
BKSGE_UNWRAP_REFERENCE_TEST(int const volatile&&, int const volatile&&);
BKSGE_UNWRAP_REFERENCE_TEST(int               *, int               *);
BKSGE_UNWRAP_REFERENCE_TEST(int const         *, int const         *);
BKSGE_UNWRAP_REFERENCE_TEST(int       volatile*, int       volatile*);
BKSGE_UNWRAP_REFERENCE_TEST(int const volatile*, int const volatile*);
BKSGE_UNWRAP_REFERENCE_TEST(int               *&, int               *&);
BKSGE_UNWRAP_REFERENCE_TEST(int const         *&, int const         *&);
BKSGE_UNWRAP_REFERENCE_TEST(int       volatile*&, int       volatile*&);
BKSGE_UNWRAP_REFERENCE_TEST(int const volatile*&, int const volatile*&);

// reference_wrapper types should get unwrapped:
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int               >, int               &);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int const         >, int const         &);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int       volatile>, int       volatile&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int const volatile>, int const volatile&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int               *>, int               *&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int const         *>, int const         *&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int       volatile*>, int       volatile*&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int const volatile*>, int const volatile*&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int               &>, int               &);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int const         &>, int const         &);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int       volatile&>, int       volatile&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int const volatile&>, int const volatile&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int               &&>, int               &);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int const         &&>, int const         &);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int       volatile&&>, int       volatile&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int const volatile&&>, int const volatile&);

// But not cv-qualified reference_wrapper types:
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int> const         , std::reference_wrapper<int> const         );
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int>       volatile, std::reference_wrapper<int>       volatile);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int> const volatile, std::reference_wrapper<int> const volatile);

// Or references to reference_wrapper types:
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int>               &, std::reference_wrapper<int>               &);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int> const         &, std::reference_wrapper<int> const         &);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int>       volatile&, std::reference_wrapper<int>       volatile&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int> const volatile&, std::reference_wrapper<int> const volatile&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int>               &&, std::reference_wrapper<int>               &&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int> const         &&, std::reference_wrapper<int> const         &&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int>       volatile&&, std::reference_wrapper<int>       volatile&&);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int> const volatile&&, std::reference_wrapper<int> const volatile&&);

// Or pointer to reference_wrapper types:
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int>               *, std::reference_wrapper<int>               *);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int> const         *, std::reference_wrapper<int> const         *);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int>       volatile*, std::reference_wrapper<int>       volatile*);
BKSGE_UNWRAP_REFERENCE_TEST(std::reference_wrapper<int> const volatile*, std::reference_wrapper<int> const volatile*);

#undef BKSGE_UNWRAP_REFERENCE_TEST
