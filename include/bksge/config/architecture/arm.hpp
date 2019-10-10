/**
 *	@file	arm.hpp
 *
 *	@brief	BKSGE_ARCHITECTURE_ARM を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_ARCHITECTURE_ARM_HPP
#define BKSGE_CONFIG_ARCHITECTURE_ARM_HPP

#if defined(__arm__) || defined(__arm64)  || defined(__thumb__) || \
    defined(_M_ARM)  || defined(_M_ARM64) || \
    defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB)
#  define BKSGE_ARCHITECTURE "arm"
#  define BKSGE_ARCHITECTURE_ARM
#endif

#endif // BKSGE_CONFIG_ARCHITECTURE_ARM_HPP
