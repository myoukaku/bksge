/**
 *	@file	unit_test_fnd_serialization_shared_ptr.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/shared_ptr.hpp>
#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace bksge_serialization_test
{

namespace shared_ptr_test
{

struct Foo
{
	Foo()
		: value1(0)
		, value2(0.0f)
	{
		s_count++;
	}

	Foo(int v1, float v2)
		: value1(v1)
		, value2(v2)
	{
		s_count++;
	}

	~Foo()
	{
		s_count--;
	}

	int value1;
	float value2;
	static int s_count;

private:
	friend class bksge::serialization::access;
	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar & BKSGE_SERIALIZATION_NVP(value1);
		ar & BKSGE_SERIALIZATION_NVP(value2);
	}
};

int Foo::s_count = 0;

template <typename Stream, typename OArchive, typename IArchive>
void SharedPtrTest()
{
	{
		EXPECT_EQ(0, Foo::s_count);

		Stream str;
		{
			bksge::shared_ptr<Foo> p(new Foo(2, 0.5f));

			EXPECT_EQ(1, Foo::s_count);
			{
				OArchive oa(str);
				oa << p;
			}
			EXPECT_EQ(1, Foo::s_count);
		}
		EXPECT_EQ(0, Foo::s_count);
		//EXPECT_STREQ("", str.str().c_str());
		{
			bksge::shared_ptr<Foo> tmp;
			{
				IArchive ia(str);
				ia >> tmp;
			}

			EXPECT_EQ(1, Foo::s_count);
			EXPECT_EQ(2, tmp->value1);
			EXPECT_EQ(0.5f, tmp->value2);
		}
		EXPECT_EQ(0, Foo::s_count);
	}
}

GTEST_TEST(SerializationTest, SharedPtrTest)
{
	using namespace bksge::serialization;

	SharedPtrTest<std::stringstream,  text_oarchive, text_iarchive>();
	SharedPtrTest<std::wstringstream, text_oarchive, text_iarchive>();
}

}	// namespace shared_ptr_test

}	// namespace bksge_serialization_test
