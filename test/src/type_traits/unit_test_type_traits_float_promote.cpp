/**
 *	@file	unit_test_type_traits_float_promote.cpp
 *
 *	@brief	float_promote のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/type_traits/float_promote.hpp>
#include <gtest/gtest.h>
#include <type_traits>

#define BKSGE_FLOAT_PROMOTE_TEST(T, ...)	\
	static_assert(std::is_same<T, bksge::float_promote<__VA_ARGS__>::type>::value, "");	\
	static_assert(std::is_same<T, bksge::float_promote_t<__VA_ARGS__>>::value, "")

GTEST_TEST(TypeTraitsTest, FloatPromoteTest)
{
	BKSGE_FLOAT_PROMOTE_TEST(float,			float);
	BKSGE_FLOAT_PROMOTE_TEST(double,		double);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	long double);
	BKSGE_FLOAT_PROMOTE_TEST(double,		int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		char);
	BKSGE_FLOAT_PROMOTE_TEST(double,		short);
	BKSGE_FLOAT_PROMOTE_TEST(double,		long);
	BKSGE_FLOAT_PROMOTE_TEST(double,		long long);
	BKSGE_FLOAT_PROMOTE_TEST(double,		unsigned int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		unsigned char);
	BKSGE_FLOAT_PROMOTE_TEST(double,		unsigned short);
	BKSGE_FLOAT_PROMOTE_TEST(double,		unsigned long);
	BKSGE_FLOAT_PROMOTE_TEST(double,		unsigned long long);

	BKSGE_FLOAT_PROMOTE_TEST(float,			float, float);
	BKSGE_FLOAT_PROMOTE_TEST(double,		float, double);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	float, long double);
	BKSGE_FLOAT_PROMOTE_TEST(double,		double, float);
	BKSGE_FLOAT_PROMOTE_TEST(double,		double, double);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	double, long double);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	long double, float);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	long double, double);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	long double, long double);

	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			char);
	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			float);
	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			double);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	int,			long double);
	BKSGE_FLOAT_PROMOTE_TEST(double,		float,			int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		float,			char);
	BKSGE_FLOAT_PROMOTE_TEST(double,		double,			int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		double,			char);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	long double,	int);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	long double,	char);

	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			int,			int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			int,			float);
	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			float,			int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			float,			float);
	BKSGE_FLOAT_PROMOTE_TEST(double,		float,			int,			int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		float,			int,			float);
	BKSGE_FLOAT_PROMOTE_TEST(double,		float,			float,			int);
	BKSGE_FLOAT_PROMOTE_TEST(float,			float,			float,			float);

	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			int,			double);
	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			double,			int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		int,			double,			double);
	BKSGE_FLOAT_PROMOTE_TEST(double,		double,			int,			int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		double,			int,			double);
	BKSGE_FLOAT_PROMOTE_TEST(double,		double,			double,			int);
	BKSGE_FLOAT_PROMOTE_TEST(double,		double,			double,			double);

	BKSGE_FLOAT_PROMOTE_TEST(long double,	int,			int,			long double);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	int,			long double,	int);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	int,			long double,	long double);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	long double,	int,			int);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	long double,	int,			long double);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	long double,	long double,	int);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	long double,	long double,	long double);

	BKSGE_FLOAT_PROMOTE_TEST(double,		float,			float,			double);
	BKSGE_FLOAT_PROMOTE_TEST(long double,	float,			float,			long double);
}

#undef BKSGE_FLOAT_PROMOTE_TEST
