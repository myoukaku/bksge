/**
 *	@file	select_stdlib_config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_SELECT_STDLIB_CONFIG_HPP
#define BKSGE_CONFIG_SELECT_STDLIB_CONFIG_HPP

#ifdef __cplusplus
#  include <cstddef>
#else
#  include <stddef.h>
#endif

#if defined(_LIBCPP_VERSION)
// libc++
#  define BKSGE_STDLIB_CONFIG	"bksge/config/stdlib/libcpp.hpp"

#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
// GNU libstdc++ 3
#  define BKSGE_STDLIB_CONFIG	"bksge/config/stdlib/libstdcpp3.hpp"

#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
// Dinkumware Library
#  define BKSGE_STDLIB_CONFIG	"bksge/config/stdlib/dinkumware.hpp"

#else
#  error "Unknown standard library"

#endif

#endif // BKSGE_CONFIG_SELECT_STDLIB_CONFIG_HPP
