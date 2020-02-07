/**
 *	@file	unit_test_fnd_serialization_array.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/array.hpp>
#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <bksge/fnd/array/array.hpp>
#include <sstream>
#include <gtest/gtest.h>

namespace bksge_serialization_test
{

namespace array_test
{

template <typename Stream, typename OArchive, typename IArchive>
void ArrayTest()
{
	{
		bksge::array<int, 5> const value = {{1,2,3,4,5}};

		Stream str;
		{
			OArchive oa(str);
			oa << value;
		}
		//EXPECT_EQ("", str.str());
		{
			bksge::array<int, 5> tmp;
			IArchive ia(str);
			ia >> tmp;

			EXPECT_EQ(value, tmp);
		}
	}
	{
		bksge::array<float, 10> const value = {{3,1,4,1,5,9,2,6,5,3}};

		Stream str;
		{
			OArchive oa(str);
			oa << value;
		}
		//EXPECT_EQ("", str.str());
		{
			bksge::array<float, 10> tmp;
			IArchive ia(str);
			ia >> tmp;

			EXPECT_EQ(value, tmp);
		}
	}
}

GTEST_TEST(SerializationTest, ArrayTest)
{
	using namespace bksge::serialization;

	ArrayTest<std::stringstream,  text_oarchive, text_iarchive>();
	ArrayTest<std::wstringstream, text_oarchive, text_iarchive>();
}

}	// namespace array_test

}	// namespace bksge_serialization_test
