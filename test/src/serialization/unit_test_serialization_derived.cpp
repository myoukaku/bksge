/**
 *	@file	unit_test_serialization_derived.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/serialization/access.hpp>
#include <bksge/serialization/base_object.hpp>
#include <bksge/serialization/text_oarchive.hpp>
#include <bksge/serialization/text_iarchive.hpp>
#include <sstream>
#include <gtest/gtest.h>
#include "serialization_test_utility.hpp"

namespace bksge_serialization_test
{

class Base
{
public:
	bool equals(Base const& rhs) const
	{
		return
			a == rhs.a &&
			b == rhs.b;
	}

private:
	friend class bksge::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar & a & b;
	}

	int   a = get_random_int<int>();
	float b = get_random_float<float>();
};

class Derived : public Base
{
public:
	bool equals(Derived const& rhs) const
	{
		return Base::equals(rhs) &&
			c == rhs.c &&
			d == rhs.d &&
			e == rhs.e;
	}

private:
	friend class bksge::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar	& bksge::serialization::make_base_object<Base>(*this)
			& c
			& d
			& e;
	}

	char   c = (char)get_random_int<short>();
	bool   d = get_random_bool();
	double e = get_random_float<double>();
};

inline bool operator==(Derived const& lhs, Derived const& rhs)
{
	return lhs.equals(rhs);
}

inline bool operator!=(Derived const& lhs, Derived const& rhs)
{
	return !(lhs == rhs);
}

template <typename Stream, typename OArchive, typename IArchive>
void DerivedTest()
{
	using T = Derived;

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

GTEST_TEST(SerializationTest, DerivedTest)
{
	DerivedTest<
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	DerivedTest<
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test
