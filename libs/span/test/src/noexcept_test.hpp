/**
 *	@file	noexcept_test.hpp
 *
 *	@brief	
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_NOEXCEPT_TEST_HPP
#define UNIT_TEST_NOEXCEPT_TEST_HPP

#define BKSGE_ASSERT_NOEXCEPT(...) \
    static_assert(noexcept(__VA_ARGS__), "Operation must be noexcept")

#endif // UNIT_TEST_NOEXCEPT_TEST_HPP
