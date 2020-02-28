/**
 *	@file	unit_test_fnd_type_traits_common_type.cpp
 *
 *	@brief	common_type のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <gtest/gtest.h>

GTEST_TEST(TypeTraitsTest, CommonTypeTest)
{
	struct A{};

	static_assert(bksge::is_same<bksge::common_type<A>::type, A>::value, "");
	static_assert(bksge::is_same<bksge::common_type<A, A>::type, A>::value, "");
	static_assert(bksge::is_same<bksge::common_type<A, A, A>::type, A>::value, "");
	static_assert(bksge::is_same<bksge::common_type<A, A, A, A>::type, A>::value, "");

	static_assert(bksge::is_same<bksge::common_type<int>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<char>::type, char>::value, "");

	static_assert(bksge::is_same<bksge::common_type<char, char>::type, char>::value, "");
	static_assert(bksge::is_same<bksge::common_type<char, unsigned char>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<char, short>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<char, unsigned short>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<char, int>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<char, unsigned int>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<char, long long>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<char, unsigned long long>::type, unsigned long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<char, double>::type, double>::value, "");

	static_assert(bksge::is_same<bksge::common_type<unsigned char, char>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned char, unsigned char>::type, unsigned char>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned char, short>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned char, unsigned short>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned char, int>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned char, unsigned int>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned char, long long>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned char, unsigned long long>::type, unsigned long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned char, double>::type, double>::value, "");

	static_assert(bksge::is_same<bksge::common_type<short, char>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<short, unsigned char>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<short, short>::type, short>::value, "");
	static_assert(bksge::is_same<bksge::common_type<short, unsigned short>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<short, int>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<short, unsigned int>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<short, long long>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<short, unsigned long long>::type, unsigned long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<short, double>::type, double>::value, "");

	static_assert(bksge::is_same<bksge::common_type<unsigned short, char>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned short, unsigned char>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned short, short>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned short, unsigned short>::type, unsigned short>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned short, int>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned short, unsigned int>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned short, long long>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned short, unsigned long long>::type, unsigned long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned short, double>::type, double>::value, "");

	static_assert(bksge::is_same<bksge::common_type<int, char>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<int, unsigned char>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<int, short>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<int, unsigned short>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<int, int>::type, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<int, unsigned int>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<int, long long>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<int, unsigned long long>::type, unsigned long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<int, double>::type, double>::value, "");

	static_assert(bksge::is_same<bksge::common_type<unsigned int, char>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned int, unsigned char>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned int, short>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned int, unsigned short>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned int, int>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned int, unsigned int>::type, unsigned int>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned int, long long>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned int, unsigned long long>::type, unsigned long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned int, double>::type, double>::value, "");

	static_assert(bksge::is_same<bksge::common_type<long long, char>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<long long, unsigned char>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<long long, short>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<long long, unsigned short>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<long long, int>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<long long, unsigned int>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<long long, long long>::type, long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<long long, unsigned long long>::type, unsigned long long>::value, "");
	static_assert(bksge::is_same<bksge::common_type<long long, double>::type, double>::value, "");

	static_assert(bksge::is_same<bksge::common_type<double, char>::type, double>::value, "");
	static_assert(bksge::is_same<bksge::common_type<double, unsigned char>::type, double>::value, "");
	static_assert(bksge::is_same<bksge::common_type<double, short>::type, double>::value, "");
	static_assert(bksge::is_same<bksge::common_type<double, unsigned short>::type, double>::value, "");
	static_assert(bksge::is_same<bksge::common_type<double, int>::type, double>::value, "");
	static_assert(bksge::is_same<bksge::common_type<double, unsigned int>::type, double>::value, "");
	static_assert(bksge::is_same<bksge::common_type<double, long long>::type, double>::value, "");
	static_assert(bksge::is_same<bksge::common_type<double, unsigned long long>::type, double>::value, "");
	static_assert(bksge::is_same<bksge::common_type<double, double>::type, double>::value, "");

	static_assert(bksge::is_same<bksge::common_type<double, char, int>::type, double>::value, "");
	static_assert(bksge::is_same<bksge::common_type<unsigned, char, long long>::type, long long>::value, "");

	// bksge::common_type_tのテスト
	static_assert(bksge::is_same<bksge::common_type_t<int>, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type_t<char>, char>::value, "");
	static_assert(bksge::is_same<bksge::common_type_t<char, char>, char>::value, "");
	static_assert(bksge::is_same<bksge::common_type_t<char, unsigned char>, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type_t<int, short>, int>::value, "");
	static_assert(bksge::is_same<bksge::common_type_t<double, char, int>, double>::value, "");
	static_assert(bksge::is_same<bksge::common_type_t<A>, A>::value, "");
	static_assert(bksge::is_same<bksge::common_type_t<A, A>, A>::value, "");
}
