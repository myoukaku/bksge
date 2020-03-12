/**
 *	@file	unit_test_fnd_algorithm_max.cpp
 *
 *	@brief	max のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <string>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_algorithm_test
{

namespace max_test
{

template <typename T>
void MaxTestUnsigned(void)
{
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  0, bksge::max((T)  0, (T)  0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1, bksge::max((T)  0, (T)  1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1, bksge::max((T)  1, (T)  0));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  1, bksge::max((T)  1, (T)  1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)100, bksge::max((T)100, (T)100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)101, bksge::max((T)100, (T)101));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)101, bksge::max((T)101, (T)100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)101, bksge::max((T)101, (T)101));

	BKSGE_CONSTEXPR_EXPECT_EQ((T)3, bksge::max((T)2, (T)3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)3, bksge::max((T)2, (T)3, bksge::less<>()));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)2, bksge::max((T)2, (T)3, bksge::greater<>()));

	EXPECT_EQ((T)3, bksge::max({(T)3}));
	EXPECT_EQ((T)3, bksge::max({(T)3, (T)1}));
	EXPECT_EQ((T)4, bksge::max({(T)3, (T)1, (T)4}));
	EXPECT_EQ((T)4, bksge::max({(T)3, (T)1, (T)4, (T)1}));
	EXPECT_EQ((T)5, bksge::max({(T)3, (T)1, (T)4, (T)1, (T)5}));
	EXPECT_EQ((T)5, bksge::max({(T)3, (T)1, (T)4, (T)1, (T)5}, bksge::less<>()));
	EXPECT_EQ((T)1, bksge::max({(T)3, (T)1, (T)4, (T)1, (T)5}, bksge::greater<>()));
}

template <typename T>
void MaxTestSigned(void)
{
	MaxTestUnsigned<T>();
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -1, bksge::max((T)  -1, (T)  -1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -1, bksge::max((T)  -1, (T)  -2));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -1, bksge::max((T)  -2, (T)  -1));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)  -2, bksge::max((T)  -2, (T)  -2));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-100, bksge::max((T)-100, (T)-100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-100, bksge::max((T)-100, (T)-101));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-100, bksge::max((T)-101, (T)-100));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-101, bksge::max((T)-101, (T)-101));

	BKSGE_CONSTEXPR_EXPECT_EQ((T)-2, bksge::max((T)-2, (T)-3));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-2, bksge::max((T)-2, (T)-3, bksge::less<>()));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-3, bksge::max((T)-2, (T)-3, bksge::greater<>()));

	EXPECT_EQ((T)-3, bksge::max({(T)-3}));
	EXPECT_EQ((T)-1, bksge::max({(T)-3, (T)-1}));
	EXPECT_EQ((T)-1, bksge::max({(T)-3, (T)-1, (T)-4}));
	EXPECT_EQ((T)-1, bksge::max({(T)-3, (T)-1, (T)-4, (T)-1}));
	EXPECT_EQ((T)-1, bksge::max({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}));
	EXPECT_EQ((T)-1, bksge::max({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}, bksge::less<>()));
	EXPECT_EQ((T)-5, bksge::max({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}, bksge::greater<>()));
}

template <typename T>
void MaxTestFloat(void)
{
	MaxTestSigned<T>();
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.00, bksge::max((T) 0.00, (T) 0.00));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.75, bksge::max((T) 0.50, (T) 0.75));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 0.50, bksge::max((T) 0.50, (T) 0.25));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-0.50, bksge::max((T)-0.50, (T)-0.75));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-0.25, bksge::max((T)-0.50, (T)-0.25));

	BKSGE_CONSTEXPR_EXPECT_EQ((T) 2.5, bksge::max((T) 1.5, (T) 2.5, bksge::less<>()));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-1.5, bksge::max((T)-1.5, (T)-2.5, bksge::less<>()));
	BKSGE_CONSTEXPR_EXPECT_EQ((T) 1.5, bksge::max((T) 1.5, (T) 2.5, bksge::greater<>()));
	BKSGE_CONSTEXPR_EXPECT_EQ((T)-2.5, bksge::max((T)-1.5, (T)-2.5, bksge::greater<>()));

	EXPECT_EQ((T)-3.5, bksge::max({(T)-3.5}));
	EXPECT_EQ((T) 1.5, bksge::max({(T)-3.5, (T)1.5}));
	EXPECT_EQ((T) 4.5, bksge::max({(T)-3.5, (T)1.5, (T)4.5}));
	EXPECT_EQ((T) 4.5, bksge::max({(T)-3.5, (T)1.5, (T)4.5, (T)-1.5}));
	EXPECT_EQ((T) 5.5, bksge::max({(T)-3.5, (T)1.5, (T)4.5, (T)-1.5, (T)5.5}));
	EXPECT_EQ((T) 5.5, bksge::max({(T)-3.5, (T)1.5, (T)4.5, (T)-1.5, (T)5.5}, bksge::less<>()));
	EXPECT_EQ((T)-3.5, bksge::max({(T)-3.5, (T)1.5, (T)4.5, (T)-1.5, (T)5.5}, bksge::greater<>()));
}

GTEST_TEST(AlgorithmTest, MaxTest)
{
	MaxTestUnsigned<unsigned char>();
	MaxTestUnsigned<unsigned short>();
	MaxTestUnsigned<unsigned int>();
	MaxTestUnsigned<unsigned long>();
	MaxTestUnsigned<unsigned long long>();

	MaxTestSigned<signed char>();
	MaxTestSigned<signed short>();
	MaxTestSigned<signed int>();
	MaxTestSigned<signed long>();
	MaxTestSigned<signed long long>();

	MaxTestFloat<float>();
	MaxTestFloat<double>();
	MaxTestFloat<long double>();

	EXPECT_EQ('a', bksge::max({'a'}));
	EXPECT_EQ('z', bksge::max({'a', 'z'}));
	EXPECT_EQ('c', bksge::max({'a', 'c', 'b'}));
	EXPECT_EQ("hoge", bksge::max(std::string("foo"), std::string("hoge")));
	EXPECT_EQ("zzzz", bksge::max({std::string("abc"), std::string("ABC"), std::string("zzzz")}));
}

}	// namespace max_test

}	// namespace bksge_algorithm_test
