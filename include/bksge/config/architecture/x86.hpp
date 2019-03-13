/**
 *	@file	x86.hpp
 *
 *	@brief	BKSGE_ARCH_X86 を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_ARCHITECTURE_X86_HPP
#define BKSGE_CONFIG_ARCHITECTURE_X86_HPP

#if defined(i386)      || defined(__i386__) || \
    defined(__i486__)  || defined(__i586__) || \
    defined(__i686__)  || defined(__i386)   || \
    defined(_M_IX86)   || defined(_X86_)    || \
    defined(__INTEL__) || defined(__I86__)  || \
    defined(__THW_INTEL__)
#  define BKSGE_ARCH_X86_32
#endif

#if defined(__x86_64)  || defined(__x86_64__) || \
    defined(__amd64__) || defined(__amd64)    || \
    defined(_M_X64)
#  define BKSGE_ARCH_X86_64
#endif

#if defined(BKSGE_ARCH_X86_32) || defined(BKSGE_ARCH_X86_64)
#  define BKSGE_ARCH_X86
#endif

#endif // BKSGE_CONFIG_ARCHITECTURE_X86_HPP
