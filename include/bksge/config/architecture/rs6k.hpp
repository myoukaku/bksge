/**
 *	@file	rs6k.hpp
 *
 *	@brief	BKSGE_ARCH_RS6000 を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CONFIG_ARCHITECTURE_RS6K_HPP
#define BKSGE_CONFIG_ARCHITECTURE_RS6K_HPP

#if defined(__THW_RS6000) || defined(_IBMR2)    || \
    defined(_POWER)       || defined(_ARCH_PWR) || \
    defined(_ARCH_PWR2)
#  define BKSGE_ARCH_RS6000
#endif

#endif // BKSGE_CONFIG_ARCHITECTURE_RS6K_HPP
