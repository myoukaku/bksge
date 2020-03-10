/**
 *	@file	unit_test_fnd_serialization_string.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/string.hpp>
#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <string>
#include <gtest/gtest.h>

namespace bksge_serialization_test
{

namespace string_test
{

template <typename Stream, typename OArchive, typename IArchive>
void StringTest()
{
	{
		std::string const value = "The quick brown fox jumps over the lazy dog.";

		Stream str;
		{
			OArchive oa(str);
			oa << value;
		}
		//EXPECT_EQ("", str.str());
		{
			std::string tmp;
			IArchive ia(str);
			ia >> tmp;

			EXPECT_EQ(value, tmp);
		}
	}
	{
		std::wstring const value = L"Jackdaws love my big sphinx of quartz.";

		Stream str;
		{
			OArchive oa(str);
			oa << value;
		}
		//EXPECT_EQ("", str.str());
		{
			std::wstring tmp;
			IArchive ia(str);
			ia >> tmp;

			EXPECT_EQ(value, tmp);
		}
	}
}

GTEST_TEST(SerializationTest, StringTest)
{
	StringTest<
		bksge::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	StringTest<
		bksge::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace string_test

}	// namespace bksge_serialization_test
