/**
 *	@file	ia64.hpp
 *
 *	@brief	BKSGE_ARCH_IA64 を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_ARCHITECTURE_IA64_HPP
#define BKSGE_CONFIG_ARCHITECTURE_IA64_HPP

#if defined(__ia64__) || defined(_IA64)  || \
    defined(__IA64__) || defined(__ia64) || \
    defined(_M_IA64)  || defined(__itanium__)
#  define BKSGE_ARCH_IA64
#endif

#endif // BKSGE_CONFIG_ARCHITECTURE_IA64_HPP
