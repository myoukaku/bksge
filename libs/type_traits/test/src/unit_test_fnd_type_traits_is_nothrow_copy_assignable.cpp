/**
 *	@file	unit_test_fnd_type_traits_is_nothrow_copy_assignable.cpp
 *
 *	@brief	is_nothrow_copy_assignable のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/is_nothrow_copy_assignable.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES)

#define BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(b, T)	\
	static_assert(bksge::is_nothrow_copy_assignable_v<T>      == b, #T ", " #b);	\
	static_assert(bksge::is_nothrow_copy_assignable<T>::value == b, #T ", " #b);	\
	static_assert(bksge::is_nothrow_copy_assignable<T>()      == b, #T ", " #b)

#else

#define BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(b, T)	\
	static_assert(bksge::is_nothrow_copy_assignable<T>::value == b, #T ", " #b);	\
	static_assert(bksge::is_nothrow_copy_assignable<T>()      == b, #T ", " #b)

#endif

namespace bksge_type_traits_test
{

namespace is_nothrow_copy_assignable_test
{

// トリビアルなコピー代入演算子を持つ
struct S1
{
	int n;
};

// 非トリビアルだが例外を投げないコピー代入演算子を持つ
struct S2
{
	S2& operator=(const S2&) BKSGE_NOEXCEPT_OR_NOTHROW;
};

// 非トリビアルだが例外を投げないコピー代入演算子を持つクラスをメンバに持つ
struct S3
{
	S2 member;
};

// コピー代入演算子が例外を投げる
struct S4
{
	S4& operator=(const S4&);
};

// コピー代入演算子が例外を投げる
struct S5
{
	S5& operator=(const S5&) BKSGE_NOEXCEPT_IF(false);
};

// コピー代入演算子を持たない
struct S6
{
	S6& operator=(const S6&) = delete;
};

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  S1);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  S2);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  S3);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, S4);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, S5);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, S6);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                void);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          void);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile void);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile void);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 int);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          int);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,        volatile int);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile int);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 int*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  const          int*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,        volatile int*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  const volatile int*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 int&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          int&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,        volatile int&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile int&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 int&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          int&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,        volatile int&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile int&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, int[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, int[]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  int(*)[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  int(*)[]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, int(&)[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, int(&)[]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, int(&&)[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, int(&&)[]);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 UDT*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  const          UDT*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,        volatile UDT*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  const volatile UDT*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, UDT[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, UDT[]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  UDT(*)[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  UDT(*)[]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, UDT(&)[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, UDT(&)[]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, UDT(&&)[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, UDT(&&)[]);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 POD_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          POD_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile POD_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile POD_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 POD_UDT*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  const          POD_UDT*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,        volatile POD_UDT*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  const volatile POD_UDT*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 POD_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          POD_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile POD_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile POD_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 POD_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          POD_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile POD_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile POD_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, POD_UDT[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, POD_UDT[]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  POD_UDT(*)[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  POD_UDT(*)[]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, POD_UDT(&)[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, POD_UDT(&)[]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, POD_UDT(&&)[2]);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, POD_UDT(&&)[]);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_default_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_default_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_default_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_default_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_default_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_default_ctor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_default_ctor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_default_ctor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_default_ctor_UDT&&);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_dtor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_dtor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_dtor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_dtor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_dtor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_dtor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_dtor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_dtor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_dtor_UDT&&);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_copy_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_copy_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_copy_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_copy_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_copy_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_copy_ctor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_copy_ctor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_copy_ctor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_copy_ctor_UDT&&);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_copy_assign_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 nothrow_copy_assign_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_copy_assign_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_copy_assign_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_copy_assign_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,                 nothrow_copy_assign_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_copy_assign_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_copy_assign_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_copy_assign_UDT&&);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_move_ctor_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_move_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_move_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_move_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_move_ctor_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_move_ctor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_move_ctor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_move_ctor_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_move_ctor_UDT&&);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_move_assign_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_move_assign_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_move_assign_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_move_assign_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_move_assign_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_move_assign_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_move_assign_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_move_assign_UDT&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,                nothrow_move_assign_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const          nothrow_move_assign_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false,       volatile nothrow_move_assign_UDT&&);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, const volatile nothrow_move_assign_UDT&&);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, bool);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, char);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, wchar_t);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, signed char);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, short);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, long);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, long long);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, unsigned char);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, unsigned int);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, unsigned short);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, unsigned long);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, unsigned long long);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, bksge::size_t);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, float);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, double);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, long double);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, void*);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, bksge::nullptr_t);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, decltype(nullptr));
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_uint32_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_uint16_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_uint8_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_int32_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_int16_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_int8_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_class_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_class_uint32_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_class_uint16_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_class_uint8_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_class_int32_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_class_int16_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum_class_int8_t_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, empty_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, empty_POD_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, union_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, POD_union_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, empty_union_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, empty_POD_union_UDT);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, Base);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, Derived);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, Derived2);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, MultiBase);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, PrivateBase);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, NonDerived);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum1);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, enum2);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, VB);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, VD);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, non_pointer);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, non_int_pointer);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, int_constructible);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, int_convertible);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, test_abc1);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  test_abc2);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, test_abc3);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true,  test_concrete1);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, test_concrete2);
//BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, incomplete_type);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, polymorphic_base);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, polymorphic_derived1);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, polymorphic_derived2);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, virtual_inherit1);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, virtual_inherit2);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, virtual_inherit3);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, virtual_inherit5);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, virtual_inherit6);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, trivial_except_construct);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, trivial_except_destroy);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, trivial_except_copy_ctor);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, trivial_except_copy_assign);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, trivial_except_move_ctor);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, trivial_except_move_assign);

BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, f1);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, f2);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, f3);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, mf1);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, mf2);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, mf3);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, mf4);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, mp);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(true, cmf);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, foo0_t);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, foo1_t);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, foo2_t);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, foo3_t);
BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST(false, foo4_t);

}	// namespace is_nothrow_copy_assignable_test

}	// namespace bksge_type_traits_test

#undef BKSGE_IS_NOTHROW_COPY_ASSIGNABLE_TEST
