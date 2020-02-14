/**
 *	@file	constexpr_test.hpp
 *
 *	@brief	
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_CONSTEXPR_TEST_HPP
#define UNIT_TEST_CONSTEXPR_TEST_HPP

#include <bksge/fnd/config.hpp>
#include <bksge/fnd/cmath/fabs.hpp>

#if defined(BKSGE_HAS_CXX11_CONSTEXPR)

#  define BKSGE_CONSTEXPR_EXPECT_EQ(x, y)	\
	static_assert((x) == (y), "");	\
	EXPECT_EQ(x, y)

#  define BKSGE_CONSTEXPR_EXPECT_NE(x, y)	\
	static_assert((x) != (y), "");	\
	EXPECT_NE(x, y)

#  define BKSGE_CONSTEXPR_EXPECT_TRUE(x)	\
	static_assert((x), #x);	\
	EXPECT_TRUE(x)

#  define BKSGE_CONSTEXPR_EXPECT_FALSE(x)	\
	static_assert(!(x), #x);	\
	EXPECT_FALSE(x)

#  define BKSGE_CONSTEXPR_EXPECT_NEAR(val1, val2, abs_error)	\
	static_assert(bksge::fabs((val1) - (val2)) <= (abs_error), "");	\
	EXPECT_NEAR(val1, val2, abs_error)

#else

#  define BKSGE_CONSTEXPR_EXPECT_EQ(x, y)	\
	EXPECT_EQ(x, y)

#  define BKSGE_CONSTEXPR_EXPECT_NE(x, y)	\
	EXPECT_NE(x, y)

#  define BKSGE_CONSTEXPR_EXPECT_TRUE(x)	\
	EXPECT_TRUE(x)

#  define BKSGE_CONSTEXPR_EXPECT_FALSE(x)	\
	EXPECT_FALSE(x)

#  define BKSGE_CONSTEXPR_EXPECT_NEAR(val1, val2, abs_error)	\
	EXPECT_NEAR(val1, val2, abs_error)

#endif


#if defined(BKSGE_HAS_CXX14_CONSTEXPR)

#  define BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(x, y)	\
	static_assert((x) == (y), "");	\
	EXPECT_EQ(x, y)

#  define BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(x)	\
	static_assert((x), #x);	\
	EXPECT_TRUE(x)

#  define BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(x)	\
	static_assert(!(x), #x);	\
	EXPECT_FALSE(x)

#  define BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(val1, val2, abs_error)	\
	static_assert(bksge::fabs((val1) - (val2)) <= (abs_error), "");	\
	EXPECT_NEAR(val1, val2, abs_error)

#else

#  define BKSGE_CXX14_CONSTEXPR_EXPECT_EQ(x, y)	\
	EXPECT_EQ(x, y)

#  define BKSGE_CXX14_CONSTEXPR_EXPECT_TRUE(x)	\
	EXPECT_TRUE(x)

#  define BKSGE_CXX14_CONSTEXPR_EXPECT_FALSE(x)	\
	EXPECT_FALSE(x)

#  define BKSGE_CXX14_CONSTEXPR_EXPECT_NEAR(val1, val2, abs_error)	\
	EXPECT_NEAR(val1, val2, abs_error)

#endif


#if defined(BKSGE_HAS_CXX17_CONSTEXPR)

#  define BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(x, y)	\
	static_assert((x) == (y), "");	\
	EXPECT_EQ(x, y)

#  define BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(x)	\
	static_assert((x), #x);	\
	EXPECT_TRUE(x)

#  define BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(x)	\
	static_assert(!(x), #x);	\
	EXPECT_FALSE(x)

#  define BKSGE_CXX17_CONSTEXPR_EXPECT_NEAR(val1, val2, abs_error)	\
	static_assert(bksge::fabs((val1) - (val2)) <= (abs_error), "");	\
	EXPECT_NEAR(val1, val2, abs_error)

#else

#  define BKSGE_CXX17_CONSTEXPR_EXPECT_EQ(x, y)	\
	EXPECT_EQ(x, y)

#  define BKSGE_CXX17_CONSTEXPR_EXPECT_TRUE(x)	\
	EXPECT_TRUE(x)

#  define BKSGE_CXX17_CONSTEXPR_EXPECT_FALSE(x)	\
	EXPECT_FALSE(x)

#  define BKSGE_CXX17_CONSTEXPR_EXPECT_NEAR(val1, val2, abs_error)	\
	EXPECT_NEAR(val1, val2, abs_error)

#endif

#endif // UNIT_TEST_CONSTEXPR_TEST_HPP
