/**
 *	@file	unit_test_fnd_type_traits_cond_res.cpp
 *
 *	@brief	cond_res のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/detail/cond_res.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace bksge_type_traits_test
{

namespace cond_res_test
{

#define BKSGE_COND_RES_TEST(T, ...)	\
	static_assert(bksge::is_same<T, bksge::detail::cond_res<__VA_ARGS__>>::value, "")

BKSGE_COND_RES_TEST(int, int               , int               );
BKSGE_COND_RES_TEST(int, int               , int const         );
BKSGE_COND_RES_TEST(int, int               , int       volatile);
BKSGE_COND_RES_TEST(int, int               , int const volatile);
BKSGE_COND_RES_TEST(int, int const         , int               );
BKSGE_COND_RES_TEST(int, int const         , int const         );
BKSGE_COND_RES_TEST(int, int const         , int       volatile);
BKSGE_COND_RES_TEST(int, int const         , int const volatile);
BKSGE_COND_RES_TEST(int, int       volatile, int               );
BKSGE_COND_RES_TEST(int, int       volatile, int const         );
BKSGE_COND_RES_TEST(int, int       volatile, int       volatile);
BKSGE_COND_RES_TEST(int, int       volatile, int const volatile);
BKSGE_COND_RES_TEST(int, int const volatile, int               );
BKSGE_COND_RES_TEST(int, int const volatile, int const         );
BKSGE_COND_RES_TEST(int, int const volatile, int       volatile);
BKSGE_COND_RES_TEST(int, int const volatile, int const volatile);
BKSGE_COND_RES_TEST(int, int               , int               &);
BKSGE_COND_RES_TEST(int, int               , int const         &);
BKSGE_COND_RES_TEST(int, int               , int       volatile&);
BKSGE_COND_RES_TEST(int, int               , int const volatile&);
BKSGE_COND_RES_TEST(int, int const         , int               &);
BKSGE_COND_RES_TEST(int, int const         , int const         &);
BKSGE_COND_RES_TEST(int, int const         , int       volatile&);
BKSGE_COND_RES_TEST(int, int const         , int const volatile&);
BKSGE_COND_RES_TEST(int, int       volatile, int               &);
BKSGE_COND_RES_TEST(int, int       volatile, int const         &);
BKSGE_COND_RES_TEST(int, int       volatile, int       volatile&);
BKSGE_COND_RES_TEST(int, int       volatile, int const volatile&);
BKSGE_COND_RES_TEST(int, int const volatile, int               &);
BKSGE_COND_RES_TEST(int, int const volatile, int const         &);
BKSGE_COND_RES_TEST(int, int const volatile, int       volatile&);
BKSGE_COND_RES_TEST(int, int const volatile, int const volatile&);
BKSGE_COND_RES_TEST(int, int               , int               &&);
BKSGE_COND_RES_TEST(int, int               , int const         &&);
BKSGE_COND_RES_TEST(int, int               , int       volatile&&);
BKSGE_COND_RES_TEST(int, int               , int const volatile&&);
BKSGE_COND_RES_TEST(int, int const         , int               &&);
BKSGE_COND_RES_TEST(int, int const         , int const         &&);
BKSGE_COND_RES_TEST(int, int const         , int       volatile&&);
BKSGE_COND_RES_TEST(int, int const         , int const volatile&&);
BKSGE_COND_RES_TEST(int, int       volatile, int               &&);
BKSGE_COND_RES_TEST(int, int       volatile, int const         &&);
BKSGE_COND_RES_TEST(int, int       volatile, int       volatile&&);
BKSGE_COND_RES_TEST(int, int       volatile, int const volatile&&);
BKSGE_COND_RES_TEST(int, int const volatile, int               &&);
BKSGE_COND_RES_TEST(int, int const volatile, int const         &&);
BKSGE_COND_RES_TEST(int, int const volatile, int       volatile&&);
BKSGE_COND_RES_TEST(int, int const volatile, int const volatile&&);

BKSGE_COND_RES_TEST(int, int               &, int               );
BKSGE_COND_RES_TEST(int, int               &, int const         );
BKSGE_COND_RES_TEST(int, int               &, int       volatile);
BKSGE_COND_RES_TEST(int, int               &, int const volatile);
BKSGE_COND_RES_TEST(int, int const         &, int               );
BKSGE_COND_RES_TEST(int, int const         &, int const         );
BKSGE_COND_RES_TEST(int, int const         &, int       volatile);
BKSGE_COND_RES_TEST(int, int const         &, int const volatile);
BKSGE_COND_RES_TEST(int, int       volatile&, int               );
BKSGE_COND_RES_TEST(int, int       volatile&, int const         );
BKSGE_COND_RES_TEST(int, int       volatile&, int       volatile);
BKSGE_COND_RES_TEST(int, int       volatile&, int const volatile);
BKSGE_COND_RES_TEST(int, int const volatile&, int               );
BKSGE_COND_RES_TEST(int, int const volatile&, int const         );
BKSGE_COND_RES_TEST(int, int const volatile&, int       volatile);
BKSGE_COND_RES_TEST(int, int const volatile&, int const volatile);
//BKSGE_COND_RES_TEST(int               &, int               &, int               &);
//BKSGE_COND_RES_TEST(int const         &, int               &, int const         &);
//BKSGE_COND_RES_TEST(int       volatile&, int               &, int       volatile&);
//BKSGE_COND_RES_TEST(int const volatile&, int               &, int const volatile&);
//BKSGE_COND_RES_TEST(int const         &, int const         &, int               &);
//BKSGE_COND_RES_TEST(int const         &, int const         &, int const         &);
//BKSGE_COND_RES_TEST(int                , int const         &, int       volatile&);
//BKSGE_COND_RES_TEST(int const volatile&, int const         &, int const volatile&);
//BKSGE_COND_RES_TEST(int       volatile&, int       volatile&, int               &);
//BKSGE_COND_RES_TEST(int                , int       volatile&, int const         &);
//BKSGE_COND_RES_TEST(int       volatile&, int       volatile&, int       volatile&);
//BKSGE_COND_RES_TEST(int const volatile&, int       volatile&, int const volatile&);
//BKSGE_COND_RES_TEST(int const volatile&, int const volatile&, int               &);
//BKSGE_COND_RES_TEST(int const volatile&, int const volatile&, int const         &);
//BKSGE_COND_RES_TEST(int const volatile&, int const volatile&, int       volatile&);
//BKSGE_COND_RES_TEST(int const volatile&, int const volatile&, int const volatile&);
BKSGE_COND_RES_TEST(int, int               &, int               &&);
BKSGE_COND_RES_TEST(int, int               &, int const         &&);
BKSGE_COND_RES_TEST(int, int               &, int       volatile&&);
BKSGE_COND_RES_TEST(int, int               &, int const volatile&&);
BKSGE_COND_RES_TEST(int, int const         &, int               &&);
BKSGE_COND_RES_TEST(int, int const         &, int const         &&);
BKSGE_COND_RES_TEST(int, int const         &, int       volatile&&);
BKSGE_COND_RES_TEST(int, int const         &, int const volatile&&);
BKSGE_COND_RES_TEST(int, int       volatile&, int               &&);
BKSGE_COND_RES_TEST(int, int       volatile&, int const         &&);
BKSGE_COND_RES_TEST(int, int       volatile&, int       volatile&&);
BKSGE_COND_RES_TEST(int, int       volatile&, int const volatile&&);
BKSGE_COND_RES_TEST(int, int const volatile&, int               &&);
BKSGE_COND_RES_TEST(int, int const volatile&, int const         &&);
BKSGE_COND_RES_TEST(int, int const volatile&, int       volatile&&);
BKSGE_COND_RES_TEST(int, int const volatile&, int const volatile&&);

BKSGE_COND_RES_TEST(int, int               &&, int               );
BKSGE_COND_RES_TEST(int, int               &&, int const         );
BKSGE_COND_RES_TEST(int, int               &&, int       volatile);
BKSGE_COND_RES_TEST(int, int               &&, int const volatile);
BKSGE_COND_RES_TEST(int, int const         &&, int               );
BKSGE_COND_RES_TEST(int, int const         &&, int const         );
BKSGE_COND_RES_TEST(int, int const         &&, int       volatile);
BKSGE_COND_RES_TEST(int, int const         &&, int const volatile);
BKSGE_COND_RES_TEST(int, int       volatile&&, int               );
BKSGE_COND_RES_TEST(int, int       volatile&&, int const         );
BKSGE_COND_RES_TEST(int, int       volatile&&, int       volatile);
BKSGE_COND_RES_TEST(int, int       volatile&&, int const volatile);
BKSGE_COND_RES_TEST(int, int const volatile&&, int               );
BKSGE_COND_RES_TEST(int, int const volatile&&, int const         );
BKSGE_COND_RES_TEST(int, int const volatile&&, int       volatile);
BKSGE_COND_RES_TEST(int, int const volatile&&, int const volatile);
BKSGE_COND_RES_TEST(int, int               &&, int               &);
BKSGE_COND_RES_TEST(int, int               &&, int const         &);
BKSGE_COND_RES_TEST(int, int               &&, int       volatile&);
BKSGE_COND_RES_TEST(int, int               &&, int const volatile&);
BKSGE_COND_RES_TEST(int, int const         &&, int               &);
BKSGE_COND_RES_TEST(int, int const         &&, int const         &);
BKSGE_COND_RES_TEST(int, int const         &&, int       volatile&);
BKSGE_COND_RES_TEST(int, int const         &&, int const volatile&);
BKSGE_COND_RES_TEST(int, int       volatile&&, int               &);
BKSGE_COND_RES_TEST(int, int       volatile&&, int const         &);
BKSGE_COND_RES_TEST(int, int       volatile&&, int       volatile&);
BKSGE_COND_RES_TEST(int, int       volatile&&, int const volatile&);
BKSGE_COND_RES_TEST(int, int const volatile&&, int               &);
BKSGE_COND_RES_TEST(int, int const volatile&&, int const         &);
BKSGE_COND_RES_TEST(int, int const volatile&&, int       volatile&);
BKSGE_COND_RES_TEST(int, int const volatile&&, int const volatile&);
//BKSGE_COND_RES_TEST(int               &&, int               &&, int               &&);
//BKSGE_COND_RES_TEST(int const         &&, int               &&, int const         &&);
//BKSGE_COND_RES_TEST(int       volatile&&, int               &&, int       volatile&&);
//BKSGE_COND_RES_TEST(int const volatile&&, int               &&, int const volatile&&);
//BKSGE_COND_RES_TEST(int const         &&, int const         &&, int               &&);
//BKSGE_COND_RES_TEST(int const         &&, int const         &&, int const         &&);
//BKSGE_COND_RES_TEST(int                 , int const         &&, int       volatile&&);
//BKSGE_COND_RES_TEST(int const volatile&&, int const         &&, int const volatile&&);
//BKSGE_COND_RES_TEST(int       volatile&&, int       volatile&&, int               &&);
//BKSGE_COND_RES_TEST(int                 , int       volatile&&, int const         &&);
//BKSGE_COND_RES_TEST(int       volatile&&, int       volatile&&, int       volatile&&);
//BKSGE_COND_RES_TEST(int const volatile&&, int       volatile&&, int const volatile&&);
//BKSGE_COND_RES_TEST(int const volatile&&, int const volatile&&, int               &&);
//BKSGE_COND_RES_TEST(int const volatile&&, int const volatile&&, int const         &&);
//BKSGE_COND_RES_TEST(int const volatile&&, int const volatile&&, int       volatile&&);
//BKSGE_COND_RES_TEST(int const volatile&&, int const volatile&&, int const volatile&&);

#undef BKSGE_COND_RES_TEST

}	// namespace cond_res_test

}	// namespace bksge_type_traits_test
