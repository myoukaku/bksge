/**
 *	@file	config.hpp
 *
 *	@brief	Bksge全体の設定
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_HPP
#define BKSGE_FND_CONFIG_HPP

#include <bksge/fnd/config/prefix.hpp>

#if !defined(BKSGE_USER_CONFIG) && !defined(BKSGE_NO_USER_CONFIG)
#	define BKSGE_USER_CONFIG <bksge/fnd/config/user.hpp>
#endif
#if defined(BKSGE_USER_CONFIG)
#	include BKSGE_USER_CONFIG
#endif

#if !defined(BKSGE_COMPILER_CONFIG) && !defined(BKSGE_NO_COMPILER_CONFIG) && !defined(BKSGE_NO_CONFIG)
#	include <bksge/fnd/config/select_compiler_config.hpp>
#endif
#if defined(BKSGE_COMPILER_CONFIG)
#	include BKSGE_COMPILER_CONFIG
#endif

#if !defined(BKSGE_STDLIB_CONFIG) && !defined(BKSGE_NO_STDLIB_CONFIG) && !defined(BKSGE_NO_CONFIG) && defined(__cplusplus)
#	include <bksge/fnd/config/select_stdlib_config.hpp>
#endif
#if defined(BKSGE_STDLIB_CONFIG)
#	include BKSGE_STDLIB_CONFIG
#endif

#if !defined(BKSGE_PLATFORM_CONFIG) && !defined(BKSGE_NO_PLATFORM_CONFIG) && !defined(BKSGE_NO_CONFIG)
#	include <bksge/fnd/config/select_platform_config.hpp>
#endif
#if defined(BKSGE_PLATFORM_CONFIG)
#	include BKSGE_PLATFORM_CONFIG
#endif

#include <bksge/fnd/config/architecture.hpp>
#include <bksge/fnd/config/suffix.hpp>

#endif // BKSGE_FND_CONFIG_HPP
