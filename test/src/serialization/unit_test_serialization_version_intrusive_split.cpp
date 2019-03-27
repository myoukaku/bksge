/**
 *	@file	unit_test_serialization_version_intrusive_split.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/serialization/version.hpp>
#include <bksge/serialization/access.hpp>
#include <bksge/serialization/text_oarchive.hpp>
#include <bksge/serialization/text_iarchive.hpp>
#include <sstream>
#include <gtest/gtest.h>
#include "serialization_test_utility.hpp"

namespace bksge_serialization_test
{

class VersionIntrusiveSplitObject1
{
private:
	char   a = (char)get_random_int<short>();
	int    b = get_random_int<int>();
	float  c = get_random_float<float>();

	friend bool operator==(VersionIntrusiveSplitObject1 const& lhs, VersionIntrusiveSplitObject1 const& rhs)
	{
		return
			lhs.a == rhs.a &&
			lhs.b == rhs.b &&
			lhs.c == rhs.c &&
			true;
	}

	friend bool operator!=(VersionIntrusiveSplitObject1 const& lhs, VersionIntrusiveSplitObject1 const& rhs)
	{
		return !(lhs == rhs);
	}

	friend class bksge::serialization::access;

	template <typename Archive>
	void save(Archive& ar, bksge::serialization::version_t version) const
	{
		EXPECT_EQ(0u, version);
		ar << a << b << c;
	}

	template <typename Archive>
	void load(Archive& ar, bksge::serialization::version_t version)
	{
		EXPECT_EQ(0u, version);
		ar >> a >> b >> c;
	}
};

class VersionIntrusiveSplitObject2
{
private:
	char   a = (char)get_random_int<short>();
	int    b = get_random_int<int>();
	float  c = get_random_float<float>();

	friend bool operator==(VersionIntrusiveSplitObject2 const& lhs, VersionIntrusiveSplitObject2 const& rhs)
	{
		return
			lhs.a == rhs.a &&
			lhs.b == rhs.b &&
			lhs.c == rhs.c &&
			true;
	}

	friend bool operator!=(VersionIntrusiveSplitObject2 const& lhs, VersionIntrusiveSplitObject2 const& rhs)
	{
		return !(lhs == rhs);
	}

	friend class bksge::serialization::access;

	template <typename Archive>
	void save(Archive& ar, bksge::serialization::version_t version) const
	{
		EXPECT_EQ(4u, version);
		ar << a << b << c;
	}

	template <typename Archive>
	void load(Archive& ar, bksge::serialization::version_t version)
	{
		EXPECT_EQ(4u, version);
		ar >> a >> b >> c;
	}
};

template <typename T, typename Stream, typename OArchive, typename IArchive>
void VersionIntrusiveSplitTest()
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

GTEST_TEST(SerializationTest, VersionIntrusiveSplitTest)
{
	VersionIntrusiveSplitTest<
		VersionIntrusiveSplitObject1,
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionIntrusiveSplitTest<
		VersionIntrusiveSplitObject2,
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionIntrusiveSplitTest<
		VersionIntrusiveSplitObject1,
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionIntrusiveSplitTest<
		VersionIntrusiveSplitObject2,
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test

BKSGE_SERIALIZATION_CLASS_VERSION(bksge_serialization_test::VersionIntrusiveSplitObject2, 4);
