/**
 *	@file	unit_test_fnd_serialization_native_array.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <sstream>
#include <gtest/gtest.h>
#include "serialization_test_utility.hpp"

namespace bksge_serialization_test
{

template <typename Stream, typename OArchive, typename IArchive>
void NativeArray()
{
	{
		int value[5] = {1,2,3,4,5};

		Stream str;
		{
			OArchive oa(str);
			oa << value;
		}
		{
			int tmp[5];
			IArchive ia(str);
			ia >> tmp;

			EXPECT_EQ(1, tmp[0]);
			EXPECT_EQ(2, tmp[1]);
			EXPECT_EQ(3, tmp[2]);
			EXPECT_EQ(4, tmp[3]);
			EXPECT_EQ(5, tmp[4]);
		}
	}
	{
		char value[2][3] =
		{
			{10, 11, 12},
			{20, 21, 22},
		};

		Stream str;
		{
			OArchive oa(str);
			oa << value;
		}
		{
			int tmp[2][3];
			IArchive ia(str);
			ia >> tmp;

			EXPECT_EQ(10, tmp[0][0]);
			EXPECT_EQ(11, tmp[0][1]);
			EXPECT_EQ(12, tmp[0][2]);
			EXPECT_EQ(20, tmp[1][0]);
			EXPECT_EQ(21, tmp[1][1]);
			EXPECT_EQ(22, tmp[1][2]);
		}
	}
}

GTEST_TEST(SerializationTest, NativeArray)
{
	NativeArray<
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	NativeArray<
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test
