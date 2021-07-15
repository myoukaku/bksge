/**
 *	@file	unit_test_fnd_utility_in_place_index.cpp
 *
 *	@brief	in_place_index のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace in_place_index_test
{

struct Foo
{
	BKSGE_CONSTEXPR Foo(std::size_t i)
		: m_in_place_initialized(false)
		, m_value(i)
	{}

	template <std::size_t I>
	BKSGE_CONSTEXPR Foo(bksge::in_place_index_t<I>)
		: m_in_place_initialized(true)
		, m_value(I)
	{}

	bool           m_in_place_initialized;
	std::size_t  m_value;
};

GTEST_TEST(UtilityTest, InPlaceIndexTest)
{
	BKSGE_CONSTEXPR Foo f1(3);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES) && !defined(_MSC_VER)
	BKSGE_CONSTEXPR Foo f2(bksge::in_place_index<3>);
#else
	BKSGE_CONSTEXPR Foo f2(bksge::in_place_index_t<3>{});
#endif

	BKSGE_CONSTEXPR_EXPECT_FALSE(f1.m_in_place_initialized);
	BKSGE_CONSTEXPR_EXPECT_TRUE (f2.m_in_place_initialized);

	BKSGE_CONSTEXPR_EXPECT_EQ(3u, f1.m_value);
	BKSGE_CONSTEXPR_EXPECT_EQ(3u, f2.m_value);
}

}	// namespace in_place_index_test

}	// namespace bksge_utility_test
