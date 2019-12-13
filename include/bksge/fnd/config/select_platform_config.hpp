/**
 *	@file	select_platform_config.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_SELECT_PLATFORM_CONFIG_HPP
#define BKSGE_FND_CONFIG_SELECT_PLATFORM_CONFIG_HPP

#if (defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)) && !defined(_CRAYC)
// linux
#  define BKSGE_PLATFORM_CONFIG "bksge/fnd/config/platform/linux.hpp"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
// win32:
#  define BKSGE_PLATFORM_CONFIG	"bksge/fnd/config/platform/win32.hpp"

#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
// MacOS
#  define BKSGE_PLATFORM_CONFIG "bksge/fnd/config/platform/macos.hpp"

#else
#  error "Unknown platform"

#endif

#endif // BKSGE_FND_CONFIG_SELECT_PLATFORM_CONFIG_HPP
