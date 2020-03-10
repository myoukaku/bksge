/**
 *	@file	unit_test_fnd_serialization_pointer.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <bksge/fnd/sstream/stringstream.hpp>
#include <bksge/fnd/sstream/wstringstream.hpp>
#include <gtest/gtest.h>
#include "serialization_test_utility.hpp"

namespace bksge_serialization_test
{

class PointerObject
{
	struct Internal
	{
		int                a = get_random_int<int>();
		unsigned long long b = get_random_int<unsigned long long>();
		double             c = get_random_float<double>();
		int*               d = nullptr;

		~Internal()
		{
			delete d;
		}

		void init()
		{
			d = new int(get_random_int<int>());
		}

		bool operator==(Internal const& rhs) const
		{
			return
				a == rhs.a &&
				b == rhs.b &&
				c == rhs.c &&
				*d == *rhs.d;
		}

		template <typename Archive>
		void serialize(Archive& ar)
		{
			ar	& BKSGE_SERIALIZATION_NVP(a);
			ar	& BKSGE_SERIALIZATION_NVP(b);
			ar	& BKSGE_SERIALIZATION_NVP(c);
			ar	& BKSGE_SERIALIZATION_NVP(d);
		}
	};

public:
	PointerObject() {}

	~PointerObject()
	{
		delete b;
		delete d;
	}

	void init()
	{
		a = get_random_int<int>();
		a_1 = &a;
		a_2 = &a;
		a_1_1 = &a_1;

		b = new int(get_random_int<int>());
		b_1 = b;
		b_2 = b;

		c = nullptr;

		d = new float(get_random_float<float>());
		d_1 = &d;
		d_1_1 = &d_1;

		e = new Internal();
		e->init();
	}

	void test(PointerObject const& rhs) const
	{
		EXPECT_TRUE(a == rhs.a);
		EXPECT_TRUE(*a_1 == *rhs.a_1);
		EXPECT_TRUE(*a_2 == *rhs.a_2);
		EXPECT_TRUE(**a_1_1 == **rhs.a_1_1);

		EXPECT_TRUE(a == *a_1);
		EXPECT_TRUE(a == *a_2);
		EXPECT_TRUE(a_1 == &a);
		EXPECT_TRUE(a_2 == &a);
		EXPECT_TRUE(*a_1_1 == &a);

		EXPECT_TRUE(rhs.a == *rhs.a_1);
		EXPECT_TRUE(rhs.a == *rhs.a_2);
		EXPECT_TRUE(rhs.a_1 == &rhs.a);
		EXPECT_TRUE(rhs.a_2 == &rhs.a);
		EXPECT_TRUE(*rhs.a_1_1 == &rhs.a);

		EXPECT_EQ(*b, *rhs.b);
		EXPECT_EQ(*b_1, *rhs.b_1);
		EXPECT_EQ(*b_2, *rhs.b_2);
		
		EXPECT_TRUE(b == b_1);
		EXPECT_TRUE(b == b_2);
		EXPECT_TRUE(b_1 == b_2);

		EXPECT_TRUE(rhs.b == rhs.b_1);
		EXPECT_TRUE(rhs.b == rhs.b_2);
		EXPECT_TRUE(rhs.b_1 == rhs.b_2);

		EXPECT_TRUE(c == nullptr);
		EXPECT_TRUE(rhs.c == nullptr);

		EXPECT_TRUE(*d == *rhs.d);

		EXPECT_TRUE(d_1 == &d);
		EXPECT_TRUE(d_1_1 == &d_1);

		EXPECT_TRUE(rhs.d_1 == &rhs.d);
		EXPECT_TRUE(rhs.d_1_1 == &rhs.d_1);

		EXPECT_TRUE(*e == *rhs.e);
	}

private:
	int        a     = 0;
	int*       a_1   = nullptr;
	const int* a_2   = nullptr;
	int**      a_1_1 = nullptr;

	int*       b     = nullptr;
	const int* b_1   = nullptr;
	int*       b_2   = nullptr;

	int*       c     = &a;

	float*     d     = nullptr;
	float**    d_1   = nullptr;
	float***   d_1_1 = nullptr;

	Internal*  e     = nullptr;

	friend class bksge::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar & BKSGE_SERIALIZATION_NVP(a_1);
		ar & BKSGE_SERIALIZATION_NVP(a);
		ar & BKSGE_SERIALIZATION_NVP(a_2);
		ar & BKSGE_SERIALIZATION_NVP(a_1_1);
		ar & BKSGE_SERIALIZATION_NVP(b_1);
		ar & BKSGE_SERIALIZATION_NVP(b);
		ar & BKSGE_SERIALIZATION_NVP(b_2);
		ar & BKSGE_SERIALIZATION_NVP(c);
		ar & BKSGE_SERIALIZATION_NVP(d);
		ar & BKSGE_SERIALIZATION_NVP(d_1);
		ar & BKSGE_SERIALIZATION_NVP(d_1_1);
		ar & BKSGE_SERIALIZATION_NVP(e);
	}
};

template <typename Stream, typename OArchive, typename IArchive>
void PointerTest()
{
	using T = PointerObject;

	T* value = new T();
	value->init();

	Stream str;
	{
		OArchive oa(str);
		oa << BKSGE_SERIALIZATION_NVP(value);
	}
//	EXPECT_STREQ("", str.str().c_str());
	{
		T* tmp;
		{
			IArchive ia(str);
			ia >> BKSGE_SERIALIZATION_NVP(tmp);
		}
		value->test(*tmp);

		delete tmp;
	}
	delete value;
}

GTEST_TEST(SerializationTest, PointerTest)
{
	PointerTest<
		bksge::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	PointerTest<
		bksge::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test
