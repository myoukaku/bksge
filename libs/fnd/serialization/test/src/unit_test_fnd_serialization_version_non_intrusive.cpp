/**
 *	@file	unit_test_fnd_serialization_version_non_intrusive.cpp
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

class VersionNonIntrusiveObject1
{
public:
	char   a = (char)get_random_int<short>();
	int    b = get_random_int<int>();
	float  c = get_random_float<float>();
};

inline bool
operator==(VersionNonIntrusiveObject1 const& lhs, VersionNonIntrusiveObject1 const& rhs)
{
	return
		lhs.a == rhs.a &&
		lhs.b == rhs.b &&
		lhs.c == rhs.c &&
		true;
}

inline bool
operator!=(VersionNonIntrusiveObject1 const& lhs, VersionNonIntrusiveObject1 const& rhs)
{
	return !(lhs == rhs);
}

template <typename Archive>
inline void
serialize(Archive& ar, VersionNonIntrusiveObject1& t, bksge::serialization::version_t version)
{
	EXPECT_EQ(0u, version);
	ar & t.a & t.b & t.c;
}

class VersionNonIntrusiveObject2
{
public:
	char   a = (char)get_random_int<short>();
	int    b = get_random_int<int>();
	float  c = get_random_float<float>();
};

inline bool
operator==(VersionNonIntrusiveObject2 const& lhs, VersionNonIntrusiveObject2 const& rhs)
{
	return
		lhs.a == rhs.a &&
		lhs.b == rhs.b &&
		lhs.c == rhs.c &&
		true;
}

inline bool
operator!=(VersionNonIntrusiveObject2 const& lhs, VersionNonIntrusiveObject2 const& rhs)
{
	return !(lhs == rhs);
}

template <typename Archive>
inline void
serialize(Archive& ar, VersionNonIntrusiveObject2& t, bksge::serialization::version_t version)
{
	EXPECT_EQ(5u, version);
	ar & t.a & t.b & t.c;
}

template <typename T, typename Stream, typename OArchive, typename IArchive>
void VersionNonIntrusiveTest()
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

GTEST_TEST(SerializationTest, VersionNonIntrusiveTest)
{
	VersionNonIntrusiveTest<
		VersionNonIntrusiveObject1,
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionNonIntrusiveTest<
		VersionNonIntrusiveObject2,
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionNonIntrusiveTest<
		VersionNonIntrusiveObject1,
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionNonIntrusiveTest<
		VersionNonIntrusiveObject2,
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test

BKSGE_SERIALIZATION_CLASS_VERSION(bksge_serialization_test::VersionNonIntrusiveObject2, 5);
