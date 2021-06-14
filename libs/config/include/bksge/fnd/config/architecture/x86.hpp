/**
 *	@file	x86.hpp
 *
 *	@brief	BKSGE_ARCHITECTURE_X86 を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_CONFIG_ARCHITECTURE_X86_HPP
#define BKSGE_FND_CONFIG_ARCHITECTURE_X86_HPP

#if defined(i386)      || defined(__i386__) || \
    defined(__i486__)  || defined(__i586__) || \
    defined(__i686__)  || defined(__i386)   || \
    defined(_M_IX86)   || defined(_X86_)    || \
    defined(__INTEL__) || defined(__I86__)  || \
    defined(__THW_INTEL__)
#  define BKSGE_ARCHITECTURE "x86_32"
#  define BKSGE_ARCHITECTURE_X86_32
#endif

#if defined(__x86_64)  || defined(__x86_64__) || \
    defined(__amd64__) || defined(__amd64)    || \
    defined(_M_X64)
#  define BKSGE_ARCHITECTURE "x86_64"
#  define BKSGE_ARCHITECTURE_X86_64
#endif

#if defined(BKSGE_ARCHITECTURE_X86_32) || defined(BKSGE_ARCHITECTURE_X86_64)
#  define BKSGE_ARCHITECTURE_X86
#endif

#endif // BKSGE_FND_CONFIG_ARCHITECTURE_X86_HPP
