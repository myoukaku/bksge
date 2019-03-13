/**
 *	@file	config.hpp
 *
 *	@brief	Bksge全体の設定
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_HPP
#define BKSGE_CONFIG_HPP

#include <bksge/config/prefix.hpp>

#if !defined(BKSGE_USER_CONFIG) && !defined(BKSGE_NO_USER_CONFIG)
#	define BKSGE_USER_CONFIG <bksge/config/user.hpp>
#endif
#if defined(BKSGE_USER_CONFIG)
#	include BKSGE_USER_CONFIG
#endif

#if !defined(BKSGE_COMPILER_CONFIG) && !defined(BKSGE_NO_COMPILER_CONFIG) && !defined(BKSGE_NO_CONFIG)
#	include <bksge/config/select_compiler_config.hpp>
#endif
#if defined(BKSGE_COMPILER_CONFIG)
#	include BKSGE_COMPILER_CONFIG
#endif

#if !defined(BKSGE_STDLIB_CONFIG) && !defined(BKSGE_NO_STDLIB_CONFIG) && !defined(BKSGE_NO_CONFIG) && defined(__cplusplus)
#	include <bksge/config/select_stdlib_config.hpp>
#endif
#if defined(BKSGE_STDLIB_CONFIG)
#	include BKSGE_STDLIB_CONFIG
#endif

#if !defined(BKSGE_PLATFORM_CONFIG) && !defined(BKSGE_NO_PLATFORM_CONFIG) && !defined(BKSGE_NO_CONFIG)
#	include <bksge/config/select_platform_config.hpp>
#endif
#if defined(BKSGE_PLATFORM_CONFIG)
#	include BKSGE_PLATFORM_CONFIG
#endif

#include <bksge/config/architecture.hpp>
#include <bksge/config/suffix.hpp>

#endif // BKSGE_CONFIG_HPP
