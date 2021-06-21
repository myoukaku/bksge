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
#include <bksge/fnd/string/string.hpp>
#include <bksge/fnd/string/wstring.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_serialization_test
{

namespace string_test
{

template <typename Stream, typename OArchive, typename IArchive>
void StringTest()
{
	{
		bksge::string const value = "The quick brown fox jumps over the lazy dog.";

		Stream str;
		{
			OArchive oa(str);
			oa << value;
		}
		//EXPECT_EQ("", str.str());
		{
			bksge::string tmp;
			IArchive ia(str);
			ia >> tmp;

			EXPECT_EQ(value, tmp);
		}
	}
	{
		bksge::wstring const value = L"Jackdaws love my big sphinx of quartz.";

		Stream str;
		{
			OArchive oa(str);
			oa << value;
		}
		//EXPECT_EQ("", str.str());
		{
			bksge::wstring tmp;
			IArchive ia(str);
			ia >> tmp;

			EXPECT_EQ(value, tmp);
		}
	}
}

GTEST_TEST(SerializationTest, StringTest)
{
	using namespace bksge::serialization;

	StringTest<std::stringstream,  text_oarchive, text_iarchive>();
	StringTest<std::wstringstream, text_oarchive, text_iarchive>();
}

}	// namespace string_test

}	// namespace bksge_serialization_test
