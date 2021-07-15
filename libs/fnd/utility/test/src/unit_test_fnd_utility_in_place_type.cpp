/**
 *	@file	unit_test_fnd_utility_in_place_type.cpp
 *
 *	@brief	in_place_type のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/config.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "constexpr_test.hpp"

namespace bksge_utility_test
{

namespace in_place_type_test
{

struct Foo
{
	BKSGE_CONSTEXPR Foo(std::size_t i)
		: m_in_place_initialized(false)
		, m_value(i)
	{}

	template <typename T>
	BKSGE_CONSTEXPR Foo(bksge::in_place_type_t<T>)
		: m_in_place_initialized(true)
		, m_value(sizeof(T))
	{}

	bool           m_in_place_initialized;
	std::size_t  m_value;
};

GTEST_TEST(UtilityTest, InPlaceTypeTest)
{
	BKSGE_CONSTEXPR Foo f1(3);
#if defined(BKSGE_HAS_CXX14_VARIABLE_TEMPLATES) && !defined(_MSC_VER)
	BKSGE_CONSTEXPR Foo f2(bksge::in_place_type<char>);
#else
	BKSGE_CONSTEXPR Foo f2(bksge::in_place_type_t<char>{});
#endif

	BKSGE_CONSTEXPR_EXPECT_FALSE(f1.m_in_place_initialized);
	BKSGE_CONSTEXPR_EXPECT_TRUE (f2.m_in_place_initialized);

	BKSGE_CONSTEXPR_EXPECT_EQ(3u, f1.m_value);
	BKSGE_CONSTEXPR_EXPECT_EQ(1u, f2.m_value);
}

}	// namespace in_place_type_test

}	// namespace bksge_utility_test
