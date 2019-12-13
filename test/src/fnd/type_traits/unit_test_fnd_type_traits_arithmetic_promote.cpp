/**
 *	@file	unit_test_fnd_type_traits_arithmetic_promote.cpp
 *
 *	@brief	arithmetic_promote のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/type_traits/arithmetic_promote.hpp>
#include <gtest/gtest.h>
#include <type_traits>

GTEST_TEST(TypeTraitsTest, ArithmeticPromoteTest)
{
#define BKSGE_ARITHMETIC_PROMOTE_TEST(T, ...)	\
	static_assert(std::is_same<T, bksge::arithmetic_promote<__VA_ARGS__>::type>::value, "");	\
	static_assert(std::is_same<T, bksge::arithmetic_promote_t<__VA_ARGS__>>::value, "")

	BKSGE_ARITHMETIC_PROMOTE_TEST(float,				float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,				double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,					int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(char,					char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(short,				short);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long,					long);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long long,			long long);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned int,			unsigned int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned char,		unsigned char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned short,		unsigned short);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned long,		unsigned long);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned long long,	unsigned long long);

	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		float,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			unsigned int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			unsigned char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			unsigned int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			unsigned char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	unsigned int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	unsigned char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		int,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		int,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			int,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			int,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned int,	int,			unsigned int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			int,			unsigned char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		char,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		char,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			char,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			char,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned int,	char,			unsigned int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			char,			unsigned char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		unsigned int,	float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		unsigned int,	double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	unsigned int,	long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned int, unsigned int,	int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned int,	unsigned int,	char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned int,	unsigned int,	unsigned int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned int,	unsigned int,	unsigned char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		unsigned char,	float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		unsigned char,	double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	unsigned char,	long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			unsigned char,	int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			unsigned char,	char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(unsigned int,	unsigned char,	unsigned int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			unsigned char,	unsigned char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			float,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		float,			float,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	float,			float,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			float,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			float,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		float,			double,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		float,			double,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	float,			double,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		float,			double,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		float,			double,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double,	float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double,	double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double,	long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double,	int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	float,			long double,	char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			int,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		float,			int,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	float,			int,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			int,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			int,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			char,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		float,			char,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	float,			char,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			char,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		float,			char,			char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			float,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			float,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	double,			float,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			float,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			float,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			double,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			double,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	double,			double,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			double,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			double,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double,	float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double,	double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double,	long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double,	int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	double,			long double,	char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			int,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			int,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	double,			int,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			int,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			int,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			char,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			char,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	double,			char,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			char,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		double,			char,			char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	float,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	double,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double,	float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double,	double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double,	long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double,	int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	long double,	char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	int,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	long double,	char,			char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		int,			float,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		int,			float,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	int,			float,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		int,			float,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		int,			float,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		int,			double,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		int,			double,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	int,			double,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		int,			double,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		int,			double,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double,	float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double,	double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double,	long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double,	int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	int,			long double,	char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		int,			int,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		int,			int,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	int,			int,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			int,			int,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			int,			int,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		int,			char,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		int,			char,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	int,			char,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			int,			char,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			int,			char,			char);

	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		char,			float,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		char,			float,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	char,			float,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		char,			float,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		char,			float,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		char,			double,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		char,			double,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	char,			double,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		char,			double,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		char,			double,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double,	float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double,	double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double,	long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double,	int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	char,			long double,	char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		char,			int,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		char,			int,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	char,			int,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			char,			int,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			char,			int,			char);
	BKSGE_ARITHMETIC_PROMOTE_TEST(float,		char,			char,			float);
	BKSGE_ARITHMETIC_PROMOTE_TEST(double,		char,			char,			double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(long double,	char,			char,			long double);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			char,			char,			int);
	BKSGE_ARITHMETIC_PROMOTE_TEST(int,			char,			char,			char);

#undef BKSGE_ARITHMETIC_PROMOTE_TEST
}
