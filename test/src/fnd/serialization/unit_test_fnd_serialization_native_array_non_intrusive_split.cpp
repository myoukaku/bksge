/**
 *	@file	unit_test_fnd_serialization_native_array_non_intrusive_split.cpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
#include <bksge/fnd/algorithm/equal.hpp>
#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
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
		bksge::equal(bksge::begin(lhs.a),       bksge::end(lhs.a),       bksge::begin(rhs.a)) &&
		bksge::equal(bksge::begin(lhs.b),       bksge::end(lhs.b),       bksge::begin(rhs.b)) &&
		bksge::equal(bksge::begin(lhs.c[0]),    bksge::end(lhs.c[0]),    bksge::begin(rhs.c[0])) &&
		bksge::equal(bksge::begin(lhs.c[1]),    bksge::end(lhs.c[1]),    bksge::begin(rhs.c[1])) &&
		bksge::equal(bksge::begin(lhs.c[2]),    bksge::end(lhs.c[2]),    bksge::begin(rhs.c[2])) &&
		bksge::equal(bksge::begin(lhs.d[0][0]), bksge::end(lhs.d[0][0]), bksge::begin(rhs.d[0][0])) &&
		bksge::equal(bksge::begin(lhs.d[0][1]), bksge::end(lhs.d[0][1]), bksge::begin(rhs.d[0][1])) &&
		bksge::equal(bksge::begin(lhs.d[0][2]), bksge::end(lhs.d[0][2]), bksge::begin(rhs.d[0][2])) &&
		bksge::equal(bksge::begin(lhs.d[1][0]), bksge::end(lhs.d[1][0]), bksge::begin(rhs.d[1][0])) &&
		bksge::equal(bksge::begin(lhs.d[1][1]), bksge::end(lhs.d[1][1]), bksge::begin(rhs.d[1][1])) &&
		bksge::equal(bksge::begin(lhs.d[1][2]), bksge::end(lhs.d[1][2]), bksge::begin(rhs.d[1][2])) &&
		bksge::equal(bksge::begin(lhs.e),       bksge::end(lhs.e),       bksge::begin(rhs.e));
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
