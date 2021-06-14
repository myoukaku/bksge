/**
 *	@file	unit_test_fnd_type_traits_underlying_type.cpp
 *
 *	@brief	underlying_type のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace bksge_type_traits_test
{

namespace underlying_type_test
{

#define BKSGE_UNDERLYING_TYPE_TEST(T1, T2)	\
	static_assert(bksge::is_same<bksge::underlying_type<T1>::type, T2>::value, "");	\
	static_assert(bksge::is_same<bksge::underlying_type_t<T1>, T2>::value, "")

enum       E1 : char {};
enum class E2 : signed char {};
enum       E3 : unsigned char {};
enum class E4 : wchar_t {};
enum       E5 : int {};
enum class E6 : short {};
enum       E7 : long {};
enum class E8 : long long {};
enum       E9 : unsigned int {};
enum class E10 : unsigned short {};
enum       E11 : unsigned long {};
enum class E12 : unsigned long long {};
enum       E13 : bksge::size_t {};

//BKSGE_UNDERLYING_TYPE_TEST(enum_UDT, unsigned int);	// 実装依存
BKSGE_UNDERLYING_TYPE_TEST(enum_uint32_t_UDT, bksge::uint32_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_uint16_t_UDT, bksge::uint16_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_uint8_t_UDT,  bksge::uint8_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_int32_t_UDT,  bksge::int32_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_int16_t_UDT,  bksge::int16_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_int8_t_UDT,   bksge::int8_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_class_UDT, int);
BKSGE_UNDERLYING_TYPE_TEST(enum_class_uint32_t_UDT, bksge::uint32_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_class_uint16_t_UDT, bksge::uint16_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_class_uint8_t_UDT,  bksge::uint8_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_class_int32_t_UDT,  bksge::int32_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_class_int16_t_UDT,  bksge::int16_t);
BKSGE_UNDERLYING_TYPE_TEST(enum_class_int8_t_UDT,   bksge::int8_t);

BKSGE_UNDERLYING_TYPE_TEST(E1, char);
BKSGE_UNDERLYING_TYPE_TEST(E2, signed char);
BKSGE_UNDERLYING_TYPE_TEST(E3, unsigned char);
BKSGE_UNDERLYING_TYPE_TEST(E4, wchar_t);
BKSGE_UNDERLYING_TYPE_TEST(E5, int);
BKSGE_UNDERLYING_TYPE_TEST(E6, short);
BKSGE_UNDERLYING_TYPE_TEST(E7, long);
BKSGE_UNDERLYING_TYPE_TEST(E8, long long);
BKSGE_UNDERLYING_TYPE_TEST(E9, unsigned int);
BKSGE_UNDERLYING_TYPE_TEST(E10, unsigned short);
BKSGE_UNDERLYING_TYPE_TEST(E11, unsigned long);
BKSGE_UNDERLYING_TYPE_TEST(E12, unsigned long long);
BKSGE_UNDERLYING_TYPE_TEST(E13, bksge::size_t);

#undef BKSGE_UNDERLYING_TYPE_TEST

}	// namespace underlying_type_test

}	// namespace bksge_type_traits_test
