/**
 *	@file	unit_test_fnd_iterator_make_reverse_iterator.cpp
 *
 *	@brief	make_reverse_iterator のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/iterator/make_reverse_iterator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace bksge_iterator_test
{

namespace make_reverse_iterator_test
{

inline BKSGE_CXX14_CONSTEXPR bool make_reverse_iterator_test()
{
	char s[] = "123";
	auto it1 = bksge::make_reverse_iterator(s);
	bksge::reverse_iterator<char*> it2(s);
	return it1 == it2;
}

GTEST_TEST(IteratorTest, MakeReverseIteratorTest)
{
	BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(make_reverse_iterator_test());
}

}	// namespace make_reverse_iterator_test

}	// namespace bksge_iterator_test
