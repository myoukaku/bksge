/**
 *	@file	unit_test_fnd_serialization_object_non_intrusive.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <gtest/gtest.h>
#include "serialization_test_utility.hpp"

namespace bksge_serialization_test
{

class NonIntrusiveObject
{
public:
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
};

inline bool
operator==(NonIntrusiveObject const& lhs, NonIntrusiveObject const& rhs)
{
	return
		lhs.a == rhs.a &&
		lhs.b == rhs.b &&
		lhs.c == rhs.c &&
		lhs.d == rhs.d &&
		lhs.e == rhs.e &&
		lhs.f == rhs.f &&
		lhs.g == rhs.g &&
		lhs.h == rhs.h &&
		lhs.i == rhs.i &&
		lhs.j == rhs.j &&
		lhs.k == rhs.k &&
		lhs.l == rhs.l &&
		lhs.m == rhs.m &&
		lhs.n == rhs.n &&
		lhs.o == rhs.o &&
		lhs.p == rhs.p &&
		lhs.q == rhs.q &&
		lhs.r == rhs.r &&
		lhs.s == rhs.s &&
		true;
}

inline bool
operator!=(NonIntrusiveObject const& lhs, NonIntrusiveObject const& rhs)
{
	return !(lhs == rhs);
}

template <typename Archive>
inline void
serialize(Archive& ar, NonIntrusiveObject& a)
{
	ar & a.a;
	ar & a.b;
	ar & a.c;
	ar & a.d;
	ar & a.e;
	ar & a.f;
	ar & a.g;
	ar & a.h;
	ar & a.i;
	ar & a.j;
	ar & a.k;
	ar & a.l;
	ar & a.m;
	ar & a.n;
	ar & a.o;
	ar & a.p;
	ar & a.q;
	ar & a.r;
	ar & a.s;
}

template <typename Stream, typename OArchive, typename IArchive>
inline void
ObjectNonIntrusiveTest()
{
	using T = NonIntrusiveObject;

	T value;
	Stream str;
	{
		OArchive oa(str);
		oa << value;
	}
	//EXPECT_EQ("", str.str());
	{
		T tmp;
		EXPECT_NE(value, tmp);

		IArchive ia(str);
		ia >> tmp;

		EXPECT_EQ(value, tmp);
	}
}

GTEST_TEST(SerializationTest, ObjectNonIntrusiveTest)
{
	ObjectNonIntrusiveTest<
		bksge::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	ObjectNonIntrusiveTest<
		bksge::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test
