/**
 *	@file	test_workarounds.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_VARIANT_TEST_WORKAROUNDS_HPP
#define UNIT_TEST_FND_VARIANT_TEST_WORKAROUNDS_HPP

#include <bksge/fnd/config.hpp>

#if defined(BKSGE_MSVC)
#  define TEST_WORKAROUND_C1XX_BROKEN_IS_TRIVIALLY_COPYABLE
#  if !defined(_MSC_EXTENSIONS)
#    define TEST_WORKAROUND_C1XX_BROKEN_ZA_CTOR_CHECK
#  endif
#else
// TODO
#  define TEST_WORKAROUND_C1XX_BROKEN_IS_TRIVIALLY_COPYABLE
#endif

#if defined(BKSGE_MSVC) || (defined(BKSGE_GCC) && (BKSGE_GCC < 90000))
#  define TEST_WORKAROUND_CONSTEXPR_IMPLIES_NOEXCEPT
#endif

#endif // UNIT_TEST_FND_VARIANT_TEST_WORKAROUNDS_HPP
