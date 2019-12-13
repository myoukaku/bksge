/**
 *	@file	unit_test_fnd_serialization_version_non_intrusive_split.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <sstream>
#include <gtest/gtest.h>
#include "serialization_test_utility.hpp"

namespace bksge_serialization_test
{

class VersionNonIntrusiveSplitObject1
{
public:
	char   a = (char)get_random_int<short>();
	int    b = get_random_int<int>();
	float  c = get_random_float<float>();
};

inline bool
operator==(VersionNonIntrusiveSplitObject1 const& lhs, VersionNonIntrusiveSplitObject1 const& rhs)
{
	return
		lhs.a == rhs.a &&
		lhs.b == rhs.b &&
		lhs.c == rhs.c &&
		true;
}

inline bool
operator!=(VersionNonIntrusiveSplitObject1 const& lhs, VersionNonIntrusiveSplitObject1 const& rhs)
{
	return !(lhs == rhs);
}

template <typename Archive>
inline void
save(Archive& ar, VersionNonIntrusiveSplitObject1 const& t, bksge::serialization::version_t version)
{
	EXPECT_EQ(0u, version);
	ar << t.a << t.b << t.c;
}

template <typename Archive>
inline void
load(Archive& ar, VersionNonIntrusiveSplitObject1& t, bksge::serialization::version_t version)
{
	EXPECT_EQ(0u, version);
	ar >> t.a >> t.b >> t.c;
}

class VersionNonIntrusiveSplitObject2
{
public:
	char   a = (char)get_random_int<short>();
	int    b = get_random_int<int>();
	float  c = get_random_float<float>();
};

inline bool
operator==(VersionNonIntrusiveSplitObject2 const& lhs, VersionNonIntrusiveSplitObject2 const& rhs)
{
	return
		lhs.a == rhs.a &&
		lhs.b == rhs.b &&
		lhs.c == rhs.c &&
		true;
}

inline bool
operator!=(VersionNonIntrusiveSplitObject2 const& lhs, VersionNonIntrusiveSplitObject2 const& rhs)
{
	return !(lhs == rhs);
}

template <typename Archive>
inline void
save(Archive& ar, VersionNonIntrusiveSplitObject2 const& t, bksge::serialization::version_t version)
{
	EXPECT_EQ(6u, version);
	ar << t.a << t.b << t.c;
}

template <typename Archive>
inline void
load(Archive& ar, VersionNonIntrusiveSplitObject2& t, bksge::serialization::version_t version)
{
	EXPECT_EQ(6u, version);
	ar >> t.a >> t.b >> t.c;
}

template <typename T, typename Stream, typename OArchive, typename IArchive>
void VersionNonIntrusiveSplitTest()
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

GTEST_TEST(SerializationTest, VersionNonIntrusiveSplitTest)
{
	VersionNonIntrusiveSplitTest<
		VersionNonIntrusiveSplitObject1,
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionNonIntrusiveSplitTest<
		VersionNonIntrusiveSplitObject2,
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionNonIntrusiveSplitTest<
		VersionNonIntrusiveSplitObject1,
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VersionNonIntrusiveSplitTest<
		VersionNonIntrusiveSplitObject2,
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test

BKSGE_SERIALIZATION_CLASS_VERSION(bksge_serialization_test::VersionNonIntrusiveSplitObject2, 6);
