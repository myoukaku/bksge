/**
 *	@file	test_macros.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_VARIANT_TEST_MACROS_HPP
#define UNIT_TEST_FND_VARIANT_TEST_MACROS_HPP

#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/config.hpp>

#define ASSERT_NOEXCEPT(...) \
    static_assert(noexcept(__VA_ARGS__), "Operation must be noexcept")

#define ASSERT_NOT_NOEXCEPT(...) \
    static_assert(!noexcept(__VA_ARGS__), "Operation must NOT be noexcept")

#define ASSERT_SAME_TYPE(...) \
    static_assert((bksge::is_same<__VA_ARGS__>::value), \
                 "Types differ unexpectedly")

#define TEST_IGNORE_NODISCARD (void)

#define LIBCPP_ASSERT(...) ((void)0)
#define LIBCPP_STATIC_ASSERT(...) ((void)0)
#define LIBCPP_ASSERT_NOEXCEPT(...) ((void)0)
#define LIBCPP_ASSERT_NOT_NOEXCEPT(...) ((void)0)
#define LIBCPP_ONLY(...) ((void)0)

#if !defined(BKSGE_NO_EXCEPTIONS)
#  define TEST_THROW(...) throw __VA_ARGS__
#else
#  include <stdlib.h>
#  define TEST_THROW(...) ::abort()
#endif

#endif // UNIT_TEST_FND_VARIANT_TEST_MACROS_HPP
