/**
 *	@file	unit_test_fnd_serialization_nvp.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "serialization_test_utility.hpp"

namespace bksge_serialization_test
{

class NvpObject
{
private:
	char  a = (char)get_random_int<short>();
	int   b = get_random_int<int>();
	float c = get_random_float<float>();

	friend bool operator==(NvpObject const& lhs, NvpObject const& rhs)
	{
		return
			lhs.a == rhs.a &&
			lhs.b == rhs.b &&
			lhs.c == rhs.c &&
			true;
	}

	friend bool operator!=(NvpObject const& lhs, NvpObject const& rhs)
	{
		return !(lhs == rhs);
	}

	friend class bksge::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar	& BKSGE_SERIALIZATION_NVP(a)
			& BKSGE_SERIALIZATION_NVP(b)
			& BKSGE_SERIALIZATION_NVP(c);
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void NvpTest()
{
	using T = NvpObject;

	T value;
	Stream str;
	{
		OArchive oa(str);
		oa << bksge::serialization::make_nvp("value", value);
	}
	//EXPECT_EQ("", str.str());
	{
		T tmp;
		EXPECT_NE(value, tmp);

		IArchive ia(str);
		ia >> bksge::serialization::make_nvp("value", tmp);

		EXPECT_EQ(value, tmp);
	}
}

GTEST_TEST(SerializationTest, NvpTest)
{
	NvpTest<
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	NvpTest<
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test
