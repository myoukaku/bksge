/**
 *	@file	unit_test_fnd_serialization_vector.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/vector.hpp>
#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <sstream>
#include <bksge/fnd/vector.hpp>
#include <gtest/gtest.h>

namespace bksge_serialization_test
{

namespace vector_test
{

struct Point
{
	float x;
	float y;

private:
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar, bksge::serialization::version_t /*version*/)
	{
		ar & x;
		ar & y;
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void VectorTest()
{
	{
		bksge::vector<int> const value = {1,2,3,4,5};

		Stream str;
		{
			OArchive oa(str);
			oa << value;
		}
		{
			bksge::vector<int> tmp;
			IArchive ia(str);
			ia >> tmp;

			EXPECT_EQ(5u, tmp.size());
			EXPECT_EQ(1, tmp[0]);
			EXPECT_EQ(2, tmp[1]);
			EXPECT_EQ(3, tmp[2]);
			EXPECT_EQ(4, tmp[3]);
			EXPECT_EQ(5, tmp[4]);
		}
	}
	{
		bksge::vector<Point> const value =
		{
			{ 0.5f, 1.5f },
			{ 2.5f,-3.5f },
		};

		Stream str;
		{
			OArchive oa(str);
			oa << value;
		}
		{
			bksge::vector<Point> tmp;
			IArchive ia(str);
			ia >> tmp;

			EXPECT_EQ(2u, tmp.size());
			EXPECT_EQ( 0.5f, tmp[0].x);
			EXPECT_EQ( 1.5f, tmp[0].y);
			EXPECT_EQ( 2.5f, tmp[1].x);
			EXPECT_EQ(-3.5f, tmp[1].y);
		}
	}
}

GTEST_TEST(SerializationTest, VectorTest)
{
	VectorTest<
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	VectorTest<
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace vector_test

}	// namespace bksge_serialization_test
