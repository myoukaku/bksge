/**
 *	@file	unit_test_serialization_native_array_non_intrusive_split.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/serialization/text_oarchive.hpp>
#include <bksge/serialization/text_iarchive.hpp>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <gtest/gtest.h>
#include "serialization_test_utility.hpp"

namespace bksge_serialization_test
{

struct NativeArrayNonIntrusiveSplit
{
	enum Enum { One, Two, Three };

	NativeArrayNonIntrusiveSplit()
	{
		for (auto& x : a)
		{
			x = get_random_int<int>();
		}
		for (auto& x : b)
		{
			x = get_random_float<float>();
		}
		for (auto& x : c)
		{
			for (auto& y : x)
			{
				y = (char)get_random_int<short>();
			}
		}
		for (auto& x : d)
		{
			for (auto& y : x)
			{
				for (auto& z : y)
				{
					z = get_random_bool();
				}
			}
		}
		for (auto& x : e)
		{
			x = Enum(get_random_int<unsigned int>() % 3);
		}
	}

	int   a[2];
	float b[3];
	char  c[3][2];
	bool  d[2][3][4];
	Enum  e[4];
};

inline bool
operator==(NativeArrayNonIntrusiveSplit const& lhs, NativeArrayNonIntrusiveSplit const& rhs)
{
	return
		std::equal(std::begin(lhs.a), std::end(lhs.a), std::begin(rhs.a)) &&
		std::equal(std::begin(lhs.b), std::end(lhs.b), std::begin(rhs.b)) &&
		std::equal(std::begin(lhs.c[0]), std::end(lhs.c[0]), std::begin(rhs.c[0])) &&
		std::equal(std::begin(lhs.c[1]), std::end(lhs.c[1]), std::begin(rhs.c[1])) &&
		std::equal(std::begin(lhs.c[2]), std::end(lhs.c[2]), std::begin(rhs.c[2])) &&
		std::equal(std::begin(lhs.d[0][0]), std::end(lhs.d[0][0]), std::begin(rhs.d[0][0])) &&
		std::equal(std::begin(lhs.d[0][1]), std::end(lhs.d[0][1]), std::begin(rhs.d[0][1])) &&
		std::equal(std::begin(lhs.d[0][2]), std::end(lhs.d[0][2]), std::begin(rhs.d[0][2])) &&
		std::equal(std::begin(lhs.d[1][0]), std::end(lhs.d[1][0]), std::begin(rhs.d[1][0])) &&
		std::equal(std::begin(lhs.d[1][1]), std::end(lhs.d[1][1]), std::begin(rhs.d[1][1])) &&
		std::equal(std::begin(lhs.d[1][2]), std::end(lhs.d[1][2]), std::begin(rhs.d[1][2])) &&
		std::equal(std::begin(lhs.e), std::end(lhs.e), std::begin(rhs.e));
}

inline bool
operator!=(NativeArrayNonIntrusiveSplit const& lhs, NativeArrayNonIntrusiveSplit const& rhs)
{
	return !(lhs == rhs);
}

template <typename Archive>
inline void
save(Archive& ar, NativeArrayNonIntrusiveSplit const& a)
{
	ar << a.a;
	ar << a.b;
	ar << a.c;
	ar << a.d;
	ar << a.e;
}

template <typename Archive>
inline void
load(Archive& ar, NativeArrayNonIntrusiveSplit& a)
{
	ar >> a.a;
	ar >> a.b;
	ar >> a.c;
	ar >> a.d;
	ar >> a.e;
}

template <typename Stream, typename OArchive, typename IArchive>
void NativeArrayNonIntrusiveSplitTest()
{
	using T = NativeArrayNonIntrusiveSplit;

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

GTEST_TEST(SerializationTest, NativeArrayNonIntrusiveSplitTest)
{
	NativeArrayNonIntrusiveSplitTest<
		std::stringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
	NativeArrayNonIntrusiveSplitTest<
		std::wstringstream,
		bksge::serialization::text_oarchive,
		bksge::serialization::text_iarchive
	>();
}

}	// namespace bksge_serialization_test
