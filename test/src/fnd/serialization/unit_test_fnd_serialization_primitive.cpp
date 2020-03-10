/**
 *	@file	unit_test_fnd_serialization_primitive.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <gtest/gtest.h>
#include "serialization_test_utility.hpp"

namespace bksge_serialization_test
{

template <typename Stream, typename OArchive, typename IArchive>
void PrimitiveTest()
{
	enum Enum { One, Two, Three };

	char               a = (char)get_random_int<short>();
	signed char        b = (signed char)get_random_int<signed short>();
	unsigned char      c = (unsigned char)get_random_int<unsigned short>();
	short              d = get_random_int<short>();
	unsigned short     e = get_random_int<unsigned short>();
	int                f = get_random_int<int>();
	unsigned int       g = get_random_int<unsigned int>();
	long               h = get_random_int<long>();
	unsigned long      i = get_random_int<unsigned long>();
	long long          j = get_random_int<long long>();
	unsigned long long k = get_random_int<unsigned long long>();
	wchar_t            l = (wchar_t)get_random_int<unsigned int>();
	bool               m = get_random_bool();
	float              n = get_random_float<float>();
	double             o = get_random_float<double>();
	long double        p = get_random_float<long double>();
	Enum               q = Enum(get_random_int<unsigned int>() % 3);
	bksge::size_t      r = get_random_int<bksge::size_t>();
	bksge::nullptr_t   s = nullptr;

	Stream str;
	{
		OArchive oa(str);
		oa	<< a
			<< b
			<< c
			<< d
			<< e
			<< f
			<< g
			<< h
			<< i
			<< j
			<< k
			<< l
			<< m
			<< n
			<< o
			<< p
			<< q
			<< r
			<< s;
	}
	{
		char               a_2;
		signed char        b_2;
		unsigned char      c_2;
		short              d_2;
		unsigned short     e_2;
		int                f_2;
		unsigned int       g_2;
		long               h_2;
		unsigned long      i_2;
		long long          j_2;
		unsigned long long k_2;
		wchar_t            l_2;
		bool               m_2;
		float              n_2;
		double             o_2;
		long double        p_2;
		Enum               q_2;
		bksge::size_t      r_2;
		bksge::nullptr_t   s_2;

		IArchive ia(str);
		
		ia	>> a_2
			>> b_2
			>> c_2
			>> d_2
			>> e_2
			>> f_2
			>> g_2
			>> h_2
			>> i_2
			>> j_2
			>> k_2
			>> l_2
			>> m_2
			>> n_2
			>> o_2
			>> p_2
			>> q_2
			>> r_2
			>> s_2;

		EXPECT_EQ(a, a_2);
		EXPECT_EQ(b, b_2);
		EXPECT_EQ(c, c_2);
		EXPECT_EQ(d, d_2);
		EXPECT_EQ(e, e_2);
		EXPECT_EQ(f, f_2);
		EXPECT_EQ(g, g_2);
		EXPECT_EQ(h, h_2);
		EXPECT_EQ(i, i_2);
		EXPECT_EQ(j, j_2);
		EXPECT_EQ(k, k_2);
		EXPECT_EQ(l, l_2);
		EXPECT_EQ(m, m_2);
		EXPECT_EQ(n, n_2);
		EXPECT_EQ(o, o_2);
		EXPECT_EQ(p, p_2);
		EXPECT_EQ(q, q_2);
		EXPECT_EQ(r, r_2);
		EXPECT_EQ(s, s_2);
	}
}

GTEST_TEST(SerializationTest, PrimitiveTest)
{
	PrimitiveTest<
		bksge::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	PrimitiveTest<
		bksge::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test
