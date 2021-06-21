/**
 *	@file	unit_test_fnd_serialization_version_intrusive.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialization_test_utility.hpp"

namespace bksge_serialization_test
{

class VersionIntrusiveObject1
{
private:
	char   a = (char)get_random_int<short>();
	int    b = get_random_int<int>();
	float  c = get_random_float<float>();

	friend bool operator==(VersionIntrusiveObject1 const& lhs, VersionIntrusiveObject1 const& rhs)
	{
		return
			lhs.a == rhs.a &&
			lhs.b == rhs.b &&
			lhs.c == rhs.c &&
			true;
	}

	friend bool operator!=(VersionIntrusiveObject1 const& lhs, VersionIntrusiveObject1 const& rhs)
	{
		return !(lhs == rhs);
	}

	friend class bksge::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t version)
	{
		EXPECT_EQ(0u, version);
		ar & a & b & c;
	}
};

class VersionIntrusiveObject2
{
private:
	char   a = (char)get_random_int<short>();
	int    b = get_random_int<int>();
	float  c = get_random_float<float>();

	friend bool operator==(VersionIntrusiveObject2 const& lhs, VersionIntrusiveObject2 const& rhs)
	{
		return
			lhs.a == rhs.a &&
			lhs.b == rhs.b &&
			lhs.c == rhs.c &&
			true;
	}

	friend bool operator!=(VersionIntrusiveObject2 const& lhs, VersionIntrusiveObject2 const& rhs)
	{
		return !(lhs == rhs);
	}

	friend class bksge::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t version)
	{
		EXPECT_EQ(3u, version);
		ar & a & b & c;
	}
};

template <typename T, typename Stream, typename OArchive, typename IArchive>
void VersionIntrusiveTest()
{
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

GTEST_TEST(SerializationTest, VersionIntrusiveTest)
{
	VersionIntrusiveTest<
		VersionIntrusiveObject1,
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionIntrusiveTest<
		VersionIntrusiveObject2,
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionIntrusiveTest<
		VersionIntrusiveObject1,
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionIntrusiveTest<
		VersionIntrusiveObject2,
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test

BKSGE_SERIALIZATION_CLASS_VERSION(bksge_serialization_test::VersionIntrusiveObject2, 3);
